/*
 * SPDX-License-Identifier: Apache-2.0
 *
 * Copyright (c) 2017-2018 Linaro LTD
 * Copyright (c) 2017-2019 JUUL Labs
 * Copyright (c) 2020 Arm Limited
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
#ifdef MCUBOOT_SIGN_RSA
 #if defined MCUBOOT_USE_USER_DEFINED_CRYPTO_STACK
  #include "bootutil/sign_key.h"
  #include "bootutil/crypto/sha256.h"

  #include "bootutil_priv.h"
  #include "bootutil/fault_injection_hardening.h"

  #if (MCUBOOT_SIGN_RSA_LEN == 2048)
static sce_rsa2048_public_wrapped_key_t rsa_public_key_installed;
  #elif (MCUBOOT_SIGN_RSA_LEN == 3072)
static sce_rsa3072_public_wrapped_key_t rsa_public_key_installed;
  #endif

/*
 * Constants for this particular constrained implementation of
 * RSA-PSS.  In particular, we support RSA 2048, with a SHA256 hash,
 * and a 32-byte salt.  A signature with different parameters will be
 * rejected as invalid.
 */

/* The size, in octets, of the message. */
#define PSS_EMLEN (MCUBOOT_SIGN_RSA_LEN / 8)

/* The size of the hash function.  For SHA256, this is 32 bytes. */
#define PSS_HLEN 32

/* Size of the salt, should be fixed. */
#define PSS_SLEN 32

/* The length of the mask: emLen - hLen - 1. */
#define PSS_MASK_LEN (PSS_EMLEN - PSS_HLEN - 1)

#define PSS_HASH_OFFSET PSS_MASK_LEN

/* For the mask itself, how many bytes should be all zeros. */
#define PSS_MASK_ZERO_COUNT (PSS_MASK_LEN - PSS_SLEN - 1)
#define PSS_MASK_ONE_POS   PSS_MASK_ZERO_COUNT

/* Where the salt starts. */
#define PSS_MASK_SALT_POS   (PSS_MASK_ONE_POS + 1)

static const uint8_t pss_zeros[8] = {0};

typedef fsp_err_t (* r_sce_rsa_modular_exponent_encrypt_private_t)(uint32_t * InData_KeyIndex, uint32_t * InData_Text,
                                                                   uint32_t * OutData_Text);
r_sce_rsa_modular_exponent_encrypt_private_t p_rsa_modular_exponent_encrypt;

extern fsp_err_t R_SCE_Rsa2048ModularExponentEncryptPrivate(uint32_t * InData_KeyIndex,
                                                            uint32_t * InData_Text,
                                                            uint32_t * OutData_Text);
extern fsp_err_t R_SCE_Rsa3072ModularExponentEncryptPrivate(uint32_t * InData_KeyIndex,
                                                            uint32_t * InData_Text,
                                                            uint32_t * OutData_Text);

/*
 * Compute the RSA-PSS mask-generation function, MGF1.  Assumptions
 * are that the mask length will be less than 256 * PSS_HLEN, and
 * therefore we never need to increment anything other than the low
 * byte of the counter.
 *
 * This is described in PKCS#1, B.2.1.
 */
static void
pss_mgf1(uint8_t *mask, const uint8_t *hash)
{
    bootutil_sha256_context ctx;
    uint8_t counter[4] = { 0, 0, 0, 0 };
    uint8_t htmp[PSS_HLEN];
    int count = PSS_MASK_LEN;
    int bytes;

    while (count > 0) {
        bootutil_sha256_init(&ctx);
        bootutil_sha256_update(&ctx, hash, PSS_HLEN);
        bootutil_sha256_update(&ctx, counter, 4);
        bootutil_sha256_finish(&ctx, htmp);

        counter[3]++;

        bytes = PSS_HLEN;
        if (bytes > count)
            bytes = count;

        memcpy(mask, htmp, (size_t)bytes);
        mask += bytes;
        count -= bytes;
    }

    bootutil_sha256_drop(&ctx);
}

/*
 * Validate an RSA signature, using RSA-PSS, as described in PKCS #1
 * v2.2, section 9.1.2, with many parameters required to have fixed
 * values.
 */
