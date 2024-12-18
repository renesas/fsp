/*
 * Copyright (c) 2021, Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "tfm_plat_provisioning.h"

#include "cmsis_compiler.h"
#include "tfm_plat_otp.h"
#include "tfm_attest_hal.h"
#include "psa/crypto.h"
#include "tfm_spm_log.h"
#include "tfm_common_config.h"
#include "flash_otp_nv_counters_backend.h"
#include "Driver_Flash.h"


#ifdef TFM_DUMMY_PROVISIONING
#include "bootutil/sign_key.h"
#endif

#include <string.h>

#define INT2LE(A) (uint8_t)(A & 0xFF), (uint8_t )((A >> 8) & 0xFF),\
         (uint8_t )((A >> 16) & 0xFF), (uint8_t )((A >> 24) & 0xFF)

#define INT64NULL 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,  \
                  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,  \
                  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,  \
                  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,  \
                  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,  \
                  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,  \
                  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,  \
                  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0

extern ARM_DRIVER_FLASH FLASH_DEV_NAME;

#ifdef TFM_DUMMY_PROVISIONING

const struct flash_otp_nv_counters_region_t otp_rea_dummy_provision =
{
    .init_value = OTP_NV_COUNTERS_INITIALIZED,
    .boot_seed  =
    {
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7,
        0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF,
        0xB0, 0xB1, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7,
        0xB8, 0xB9, 0xBA, 0xBB, 0xBC, 0xBD, 0xBE, 0xBF,
    },
    .huk                      =
    {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
    },
    .iak                      =
    {
        0xA9, 0xB4, 0x54, 0xB2, 0x6D, 0x6F, 0x90, 0xA4,
        0xEA, 0x31, 0x19, 0x35, 0x64, 0xCB, 0xA9, 0x1F,
        0xEC, 0x6F, 0x9A, 0x00, 0x2A, 0x7D, 0xC0, 0x50,
        0x4B, 0x92, 0xA1, 0x93, 0x71, 0x34, 0x58, 0x5F
    },
    .iak_len  = {INT2LE(32)},
    .iak_type = {INT2LE(PSA_ECC_FAMILY_SECP_R1)},
    .iak_id   =
    {'r', 'e', 'n', 'e', 's', 'a',
     's',
     '.', 'f', \
     's', 'p'},
    .lcs                      = {INT2LE(PLAT_OTP_LCS_SECURED)},

    .implementation_id        =
    {
        0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA,
        0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB,
        0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC,
        0xDD, 0xDD, 0xDD, 0xDD, 0xDD, 0xDD, 0xDD, 0xDD,
    },
    .verification_service_url = "www.trustedfirmware.org",
    .profile_definition       = "PSA_IOT_PROFILE_1",

    /* Entropy seed */
    .entropy_seed             =
    {
        0x12, 0x13, 0x23, 0x34, 0x0a, 0x05, 0x89, 0x78,
        0xa3, 0x66, 0x8c, 0x0d, 0x97, 0x55, 0x53, 0xca,
        0xb5, 0x76, 0x18, 0x62, 0x29, 0xc6, 0xb6, 0x79,
        0x75, 0xc8, 0x5a, 0x8d, 0x9e, 0x11, 0x8f, 0x85,
        0xde, 0xc4, 0x5f, 0x66, 0x21, 0x52, 0xf9, 0x39,
        0xd9, 0x77, 0x93, 0x28, 0xb0, 0x5e, 0x02, 0xfa,
        0x58, 0xb4, 0x16, 0xc8, 0x0f, 0x38, 0x91, 0xbb,
        0x28, 0x17, 0xcd, 0x8a, 0xc9, 0x53, 0x72, 0x66,
    },

    .bl2_nv_counter_0 = {INT64NULL},
    .bl2_nv_counter_1 = {INT64NULL},
    .bl2_nv_counter_2 = {INT64NULL},

    .bl2_rotpk_0              =
    {
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    },
    .bl2_rotpk_1              =
    {
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    },

    .bl2_rotpk_2              =
    {
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    },
 #ifdef PLATFORM_DEFAULT_NV_COUNTERS
    .flash_nv_counters        = {0x0,0x0,0x0},
 #endif
};
#else
static struct flash_otp_nv_counters_region_t otp_rea_dummy_provision;
#endif /* TFM_DUMMY_PROVISIONING */

