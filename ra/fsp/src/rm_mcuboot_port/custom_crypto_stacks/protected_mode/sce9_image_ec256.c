/*
 * SPDX-License-Identifier: Apache-2.0
 *
 * Copyright (c) 2016-2019 JUUL Labs
 * Copyright (c) 2017 Linaro LTD
 *
 * Original license:
 *
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#include <string.h>

#include "mcuboot_config/mcuboot_config.h"
#include "sce9_keys.h"

#ifdef MCUBOOT_SIGN_EC256

 #if defined MCUBOOT_USE_USER_DEFINED_CRYPTO_STACK
  #include "mbedtls/build_info.h"
  #include "bootutil/sign_key.h"

  #include "mbedtls/oid.h"
  #include "mbedtls/asn1.h"
  #include "bootutil/crypto/ecdsa_p256.h"
  #include "bootutil_priv.h"
  #include "sce9_ecdsa_p256.h"

/*
 * Declaring these like this adds NULL termination.
 */
static const uint8_t ec_pubkey_oid[] = MBEDTLS_OID_EC_ALG_UNRESTRICTED;
static const uint8_t ec_secp256r1_oid[] = MBEDTLS_OID_EC_GRP_SECP256R1;

/** Aligned buffers to be used if the input data is unaligned since the SCE procedures require 32 bit aligned buffers. */
static uint32_t aligned_sig[BOOTUTIL_CRYPTO_ECDSA_P256_SIGNATURE_SIZE_BYTES/4] = {0};
static uint32_t aligned_hash[BOOTUTIL_CRYPTO_SHA256_DIGEST_SIZE_BYTES/4] = {0};
static uint32_t aligned_pk[MCUBOOT_SCE9_ECC_PUBLIC_KEY_IDX_SIZE_BYTES/4] = {0};

static int bootutil_ecdsa_p256_verify (bootutil_ecdsa_p256_context * ctx,
                                              const uint8_t               * pk,
                                              const uint8_t               * hash,
                                              const uint8_t               * sig)
{
    (void) ctx;
    fsp_err_t fsp_err = FSP_SUCCESS;
    uint8_t * p_pk = (uint8_t *) pk; 
    uint8_t * p_hash = (uint8_t *) hash;
    uint8_t * p_sig = (uint8_t *) sig;

    if (MCUBOOT_CHECK_32BIT_UNALIGNED((uint32_t) pk))
    {
        memcpy(aligned_pk, pk, MCUBOOT_SCE9_ECC_PUBLIC_KEY_IDX_SIZE_BYTES);
        p_pk = (uint8_t *) aligned_pk;
    }
    if (MCUBOOT_CHECK_32BIT_UNALIGNED((uint32_t) hash))
    {
        memcpy(aligned_hash, hash, BOOTUTIL_CRYPTO_SHA256_DIGEST_SIZE_BYTES);
        p_hash = (uint8_t *) aligned_hash;
    }
    if (MCUBOOT_CHECK_32BIT_UNALIGNED((uint32_t) sig))
    {
        memcpy(aligned_sig, sig, BOOTUTIL_CRYPTO_ECDSA_P256_SIGNATURE_SIZE_BYTES);
        p_sig = (uint8_t *) aligned_sig;
    }

    fsp_err = R_SCE_EcdsaNistP256SignatureVerificationSub((uint32_t *) p_pk, (uint32_t *) p_hash, (uint32_t *) p_sig);

    if (fsp_err != FSP_SUCCESS)
    {
        return -1;
    }

    return 0;
}
/*
 * Parse the public key used for signing.
 */
static int
bootutil_import_key(uint8_t **cp, uint8_t *end)
{
    size_t len;
    mbedtls_asn1_buf alg;
    mbedtls_asn1_buf param;

    if (mbedtls_asn1_get_tag(cp, end, &len,
        MBEDTLS_ASN1_CONSTRUCTED | MBEDTLS_ASN1_SEQUENCE)) {
        return -1;
    }
    end = *cp + len;

    /* ECParameters (RFC5480) */
    if (mbedtls_asn1_get_alg(cp, end, &alg, &param)) {
        return -2;
    }
    /* id-ecPublicKey (RFC5480) */
    if (alg.len != sizeof(ec_pubkey_oid) - 1 ||
        memcmp(alg.p, ec_pubkey_oid, sizeof(ec_pubkey_oid) - 1)) {
        return -3;
    }
    /* namedCurve (RFC5480) */
    if (param.len != sizeof(ec_secp256r1_oid) - 1 ||
        memcmp(param.p, ec_secp256r1_oid, sizeof(ec_secp256r1_oid) - 1)) {
        return -4;
    }
    /* ECPoint (RFC5480) */
    if (mbedtls_asn1_get_bitstring_null(cp, end, &len)) {
        return -6;
    }
    if (*cp + len != end) {
        return -7;
    }

    if (len != 2 * NUM_ECC_BYTES + 1) {
        return -8;
    }
    /* Is uncompressed? */
    if (*cp[0] != 0x04) {
        return -9;
    }

    (*cp)++;

    return 0;
}

