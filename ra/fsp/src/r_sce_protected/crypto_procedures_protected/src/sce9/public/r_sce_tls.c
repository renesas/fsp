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

/*******************************************************************************************************************//**
 * @addtogroup SCE_PROTECTED
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Verify root CA certificate.
 *
 * @param[in]  public_key_type              key type
 * @param[in]  certificate                  certificates.
 * @param[in]  certificate_length           byte size of certificates.
 * @param[in]  public_key_n_start_position  start position of public key n.
 * @param[in]  public_key_n_end_position    end position of public key n.
 * @param[in]  public_key_e_start_position  start position of public key e.
 * @param[in]  public_key_e_end_position    end position of public key e.
 * @param[in]  signature                    signature for certificates.
 * @param[out] encrypted_root_public_key    public key for RSA 2048bit.
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource needed
 *                                              by the processing routine was in use by another processing routine.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              An internal error occurred.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 *
 **********************************************************************************************************************/
fsp_err_t R_SCE_TLS_RootCertificateVerify(uint32_t public_key_type, uint8_t *certificate,
        uint32_t certificate_length, uint32_t public_key_n_start_position, uint32_t public_key_n_end_position,
        uint32_t public_key_e_start_position, uint32_t public_key_e_end_position, uint8_t *signature,
        uint32_t *encrypted_root_public_key)
{
    uint32_t information[4] =
    {
        0
    };
    uint32_t certificate_length_sub = 0;
    uint32_t certificate_length_sub2 = 0;
    uint32_t public_key_type_sub = 0;

    public_key_type_sub = change_endian_long(public_key_type);
    certificate_length_sub = change_endian_long(certificate_length);
    certificate_length_sub2 = (certificate_length + 3) / 4;
    certificate_length_sub2 = change_endian_long(certificate_length_sub2);

    information[0] = change_endian_long(public_key_n_start_position);
    information[1] = change_endian_long(public_key_n_end_position);
    information[2] = change_endian_long(public_key_e_start_position);
    information[3] = change_endian_long(public_key_e_end_position);

    return R_SCE_TlsRootCertificateVerificationSub(
    /* Casting uint32_t pointer is used for address. */
    /* uint32_t *InData_Sel_PubKeyType,       */&public_key_type_sub,
    /* uint32_t *InData_Certificates,         */(uint32_t *) (certificate),
    /* uint32_t *InData_CertificatesLength,   */&certificate_length_sub,
    /* uint32_t *InData_Signature,            */(uint32_t *) (signature),
    /* uint32_t *InData_CertificatesInfo,     */information,
    /* uint32_t length,                       */certificate_length_sub2,
    /* uint32_t *OutData_PubKey,              */encrypted_root_public_key);

}

/*******************************************************************************************************************//**
 * Verify server certificate and intermediate certificate.
 *
 * @param[in]  public_key_type             key type
 * @param[in]  encrypted_input_public_key  public key.
 * @param[in]  certificate                 certificates.
 * @param[in]  certificate_length          byte size of certificates.
 * @param[in]  signature                   signature for certificates.
 * @param[in]  public_key_n_start_position start position of public key n.
 * @param[in]  public_key_n_end_position   end position of public key n.
 * @param[in]  public_key_e_start_position start position of public key e.
 * @param[in]  public_key_e_end_position   end position of public key e.
 * @param[out] encrypted_output_public_key public key for RSA 2048bit.
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource needed
 *                                              by the processing routine was in use by another processing routine.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              An internal error occurred.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 *
 **********************************************************************************************************************/
