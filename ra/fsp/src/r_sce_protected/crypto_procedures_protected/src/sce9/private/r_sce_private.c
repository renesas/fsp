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
 * Includes
 **********************************************************************************************************************/
#include <string.h>
#include "r_sce_private.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#ifndef SCE_HEX_6A09E667
 #define SCE_HEX_6A09E667    0x6a09e667UL
#endif
#ifndef SCE_HEX_BB67AE85
 #define SCE_HEX_BB67AE85    0xbb67ae85UL
#endif
#ifndef SCE_HEX_3C6EF372
 #define SCE_HEX_3C6EF372    0x3c6ef372UL
#endif
#ifndef SCE_HEX_A54FF53A
 #define SCE_HEX_A54FF53A    0xa54ff53aUL
#endif
#ifndef SCE_HEX_510E527F
 #define SCE_HEX_510E527F    0x510e527fUL
#endif
#ifndef SCE_HEX_9B05688C
 #define SCE_HEX_9B05688C    0x9b05688cUL
#endif
#ifndef SCE_HEX_1F83D9AB
 #define SCE_HEX_1F83D9AB    0x1f83d9abUL
#endif
#ifndef SCE_HEX_5BE0CD19
 #define SCE_HEX_5BE0CD19    0x5be0cd19UL
#endif

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Encrypt data to cipher using AES ECB mode algorithm with AES 128 key.
 *
 * @param InData_KeyIndex User key generation information area.
 *
 * @retval FSP_SUCCESS                          Normal termination.
 * @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      Input illegal user Key Generation Information
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT resource conflict
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              Internal error occurred.
 **********************************************************************************************************************/
fsp_err_t R_SCE_Aes128EcbEncryptInitPrivate (sce_aes_wrapped_key_t * InData_KeyIndex)
{
    uint32_t indata_keytype = 0; /* For normal */
    uint32_t indata_cmd   = 0;
    uint32_t indata_iv[4] =            /* dummy */
    {
        0
    };

    if ((SCE_KEY_INDEX_TYPE_AES128 != InData_KeyIndex->type) && (SCE_KEY_INDEX_TYPE_AES128_FOR_ECDH != InData_KeyIndex->type))
    {
        return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
    }
    indata_cmd = change_endian_long(0); /* ECB-Encrypt command */
    if (SCE_KEY_INDEX_TYPE_AES128_FOR_ECDH == InData_KeyIndex->type)
    {
        indata_keytype = change_endian_long(2); /* For ECDH */
    }
    return R_SCE_Aes128EncryptDecryptInitSub(&indata_keytype, &indata_cmd, InData_KeyIndex->value, indata_iv);
}

/*******************************************************************************************************************//**
 * Encrypt data to cipher using AES ECB mode algorithm with AES 128 key.
 *
 * @param InData_Text  Input plain text.
 * @param OutData_Text Output cipher text.
 * @param MAX_CNT      Input byte size of plain.
 *
 * @retval FSP_SUCCESS Normal termination.
 **********************************************************************************************************************/
