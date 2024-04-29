/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

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

fsp_err_t HW_SCE_Aes128EncryptDecryptInitSub (const uint32_t *InData_KeyType,
                                                 const uint32_t * InData_Cmd,
                                                 const uint32_t * InData_KeyIndex,
                                                 const uint32_t * InData_IV)
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
    (void)InData_KeyType;
    if (0x0U != (SCE->REG_1BCH & 0x1fU))
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }
    SCE->REG_84H = 0x00004702U;
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
    SCE->REG_E0H = 0x80020000U;
    SCE->REG_104H = 0x00000168U;
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
    SCE->REG_100H = InData_KeyType[0];
    SCE->REG_ECH = 0x38008820U;
    SCE->REG_ECH = 0x00000001U;
    SCE->REG_E0H = 0x00000080U;
    SCE->REG_1CH = 0x00260000U;
    HW_SCE_p_func100(0x532c8e1cU, 0xd74f9414U, 0xf0668f09U, 0xdb7c033fU);
    SCE->REG_1CH = 0x00400000U;
    SCE->REG_1D0H = 0x00000000U;
    if (1U == (SCE->REG_1CH_b.B22))
    {
        HW_SCE_p_func102(0x08fc129bU, 0xca48bf72U, 0x83bffd7bU, 0xe2ae50ebU);
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
        SCE->REG_ECH = 0x3000a800U;
        SCE->REG_ECH = 0x00000006U;
        SCE->REG_ECH = 0x00010020U;
        SCE->REG_ECH = 0x0000b400U;
        SCE->REG_ECH = 0x00000006U;
        SCE->REG_ECH = 0x00000080U;
        SCE->REG_ECH = 0x3420a800U;
        SCE->REG_ECH = 0x00000005U;
        SCE->REG_E0H = 0x00000080U;
        SCE->REG_1CH = 0x00260000U;
        HW_SCE_p_func100(0x0cf2a0baU, 0xfaa011d9U, 0xd6260a22U, 0x6b06c529U);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            SCE->REG_ECH = 0x38000c21U;
            SCE->REG_E0H = 0x00000080U;
            SCE->REG_1CH = 0x00260000U;
            HW_SCE_p_func100(0x9d6b7d16U, 0xb1711fa5U, 0xb576511fU, 0x6e4369ceU);
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
                SCE->REG_100H = change_endian_long(0x00000047U);
                HW_SCE_p_func101(0xd20024d3U, 0xacee990cU, 0x97604b90U, 0x603c6bf1U);
                HW_SCE_p_func043();
                SCE->REG_ECH = 0x0000b4e0U;
                SCE->REG_ECH = 0x00000005U;
                HW_SCE_p_func101(0x8008a7c5U, 0x05828c5bU, 0x56c92714U, 0xc12875f0U);
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
                SCE->REG_100H = change_endian_long(0x00000047U);
                HW_SCE_p_func101(0x14e64260U, 0xced09e8dU, 0xeb683f31U, 0x5d23c058U);
                HW_SCE_p_func068();
                SCE->REG_ECH = 0x0000b4e0U;
                SCE->REG_ECH = 0x0146c04bU;
                HW_SCE_p_func101(0x5e4130b7U, 0x2f8db7dfU, 0x1fa3ae39U, 0xb088b8bdU);
            }
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x800103a0U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000047U);
            HW_SCE_p_func101(0xbd5f7685U, 0x83297732U, 0xe56b3888U, 0x418c6101U);
            HW_SCE_p_func044();
            HW_SCE_p_func100(0x5250cc11U, 0xb301ced7U, 0x9817c7a8U, 0x9bd7e48bU);
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
            SCE->REG_C4H = 0x00900c45U;
            SCE->REG_00H = 0x00002213U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            HW_SCE_p_func101(0x71a31542U, 0x9aed6fa8U, 0xf59174f1U, 0x27db8085U);
        }
        else
        {
            SCE->REG_104H = 0x00000368U;
            SCE->REG_E0H = 0x80040040U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_KeyIndex[0];
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_KeyIndex[1];
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_KeyIndex[2];
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_KeyIndex[3];
            SCE->REG_ECH = 0x00000bdeU;
            SCE->REG_ECH = 0x000037e2U;
            SCE->REG_ECH = 0x00008fe0U;
            SCE->REG_ECH = 0x00ff0000U;
            SCE->REG_ECH = 0x38008be0U;
            SCE->REG_ECH = 0x00000000U;
            SCE->REG_ECH = 0x1000d3c0U;
            SCE->REG_ECH = 0x38008800U;
            SCE->REG_ECH = 0x00000005U;
            SCE->REG_ECH = 0x1000b540U;
            SCE->REG_ECH = 0x0000000fU;
            SCE->REG_ECH = 0x2000b540U;
            SCE->REG_ECH = 0x0000000eU;
            SCE->REG_ECH = 0x3800584aU;
            SCE->REG_ECH = 0x2000d3c1U;
            SCE->REG_ECH = 0x000037e2U;
            SCE->REG_ECH = 0x00008fe0U;
            SCE->REG_ECH = 0x000000feU;
            SCE->REG_ECH = 0x38008be0U;
            SCE->REG_ECH = 0x00000000U;
            SCE->REG_ECH = 0x1000d3c2U;
            SCE->REG_ECH = 0x38008bc0U;
            SCE->REG_ECH = 0x00000007U;
            SCE->REG_E0H = 0x00000080U;
            SCE->REG_1CH = 0x00A60000U;
            SCE->REG_ECH = 0x0000a800U;
            SCE->REG_ECH = 0x00000003U;
            SCE->REG_ECH = 0x00003542U;
            SCE->REG_ECH = 0x00003563U;
            SCE->REG_ECH = 0x00003584U;
            SCE->REG_ECH = 0x000035a5U;
            SCE->REG_104H = 0x00000058U;
            SCE->REG_E0H = 0x800103a0U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = change_endian_long(0x00000047U);
            HW_SCE_p_func101(0x1687882dU, 0x9da40824U, 0xc51cb495U, 0x72e5393fU);
            HW_SCE_p_func059();
            HW_SCE_p_func100(0x1d35c958U, 0x8ab99b81U, 0x1fab250aU, 0xeeb14dabU);
            SCE->REG_104H = 0x00000362U;
            SCE->REG_D0H = 0x40000000U;
            SCE->REG_C4H = 0x02f087b5U;
            /* WAIT_LOOP */
            while (1U != SCE->REG_104H_b.B31)
            {
                /* waiting */
            }
            SCE->REG_100H = InData_KeyIndex[4];
            SCE->REG_100H = InData_KeyIndex[5];
            SCE->REG_100H = InData_KeyIndex[6];
            SCE->REG_100H = InData_KeyIndex[7];
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
            SCE->REG_100H = InData_KeyIndex[8];
            SCE->REG_100H = InData_KeyIndex[9];
            SCE->REG_100H = InData_KeyIndex[10];
            SCE->REG_100H = InData_KeyIndex[11];
            SCE->REG_C4H = 0x00900c45U;
            SCE->REG_00H = 0x00002213U;
            /* WAIT_LOOP */
            while (0U != SCE->REG_00H_b.B25)
            {
                /* waiting */
            }
            SCE->REG_1CH = 0x00001800U;
            HW_SCE_p_func101(0x2ed80b05U, 0x05c0a092U, 0x2d7c1493U, 0xa013dd18U);
        }
        HW_SCE_p_func100(0x23d71ff2U, 0x269e97edU, 0x7c5758d6U, 0x7eee3c98U);
        SCE->REG_1CH = 0x00400000U;
        SCE->REG_1D0H = 0x00000000U;
        if (1U == (SCE->REG_1CH_b.B22))
        {
            HW_SCE_p_func102(0xc49afd04U, 0xad543216U, 0x365184f1U, 0x682bed01U);
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
            HW_SCE_p_func100(0xaeda5fa2U, 0xde5b2655U, 0xf5f717d4U, 0x561961b6U);
            SCE->REG_ECH = 0x00007c00U;
            SCE->REG_1CH = 0x00600000U;
            SCE->REG_1D0H = 0x00000000U;
            if (0x00000000U == (SCE->REG_1CH & 0xff000000U))
            {
                HW_SCE_p_func101(0x6317b67fU, 0x19fb60bbU, 0xfd5be6a1U, 0xe4ba0012U);
            }
            else if (0x01000000U == (SCE->REG_1CH & 0xff000000U))
            {
                HW_SCE_p_func101(0x2cbc50c3U, 0x98f57fb0U, 0x6cb20cc8U, 0xb53b230fU);
            }
            else if (0x02000000U == (SCE->REG_1CH & 0xff000000U))
            {
                SCE->REG_104H = 0x00000361U;
                SCE->REG_A4H = 0x00040805U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = InData_IV[0];
                SCE->REG_100H = InData_IV[1];
                SCE->REG_100H = InData_IV[2];
                SCE->REG_100H = InData_IV[3];
                HW_SCE_p_func101(0xbb9fe1d2U, 0x1a6df08bU, 0x363b6c60U, 0xd6a6c086U);
            }
            else if (0x03000000U == (SCE->REG_1CH & 0xff000000U))
            {
                SCE->REG_104H = 0x00000361U;
                SCE->REG_A4H = 0x00040805U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = InData_IV[0];
                SCE->REG_100H = InData_IV[1];
                SCE->REG_100H = InData_IV[2];
                SCE->REG_100H = InData_IV[3];
                HW_SCE_p_func101(0x2071f517U, 0x5e521a7cU, 0x0778d7aaU, 0xf1658938U);
            }
            else if (0x04000000U == (SCE->REG_1CH & 0xff000000U))
            {
                SCE->REG_104H = 0x00000361U;
                SCE->REG_A4H = 0x00040805U;
                /* WAIT_LOOP */
                while (1U != SCE->REG_104H_b.B31)
                {
                    /* waiting */
                }
                SCE->REG_100H = InData_IV[0];
                SCE->REG_100H = InData_IV[1];
                SCE->REG_100H = InData_IV[2];
                SCE->REG_100H = InData_IV[3];
                HW_SCE_p_func101(0xc1078ed4U, 0x62c94addU, 0x1c3172c4U, 0x73654dd1U);
            }
            return FSP_SUCCESS;
        }
    }
}

/***********************************************************************************************************************
End of function ./input_dir/S6C1/Cryptographic_PlainKey/HW_SCE_p_p47i_r2.prc
***********************************************************************************************************************/
