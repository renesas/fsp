#include "common.h"

#if defined(MBEDTLS_MLKEM_C)

#include "mbedtls/mlkem.h"
#include "mbedtls/threading.h"
#include "mbedtls/platform_util.h"
#include "mbedtls/error.h"
#include "psa/crypto.h"

#include <string.h>

#include "mbedtls/platform.h"
#include "r_pqc_api.h"
#include "r_sha_api.h"

/* The addition of `PQC_SIZE_MLKEM1024_ENCAPKEY` here is to accomodate the addition of the encapsulation key in PQC-Lib needed for key import/export */
#define PQC_BUF_BYTESIZE    (PQC_BUFSIZE_USECASE_ALL+PQC_SIZE_MLKEM1024_ENCAPKEY)
#define PQC_SHA_BYTESIZE    (232U)
#define PQC_MLKEM_DKD_LEN_CALC_VAL      (0xCU)
#define PQC_MLKEM_N                     (256U)
#define PQC_MLKEM_512_ENCAPS_POS        ((PQC_MLKEM_DKD_LEN_CALC_VAL * 2 * PQC_MLKEM_N) / 8U) /* k=2 */
#define PQC_MLKEM_768_ENCAPS_POS        ((PQC_MLKEM_DKD_LEN_CALC_VAL * 3 * PQC_MLKEM_N) / 8U) /* k=3 */
#define PQC_MLKEM_1024_ENCAPS_POS       ((PQC_MLKEM_DKD_LEN_CALC_VAL * 4 * PQC_MLKEM_N) / 8U) /* k=4 */ 
#define PSA_TO_PQC_RET(status) ((PSA_SUCCESS == (status)) ? PQC_RET_OK : PQC_RET_INTERNALERR)

static uint32_t pqc_buf[PQC_BUF_BYTESIZE / 4];
static uint32_t sha_buf[PQC_SHA_BYTESIZE / 4];

#if defined(MBEDTLS_SHA3_C) 
typedef struct pqc_hash_ctx
{
    psa_hash_operation_t hash_operation;
    psa_algorithm_t alg;
    size_t hash_buf_len;

} pqc_hash_ctx_t;
#endif /* MBEDTLS_SHA3_C */

st_pqc_hash_t      hash_info_sha3_256;
st_pqc_hash_t      hash_info_sha3_512;
st_pqc_hash_t      hash_info_shake128;
st_pqc_hash_t      hash_info_shake256;
#if defined(MBEDTLS_SHA3_C) 
pqc_hash_ctx_t       ctx_sw_sha3_256;
pqc_hash_ctx_t       ctx_sw_sha3_512;
#else
st_sha_ctx_t       ctx_sw_sha3_256;
st_sha_ctx_t       ctx_sw_sha3_512;
#endif /* MBEDTLS_SHA3_C */
st_sha_ctx_t       ctx_sw_shake128;
st_sha_ctx_t       ctx_sw_shake256; 

static void pqc_initialize_hash(st_pqc_mlkem_ctx_t * ctx, mbedtls_mlkem_bits_t bits);
#if defined(MBEDTLS_SHA3_C) 
uint32_t pqc_sha3_accel_init (void * const p_hash_ctx);
uint32_t pqc_sha3_accel_update (void * const p_hash_ctx,
                                const uint32_t * const p_data,
                                const uint32_t data_len);
uint32_t pqc_sha3_accel_final (void * const p_hash_ctx,
                                uint32_t * const p_md,
                                uint32_t * const p_md_len);
#endif /* MBEDTLS_SHA3_C */
uint32_t pqc_sha3_internal_init (void * const p_hash_ctx);
uint32_t pqc_sha3_internal_update (void * const p_hash_ctx,
                                const uint32_t * const p_data,
                                const uint32_t data_len);
uint32_t pqc_sha3_internal_final (void * const p_hash_ctx,
                                uint32_t * const p_md,
                                uint32_t * const p_md_len);
static int mbedtls_mlkem_get_ek_from_decaps_key(const mbedtls_mlkem_bits_t bits,
                                                const mbedtls_mlkem_data_t * const p_decaps_key,
                                                mbedtls_mlkem_data_t * p_encaps_key);

