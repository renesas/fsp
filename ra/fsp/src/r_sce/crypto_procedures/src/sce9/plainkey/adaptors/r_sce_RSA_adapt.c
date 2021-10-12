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
#include "hw_sce_private.h"
#include "hw_sce_ra_private.h"
#include "hw_sce_rsa_private.h"

fsp_err_t HW_SCE_RSA_4096PublicKeyEncrypt (const uint32_t * InData_Text,
                                           const uint32_t * InData_PublicKey,
                                           const uint32_t * InData_N,
                                           uint32_t       * OutData_Text)

{
    fsp_err_t err = FSP_SUCCESS;

    /* Create storage to hold the generated OEM key index */
    sce_rsa4096_public_key_index_t formatted_rsa_public_key_output;
    uint8_t formatted_rsa_public_key_input[HW_SCE_RSA4096_NE_KEY_BYTE_SIZE] = {0};
    memcpy(&formatted_rsa_public_key_input[0], InData_N, HW_SCE_RSA_4096_KEY_N_LENGTH_BYTE_SIZE);
    memcpy(&formatted_rsa_public_key_input[HW_SCE_RSA_4096_KEY_N_LENGTH_BYTE_SIZE],
           InData_PublicKey,
           HW_SCE_RSA_4096_KEY_E_LENGTH_BYTE_SIZE);

    err =
        HW_SCE_GenerateOemKeyIndexPrivate(SCE_OEM_KEY_TYPE_PLAIN,
                                          SCE_OEM_CMD_RSA4096_PUBLIC,
                                          NULL,
                                          NULL,
                                          (const uint8_t *) &formatted_rsa_public_key_input,
                                          (uint32_t *) &formatted_rsa_public_key_output.value);

    if (FSP_SUCCESS == err)
    {
        err = HW_SCE_Rsa4096ModularExponentEncryptSub((uint32_t *) &formatted_rsa_public_key_output.value,
                                                      InData_Text,
                                                      OutData_Text);
    }

    return err;
}

fsp_err_t HW_SCE_RSA_3072PublicKeyEncrypt (const uint32_t * InData_Text,
                                           const uint32_t * InData_PublicKey,
                                           const uint32_t * InData_N,
                                           uint32_t       * OutData_Text)

{
    fsp_err_t err = FSP_SUCCESS;

    /* Create storage to hold the generated OEM key index */
    sce_rsa3072_public_key_index_t formatted_rsa_public_key_output;
    uint8_t formatted_rsa_public_key_input[HW_SCE_RSA3072_NE_KEY_BYTE_SIZE] = {0};
    memcpy(&formatted_rsa_public_key_input[0], InData_N, HW_SCE_RSA_3072_KEY_N_LENGTH_BYTE_SIZE);
    memcpy(&formatted_rsa_public_key_input[HW_SCE_RSA_3072_KEY_N_LENGTH_BYTE_SIZE],
           InData_PublicKey,
           HW_SCE_RSA_3072_KEY_E_LENGTH_BYTE_SIZE);

    err =
        HW_SCE_GenerateOemKeyIndexPrivate(SCE_OEM_KEY_TYPE_PLAIN,
                                          SCE_OEM_CMD_RSA3072_PUBLIC,
                                          NULL,
                                          NULL,
                                          (const uint8_t *) &formatted_rsa_public_key_input,
                                          (uint32_t *) &formatted_rsa_public_key_output.value);

    if (FSP_SUCCESS == err)
    {
        err = HW_SCE_Rsa3072ModularExponentEncryptSub((uint32_t *) &formatted_rsa_public_key_output.value,
                                                      InData_Text,
                                                      OutData_Text);
    }

    return err;
}

fsp_err_t HW_SCE_RSA_2048KeyGenerate (uint32_t   num_tries,
                                      uint32_t * OutData_PrivateKey,
                                      uint32_t * OutData_N,
                                      uint32_t * OutData_DomainParam)

{
    FSP_PARAMETER_NOT_USED(num_tries);
    FSP_PARAMETER_NOT_USED(OutData_PrivateKey);
    FSP_PARAMETER_NOT_USED(OutData_N);
    FSP_PARAMETER_NOT_USED(OutData_DomainParam);

    return FSP_ERR_UNSUPPORTED;
}

fsp_err_t HW_SCE_RSA_2048PublicKeyEncrypt (const uint32_t * InData_Text,
                                           const uint32_t * InData_PublicKey,
                                           const uint32_t * InData_N,
                                           uint32_t       * OutData_Text)

