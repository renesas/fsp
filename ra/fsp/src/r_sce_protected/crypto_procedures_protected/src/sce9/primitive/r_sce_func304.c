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

void R_SCE_func304(void)
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
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000024U;
    SCE->REG_ECH = 0x00003c1eU;
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_ECH = 0x0000d779U;
    SCE->REG_28H = 0x00870001U;
    SCE->REG_ECH = 0x00000b18U;
    SCE->REG_E0H = 0x80010300U;
    SCE->REG_00H = 0x00008307U;
    SCE->REG_2CH = 0x000000adU;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_00H = 0x0000031fU;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_ECH = 0x3800db1fU;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00A60000U;
    R_SCE_func100(0x4f14f489U, 0xfa10fda3U, 0xda4c5453U, 0xf2914203U);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        R_SCE_func101(0x30aacd26U, 0xc5edc197U, 0xddbcc6a2U, 0x57abf381U);
    }
    else
    {
        SCE->REG_28H = 0x00800001U;
        SCE->REG_24H = 0x000001c0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_34H = 0x00000400U;
        SCE->REG_24H = 0x800080c1U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x00000581U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x000080c1U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_28H = 0x00bf0001U;
        SCE->REG_24H = 0x000001c0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x04001991U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x0000c0c1U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_28H = 0x00800001U;
        SCE->REG_24H = 0x000011c0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_34H = 0x00000004U;
        SCE->REG_24H = 0x82001191U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x000080c1U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_28H = 0x00bf0001U;
        SCE->REG_ECH = 0x0000d379U;
        R_SCE_func101(0xc74af482U, 0x99c93ee9U, 0xb2744daaU, 0x2f1fb4e4U);
    }
    R_SCE_func100(0x173c9c4dU, 0xd60a7bf1U, 0x60093bfdU, 0x2ec74acfU);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x017da167U);
    R_SCE_func080();
    R_SCE_func100(0xa85d0bd8U, 0xcc60ad18U, 0x3e085308U, 0xe87efa5aU);
    SCE->REG_00H = 0x00012303U;
    SCE->REG_2CH = 0x00000024U;
    R_SCE_func313(1156);
    R_SCE_func100(0xe5fce155U, 0x689bcd24U, 0xa47eb743U, 0x7dc3af71U);
    R_SCE_func314(1156+64);
    SCE->REG_ECH = 0x00000b5aU;
    SCE->REG_24H = 0x000001c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_ECH = 0x0000d77cU;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000000U;
    SCE->REG_ECH = 0x3800db7aU;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00A60000U;
    R_SCE_func100(0xa8f8757cU, 0xc2532beaU, 0xfbba4cc5U, 0x84c7d682U);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        SCE->REG_28H = 0x00800001U;
        SCE->REG_24H = 0x000001c0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_34H = 0x00000400U;
        SCE->REG_24H = 0x800080c1U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_104H = 0x00000157U;
        SCE->REG_2CH = 0x00000050U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000001U);
        SCE->REG_E0H = 0x8181001eU;
        SCE->REG_00H = 0x00003807U;
        SCE->REG_2CH = 0x00000110U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_2CH = 0x00000050U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000U);
        SCE->REG_24H = 0x000011c0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_28H = 0x00bf0001U;
        oLoop1 = 1;
        while(oLoop1 == 1)
        {
            SCE->REG_1CH = 0x00210000U;
            R_SCE_func100(0xa7e9686fU, 0xda8e5b68U, 0x81f149bdU, 0x6b78d9e6U);
            SCE->REG_1CH = 0x00400000U;
            SCE->REG_1D0H = 0x00000000U;
            if (1U == (SCE->REG_1CH_b.B22))
            {
                SCE->REG_24H = 0x000009c0U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x04001981U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x000040c1U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_28H = 0x00800001U;
                SCE->REG_24H = 0x000011c0U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_34H = 0x00000004U;
                SCE->REG_24H = 0x82001181U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x000080c1U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_28H = 0x00bf0001U;
                SCE->REG_ECH = 0x00003340U;
                R_SCE_func101(0xb7418b1eU, 0xab29cb8bU, 0xee70cb7dU, 0xa4d90812U);
            }
            else
            {
                R_SCE_func101(0xa8273f89U, 0x45442134U, 0xd4850bfcU, 0xcccddce6U);
                oLoop1 = 0;
            }
        }
        SCE->REG_ECH = 0x0000d37cU;
        SCE->REG_ECH = 0x00000b9cU;
        SCE->REG_ECH = 0x00002b9aU;
        SCE->REG_ECH = 0x0000375cU;
        R_SCE_func101(0xa5d35c20U, 0x5cbdfacdU, 0x1df44fc2U, 0xb0433084U);
    }
    else
    {
        SCE->REG_28H = 0x00800001U;
        SCE->REG_E0H = 0x8181001eU;
        SCE->REG_00H = 0x00003807U;
        SCE->REG_2CH = 0x00000010U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_24H = 0x000001c0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_34H = 0x00000400U;
        SCE->REG_24H = 0x800080c1U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_28H = 0x00bf0001U;
        SCE->REG_24H = 0x000009c0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x04001991U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x000040c1U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_28H = 0x00800001U;
        SCE->REG_24H = 0x000011c0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_34H = 0x00000004U;
        SCE->REG_24H = 0x82001191U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x000080c1U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_28H = 0x00bf0001U;
        oLoop1 = 1;
        while(oLoop1 == 1)
        {
            SCE->REG_1CH = 0x00210000U;
            R_SCE_func100(0xba805753U, 0x852ca913U, 0x4fd9cedbU, 0x5f9bf052U);
            SCE->REG_1CH = 0x00400000U;
            SCE->REG_1D0H = 0x00000000U;
            if (1U == (SCE->REG_1CH_b.B22))
            {
                SCE->REG_24H = 0x000009c0U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x04001981U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x000040c1U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_28H = 0x00800001U;
                SCE->REG_24H = 0x000011c0U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_34H = 0x00000004U;
                SCE->REG_24H = 0x82001181U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x000080c1U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_28H = 0x00bf0001U;
                R_SCE_func101(0x63c32367U, 0x9986dc87U, 0x19768848U, 0x94f141ceU);
                oLoop1 = 0;
            }
            else
            {
                SCE->REG_24H = 0x000009c0U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x04001991U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x000040c1U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_28H = 0x00800001U;
                SCE->REG_24H = 0x000011c0U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_34H = 0x00000004U;
                SCE->REG_24H = 0x82001191U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x000080c1U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_28H = 0x00bf0001U;
                SCE->REG_ECH = 0x00002f40U;
                R_SCE_func101(0xeb85c7e8U, 0x15dbf0eeU, 0xb6f4532bU, 0x068b44aeU);
            }
        }
        R_SCE_func101(0x1993b44bU, 0x690f4b3bU, 0x87d17206U, 0x390becc4U);
    }
    SCE->REG_24H = 0x000088d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x000000a0U;
    SCE->REG_E0H = 0x81c0001eU;
    SCE->REG_00H = 0x00013803U;
    SCE->REG_2CH = 0x00000012U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x000000a0U;
    SCE->REG_E0H = 0x80c0001eU;
    SCE->REG_00H = 0x00018303U;
    SCE->REG_2CH = 0x00000020U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_ECH = 0x00000b39U;
    SCE->REG_24H = 0x000001c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_ECH = 0x0000d77dU;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000004U;
    SCE->REG_ECH = 0x3800db7bU;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00A60000U;
    R_SCE_func100(0x07464bfaU, 0xa41ec7a0U, 0xe48ea12fU, 0x92351e93U);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        SCE->REG_28H = 0x00800001U;
        SCE->REG_24H = 0x000001c0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_34H = 0x00000400U;
        SCE->REG_24H = 0x800080c1U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_104H = 0x00000157U;
        SCE->REG_2CH = 0x00000050U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000001U);
        SCE->REG_E0H = 0x8181001eU;
        SCE->REG_00H = 0x00003807U;
        SCE->REG_2CH = 0x00000110U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_2CH = 0x00000050U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000U);
        SCE->REG_24H = 0x000011c0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_28H = 0x00bf0001U;
        oLoop1 = 1;
        while(oLoop1 == 1)
        {
            SCE->REG_1CH = 0x00210000U;
            R_SCE_func100(0x97652807U, 0x3725e7edU, 0xa93ced2bU, 0x511fbee0U);
            SCE->REG_1CH = 0x00400000U;
            SCE->REG_1D0H = 0x00000000U;
            if (1U == (SCE->REG_1CH_b.B22))
            {
                SCE->REG_24H = 0x000009c0U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x04001981U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x000040c1U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_28H = 0x00800001U;
                SCE->REG_24H = 0x000011c0U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_34H = 0x00000004U;
                SCE->REG_24H = 0x82001181U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x000080c1U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_28H = 0x00bf0001U;
                SCE->REG_ECH = 0x00003320U;
                R_SCE_func101(0xdebb77c3U, 0x5a323f95U, 0xa39ef0dfU, 0x8f2ce0b8U);
            }
            else
            {
                R_SCE_func101(0x0ee7d020U, 0x1e0c8005U, 0x590cbe94U, 0xa5c2a969U);
                oLoop1 = 0;
            }
        }
        SCE->REG_ECH = 0x0000d37dU;
        SCE->REG_ECH = 0x00000b9cU;
        SCE->REG_ECH = 0x00002b99U;
        SCE->REG_ECH = 0x0000373cU;
        R_SCE_func101(0x43e466efU, 0xf4483116U, 0x35524ff7U, 0x335fb075U);
    }
    else
    {
        SCE->REG_28H = 0x00800001U;
        SCE->REG_E0H = 0x8181001eU;
        SCE->REG_00H = 0x00003807U;
        SCE->REG_2CH = 0x00000010U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_24H = 0x000001c0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_34H = 0x00000400U;
        SCE->REG_24H = 0x800080c1U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_28H = 0x00bf0001U;
        SCE->REG_24H = 0x000009c0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x04001991U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x000040c1U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_28H = 0x00800001U;
        SCE->REG_24H = 0x000011c0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_34H = 0x00000004U;
        SCE->REG_24H = 0x82001191U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x000080c1U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_28H = 0x00bf0001U;
        oLoop1 = 1;
        while(oLoop1 == 1)
        {
            SCE->REG_1CH = 0x00210000U;
            R_SCE_func100(0xb2a344d7U, 0x6766834fU, 0xba498b36U, 0x575d104cU);
            SCE->REG_1CH = 0x00400000U;
            SCE->REG_1D0H = 0x00000000U;
            if (1U == (SCE->REG_1CH_b.B22))
            {
                SCE->REG_24H = 0x000009c0U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x04001981U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x000040c1U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_28H = 0x00800001U;
                SCE->REG_24H = 0x000011c0U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_34H = 0x00000004U;
                SCE->REG_24H = 0x82001181U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x000080c1U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_28H = 0x00bf0001U;
                R_SCE_func101(0xb5428e25U, 0xf1ee76a5U, 0xb74a8042U, 0x667e80e1U);
                oLoop1 = 0;
            }
            else
            {
                SCE->REG_24H = 0x000009c0U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x04001991U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x000040c1U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_28H = 0x00800001U;
                SCE->REG_24H = 0x000011c0U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_34H = 0x00000004U;
                SCE->REG_24H = 0x82001191U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_24H = 0x000080c1U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_24H_b.B21)
                {
                    /* waiting */
                }
                SCE->REG_28H = 0x00bf0001U;
                SCE->REG_ECH = 0x00002f20U;
                R_SCE_func101(0xfc31d44fU, 0x2cafedcaU, 0xea8a4d0fU, 0xd90074ccU);
            }
        }
        R_SCE_func101(0xfe80d7c9U, 0xf195e713U, 0xea86d754U, 0x3095b9cfU);
    }
    R_SCE_func100(0xa9a633feU, 0x165fa494U, 0xc9b98bb2U, 0x9f348831U);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x013fd1d7U);
    R_SCE_func080();
    R_SCE_func100(0x84ac0b6fU, 0x105f3192U, 0xb42c04f2U, 0x5e89f356U);
    SCE->REG_00H = 0x00012303U;
    SCE->REG_2CH = 0x00000022U;
    R_SCE_func313(1088);
    R_SCE_func100(0xe7b483f6U, 0x7d0d7774U, 0xdf86636dU, 0xaf59265aU);
    R_SCE_func314(1088+64);
    R_SCE_func100(0x829ce331U, 0xb3fcb53cU, 0x182da1e8U, 0xfbfb9d4cU);
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_24H = 0x000088d0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x000000a0U;
    SCE->REG_E0H = 0x81c0001eU;
    SCE->REG_00H = 0x00013803U;
    SCE->REG_2CH = 0x00000012U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_28H = 0x00870001U;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000050U;
    SCE->REG_E0H = 0x8088001eU;
    SCE->REG_00H = 0x00008323U;
    SCE->REG_2CH = 0x00000022U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000070U;
    SCE->REG_E0H = 0x8088001eU;
    SCE->REG_00H = 0x00008323U;
    SCE->REG_2CH = 0x00000020U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_24H = 0x0000480cU;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01a2b89bU);
    R_SCE_func080();
    R_SCE_func100(0x36a2ffd9U, 0x6876d72fU, 0x7993c31fU, 0x7f0068ebU);
    SCE->REG_00H = 0x00012303U;
    SCE->REG_2CH = 0x00000022U;
    R_SCE_func313(1224);
    R_SCE_func100(0x1a40bf95U, 0x1310b477U, 0x63845836U, 0xeabe9fb4U);
    R_SCE_func314(1224+64);
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x000000a0U;
    SCE->REG_E0H = 0x81c0001eU;
    SCE->REG_00H = 0x00013803U;
    SCE->REG_2CH = 0x00000012U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_28H = 0x00800001U;
    SCE->REG_2CH = 0x00000000U;
    SCE->REG_24H = 0x0000080aU;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_E0H = 0x80010380U;
    SCE->REG_00H = 0x00008307U;
    SCE->REG_2CH = 0x00000020U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_28H = 0x00870001U;
    SCE->REG_E0H = 0x800103a0U;
    SCE->REG_00H = 0x00008307U;
    SCE->REG_2CH = 0x000000adU;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_00H = 0x0000031fU;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_2CH = 0x00000012U;
    SCE->REG_104H = 0x00000767U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x40000000U);
    SCE->REG_100H = change_endian_long(0x00000000U);
    SCE->REG_100H = change_endian_long(0x00000000U);
    SCE->REG_100H = change_endian_long(0x00000000U);
    SCE->REG_100H = change_endian_long(0x00000000U);
    SCE->REG_100H = change_endian_long(0x00000000U);
    SCE->REG_100H = change_endian_long(0x00000000U);
    SCE->REG_100H = change_endian_long(0x00000000U);
    SCE->REG_34H = 0x00000030U;
    SCE->REG_24H = 0x80001dc0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_ECH = 0x3800dbbeU;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00A60000U;
    R_SCE_func100(0xcfee5b98U, 0x14e9e7a5U, 0x4735cd59U, 0xd6c8f45aU);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        SCE->REG_24H = 0x00000991U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_ECH = 0x0000d375U;
        R_SCE_func101(0x62dbb035U, 0xc5080e3cU, 0xf420a58aU, 0x0ff31dbcU);
    }
    else
    {
        SCE->REG_24H = 0x00000981U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_ECH = 0x0000d775U;
        R_SCE_func101(0x5a8eebccU, 0x2a5f321cU, 0x7aee6d6fU, 0xaaadc8d8U);
    }
    R_SCE_func100(0xa02f1c27U, 0x9115aaabU, 0xa806611aU, 0xf0e6896aU);
    SCE->REG_34H = 0x00000c00U;
    SCE->REG_24H = 0x8000e0c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x013d2cc1U);
    R_SCE_func080();
    R_SCE_func100(0x23ec631fU, 0xea71d0c0U, 0xa6206b37U, 0x3312d30cU);
    SCE->REG_00H = 0x00012303U;
    SCE->REG_2CH = 0x00000024U;
    R_SCE_func313(1428);
    R_SCE_func100(0x03c4bc4eU, 0x5f69a0d7U, 0xa0a5a1acU, 0xa13175c8U);
    R_SCE_func314(1428+64);
    R_SCE_func100(0x24b3860cU, 0x17cbef28U, 0x1bb0fe5fU, 0xcff028beU);
    SCE->REG_28H = 0x00870001U;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000050U;
    SCE->REG_E0H = 0x8188001eU;
    SCE->REG_00H = 0x00003823U;
    SCE->REG_2CH = 0x00000012U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000070U;
    SCE->REG_E0H = 0x8188001eU;
    SCE->REG_00H = 0x00003823U;
    SCE->REG_2CH = 0x00000010U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_24H = 0x000009c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000019a1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000040c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000011c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000019a1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000080c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x0000c80cU;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x01a2b89bU);
    R_SCE_func080();
    SCE->REG_00H = 0x00013203U;
    SCE->REG_2CH = 0x00000012U;
    R_SCE_func312(1224);
    SCE->REG_ECH = 0x0000d776U;
    SCE->REG_ECH = 0x3800db75U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00A60000U;
    R_SCE_func100(0xdb721df3U, 0x8814ee7dU, 0x5fe43ab2U, 0x5a1ce76eU);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        SCE->REG_24H = 0x000019c0U;
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
        SCE->REG_24H = 0x000040c1U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00210000U;
        R_SCE_func100(0xb2c9b808U, 0x5203c390U, 0xda823217U, 0x83024e8eU);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            SCE->REG_ECH = 0x0000d376U;
            SCE->REG_28H = 0x00800001U;
            SCE->REG_104H = 0x00000257U;
            SCE->REG_2CH = 0x00000050U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000001U);
            SCE->REG_2CH = 0x00000110U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0xFFFFFFFFU);
            SCE->REG_2CH = 0x00000050U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000000U);
            SCE->REG_28H = 0x00bf0001U;
            R_SCE_func101(0xd52facf8U, 0x8c1cdffcU, 0x4ad010a5U, 0x9e5888d0U);
        }
        else
        {
            SCE->REG_ECH = 0x0000d776U;
            SCE->REG_28H = 0x00800001U;
            SCE->REG_2CH = 0x00000010U;
            SCE->REG_104H = 0x00000067U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000000U);
            SCE->REG_28H = 0x00bf0001U;
            R_SCE_func101(0x134325c4U, 0x4ba6582aU, 0xde413a22U, 0x8b0f3924U);
        }
    }
    else
    {
        SCE->REG_24H = 0x000009c0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x00001991U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x000040c1U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00210000U;
        R_SCE_func100(0xac3be9bbU, 0x975f21f0U, 0x7b9c0e6dU, 0xb479aacbU);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            SCE->REG_ECH = 0x0000d376U;
            SCE->REG_28H = 0x00800001U;
            SCE->REG_104H = 0x00000257U;
            SCE->REG_2CH = 0x00000050U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000001U);
            SCE->REG_2CH = 0x00000110U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0xFFFFFFFFU);
            SCE->REG_2CH = 0x00000050U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000000U);
            SCE->REG_28H = 0x00bf0001U;
            R_SCE_func101(0x51c94560U, 0x8e6e6599U, 0xea4892a9U, 0x7662cc6fU);
        }
        else
        {
            SCE->REG_ECH = 0x0000d776U;
            SCE->REG_28H = 0x00800001U;
            SCE->REG_2CH = 0x00000010U;
            SCE->REG_104H = 0x00000067U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000000U);
            SCE->REG_28H = 0x00bf0001U;
            R_SCE_func101(0x0b77a168U, 0xb53edd31U, 0xb2cf3a59U, 0x67a5fce4U);
        }
    }
    R_SCE_func100(0xc29f1ef9U, 0xa11202baU, 0x4608d26cU, 0x59575c66U);
    SCE->REG_24H = 0x000009c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x04000189U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000040c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00800001U;
    SCE->REG_24H = 0x000011c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x02000189U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000080c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_24H = 0x000009c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x04000189U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000040c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00800001U;
    SCE->REG_24H = 0x000011c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x02000189U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000080c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x016be062U);
    R_SCE_func080();
    R_SCE_func100(0x7fd8687dU, 0x59f33691U, 0x67e26de8U, 0x8f1a435cU);
    SCE->REG_00H = 0x00012303U;
    SCE->REG_2CH = 0x00000022U;
    R_SCE_func313(1360);
    R_SCE_func100(0xb7d8d104U, 0xd03fc109U, 0x6fcd0cbaU, 0x5a202c97U);
    R_SCE_func314(1360+64);
    R_SCE_func100(0x49d39b7fU, 0x1a11709dU, 0xb916b6f4U, 0xc66464e6U);
    SCE->REG_28H = 0x00800001U;
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000008U;
    SCE->REG_E0H = 0x8081001eU;
    SCE->REG_00H = 0x00008307U;
    SCE->REG_2CH = 0x00000020U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_28H = 0x00800001U;
    SCE->REG_ECH = 0x000037dcU;
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x016be062U);
    R_SCE_func080();
    R_SCE_func100(0xdf08d7eeU, 0x96b345e7U, 0xa9d22a61U, 0x8198e092U);
    SCE->REG_00H = 0x00013203U;
    SCE->REG_2CH = 0x00000012U;
    R_SCE_func312(1360);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x017da167U);
    R_SCE_func080();
    R_SCE_func100(0x5fbc667aU, 0xf7ca0146U, 0x216ca9efU, 0xdc2b921bU);
    SCE->REG_00H = 0x00013203U;
    SCE->REG_2CH = 0x00000010U;
    R_SCE_func312(1156);
    SCE->REG_28H = 0x00800001U;
    SCE->REG_E0H = 0x80010380U;
    SCE->REG_00H = 0x00008307U;
    SCE->REG_2CH = 0x00000020U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_2CH = 0x00000000U;
    SCE->REG_24H = 0x0000080aU;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_E0H = 0x810103c0U;
    SCE->REG_00H = 0x00003807U;
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
    SCE->REG_24H = 0x000080c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_E0H = 0x81010380U;
    SCE->REG_00H = 0x00003807U;
    SCE->REG_2CH = 0x00000012U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_2CH = 0x00000000U;
    SCE->REG_24H = 0x0000080aU;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_2CH = 0x00000000U;
    SCE->REG_24H = 0x0000080aU;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_E0H = 0x800103c0U;
    SCE->REG_00H = 0x00008307U;
    SCE->REG_2CH = 0x00000020U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_ECH = 0x00008fc0U;
    SCE->REG_ECH = 0x0000000fU;
    SCE->REG_ECH = 0x0000d777U;
    SCE->REG_ECH = 0x0000b7a0U;
    SCE->REG_ECH = 0x00000010U;
    SCE->REG_ECH = 0x3000dbc3U;
    SCE->REG_ECH = 0x00020020U;
    SCE->REG_ECH = 0x00002bddU;
    SCE->REG_ECH = 0x00070020U;
    SCE->REG_ECH = 0x0000d377U;
    SCE->REG_ECH = 0x00000b9cU;
    SCE->REG_ECH = 0x00002b9eU;
    SCE->REG_ECH = 0x000037dcU;
    SCE->REG_ECH = 0x00000080U;
    SCE->REG_ECH = 0x00000080U;
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_24H = 0x000001c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000040c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000080c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x013d2cc1U);
    R_SCE_func080();
    SCE->REG_00H = 0x00013203U;
    SCE->REG_2CH = 0x00000014U;
    R_SCE_func312(1428);
    SCE->REG_ECH = 0x00000bffU;
    SCE->REG_ECH = 0x3800db77U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00A60000U;
    R_SCE_func100(0xa02e78abU, 0x8cdbbf6bU, 0xedf2e965U, 0xc1f8374bU);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        R_SCE_func100(0x74a0fb2dU, 0x1f242d1fU, 0xae5d98fcU, 0x91e71762U);
        SCE->REG_E0H = 0x810103c0U;
        SCE->REG_04H = 0x00000607U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        S_RAM[0] = change_endian_long(SCE->REG_100H);
        for (oLoop2 = 0; oLoop2 < S_RAM[0]; oLoop2 = oLoop2 + 1)
        {
            SCE->REG_24H = 0x000009c0U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x04001991U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x000040c1U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_28H = 0x00800001U;
            SCE->REG_24H = 0x000011c0U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_34H = 0x00000004U;
            SCE->REG_24H = 0x82001191U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x000080c1U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_28H = 0x00bf0001U;
            SCE->REG_ECH = 0x00002fe0U;
            R_SCE_func101(0xefdd5812U, 0x82089e95U, 0xd17ef168U, 0xaa29a094U);
        }
        R_SCE_func101(0x96f44f7cU, 0xdb16c62dU, 0xde56b0a0U, 0x4ab8e241U);
    }
    else
    {
        R_SCE_func100(0xf93b9b92U, 0x945f6d5dU, 0x3e0c3e56U, 0x06ef9c7dU);
        SCE->REG_E0H = 0x810103c0U;
        SCE->REG_04H = 0x00000607U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_04H_b.B30)
        {
            /* waiting */
        }
        S_RAM[0] = change_endian_long(SCE->REG_100H);
        for (oLoop2 = 0; oLoop2 < S_RAM[0]; oLoop2 = oLoop2 + 1)
        {
            SCE->REG_24H = 0x000009c0U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x04001981U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x000040c1U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_28H = 0x00800001U;
            SCE->REG_24H = 0x000011c0U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_34H = 0x00000004U;
            SCE->REG_24H = 0x82001181U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_24H = 0x000080c1U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_24H_b.B21)
            {
                /* waiting */
            }
            SCE->REG_28H = 0x00bf0001U;
            SCE->REG_ECH = 0x00002fe0U;
            R_SCE_func101(0x9c44d017U, 0x6e2aaf0cU, 0xdaed6879U, 0xfbd8e08cU);
        }
        R_SCE_func101(0x64751973U, 0xac4fd03aU, 0xfd004cbcU, 0xda40b9f0U);
    }
    SCE->REG_ECH = 0x38000bdfU;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00260000U;
    SCE->REG_1CH = 0x00402000U;
    R_SCE_func100(0xbf319692U, 0xb45847feU, 0x961a5b99U, 0xba92bd78U);
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000008U;
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x016be062U);
    R_SCE_func080();
    SCE->REG_00H = 0x00013203U;
    SCE->REG_2CH = 0x00000014U;
    R_SCE_func312(1360);
    SCE->REG_ECH = 0x3800db76U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00A60000U;
    R_SCE_func100(0x32c05eb1U, 0x1af4747bU, 0x65a2d1ebU, 0x6e53d91bU);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        R_SCE_func315(0x00000190U);
        R_SCE_func101(0xdf9f8695U, 0xc9d30237U, 0x400af7bcU, 0x8af14fd3U);
    }
    else
    {
        SCE->REG_28H = 0x00800001U;
        SCE->REG_E0H = 0x8181001eU;
        SCE->REG_00H = 0x00003807U;
        SCE->REG_2CH = 0x00000090U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_28H = 0x00bf0001U;
        R_SCE_func101(0x781149b1U, 0x2713ae81U, 0x08637c82U, 0x21dc84e7U);
    }
    SCE->REG_24H = 0x000009c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x04001981U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000040c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00800001U;
    SCE->REG_24H = 0x000011c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000004U;
    SCE->REG_24H = 0x82001181U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000080c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_ECH = 0x00000bdeU;
    SCE->REG_ECH = 0x02816fdeU;
    SCE->REG_ECH = 0x30008bc0U;
    SCE->REG_ECH = 0x00000000U;
    SCE->REG_ECH = 0x00020020U;
    SCE->REG_ECH = 0x0000d378U;
    SCE->REG_ECH = 0x00000060U;
    SCE->REG_ECH = 0x0000d778U;
    SCE->REG_ECH = 0x00000080U;
    R_SCE_func100(0x8a55234aU, 0x1c58b72fU, 0xa6636cf5U, 0xbe997152U);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x016efbeaU);
    R_SCE_func080();
    R_SCE_func100(0x2926188cU, 0x91e465bbU, 0xee232e57U, 0xc45a6f23U);
    SCE->REG_00H = 0x00012303U;
    SCE->REG_2CH = 0x00000022U;
    R_SCE_func313(1292);
    R_SCE_func100(0x561468bdU, 0x2b678626U, 0x7896fb83U, 0xc446a4a9U);
    R_SCE_func314(1292+64);
    R_SCE_func100(0xe8d9928dU, 0x4abaaa93U, 0x148dd000U, 0x67fdeaa0U);
    SCE->REG_28H = 0x00800001U;
    SCE->REG_E0H = 0x81010320U;
    SCE->REG_00H = 0x00003807U;
    SCE->REG_2CH = 0x00000010U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_E0H = 0x81010340U;
    SCE->REG_00H = 0x00003807U;
    SCE->REG_2CH = 0x00000012U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_2CH = 0x00000000U;
    SCE->REG_24H = 0x0000080aU;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_E0H = 0x80010300U;
    SCE->REG_00H = 0x00008307U;
    SCE->REG_2CH = 0x00000020U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_ECH = 0x0000d77eU;
    SCE->REG_ECH = 0x00000bdeU;
    SCE->REG_ECH = 0x3000db7cU;
    SCE->REG_ECH = 0x00020020U;
    SCE->REG_ECH = 0x00002fc0U;
    SCE->REG_ECH = 0x00000080U;
    SCE->REG_ECH = 0x3000db7dU;
    SCE->REG_ECH = 0x00020020U;
    SCE->REG_ECH = 0x00002fc0U;
    SCE->REG_ECH = 0x00000080U;
    SCE->REG_ECH = 0x3000dbc0U;
    SCE->REG_ECH = 0x00030020U;
    SCE->REG_ECH = 0x0000d77eU;
    SCE->REG_ECH = 0x00000060U;
    SCE->REG_ECH = 0x0000d37eU;
    SCE->REG_ECH = 0x00000080U;
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_24H = 0x000001c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000040c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000080c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x013fd1d7U);
    R_SCE_func080();
    SCE->REG_00H = 0x00013203U;
    SCE->REG_2CH = 0x00000014U;
    R_SCE_func312(1088);
    SCE->REG_ECH = 0x3000db7cU;
    SCE->REG_ECH = 0x00030020U;
    SCE->REG_ECH = 0x0000d76bU;
    SCE->REG_ECH = 0x00000060U;
    SCE->REG_ECH = 0x0000d36bU;
    SCE->REG_ECH = 0x00000080U;
    SCE->REG_ECH = 0x000037daU;
    SCE->REG_ECH = 0x0000b400U;
    SCE->REG_ECH = 0x00000097U;
    R_SCE_func101(0xb5beeb77U, 0x639a74ceU, 0xaa351464U, 0x56c04524U);
    R_SCE_func310();
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x000000a0U;
    SCE->REG_E0H = 0x81c0001eU;
    SCE->REG_00H = 0x00013803U;
    SCE->REG_2CH = 0x00000014U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_00H_b.B25)
    {
        /* waiting */
    }
    SCE->REG_1CH = 0x00001800U;
    SCE->REG_ECH = 0x3000db7dU;
    SCE->REG_ECH = 0x00030020U;
    SCE->REG_ECH = 0x0000d76bU;
    SCE->REG_ECH = 0x00000060U;
    SCE->REG_ECH = 0x0000d36bU;
    SCE->REG_ECH = 0x00000080U;
    SCE->REG_ECH = 0x000037d9U;
    SCE->REG_ECH = 0x0000b400U;
    SCE->REG_ECH = 0x00000098U;
    R_SCE_func101(0x7b385a43U, 0x9c412010U, 0x9a0462d1U, 0xfff8fa33U);
    R_SCE_func310();
    R_SCE_func100(0xbbd74204U, 0xba55a969U, 0x0a288a89U, 0x4e58bd07U);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x017da167U);
    R_SCE_func080();
    SCE->REG_00H = 0x00013203U;
    SCE->REG_2CH = 0x00000014U;
    R_SCE_func312(1156);
    SCE->REG_ECH = 0x3000db7eU;
    SCE->REG_ECH = 0x00030020U;
    SCE->REG_ECH = 0x0000d76bU;
    SCE->REG_ECH = 0x00000060U;
    SCE->REG_ECH = 0x0000d36bU;
    SCE->REG_ECH = 0x00000080U;
    SCE->REG_ECH = 0x000037d8U;
    SCE->REG_ECH = 0x0000b400U;
    SCE->REG_ECH = 0x00000099U;
    R_SCE_func101(0xe9f4d766U, 0xc60e2d03U, 0x1fa7a830U, 0xed3e60ddU);
    R_SCE_func310();
    R_SCE_func100(0x751b1264U, 0xe2a38d23U, 0x0052a8a3U, 0xf6e02c2eU);
    SCE->REG_104H = 0x00000058U;
    SCE->REG_E0H = 0x80010020U;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = change_endian_long(0x016efbeaU);
    R_SCE_func080();
    SCE->REG_00H = 0x00013203U;
    SCE->REG_2CH = 0x00000014U;
    R_SCE_func312(1292);
    SCE->REG_ECH = 0x3800db78U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00A60000U;
    R_SCE_func100(0x7a2639a9U, 0xb43e18a0U, 0x350f43f8U, 0xe16b9a92U);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        SCE->REG_28H = 0x00800001U;
        SCE->REG_104H = 0x00000257U;
        SCE->REG_2CH = 0x00000050U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000001U);
        SCE->REG_2CH = 0x00000190U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0xFFFFFFFFU);
        SCE->REG_2CH = 0x00000050U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000000U);
        SCE->REG_28H = 0x00bf0001U;
        R_SCE_func101(0xa354f5b9U, 0xd19e8d7aU, 0xa9ad322dU, 0x023d5281U);
    }
    else
    {
        R_SCE_func101(0xf17c2d3bU, 0x4df9c4c4U, 0x9e3a4a88U, 0x8c116bf4U);
    }
    SCE->REG_24H = 0x000009c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x04001981U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000040c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00800001U;
    SCE->REG_24H = 0x000011c0U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_34H = 0x00000004U;
    SCE->REG_24H = 0x82001181U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_24H = 0x000080c1U;
    /* WAIT_LOOP */
    while (0U != SCE->REG_24H_b.B21)
    {
        /* waiting */
    }
    SCE->REG_28H = 0x00bf0001U;
    SCE->REG_ECH = 0x3800db79U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00A60000U;
    R_SCE_func100(0xa65d5472U, 0x9892f0e0U, 0xb4f3eb48U, 0x1e379814U);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        R_SCE_func100(0xec28935eU, 0xa835a732U, 0x0264c69eU, 0x99367e05U);
        SCE->REG_28H = 0x00800001U;
        SCE->REG_24H = 0x000001c0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_34H = 0x00000400U;
        SCE->REG_24H = 0x800080c1U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_28H = 0x00bf0001U;
        SCE->REG_24H = 0x000001c0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x04000991U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x000040c1U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_28H = 0x00800001U;
        SCE->REG_34H = 0x00000004U;
        SCE->REG_24H = 0x800011c0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x02001191U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x000080c1U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_28H = 0x00bf0001U;
        SCE->REG_ECH = 0x00000bdeU;
        SCE->REG_ECH = 0x02816fdeU;
        SCE->REG_ECH = 0x30008bc0U;
        SCE->REG_ECH = 0x00000000U;
        SCE->REG_ECH = 0x00020020U;
        SCE->REG_ECH = 0x0000d368U;
        SCE->REG_ECH = 0x00000060U;
        SCE->REG_ECH = 0x0000d768U;
        SCE->REG_ECH = 0x00000080U;
        SCE->REG_28H = 0x00800001U;
        SCE->REG_ECH = 0x0000b7c0U;
        SCE->REG_ECH = 0x0000001cU;
        SCE->REG_E0H = 0x8081001eU;
        SCE->REG_00H = 0x00008307U;
        SCE->REG_2CH = 0x00000020U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_28H = 0x00bf0001U;
        SCE->REG_104H = 0x00000058U;
        SCE->REG_E0H = 0x80010020U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x01a2b89bU);
        R_SCE_func080();
        SCE->REG_00H = 0x00013203U;
        SCE->REG_2CH = 0x00000014U;
        R_SCE_func312(1224);
        SCE->REG_24H = 0x000019c0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x04000991U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x0000c0c1U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_28H = 0x00800001U;
        SCE->REG_34H = 0x00000004U;
        SCE->REG_24H = 0x800011c0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x02001191U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x000080c1U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_28H = 0x00bf0001U;
        SCE->REG_ECH = 0x00000bdeU;
        SCE->REG_ECH = 0x02816fdeU;
        SCE->REG_ECH = 0x30008bc0U;
        SCE->REG_ECH = 0x00000000U;
        SCE->REG_ECH = 0x00020020U;
        SCE->REG_ECH = 0x0000d372U;
        SCE->REG_ECH = 0x00000060U;
        SCE->REG_ECH = 0x0000d772U;
        SCE->REG_ECH = 0x00000080U;
        SCE->REG_28H = 0x00800001U;
        SCE->REG_ECH = 0x0000b7c0U;
        SCE->REG_ECH = 0x00000018U;
        SCE->REG_E0H = 0x8081001eU;
        SCE->REG_00H = 0x00008307U;
        SCE->REG_2CH = 0x00000020U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_28H = 0x00bf0001U;
        SCE->REG_24H = 0x000098d0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        R_SCE_func101(0x341a1247U, 0x991801fdU, 0x99b06d2aU, 0x48fde684U);
    }
    else
    {
        R_SCE_func100(0xfa62f3d1U, 0x45d873f3U, 0xd70b5db4U, 0x62b9d483U);
        SCE->REG_ECH = 0x00000bdeU;
        SCE->REG_ECH = 0x02816fdeU;
        SCE->REG_ECH = 0x30008bc0U;
        SCE->REG_ECH = 0x00000000U;
        SCE->REG_ECH = 0x00020020U;
        SCE->REG_ECH = 0x0000d368U;
        SCE->REG_ECH = 0x00000060U;
        SCE->REG_ECH = 0x0000d768U;
        SCE->REG_ECH = 0x00000080U;
        SCE->REG_28H = 0x00800001U;
        SCE->REG_ECH = 0x0000b7c0U;
        SCE->REG_ECH = 0x0000001cU;
        SCE->REG_E0H = 0x8081001eU;
        SCE->REG_00H = 0x00008307U;
        SCE->REG_2CH = 0x00000020U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_28H = 0x00bf0001U;
        SCE->REG_28H = 0x00800001U;
        SCE->REG_ECH = 0x0000b7c0U;
        SCE->REG_ECH = 0x00000018U;
        SCE->REG_24H = 0x000001c0U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_24H = 0x000080c1U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_24H_b.B21)
        {
            /* waiting */
        }
        SCE->REG_E0H = 0x8081001eU;
        SCE->REG_00H = 0x00008307U;
        SCE->REG_2CH = 0x00000020U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_28H = 0x00bf0001U;
        SCE->REG_ECH = 0x0000d772U;
        SCE->REG_104H = 0x00000058U;
        SCE->REG_E0H = 0x80010020U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x01a2b89bU);
        R_SCE_func080();
        SCE->REG_00H = 0x00013203U;
        SCE->REG_2CH = 0x00000010U;
        R_SCE_func312(1224);
        R_SCE_func101(0x5f430397U, 0x24c39b0dU, 0x6e36db4eU, 0x8f177f91U);
    }
    SCE->REG_ECH = 0x0000b7c0U;
    SCE->REG_ECH = 0x00000024U;
    SCE->REG_ECH = 0x0000381eU;
    SCE->REG_ECH = 0x00007c00U;
    SCE->REG_1CH = 0x00602000U;
}

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic/R_SCE_func304.prc
***********************************************************************************************************************/