void pqc_initialize_hash(st_pqc_mlkem_ctx_t * ctx, mbedtls_mlkem_bits_t bits)
{

    if (ctx == NULL) {
        return;
    }

    switch (bits)
    {
        case MBEDTLS_MLKEM_512:
        {
            ctx->algo_params = PQC_ALGO_MLKEM512;
            break;
        }
        case MBEDTLS_MLKEM_768:
        {
            ctx->algo_params = PQC_ALGO_MLKEM768;
            break;
        }
        case MBEDTLS_MLKEM_1024:
        {
            ctx->algo_params = PQC_ALGO_MLKEM1024;
            break;
        }
        default:
        {
            return;
        }
    }

    ctx->p_buf = pqc_buf;

    ctx->p_hash_info_sha3_256    = &hash_info_sha3_256;
    ctx->p_hash_info_sha3_512    = &hash_info_sha3_512;
    ctx->p_hash_info_shake128    = &hash_info_shake128;
    ctx->p_hash_info_shake256    = &hash_info_shake256;

#if defined(MBEDTLS_SHA3_C) 
    ctx_sw_sha3_256.alg                 = PSA_ALG_SHA3_256;
    ctx_sw_sha3_512.alg                 = PSA_ALG_SHA3_512;
#else
    ctx_sw_sha3_256.algo_opt            = SHA_ALGO_SHA3_256;
    ctx_sw_sha3_256.p_buf               = sha_buf;
    ctx_sw_sha3_512.algo_opt            = SHA_ALGO_SHA3_512;
    ctx_sw_sha3_512.p_buf               = sha_buf;
#endif /* MBEDTLS_SHA3_C */
    ctx_sw_shake128.algo_opt            = SHA_ALGO_SHAKE128;
    ctx_sw_shake128.p_buf               = sha_buf;
    ctx_sw_shake256.algo_opt            = SHA_ALGO_SHAKE256;
    ctx_sw_shake256.p_buf               = sha_buf;

#if defined(MBEDTLS_SHA3_C) 
    hash_info_sha3_256.p_hash_ctx               = &ctx_sw_sha3_256;
    hash_info_sha3_256.p_hash_init_api          = pqc_sha3_accel_init;
    hash_info_sha3_256.p_hash_update_api        = pqc_sha3_accel_update;
    hash_info_sha3_256.p_hash_final_api         = pqc_sha3_accel_final;

    hash_info_sha3_512.p_hash_ctx               = &ctx_sw_sha3_512;
    hash_info_sha3_512.p_hash_init_api          = pqc_sha3_accel_init;
    hash_info_sha3_512.p_hash_update_api        = pqc_sha3_accel_update;
    hash_info_sha3_512.p_hash_final_api         = pqc_sha3_accel_final;
#else
    hash_info_sha3_256.p_hash_ctx               = &ctx_sw_sha3_256;
    hash_info_sha3_256.p_hash_init_api          = pqc_sha3_internal_init;
    hash_info_sha3_256.p_hash_update_api        = pqc_sha3_internal_update;
    hash_info_sha3_256.p_hash_final_api         = pqc_sha3_internal_final;

    hash_info_sha3_512.p_hash_ctx               = &ctx_sw_sha3_512;
    hash_info_sha3_512.p_hash_init_api          = pqc_sha3_internal_init;
    hash_info_sha3_512.p_hash_update_api        = pqc_sha3_internal_update;
    hash_info_sha3_512.p_hash_final_api         = pqc_sha3_internal_final;
#endif /* MBEDTLS_SHA3_C */

    hash_info_shake128.p_hash_ctx               = &ctx_sw_shake128;
    hash_info_shake128.p_hash_init_api          = pqc_sha3_internal_init;
    hash_info_shake128.p_hash_update_api        = pqc_sha3_internal_update;
    hash_info_shake128.p_hash_final_api         = pqc_sha3_internal_final;

    hash_info_shake256.p_hash_ctx               = &ctx_sw_shake256;
    hash_info_shake256.p_hash_init_api          = pqc_sha3_internal_init;
    hash_info_shake256.p_hash_update_api        = pqc_sha3_internal_update;
    hash_info_shake256.p_hash_final_api         = pqc_sha3_internal_final;
}

#if defined(MBEDTLS_SHA3_C) 
uint32_t pqc_sha3_accel_init (void * const p_hash_ctx)
{
    pqc_hash_ctx_t *ctx = (pqc_hash_ctx_t*)p_hash_ctx;
    ctx->hash_buf_len = PSA_HASH_LENGTH(ctx->alg);
    psa_status_t status = psa_hash_setup(&ctx->hash_operation, ctx->alg);
    return PSA_TO_PQC_RET(status);
}

uint32_t pqc_sha3_accel_update (void * const p_hash_ctx,
                                const uint32_t * const p_data,
                                const uint32_t data_len)
{
    pqc_hash_ctx_t *ctx = (pqc_hash_ctx_t*)p_hash_ctx;
    psa_status_t status = psa_hash_update(&ctx->hash_operation, (uint8_t*)p_data, (size_t)data_len);
    return PSA_TO_PQC_RET(status);
}