fsp_err_t R_SCE_TLS_CertificateVerify(uint32_t public_key_type, uint32_t *encrypted_input_public_key,
        uint8_t *certificate, uint32_t certificate_length, uint8_t *signature, uint32_t public_key_n_start_position,
        uint32_t public_key_n_end_position, uint32_t public_key_e_start_position, uint32_t public_key_e_end_position,
        uint32_t *encrypted_output_public_key)
{
    uint32_t information[4] =
    {
        0
    };
    uint32_t certificate_length_sub = 0;
    uint32_t certificate_length_sub2 = 0;
    uint32_t tmp_public_key_type = 0;

    tmp_public_key_type = change_endian_long(public_key_type);
    certificate_length_sub = change_endian_long(certificate_length);
    certificate_length_sub2 = (certificate_length + 3) / 4;
    certificate_length_sub2 = change_endian_long(certificate_length_sub2);

    information[0] = change_endian_long(public_key_n_start_position);
    information[1] = change_endian_long(public_key_n_end_position);
    information[2] = change_endian_long(public_key_e_start_position);
    information[3] = change_endian_long(public_key_e_end_position);

    /* Casting uint32_t pointer is used for address. */
    return R_SCE_TlsCertificateVerificationSub(
    /* uint32_t *InData_Sel_PubKeyType,       */&tmp_public_key_type,
    /* uint32_t *InData_PubKey,               */encrypted_input_public_key,
    /* uint32_t *InData_TBSCertificate,       */(uint32_t *) certificate,
    /* uint32_t *InData_TBSCertificateLength, */&certificate_length_sub,
    /* uint32_t *InData_Signature,            */(uint32_t *) signature,
    /* uint32_t *InData_TBSCertificatesInfo,  */information,
    /* uint32_t length,                       */certificate_length_sub2,
    /* uint32_t *OutData_PubKey);             */encrypted_output_public_key);
}

/*******************************************************************************************************************//**
 * Generate encrypted pre-master secret.
 *
 * @param[out]    sce_pre_master_secret pre-master secret value for SCE.
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource needed
 *                                              by the processing routine was in use by another processing routine.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 *
 **********************************************************************************************************************/
fsp_err_t R_SCE_TLS_PreMasterSecretGenerateForRSA2048(uint32_t *sce_pre_master_secret)
{
    return R_SCE_TlsGeneratePreMasterSecretSub(sce_pre_master_secret);
}

/*******************************************************************************************************************//**
 * Generate encrypted master secret.
 *
 * @param[in]     select_cipher_suite    cipher suite type
 * @param[in]     sce_pre_master_secret  pre-master secret value for SCE.
 * @param[in]     client_random          random value reported ClientHello.
 * @param[in]     server_random          random value reported ServerHello.
 * @param[out]    sce_master_secret      master secret value with SCE-specific conversion.
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource needed
 *                                              by the processing routine was in use by another processing routine.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              An internal error occurred.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 *
 **********************************************************************************************************************/
fsp_err_t R_SCE_TLS_MasterSecretGenerate (uint32_t select_cipher_suite, uint32_t *sce_pre_master_secret,
        uint8_t *client_random, uint8_t *server_random, uint32_t *sce_master_secret)
{
    uint32_t cipher_suite_sub = 0;

    cipher_suite_sub = change_endian_long(select_cipher_suite);

    return R_SCE_TlsGenerateMasterSecretSub(&cipher_suite_sub, sce_pre_master_secret, 
            /* Casting uint32_t pointer is used for address. */
            (uint32_t *) (client_random), (uint32_t *) (server_random), sce_master_secret);

}

/*******************************************************************************************************************//**
 * Output the result encrypted pre-master secret with RSA 2048bit
 *
 * @param[in]     encrypted_public_key        public key data.
 * @param[in]     sce_pre_master_secret       pre-master secret value.
 * @param[out]    encrypted_pre_master_secret the value encrypted pre-master secret.
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource needed
 *                                              by the processing routine was in use by another processing routine.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              An internal error occurred.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 *
 **********************************************************************************************************************/
fsp_err_t R_SCE_TLS_PreMasterSecretEncryptWithRSA2048(uint32_t *encrypted_public_key,
        uint32_t *sce_pre_master_secret, uint8_t *encrypted_pre_master_secret)
{
    return R_SCE_TlsEncryptPreMasterSecretSub(encrypted_public_key, sce_pre_master_secret,
        /* Casting uint32_t pointer is used for address. */
        (uint32_t *) encrypted_pre_master_secret);
}