fsp_err_t R_SCE_Aes128EcbEncryptUpdatePrivate (uint32_t * InData_Text, uint32_t * OutData_Text, uint32_t MAX_CNT)
{
    R_SCE_Aes128EncryptDecryptUpdateSub(InData_Text, OutData_Text, MAX_CNT);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Encrypt data to cipher using AES ECB mode algorithm with AES 128 key.
 *
 * @param OutData_Text   Output cipher text.
 * @param OutData_length Output byte size of cipher.
 *
 * @retval FSP_SUCCESS             Normal termination.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL Internal error occurred.
 **********************************************************************************************************************/
fsp_err_t R_SCE_Aes128EcbEncryptFinalPrivate (uint32_t * OutData_Text, uint32_t * OutData_length)
{
    FSP_PARAMETER_NOT_USED(OutData_Text);
    FSP_PARAMETER_NOT_USED(OutData_length);

    return R_SCE_Aes128EncryptDecryptFinalSub();
}

/*******************************************************************************************************************//**
 * Decrypt data to plain using AES ECB mode algorithm with AES 128 key.
 *
 * @param InData_KeyIndex User key generation information area.
 *
 * @retval FSP_SUCCESS                          Normal termination.
 * @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      Input illegal user Key Generation Information
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT resource conflict
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              Internal error occurred.
 **********************************************************************************************************************/
fsp_err_t R_SCE_Aes128EcbDecryptInitPrivate (sce_aes_wrapped_key_t * InData_KeyIndex)
{
    uint32_t indata_keytype = 0; /* For normal */
    uint32_t indata_cmd   = 0;
    uint32_t indata_iv[4] =            /* dummy */
    {
        0
    };

    if ((SCE_KEY_INDEX_TYPE_AES128 != InData_KeyIndex->type) && (SCE_KEY_INDEX_TYPE_AES128_FOR_ECDH != InData_KeyIndex->type))
    {
        return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
    }
    indata_cmd = change_endian_long(1); /* ECB-Decrypt command */
    if (SCE_KEY_INDEX_TYPE_AES128_FOR_ECDH == InData_KeyIndex->type)
    {
        indata_keytype = change_endian_long(2); /* For ECDH */
    }
    return R_SCE_Aes128EncryptDecryptInitSub(&indata_keytype, &indata_cmd, InData_KeyIndex->value, indata_iv);
}

/*******************************************************************************************************************//**
 * Decrypt data to plain using AES ECB mode algorithm with AES 128 key.
 *
 * @param InData_Text  Input cipher text.
 * @param OutData_Text Output plain text.
 * @param MAX_CNT      Input byte size of cipher.
 *
 * @retval FSP_SUCCESS Normal termination.
 **********************************************************************************************************************/
fsp_err_t R_SCE_Aes128EcbDecryptUpdatePrivate (uint32_t * InData_Text, uint32_t * OutData_Text, uint32_t MAX_CNT)
{
    R_SCE_Aes128EncryptDecryptUpdateSub(InData_Text, OutData_Text, MAX_CNT);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Decrypt data to plain using AES ECB mode algorithm with AES 128 key.
 *
 * @param OutData_Text   Output plain text.
 * @param OutData_length Output byte size of plain.
 *
 * @retval FSP_SUCCESS             Normal termination.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL Internal error occurred.
 **********************************************************************************************************************/
fsp_err_t R_SCE_Aes128EcbDecryptFinalPrivate (uint32_t * OutData_Text, uint32_t * OutData_length)
{
    FSP_PARAMETER_NOT_USED(OutData_Text);
    FSP_PARAMETER_NOT_USED(OutData_length);

    return R_SCE_Aes128EncryptDecryptFinalSub();
}

/*******************************************************************************************************************//**
 * Encrypt data to cipher using AES ECB mode algorithm with AES 256 key.
 *
 * @param InData_KeyIndex User key generation information area.
 *
 * @retval FSP_SUCCESS                          Normal termination.
 * @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      Input illegal user Key Generation Information
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT resource conflict
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              Internal error occurred.
 **********************************************************************************************************************/
fsp_err_t R_SCE_Aes256EcbEncryptInitPrivate (sce_aes_wrapped_key_t * InData_KeyIndex)
{
    uint32_t indata_keytype = 0; /* For normal */
    uint32_t indata_cmd   = 0;
    uint32_t indata_iv[4] =            /* dummy */
    {
        0
    };

    if ((SCE_KEY_INDEX_TYPE_AES256 != InData_KeyIndex->type) && (SCE_KEY_INDEX_TYPE_AES256_FOR_ECDH != InData_KeyIndex->type))
    {
        return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
    }
    indata_cmd = change_endian_long(0); /* ECB-Encrypt command */
    if (SCE_KEY_INDEX_TYPE_AES256_FOR_ECDH == InData_KeyIndex->type)
    {
        indata_keytype = change_endian_long(2); /* For ECDH */
    }
    return R_SCE_Aes256EncryptDecryptInitSub(&indata_keytype, &indata_cmd, InData_KeyIndex->value, indata_iv);
}

/*******************************************************************************************************************//**
 * Encrypt data to cipher using AES ECB mode algorithm with AES 256 key.
 *
 * @param InData_Text  Input plain text.
 * @param OutData_Text Output cipher text.
 * @param MAX_CNT      Input byte size of plain.
 *
 * @retval FSP_SUCCESS Normal termination.
 **********************************************************************************************************************/
fsp_err_t R_SCE_Aes256EcbEncryptUpdatePrivate (uint32_t * InData_Text, uint32_t * OutData_Text, uint32_t MAX_CNT)
{
    R_SCE_Aes256EncryptDecryptUpdateSub(InData_Text, OutData_Text, MAX_CNT);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Encrypt data to cipher using AES ECB mode algorithm with AES 256 key.
 *
 * @param OutData_Text   Output cipher text.
 * @param OutData_length Output byte size of cipher.
 *
 * @retval FSP_SUCCESS             Normal termination.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL Internal error occurred.
 **********************************************************************************************************************/
fsp_err_t R_SCE_Aes256EcbEncryptFinalPrivate (uint32_t * OutData_Text, uint32_t * OutData_length)
{
    FSP_PARAMETER_NOT_USED(OutData_Text);
    FSP_PARAMETER_NOT_USED(OutData_length);

    return R_SCE_Aes256EncryptDecryptFinalSub();
}

/*******************************************************************************************************************//**
 * Decrypt data to plain using AES ECB mode algorithm with AES 256 key.
 *
 * @param InData_KeyIndex User key generation information area.
 *
 * @retval FSP_SUCCESS                          Normal termination.
 * @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      Input illegal user Key Generation Information
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT resource conflict
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              Internal error occurred.
 **********************************************************************************************************************/
fsp_err_t R_SCE_Aes256EcbDecryptInitPrivate (sce_aes_wrapped_key_t * InData_KeyIndex)
{
    uint32_t indata_keytype = 0; /* For normal */
    uint32_t indata_cmd   = 0;
    uint32_t indata_iv[4] =            /* dummy */
    {
        0
    };

    if ((SCE_KEY_INDEX_TYPE_AES256 != InData_KeyIndex->type) && (SCE_KEY_INDEX_TYPE_AES256_FOR_ECDH != InData_KeyIndex->type))
    {
        return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
    }
    indata_cmd = change_endian_long(1); /* ECB-Decrypt command */
    if (SCE_KEY_INDEX_TYPE_AES256_FOR_ECDH == InData_KeyIndex->type)
    {
        indata_keytype = change_endian_long(2); /* For ECDH */
    }
    return R_SCE_Aes256EncryptDecryptInitSub(&indata_keytype, &indata_cmd, InData_KeyIndex->value, indata_iv);
}

/*******************************************************************************************************************//**
 * Decrypt data to plain using AES ECB mode algorithm with AES 256 key.
 *
 * @param InData_Text  Input cipher text.
 * @param OutData_Text Output plain text.
 * @param MAX_CNT      Input byte size of cipher.
 *
 * @retval FSP_SUCCESS Normal termination.
 **********************************************************************************************************************/
fsp_err_t R_SCE_Aes256EcbDecryptUpdatePrivate (uint32_t * InData_Text, uint32_t * OutData_Text, uint32_t MAX_CNT)
{
    R_SCE_Aes256EncryptDecryptUpdateSub(InData_Text, OutData_Text, MAX_CNT);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Decrypt data to plain using AES ECB mode algorithm with AES 256 key.
 *
 * @param OutData_Text   Output plain text.
 * @param OutData_length Output byte size of plain.
 *
 * @retval FSP_SUCCESS             Normal termination.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL Internal error occurred.
 **********************************************************************************************************************/
fsp_err_t R_SCE_Aes256EcbDecryptFinalPrivate (uint32_t * OutData_Text, uint32_t * OutData_length)
{
    FSP_PARAMETER_NOT_USED(OutData_Text);
    FSP_PARAMETER_NOT_USED(OutData_length);

    return R_SCE_Aes256EncryptDecryptFinalSub();
}

/*******************************************************************************************************************//**
 * Encrypt data to cipher using AES CBC mode algorithm with AES 128 key.
 *
 * @param InData_KeyIndex User key generation information area.
 * @param InData_IV       Input initial vector.
 *
 * @retval FSP_SUCCESS                          Normal termination.
 * @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      Input illegal user Key Generation Information
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT resource conflict
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              Internal error occurred.
 **********************************************************************************************************************/
fsp_err_t R_SCE_Aes128CbcEncryptInitPrivate (sce_aes_wrapped_key_t * InData_KeyIndex, uint32_t * InData_IV)
{
    uint32_t indata_keytype = 0; /* For normal */
    uint32_t indata_cmd = 0;

    if ((SCE_KEY_INDEX_TYPE_AES128 != InData_KeyIndex->type) && ((SCE_KEY_INDEX_TYPE_AES128_FOR_TLS != InData_KeyIndex->type)
    && (SCE_KEY_INDEX_TYPE_AES128_FOR_ECDH != InData_KeyIndex->type)))
    {
        return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
    }
    if (SCE_KEY_INDEX_TYPE_AES128_FOR_TLS != InData_KeyIndex->type)
    {
        indata_cmd = change_endian_long(2); /* CBC-Encrypt command */
        if (SCE_KEY_INDEX_TYPE_AES128_FOR_ECDH == InData_KeyIndex->type)
        {
            indata_keytype = change_endian_long(2); /* For ECDH */
        }
    }
    else
    {
        indata_cmd = change_endian_long(5); /* CBC-Encrypt for TLS command */
    }
    return R_SCE_Aes128EncryptDecryptInitSub(&indata_keytype, &indata_cmd, InData_KeyIndex->value, InData_IV);
}

/*******************************************************************************************************************//**
 * Encrypt data to cipher using AES CBC mode algorithm with AES 128 key.
 *
 * @param InData_Text  Input plain text.
 * @param OutData_Text Output cipher text.
 * @param MAX_CNT      Input byte size of plain.
 *
 * @retval FSP_SUCCESS Normal termination.
 **********************************************************************************************************************/
fsp_err_t R_SCE_Aes128CbcEncryptUpdatePrivate (uint32_t * InData_Text, uint32_t * OutData_Text, uint32_t MAX_CNT)
{
    R_SCE_Aes128EncryptDecryptUpdateSub(InData_Text, OutData_Text, MAX_CNT);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Encrypt data to cipher using AES CBC mode algorithm with AES 128 key.
 *
 * @param OutData_Text   Output cipher text.
 * @param OutData_length Output byte size of cipher.
 *
 * @retval FSP_SUCCESS             Normal termination.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL Internal error occurred.
 **********************************************************************************************************************/
fsp_err_t R_SCE_Aes128CbcEncryptFinalPrivate (uint32_t * OutData_Text, uint32_t * OutData_length)
{
    FSP_PARAMETER_NOT_USED(OutData_Text);
    FSP_PARAMETER_NOT_USED(OutData_length);

    return R_SCE_Aes128EncryptDecryptFinalSub();
}

/*******************************************************************************************************************//**
 * Decrypt data to plain using AES CBC mode algorithm with AES 128 key.
 *
 * @param InData_KeyIndex User key generation information area.
 * @param InData_IV       Input initial vector.
 *
 * @retval FSP_SUCCESS                          Normal termination.
 * @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      Input illegal user Key Generation Information
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT resource conflict
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              Internal error occurred.
 **********************************************************************************************************************/
fsp_err_t R_SCE_Aes128CbcDecryptInitPrivate (sce_aes_wrapped_key_t * InData_KeyIndex, uint32_t * InData_IV)
{
    uint32_t indata_keytype = 0; /* For normal */
    uint32_t indata_cmd = 0;

    if ((SCE_KEY_INDEX_TYPE_AES128 != InData_KeyIndex->type) && ((SCE_KEY_INDEX_TYPE_AES128_FOR_TLS != InData_KeyIndex->type)
    && (SCE_KEY_INDEX_TYPE_AES128_FOR_ECDH != InData_KeyIndex->type)))
    {
        return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
    }
    if (SCE_KEY_INDEX_TYPE_AES128_FOR_TLS != InData_KeyIndex->type)
    {
        indata_cmd = change_endian_long(3); /* CBC-Decrypt command */
        if (SCE_KEY_INDEX_TYPE_AES128_FOR_ECDH == InData_KeyIndex->type)
        {
            indata_keytype = change_endian_long(2); /* For ECDH */
        }
    }
    else
    {
        indata_cmd = change_endian_long(6); /* CBC-Decrypt for TLS command */
    }
    return R_SCE_Aes128EncryptDecryptInitSub(&indata_keytype, &indata_cmd, InData_KeyIndex->value, InData_IV);
}

/*******************************************************************************************************************//**
 * Decrypt data to plain using AES CBC mode algorithm with AES 128 key.
 *
 * @param InData_Text  Input cipher text.
 * @param OutData_Text Output plain text.
 * @param MAX_CNT      Input byte size of cipher.
 *
 * @retval FSP_SUCCESS Normal termination.
 **********************************************************************************************************************/
fsp_err_t R_SCE_Aes128CbcDecryptUpdatePrivate (uint32_t * InData_Text, uint32_t * OutData_Text, uint32_t MAX_CNT)
{
    R_SCE_Aes128EncryptDecryptUpdateSub(InData_Text, OutData_Text, MAX_CNT);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Decrypt data to plain using AES CBC mode algorithm with AES 128 key.
 *
 * @param OutData_Text   Output plain text.
 * @param OutData_length Output byte size of plain.
 *
 * @retval FSP_SUCCESS             Normal termination.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL Internal error occurred.
 **********************************************************************************************************************/
fsp_err_t R_SCE_Aes128CbcDecryptFinalPrivate (uint32_t * OutData_Text, uint32_t * OutData_length)
{
    FSP_PARAMETER_NOT_USED(OutData_Text);
    FSP_PARAMETER_NOT_USED(OutData_length);

    return R_SCE_Aes128EncryptDecryptFinalSub();
}

/*******************************************************************************************************************//**
 * Encrypt data to cipher using AES CBC mode algorithm with AES 256 key.
 *
 * @param InData_KeyIndex User key generation information area.
 * @param InData_IV       Input initial vector.
 *
 * @retval FSP_SUCCESS                          Normal termination.
 * @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      Input illegal user Key Generation Information
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT resource conflict
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              Internal error occurred.
 **********************************************************************************************************************/
fsp_err_t R_SCE_Aes256CbcEncryptInitPrivate (sce_aes_wrapped_key_t * InData_KeyIndex, uint32_t * InData_IV)
{
    uint32_t indata_keytype = 0; /* For normal */
    uint32_t indata_cmd = 0;

    if ((SCE_KEY_INDEX_TYPE_AES256 != InData_KeyIndex->type) && ((SCE_KEY_INDEX_TYPE_AES256_FOR_TLS != InData_KeyIndex->type)
    && (SCE_KEY_INDEX_TYPE_AES256_FOR_ECDH != InData_KeyIndex->type)))
    {
        return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
    }
    if (SCE_KEY_INDEX_TYPE_AES256_FOR_TLS != InData_KeyIndex->type)
    {
        indata_cmd = change_endian_long(2); /* CBC-Encrypt command */
        if (SCE_KEY_INDEX_TYPE_AES256_FOR_ECDH == InData_KeyIndex->type)
        {
            indata_keytype = change_endian_long(2); /* For ECDH */
        }
    }
    else
    {
        indata_cmd = change_endian_long(5); /* CBC-Encrypt for TLS command */
    }
    return R_SCE_Aes256EncryptDecryptInitSub(&indata_keytype, &indata_cmd, InData_KeyIndex->value, InData_IV);
}

/*******************************************************************************************************************//**
 * Encrypt data to cipher using AES CBC mode algorithm with AES 256 key.
 *
 * @param InData_Text  Input plain text.
 * @param OutData_Text Output cipher text.
 * @param MAX_CNT      Input byte size of plain.
 *
 * @retval FSP_SUCCESS Normal termination.
 **********************************************************************************************************************/
fsp_err_t R_SCE_Aes256CbcEncryptUpdatePrivate (uint32_t * InData_Text, uint32_t * OutData_Text, uint32_t MAX_CNT)
{
    R_SCE_Aes256EncryptDecryptUpdateSub(InData_Text, OutData_Text, MAX_CNT);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Encrypt data to cipher using AES CBC mode algorithm with AES 256 key.
 *
 * @param OutData_Text   Output cipher text.
 * @param OutData_length Output byte size of cipher.
 *
 * @retval FSP_SUCCESS             Normal termination.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL Internal error occurred.
 **********************************************************************************************************************/
fsp_err_t R_SCE_Aes256CbcEncryptFinalPrivate (uint32_t * OutData_Text, uint32_t * OutData_length)
{
    FSP_PARAMETER_NOT_USED(OutData_Text);
    FSP_PARAMETER_NOT_USED(OutData_length);

    return R_SCE_Aes256EncryptDecryptFinalSub();
}

/*******************************************************************************************************************//**
 * Decrypt data to plain using AES CBC mode algorithm with AES 256 key.
 *
 * @param InData_KeyIndex User key generation information area.
 * @param InData_IV       Input initial vector.
 *
 * @retval FSP_SUCCESS                          Normal termination.
 * @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      Input illegal user Key Generation Information
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT resource conflict
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              Internal error occurred.
 **********************************************************************************************************************/
fsp_err_t R_SCE_Aes256CbcDecryptInitPrivate (sce_aes_wrapped_key_t * InData_KeyIndex, uint32_t * InData_IV)
{
    uint32_t indata_keytype = 0; /* For normal */
    uint32_t indata_cmd = 0;

    if ((SCE_KEY_INDEX_TYPE_AES256 != InData_KeyIndex->type) && ((SCE_KEY_INDEX_TYPE_AES256_FOR_TLS != InData_KeyIndex->type)
    && (SCE_KEY_INDEX_TYPE_AES256_FOR_ECDH != InData_KeyIndex->type)))
    {
        return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
    }
    if (SCE_KEY_INDEX_TYPE_AES256_FOR_TLS != InData_KeyIndex->type)
    {
        indata_cmd = change_endian_long(3); /* CBC-Decrypt command */
        if (SCE_KEY_INDEX_TYPE_AES256_FOR_ECDH == InData_KeyIndex->type)
        {
            indata_keytype = change_endian_long(2); /* For ECDH */
        }
    }
    else
    {
        indata_cmd = change_endian_long(6); /* CBC-Decrypt for TLS command */
    }
    return R_SCE_Aes256EncryptDecryptInitSub(&indata_keytype, &indata_cmd, InData_KeyIndex->value, InData_IV);
}

/*******************************************************************************************************************//**
 * Decrypt data to plain using AES CBC mode algorithm with AES 256 key.
 *
 * @param InData_Text  Input cipher text.
 * @param OutData_Text Output plain text.
 * @param MAX_CNT      Input byte size of cipher.
 *
 * @retval FSP_SUCCESS Normal termination.
 **********************************************************************************************************************/
fsp_err_t R_SCE_Aes256CbcDecryptUpdatePrivate (uint32_t * InData_Text, uint32_t * OutData_Text, uint32_t MAX_CNT)
{
    R_SCE_Aes256EncryptDecryptUpdateSub(InData_Text, OutData_Text, MAX_CNT);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Decrypt data to plain using AES CBC mode algorithm with AES 256 key.
 *
 * @param OutData_Text   Output plain text.
 * @param OutData_length Output byte size of plain.
 *
 * @retval FSP_SUCCESS             Normal termination.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL Internal error occurred.
 **********************************************************************************************************************/
fsp_err_t R_SCE_Aes256CbcDecryptFinalPrivate (uint32_t * OutData_Text, uint32_t * OutData_length)
{
    FSP_PARAMETER_NOT_USED(OutData_Text);
    FSP_PARAMETER_NOT_USED(OutData_length);

    return R_SCE_Aes256EncryptDecryptFinalSub();
}

/*******************************************************************************************************************//**
 * Encrypt data to cipher using AES GCM algorithm with AES 128 key.
 *
 * @param InData_KeyIndex User key generation information area.
 * @param InData_IV       Input initial vector.
 *
 * @retval FSP_SUCCESS                          Normal termination.
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT resource conflict
 * @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      Input illegal user Key Generation Information
 **********************************************************************************************************************/
fsp_err_t R_SCE_Aes128GcmEncryptInitPrivate (sce_aes_wrapped_key_t * InData_KeyIndex, uint32_t * InData_IV)
{
    uint32_t indata_cmd = 0;

    if (SCE_KEY_INDEX_TYPE_AES128 == InData_KeyIndex->type)
    {
        indata_cmd = change_endian_long(0); /* GCM-Encrypt command */
    }
    if (SCE_KEY_INDEX_TYPE_AES128_FOR_TLS == InData_KeyIndex->type)
    {
        indata_cmd = change_endian_long(1); /* For TLS */
    }
    if (SCE_KEY_INDEX_TYPE_AES128_FOR_ECDH == InData_KeyIndex->type)
    {
        indata_cmd = change_endian_long(2); /* For ECDH */
    }

    return R_SCE_Aes128GcmEncryptInitSub(&indata_cmd, InData_KeyIndex->value, InData_IV);
}

/*******************************************************************************************************************//**
 * Encrypt data to cipher using AES GCM algorithm with AES 128 key for additional authentication data.
 *
 * @param InData_DataA Input additional authentication data.
 * @param MAX_CNT      Input additional authenticated data byte size.
 *
 * @retval FSP_SUCCESS Normal termination.
 **********************************************************************************************************************/
fsp_err_t R_SCE_Aes128GcmEncryptUpdateAadPrivate (uint32_t * InData_DataA, uint32_t MAX_CNT)
{
    R_SCE_Aes128GcmEncryptUpdateAADSub(InData_DataA, MAX_CNT);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Encrypt data to cipher using AES GCM algorithm with AES 128 key.
 *
 * @param InData_Text  Input plain text.
 * @param MAX_CNT      Input byte size of plain.
 * @param OutData_Text Output cipher text.
 *
 * @retval FSP_SUCCESS Normal termination.
 **********************************************************************************************************************/
fsp_err_t R_SCE_Aes128GcmEncryptUpdatePrivate (uint32_t * InData_Text, uint32_t MAX_CNT, uint32_t * OutData_Text)
{
    R_SCE_Aes128GcmEncryptUpdateSub(InData_Text, OutData_Text, MAX_CNT);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Encrypt data to cipher using AES GCM algorithm with AES 128 key.
 *
 * @param InData_Text     Input plain text.
 * @param InData_DataALen Input byte size of additional authentication data.
 * @param InData_TextLen  Input byte size of plain.
 * @param OutData_Text    Output cipher text.
 * @param OutData_DataT   Output atag.
 *
 * @retval FSP_SUCCESS             Normal termination.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL Internal error occurred.
 **********************************************************************************************************************/
fsp_err_t R_SCE_Aes128GcmEncryptFinalPrivate (uint32_t * InData_Text,
                                               uint32_t * InData_DataALen,
                                               uint32_t * InData_TextLen,
                                               uint32_t * OutData_Text,
                                               uint32_t * OutData_DataT)
{
    return R_SCE_Aes128GcmEncryptFinalSub(InData_Text, InData_DataALen, InData_TextLen, OutData_Text, OutData_DataT);
}

/*******************************************************************************************************************//**
 * Decrypt data to plain using AES GCM algorithm with AES 128 key.
 *
 * @param InData_KeyIndex User key generation information area.
 * @param InData_IV       Input initial vector.
 *
 * @retval FSP_SUCCESS                          Normal termination.
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT resource conflict
 * @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      Input illegal user Key Generation Information
 **********************************************************************************************************************/
fsp_err_t R_SCE_Aes128GcmDecryptInitPrivate (sce_aes_wrapped_key_t * InData_KeyIndex, uint32_t * InData_IV)
{
    uint32_t indata_cmd = 0; /* For normal */

    if (SCE_KEY_INDEX_TYPE_AES128 == InData_KeyIndex->type)
    {
        indata_cmd = change_endian_long(0); /* GCM-Encrypt command */
    }
    if (SCE_KEY_INDEX_TYPE_AES128_FOR_TLS == InData_KeyIndex->type)
    {
        indata_cmd = change_endian_long(1); /* For TLS */
    }
    if (SCE_KEY_INDEX_TYPE_AES128_FOR_ECDH == InData_KeyIndex->type)
    {
        indata_cmd = change_endian_long(2); /* For ECDH */
    }
    if (SCE_KEY_INDEX_TYPE_AES128_GCM_WITH_IV == InData_KeyIndex->type)
    {
        indata_cmd = change_endian_long(3);
    }
    return R_SCE_Aes128GcmDecryptInitSub(&indata_cmd, InData_KeyIndex->value, InData_IV);
}

/*******************************************************************************************************************//**
 * Decrypt data to plain using AES GCM algorithm with AES 128 key for additional authentication data.
 *
 * @param InData_DataA Input additional authentication data.
 * @param MAX_CNT      Input additional authenticated data byte size.
 *
 * @retval FSP_SUCCESS                          Normal termination.
 **********************************************************************************************************************/
fsp_err_t R_SCE_Aes128GcmDecryptUpdateAadPrivate (uint32_t * InData_DataA, uint32_t MAX_CNT)
{
    R_SCE_Aes128GcmDecryptUpdateAADSub(InData_DataA, MAX_CNT);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Decrypt data to plain using AES GCM algorithm with AES 128 key.
 *
 * @param InData_Text  Input cipher text.
 * @param MAX_CNT      Input byte size of cipher.
 * @param OutData_Text Output plain text.
 *
 * @retval FSP_SUCCESS Normal termination.
 **********************************************************************************************************************/
fsp_err_t R_SCE_Aes128GcmDecryptUpdatePrivate (uint32_t * InData_Text, uint32_t MAX_CNT, uint32_t * OutData_Text)
{
    R_SCE_Aes128GcmDecryptUpdateSub(InData_Text, OutData_Text, MAX_CNT);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Decrypt data to plain using AES GCM algorithm with AES 128 key.
 *
 * @param InData_Text     Input plain text.
 * @param InData_DataT    Input atag.
 * @param InData_DataALen Input byte size of additional authentication data.
 * @param InData_TextLen  Input byte size of cipher.
 * @param InData_DataTLen Input byte size of atag.
 * @param OutData_Text    Output plain text.
 *
 * @retval FSP_SUCCESS                       Normal termination.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL           Internal error occurred.
 * @retval FSP_ERR_CRYPTO_SCE_AUTHENTICATION Authentication NG
 **********************************************************************************************************************/
fsp_err_t R_SCE_Aes128GcmDecryptFinalPrivate (uint32_t * InData_Text,
                                               uint32_t * InData_DataT,
                                               uint32_t * InData_DataALen,
                                               uint32_t * InData_TextLen,
                                               uint32_t * InData_DataTLen,
                                               uint32_t * OutData_Text)
{
    return R_SCE_Aes128GcmDecryptFinalSub(InData_Text,
                                           InData_DataT,
                                           InData_DataALen,
                                           InData_TextLen,
                                           InData_DataTLen,
                                           OutData_Text);
}

/*******************************************************************************************************************//**
 * Encrypt data to cipher using AES GCM mode algorithm with AES 256 key.
 *
 * @param InData_KeyIndex User key generation information area.
 * @param InData_IV       Input initial vector.
 *
 * @retval FSP_SUCCESS                          Normal termination.
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT resource conflict
 * @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      Input illegal user Key Generation Information
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              Internal error occurred.
 **********************************************************************************************************************/
fsp_err_t R_SCE_Aes256GcmEncryptInitPrivate (sce_aes_wrapped_key_t * InData_KeyIndex, uint32_t * InData_IV)
{
    uint32_t indata_keytype = 0; /* For normal */

    if (SCE_KEY_INDEX_TYPE_AES256_FOR_ECDH == InData_KeyIndex->type)
    {
        indata_keytype = change_endian_long(2); /* For ECDH */
    }
    return R_SCE_Aes256GcmEncryptInitSub(&indata_keytype, InData_KeyIndex->value, InData_IV);
}

/*******************************************************************************************************************//**
 * Encrypt data to cipher using AES GCM algorithm with AES 256 key for additional authentication data.
 *
 * @param InData_DataA Input additional authentication data.
 * @param MAX_CNT      Input additional authenticated data byte size.
 *
 * @retval FSP_SUCCESS                          Normal termination.
 **********************************************************************************************************************/
fsp_err_t R_SCE_Aes256GcmEncryptUpdateAadPrivate (uint32_t * InData_DataA, uint32_t MAX_CNT)
{
    R_SCE_Aes256GcmEncryptUpdateAADSub(InData_DataA, MAX_CNT);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Encrypt data to cipher using AES GCM algorithm with AES 256 key.
 *
 * @param InData_Text  Input plain text.
 * @param MAX_CNT      Input byte size of plain.
 * @param OutData_Text Output cipher text.
 *
 * @retval FSP_SUCCESS Normal termination.
 **********************************************************************************************************************/
fsp_err_t R_SCE_Aes256GcmEncryptUpdatePrivate (uint32_t * InData_Text, uint32_t MAX_CNT, uint32_t * OutData_Text)
{
    R_SCE_Aes256GcmEncryptUpdateSub(InData_Text, OutData_Text, MAX_CNT);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Encrypt data to cipher using AES GCM algorithm with AES 256 key.
 *
 * @param InData_Text     Input plain text.
 * @param InData_DataALen Input byte size of additional authentication data.
 * @param InData_TextLen  Input byte size of plain.
 * @param OutData_Text    Output cipher text.
 * @param OutData_DataT   Output atag.
 *
 * @retval FSP_SUCCESS             Normal termination.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL Internal error occurred.
 **********************************************************************************************************************/
fsp_err_t R_SCE_Aes256GcmEncryptFinalPrivate (uint32_t * InData_Text,
                                               uint32_t * InData_DataALen,
                                               uint32_t * InData_TextLen,
                                               uint32_t * OutData_Text,
                                               uint32_t * OutData_DataT)
{
    return R_SCE_Aes256GcmEncryptFinalSub(InData_Text, InData_DataALen, InData_TextLen, OutData_Text, OutData_DataT);
}

/*******************************************************************************************************************//**
 * Decrypt data to plain using AES GCM algorithm with AES 256 key.
 *
 * @param InData_KeyIndex User key generation information area.
 * @param InData_IV       Input initial vector.
 *
 * @retval FSP_SUCCESS                          Normal termination.
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT resource conflict
 * @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      Input illegal user Key Generation Information
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              Internal error occurred.
 **********************************************************************************************************************/
fsp_err_t R_SCE_Aes256GcmDecryptInitPrivate (sce_aes_wrapped_key_t * InData_KeyIndex, uint32_t * InData_IV)
{
    uint32_t indata_keytype = 0; /* For normal */

    if (SCE_KEY_INDEX_TYPE_AES256_FOR_ECDH == InData_KeyIndex->type)
    {
        indata_keytype = change_endian_long(2); /* For ECDH */
    }
    return R_SCE_Aes256GcmDecryptInitSub(&indata_keytype, InData_KeyIndex->value, InData_IV);
}

/*******************************************************************************************************************//**
 * Decrypt data to plain using AES GCM algorithm with AES 256 key for additional authentication data.
 *
 * @param InData_DataA Input additional authentication data.
 * @param MAX_CNT      Input additional authenticated data byte size.
 *
 * @retval FSP_SUCCESS                          Normal termination.
 **********************************************************************************************************************/
fsp_err_t R_SCE_Aes256GcmDecryptUpdateAadPrivate (uint32_t * InData_DataA, uint32_t MAX_CNT)
{
    R_SCE_Aes256GcmDecryptUpdateAADSub(InData_DataA, MAX_CNT);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Decrypt data to plain using AES GCM algorithm with AES 256 key.
 *
 * @param InData_Text  Input cipher text.
 * @param MAX_CNT      Input byte size of cipher.
 * @param OutData_Text Output plain text.
 *
 * @retval FSP_SUCCESS Normal termination.
 **********************************************************************************************************************/
fsp_err_t R_SCE_Aes256GcmDecryptUpdatePrivate (uint32_t * InData_Text, uint32_t MAX_CNT, uint32_t * OutData_Text)
{
    R_SCE_Aes256GcmDecryptUpdateSub(InData_Text, OutData_Text, MAX_CNT);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Decrypt data to plain using AES GCM algorithm with AES 256 key.
 *
 * @param InData_Text     Input plain text.
 * @param InData_DataT    Input atag.
 * @param InData_DataALen Input byte size of additional authentication data.
 * @param InData_TextLen  Input byte size of cipher.
 * @param InData_DataTLen Input byte size of atag.
 * @param OutData_Text    Output plain text.
 *
 * @retval FSP_SUCCESS                       Normal termination.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL           Internal error occurred.
 * @retval FSP_ERR_CRYPTO_SCE_AUTHENTICATION Authentication NG
 **********************************************************************************************************************/
fsp_err_t R_SCE_Aes256GcmDecryptFinalPrivate (uint32_t * InData_Text,
                                               uint32_t * InData_DataT,
                                               uint32_t * InData_DataALen,
                                               uint32_t * InData_TextLen,
                                               uint32_t * InData_DataTLen,
                                               uint32_t * OutData_Text)
{
    return R_SCE_Aes256GcmDecryptFinalSub(InData_Text,
                                           InData_DataT,
                                           InData_DataALen,
                                           InData_TextLen,
                                           InData_DataTLen,
                                           OutData_Text);
}

/*******************************************************************************************************************//**
 * Transition SCE mode for encrypt data using AES128 GCM algorithm.
 **********************************************************************************************************************/
void R_SCE_Aes128GcmEncryptUpdateTransitionPrivate (void)
{
    R_SCE_Aes128GcmEncryptUpdateTransitionSub();
}

/*******************************************************************************************************************//**
 * Transition SCE mode for decrypt data using AES128 GCM algorithm.
 **********************************************************************************************************************/
void R_SCE_Aes128GcmDecryptUpdateTransitionPrivate (void)
{
    R_SCE_Aes128GcmDecryptUpdateTransitionSub();
}

/*******************************************************************************************************************//**
 * Transition SCE mode for encrypt data using AES256 GCM algorithm.
 **********************************************************************************************************************/
void R_SCE_Aes256GcmEncryptUpdateTransitionPrivate (void)
{
    R_SCE_Aes256GcmEncryptUpdateTransitionSub();
}

/*******************************************************************************************************************//**
 * Transition SCE mode for decrypt data using AES256 GCM algorithm.
 **********************************************************************************************************************/
void R_SCE_Aes256GcmDecryptUpdateTransitionPrivate (void)
{
    R_SCE_Aes256GcmDecryptUpdateTransitionSub();
}

/*******************************************************************************************************************//**
 * Encrypt data to cipher using AES CCM algorithm with AES 128 key.
 *
 * @param InData_KeyIndex User key generation information area.
 * @param InData_IV       Input initial vector.
 * @param InData_Header   Formatted data area.
 * @param Header_Len      Formatted data length.
 *
 * @retval FSP_SUCCESS                          Normal termination.
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT resource conflict
 * @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      Input illegal user Key Generation Information
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              Internal error occurred.
 **********************************************************************************************************************/
fsp_err_t R_SCE_Aes128CcmEncryptInitPrivate (sce_aes_wrapped_key_t * InData_KeyIndex,
                                              uint32_t              * InData_IV,
                                              uint32_t              * InData_Header,
                                              uint32_t                Header_Len)
{
    uint32_t indata_keytype = 0; /* For normal */

    if (SCE_KEY_INDEX_TYPE_AES128_FOR_ECDH == InData_KeyIndex->type)
    {
        indata_keytype = change_endian_long(2); /* For ECDH */
    }
    return R_SCE_Aes128CcmEncryptInitSub(&indata_keytype, InData_KeyIndex->value, InData_IV, InData_Header, Header_Len);
}

/*******************************************************************************************************************//**
 * Encrypt data to cipher using AES CCM algorithm with AES 128 key.
 *
 * @param InData_Text  Input plain text.
 * @param OutData_Text Output cipher text.
 * @param MAX_CNT      Input byte size of plain.
 *
 * @retval FSP_SUCCESS Normal termination.
 **********************************************************************************************************************/
fsp_err_t R_SCE_Aes128CcmEncryptUpdatePrivate (uint32_t * InData_Text, uint32_t * OutData_Text, uint32_t MAX_CNT)
{
    R_SCE_Aes128CcmEncryptUpdateSub(InData_Text, OutData_Text, MAX_CNT);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Encrypt data to cipher using AES CCM algorithm with AES 128 key.
 *
 * @param InData_TextLen Input byte size of plain.
 * @param InData_Text    Input plain text.
 * @param OutData_Text   Output cipher text.
 * @param OutData_MAC    Output MAC data.
 *
 * @retval FSP_SUCCESS             Normal termination.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL Internal error occurred.
 **********************************************************************************************************************/
fsp_err_t R_SCE_Aes128CcmEncryptFinalPrivate (uint32_t * InData_TextLen,
                                               uint32_t * InData_Text,
                                               uint32_t * OutData_Text,
                                               uint32_t * OutData_MAC)
{
    return R_SCE_Aes128CcmEncryptFinalSub(InData_TextLen, InData_Text, OutData_Text, OutData_MAC);
}

/*******************************************************************************************************************//**
 * Decrypt data to plain using AES CCM algorithm with AES 128 key.
 *
 * @param InData_KeyIndex User key generation information area.
 * @param InData_IV       Input initial vector.
 * @param InData_Header   Formatted data area.
 * @param Header_Len      Formatted data length.
 *
 * @retval FSP_SUCCESS                          Normal termination.
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT resource conflict
 * @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      Input illegal user Key Generation Information
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              Internal error occurred.
 **********************************************************************************************************************/
fsp_err_t R_SCE_Aes128CcmDecryptInitPrivate (sce_aes_wrapped_key_t * InData_KeyIndex,
                                              uint32_t              * InData_IV,
                                              uint32_t              * InData_Header,
                                              uint32_t                Header_Len)
{
    uint32_t indata_keytype = 0; /* For normal */

    if (SCE_KEY_INDEX_TYPE_AES128_FOR_ECDH == InData_KeyIndex->type)
    {
        indata_keytype = change_endian_long(2); /* For ECDH */
    }
    return R_SCE_Aes128CcmDecryptInitSub(&indata_keytype, InData_KeyIndex->value, InData_IV, InData_Header, Header_Len);
}

/*******************************************************************************************************************//**
 * Decrypt data to plain using AES CCM algorithm with AES 128 key.
 *
 * @param InData_Text  Input cipher text.
 * @param OutData_Text Output plain text.
 * @param MAX_CNT      Input byte size of cipher.
 *
 * @retval FSP_SUCCESS Normal termination.
 **********************************************************************************************************************/
fsp_err_t R_SCE_Aes128CcmDecryptUpdatePrivate (uint32_t * InData_Text, uint32_t * OutData_Text, uint32_t MAX_CNT)
{
    R_SCE_Aes128CcmDecryptUpdateSub(InData_Text, OutData_Text, MAX_CNT);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Decrypt data to plain using AES CCM algorithm with AES 128 key.
 *
 * @param InData_Text     Input cipher text.
 * @param InData_TextLen  Input byte size of cipher.
 * @param InData_MAC      Input MAC data.
 * @param InData_MACLength Input byte size of MAC data.
 * @param OutData_Text    Output plain text.
 *
 * @retval FSP_SUCCESS             Normal termination.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL Internal error occurred.
 **********************************************************************************************************************/
fsp_err_t R_SCE_Aes128CcmDecryptFinalPrivate (uint32_t * InData_Text,
                                               uint32_t * InData_TextLen,
                                               uint32_t * InData_MAC,
                                               uint32_t * InData_MACLength,
                                               uint32_t * OutData_Text)
{
    return R_SCE_Aes128CcmDecryptFinalSub(InData_Text, InData_TextLen, InData_MAC, InData_MACLength, OutData_Text);
}

/*******************************************************************************************************************//**
 * Encrypt data to cipher using AES CCM algorithm with AES 256 key.
 *
 * @param InData_KeyIndex User key generation information area.
 * @param InData_IV       Input initial vector.
 * @param InData_Header   Formatted data area.
 * @param Header_Len      Formatted data length.
 *
 * @retval FSP_SUCCESS                          Normal termination.
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT resource conflict
 * @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      Input illegal user Key Generation Information
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              Internal error occurred.
 **********************************************************************************************************************/
fsp_err_t R_SCE_Aes256CcmEncryptInitPrivate (sce_aes_wrapped_key_t * InData_KeyIndex,
                                              uint32_t              * InData_IV,
                                              uint32_t              * InData_Header,
                                              uint32_t                Header_Len)
{
    uint32_t indata_keytype = 0; /* For normal */

    if (SCE_KEY_INDEX_TYPE_AES256_FOR_ECDH == InData_KeyIndex->type)
    {
        indata_keytype = change_endian_long(2); /* For ECDH */
    }
    return R_SCE_Aes256CcmEncryptInitSub(&indata_keytype, InData_KeyIndex->value, InData_IV, InData_Header, Header_Len);
}

/*******************************************************************************************************************//**
 * Encrypt data to cipher using AES CCM algorithm with AES 256 key.
 *
 * @param InData_Text  Input plain text.
 * @param OutData_Text Output cipher text.
 * @param MAX_CNT      Input byte size of plain.
 *
 * @retval FSP_SUCCESS Normal termination.
 **********************************************************************************************************************/
fsp_err_t R_SCE_Aes256CcmEncryptUpdatePrivate (uint32_t * InData_Text, uint32_t * OutData_Text, uint32_t MAX_CNT)
{
    R_SCE_Aes256CcmEncryptUpdateSub(InData_Text, OutData_Text, MAX_CNT);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Encrypt data to cipher using AES CCM algorithm with AES 256 key.
 *
 * @param InData_TextLen Input byte size of plain.
 * @param InData_Text    Input plain text.
 * @param OutData_Text   Output cipher text.
 * @param OutData_MAC    Output MAC data.
 *
 * @retval FSP_SUCCESS             Normal termination.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL Internal error occurred.
 **********************************************************************************************************************/
fsp_err_t R_SCE_Aes256CcmEncryptFinalPrivate (uint32_t * InData_TextLen,
                                               uint32_t * InData_Text,
                                               uint32_t * OutData_Text,
                                               uint32_t * OutData_MAC)
{
    return R_SCE_Aes256CcmEncryptFinalSub(InData_TextLen, InData_Text, OutData_Text, OutData_MAC);
}

/*******************************************************************************************************************//**
 * Decrypt data to plain using AES CCM algorithm with AES 256 key.
 *
 * @param InData_KeyIndex User key generation information area.
 * @param InData_IV       Input initial vector.
 * @param InData_Header   Formatted data area.
 * @param Header_Len      Formatted data length.
 *
 * @retval FSP_SUCCESS                          Normal termination.
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT resource conflict
 * @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      Input illegal user Key Generation Information
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              Internal error occurred.
 **********************************************************************************************************************/
fsp_err_t R_SCE_Aes256CcmDecryptInitPrivate (sce_aes_wrapped_key_t * InData_KeyIndex,
                                              uint32_t              * InData_IV,
                                              uint32_t              * InData_Header,
                                              uint32_t                Header_Len)
{
    uint32_t indata_keytype = 0; /* For normal */

    if (SCE_KEY_INDEX_TYPE_AES256_FOR_ECDH == InData_KeyIndex->type)
    {
        indata_keytype = change_endian_long(2); /* For ECDH */
    }
    return R_SCE_Aes256CcmDecryptInitSub(&indata_keytype, InData_KeyIndex->value, InData_IV, InData_Header, Header_Len);
}

/*******************************************************************************************************************//**
 * Decrypt data to plain using AES CCM algorithm with AES 256 key.
 *
 * @param InData_Text  Input cipher text.
 * @param OutData_Text Output plain text.
 * @param MAX_CNT      Input byte size of cipher.
 *
 * @retval FSP_SUCCESS Normal termination.
 **********************************************************************************************************************/
fsp_err_t R_SCE_Aes256CcmDecryptUpdatePrivate (uint32_t * InData_Text, uint32_t * OutData_Text, uint32_t MAX_CNT)
{
    R_SCE_Aes256CcmDecryptUpdateSub(InData_Text, OutData_Text, MAX_CNT);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Decrypt data to plain using AES CCM algorithm with AES 256 key.
 *
 * @param InData_Text     Input cipher text.
 * @param InData_TextLen  Input byte size of cipher.
 * @param InData_MAC      Input MAC data.
 * @param InData_MACLength Input byte size of MAC data.
 * @param OutData_Text    Output plain text.
 *
 * @retval FSP_SUCCESS             Normal termination.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL Internal error occurred.
 **********************************************************************************************************************/
fsp_err_t R_SCE_Aes256CcmDecryptFinalPrivate (uint32_t * InData_Text,
                                               uint32_t * InData_TextLen,
                                               uint32_t * InData_MAC,
                                               uint32_t * InData_MACLength,
                                               uint32_t * OutData_Text)
{
    return R_SCE_Aes256CcmDecryptFinalSub(InData_Text, InData_TextLen, InData_MAC, InData_MACLength, OutData_Text);
}

/*******************************************************************************************************************//**
 * Prepare to execute AES calculation.
 *
 * @param InData_KeyIndex User key generation information area
 *
 * @retval FSP_SUCCESS                          Normal termination.
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT resource conflict
 * @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      Input illegal user Key Generation Information
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              Internal error occurred.
 **********************************************************************************************************************/
fsp_err_t R_SCE_Aes128CmacGenerateInitPrivate (sce_aes_wrapped_key_t * InData_KeyIndex)
{
    uint32_t indata_keytype = 0; /* For normal */

    if (SCE_KEY_INDEX_TYPE_AES128_FOR_ECDH == InData_KeyIndex->type)
    {
        indata_keytype = change_endian_long(2); /* For ECDH */
    }
    return R_SCE_Aes128CmacInitSub(&indata_keytype, InData_KeyIndex->value);
}

/*******************************************************************************************************************//**
 * Generates a MAC value from the message specified.
 *
 * @param InData_Text Message data area (data_len byte)
 * @param MAX_CNT     Message data length (0 to arbitrary byte)
 *
 * @retval FSP_SUCCESS Normal termination.
 **********************************************************************************************************************/
fsp_err_t R_SCE_Aes128CmacGenerateUpdatePrivate (uint32_t * InData_Text, uint32_t MAX_CNT)
{
    R_SCE_Aes128CmacUpdateSub(InData_Text, MAX_CNT);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Outputs the Mac value.
 *
 * @param All_Msg_Len   Input byte size of message data.
 * @param InData_Text   Input message data.
 * @param OutData_DataT MAC data area (data_len byte)
 *
 * @retval FSP_SUCCESS                       Normal termination.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL           Internal error occurred.
 * @retval FSP_ERR_CRYPTO_SCE_AUTHENTICATION Reserved.
 **********************************************************************************************************************/
fsp_err_t R_SCE_Aes128CmacGenerateFinalPrivate (uint32_t All_Msg_Len, uint32_t * InData_Text, uint32_t * OutData_DataT)
{
    uint32_t indata_cmd      = 0;
    uint32_t indata_datat[4] =         /* dummy */
    {
        0
    };
    uint32_t indata_datat_len = 0;     /* dummy */

    if ((0 == (All_Msg_Len % 16)) && (0 != All_Msg_Len))
    {
        indata_cmd = 0;
    }
    else
    {
        indata_cmd = 1;
    }

    return R_SCE_Aes128CmacFinalSub(&indata_cmd, InData_Text, indata_datat, &indata_datat_len, OutData_DataT);
}

/*******************************************************************************************************************//**
 * Prepare to execute CMAC calculation.
 *
 * @param InData_KeyIndex User key generation information area
 *
 * @retval FSP_SUCCESS                          Normal termination.
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT resource conflict
 * @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      Input illegal user Key Generation Information
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              Internal error occurred.
 **********************************************************************************************************************/
fsp_err_t R_SCE_Aes128CmacVerifyInitPrivate (sce_aes_wrapped_key_t * InData_KeyIndex)
{
    uint32_t indata_keytype = 0; /* For normal */

    if (SCE_KEY_INDEX_TYPE_AES128_FOR_ECDH == InData_KeyIndex->type)
    {
        indata_keytype = change_endian_long(2); /* For ECDH */
    }
    return R_SCE_Aes128CmacInitSub(&indata_keytype, InData_KeyIndex->value);
}

/*******************************************************************************************************************//**
 * Verifies the MAC value.
 *
 * @param InData_Text Message data area (data_len byte)
 * @param MAX_CNT     Message data length (0 to arbitrary byte)
 *
 * @retval FSP_SUCCESS Normal termination.
 **********************************************************************************************************************/
fsp_err_t R_SCE_Aes128CmacVerifyUpdatePrivate (uint32_t * InData_Text, uint32_t MAX_CNT)
{
    R_SCE_Aes128CmacUpdateSub(InData_Text, MAX_CNT);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Validates the Mac value.
 *
 * @param All_Msg_Len     Input byte size of message data.
 * @param InData_Text     Input message data.
 * @param InData_DataT    MAC data area (data_len byte)
 * @param InData_DataTLen MAC data length
 *
 * @retval FSP_SUCCESS                       Normal termination.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL           Internal error occurred.
 * @retval FSP_ERR_CRYPTO_SCE_AUTHENTICATION Authentication NG
 **********************************************************************************************************************/
fsp_err_t R_SCE_Aes128CmacVerifyFinalPrivate (uint32_t   All_Msg_Len,
                                               uint32_t * InData_Text,
                                               uint32_t * InData_DataT,
                                               uint32_t * InData_DataTLen)
{
    uint32_t indata_cmd  = 0;
    uint32_t out_data[4] =
    {
        0
    };

    if ((0 == (All_Msg_Len % 16)) && (0 != All_Msg_Len))
    {
        indata_cmd = 2;
    }
    else
    {
        indata_cmd = 3;
    }

    return R_SCE_Aes128CmacFinalSub(&indata_cmd, InData_Text, InData_DataT, InData_DataTLen, out_data);
}

/*******************************************************************************************************************//**
 * Prepare to execute AES calculation.
 *
 * @param InData_KeyIndex User key generation information area
 *
 * @retval FSP_SUCCESS                          Normal termination.
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT resource conflict
 * @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      Input illegal user Key Generation Information
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              Internal error occurred.
 **********************************************************************************************************************/
fsp_err_t R_SCE_Aes256CmacGenerateInitPrivate (sce_aes_wrapped_key_t * InData_KeyIndex)
{
    uint32_t indata_keytype = 0; /* For normal */

    if (SCE_KEY_INDEX_TYPE_AES256_FOR_ECDH == InData_KeyIndex->type)
    {
        indata_keytype = change_endian_long(2); /* For ECDH */
    }
    return R_SCE_Aes256CmacInitSub(&indata_keytype, InData_KeyIndex->value);
}

/*******************************************************************************************************************//**
 * Generates a MAC value from the message specified.
 *
 * @param InData_Text Message data area (data_len byte)
 * @param MAX_CNT     Message data length (0 to arbitrary byte)
 *
 * @retval FSP_SUCCESS Normal termination.
 **********************************************************************************************************************/
fsp_err_t R_SCE_Aes256CmacGenerateUpdatePrivate (uint32_t * InData_Text, uint32_t MAX_CNT)
{
    R_SCE_Aes256CmacUpdateSub(InData_Text, MAX_CNT);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Outputs the Mac value.
 *
 * @param All_Msg_Len   Input byte size of message data.
 * @param InData_Text   Input message data.
 * @param OutData_DataT MAC data area (data_len byte)
 *
 * @retval FSP_SUCCESS                       Normal termination.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL           Internal error occurred.
 * @retval FSP_ERR_CRYPTO_SCE_AUTHENTICATION Reserved.
 **********************************************************************************************************************/
fsp_err_t R_SCE_Aes256CmacGenerateFinalPrivate (uint32_t All_Msg_Len, uint32_t * InData_Text, uint32_t * OutData_DataT)
{
    uint32_t indata_cmd      = 0;
    uint32_t indata_datat[4] =         /* dummy */
    {
        0
    };
    uint32_t indata_datat_len = 0;     /* dummy */

    if ((0 == (All_Msg_Len % 16)) && (0 != All_Msg_Len))
    {
        indata_cmd = 0;
    }
    else
    {
        indata_cmd = 1;
    }

    return R_SCE_Aes256CmacFinalSub(&indata_cmd, InData_Text, indata_datat, &indata_datat_len, OutData_DataT);
}

/*******************************************************************************************************************//**
 * Prepare to execute CMAC calculation.
 *
 * @param InData_KeyIndex User key generation information area
 *
 * @retval FSP_SUCCESS                          Normal termination.
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT resource conflict
 * @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      Input illegal user Key Generation Information
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              Internal error occurred.
 **********************************************************************************************************************/
fsp_err_t R_SCE_Aes256CmacVerifyInitPrivate (sce_aes_wrapped_key_t * InData_KeyIndex)
{
    uint32_t indata_keytype = 0; /* For normal */

    if (SCE_KEY_INDEX_TYPE_AES256_FOR_ECDH == InData_KeyIndex->type)
    {
        indata_keytype = change_endian_long(2); /* For ECDH */
    }
    return R_SCE_Aes256CmacInitSub(&indata_keytype, InData_KeyIndex->value);
}

/*******************************************************************************************************************//**
 * Verifies the MAC value.
 *
 * @param InData_Text Message data area (data_len byte)
 * @param MAX_CNT     Message data length (0 to arbitrary byte)
 *
 * @retval FSP_SUCCESS Normal termination.
 **********************************************************************************************************************/
fsp_err_t R_SCE_Aes256CmacVerifyUpdatePrivate (uint32_t * InData_Text, uint32_t MAX_CNT)
{
    R_SCE_Aes256CmacUpdateSub(InData_Text, MAX_CNT);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Validates the Mac value.
 *
 * @param All_Msg_Len     Input byte size of message data.
 * @param InData_Text     Input message data.
 * @param InData_DataT    MAC data area (data_len byte)
 * @param InData_DataTLen MAC data length
 *
 * @retval FSP_SUCCESS                       Normal termination.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL           Internal error occurred.
 * @retval FSP_ERR_CRYPTO_SCE_AUTHENTICATION Authentication NG
 **********************************************************************************************************************/
fsp_err_t R_SCE_Aes256CmacVerifyFinalPrivate (uint32_t   All_Msg_Len,
                                               uint32_t * InData_Text,
                                               uint32_t * InData_DataT,
                                               uint32_t * InData_DataTLen)
{
    uint32_t indata_cmd  = 0;
    uint32_t out_data[4] =
    {
        0
    };

    if ((0 == (All_Msg_Len % 16)) && (0 != All_Msg_Len))
    {
        indata_cmd = 2;
    }
    else
    {
        indata_cmd = 3;
    }

    return R_SCE_Aes256CmacFinalSub(&indata_cmd, InData_Text, InData_DataT, InData_DataTLen, out_data);
}

/*******************************************************************************************************************//**
 * prepares to execute the SHA256 hash operation
 *
 * @param handle SHA256 handler (work area)
 *
 * @retval FSP_SUCCESS Normal termination.
 **********************************************************************************************************************/
fsp_err_t R_SCE_Sha256InitPrivate (sce_sha_md5_handle_t * handle)
{
    uint32_t indata_sha256initval[8] =
    {
        0
    };

    FSP_PARAMETER_NOT_USED(handle);

    indata_sha256initval[0] = change_endian_long(SCE_HEX_6A09E667);
    indata_sha256initval[1] = change_endian_long(SCE_HEX_BB67AE85);
    indata_sha256initval[2] = change_endian_long(SCE_HEX_3C6EF372);
    indata_sha256initval[3] = change_endian_long(SCE_HEX_A54FF53A);
    indata_sha256initval[4] = change_endian_long(SCE_HEX_510E527F);
    indata_sha256initval[5] = change_endian_long(SCE_HEX_9B05688C);
    indata_sha256initval[6] = change_endian_long(SCE_HEX_1F83D9AB);
    indata_sha256initval[7] = change_endian_long(SCE_HEX_5BE0CD19);

    memcpy(handle->current_hash, indata_sha256initval, HW_SCE_SHA256_HASH_LENGTH_BYTE_SIZE);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * calculate a hash value
 *
 * @param handle           SHA256 handler (work area)
 * @param InData_PaddedMsg Input message.
 * @param MAX_CNT          Input message length
 *
 * @retval FSP_SUCCESS                          Normal termination.
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT resource conflict
 **********************************************************************************************************************/
fsp_err_t R_SCE_Sha256UpdatePrivate (sce_sha_md5_handle_t * handle, uint32_t * InData_PaddedMsg, uint32_t MAX_CNT)
{
    uint32_t out_data[8] =
    {
        0
    };
    fsp_err_t ercd = FSP_SUCCESS;

    FSP_PARAMETER_NOT_USED(handle);

    /*Casting uint32_t pointer is used for address.*/
    ercd = R_SCE_Sha224256GenerateMessageDigestSub((uint32_t *) handle->current_hash,
                                                    InData_PaddedMsg,
                                                    MAX_CNT,
                                                    out_data);
    memcpy(handle->current_hash, out_data, HW_SCE_SHA256_HASH_LENGTH_BYTE_SIZE);

    return ercd;
}

/*******************************************************************************************************************//**
 * calculate a hash value
 *
 * @param handle            SHA256 handler (work area).
 * @param InData_PaddedMsg  Input Message data
 * @param MAX_CNT           Input message length
 * @param OutData_MsgDigest Output Hash data
 * @param OutData_Length    Output Hash length
 *
 * @retval FSP_SUCCESS                          Normal termination.
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT resource conflict
 **********************************************************************************************************************/
fsp_err_t R_SCE_Sha256FinalPrivate (sce_sha_md5_handle_t * handle,
                                     uint32_t             * InData_PaddedMsg,
                                     uint32_t               MAX_CNT,
                                     uint32_t             * OutData_MsgDigest,
                                     uint32_t             * OutData_Length)
{
    fsp_err_t ercd = FSP_SUCCESS;

    FSP_PARAMETER_NOT_USED(handle);

    /*Casting uint32_t pointer is used for address.*/
    ercd = R_SCE_Sha224256GenerateMessageDigestSub((uint32_t *) handle->current_hash,
                                                    InData_PaddedMsg,
                                                    MAX_CNT,
                                                    OutData_MsgDigest);
    memcpy(handle->current_hash, OutData_MsgDigest, HW_SCE_SHA256_HASH_LENGTH_BYTE_SIZE);
    *OutData_Length = HW_SCE_SHA256_HASH_LENGTH_BYTE_SIZE;

    return ercd;
}

/*******************************************************************************************************************//**
 * Modular exponentiation operation with RSA 1024bit public key
 *
 * @param InData_KeyIndex the public key index information
 * @param InData_Text     input data
 * @param OutData_Text    output data
 *
 * @retval FSP_SUCCESS                          Normal termination.
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT resource conflict
 * @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      Input illegal user Key Generation Information
 **********************************************************************************************************************/
fsp_err_t R_SCE_Rsa1024ModularExponentEncryptPrivate (uint32_t * InData_KeyIndex,
                                                       uint32_t * InData_Text,
                                                       uint32_t * OutData_Text)
{
    return R_SCE_Rsa1024ModularExponentEncryptSub(InData_KeyIndex, InData_Text, OutData_Text);
}

/*******************************************************************************************************************//**
 * Modular exponentiation operation with RSA 1024bit private key
 *
 * @param InData_KeyIndex the private key index information
 * @param InData_Text     input data
 * @param OutData_Text    output data
 *
 * @retval FSP_SUCCESS                          Normal termination.
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT resource conflict
 * @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      Input illegal user Key Generation Information
 **********************************************************************************************************************/
fsp_err_t R_SCE_Rsa1024ModularExponentDecryptPrivate (uint32_t * InData_KeyIndex,
                                                       uint32_t * InData_Text,
                                                       uint32_t * OutData_Text)
{
    return R_SCE_Rsa1024ModularExponentDecryptSub(InData_KeyIndex, InData_Text, OutData_Text);
}

/*******************************************************************************************************************//**
 * Modular exponentiation operation with RSA 2048bit public key
 *
 * @param InData_KeyIndex the public key index information
 * @param InData_Text     input data
 * @param OutData_Text    output data
 *
 * @retval FSP_SUCCESS                          Normal termination.
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT resource conflict
 * @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      Input illegal user Key Generation Information
 **********************************************************************************************************************/
fsp_err_t R_SCE_Rsa2048ModularExponentEncryptPrivate (uint32_t * InData_KeyIndex,
                                                       uint32_t * InData_Text,
                                                       uint32_t * OutData_Text)
{
    return R_SCE_Rsa2048ModularExponentEncryptSub(InData_KeyIndex, InData_Text, OutData_Text);
}

/*******************************************************************************************************************//**
 * Modular exponentiation operation with RSA 2048bit private key
 *
 * @param InData_KeyIndex the private key index information
 * @param InData_Text     input data
 * @param OutData_Text    output data
 *
 * @retval FSP_SUCCESS                          Normal termination.
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT resource conflict
 * @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      Input illegal user Key Generation Information
 **********************************************************************************************************************/
fsp_err_t R_SCE_Rsa2048ModularExponentDecryptPrivate (uint32_t * InData_KeyIndex,
                                                       uint32_t * InData_Text,
                                                       uint32_t * OutData_Text)
{
    return R_SCE_Rsa2048ModularExponentDecryptSub(InData_KeyIndex, InData_Text, OutData_Text);
}

/*******************************************************************************************************************//**
 * Modular exponentiation operation with RSA 3072bit public key
 *
 * @param InData_KeyIndex the public key index information
 * @param InData_Text     input data
 * @param OutData_Text    output data
 *
 * @retval FSP_SUCCESS                          Normal termination.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              Internal error occurred.
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT resource conflict
 * @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      Input illegal user Key Generation Information
 **********************************************************************************************************************/
fsp_err_t R_SCE_Rsa3072ModularExponentEncryptPrivate (uint32_t * InData_KeyIndex,
                                                       uint32_t * InData_Text,
                                                       uint32_t * OutData_Text)
{
    return R_SCE_Rsa3072ModularExponentEncryptSub(InData_KeyIndex, InData_Text, OutData_Text);
}

/*******************************************************************************************************************//**
 * Modular exponentiation operation with RSA 4096bit public key
 *
 * @param InData_KeyIndex the public key index information
 * @param InData_Text     input data
 * @param OutData_Text    output data
 *
 * @retval FSP_SUCCESS                          Normal termination.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              Internal error occurred.
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT resource conflict
 * @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      Input illegal user Key Generation Information
 **********************************************************************************************************************/
fsp_err_t R_SCE_Rsa4096ModularExponentEncryptPrivate (uint32_t * InData_KeyIndex,
                                                       uint32_t * InData_Text,
                                                       uint32_t * OutData_Text)
{
    return R_SCE_Rsa4096ModularExponentEncryptSub(InData_KeyIndex, InData_Text, OutData_Text);
}

/*******************************************************************************************************************//**
 * prepares to generate the SHA256 HMAC hash value
 *
 * @param handle          SHA256 hamc handler (work area).
 * @param InData_KeyIndex key index
 *
 * @retval FSP_SUCCESS                          Normal termination.
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT resource conflict
 * @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      Input illegal user Key Generation Information
 **********************************************************************************************************************/
fsp_err_t R_SCE_Sha256HmacGenerateInitPrivate (sce_hmac_sha_handle_t      * handle,
                                                sce_hmac_sha_wrapped_key_t * InData_KeyIndex)
{
    uint32_t indata_keytype = 0;
    uint32_t key_length     = HW_SCE_HMAC_KEY_INDEX_WORD_SIZE;

    FSP_PARAMETER_NOT_USED(handle);

    if (SCE_KEY_INDEX_TYPE_HMAC_SHA256_FOR_ECDH == InData_KeyIndex->type)
    {
        indata_keytype = change_endian_long(2); /* For ECDH */
    }
    if (SCE_KEY_INDEX_TYPE_HMAC_SHA256_FOR_TLS == InData_KeyIndex->type)
    {
        indata_keytype = change_endian_long(1); /* For TLS */
        key_length = SCE_TLS_HMAC_KEY_INDEX_WORD_SIZE;
    }
    return R_SCE_Sha256HmacInitSub(&indata_keytype, InData_KeyIndex->value, key_length);
}

/*******************************************************************************************************************//**
 * Calculate the SHA256 HMAC hash value
 *
 * @param handle           SHA256 HMAC handler (work area).
 * @param InData_PaddedMsg Input value
 * @param MAX_CNT          Input value byte size
 *
 * @retval FSP_SUCCESS Normal termination.
 **********************************************************************************************************************/
fsp_err_t R_SCE_Sha256HmacGenerateUpdatePrivate (sce_hmac_sha_handle_t * handle,
                                                  uint32_t              * InData_PaddedMsg,
                                                  uint32_t                MAX_CNT)
{
    FSP_PARAMETER_NOT_USED(handle);

    R_SCE_Sha256HmacUpdateSub(InData_PaddedMsg, MAX_CNT);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Generate the SHA256 HMAC hash value
 *
 * @param handle      SHA256 HMAC handler (work area).
 * @param OutData_Mac Output MAC value
 *
 * @retval FSP_SUCCESS             Normal termination.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL Internal error occurred.
 **********************************************************************************************************************/
fsp_err_t R_SCE_Sha256HmacGenerateFinalPrivate (sce_hmac_sha_handle_t * handle, uint32_t * OutData_Mac)
{
    FSP_PARAMETER_NOT_USED(handle);

    uint32_t indata_cmd    = 0;
    uint32_t indata_mac    = 0;        /*dummy*/
    uint32_t indata_length = 0;        /*dummy*/

    indata_cmd = change_endian_long(0);

    return R_SCE_Sha256HmacFinalSub(&indata_cmd, &indata_mac, &indata_length, OutData_Mac);
}

/*******************************************************************************************************************//**
 * prepares to generate the SHA256 HMAC hash value for TLS
 *
 * @param handle          SHA256 HMAC handler (work area).
 * @param InData_KeyIndex key index
 *
 * @retval FSP_SUCCESS                          Normal termination.
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT resource conflict
 * @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      Input illegal user Key Generation Information
 **********************************************************************************************************************/
fsp_err_t R_SCE_Sha256HmacVerifyInitPrivate (sce_hmac_sha_handle_t      * handle,
                                              sce_hmac_sha_wrapped_key_t * InData_KeyIndex)
{
    FSP_PARAMETER_NOT_USED(handle);

    uint32_t indata_keytype = 0;
    uint32_t key_length     = SCE_TLS_HMAC_KEY_INDEX_WORD_SIZE;

    if (SCE_KEY_INDEX_TYPE_HMAC_SHA256_FOR_ECDH == InData_KeyIndex->type)
    {
        indata_keytype = change_endian_long(2); /* For ECDH */
    }
    if (SCE_KEY_INDEX_TYPE_HMAC_SHA256_FOR_TLS == InData_KeyIndex->type)
    {
        indata_keytype = change_endian_long(1); /* For TLS */
        key_length = SCE_TLS_HMAC_KEY_INDEX_WORD_SIZE;
    }
    return R_SCE_Sha256HmacInitSub(&indata_keytype, InData_KeyIndex->value, key_length);
}

/*******************************************************************************************************************//**
 * Calculate the SHA256 HMAC hash value
 *
 * @param handle           SHA256 HMAC handler (work area).
 * @param InData_PaddedMsg Input value
 * @param MAX_CNT          Input value byte size
 *
 * @retval FSP_SUCCESS Normal termination.
 **********************************************************************************************************************/
fsp_err_t R_SCE_Sha256HmacVerifyUpdatePrivate (sce_hmac_sha_handle_t * handle,
                                                uint32_t              * InData_PaddedMsg,
                                                uint32_t                MAX_CNT)
{
    FSP_PARAMETER_NOT_USED(handle);

    R_SCE_Sha256HmacUpdateSub(InData_PaddedMsg, MAX_CNT);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Verify the SHA256 HMAC hash value
 *
 * @param handle        SHA256 HMAC handler (work area).
 * @param InData_Mac    Input MAC value
 * @param InData_length Input MAC value byte size
 *
 * @retval FSP_SUCCESS             Normal termination.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL Internal error occurred.
 **********************************************************************************************************************/
fsp_err_t R_SCE_Sha256HmacVerifyFinalPrivate (sce_hmac_sha_handle_t * handle,
                                               uint32_t              * InData_Mac,
                                               uint32_t              * InData_length)
{
    uint32_t indata_cmd  = 0;
    uint32_t outdata_mac = 0;

    FSP_PARAMETER_NOT_USED(handle);

    indata_cmd = change_endian_long(1);

    return R_SCE_Sha256HmacFinalSub(&indata_cmd, InData_Mac, InData_length, &outdata_mac);
}

/*******************************************************************************************************************//**
 * Verify signature of ECC P-256 public key and output public key generation information.
 *
 * @param InData_Cmd       key_id use or not
 * @param InData_KeyIndex  public key index for signature verification
 * @param InData_data      API function argument "public_key_data" plus "stop bit" and "message length"
 * @param InData_Signature signature text
 * @param OutData_KeyIndex public key index for API function argument "public_key_data"
 *
 * @retval FSP_SUCCESS                          Normal termination.
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT resource conflict
 * @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      Input illegal user Key Generation Information
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              Internal error occurred or signature verification failed.
 **********************************************************************************************************************/
fsp_err_t R_SCE_EcdhReadPublicKeyPrivate (uint32_t * InData_Cmd,
                                           uint32_t * InData_KeyIndex,
                                           uint32_t * InData_data,
                                           uint32_t * InData_Signature,
                                           uint32_t * OutData_KeyIndex)
{
    return R_SCE_DlmsCosemQeuSignatureVerificationSub(InData_Cmd,
                                                       InData_KeyIndex,
                                                       InData_data,
                                                       InData_Signature,
                                                       OutData_KeyIndex);
}

/*******************************************************************************************************************//**
 * Output the key index of QeU without signature verification.
 *
 * @param InData_Cmd       key_id use or not
 * @param InData_data      API function argument "public_key_data" plus "stop bit" and "message length"
 * @param OutData_KeyIndex public key index for API function argument "public_key_data"
 *
 * @retval FSP_SUCCESS                          Normal termination.
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT resource conflict
 **********************************************************************************************************************/
fsp_err_t R_SCE_EcdhReadPublicKeyWithoutSignaturePrivate (uint32_t * InData_Cmd,
                                                           uint32_t * InData_data,
                                                           uint32_t * OutData_KeyIndex)
{
    return R_SCE_EcdhP256QeuOutputSub(InData_Cmd, InData_data, OutData_KeyIndex);
}

/*******************************************************************************************************************//**
 * Generate signature for public key generation information for ECDH key exchange.
 *
 * @param InData_Cmd          key_id use or not
 * @param InData_KeyType      type of key to be exchanged
 * @param InData_PubKeyIndex  public key index(for ECDH)
 * @param InData_PrivKeyIndex private key index for signature generation
 * @param InData_key_id       key_id
 * @param OutData_data        public key for key exchange
 * @param OutData_Signature   signature text
 * @param OutData_KeyIndex    private key index generated from random numbers(for ECDHE)
 *
 * @retval FSP_SUCCESS                          Normal termination.
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT resource conflict
 * @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      Input illegal user Key Generation Information
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              Internal error occurred.
 **********************************************************************************************************************/
fsp_err_t R_SCE_EcdhMakePublicKeyPrivate (uint32_t * InData_Cmd,
                                           uint32_t * InData_KeyType,
                                           uint32_t * InData_PubKeyIndex,
                                           uint32_t * InData_PrivKeyIndex,
                                           uint32_t * InData_key_id,
                                           uint32_t * OutData_data,
                                           uint32_t * OutData_Signature,
                                           uint32_t * OutData_KeyIndex)
{
    return R_SCE_DlmsCosemQevSignatureGenerationSub(InData_Cmd,
                                                     InData_KeyType,
                                                     InData_PubKeyIndex,
                                                     InData_PrivKeyIndex,
                                                     InData_key_id,
                                                     OutData_data,
                                                     OutData_Signature,
                                                     OutData_KeyIndex);
}

/*******************************************************************************************************************//**
 * Output key generation information of shared secret "Z" from partner public key and your private key.
 *
 * @param InData_KeyType type of key to be exchanged
 * @param InData_PubKeyIndex public key index
 * @param InData_PrivKeyIndex  private key index
 * @param OutData_KeyIndex key index of shared secret "Z"
 *
 * @retval FSP_SUCCESS                          Normal termination.
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT resource conflict
 * @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      Input illegal user Key Generation Information
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              Internal error occurred.
 **********************************************************************************************************************/
fsp_err_t R_SCE_EcdhCalculateSharedSecretIndexPrivate (uint32_t * InData_KeyType,
                                                        uint32_t * InData_PubKeyIndex,
                                                        uint32_t * InData_PrivKeyIndex,
                                                        uint32_t * OutData_KeyIndex)
{
    return R_SCE_DlmsCosemCalculateZSub(InData_KeyType, InData_PubKeyIndex, InData_PrivKeyIndex, OutData_KeyIndex);
}

/*******************************************************************************************************************//**
 * Key is derived using the shared secret "Z" as the key material.
 *
 * @param InData_KeyIndexType Derived key type(0:AES-128, 1:AES-256, 2:HMAC-SHA256)
 * @param InData_KeyIndex     key index of shared secret "Z"
 * @param InData_KDFType      Algorithm used for key derivation calculation(0:SHA256, 1:HMAC-SHA256)
 * @param InData_PaddedMsg    additional data used for key derivation, preceded by Algorithm ID encoded value,
 *                            followed by stop bit and data length
 * @param MAX_CNT             maximum number of loops when reading InData_PaddedMsg
 * @param InData_SaltKeyIndex Salt key index
 * @param OutData_KeyIndex    key index of KEK
 *
 * @retval FSP_SUCCESS                          Normal termination.
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT resource conflict
 * @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      Input illegal user Key Generation Information
 **********************************************************************************************************************/
fsp_err_t R_SCE_EcdhKeyDerivationPrivate (uint32_t *InData_KeyIndexType, uint32_t *InData_KeyIndex,
        uint32_t *InData_KDFType, uint32_t *InData_PaddedMsg, uint32_t MAX_CNT, uint32_t *InData_SaltKeyIndex,
        uint32_t *OutData_KeyIndex)
{
    return R_SCE_DlmsCosemCalculateKekSub(InData_KeyIndexType, InData_KeyIndex, InData_KDFType, InData_PaddedMsg,
            MAX_CNT, InData_SaltKeyIndex, OutData_KeyIndex);
}

/*******************************************************************************************************************//**
 * Wrap InData_WrappedKeyIndex with InData_KeyIndex.
 *
 * @param InData_KeyIndex User   key generation information area.
 * @param InData_WrappedKeyType  select key to be wrapped.
 * @param InData_WrappedKeyIndex key to be wrapped.
 * @param OutData_Text           wrapped key.
 *
 * @retval FSP_SUCCESS                          Normal termination.
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT Resource conflict.
 * @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      Input illegal user Key Generation Information.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              Internal error occurred.
 *********************************************************************************************************************/
fsp_err_t R_SCE_Aes128KeyWrapPrivate(uint32_t * InData_KeyIndex,
                                     uint32_t * InData_WrappedKeyType,
                                     uint32_t * InData_WrappedKeyIndex,
                                     uint32_t * OutData_Text)
{
    uint32_t indata_cmd = 0;
    int32_t key_index_size = 0;
    uint32_t wrapped_key_size = 0;

    indata_cmd = change_endian_long(0);

    if (SCE_KEYWRAP_AES128 == (*InData_WrappedKeyType))
    {
        wrapped_key_size = 6;
        key_index_size = 9;
    }
    else
    {
        wrapped_key_size = 10;
        key_index_size = 13;
    }

    *InData_WrappedKeyType = change_endian_long(*InData_WrappedKeyType);
    return R_SCE_AesKeyWrapSub(&indata_cmd, InData_KeyIndex, key_index_size, InData_WrappedKeyType,
            InData_WrappedKeyIndex, wrapped_key_size, OutData_Text);
}

/*******************************************************************************************************************//**
 * Wrap InData_WrappedKeyIndex with InData_KeyIndex.
 *
 * @param InData_KeyIndex User   key generation information area.
 * @param InData_WrappedKeyType  select key to be wrapped.
 * @param InData_WrappedKeyIndex key to be wrapped.
 * @param OutData_Text           wrapped key.
 *
 * @retval FSP_SUCCESS                          Normal termination.
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT Resource conflict.
 * @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      Input illegal user Key Generation Information.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              Internal error occurred.
 *********************************************************************************************************************/
fsp_err_t R_SCE_Aes256KeyWrapPrivate(uint32_t * InData_KeyIndex,
                                     uint32_t * InData_WrappedKeyType,
                                     uint32_t * InData_WrappedKeyIndex,
                                     uint32_t * OutData_Text)
{
    uint32_t indata_cmd = 0;
    int32_t key_index_size = 0;
    uint32_t wrapped_key_size = 0;

    indata_cmd = change_endian_long(1);

    if (SCE_KEYWRAP_AES128 == (*InData_WrappedKeyType))
    {
        wrapped_key_size = 6;
        key_index_size = 9;
    }
    else
    {
        wrapped_key_size = 10;
        key_index_size = 13;
    }

    *InData_WrappedKeyType = change_endian_long(*InData_WrappedKeyType);

    return R_SCE_AesKeyWrapSub(&indata_cmd, InData_KeyIndex, key_index_size, InData_WrappedKeyType,
            InData_WrappedKeyIndex, wrapped_key_size, OutData_Text);
}

/*******************************************************************************************************************//**
 * Unwrap InData_Text with key_index.
 *
 * @param InData_MasterKey      key used for unwrapping.
 * @param InData_WrappedKeyType select key to be wrapped.
 * @param InData_Text           wrapped key.
 * @param OutData_KeyIndex      key to be unwrapped.
 *
 * @retval FSP_SUCCESS                          Normal termination.
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT Resource conflict.
 * @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      Input illegal user Key Generation Information.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              Internal error occurred.
 *********************************************************************************************************************/
fsp_err_t R_SCE_Aes128KeyUnWrapPrivate(sce_aes_wrapped_key_t * InData_MasterKey,
                                       uint32_t * InData_WrappedKeyType,
                                       uint32_t * InData_Text,
                                       uint32_t * OutData_KeyIndex)
{
    uint32_t indata_keytype = 0; /* For normal */
    uint32_t indata_cmd = 0;
    uint32_t key_index_size = 0;
    uint32_t wrapped_key_size = 0;

    if (SCE_KEY_INDEX_TYPE_AES128_FOR_ECDH == InData_MasterKey->type)
    {
        indata_keytype = change_endian_long(2); /* For ECDH */
    }
    indata_cmd = change_endian_long(0);

    if (SCE_KEYWRAP_AES128 == (*InData_WrappedKeyType))
    {
        wrapped_key_size = 6;
        key_index_size = 9;
    }
    else
    {
        wrapped_key_size = 10;
        key_index_size = 13;
    }

    *InData_WrappedKeyType = change_endian_long(*InData_WrappedKeyType);

    return R_SCE_AesKeyUnwrapSub(&indata_keytype, &indata_cmd, InData_MasterKey->value, key_index_size,
            InData_WrappedKeyType, InData_Text, wrapped_key_size, OutData_KeyIndex);
}

/*******************************************************************************************************************//**
 * Unwrap InData_Text with key_index.
 *
 * @param InData_MasterKey      key used for unwrapping.
 * @param InData_WrappedKeyType select key to be wrapped.
 * @param InData_Text           wrapped key.
 * @param OutData_KeyIndex      key to be unwrapped.
 *
 * @retval FSP_SUCCESS                          Normal termination.
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT Resource conflict.
 * @retval FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL      Input illegal user Key Generation Information.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              Internal error occurred.
 *********************************************************************************************************************/
fsp_err_t R_SCE_Aes256KeyUnWrapPrivate(sce_aes_wrapped_key_t * InData_MasterKey,
                                       uint32_t * InData_WrappedKeyType,
                                       uint32_t * InData_Text,
                                       uint32_t * OutData_KeyIndex)
{
    uint32_t indata_keytype = 0; /* For normal */
    uint32_t indata_cmd = 0;
    uint32_t key_index_size = 0;
    uint32_t wrapped_key_size = 0;

    if (SCE_KEY_INDEX_TYPE_AES256_FOR_ECDH == InData_MasterKey->type)
    {
        indata_keytype = change_endian_long(2); /* For ECDH */
    }
    indata_cmd = change_endian_long(1);

    if (SCE_KEYWRAP_AES128 == (*InData_WrappedKeyType))
    {
        wrapped_key_size = 6;
        key_index_size = 9;
    }
    else
    {
        wrapped_key_size = 10;
        key_index_size = 13;
    }

    *InData_WrappedKeyType = change_endian_long(*InData_WrappedKeyType);

    return R_SCE_AesKeyUnwrapSub(&indata_keytype, &indata_cmd, InData_MasterKey->value, key_index_size,
            InData_WrappedKeyType, InData_Text, wrapped_key_size, OutData_KeyIndex);
}

/*******************************************************************************************************************//**
 * change endian
 *
 * @param data input data
 *
 * @return the data changing endian
 **********************************************************************************************************************/

uint32_t change_endian_long (uint32_t data)
{
#ifndef __ARMEB__                      /* Little endian */

    /* Casting is valid because it matches the type to the right side or argument. */
    return __REV(data);
#else                                  /* Big endian */
    return data;
#endif  /* defined __LIT */
}
