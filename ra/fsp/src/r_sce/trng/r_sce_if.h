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

/**********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 *********************************************************************************************************************/

#include "bsp_api.h"

/**********************************************************************************************************************
 * Macro definitions
 *********************************************************************************************************************/

#ifndef R_SCE_IF_HEADER_FILE
 #define R_SCE_IF_HEADER_FILE

 #define HW_SCE_AES128XTS_KEY_BIT_SIZE    (256U)
 #define HW_SCE_AES256XTS_KEY_BIT_SIZE    (512U)

/* OEM Command */
typedef enum e_sce_oem_cmd
{
    SCE_OEM_CMD_AES128 = 5,
    SCE_OEM_CMD_AES192,
    SCE_OEM_CMD_AES256,
    SCE_OEM_CMD_AES128_XTS,
    SCE_OEM_CMD_AES256_XTS,
    SCE_OEM_CMD_RSA1024_PUBLIC,
    SCE_OEM_CMD_RSA1024_PRIVATE,
    SCE_OEM_CMD_RSA2048_PUBLIC,
    SCE_OEM_CMD_RSA2048_PRIVATE,
    SCE_OEM_CMD_RSA3072_PUBLIC,
    SCE_OEM_CMD_RSA3072_PRIVATE,
    SCE_OEM_CMD_RSA4096_PUBLIC,
    SCE_OEM_CMD_RSA4096_PRIVATE,
    SCE_OEM_CMD_ECC_P192_PUBLIC,
    SCE_OEM_CMD_ECC_P192_PRIVATE,
    SCE_OEM_CMD_ECC_P224_PUBLIC,
    SCE_OEM_CMD_ECC_P224_PRIVATE,
    SCE_OEM_CMD_ECC_P256_PUBLIC,
    SCE_OEM_CMD_ECC_P256_PRIVATE,
    SCE_OEM_CMD_ECC_P384_PUBLIC,
    SCE_OEM_CMD_ECC_P384_PRIVATE,
    SCE_OEM_CMD_HMAC_SHA224,
    SCE_OEM_CMD_HMAC_SHA256,
    SCE_OEM_CMD_ECC_P256R1_PUBLIC,
    SCE_OEM_CMD_ECC_P256R1_PRIVATE,
    SCE_OEM_CMD_ECC_P384R1_PUBLIC,
    SCE_OEM_CMD_ECC_P384R1_PRIVATE,
    SCE_OEM_CMD_ECC_P512R1_PUBLIC,
    SCE_OEM_CMD_ECC_P512R1_PRIVATE,
    SCE_OEM_CMD_ECC_SECP256K1_PUBLIC,
    SCE_OEM_CMD_ECC_SECP256K1_PRIVATE,
    SCE_OEM_CMD_NUM
} sce_oem_cmd_t;

typedef enum e_sce_oem_key_type
{
    SCE_OEM_KEY_TYPE_ENCRYPTED = 0,
    SCE_OEM_KEY_TYPE_PLAIN     = 1
} sce_oem_key_type_t;

#endif                                 /* R_SCE_IF_HEADER_FILE */
