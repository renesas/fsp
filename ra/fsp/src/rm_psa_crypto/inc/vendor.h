/**
 *  vendor.h
 *
 *  This file contains definitions and functions for the vendor defined key format implementation.
 *
 */

#ifndef VENDOR_H
 #define VENDOR_H

 #if !defined(MBEDTLS_CONFIG_FILE)
  #include "mbedtls/config.h"
 #else
  #include MBEDTLS_CONFIG_FILE
 #endif

 #include <stddef.h>
 #include <stdint.h>

 #include "psa/crypto.h"

 #include "../library/psa_crypto_core.h"
 #include "../library/psa_crypto_invasive.h"
 #include "../library/psa_crypto_slot_management.h"
 #include "../library/psa_crypto_storage.h"
 #include "mbedtls/cipher.h"
 #include "psa/crypto_accel_driver.h"
 #include "psa/crypto_sizes.h"
 #include "psa/crypto_types.h"

 #include <assert.h>
 #include <stdlib.h>
 #include <string.h>
 #include "mbedtls/platform.h"
 #include "mbedtls/bignum.h"

 #include "rm_psa_crypto.h"

 #ifdef __cplusplus
extern "C"
{
 #endif

/* Functions used directly from mbedCrypto */
psa_status_t mbedtls_to_psa_error(int ret);
psa_status_t psa_finish_key_creation(psa_key_slot_t * slot, psa_se_drv_table_entry_t * driver, mbedtls_svc_key_id_t * key);
psa_status_t psa_internal_export_key(const psa_key_slot_t * slot,
                                     uint8_t              * data,
                                     size_t                 data_size,
                                     size_t               * data_length,
                                     int                    export_public_key);

/* Functions to support vendor defined format */
psa_status_t vendor_bitlength_to_raw_bitlength(psa_key_type_t type, size_t vendor_bits, size_t * raw_bits);

 #ifdef __cplusplus
}
 #endif

#endif                                 /* VENDOR_H */