void tfm_plat_provisioning_check_for_dummy_keys (void)
{
    uint64_t iak_start;

    tfm_plat_otp_read(PLAT_OTP_ID_IAK, sizeof(iak_start), (uint8_t *) &iak_start);

    if (iak_start == 0xA4906F6DB254B4A9)
    {
        SPMLOG_ERRMSG("[WRN]\033[1;31m ");
        SPMLOG_ERRMSG("This device was provisioned with dummy keys. ");
        SPMLOG_ERRMSG("This device is \033[1;1mNOT SECURE");
        SPMLOG_ERRMSG("\033[0m\r\n");
    }

    memset(&iak_start, 0, sizeof(iak_start));
}

int tfm_plat_provisioning_is_required (void)
{
    enum tfm_plat_err_t err;
    enum plat_otp_lcs_t lcs;

    err = tfm_plat_otp_read(PLAT_OTP_ID_LCS, sizeof(lcs), (uint8_t *) &lcs);
    if (err != TFM_PLAT_ERR_SUCCESS)
    {
        return err;
    }

    return lcs == PLAT_OTP_LCS_ASSEMBLY_AND_TEST ||
           lcs == PLAT_OTP_LCS_PSA_ROT_PROVISIONING;
}

#ifdef TFM_DUMMY_PROVISIONING
enum tfm_plat_err_t tfm_renesas_validate_provisioning (void)
{
    enum tfm_plat_err_t err;
    int32_t             result;
    uint8_t             key_hash[PSA_HASH_LENGTH(PSA_ALG_SHA_256)] = {0};

    err = read_otp_nv_counters_flash(offsetof(struct flash_otp_nv_counters_region_t, bl2_rotpk_0), key_hash, sizeof(key_hash));
    
    if (err != TFM_PLAT_ERR_SUCCESS)
    {
        return err;
    }

    result = psa_hash_compare(PSA_ALG_SHA_256, bootutil_keys[0].key, *(bootutil_keys[0].len), key_hash, sizeof(key_hash));

    if(PSA_SUCCESS != result)
    {
        return TFM_PLAT_ERR_SYSTEM_ERR;
    }
    
    return TFM_PLAT_ERR_SUCCESS;
}
#endif

static enum tfm_plat_err_t fsp_example_provision_rot (void)
{
    enum tfm_plat_err_t err;
    uint32_t offset = 0U;
    psa_algorithm_t      alg       = PSA_ALG_SHA_256;
    psa_hash_operation_t operation = {0};
    uint8_t              key_hash[PSA_HASH_LENGTH(PSA_ALG_SHA_256)] = {0};
    size_t               hash_length = 0;
    int32_t              result;

    err = write_otp_nv_counters_flash(offset, &otp_rea_dummy_provision,
                                         sizeof(otp_rea_dummy_provision));
#if defined(BL2) && defined(TFM_DUMMY_PROVISIONING)
    result = psa_hash_setup(&operation, alg);

    result = psa_hash_update(&operation, bootutil_keys[0].key, *(bootutil_keys[0].len));

    result = psa_hash_finish(&operation, key_hash, sizeof(key_hash), &hash_length);

    if(PSA_SUCCESS != result)
    {
        return TFM_PLAT_ERR_SYSTEM_ERR;
    }

    err = write_otp_nv_counters_flash(offsetof(struct flash_otp_nv_counters_region_t, bl2_rotpk_0), key_hash, sizeof(key_hash));
#endif

    return err;
}

enum tfm_plat_err_t tfm_plat_provisioning_perform (void)
{
    enum tfm_plat_err_t err;
    enum plat_otp_lcs_t lcs;

    err = tfm_plat_otp_read(PLAT_OTP_ID_LCS, sizeof(lcs), (uint8_t *) &lcs);
    if (err != TFM_PLAT_ERR_SUCCESS)
    {
        return err;
    }

    SPMLOG_INFMSG("[INF] Beginning TF-M provisioning\r\n");

#ifdef TFM_DUMMY_PROVISIONING
    SPMLOG_ERRMSG("[WRN]\033[1;31m ");
    SPMLOG_ERRMSG("TFM_DUMMY_PROVISIONING is not suitable for production! ");
    SPMLOG_ERRMSG("This device is \033[1;1mNOT SECURE");
    SPMLOG_ERRMSG("\033[0m\r\n");
#endif                                 /* TFM_DUMMY_PROVISIONING */

    err = fsp_example_provision_rot();
    if (err != TFM_PLAT_ERR_SUCCESS)
    {
        return err;
    }

    return TFM_PLAT_ERR_SUCCESS;
}