/*******************************************************************************************************************//**
 * Output various key information.
 *
 * @param[in]     select_cipher_suite       Key suite information number.
 * @param[in]     sce_master_secret         master secret value.
 * @param[in]     client_random             random value reported ClientHello.
 * @param[in]     server_random             random value reported ServerHello.
 * @param[in]     nonce_explicit            nonce value
 * @param[out]    client_mac_wrapped_key    the mac key during communication from client to server.
 * @param[out]    server_mac_wrapped_key    the mac key during communication from server to client.
 * @param[out]    client_crypto_wrapped_key the crypto key during communication from client to server.
 * @param[out]    server_crypto_wrapped_key the crypto key during communication from server to client.
 * @param[in]     client_initial_vector     not use.
 * @param[in]     server_initial_vector     not use.
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource needed
 *                                              by the processing routine was in use by another processing routine.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              An internal error occurred.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 *
 **********************************************************************************************************************/
fsp_err_t R_SCE_TLS_SessionKeyGenerate(uint32_t select_cipher_suite, uint32_t *sce_master_secret,
        uint8_t *client_random, uint8_t *server_random, uint8_t* nonce_explicit,
        sce_hmac_sha_wrapped_key_t *client_mac_wrapped_key, sce_hmac_sha_wrapped_key_t *server_mac_wrapped_key,
        sce_aes_wrapped_key_t *client_crypto_wrapped_key, sce_aes_wrapped_key_t *server_crypto_wrapped_key,
        uint8_t *client_initial_vector, uint8_t *server_initial_vector)
{
    FSP_PARAMETER_NOT_USED(client_initial_vector);
    FSP_PARAMETER_NOT_USED(server_initial_vector);

    fsp_err_t error_code = FSP_SUCCESS;
    uint32_t cipher_suite = 0;

    cipher_suite = change_endian_long(select_cipher_suite);

    /* Casting uint32_t pointer is used for address. */
    error_code = R_SCE_TlsGenerateSessionKeySub(
    /* uint32_t *InData_Sel_CipherSuite,            */&cipher_suite,
    /* uint32_t *InData_MasterSecret,               */sce_master_secret,
    /* uint32_t *InData_ClientRandom,               */(uint32_t *) (client_random),
    /* uint32_t *InData_ServerRandom,               */(uint32_t *) (server_random),
    /* uint32_t *InData_NonceExplicit,              */(uint32_t *) (nonce_explicit),
    /* uint32_t *OutData_ClientMACKeyOperationCode, */(uint32_t *) client_mac_wrapped_key->value,
    /* uint32_t *OutData_ServerMACKeyOperationCode, */(uint32_t *) server_mac_wrapped_key->value,
    /* uint32_t *OutData_ClientEncKeyOperationCode, */(uint32_t *) client_crypto_wrapped_key->value,
    /* uint32_t *OutData_ServerEncKeyOperationCode, */(uint32_t *) server_crypto_wrapped_key->value,
    /* uint32_t OutLen);                            */0);

    if (FSP_SUCCESS == error_code)
    {
        if (SCE_TLS_RSA_WITH_AES_128_CBC_SHA == select_cipher_suite)
        {
            client_mac_wrapped_key->type = SCE_KEY_INDEX_TYPE_HMAC_SHA1_FOR_TLS;
            server_mac_wrapped_key->type = SCE_KEY_INDEX_TYPE_HMAC_SHA1_FOR_TLS;
            client_crypto_wrapped_key->type = SCE_KEY_INDEX_TYPE_AES128_FOR_TLS;
            server_crypto_wrapped_key->type = SCE_KEY_INDEX_TYPE_AES128_FOR_TLS;
        }
        else if (SCE_TLS_RSA_WITH_AES_256_CBC_SHA == select_cipher_suite)
        {
            client_mac_wrapped_key->type = SCE_KEY_INDEX_TYPE_HMAC_SHA1_FOR_TLS;
            server_mac_wrapped_key->type = SCE_KEY_INDEX_TYPE_HMAC_SHA1_FOR_TLS;
            client_crypto_wrapped_key->type = SCE_KEY_INDEX_TYPE_AES256_FOR_TLS;
            server_crypto_wrapped_key->type = SCE_KEY_INDEX_TYPE_AES256_FOR_TLS;
        }
        else if (SCE_TLS_RSA_WITH_AES_256_CBC_SHA256 == select_cipher_suite)
        {
            client_mac_wrapped_key->type = SCE_KEY_INDEX_TYPE_HMAC_SHA256_FOR_TLS;
            server_mac_wrapped_key->type = SCE_KEY_INDEX_TYPE_HMAC_SHA256_FOR_TLS;
            client_crypto_wrapped_key->type = SCE_KEY_INDEX_TYPE_AES256_FOR_TLS;
            server_crypto_wrapped_key->type = SCE_KEY_INDEX_TYPE_AES256_FOR_TLS;
        }
        else
        {
            /* These 5 cases are intentionally combined. */
            /* SCE_TLS_RSA_WITH_AES_128_CBC_SHA256 */
            /* SCE_TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256 */
            /* SCE_TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA256 */
            /* SCE_TLS_ECDHE_ECDSA_WITH_AES_128_GCM_SHA256 */
            /* SCE_TLS_ECDHE_RSA_WITH_AES_128_GCM_SHA256 */
            if ((SCE_TLS_ECDHE_ECDSA_WITH_AES_128_GCM_SHA256 != select_cipher_suite) &&
                (SCE_TLS_ECDHE_RSA_WITH_AES_128_GCM_SHA256 != select_cipher_suite))
            {
                /* These 3 cases are intentionally combined. */
                /* SCE_TLS_RSA_WITH_AES_128_CBC_SHA256 */
                /* SCE_TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256 */
                /* SCE_TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA256 */
                client_mac_wrapped_key->type = SCE_KEY_INDEX_TYPE_HMAC_SHA256_FOR_TLS;
                server_mac_wrapped_key->type = SCE_KEY_INDEX_TYPE_HMAC_SHA256_FOR_TLS;
            }
            client_crypto_wrapped_key->type = SCE_KEY_INDEX_TYPE_AES128_FOR_TLS;
            server_crypto_wrapped_key->type = SCE_KEY_INDEX_TYPE_AES128_FOR_TLS;
        }
    }
    else
    {
        client_mac_wrapped_key->type = SCE_KEY_INDEX_TYPE_INVALID;
        server_mac_wrapped_key->type = SCE_KEY_INDEX_TYPE_INVALID;
        client_crypto_wrapped_key->type = SCE_KEY_INDEX_TYPE_INVALID;
        server_crypto_wrapped_key->type = SCE_KEY_INDEX_TYPE_INVALID;
    }
    return error_code;
}

