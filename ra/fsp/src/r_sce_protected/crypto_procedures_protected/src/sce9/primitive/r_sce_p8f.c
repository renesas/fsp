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

fsp_err_t R_SCE_AesKeyWrapSub(uint32_t *InData_Cmd, uint32_t *InData_KeyIndex, int32_t KEY_INDEX_SIZE, uint32_t *InData_WrappedKeyType, uint32_t *InData_WrappedKeyIndex, uint32_t WRAPPED_KEY_SIZE, uint32_t *OutData_Text)
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
    SCE->REG_84H = 0x00008f01U;
    SCE->REG_108H = 0x00000000U;
    SCE->REG_104H = 0x00000168U;
    SCE->REG_E0H = 0x80020100U;
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
    SCE->REG_ECH = 0x00003409U;
    SCE->REG_ECH = 0x3420a900U;
    SCE->REG_ECH = 0x00000002U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00A60000U;
    SCE->REG_ECH = 0x3420a800U;
    SCE->REG_ECH = 0x00000003U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00A60000U;
    R_SCE_func100(0x305b5351U, 0x83de6717U, 0x6cba8950U, 0xa2b864e1U);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        R_SCE_func102(0x5c3a55e3U, 0xa0c3ecc3U, 0xfe11efd2U, 0x27f3f41cU);
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
        SCE->REG_100H = change_endian_long(0x0000008fU);
        R_SCE_func101(0xe07b9c32U, 0x4dadeecaU, 0x1d32404dU, 0x513c7ae7U);
        R_SCE_func043();
        SCE->REG_ECH = 0x38000d08U;
        SCE->REG_E0H = 0x00000080U;
        SCE->REG_1CH = 0x00260000U;
        R_SCE_func100(0xfe2d3562U, 0x35b00141U, 0x0321e8e0U, 0xbc1264c3U);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            SCE->REG_ECH = 0x0000b4e0U;
            SCE->REG_ECH = 0x00000005U;
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x800103a0U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x0000008fU);
            R_SCE_func101(0x555e89e1U, 0x2019090bU, 0xe3fbb932U, 0x730f87e1U);
            R_SCE_func044();
            R_SCE_func100(0x3fbf2779U, 0x177c865eU, 0xcb70763fU, 0x9c30d3ceU);
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
            R_SCE_func101(0x051c7a41U, 0xf3e46c79U, 0x1db171daU, 0xf478499aU);
        }
        else
        {
            SCE->REG_ECH = 0x0000b4e0U;
            SCE->REG_ECH = 0x00000007U;
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x800103a0U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000049U);
            R_SCE_func101(0x073eb526U, 0x8866c426U, 0x2499eabcU, 0xd50a629cU);
            R_SCE_func044();
            R_SCE_func100(0x36ac2bd4U, 0x7e94cd53U, 0xf5089cb2U, 0x96149e95U);
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
            R_SCE_func100(0x5b8c39f8U, 0x9d5a1504U, 0x1d407669U, 0xfe2a943eU);
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
            R_SCE_func101(0x3a16aecfU, 0x6e42d934U, 0x977e9877U, 0x5eabd49bU);
        }
        SCE->REG_C4H = 0x00900c45U;
        SCE->REG_00H = 0x00002213U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        R_SCE_func100(0xe29deb0cU, 0xd6a8327bU, 0xf3ba375bU, 0x0f489ec9U);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            R_SCE_func102(0x0c0c0f82U, 0x8b143776U, 0x2a13a8aeU, 0xa90178d7U);
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
            SCE->REG_ECH = 0x000035c7U;
            SCE->REG_104H = 0x00000068U;
            SCE->REG_E0H = 0x800100e0U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_WrappedKeyIndex[0];
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x800103a0U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x0000004aU);
            R_SCE_func101(0xfd520067U, 0xbb3e0262U, 0xb2168269U, 0xfa545989U);
            R_SCE_func043();
            SCE->REG_ECH = 0x000034e6U;
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x800103a0U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x0000004aU);
            R_SCE_func101(0xc297c1e4U, 0xe8534007U, 0xc26cf313U, 0x57c0f657U);
            R_SCE_func044();
            SCE->REG_ECH = 0x000034eeU;
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
            SCE->REG_ECH = 0x0000b7e0U;
            SCE->REG_ECH = 0x00000008U;
            SCE->REG_ECH = 0x0000b780U;
            SCE->REG_ECH = 0x00000010U;
            SCE->REG_ECH = 0x00000bdeU;
            SCE->REG_ECH = 0x0000b760U;
            SCE->REG_ECH = 0x00000004U;
            SCE->REG_ECH = 0x0000a8e0U;
            SCE->REG_ECH = 0x00000005U;
            for(iLoop = 0; iLoop < (uint32_t)KEY_INDEX_SIZE-5; iLoop = iLoop + 4)
            {
                SCE->REG_104H = 0x00000362U;
                SCE->REG_D0H = 0x40000000U;
                SCE->REG_C4H = 0x00f087b5U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = InData_WrappedKeyIndex[iLoop+1 + 0];
                SCE->REG_100H = InData_WrappedKeyIndex[iLoop+1 + 1];
                SCE->REG_100H = InData_WrappedKeyIndex[iLoop+1 + 2];
                SCE->REG_100H = InData_WrappedKeyIndex[iLoop+1 + 3];
                SCE->REG_E0H = 0x8084001fU;
                SCE->REG_00H = 0x00008213U;
                /* WAIT_LOOP */
                while (0U != SCE->REG_00H_b.B25)
                {
                    /* waiting */
                }
                SCE->REG_1CH = 0x00001800U;
                SCE->REG_ECH = 0x000027fcU;
                SCE->REG_ECH = 0x000027dbU;
                R_SCE_func101(0x7929fa04U, 0xd415ca63U, 0x79d9e785U, 0xbb4704abU);
            }
            SCE->REG_ECH = 0x38000bc7U;
            SCE->REG_E0H = 0x00000080U;
            SCE->REG_1CH = 0x00260000U;
            SCE->REG_1CH = 0x00402000U;
            SCE->REG_104H = 0x00000362U;
            SCE->REG_D0H = 0x40000000U;
            SCE->REG_C4H = 0x000087b5U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_WrappedKeyIndex[iLoop+1 + 0];
            SCE->REG_100H = InData_WrappedKeyIndex[iLoop+1 + 1];
            SCE->REG_100H = InData_WrappedKeyIndex[iLoop+1 + 2];
            SCE->REG_100H = InData_WrappedKeyIndex[iLoop+1 + 3];
            SCE->REG_C4H = 0x00900c45U;
            SCE->REG_00H = 0x00002213U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            R_SCE_func100(0x5fdb42e0U, 0xe6f0f23eU, 0x6335e689U, 0x3da1fd30U);
            SCE->REG_1CH = 0x00400000U;
            SCE->REG_1D0H = 0x00000000U;
            if (1U == (SCE->REG_1CH_b.B22))
            {
                R_SCE_func102(0x1843c1a2U, 0xb52d7749U, 0xf91ab81aU, 0x9f2bceedU);
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
                SCE->REG_ECH = 0x0000b400U;
                SCE->REG_ECH = 0xa6a6a6a6U;
                SCE->REG_ECH = 0x00003420U;
                SCE->REG_ECH = 0x0000b760U;
                SCE->REG_ECH = 0x00000008U;
                SCE->REG_ECH = 0x0000b780U;
                SCE->REG_ECH = 0x00000004U;
                SCE->REG_ECH = 0x0000b480U;
                SCE->REG_ECH = 0x00000001U;
                SCE->REG_ECH = 0x00000bdeU;
                for(jLoop = 0; jLoop <= 5; jLoop = jLoop + 1)
                {
                    SCE->REG_ECH = 0x000037fbU;
                    SCE->REG_ECH = 0x00000bbdU;
                    for(iLoop = 1; iLoop <= (WRAPPED_KEY_SIZE-2)/2; iLoop = iLoop + 1)
                    {
                        SCE->REG_A4H = 0x00008a85U;
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
                        SCE->REG_ECH = 0x00000824U;
                        SCE->REG_ECH = 0x00003c5fU;
                        SCE->REG_ECH = 0x000027fcU;
                        SCE->REG_ECH = 0x00003c7fU;
                        SCE->REG_ECH = 0x000027fcU;
                        SCE->REG_ECH = 0x00002c80U;
                        SCE->REG_ECH = 0x00002fa0U;
                        R_SCE_func101(0xda78279fU, 0x0a5f1eb6U, 0xc06af53dU, 0xeab4c9a0U);
                    }
                    SCE->REG_ECH = 0x38000ba5U;
                    SCE->REG_E0H = 0x00000080U;
                    SCE->REG_1CH = 0x00260000U;
                    SCE->REG_1CH = 0x00402000U;
                    SCE->REG_ECH = 0x00002fc0U;
                    R_SCE_func101(0x34d25252U, 0x40dbdb6dU, 0x99df6038U, 0x67fa964aU);
                }
                SCE->REG_ECH = 0x38008bc0U;
                SCE->REG_ECH = 0x00000006U;
                SCE->REG_E0H = 0x00000080U;
                SCE->REG_1CH = 0x00260000U;
                SCE->REG_1CH = 0x00402000U;
                SCE->REG_ECH = 0x00000bffU;
                SCE->REG_ECH = 0x00003c1fU;
                SCE->REG_ECH = 0x000027fcU;
                SCE->REG_ECH = 0x00003c3fU;
                SCE->REG_ECH = 0x00000bffU;
                SCE->REG_ECH = 0x00000bdeU;
                SCE->REG_ECH = 0x000037a5U;
                SCE->REG_ECH = 0x00002fa0U;
                SCE->REG_ECH = 0x0000b780U;
                SCE->REG_ECH = 0x00000008U;
                for(iLoop = 0; iLoop < WRAPPED_KEY_SIZE; iLoop = iLoop + 2)
                {
                    SCE->REG_ECH = 0x000008c6U;
                    SCE->REG_ECH = 0x34202bddU;
                    SCE->REG_ECH = 0x2000d0c0U;
                    SCE->REG_ECH = 0x00007c06U;
                    SCE->REG_1CH = 0x00602000U;
                    R_SCE_func100(0x6f510921U, 0xe28adf5bU, 0x31e7aa86U, 0x438b03b1U);
                    SCE->REG_E0H = 0x8182001fU;
                    SCE->REG_04H = 0x0000060aU;
                    /* WAIT_LOOP */
                    while (1U != SCE->REG_04H_b.B30)
                    {
                        /* waiting */
                    }
                    OutData_Text[iLoop + 0] = SCE->REG_100H;
                    /* WAIT_LOOP */
                    while (1U != SCE->REG_04H_b.B30)
                    {
                        /* waiting */
                    }
                    OutData_Text[iLoop+1 + 0] = SCE->REG_100H;
                    SCE->REG_ECH = 0x000027fcU;
                    SCE->REG_ECH = 0x00002fc0U;
                    R_SCE_func101(0xb9ed7705U, 0x23665053U, 0x13bd71d9U, 0x4e7a1e30U);
                }
                SCE->REG_ECH = 0x38000bddU;
                SCE->REG_E0H = 0x00000080U;
                SCE->REG_1CH = 0x00260000U;
                SCE->REG_1CH = 0x00402000U;
                R_SCE_func102(0x1a61c563U, 0x297d72b2U, 0x6448120bU, 0xb7ec730eU);
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
End of function ./input_dir/S6C1/Cryptographic/R_SCE_p8f.prc
***********************************************************************************************************************/