static fih_int
sce9_bootutil_cmp_rsasig(uint8_t * pub_key, uint8_t *hash, uint32_t hlen,
  uint8_t *sig)
{
    bootutil_sha256_context shactx;
    uint8_t em[PSS_EMLEN];
    uint8_t db_mask[PSS_MASK_LEN];
    uint8_t h2[PSS_HLEN];
    int i;
    int rc = 0;
    fih_int fih_rc = FIH_FAILURE;
    SCE_KEY_INDEX_TYPE key_type = SCE_KEY_INDEX_TYPE_INVALID;

  #if (MCUBOOT_SIGN_RSA_LEN == 2048)
    p_rsa_modular_exponent_encrypt = R_SCE_Rsa2048ModularExponentEncryptPrivate;
    key_type = SCE_KEY_INDEX_TYPE_RSA2048_PUBLIC;
  #elif (MCUBOOT_SIGN_RSA_LEN == 3072)
    p_rsa_modular_exponent_encrypt = R_SCE_Rsa3072ModularExponentEncryptPrivate;
    key_type = SCE_KEY_INDEX_TYPE_RSA3072_PUBLIC;
  #endif

    if (hlen != PSS_HLEN) {
        rc = -1;
        goto out;
    }
    sce_rsa_byte_data_t local_data;
    sce_rsa_byte_data_t local_cipher;
    local_data.pdata       = sig;
    local_data.data_length = MCUBOOT_SIGN_RSA_LEN;

    local_cipher.pdata       = em;
    local_cipher.data_length = sizeof(em);

    memcpy((uint8_t *) &rsa_public_key_installed.value, pub_key, sizeof(rsa_public_key_installed.value));
    rsa_public_key_installed.type = key_type;
    if (p_rsa_modular_exponent_encrypt((uint32_t *) &rsa_public_key_installed.value, (uint32_t *) local_data.pdata,
                                       (uint32_t *) local_cipher.pdata))
    {
        rc = -1;
        goto out;
    }

    /*
     * PKCS #1 v2.2, 9.1.2 EMSA-PSS-Verify
     *
     * emBits is 2048
     * emLen = ceil(emBits/8) = 256
     *
     * The salt length is not known at the beginning.
     */

    /* Step 1.  The message is constrained by the address space of a
     * 32-bit processor, which is far less than the 2^61-1 limit of
     * SHA-256.
     */

    /* Step 2.  mHash is passed in as 'hash', with hLen the hlen
     * argument. */

    /* Step 3.  if emLen < hLen + sLen + 2, inconsistent and stop.
     * The salt length is not known at this point.
     */

    /* Step 4.  If the rightmost octet of EM does have the value
     * 0xbc, output inconsistent and stop.
     */
    if (em[PSS_EMLEN - 1] != 0xbc) {
        rc = -1;
        goto out;
    }

    /* Step 5.  Let maskedDB be the leftmost emLen - hLen - 1 octets
     * of EM, and H be the next hLen octets.
     *
     * maskedDB is then the first 256 - 32 - 1 = 0-222
     * H is 32 bytes 223-254
     */

    /* Step 6.  If the leftmost 8emLen - emBits bits of the leftmost
     * octet in maskedDB are not all equal to zero, output
     * inconsistent and stop.
     *
     * 8emLen - emBits is zero, so there is nothing to test here.
     */

    /* Step 7.  let dbMask = MGF(H, emLen - hLen - 1). */
    pss_mgf1(db_mask, &em[PSS_HASH_OFFSET]);

    /* Step 8.  let DB = maskedDB xor dbMask.
     * To avoid needing an additional buffer, store the 'db' in the
     * same buffer as db_mask.  From now, to the end of this function,
     * db_mask refers to the unmasked 'db'. */
    for (i = 0; i < PSS_MASK_LEN; i++) {
        db_mask[i] ^= em[i];
    }

    /* Step 9.  Set the leftmost 8emLen - emBits bits of the leftmost
     * octet in DB to zero.
     * pycrypto seems to always make the emBits 2047, so we need to
     * clear the top bit. */
    db_mask[0] &= 0x7F;

    /* Step 10.  If the emLen - hLen - sLen - 2 leftmost octets of DB
     * are not zero or if the octet at position emLen - hLen - sLen -
     * 1 (the leftmost position is "position 1") does not have
     * hexadecimal value 0x01, output "inconsistent" and stop. */
    for (i = 0; i < PSS_MASK_ZERO_COUNT; i++) {
        if (db_mask[i] != 0) {
            rc = -1;
            goto out;
        }
    }

    if (db_mask[PSS_MASK_ONE_POS] != 1) {
        rc = -1;
        goto out;
    }

    /* Step 11. Let salt be the last sLen octets of DB */

    /* Step 12.  Let M' = 0x00 00 00 00 00 00 00 00 || mHash || salt; */

    /* Step 13.  Let H' = Hash(M') */
    bootutil_sha256_init(&shactx);
    bootutil_sha256_update(&shactx, pss_zeros, 8);
    bootutil_sha256_update(&shactx, hash, PSS_HLEN);
    bootutil_sha256_update(&shactx, &db_mask[PSS_MASK_SALT_POS], PSS_SLEN);
    bootutil_sha256_finish(&shactx, h2);
    bootutil_sha256_drop(&shactx);

    /* Step 14.  If H = H', output "consistent".  Otherwise, output
     * "inconsistent". */
    FIH_CALL(boot_fih_memequal, fih_rc, h2, &em[PSS_HASH_OFFSET], PSS_HLEN);

out:
    if (rc) {
        fih_rc = fih_int_encode(rc);
    }

    FIH_RET(fih_rc);
}

fih_int
bootutil_verify_sig(uint8_t *hash, uint32_t hlen, uint8_t *sig, size_t slen,
  uint8_t key_id)
{
    fih_int fih_rc = FIH_FAILURE;
    uint8_t * pubkey;

    if (slen != RM_MCUBOOT_PORT_BITS_TO_BYTES(MCUBOOT_SIGN_RSA_LEN))
    {
        goto out;
    }

    pubkey = (uint8_t *) bootutil_keys_wrapped[key_id].key;
    FIH_CALL(sce9_bootutil_cmp_rsasig, fih_rc, pubkey, hash, hlen, sig);

out:
    FIH_RET(fih_rc);
}

 #endif                                /* MCUBOOT_USE_USER_DEFINED_CRYPTO_STACK */
#endif                                 /* MCUBOOT_SIGN_RSA */
