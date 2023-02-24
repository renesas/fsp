/***********************************************************************************************************************
 * Copyright [2020-2023] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software and documentation are supplied by Renesas Electronics America Inc. and may only be used with products
 * of Renesas Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.  Renesas products are
 * sold pursuant to Renesas terms and conditions of sale.  Purchasers are solely responsible for the selection and use
 * of Renesas products and Renesas assumes no liability.  No license, express or implied, to any intellectual property
 * right is granted by Renesas. This software is protected under all applicable laws, including copyright laws. Renesas
 * reserves the right to change or discontinue this software and/or this documentation. THE SOFTWARE AND DOCUMENTATION
 * IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND TO THE FULLEST EXTENT
 * PERMISSIBLE UNDER APPLICABLE LAW, DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY, INCLUDING WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE SOFTWARE OR
 * DOCUMENTATION.  RENESAS SHALL HAVE NO LIABILITY ARISING OUT OF ANY SECURITY VULNERABILITY OR BREACH.  TO THE MAXIMUM
 * EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE OR DOCUMENTATION
 * (OR ANY PERSON OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER, INCLUDING,
 * WITHOUT LIMITATION, ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES; ANY LOST PROFITS,
 * OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF THE POSSIBILITY
 * OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS.
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 ***********************************************************************************************************************/
#include "hw_sce_ra_private.h"

/***********************************************************************************************************************
 * Macro definitions
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Imported global variables and functions
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global variables
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables and functions
 ***********************************************************************************************************************/

uint32_t change_endian_long (uint32_t a)
{
    return __REV(a);
}

fsp_err_t HW_SCE_GenerateAes128RandomKeyIndexSub (uint32_t * OutData_KeyIndex)
{
    FSP_PARAMETER_NOT_USED(OutData_KeyIndex);

    return FSP_ERR_UNSUPPORTED;
}

fsp_err_t HW_SCE_GenerateAes192RandomKeyIndexSub (uint32_t * OutData_KeyIndex)
{
    FSP_PARAMETER_NOT_USED(OutData_KeyIndex);

    return FSP_ERR_UNSUPPORTED;
}

fsp_err_t HW_SCE_GenerateAes256RandomKeyIndexSub (uint32_t * OutData_KeyIndex)
{
    FSP_PARAMETER_NOT_USED(OutData_KeyIndex);

    return FSP_ERR_UNSUPPORTED;
}

fsp_err_t HW_SCE_Aes192EncryptDecryptInitSub (const uint32_t * InData_Cmd,
                                              const uint32_t * InData_KeyIndex,
                                              const uint32_t * InData_IV)
{
    FSP_PARAMETER_NOT_USED(InData_Cmd);
    FSP_PARAMETER_NOT_USED(InData_KeyIndex);
    FSP_PARAMETER_NOT_USED(InData_IV);

    return FSP_ERR_UNSUPPORTED;
}

void HW_SCE_Aes192EncryptDecryptUpdateSub (const uint32_t * InData_Text, uint32_t * OutData_Text,
                                           const uint32_t MAX_CNT)
{
    FSP_PARAMETER_NOT_USED(InData_Text);
    FSP_PARAMETER_NOT_USED(OutData_Text);
    FSP_PARAMETER_NOT_USED(MAX_CNT);
}

fsp_err_t HW_SCE_Aes192EncryptDecryptFinalSub (void)
{
    return FSP_ERR_UNSUPPORTED;
}

fsp_err_t HW_SCE_Aes128EncryptDecryptInitSub (const uint32_t * InData_KeyType,
                                              const uint32_t * InData_Cmd,
                                              const uint32_t * InData_KeyIndex,
                                              const uint32_t * InData_IV)
{
    FSP_PARAMETER_NOT_USED(InData_KeyType);
    FSP_PARAMETER_NOT_USED(InData_Cmd);
    FSP_PARAMETER_NOT_USED(InData_KeyIndex);
    FSP_PARAMETER_NOT_USED(InData_IV);

    return FSP_ERR_UNSUPPORTED;
}

void HW_SCE_Aes128EncryptDecryptUpdateSub (const uint32_t * InData_Text, uint32_t * OutData_Text,
                                           const uint32_t MAX_CNT)
{
    FSP_PARAMETER_NOT_USED(InData_Text);
    FSP_PARAMETER_NOT_USED(OutData_Text);
    FSP_PARAMETER_NOT_USED(MAX_CNT);
}

fsp_err_t HW_SCE_Aes128EncryptDecryptFinalSub (void)
{
    return FSP_ERR_UNSUPPORTED;
}

fsp_err_t HW_SCE_Aes256EncryptDecryptInitSub (const uint32_t * InData_KeyType,
                                              const uint32_t * InData_Cmd,
                                              const uint32_t * InData_KeyIndex,
                                              const uint32_t * InData_IV)
{
    FSP_PARAMETER_NOT_USED(InData_KeyType);
    FSP_PARAMETER_NOT_USED(InData_Cmd);
    FSP_PARAMETER_NOT_USED(InData_KeyIndex);
    FSP_PARAMETER_NOT_USED(InData_IV);

    return FSP_ERR_UNSUPPORTED;
}

void HW_SCE_Aes256EncryptDecryptUpdateSub (const uint32_t * InData_Text, uint32_t * OutData_Text,
                                           const uint32_t MAX_CNT)
{
    FSP_PARAMETER_NOT_USED(InData_Text);
    FSP_PARAMETER_NOT_USED(OutData_Text);
    FSP_PARAMETER_NOT_USED(MAX_CNT);
}

fsp_err_t HW_SCE_Aes256EncryptDecryptFinalSub (void)
{
    return FSP_ERR_UNSUPPORTED;
}
