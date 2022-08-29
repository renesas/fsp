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

fsp_err_t HW_SCE_LoadHukSub(uint32_t *InData_LC, uint32_t *InData_KeyIndex)
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
    SCE->REG_84H = 0x00006501U;
    SCE->REG_108H = 0x00000000U;
    SCE->REG_A4H = 0x600e180dU;
    /* WAIT_LOOP */
    while (1U != SCE->REG_104H_b.B31)
    {
        /* waiting */
    }
    SCE->REG_100H = S_RAM[16+0 + 0];
    SCE->REG_100H = S_RAM[16+0 + 1];
    SCE->REG_100H = S_RAM[16+0 + 2];
    SCE->REG_100H = S_RAM[16+0 + 3];
    HW_SCE_func048(InData_LC);
    SCE->REG_ECH = 0x0000b420U;
    SCE->REG_ECH = 0x00000009U;
    SCE->REG_ECH = 0x34202801U;
    SCE->REG_ECH = 0x20003401U;
    SCE->REG_ECH = 0x00007c00U;
    SCE->REG_1CH = 0x00602000U;
    if (InData_LC[0] == 0x00000000)
    {
        SCE->REG_1CH = 0x00b80000U;
        HW_SCE_func101(0x7f21f8eeU, 0x4387d537U, 0x5f4fab08U, 0x5ce85537U);
    }
else if (InData_LC[0] == 0x00000001) 
    {
        SCE->REG_1CH = 0x00b00000U;
        HW_SCE_func101(0xa35cf18cU, 0x88d914ecU, 0xe4237afcU, 0x9ca10cb8U);
    }
else if (InData_LC[0] == 0x00000002) 
    {
        SCE->REG_1CH = 0x00b10000U;
        HW_SCE_func101(0x0f8cc1ecU, 0x47db8e4aU, 0x794bf538U, 0x36f37776U);
    }
else if (InData_LC[0] == 0x00000003) 
    {
        SCE->REG_1CH = 0x00b20000U;
        HW_SCE_func101(0x49046cd8U, 0x33f4839eU, 0xd33b2550U, 0x7060f6aaU);
    }
else if (InData_LC[0] == 0x00000004) 
    {
        SCE->REG_1CH = 0x00b30000U;
        HW_SCE_func101(0x78db09b5U, 0x06867378U, 0x16ea2f7fU, 0xc5e05658U);
    }
else if (InData_LC[0] == 0x00000005) 
    {
        SCE->REG_1CH = 0x00b40000U;
        HW_SCE_func101(0xdd0c9c05U, 0xefe284f5U, 0x0d64a46aU, 0x38344179U);
    }
else if (InData_LC[0] == 0x00000006) 
    {
        SCE->REG_1CH = 0x00b50000U;
        HW_SCE_func101(0xf46ae1a7U, 0x44e66b75U, 0x3d719828U, 0x3ef91e92U);
    }
else if (InData_LC[0] == 0x00000007) 
    {
        SCE->REG_1CH = 0x00b60000U;
        HW_SCE_func101(0xb582e8d6U, 0xe4749dabU, 0x8d989e43U, 0x30f8fdbaU);
    }
else if (InData_LC[0] == 0x00000008) 
    {
        SCE->REG_1CH = 0x00b70000U;
        HW_SCE_func101(0xfe7236d9U, 0x11abe458U, 0x988b8f86U, 0xb4dc22a2U);
    }
    else
    {
        SCE->REG_ECH = 0x38000c00U;
        SCE->REG_E0H = 0x00000080U;
        SCE->REG_1CH = 0x00A60000U;
        HW_SCE_func101(0x880ae0edU, 0xba1a8c22U, 0x6d9eb844U, 0xe903f319U);
    }
    HW_SCE_func100(0xc81a1481U, 0xf6c50976U, 0xaba361b8U, 0xa869fb82U);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_func102(0x2b40aae9U, 0x54be7094U, 0x3bd958ceU, 0x08c24539U);
        SCE->REG_1BCH = 0x00000040U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_18H_b.B12)
        {
            /* waiting */
        }
        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        SCE->REG_104H = 0x00000058U;
        SCE->REG_E0H = 0x800100c0U;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = change_endian_long(0x00000065U);
        HW_SCE_func101(0x46d8ce02U, 0x1cb3a1faU, 0xd012f102U, 0xd16dd1e6U);
        HW_SCE_func040();
        SCE->REG_104H = 0x00000361U;
        SCE->REG_A4H = 0x02f006bdU;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_KeyIndex[0];
        SCE->REG_100H = InData_KeyIndex[1];
        SCE->REG_100H = InData_KeyIndex[2];
        SCE->REG_100H = InData_KeyIndex[3];
        SCE->REG_ECH = 0x0000b420U;
        SCE->REG_ECH = 0x00000010U;
        SCE->REG_E0H = 0x80840001U;
        SCE->REG_00H = 0x00008113U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        SCE->REG_ECH = 0x000034e0U;
        SCE->REG_104H = 0x00000361U;
        SCE->REG_A4H = 0x000006bdU;
        /* WAIT_LOOP */
        while (1U != SCE->REG_104H_b.B31)
        {
            /* waiting */
        }
        SCE->REG_100H = InData_KeyIndex[4];
        SCE->REG_100H = InData_KeyIndex[5];
        SCE->REG_100H = InData_KeyIndex[6];
        SCE->REG_100H = InData_KeyIndex[7];
        SCE->REG_A4H = 0x00900c45U;
        SCE->REG_00H = 0x00001113U;
        /* WAIT_LOOP */
        while (0U != SCE->REG_00H_b.B25)
        {
            /* waiting */
        }
        SCE->REG_1CH = 0x00001800U;
        HW_SCE_func100(0x6e5dc2e1U, 0xfefad0dfU, 0xa6dc2d50U, 0xa06f5c8aU);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            HW_SCE_func102(0xf6405773U, 0xd58fe6f0U, 0x6c18730eU, 0xb679263dU);
            SCE->REG_1BCH = 0x00000040U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_18H_b.B12)
            {
                /* waiting */
            }
            return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
        }
        else
        {
            HW_SCE_func100(0x54237ac8U, 0xb393b5ebU, 0x40a210f3U, 0xd16be39fU);
            SCE->REG_A4H = 0x6044380cU;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000000U);
            SCE->REG_104H = 0x00000051U;
            SCE->REG_A4H = 0x00440604U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000000U);
            SCE->REG_A4H = 0x600c3c1cU;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x0152db38U);
            HW_SCE_func100(0xef0905e9U, 0xd439afdcU, 0xcc637990U, 0x862b91dbU);
            SCE->REG_A4H = 0x4004080cU;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000000U);
            SCE->REG_104H = 0x00000051U;
            SCE->REG_A4H = 0x00440604U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000000U);
            SCE->REG_A4H = 0x40080c9cU;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x01f7370eU);
            SCE->REG_13CH = 0x00000210U;
            HW_SCE_func102(0xe30fe9d5U, 0xb397d063U, 0xa0603457U, 0x8378b663U);
            SCE->REG_1BCH = 0x00000040U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_18H_b.B12)
            {
                /* waiting */
            }
            return FSP_SUCCESS;
        }
    }
}

/***********************************************************************************************************************
End of function ./input_dir/RA6T_Boot/200821/HW_SCE/Cryptographic/HW_SCE_p65.prc
***********************************************************************************************************************/
