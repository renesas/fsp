/**
 *  aes_alt.h
 *
 *  This file contains AES definitions and functions for the alternate implementation.
 *
 */

#ifndef AES_VENDOR_H
 #define AES_VENDOR_H

 #if !defined(MBEDTLS_CONFIG_FILE)
  #include "mbedtls/config.h"
 #else
  #include MBEDTLS_CONFIG_FILE
 #endif

 #include <stddef.h>
 #include <stdint.h>

 #include "vendor.h"
 #include "mbedtls/aes.h"
 #include "hw_sce_aes_private.h"
 #ifdef __cplusplus
extern "C"
{
 #endif

 #define PSA_AES_BITS_VENDOR_RAW(bit_length)                                             \
    ((bit_length) == SIZE_AES_128BIT_KEYLEN_BITS ? SIZE_AES_128BIT_KEYLEN_BITS :         \
     (bit_length) == SIZE_AES_128BIT_KEYLEN_BITS_WRAPPED ? SIZE_AES_128BIT_KEYLEN_BITS : \
     (bit_length) == SIZE_AES_192BIT_KEYLEN_BITS ? SIZE_AES_192BIT_KEYLEN_BITS :         \
     (bit_length) == SIZE_AES_192BIT_KEYLEN_BITS_WRAPPED ? SIZE_AES_192BIT_KEYLEN_BITS : \
     (bit_length) == SIZE_AES_256BIT_KEYLEN_BITS ? SIZE_AES_256BIT_KEYLEN_BITS :         \
     (bit_length) == SIZE_AES_256BIT_KEYLEN_BITS_WRAPPED ? SIZE_AES_256BIT_KEYLEN_BITS : \
     0)

const mbedtls_cipher_info_t * mbedtls_cipher_info_from_psa(psa_algorithm_t       alg,
                                                           psa_key_type_t        key_type,
                                                           size_t                key_bits,
                                                           mbedtls_cipher_id_t * cipher_id);

psa_status_t prepare_raw_data_slot_vendor(psa_key_type_t type, size_t bits, struct key_data * key);

 #ifdef __cplusplus
}
 #endif

#endif                                 /* AES_VENDOR_H */
