/*
 * Copyright (c) 2018-2020, Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include <stddef.h>
#include <stdint.h>
#include "tfm_attest_hal.h"
#include "tfm_plat_boot_seed.h"
#include "tfm_plat_device_id.h"
#include "tfm_plat_otp.h"
#include "tfm_strnlen.h"
#include "tfm_common_config.h"
#include "region_defs.h"

static enum tfm_security_lifecycle_t map_otp_lcs_to_tfm_slc(enum plat_otp_lcs_t lcs) {
    switch (lcs) {
        case PLAT_OTP_LCS_ASSEMBLY_AND_TEST:
            return TFM_SLC_ASSEMBLY_AND_TEST;
        case PLAT_OTP_LCS_PSA_ROT_PROVISIONING:
            return TFM_SLC_PSA_ROT_PROVISIONING;
        case PLAT_OTP_LCS_SECURED:
            return TFM_SLC_SECURED;
        case PLAT_OTP_LCS_DECOMMISSIONED:
            return TFM_SLC_DECOMMISSIONED;
        case PLAT_OTP_LCS_UNKNOWN:
        default:
            return TFM_SLC_UNKNOWN;
    }
}

enum tfm_security_lifecycle_t tfm_attest_hal_get_security_lifecycle(void)
{
    enum plat_otp_lcs_t otp_lcs;
    enum tfm_plat_err_t err;

    err = tfm_plat_otp_read(PLAT_OTP_ID_LCS, sizeof(otp_lcs), (uint8_t*)&otp_lcs);
    if (err != TFM_PLAT_ERR_SUCCESS) {
        return TFM_SLC_UNKNOWN;
    }

    return map_otp_lcs_to_tfm_slc(otp_lcs);
}


enum tfm_plat_err_t
tfm_attest_hal_get_verification_service(uint32_t *size, uint8_t *buf)
{
    enum tfm_plat_err_t err;
    size_t otp_size;
    size_t copy_size;

    err = tfm_plat_otp_read(PLAT_OTP_ID_VERIFICATION_SERVICE_URL, *size, buf);
    if(err != TFM_PLAT_ERR_SUCCESS) {
        return err;
    }

    err =  tfm_plat_otp_get_size(PLAT_OTP_ID_VERIFICATION_SERVICE_URL, &otp_size);
    if(err != TFM_PLAT_ERR_SUCCESS) {
        return err;
    }

    /* Actually copied data is always the smaller */
    copy_size = *size < otp_size ? *size : otp_size;
    /* String content */
    *size = tfm_strnlen((char*)buf, copy_size);

    return TFM_PLAT_ERR_SUCCESS;
}

enum tfm_plat_err_t
tfm_attest_hal_get_profile_definition(uint32_t *size, uint8_t *buf)
{
    enum tfm_plat_err_t err;
    size_t otp_size;
    size_t copy_size;

    err = tfm_plat_otp_read(PLAT_OTP_ID_PROFILE_DEFINITION, *size, buf);
    if(err != TFM_PLAT_ERR_SUCCESS) {
        return err;
    }

    err =  tfm_plat_otp_get_size(PLAT_OTP_ID_PROFILE_DEFINITION, &otp_size);
    if(err != TFM_PLAT_ERR_SUCCESS) {
        return err;
    }

    /* Actually copied data is always the smaller */
    copy_size = *size < otp_size ? *size : otp_size;
    /* String content */
    *size = tfm_strnlen((char*)buf, copy_size);

    return TFM_PLAT_ERR_SUCCESS;
}

enum tfm_plat_err_t tfm_plat_get_boot_seed(uint32_t size, uint8_t *buf)
{
    uint32_t i;
    uint8_t *p_dst = buf;
    const uint8_t *p_src;

    if (size != BOOT_TFM_SHARED_SEED_SIZE) 
    {
        return TFM_PLAT_ERR_SYSTEM_ERR;
    }

    p_src = (const uint8_t *)BOOT_TFM_SHARED_SEED_BASE;

    for (i = size; i > 0; i--) 
    {
        *p_dst = *p_src;
        p_src++;
        p_dst++;
    }
    return TFM_PLAT_ERR_SUCCESS;
}

enum tfm_plat_err_t tfm_plat_get_implementation_id(uint32_t *size,
                                                   uint8_t  *buf)
{
    enum tfm_plat_err_t err;
    size_t otp_size;
    size_t copy_size;

    err = tfm_plat_otp_read(PLAT_OTP_ID_IMPLEMENTATION_ID, *size, buf);
    if(err != TFM_PLAT_ERR_SUCCESS) {
        return err;
    }

    err =  tfm_plat_otp_get_size(PLAT_OTP_ID_IMPLEMENTATION_ID, &otp_size);
    if(err != TFM_PLAT_ERR_SUCCESS) {
        return err;
    }

    /* Actually copied data is always the smaller */
    copy_size = *size < otp_size ? *size : otp_size;
    /* Binary data */
    *size = copy_size;

    return TFM_PLAT_ERR_SUCCESS;
}

enum tfm_plat_err_t tfm_plat_get_cert_ref(uint32_t *size, uint8_t *buf)
{
    enum tfm_plat_err_t err;
    size_t otp_size;
    size_t copy_size;

    err = tfm_plat_otp_read(PLAT_OTP_ID_CERT_REF, *size, buf);
    if(err != TFM_PLAT_ERR_SUCCESS) {
        return err;
    }

    err =  tfm_plat_otp_get_size(PLAT_OTP_ID_CERT_REF, &otp_size);
    if(err != TFM_PLAT_ERR_SUCCESS) {
        return err;
    }

    /* Actually copied data is always the smaller */
    copy_size = *size < otp_size ? *size : otp_size;
    /* String content */
    *size = tfm_strnlen((char*)buf, copy_size);

    return TFM_PLAT_ERR_SUCCESS;
}

enum tfm_plat_err_t tfm_attest_hal_get_platform_config(uint32_t *size,
                                                       uint8_t  *buf)
{
    uint32_t dummy_plat_config = 0xDEADBEEF;

    if (*size < sizeof(dummy_plat_config)) {
        return TFM_PLAT_ERR_SYSTEM_ERR;
    }

     memcpy(buf, &dummy_plat_config, sizeof(dummy_plat_config));
     *size = sizeof(dummy_plat_config);

    return TFM_PLAT_ERR_SUCCESS;
}

enum tfm_plat_err_t tfm_attest_hal_get_platform_hash_algo(uint32_t *size,
                                                          uint8_t *buf)
{
#ifdef MEASUREMENT_HASH_ALGO_NAME
    const char hash_algo[] = MEASUREMENT_HASH_ALGO_NAME;
#else
    const char hash_algo[] = "not-hash-extended";
#endif

    if (*size < sizeof(hash_algo) - 1) {
        return TFM_PLAT_ERR_SYSTEM_ERR;
    }

    /* Not including the null-terminator. */
     memcpy(buf, hash_algo, sizeof(hash_algo) - 1);
    *size = sizeof(hash_algo) - 1;

    return TFM_PLAT_ERR_SUCCESS;
}