/*
 * cp points to ASN1 string containing an integer.
 * Verify the tag, and that the length is 32 bytes.
 */
static int
bootutil_read_bigint(uint8_t i[NUM_ECC_BYTES], uint8_t **cp, uint8_t *end)
{
    size_t len;

    if (mbedtls_asn1_get_tag(cp, end, &len, MBEDTLS_ASN1_INTEGER)) {
        return -3;
    }

    if (len >= NUM_ECC_BYTES) {
        memcpy(i, *cp + len - NUM_ECC_BYTES, NUM_ECC_BYTES);
    } else {
        memset(i, 0, NUM_ECC_BYTES - len);
        memcpy(i + NUM_ECC_BYTES - len, *cp, len);
    }
    *cp += len;
    return 0;
}

/*
 * Read in signature. Signature has r and s encoded as integers.
 */
static int
bootutil_decode_sig(uint8_t signature[NUM_ECC_BYTES * 2], uint8_t *cp, uint8_t *end)
{
    int rc;
    size_t len;

    rc = mbedtls_asn1_get_tag(&cp, end, &len,
                              MBEDTLS_ASN1_CONSTRUCTED | MBEDTLS_ASN1_SEQUENCE);
    if (rc) {
        return -1;
    }
    if (cp + len > end) {
        return -2;
    }

    rc = bootutil_read_bigint(signature, &cp, end);
    if (rc) {
        return -3;
    }
    rc = bootutil_read_bigint(signature + NUM_ECC_BYTES, &cp, end);
    if (rc) {
        return -4;
    }
    return 0;
}

int
bootutil_verify_sig(uint8_t *hash, uint32_t hlen, uint8_t *sig, size_t slen,
  uint8_t key_id)
{
    int rc;
    bootutil_ecdsa_p256_context ctx;
    uint8_t *pubkey;
    uint8_t *end;

    uint8_t signature[2 * NUM_ECC_BYTES];
    mcb_sce_ecc_public_wrapped_key_t public_key_installed;

    pubkey = (uint8_t *)bootutil_keys[key_id].key;
    end = pubkey + *bootutil_keys[key_id].len;

    rc = bootutil_import_key(&pubkey, end);
    if (rc) {
        return -1;
    }

    rc = bootutil_decode_sig(signature, sig, sig + slen);
    if (rc) {
        return -1;
    }

    /* The key_id passed to this function is for a key from bootutil_keys[] and its hash has already been validated.
     * Since the imgtool.py does not handle the hash for the wrapped public key, we compare the public key portion of the
     * wrappedkey from bootutil_keys_wrapped[] with the key from bootutil_keys[] and if both are the same, then we use the
     * key from bootutil_keys_wrapped[] to perform the verification using the protected mode procedures. */
    memcpy((uint8_t *) &public_key_installed.value,
           (uint8_t *) bootutil_keys_wrapped[key_id].key,
           MCUBOOT_SCE9_ECC_PUBLIC_KEY_IDX_SIZE_BYTES);
    if (memcmp(&public_key_installed.value.key_q, pubkey, 2 * NUM_ECC_BYTES))
    {
        return -1;
    }
    /*
     * This is simplified, as the hash length is also 32 bytes.
     */
    if (hlen != NUM_ECC_BYTES) {
        return -1;
    }

    bootutil_ecdsa_p256_init(&ctx);
    rc = bootutil_ecdsa_p256_verify(&ctx, (uint8_t*)&public_key_installed.value, hash, signature);
    bootutil_ecdsa_p256_drop(&ctx);

    return rc;
}

 #endif /* MCUBOOT_USE_USER_DEFINED_CRYPTO_STACK */
#endif /* MCUBOOT_SIGN_EC256 */