uint32_t pqc_sha3_accel_final (void * const p_hash_ctx,
                                uint32_t * const p_md,
                                uint32_t * const p_md_len)
{
    pqc_hash_ctx_t *ctx = (pqc_hash_ctx_t*)p_hash_ctx;
    psa_status_t status = psa_hash_finish(&ctx->hash_operation, (uint8_t*)p_md, ctx->hash_buf_len, (size_t*)p_md_len);
    return PSA_TO_PQC_RET(status);
}
#endif /* MBEDTLS_SHA3_C */

uint32_t pqc_sha3_internal_init (void * const p_hash_ctx)
{
    uint32_t ret = PQC_RET_INTERNALERR;

    ret = R_SHA_Sha3Init((st_sha_ctx_t*)p_hash_ctx);
    return ret;
}

uint32_t pqc_sha3_internal_update (void * const p_hash_ctx,
                                const uint32_t * const p_data,
                                const uint32_t data_len)
{
    uint32_t ret = PQC_RET_INTERNALERR;

    ret = R_SHA_Sha3Update((st_sha_ctx_t*)p_hash_ctx, p_data, data_len);
    return ret;
}

uint32_t pqc_sha3_internal_final (void * const p_hash_ctx,
                                uint32_t * const p_md,
                                uint32_t * const p_md_len)
{
    uint32_t ret = PQC_RET_INTERNALERR;

    ret = R_SHA_Sha3Final((st_sha_ctx_t*)p_hash_ctx, p_md, p_md_len);
    return ret;
}

/* Helper to parse out the ek from the dk */
static int mbedtls_mlkem_get_ek_from_decaps_key(const mbedtls_mlkem_bits_t bits,
                                                const mbedtls_mlkem_data_t * const p_decaps_key,
                                                mbedtls_mlkem_data_t * p_encaps_key)
{
    uint32_t ek_pos = 0;
    if (MBEDTLS_MLKEM_512 == bits)
    {
        ek_pos = PQC_MLKEM_512_ENCAPS_POS;
        p_encaps_key->key_len = PQC_SIZE_MLKEM512_ENCAPKEY;
    }
    else if (MBEDTLS_MLKEM_768 == bits)
    {
        ek_pos = PQC_MLKEM_768_ENCAPS_POS;
        p_encaps_key->key_len = PQC_SIZE_MLKEM768_ENCAPKEY;
    }
    else if (MBEDTLS_MLKEM_1024 == bits)
    {
        ek_pos = PQC_MLKEM_1024_ENCAPS_POS;
        p_encaps_key->key_len = PQC_SIZE_MLKEM1024_ENCAPKEY;
    }
    else
    {
        return MBEDTLS_ERR_ERROR_CORRUPTION_DETECTED;
    }
    p_encaps_key->key_data = p_decaps_key->key_data + (ek_pos / 4U);

    return 0;
}

void mbedtls_mlkem_init(mbedtls_mlkem_context * ctx)
{
    if (ctx == NULL) {
        return;
    }

    memset(ctx, 0, sizeof(mbedtls_mlkem_context));
}

int mbedtls_mlkem_export_keypair(mbedtls_mlkem_context * ctx,
                                 uint8_t * key_buffer,
                                 size_t * key_buffer_length)
{
    memcpy(key_buffer, ctx->d.key_data, ctx->d.key_len);
    memcpy(key_buffer + ctx->d.key_len, ctx->z.key_data, ctx->z.key_len);
    *key_buffer_length = ctx->d.key_len + ctx->z.key_len;
    return 0;
}

int mbedtls_mlkem_export_public_key(mbedtls_mlkem_context * ctx,
                                    mbedtls_mlkem_bits_t bits)
{
    int ret = MBEDTLS_ERR_ERROR_CORRUPTION_DETECTED;

    ret = mbedtls_mlkem_get_ek_from_decaps_key(bits, &ctx->decaps_key, &ctx->encaps_key);
    if (ret != 0) {
        return ret;
    }

    return 0;
}

int mbedtls_mlkem_expand_key_pair(mbedtls_mlkem_context *ctx,
                               mbedtls_mlkem_bits_t bits,
                               mbedtls_mlkem_data_t *random_d,
                               mbedtls_mlkem_data_t *random_z,
                               uint32_t (*f_rng)(uint32_t, uint32_t *))
{
    pqc_ret_t pqc_ret;
    st_pqc_mlkem_ctx_t pqc_ctx;

    pqc_initialize_hash(&pqc_ctx, bits);
    pqc_ctx.p_drbg_api = f_rng;
    
    pqc_ret = R_PQC_MlkemKeyGenInit(&pqc_ctx, (st_pqc_data_t*)random_d, (st_pqc_data_t*)random_z);
    if (PQC_RET_OK != pqc_ret)
    {
        return MBEDTLS_ERR_ERROR_GENERIC_ERROR;
    }

    pqc_ret = R_PQC_MlkemKeyGenOperate(&pqc_ctx);
    if (PQC_RET_OK != pqc_ret)
    {
        return MBEDTLS_ERR_ERROR_GENERIC_ERROR;
    }

    pqc_ret = R_PQC_MlkemKeyGenFinal(&pqc_ctx, (st_pqc_data_t*)&(ctx->decaps_key), (st_pqc_data_t*)&(ctx->d), (st_pqc_data_t*)&(ctx->z));

    if (PQC_RET_OK != pqc_ret)
    {
        return MBEDTLS_ERR_ERROR_GENERIC_ERROR;
    }
    return 0;
}