{
    fsp_err_t err = FSP_SUCCESS;

    /* Create storage to hold the generated OEM key index */
    sce_rsa2048_public_key_index_t formatted_rsa_public_key_output;
    uint8_t formatted_rsa_public_key_input[HW_SCE_RSA2048_NE_KEY_BYTE_SIZE] = {0};
    memcpy(&formatted_rsa_public_key_input[0], InData_N, HW_SCE_RSA_2048_KEY_N_LENGTH_BYTE_SIZE);
    memcpy(&formatted_rsa_public_key_input[HW_SCE_RSA_2048_KEY_N_LENGTH_BYTE_SIZE],
           InData_PublicKey,
           HW_SCE_RSA_2048_KEY_E_LENGTH_BYTE_SIZE);

    err =
        HW_SCE_GenerateOemKeyIndexPrivate(SCE_OEM_KEY_TYPE_PLAIN,
                                          SCE_OEM_CMD_RSA2048_PUBLIC,
                                          NULL,
                                          NULL,
                                          (const uint8_t *) &formatted_rsa_public_key_input,
                                          (uint32_t *) &formatted_rsa_public_key_output.value);

    if (FSP_SUCCESS == err)
    {
        err = HW_SCE_Rsa2048ModularExponentEncryptSub((uint32_t *) &formatted_rsa_public_key_output.value,
                                                      InData_Text,
                                                      OutData_Text);
    }

    return err;
}

fsp_err_t HW_SCE_RSA_2048PrivateKeyDecrypt (const uint32_t * InData_Text,
                                            const uint32_t * InData_PrivateKey,
                                            const uint32_t * InData_N,
                                            uint32_t       * OutData_Text)

{
    FSP_PARAMETER_NOT_USED(InData_PrivateKey);
    fsp_err_t err = FSP_SUCCESS;

    /* Create storage to hold the generated OEM key index */
    sce_rsa2048_private_key_index_t encrypted_rsa_key;

    /*This function requires the plaintext RSA key is provided in a single buffer in the order:
     * Public Key (N) of size RSA_MODULUS_SIZE_BYTES(x)
     * Private Key (D) of size private_key_size_bytes
     * The buffer in mbedtls_rsa_private() already contains the data in that format, so InData_N
     * is directly provided to this function.
     */
    err =
        HW_SCE_GenerateOemKeyIndexPrivate(SCE_OEM_KEY_TYPE_PLAIN, SCE_OEM_CMD_RSA2048_PRIVATE, NULL, NULL,
                                          (const uint8_t *) InData_N, (uint32_t *) &encrypted_rsa_key.value);

    if (FSP_SUCCESS == err)
    {
        err = HW_SCE_Rsa2048ModularExponentDecryptSub((uint32_t *) &encrypted_rsa_key.value, InData_Text, OutData_Text);
    }

    return err;
}

fsp_err_t HW_SCE_HRK_RSA_2048KeyGenerate (uint32_t   num_tries,
                                          uint32_t * OutData_KeyIndex,
                                          uint32_t * OutData_N,
                                          uint32_t * OutData_DomainParam)

{
    sce_rsa2048_key_pair_index_t key_pair_index = {0};
    fsp_err_t err = FSP_SUCCESS;

    /* P.Q are the prime 1 and 2 fields that are in some cases generated when the private key is generated.
     * This was the case with W1D; but this information is not provided on the RA6M4.
     * There is no functional issue since the procedures do not require it for operation,
     * however mbedCrypto requires these fields to be non-zero in order for the private key_export to work.
     * These dummy values are placed into those fields to get past the non-zero check. */
    uint8_t dummy_P_Q[20] = {5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5};

    err =
        HW_SCE_GenerateRsa2048RandomKeyIndexSub(num_tries,
                                                (uint32_t *) &key_pair_index.pub_key.value,
                                                (uint32_t *) &key_pair_index.priv_key.value);

    if (FSP_SUCCESS == err)
    {
        memcpy(OutData_KeyIndex, &key_pair_index.priv_key.value, sizeof(key_pair_index.priv_key.value));
        memcpy(OutData_N, &key_pair_index.pub_key.value.key_n, sizeof(key_pair_index.pub_key.value.key_n));
        memcpy(OutData_DomainParam, dummy_P_Q, sizeof(dummy_P_Q));
    }

    return err;
}

fsp_err_t HW_SCE_HRK_RSA_2048PrivateKeyDecrypt (const uint32_t * InData_Text,
                                                const uint32_t * InData_KeyIndex,
                                                const uint32_t * InData_N,
                                                uint32_t       * OutData_Text)

{
    FSP_PARAMETER_NOT_USED(InData_N);

    fsp_err_t err = FSP_SUCCESS;

    err = HW_SCE_Rsa2048ModularExponentDecryptSub((uint32_t *) InData_KeyIndex, InData_Text, OutData_Text);

    return err;
}
