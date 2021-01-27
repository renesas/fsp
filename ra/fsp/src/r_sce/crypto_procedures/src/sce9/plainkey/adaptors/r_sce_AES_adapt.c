/***********************************************************************************************************************
 * Copyright [2020-2021] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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

#include "hw_sce_ra_private.h"
#include "hw_sce_private.h"

typedef enum e_sce_aes_key_size
{
    SCE_AES_KEY_SIZE_128 = 0,
    SCE_AES_KEY_SIZE_192,
    SCE_AES_KEY_SIZE_256
} sce_aes_key_size_t;

fsp_err_t (* init[])(const uint32_t * InData_Cmd, const uint32_t * InData_KeyIndex, const uint32_t * InData_IV) =
{
    [SCE_AES_KEY_SIZE_128] = HW_SCE_Aes128EncryptDecryptInitSub,
    [SCE_AES_KEY_SIZE_192] = HW_SCE_Aes192EncryptDecryptInitSub,
    [SCE_AES_KEY_SIZE_256] = HW_SCE_Aes256EncryptDecryptInitSub,
};

void (* update[])(const uint32_t * InData_Text, uint32_t * OutData_Text, const uint32_t MAX_CNT) =
{
    [SCE_AES_KEY_SIZE_128] = HW_SCE_Aes128EncryptDecryptUpdateSub,
    [SCE_AES_KEY_SIZE_192] = HW_SCE_Aes192EncryptDecryptUpdateSub,
    [SCE_AES_KEY_SIZE_256] = HW_SCE_Aes256EncryptDecryptUpdateSub,
};

fsp_err_t (* final[])(void) =
{
    [SCE_AES_KEY_SIZE_128] = HW_SCE_Aes128EncryptDecryptFinalSub,
    [SCE_AES_KEY_SIZE_192] = HW_SCE_Aes192EncryptDecryptFinalSub,
    [SCE_AES_KEY_SIZE_256] = HW_SCE_Aes256EncryptDecryptFinalSub,
};

static fsp_err_t hw_sce_aes_encrypt_decrypt(sce_aes_key_size_t key_size,
                                            uint32_t           command,
                                            const uint32_t   * InData_KeyIndex,
                                            const uint32_t     num_words,
                                            const uint32_t   * InData_Text,
                                            uint32_t         * OutData_Text);

static fsp_err_t hw_sce_aes_encrypt_decrypt (sce_aes_key_size_t key_size,
                                             uint32_t           command,
                                             const uint32_t   * InData_KeyIndex,
                                             const uint32_t     num_words,
                                             const uint32_t   * InData_Text,
                                             uint32_t         * OutData_Text)
{
    fsp_err_t status      = FSP_ERR_CRYPTO_SCE_FAIL;
    uint32_t  indata_cmd  = change_endian_long(command); /* ECB-Encrypt */
    uint32_t  Dummy_IV[4] = {0};
    status = init[key_size](&indata_cmd, InData_KeyIndex, Dummy_IV);
    if (FSP_SUCCESS == status)
    {
        update[key_size](InData_Text, OutData_Text, num_words);
        status = final[key_size]();
    }

    if (FSP_SUCCESS != status)
    {
        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        return FSP_SUCCESS;
    }
}

fsp_err_t HW_SCE_AES_128EcbEncryptUsingEncryptedKey (const uint32_t * InData_KeyIndex,
                                                     const uint32_t   num_words,
                                                     const uint32_t * InData_Text,
                                                     uint32_t       * OutData_Text)
{
    return hw_sce_aes_encrypt_decrypt(SCE_AES_KEY_SIZE_128,
                                      0x00000000u,
                                      InData_KeyIndex,
                                      num_words,
                                      InData_Text,
                                      OutData_Text);
}

fsp_err_t HW_SCE_AES_128EcbDecryptUsingEncryptedKey (const uint32_t * InData_KeyIndex,
                                                     const uint32_t   num_words,
                                                     const uint32_t * InData_Text,
                                                     uint32_t       * OutData_Text)
{
    return hw_sce_aes_encrypt_decrypt(SCE_AES_KEY_SIZE_128,
                                      0x00000001u,
                                      InData_KeyIndex,
                                      num_words,
                                      InData_Text,
                                      OutData_Text);
}

fsp_err_t HW_SCE_AES_128EcbEncrypt (const uint32_t * InData_KeyIndex,
                                    const uint32_t   num_words,
                                    const uint32_t * InData_Text,
                                    uint32_t       * OutData_Text)
{
    return hw_sce_aes_encrypt_decrypt(SCE_AES_KEY_SIZE_128,
                                      0x00000000u,
                                      InData_KeyIndex,
                                      num_words,
                                      InData_Text,
                                      OutData_Text);
}

fsp_err_t HW_SCE_AES_128EcbDecrypt (const uint32_t * InData_KeyIndex,
                                    const uint32_t   num_words,
                                    const uint32_t * InData_Text,
                                    uint32_t       * OutData_Text)
{
    return hw_sce_aes_encrypt_decrypt(SCE_AES_KEY_SIZE_128,
                                      0x00000001u,
                                      InData_KeyIndex,
                                      num_words,
                                      InData_Text,
                                      OutData_Text);
}

fsp_err_t HW_SCE_AES_192EcbEncryptUsingEncryptedKey (const uint32_t * InData_KeyIndex,
                                                     const uint32_t   num_words,
                                                     const uint32_t * InData_Text,
                                                     uint32_t       * OutData_Text)
{
    return hw_sce_aes_encrypt_decrypt(SCE_AES_KEY_SIZE_192,
                                      0x00000000u,
                                      InData_KeyIndex,
                                      num_words,
                                      InData_Text,
                                      OutData_Text);
}