/*******************************************************************************************************************//**
 * Generate verify data.
 *
 * @param[in]     select_verify_data Select Client/Server data.
 * @param[in]     sce_master_secret  master secret data.
 * @param[in]     hand_shake_hash    TLS hand shake message SHA256 HASH value.
 * @param[out]    verify_data        verify data.

 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource needed
 *                                              by the processing routine was in use by another processing routine.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              An internal error occurred.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 *
 **********************************************************************************************************************/
fsp_err_t R_SCE_TLS_VerifyDataGenerate(uint32_t select_verify_data, uint32_t *sce_master_secret,
        uint8_t *hand_shake_hash, uint8_t *verify_data)
{
    uint32_t tmp_select_verify_data = 0;

    tmp_select_verify_data = change_endian_long(select_verify_data);

    /* Casting uint32_t pointer is used for address. */
    return R_SCE_TlsGenerateVerifyDataSub(
    /* uint32_t *InData_Sel_VerifyData, */&tmp_select_verify_data,
    /* uint32_t *InData_MasterSecret,   */sce_master_secret,
    /* uint32_t *InData_HandShakeHash,  */(uint32_t *) (hand_shake_hash),
    /* uint32_t *OutData_VerifyData);   */(uint32_t *) (verify_data));
}

/*******************************************************************************************************************//**
 * Retrives ECDH public key.
 *
 * @param[in]     public_key_type                     key type
 * @param[in]     client_random                       random value reported ClientHello.
 * @param[in]     server_random                       random value reported ServerHello.
 * @param[in]     server_ephemeral_ecdh_public_key    Ephemeral ECDH public key from Server.
 * @param[in]     server_key_exchange_signature       Server Key Exchange sigunature.
 * @param[in]     encrypted_public_key                encrypted public key.
 * @param[out]    encrypted_ephemeral_ecdh_public_key encrypted Ephemeral ECDH public key.
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource needed
 *                                              by the processing routine was in use by another processing routine.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              An internal error occurred.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 *
 **********************************************************************************************************************/
