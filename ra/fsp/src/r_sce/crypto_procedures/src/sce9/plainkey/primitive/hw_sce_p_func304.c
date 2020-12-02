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

void HW_SCE_p_func304(void)
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
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x00000024u;
    SCE->REG_ECH = 0x00003c1eu;
    SCE->REG_28H = 0x00bf0001u;
    SCE->REG_ECH = 0x0000d779u;
    SCE->REG_28H = 0x00870001u;
    SCE->REG_ECH = 0x00000b18u;
    SCE->REG_E0H = 0x80010300u;
    SCE->REG_00H = 0x00008307u;
    SCE->REG_2CH = 0x000000adu;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    SCE->REG_00H = 0x0000031fu;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    SCE->REG_28H = 0x00bf0001u;
    SCE->REG_ECH = 0x3800db1fu;
    SCE->REG_E0H = 0x00000080u;
    SCE->REG_1CH = 0x00A60000u;
    HW_SCE_p_func100(0xe5986152u, 0x77a0ec4cu, 0x96bf2690u, 0x6a2cacffu);
    SCE->REG_1CH = 0x00400000u;
    SCE->REG_1D0H = 0x00000000u;
    if (1u == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func101(0x10ff3fe3u, 0x4b460b48u, 0x277e1172u, 0x463feb78u);
    }
    else
    {
        SCE->REG_28H = 0x00800001u;
        SCE->REG_24H = 0x000001c0u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_34H = 0x00000400u;
        SCE->REG_24H = 0x800080c1u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x00000581u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x000080c1u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_28H = 0x00bf0001u;
        SCE->REG_24H = 0x000001c0u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x04001991u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x0000c0c1u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_28H = 0x00800001u;
        SCE->REG_24H = 0x000011c0u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_34H = 0x00000004u;
        SCE->REG_24H = 0x82001191u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x000080c1u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_28H = 0x00bf0001u;
        SCE->REG_ECH = 0x0000d379u;
        HW_SCE_p_func101(0x969611fbu, 0x4648fd51u, 0x43577ed6u, 0xff05cec7u);
    }
    HW_SCE_p_func100(0xab8c8692u, 0xebf4f03eu, 0xcca553b8u, 0x62b91c3au);
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x017da167u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xf2ca2938u, 0xa80f39e9u, 0xc43330dau, 0xf5fde800u);
    SCE->REG_00H = 0x00012303u;
    SCE->REG_2CH = 0x00000024u;
    HW_SCE_p_func313(1156);
    HW_SCE_p_func100(0xb49d7ef6u, 0x65fe3fafu, 0xcdf2ff51u, 0x40cac15bu);
    HW_SCE_p_func314(1156+64);
    SCE->REG_ECH = 0x00000b5au;
    SCE->REG_24H = 0x000001c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_ECH = 0x0000d77cu;
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x00000000u;
    SCE->REG_ECH = 0x3800db7au;
    SCE->REG_E0H = 0x00000080u;
    SCE->REG_1CH = 0x00A60000u;
    HW_SCE_p_func100(0x01dd3aa3u, 0xe9b30484u, 0xe9ee2277u, 0xf9d02553u);
    SCE->REG_1CH = 0x00400000u;
    SCE->REG_1D0H = 0x00000000u;
    if (1u == (SCE->REG_1CH_b.B22))
    {
        SCE->REG_28H = 0x00800001u;
        SCE->REG_24H = 0x000001c0u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_34H = 0x00000400u;
        SCE->REG_24H = 0x800080c1u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_104H = 0x00000157u;
        SCE->REG_2CH = 0x00000050u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000001u);
        SCE->REG_E0H = 0x8181001eu;
        SCE->REG_00H = 0x00003807u;
        SCE->REG_2CH = 0x00000110u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        SCE->REG_2CH = 0x00000050u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000u);
        SCE->REG_24H = 0x000011c0u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_28H = 0x00bf0001u;
        oLoop1 = 1;
        while(oLoop1 == 1)
        {
            SCE->REG_1CH = 0x00210000u;
            HW_SCE_p_func100(0xd26d42ffu, 0xc3695e06u, 0x9cf5af99u, 0x9bfeede5u);
            SCE->REG_1CH = 0x00400000u;
            SCE->REG_1D0H = 0x00000000u;
            if (1u == (SCE->REG_1CH_b.B22))
            {
                SCE->REG_24H = 0x000009c0u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x04001981u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x000040c1u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_28H = 0x00800001u;
                SCE->REG_24H = 0x000011c0u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_34H = 0x00000004u;
                SCE->REG_24H = 0x82001181u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x000080c1u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_28H = 0x00bf0001u;
                SCE->REG_ECH = 0x00003340u;
                HW_SCE_p_func101(0xefd40792u, 0x390bb84au, 0x4c63e1c2u, 0x269e897bu);
            }
            else
            {
                HW_SCE_p_func101(0x7ea798c1u, 0x39d52927u, 0xb2a79290u, 0xfca05510u);
                oLoop1 = 0;
            }
        }
        SCE->REG_ECH = 0x0000d37cu;
        SCE->REG_ECH = 0x00000b9cu;
        SCE->REG_ECH = 0x00002b9au;
        SCE->REG_ECH = 0x0000375cu;
        HW_SCE_p_func101(0xb4818009u, 0x9240b2ceu, 0x392a2156u, 0xedf546aeu);
    }
    else
    {
        SCE->REG_28H = 0x00800001u;
        SCE->REG_E0H = 0x8181001eu;
        SCE->REG_00H = 0x00003807u;
        SCE->REG_2CH = 0x00000010u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        SCE->REG_24H = 0x000001c0u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_34H = 0x00000400u;
        SCE->REG_24H = 0x800080c1u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_28H = 0x00bf0001u;
        SCE->REG_24H = 0x000009c0u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x04001991u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x000040c1u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_28H = 0x00800001u;
        SCE->REG_24H = 0x000011c0u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_34H = 0x00000004u;
        SCE->REG_24H = 0x82001191u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x000080c1u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_28H = 0x00bf0001u;
        oLoop1 = 1;
        while(oLoop1 == 1)
        {
            SCE->REG_1CH = 0x00210000u;
            HW_SCE_p_func100(0xcf9e1796u, 0xe867c7f2u, 0x0c8b147au, 0x5844a87eu);
            SCE->REG_1CH = 0x00400000u;
            SCE->REG_1D0H = 0x00000000u;
            if (1u == (SCE->REG_1CH_b.B22))
            {
                SCE->REG_24H = 0x000009c0u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x04001981u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x000040c1u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_28H = 0x00800001u;
                SCE->REG_24H = 0x000011c0u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_34H = 0x00000004u;
                SCE->REG_24H = 0x82001181u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x000080c1u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_28H = 0x00bf0001u;
                HW_SCE_p_func101(0x64029b2fu, 0x0f0e1921u, 0x574ab5cbu, 0x278bca4bu);
                oLoop1 = 0;
            }
            else
            {
                SCE->REG_24H = 0x000009c0u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x04001991u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x000040c1u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_28H = 0x00800001u;
                SCE->REG_24H = 0x000011c0u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_34H = 0x00000004u;
                SCE->REG_24H = 0x82001191u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x000080c1u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_28H = 0x00bf0001u;
                SCE->REG_ECH = 0x00002f40u;
                HW_SCE_p_func101(0xe2b49ae6u, 0x659727f9u, 0x3a18be25u, 0x6e781766u);
            }
        }
        HW_SCE_p_func101(0xa170ddb7u, 0x02cde70cu, 0x20f0afa1u, 0x6e9e2b7au);
    }
    SCE->REG_24H = 0x000088d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x000000a0u;
    SCE->REG_E0H = 0x81c0001eu;
    SCE->REG_00H = 0x00013803u;
    SCE->REG_2CH = 0x00000012u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x000000a0u;
    SCE->REG_E0H = 0x80c0001eu;
    SCE->REG_00H = 0x00018303u;
    SCE->REG_2CH = 0x00000020u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    SCE->REG_ECH = 0x00000b39u;
    SCE->REG_24H = 0x000001c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_ECH = 0x0000d77du;
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x00000004u;
    SCE->REG_ECH = 0x3800db7bu;
    SCE->REG_E0H = 0x00000080u;
    SCE->REG_1CH = 0x00A60000u;
    HW_SCE_p_func100(0x3d1e1391u, 0xc39a7bdbu, 0x02df7a57u, 0xa1095da7u);
    SCE->REG_1CH = 0x00400000u;
    SCE->REG_1D0H = 0x00000000u;
    if (1u == (SCE->REG_1CH_b.B22))
    {
        SCE->REG_28H = 0x00800001u;
        SCE->REG_24H = 0x000001c0u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_34H = 0x00000400u;
        SCE->REG_24H = 0x800080c1u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_104H = 0x00000157u;
        SCE->REG_2CH = 0x00000050u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000001u);
        SCE->REG_E0H = 0x8181001eu;
        SCE->REG_00H = 0x00003807u;
        SCE->REG_2CH = 0x00000110u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        SCE->REG_2CH = 0x00000050u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000u);
        SCE->REG_24H = 0x000011c0u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_28H = 0x00bf0001u;
        oLoop1 = 1;
        while(oLoop1 == 1)
        {
            SCE->REG_1CH = 0x00210000u;
            HW_SCE_p_func100(0x9ffb65aau, 0x2cf47374u, 0x960cbf4bu, 0xe0d92891u);
            SCE->REG_1CH = 0x00400000u;
            SCE->REG_1D0H = 0x00000000u;
            if (1u == (SCE->REG_1CH_b.B22))
            {
                SCE->REG_24H = 0x000009c0u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x04001981u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x000040c1u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_28H = 0x00800001u;
                SCE->REG_24H = 0x000011c0u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_34H = 0x00000004u;
                SCE->REG_24H = 0x82001181u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x000080c1u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_28H = 0x00bf0001u;
                SCE->REG_ECH = 0x00003320u;
                HW_SCE_p_func101(0x9f6d4d47u, 0x5a540a97u, 0x90e36ff3u, 0xb3e0c0e5u);
            }
            else
            {
                HW_SCE_p_func101(0x428b2571u, 0xa7416f10u, 0x0de2c174u, 0x45a203f0u);
                oLoop1 = 0;
            }
        }
        SCE->REG_ECH = 0x0000d37du;
        SCE->REG_ECH = 0x00000b9cu;
        SCE->REG_ECH = 0x00002b99u;
        SCE->REG_ECH = 0x0000373cu;
        HW_SCE_p_func101(0x6acd5fb2u, 0xdf585e2eu, 0x1c716be9u, 0xff0414eau);
    }
    else
    {
        SCE->REG_28H = 0x00800001u;
        SCE->REG_E0H = 0x8181001eu;
        SCE->REG_00H = 0x00003807u;
        SCE->REG_2CH = 0x00000010u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        SCE->REG_24H = 0x000001c0u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_34H = 0x00000400u;
        SCE->REG_24H = 0x800080c1u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_28H = 0x00bf0001u;
        SCE->REG_24H = 0x000009c0u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x04001991u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x000040c1u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_28H = 0x00800001u;
        SCE->REG_24H = 0x000011c0u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_34H = 0x00000004u;
        SCE->REG_24H = 0x82001191u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x000080c1u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_28H = 0x00bf0001u;
        oLoop1 = 1;
        while(oLoop1 == 1)
        {
            SCE->REG_1CH = 0x00210000u;
            HW_SCE_p_func100(0xcdb35358u, 0x9476764cu, 0xa8981e90u, 0xdd46be8bu);
            SCE->REG_1CH = 0x00400000u;
            SCE->REG_1D0H = 0x00000000u;
            if (1u == (SCE->REG_1CH_b.B22))
            {
                SCE->REG_24H = 0x000009c0u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x04001981u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x000040c1u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_28H = 0x00800001u;
                SCE->REG_24H = 0x000011c0u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_34H = 0x00000004u;
                SCE->REG_24H = 0x82001181u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x000080c1u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_28H = 0x00bf0001u;
                HW_SCE_p_func101(0xbd0b86adu, 0x8c871c31u, 0xdfd5d06cu, 0xf4194799u);
                oLoop1 = 0;
            }
            else
            {
                SCE->REG_24H = 0x000009c0u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x04001991u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x000040c1u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_28H = 0x00800001u;
                SCE->REG_24H = 0x000011c0u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_34H = 0x00000004u;
                SCE->REG_24H = 0x82001191u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x000080c1u;
                /* WAIT_LOOP */
                while (0u != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_28H = 0x00bf0001u;
                SCE->REG_ECH = 0x00002f20u;
                HW_SCE_p_func101(0x568a7b8bu, 0x164d8cdeu, 0xdb712a97u, 0xf572288du);
            }
        }
        HW_SCE_p_func101(0xc33dc603u, 0x8a8373acu, 0x372774ccu, 0x978192f9u);
    }
    HW_SCE_p_func100(0x3461b0c9u, 0xd8ad5898u, 0xe4570345u, 0x8d731553u);
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x013fd1d7u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xcdb27765u, 0x54ad18a7u, 0x2a027349u, 0xaa40ee12u);
    SCE->REG_00H = 0x00012303u;
    SCE->REG_2CH = 0x00000022u;
    HW_SCE_p_func313(1088);
    HW_SCE_p_func100(0x6ca37557u, 0xd24a3739u, 0x7c970af6u, 0x200ecc3eu);
    HW_SCE_p_func314(1088+64);
    HW_SCE_p_func100(0x65e7019au, 0xc524e055u, 0x269764ceu, 0x48b54eefu);
    SCE->REG_28H = 0x00bf0001u;
    SCE->REG_24H = 0x000088d0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x000000a0u;
    SCE->REG_E0H = 0x81c0001eu;
    SCE->REG_00H = 0x00013803u;
    SCE->REG_2CH = 0x00000012u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    SCE->REG_28H = 0x00870001u;
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x00000050u;
    SCE->REG_E0H = 0x8088001eu;
    SCE->REG_00H = 0x00008323u;
    SCE->REG_2CH = 0x00000022u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x00000070u;
    SCE->REG_E0H = 0x8088001eu;
    SCE->REG_00H = 0x00008323u;
    SCE->REG_2CH = 0x00000020u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    SCE->REG_28H = 0x00bf0001u;
    SCE->REG_24H = 0x0000480cu;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01a2b89bu);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xdbfd0b8cu, 0x55072b70u, 0x2b8d035au, 0xe0f5939au);
    SCE->REG_00H = 0x00012303u;
    SCE->REG_2CH = 0x00000022u;
    HW_SCE_p_func313(1224);
    HW_SCE_p_func100(0xdc20f138u, 0xd0d20635u, 0x62fe940fu, 0x16494aeeu);
    HW_SCE_p_func314(1224+64);
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x000000a0u;
    SCE->REG_E0H = 0x81c0001eu;
    SCE->REG_00H = 0x00013803u;
    SCE->REG_2CH = 0x00000012u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    SCE->REG_28H = 0x00800001u;
    SCE->REG_2CH = 0x00000000u;
    SCE->REG_24H = 0x0000080au;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_E0H = 0x80010380u;
    SCE->REG_00H = 0x00008307u;
    SCE->REG_2CH = 0x00000020u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    SCE->REG_28H = 0x00870001u;
    SCE->REG_E0H = 0x800103a0u;
    SCE->REG_00H = 0x00008307u;
    SCE->REG_2CH = 0x000000adu;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    SCE->REG_00H = 0x0000031fu;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    SCE->REG_2CH = 0x00000012u;
    SCE->REG_104H = 0x00000767u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x40000000u);
    SCE->REG_100H = change_endian_long(0x00000000u);
    SCE->REG_100H = change_endian_long(0x00000000u);
    SCE->REG_100H = change_endian_long(0x00000000u);
    SCE->REG_100H = change_endian_long(0x00000000u);
    SCE->REG_100H = change_endian_long(0x00000000u);
    SCE->REG_100H = change_endian_long(0x00000000u);
    SCE->REG_100H = change_endian_long(0x00000000u);
    SCE->REG_34H = 0x00000030u;
    SCE->REG_24H = 0x80001dc0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_ECH = 0x3800dbbeu;
    SCE->REG_E0H = 0x00000080u;
    SCE->REG_1CH = 0x00A60000u;
    HW_SCE_p_func100(0x71b9f77bu, 0x15ebca7bu, 0xf7ac0f68u, 0x4f17baf2u);
    SCE->REG_1CH = 0x00400000u;
    SCE->REG_1D0H = 0x00000000u;
    if (1u == (SCE->REG_1CH_b.B22))
    {
        SCE->REG_24H = 0x00000991u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_ECH = 0x0000d375u;
        HW_SCE_p_func101(0x3adaeacau, 0x6e43d4abu, 0x8db7589fu, 0xc4323a0eu);
    }
    else
    {
        SCE->REG_24H = 0x00000981u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_ECH = 0x0000d775u;
        HW_SCE_p_func101(0x7efebc70u, 0xe8bbac54u, 0x76d54f63u, 0xc908420bu);
    }
    HW_SCE_p_func100(0xc22d191fu, 0x4585204au, 0xe46132b0u, 0x3b5fcb5au);
    SCE->REG_34H = 0x00000c00u;
    SCE->REG_24H = 0x8000e0c1u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00bf0001u;
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x013d2cc1u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x6d3ccc34u, 0xfd034277u, 0xe9f917a1u, 0x4b7fe353u);
    SCE->REG_00H = 0x00012303u;
    SCE->REG_2CH = 0x00000024u;
    HW_SCE_p_func313(1428);
    HW_SCE_p_func100(0xae117735u, 0x1a2569e6u, 0x41130d87u, 0x42e20119u);
    HW_SCE_p_func314(1428+64);
    HW_SCE_p_func100(0x0f09dc1bu, 0x0d25ed9bu, 0xc647791bu, 0x2b003f89u);
    SCE->REG_28H = 0x00870001u;
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x00000050u;
    SCE->REG_E0H = 0x8188001eu;
    SCE->REG_00H = 0x00003823u;
    SCE->REG_2CH = 0x00000012u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x00000070u;
    SCE->REG_E0H = 0x8188001eu;
    SCE->REG_00H = 0x00003823u;
    SCE->REG_2CH = 0x00000010u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    SCE->REG_28H = 0x00bf0001u;
    SCE->REG_24H = 0x000009c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000019a1u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000040c1u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000011c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000019a1u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000080c1u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000c80cu;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01a2b89bu);
    HW_SCE_p_func080();
    SCE->REG_00H = 0x00013203u;
    SCE->REG_2CH = 0x00000012u;
    HW_SCE_p_func312(1224);
    SCE->REG_ECH = 0x0000d776u;
    SCE->REG_ECH = 0x3800db75u;
    SCE->REG_E0H = 0x00000080u;
    SCE->REG_1CH = 0x00A60000u;
    HW_SCE_p_func100(0x5cc64a69u, 0xf2a44982u, 0xc740beb0u, 0x6a2516bdu);
    SCE->REG_1CH = 0x00400000u;
    SCE->REG_1D0H = 0x00000000u;
    if (1u == (SCE->REG_1CH_b.B22))
    {
        SCE->REG_24H = 0x000019c0u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x00000991u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x000040c1u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00210000u;
        HW_SCE_p_func100(0x33b90ce4u, 0x5db0e894u, 0x00e112ddu, 0xf58dcd06u);
        SCE->REG_1CH = 0x00400000u;
        SCE->REG_1D0H = 0x00000000u;
        if (1u == (SCE->REG_1CH_b.B22))
        {
            SCE->REG_ECH = 0x0000d376u;
            SCE->REG_28H = 0x00800001u;
            SCE->REG_104H = 0x00000257u;
            SCE->REG_2CH = 0x00000050u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000001u);
            SCE->REG_2CH = 0x00000110u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0xFFFFFFFFu);
            SCE->REG_2CH = 0x00000050u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000000u);
            SCE->REG_28H = 0x00bf0001u;
            HW_SCE_p_func101(0xae9e04cfu, 0xd330fbdeu, 0x30d4edf8u, 0xc9a2ff40u);
        }
        else
        {
            SCE->REG_ECH = 0x0000d776u;
            SCE->REG_28H = 0x00800001u;
            SCE->REG_2CH = 0x00000010u;
            SCE->REG_104H = 0x00000067u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000000u);
            SCE->REG_28H = 0x00bf0001u;
            HW_SCE_p_func101(0xcd1f90deu, 0x9ac953a4u, 0xfeda1414u, 0xec875363u);
        }
    }
    else
    {
        SCE->REG_24H = 0x000009c0u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x00001991u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x000040c1u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00210000u;
        HW_SCE_p_func100(0x5f5687adu, 0xae101c00u, 0x054dc8e3u, 0x12360356u);
        SCE->REG_1CH = 0x00400000u;
        SCE->REG_1D0H = 0x00000000u;
        if (1u == (SCE->REG_1CH_b.B22))
        {
            SCE->REG_ECH = 0x0000d376u;
            SCE->REG_28H = 0x00800001u;
            SCE->REG_104H = 0x00000257u;
            SCE->REG_2CH = 0x00000050u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000001u);
            SCE->REG_2CH = 0x00000110u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0xFFFFFFFFu);
            SCE->REG_2CH = 0x00000050u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000000u);
            SCE->REG_28H = 0x00bf0001u;
            HW_SCE_p_func101(0xffbb0cbcu, 0x0e646d5cu, 0xce376485u, 0x470e965bu);
        }
        else
        {
            SCE->REG_ECH = 0x0000d776u;
            SCE->REG_28H = 0x00800001u;
            SCE->REG_2CH = 0x00000010u;
            SCE->REG_104H = 0x00000067u;
            /* WAIT_LOOP */
            while (1u != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000000u);
            SCE->REG_28H = 0x00bf0001u;
            HW_SCE_p_func101(0xd2c19e49u, 0xe40ff80du, 0x83aeb8a3u, 0xbd0e4c85u);
        }
    }
    HW_SCE_p_func100(0x18b5fb6cu, 0x7d7790ffu, 0x9c25c4f6u, 0x8c05cb7fu);
    SCE->REG_24H = 0x000009c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x04000189u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000040c1u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00800001u;
    SCE->REG_24H = 0x000011c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x02000189u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000080c1u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00bf0001u;
    SCE->REG_24H = 0x000009c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x04000189u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000040c1u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00800001u;
    SCE->REG_24H = 0x000011c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x02000189u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000080c1u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00bf0001u;
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x016be062u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xda802bb3u, 0x2d8929d6u, 0x76e9e8cfu, 0xdbc5b788u);
    SCE->REG_00H = 0x00012303u;
    SCE->REG_2CH = 0x00000022u;
    HW_SCE_p_func313(1360);
    HW_SCE_p_func100(0xe6339cf1u, 0xb532bf6au, 0xa3482974u, 0xd9807aecu);
    HW_SCE_p_func314(1360+64);
    HW_SCE_p_func100(0x6bc0e5eau, 0x4aedebcau, 0xa9fcf8f6u, 0x785dfbb8u);
    SCE->REG_28H = 0x00800001u;
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x00000008u;
    SCE->REG_E0H = 0x8081001eu;
    SCE->REG_00H = 0x00008307u;
    SCE->REG_2CH = 0x00000020u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    SCE->REG_28H = 0x00bf0001u;
    SCE->REG_28H = 0x00800001u;
    SCE->REG_ECH = 0x000037dcu;
    SCE->REG_28H = 0x00bf0001u;
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x016be062u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0xcb65077au, 0x4d3fa4b8u, 0x1cfe2b93u, 0x8d794d55u);
    SCE->REG_00H = 0x00013203u;
    SCE->REG_2CH = 0x00000012u;
    HW_SCE_p_func312(1360);
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x017da167u);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x402e7dbfu, 0xfadf9e7eu, 0x4687ad22u, 0x8fe85d29u);
    SCE->REG_00H = 0x00013203u;
    SCE->REG_2CH = 0x00000010u;
    HW_SCE_p_func312(1156);
    SCE->REG_28H = 0x00800001u;
    SCE->REG_E0H = 0x80010380u;
    SCE->REG_00H = 0x00008307u;
    SCE->REG_2CH = 0x00000020u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    SCE->REG_2CH = 0x00000000u;
    SCE->REG_24H = 0x0000080au;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_E0H = 0x810103c0u;
    SCE->REG_00H = 0x00003807u;
    SCE->REG_2CH = 0x00000012u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    SCE->REG_24H = 0x000009c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x00001191u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000080c1u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_E0H = 0x81010380u;
    SCE->REG_00H = 0x00003807u;
    SCE->REG_2CH = 0x00000012u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    SCE->REG_2CH = 0x00000000u;
    SCE->REG_24H = 0x0000080au;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_2CH = 0x00000000u;
    SCE->REG_24H = 0x0000080au;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_E0H = 0x800103c0u;
    SCE->REG_00H = 0x00008307u;
    SCE->REG_2CH = 0x00000020u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    SCE->REG_ECH = 0x00008fc0u;
    SCE->REG_ECH = 0x0000000fu;
    SCE->REG_ECH = 0x0000d777u;
    SCE->REG_ECH = 0x0000b7a0u;
    SCE->REG_ECH = 0x00000010u;
    SCE->REG_ECH = 0x3000dbc3u;
    SCE->REG_ECH = 0x00020020u;
    SCE->REG_ECH = 0x00002bddu;
    SCE->REG_ECH = 0x00070020u;
    SCE->REG_ECH = 0x0000d377u;
    SCE->REG_ECH = 0x00000b9cu;
    SCE->REG_ECH = 0x00002b9eu;
    SCE->REG_ECH = 0x000037dcu;
    SCE->REG_ECH = 0x00000080u;
    SCE->REG_ECH = 0x00000080u;
    SCE->REG_28H = 0x00bf0001u;
    SCE->REG_24H = 0x000001c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000040c1u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000080c1u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x013d2cc1u);
    HW_SCE_p_func080();
    SCE->REG_00H = 0x00013203u;
    SCE->REG_2CH = 0x00000014u;
    HW_SCE_p_func312(1428);
    SCE->REG_ECH = 0x00000bffu;
    SCE->REG_ECH = 0x3800db77u;
    SCE->REG_E0H = 0x00000080u;
    SCE->REG_1CH = 0x00A60000u;
    HW_SCE_p_func100(0xc0dff601u, 0xdd161907u, 0x3683b9ecu, 0xfbd124aeu);
    SCE->REG_1CH = 0x00400000u;
    SCE->REG_1D0H = 0x00000000u;
    if (1u == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func100(0x143b4871u, 0xb551f34eu, 0xd21077e6u, 0x930f4960u);
        SCE->REG_E0H = 0x810103c0u;
        SCE->REG_04H = 0x00000607u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        S_RAM[0] = change_endian_long(SCE->REG_100H);
        for (oLoop2 = 0; oLoop2 < S_RAM[0]; oLoop2 = oLoop2 + 1)
        {
            SCE->REG_24H = 0x000009c0u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x04001991u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x000040c1u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_28H = 0x00800001u;
            SCE->REG_24H = 0x000011c0u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_34H = 0x00000004u;
            SCE->REG_24H = 0x82001191u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x000080c1u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_28H = 0x00bf0001u;
            SCE->REG_ECH = 0x00002fe0u;
            HW_SCE_p_func101(0xe0c3f7d3u, 0x43549f5eu, 0x91d5a220u, 0xc0ccba56u);
        }
        HW_SCE_p_func101(0x5615313fu, 0x56817861u, 0xebc2c1acu, 0x5531da32u);
    }
    else
    {
        HW_SCE_p_func100(0x32226c01u, 0x47382077u, 0x5543d625u, 0x0538b162u);
        SCE->REG_E0H = 0x810103c0u;
        SCE->REG_04H = 0x00000607u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        S_RAM[0] = change_endian_long(SCE->REG_100H);
        for (oLoop2 = 0; oLoop2 < S_RAM[0]; oLoop2 = oLoop2 + 1)
        {
            SCE->REG_24H = 0x000009c0u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x04001981u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x000040c1u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_28H = 0x00800001u;
            SCE->REG_24H = 0x000011c0u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_34H = 0x00000004u;
            SCE->REG_24H = 0x82001181u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x000080c1u;
            /* WAIT_LOOP */
            while (0u != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_28H = 0x00bf0001u;
            SCE->REG_ECH = 0x00002fe0u;
            HW_SCE_p_func101(0xda5dda6eu, 0x33afdb96u, 0x36b203a6u, 0x4450e14au);
        }
        HW_SCE_p_func101(0x3afc982bu, 0x640862e2u, 0xdee123a1u, 0xca8502c7u);
    }
    SCE->REG_ECH = 0x38000bdfu;
    SCE->REG_E0H = 0x00000080u;
    SCE->REG_1CH = 0x00260000u;
    SCE->REG_1CH = 0x00402000u;
    HW_SCE_p_func100(0x06131c0au, 0x4c7c54f5u, 0x3ab8cdceu, 0xb791ca1cu);
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x00000008u;
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x016be062u);
    HW_SCE_p_func080();
    SCE->REG_00H = 0x00013203u;
    SCE->REG_2CH = 0x00000014u;
    HW_SCE_p_func312(1360);
    SCE->REG_ECH = 0x3800db76u;
    SCE->REG_E0H = 0x00000080u;
    SCE->REG_1CH = 0x00A60000u;
    HW_SCE_p_func100(0x8abe5331u, 0x481743e0u, 0x5b657230u, 0xbf6f27d2u);
    SCE->REG_1CH = 0x00400000u;
    SCE->REG_1D0H = 0x00000000u;
    if (1u == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func315(0x00000190u);
        HW_SCE_p_func101(0x8f559563u, 0x97af0837u, 0xd313a066u, 0xa2705e73u);
    }
    else
    {
        SCE->REG_28H = 0x00800001u;
        SCE->REG_E0H = 0x8181001eu;
        SCE->REG_00H = 0x00003807u;
        SCE->REG_2CH = 0x00000090u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        SCE->REG_28H = 0x00bf0001u;
        HW_SCE_p_func101(0xb42e3262u, 0x9859ebaeu, 0x954f236bu, 0x77816924u);
    }
    SCE->REG_24H = 0x000009c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x04001981u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000040c1u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00800001u;
    SCE->REG_24H = 0x000011c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000004u;
    SCE->REG_24H = 0x82001181u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000080c1u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00bf0001u;
    SCE->REG_ECH = 0x00000bdeu;
    SCE->REG_ECH = 0x02816fdeu;
    SCE->REG_ECH = 0x30008bc0u;
    SCE->REG_ECH = 0x00000000u;
    SCE->REG_ECH = 0x00020020u;
    SCE->REG_ECH = 0x0000d378u;
    SCE->REG_ECH = 0x00000060u;
    SCE->REG_ECH = 0x0000d778u;
    SCE->REG_ECH = 0x00000080u;
    HW_SCE_p_func100(0xc9ed9bb6u, 0x433b0541u, 0xcc23870au, 0x214a676bu);
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x016efbeau);
    HW_SCE_p_func080();
    HW_SCE_p_func100(0x713e9a08u, 0x75913315u, 0x841cf33du, 0xb3a1c40du);
    SCE->REG_00H = 0x00012303u;
    SCE->REG_2CH = 0x00000022u;
    HW_SCE_p_func313(1292);
    HW_SCE_p_func100(0x76276a5du, 0xf64ab6d3u, 0x8e0a61c5u, 0x3355b0fdu);
    HW_SCE_p_func314(1292+64);
    HW_SCE_p_func100(0xb5d07c20u, 0x8e60825au, 0x1ca4c842u, 0x53189972u);
    SCE->REG_28H = 0x00800001u;
    SCE->REG_E0H = 0x81010320u;
    SCE->REG_00H = 0x00003807u;
    SCE->REG_2CH = 0x00000010u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    SCE->REG_E0H = 0x81010340u;
    SCE->REG_00H = 0x00003807u;
    SCE->REG_2CH = 0x00000012u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    SCE->REG_2CH = 0x00000000u;
    SCE->REG_24H = 0x0000080au;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_E0H = 0x80010300u;
    SCE->REG_00H = 0x00008307u;
    SCE->REG_2CH = 0x00000020u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    SCE->REG_ECH = 0x0000d77eu;
    SCE->REG_ECH = 0x00000bdeu;
    SCE->REG_ECH = 0x3000db7cu;
    SCE->REG_ECH = 0x00020020u;
    SCE->REG_ECH = 0x00002fc0u;
    SCE->REG_ECH = 0x00000080u;
    SCE->REG_ECH = 0x3000db7du;
    SCE->REG_ECH = 0x00020020u;
    SCE->REG_ECH = 0x00002fc0u;
    SCE->REG_ECH = 0x00000080u;
    SCE->REG_ECH = 0x3000dbc0u;
    SCE->REG_ECH = 0x00030020u;
    SCE->REG_ECH = 0x0000d77eu;
    SCE->REG_ECH = 0x00000060u;
    SCE->REG_ECH = 0x0000d37eu;
    SCE->REG_ECH = 0x00000080u;
    SCE->REG_28H = 0x00bf0001u;
    SCE->REG_24H = 0x000001c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000040c1u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000080c1u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x013fd1d7u);
    HW_SCE_p_func080();
    SCE->REG_00H = 0x00013203u;
    SCE->REG_2CH = 0x00000014u;
    HW_SCE_p_func312(1088);
    SCE->REG_ECH = 0x3000db7cu;
    SCE->REG_ECH = 0x00030020u;
    SCE->REG_ECH = 0x0000d76bu;
    SCE->REG_ECH = 0x00000060u;
    SCE->REG_ECH = 0x0000d36bu;
    SCE->REG_ECH = 0x00000080u;
    SCE->REG_ECH = 0x000037dau;
    SCE->REG_ECH = 0x0000b400u;
    SCE->REG_ECH = 0x00000097u;
    HW_SCE_p_func101(0x3f40f3f7u, 0xbcae5503u, 0xa1e66292u, 0x25e9989cu);
    HW_SCE_p_func310();
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x000000a0u;
    SCE->REG_E0H = 0x81c0001eu;
    SCE->REG_00H = 0x00013803u;
    SCE->REG_2CH = 0x00000014u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800u;
    SCE->REG_ECH = 0x3000db7du;
    SCE->REG_ECH = 0x00030020u;
    SCE->REG_ECH = 0x0000d76bu;
    SCE->REG_ECH = 0x00000060u;
    SCE->REG_ECH = 0x0000d36bu;
    SCE->REG_ECH = 0x00000080u;
    SCE->REG_ECH = 0x000037d9u;
    SCE->REG_ECH = 0x0000b400u;
    SCE->REG_ECH = 0x00000098u;
    HW_SCE_p_func101(0x2549e4eau, 0xa0d3cc6fu, 0x23a5edaau, 0xd5bffedau);
    HW_SCE_p_func310();
    HW_SCE_p_func100(0xe6e2105fu, 0xf966fefeu, 0x430a3701u, 0x6a1b7bcbu);
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x017da167u);
    HW_SCE_p_func080();
    SCE->REG_00H = 0x00013203u;
    SCE->REG_2CH = 0x00000014u;
    HW_SCE_p_func312(1156);
    SCE->REG_ECH = 0x3000db7eu;
    SCE->REG_ECH = 0x00030020u;
    SCE->REG_ECH = 0x0000d76bu;
    SCE->REG_ECH = 0x00000060u;
    SCE->REG_ECH = 0x0000d36bu;
    SCE->REG_ECH = 0x00000080u;
    SCE->REG_ECH = 0x000037d8u;
    SCE->REG_ECH = 0x0000b400u;
    SCE->REG_ECH = 0x00000099u;
    HW_SCE_p_func101(0xfa5ebe91u, 0x608dd2a2u, 0x703e6190u, 0xe345f97au);
    HW_SCE_p_func310();
    HW_SCE_p_func100(0x7098f4e1u, 0x755029a7u, 0xcf086487u, 0x3a769432u);
    SCE->REG_104H = 0x00000058u;
    SCE->REG_E0H = 0x80010020u;
    /* WAIT_LOOP */
    while (1u != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x016efbeau);
    HW_SCE_p_func080();
    SCE->REG_00H = 0x00013203u;
    SCE->REG_2CH = 0x00000014u;
    HW_SCE_p_func312(1292);
    SCE->REG_ECH = 0x3800db78u;
    SCE->REG_E0H = 0x00000080u;
    SCE->REG_1CH = 0x00A60000u;
    HW_SCE_p_func100(0xb5e88869u, 0x47d1e807u, 0x1f8e358du, 0x13c8289fu);
    SCE->REG_1CH = 0x00400000u;
    SCE->REG_1D0H = 0x00000000u;
    if (1u == (SCE->REG_1CH_b.B22))
    {
        SCE->REG_28H = 0x00800001u;
        SCE->REG_104H = 0x00000257u;
        SCE->REG_2CH = 0x00000050u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000001u);
        SCE->REG_2CH = 0x00000190u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0xFFFFFFFFu);
        SCE->REG_2CH = 0x00000050u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000u);
        SCE->REG_28H = 0x00bf0001u;
        HW_SCE_p_func101(0x1e90575au, 0x6f9e8914u, 0x56924477u, 0x20dfd07du);
    }
    else
    {
        HW_SCE_p_func101(0xee9e77e3u, 0x6eae0791u, 0x4ab75099u, 0x0a8da033u);
    }
    SCE->REG_24H = 0x000009c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x04001981u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000040c1u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00800001u;
    SCE->REG_24H = 0x000011c0u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000004u;
    SCE->REG_24H = 0x82001181u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000080c1u;
    /* WAIT_LOOP */
    while (0u != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00bf0001u;
    SCE->REG_ECH = 0x3800db79u;
    SCE->REG_E0H = 0x00000080u;
    SCE->REG_1CH = 0x00A60000u;
    HW_SCE_p_func100(0x6dfc72e1u, 0x4aa97e03u, 0x9fefa641u, 0xb7d6a06au);
    SCE->REG_1CH = 0x00400000u;
    SCE->REG_1D0H = 0x00000000u;
    if (1u == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func100(0xa6fcc1c7u, 0x509bfa42u, 0xd75055a0u, 0x559ad70fu);
        SCE->REG_28H = 0x00800001u;
        SCE->REG_24H = 0x000001c0u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_34H = 0x00000400u;
        SCE->REG_24H = 0x800080c1u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_28H = 0x00bf0001u;
        SCE->REG_24H = 0x000001c0u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x04000991u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x000040c1u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_28H = 0x00800001u;
        SCE->REG_34H = 0x00000004u;
        SCE->REG_24H = 0x800011c0u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x02001191u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x000080c1u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_28H = 0x00bf0001u;
        SCE->REG_ECH = 0x00000bdeu;
        SCE->REG_ECH = 0x02816fdeu;
        SCE->REG_ECH = 0x30008bc0u;
        SCE->REG_ECH = 0x00000000u;
        SCE->REG_ECH = 0x00020020u;
        SCE->REG_ECH = 0x0000d368u;
        SCE->REG_ECH = 0x00000060u;
        SCE->REG_ECH = 0x0000d768u;
        SCE->REG_ECH = 0x00000080u;
        SCE->REG_28H = 0x00800001u;
        SCE->REG_ECH = 0x0000b7c0u;
        SCE->REG_ECH = 0x0000001cu;
        SCE->REG_E0H = 0x8081001eu;
        SCE->REG_00H = 0x00008307u;
        SCE->REG_2CH = 0x00000020u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        SCE->REG_28H = 0x00bf0001u;
        SCE->REG_104H = 0x00000058u;
        SCE->REG_E0H = 0x80010020u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x01a2b89bu);
        HW_SCE_p_func080();
        SCE->REG_00H = 0x00013203u;
        SCE->REG_2CH = 0x00000014u;
        HW_SCE_p_func312(1224);
        SCE->REG_24H = 0x000019c0u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x04000991u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x0000c0c1u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_28H = 0x00800001u;
        SCE->REG_34H = 0x00000004u;
        SCE->REG_24H = 0x800011c0u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x02001191u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x000080c1u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_28H = 0x00bf0001u;
        SCE->REG_ECH = 0x00000bdeu;
        SCE->REG_ECH = 0x02816fdeu;
        SCE->REG_ECH = 0x30008bc0u;
        SCE->REG_ECH = 0x00000000u;
        SCE->REG_ECH = 0x00020020u;
        SCE->REG_ECH = 0x0000d372u;
        SCE->REG_ECH = 0x00000060u;
        SCE->REG_ECH = 0x0000d772u;
        SCE->REG_ECH = 0x00000080u;
        SCE->REG_28H = 0x00800001u;
        SCE->REG_ECH = 0x0000b7c0u;
        SCE->REG_ECH = 0x00000018u;
        SCE->REG_E0H = 0x8081001eu;
        SCE->REG_00H = 0x00008307u;
        SCE->REG_2CH = 0x00000020u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        SCE->REG_28H = 0x00bf0001u;
        SCE->REG_24H = 0x000098d0u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        HW_SCE_p_func101(0xc3143860u, 0xcb79a6fdu, 0x9bf4bad1u, 0x20e4b647u);
    }
    else
    {
        HW_SCE_p_func100(0x8d0528ddu, 0x4e505ffbu, 0xe5a9e4e6u, 0x71567e2eu);
        SCE->REG_ECH = 0x00000bdeu;
        SCE->REG_ECH = 0x02816fdeu;
        SCE->REG_ECH = 0x30008bc0u;
        SCE->REG_ECH = 0x00000000u;
        SCE->REG_ECH = 0x00020020u;
        SCE->REG_ECH = 0x0000d368u;
        SCE->REG_ECH = 0x00000060u;
        SCE->REG_ECH = 0x0000d768u;
        SCE->REG_ECH = 0x00000080u;
        SCE->REG_28H = 0x00800001u;
        SCE->REG_ECH = 0x0000b7c0u;
        SCE->REG_ECH = 0x0000001cu;
        SCE->REG_E0H = 0x8081001eu;
        SCE->REG_00H = 0x00008307u;
        SCE->REG_2CH = 0x00000020u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        SCE->REG_28H = 0x00bf0001u;
        SCE->REG_28H = 0x00800001u;
        SCE->REG_ECH = 0x0000b7c0u;
        SCE->REG_ECH = 0x00000018u;
        SCE->REG_24H = 0x000001c0u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x000080c1u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_E0H = 0x8081001eu;
        SCE->REG_00H = 0x00008307u;
        SCE->REG_2CH = 0x00000020u;
        /* WAIT_LOOP */
        while (0u != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800u;
        SCE->REG_28H = 0x00bf0001u;
        SCE->REG_ECH = 0x0000d772u;
        SCE->REG_104H = 0x00000058u;
        SCE->REG_E0H = 0x80010020u;
        /* WAIT_LOOP */
        while (1u != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x01a2b89bu);
        HW_SCE_p_func080();
        SCE->REG_00H = 0x00013203u;
        SCE->REG_2CH = 0x00000010u;
        HW_SCE_p_func312(1224);
        HW_SCE_p_func101(0x5fc4a8f8u, 0x188438f1u, 0x443f6818u, 0xdc8f97a7u);
    }
    SCE->REG_ECH = 0x0000b7c0u;
    SCE->REG_ECH = 0x00000024u;
    SCE->REG_ECH = 0x0000381eu;
    SCE->REG_ECH = 0x00007c00u;
    SCE->REG_1CH = 0x00602000u;
}

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCE_p_func304.prc
***********************************************************************************************************************/