fsp_err_t HW_SCE_AES_192EcbDecryptUsingEncryptedKey (const uint32_t * InData_KeyIndex,
                                                     const uint32_t   num_words,
                                                     const uint32_t * InData_Text,
                                                     uint32_t       * OutData_Text)
{
    return hw_sce_aes_encrypt_decrypt(SCE_AES_KEY_SIZE_192,
                                      0x00000001u,
                                      InData_KeyIndex,
                                      num_words,
                                      InData_Text,
                                      OutData_Text);
}

fsp_err_t HW_SCE_AES_192EcbEncrypt (const uint32_t * InData_KeyIndex,
                                    const uint32_t   num_words,
                                    const uint32_t * InData_Text,
                                    uint32_t       * OutData_Text)
{
    return hw_sce_aes_encrypt_decrypt(SCE_AES_KEY_SIZE_192,
                                      0x00000000u,
                                      InData_KeyIndex,
                                      num_words,
                                      InData_Text,
                                      OutData_Text);
}

fsp_err_t HW_SCE_AES_192EcbDecrypt (const uint32_t * InData_KeyIndex,
                                    const uint32_t   num_words,
                                    const uint32_t * InData_Text,
                                    uint32_t       * OutData_Text)
{
    return hw_sce_aes_encrypt_decrypt(SCE_AES_KEY_SIZE_192,
                                      0x00000001u,
                                      InData_KeyIndex,
                                      num_words,
                                      InData_Text,
                                      OutData_Text);
}

fsp_err_t HW_SCE_AES_256EcbEncryptUsingEncryptedKey (const uint32_t * InData_KeyIndex,
                                                     const uint32_t   num_words,
                                                     const uint32_t * InData_Text,
                                                     uint32_t       * OutData_Text)
{
    return hw_sce_aes_encrypt_decrypt(SCE_AES_KEY_SIZE_256,
                                      0x00000000u,
                                      InData_KeyIndex,
                                      num_words,
                                      InData_Text,
                                      OutData_Text);
}

fsp_err_t HW_SCE_AES_256EcbDecryptUsingEncryptedKey (const uint32_t * InData_KeyIndex,
                                                     const uint32_t   num_words,
                                                     const uint32_t * InData_Text,
                                                     uint32_t       * OutData_Text)
{
    return hw_sce_aes_encrypt_decrypt(SCE_AES_KEY_SIZE_256,
                                      0x00000001u,
                                      InData_KeyIndex,
                                      num_words,
                                      InData_Text,
                                      OutData_Text);
}

fsp_err_t HW_SCE_AES_256EcbEncrypt (const uint32_t * InData_KeyIndex,
                                    const uint32_t   num_words,
                                    const uint32_t * InData_Text,
                                    uint32_t       * OutData_Text)
{
    return hw_sce_aes_encrypt_decrypt(SCE_AES_KEY_SIZE_256,
                                      0x00000000u,
                                      InData_KeyIndex,
                                      num_words,
                                      InData_Text,
                                      OutData_Text);
}

fsp_err_t HW_SCE_AES_256EcbDecrypt (const uint32_t * InData_KeyIndex,
                                    const uint32_t   num_words,
                                    const uint32_t * InData_Text,
                                    uint32_t       * OutData_Text)
{
    return hw_sce_aes_encrypt_decrypt(SCE_AES_KEY_SIZE_256,
                                      0x00000001u,
                                      InData_KeyIndex,
                                      num_words,
                                      InData_Text,
                                      OutData_Text);
}

fsp_err_t HW_SCE_AES_128CreateEncryptedKey (uint32_t * OutData_KeyIndex)
{
    if (FSP_SUCCESS != HW_SCE_GenerateAes128RandomKeyIndexSub(OutData_KeyIndex))
    {
        return FSP_ERR_CRYPTO_SCE_FAIL;
    }

    return FSP_SUCCESS;
}

fsp_err_t HW_SCE_AES_192CreateEncryptedKey (uint32_t * OutData_KeyIndex)
{
    if (FSP_SUCCESS != HW_SCE_GenerateAes192RandomKeyIndexSub(OutData_KeyIndex))
    {
        return FSP_ERR_CRYPTO_SCE_FAIL;
    }

    return FSP_SUCCESS;
}

fsp_err_t HW_SCE_AES_256CreateEncryptedKey (uint32_t * OutData_KeyIndex)
{
    if (FSP_SUCCESS != HW_SCE_GenerateAes256RandomKeyIndexSub(OutData_KeyIndex))
    {
        return FSP_ERR_CRYPTO_SCE_FAIL;
    }

    return FSP_SUCCESS;
}

/* AES GCM 256bit init adaptors */
fsp_err_t HW_SCE_Aes256GcmEncryptInitSubGeneral(uint32_t *InData_KeyType, uint32_t *InData_KeyIndex, uint32_t *InData_IV)
{
    FSP_PARAMETER_NOT_USED(InData_KeyType);
    return(HW_SCE_Aes256GcmEncryptInitSub(InData_KeyIndex, InData_IV));
}

fsp_err_t HW_SCE_Aes256GcmDecryptInitSubGeneral(uint32_t *InData_KeyType, uint32_t *InData_KeyIndex, uint32_t *InData_IV)
{
    FSP_PARAMETER_NOT_USED(InData_KeyType);
    return(HW_SCE_Aes256GcmDecryptInitSub(InData_KeyIndex, InData_IV));
}