int mbedtls_mlkem_generate_key(mbedtls_mlkem_context * ctx, 
                               mbedtls_mlkem_bits_t bits,
                               uint32_t (*f_rng)(uint32_t, uint32_t *))
{
    pqc_ret_t pqc_ret;
    st_pqc_mlkem_ctx_t pqc_ctx;

    pqc_initialize_hash(&pqc_ctx, bits);
    pqc_ctx.p_drbg_api = f_rng;
    
    pqc_ret = R_PQC_MlkemKeyGenInit(&pqc_ctx, NULL, NULL);
    if (PQC_RET_OK != pqc_ret)
    {
        return MBEDTLS_ERR_ERROR_GENERIC_ERROR;
    }

    pqc_ret = R_PQC_MlkemKeyGenOperate(&pqc_ctx);
    if (PQC_RET_OK != pqc_ret)
    {
        return MBEDTLS_ERR_ERROR_GENERIC_ERROR;
    }

    pqc_ret = R_PQC_MlkemKeyGenFinal(&pqc_ctx, (st_pqc_data_t*)&(ctx->decaps_key), (st_pqc_data_t*)&(ctx->d), (st_pqc_data_t*)&(ctx->z));

    if (PQC_RET_OK != pqc_ret)
    {
        return MBEDTLS_ERR_ERROR_GENERIC_ERROR;
    }
    return 0;
}

int mbedtls_mlkem_encapsulate(mbedtls_mlkem_context * ctx,
                              mbedtls_mlkem_bits_t bits,
                              mbedtls_mlkem_data_t * cipher,
                              mbedtls_mlkem_data_t * shared_key,
                              uint32_t (*f_rng)(uint32_t, uint32_t *))
{
    pqc_ret_t pqc_ret;
    st_pqc_mlkem_ctx_t pqc_ctx;

    pqc_initialize_hash(&pqc_ctx, bits);
    pqc_ctx.p_drbg_api = f_rng;

    pqc_ret = R_PQC_MlkemEncapsInit((st_pqc_data_t*)&(ctx->encaps_key), &pqc_ctx);
    if (PQC_RET_OK != pqc_ret)
    {
        return MBEDTLS_ERR_ERROR_GENERIC_ERROR;
    }

    pqc_ret = R_PQC_MlkemEncapsOperate(&pqc_ctx);
    if (PQC_RET_OK != pqc_ret)
    {
        return MBEDTLS_ERR_ERROR_GENERIC_ERROR;
    }

    pqc_ret = R_PQC_MlkemEncapsFinal(&pqc_ctx, (st_pqc_data_t*)cipher, (st_pqc_data_t*)shared_key);
    if (PQC_RET_OK != pqc_ret)
    {
        return MBEDTLS_ERR_ERROR_GENERIC_ERROR;
    }
    return 0;
}
                              
int mbedtls_mlkem_decapsulate(mbedtls_mlkem_context * ctx,
                              mbedtls_mlkem_bits_t bits,
                              mbedtls_mlkem_data_t * cipher,
                              mbedtls_mlkem_data_t * shared_key,
                              uint32_t (*f_rng)(uint32_t, uint32_t *))
{
    pqc_ret_t pqc_ret;
    st_pqc_mlkem_ctx_t pqc_ctx;

    pqc_initialize_hash(&pqc_ctx, bits);
    pqc_ctx.p_drbg_api = f_rng;

    pqc_ret = R_PQC_MlkemDecapsInit((st_pqc_data_t*)cipher, (st_pqc_data_t*)&(ctx->decaps_key), &pqc_ctx);
    if (PQC_RET_OK != pqc_ret)
    {
        return MBEDTLS_ERR_ERROR_GENERIC_ERROR;
    }

    pqc_ret = R_PQC_MlkemDecapsOperate(&pqc_ctx);
    if (PQC_RET_OK != pqc_ret)
    {
        return MBEDTLS_ERR_ERROR_GENERIC_ERROR;
    }

    pqc_ret = R_PQC_MlkemDecapsFinal(&pqc_ctx, (st_pqc_data_t*)shared_key);
    if (PQC_RET_OK != pqc_ret)
    {
        return MBEDTLS_ERR_ERROR_GENERIC_ERROR;
    }

    return 0;
}
#endif /* MBEDTLS_MLKEM_C */
