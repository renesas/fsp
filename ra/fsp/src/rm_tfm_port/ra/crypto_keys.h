/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef CRYPTO_KEYS_H_
 #define CRYPTO_KEYS_H_

 #include "psa/crypto_types.h"
 #include "psa/crypto_values.h"

 #ifdef __cplusplus
extern "C" {
 #endif

/* Set this to 32 for now since we only support SECP256R */
 #define MAX_IAK_BYTES    32U

 #define MAX_HUK_BYTES    32U

/** IAK definition */
typedef struct st_iak_data_t
{
    uint8_t          key[MAX_IAK_BYTES];
    uint32_t         key_size;
    psa_ecc_family_t curve_type;
} iak_data_t;

/** HUK definition. */
typedef struct st_huk_data_t
{
    uint8_t  key[MAX_HUK_BYTES];
    uint32_t key_size;
} huk_data_t;

 #ifdef __cplusplus
}
 #endif

#endif                                 /* CRYPTO_KEYS_H_ */