fsp_err_t R_SCE_TLS_ServerKeyExchangeVerify(uint32_t public_key_type, uint8_t *client_random,
        uint8_t *server_random, uint8_t *server_ephemeral_ecdh_public_key, uint8_t *server_key_exchange_signature,
        uint32_t *encrypted_public_key, uint32_t *encrypted_ephemeral_ecdh_public_key)
{
    uint32_t tmp_public_key_type = 0;
    uint32_t tmp_compless_type = 0;

    tmp_public_key_type = change_endian_long(public_key_type);

    /* Casting uint32_t pointer is used for address. */
    return R_SCE_TlsServersEphemeralEcdhPublicKeyRetrievesSub(
    /* uint32_t *InData_Sel_PubKeyType,   */&tmp_public_key_type,
    /* uint32_t *InData_ClientRandom,     */(uint32_t*)client_random,
    /* uint32_t *InData_ServerRandom,     */(uint32_t*)server_random,
    /* uint32_t *InData_Sel_CompressType, */&tmp_compless_type,
    /* uint32_t *InData_SKE_Message,      */(uint32_t*)server_ephemeral_ecdh_public_key,
    /* uint32_t *InData_SKE_Signature,    */(uint32_t*)server_key_exchange_signature,
    /* uint32_t *InData_PubKey,           */encrypted_public_key,
    /* uint32_t *OutData_EphemeralPubKey  */encrypted_ephemeral_ecdh_public_key
    );
}

/*******************************************************************************************************************//**
 * Generate encrypted pre-master secret.
 *
 * @param[in]     encrypted_public_key     encrypted public key
 * @param[in]     tls_p256_ecc_wrapped_key P-256 ECC key index.
 * @param[out]    sce_pre_master_secret    encrypted pre-master secret value for SCE.
 *
 * @retval FSP_SUCCESS                          Normal termination
 * @retval FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource needed
 *                                              by the processing routine was in use by another processing routine.
 * @retval FSP_ERR_CRYPTO_SCE_FAIL              An internal error occurred.
 *
 * @note The pre-run state is SCE Enabled State.
 *       After the function runs the state transitions to SCE Enabled State.
 *
 **********************************************************************************************************************/
fsp_err_t R_SCE_TLS_PreMasterSecretGenerateForECC_secp256r1(uint32_t *encrypted_public_key,
    sce_tls_p256_ecc_wrapped_key_t *tls_p256_ecc_wrapped_key, uint32_t *sce_pre_master_secret)
{
    return R_SCE_TlsGeneratePreMasterSecretWithEccP256KeySub(
    /* uint32_t *InData_PubKey,               */encrypted_public_key,
    /* uint32_t *InData_KeyIndex,             */tls_p256_ecc_wrapped_key->value,
    /* uint32_t *OutData_PreMasterSecretIndex */sce_pre_master_secret
    );
}

/*******************************************************************************************************************//**
 * @} (end addtogroup SCE_PROTECTED)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/
