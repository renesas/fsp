#include "common.h"

#if defined(MBEDTLS_ML_DSA_C)

#include "mbedtls/mldsa.h"
#include "mbedtls/threading.h"
#include "mbedtls/platform_util.h"
#include "mbedtls/error.h"

#include "mbedtls/platform.h"
#include "r_pqc_api.h"
#include "r_sha_api.h"

#define PQC_BUF_BYTESIZE    (15664U)
#define PQC_SHA_BYTESIZE    (224)

static uint32_t         pqc_buf[PQC_BUF_BYTESIZE / 4];
static uint32_t         sha_buf[PQC_SHA_BYTESIZE / 4];
static uint32_t         sha_buf2[PQC_SHA_BYTESIZE / 4];

static st_pqc_hash_t    hash_info_shake128;
static st_pqc_hash_t    hash_info_shake256;
static st_sha_ctx_t     ctx_sw_shake128;
static st_sha_ctx_t     ctx_sw_shake256;

static void mldsa_initialize_context(st_pqc_mldsa_ctx_t * ctx, mbedtls_mldsa_bits_t bits);
static uint32_t mldsa_sha3_internal_init (void * const p_hash_ctx);
static uint32_t mldsa_sha3_internal_update (void * const p_hash_ctx,
                                            const uint32_t * const p_data,
                                            const uint32_t data_len);
static uint32_t mldsa_sha3_internal_final (void * const p_hash_ctx,
                                           uint32_t * const p_md,
                                           uint32_t * const p_md_len);
static int mbedtls_mldsa_generate_key_helper(mbedtls_mldsa_context *ctx, st_pqc_mldsa_ctx_t* pqc_ctx, st_pqc_data_t* seed);

static void mldsa_initialize_context(st_pqc_mldsa_ctx_t * ctx, mbedtls_mldsa_bits_t bits)
{

    if (MBEDTLS_ML_DSA_44 == bits) 
    {
        ctx->algo_params = PQC_ALGO_MLDSA44;
    } 
    else 
    { 
        // (MBEDTLS_ML_DSA_65 == bits)
        ctx->algo_params = PQC_ALGO_MLDSA65;
    }

    ctx->p_buf = pqc_buf;
    ctx->p_pre_hash_oid = NULL;

    ctx->p_hash_info_shake128    = &hash_info_shake128;
    ctx->p_hash_info_shake256    = &hash_info_shake256;

    ctx_sw_shake128.algo_opt            = SHA_ALGO_SHAKE128;
    ctx_sw_shake128.p_buf               = sha_buf;
    ctx_sw_shake256.algo_opt            = SHA_ALGO_SHAKE256;
    ctx_sw_shake256.p_buf               = sha_buf2;

    hash_info_shake128.p_hash_ctx               = &ctx_sw_shake128;
    hash_info_shake128.p_hash_init_api          = mldsa_sha3_internal_init;
    hash_info_shake128.p_hash_update_api        = mldsa_sha3_internal_update;
    hash_info_shake128.p_hash_final_api         = mldsa_sha3_internal_final;

    hash_info_shake256.p_hash_ctx               = &ctx_sw_shake256;
    hash_info_shake256.p_hash_init_api          = mldsa_sha3_internal_init;
    hash_info_shake256.p_hash_update_api        = mldsa_sha3_internal_update;
    hash_info_shake256.p_hash_final_api         = mldsa_sha3_internal_final;
}

static uint32_t mldsa_sha3_internal_init (void * const p_hash_ctx)
{
    uint32_t ret = PQC_RET_INTERNALERR;

    ret = R_SHA_Sha3Init((st_sha_ctx_t*)p_hash_ctx);
    return ret;
}

static uint32_t mldsa_sha3_internal_update (void * const p_hash_ctx,
                                            const uint32_t * const p_data,
                                            const uint32_t data_len)
{
    uint32_t ret = PQC_RET_INTERNALERR;

    ret = R_SHA_Sha3Update((st_sha_ctx_t*)p_hash_ctx, p_data, data_len);
    return ret;
}

static uint32_t mldsa_sha3_internal_final (void * const p_hash_ctx,
                                           uint32_t * const p_md,
                                           uint32_t * const p_md_len)
{
    uint32_t ret = PQC_RET_INTERNALERR;

    ret = R_SHA_Sha3Final((st_sha_ctx_t*)p_hash_ctx, p_md, p_md_len);
    return ret;
}

static int mbedtls_mldsa_generate_key_helper(mbedtls_mldsa_context *ctx, st_pqc_mldsa_ctx_t* pqc_ctx, st_pqc_data_t* seed)
{
    pqc_ret_t pqc_ret;
    pqc_ret = R_PQC_MldsaKeyGenInit(pqc_ctx, seed);
    if (PQC_RET_OK != pqc_ret)
    {
        return MBEDTLS_ERR_ERROR_GENERIC_ERROR;
    }

    pqc_ret = R_PQC_MldsaKeyGenOperate(pqc_ctx);
    if (PQC_RET_OK != pqc_ret)
    {
        return MBEDTLS_ERR_ERROR_GENERIC_ERROR;
    }

    pqc_ret = R_PQC_MldsaKeyGenFinal(pqc_ctx, (st_pqc_data_t*)&(ctx->private_key), (st_pqc_data_t*)&(ctx->public_key), (st_pqc_data_t*)&(ctx->seed));

    if (PQC_RET_OK != pqc_ret)
    {
        return MBEDTLS_ERR_ERROR_GENERIC_ERROR;
    }
    return 0;
}

void mbedtls_mldsa_init(mbedtls_mldsa_context * ctx)
{
    if (ctx == NULL) {
        return;
    }

    memset(ctx, 0, sizeof(mbedtls_mldsa_context));
}

int mbedtls_mldsa_export_keypair(mbedtls_mldsa_context * ctx,
                                 uint8_t * key_buffer,
                                 size_t * key_buffer_length)
{
    memcpy(key_buffer, ctx->seed.key_data, ctx->seed.key_len);
    *key_buffer_length = ctx->seed.key_len;
    return 0;
}

int mbedtls_mldsa_export_public_key(mbedtls_mldsa_context * ctx,
                                    uint8_t * key_buffer,
                                    size_t * key_buffer_length)
{
    memcpy(key_buffer, ctx->public_key.key_data, ctx->public_key.key_len);
    *key_buffer_length = ctx->public_key.key_len;
    return 0;
}

int mbedtls_mldsa_expand_key_pair(mbedtls_mldsa_context *ctx,
                                  mbedtls_mldsa_bits_t bits,
                                  mbedtls_mldsa_data_t *seed,
                                  uint32_t (*f_rng)(uint32_t, uint32_t *))
{
    st_pqc_mldsa_ctx_t pqc_ctx;

    mldsa_initialize_context(&pqc_ctx, bits);
    pqc_ctx.p_drbg_api = f_rng;

    return mbedtls_mldsa_generate_key_helper(ctx, &pqc_ctx, (st_pqc_data_t*)seed);
}

int mbedtls_mldsa_generate_key(mbedtls_mldsa_context * ctx, 
                               mbedtls_mldsa_bits_t bits, 
                               uint32_t (*f_rng)(uint32_t, uint32_t *))
{
    st_pqc_mldsa_ctx_t pqc_ctx;

    mldsa_initialize_context(&pqc_ctx, bits);
    pqc_ctx.p_drbg_api = f_rng;
    
    return mbedtls_mldsa_generate_key_helper(ctx, &pqc_ctx, NULL);
}

int mbedtls_mldsa_sign(mbedtls_mldsa_context * ctx,
                              mbedtls_mldsa_bits_t bits,
                              mbedtls_mldsa_data_t * msg,
                              mbedtls_mldsa_data_t * signature,
                             uint32_t (*f_rng)(uint32_t, uint32_t *))
{
    pqc_ret_t pqc_ret;
    st_pqc_mldsa_ctx_t pqc_ctx;
    st_pqc_data_t mldsa_ctx_string = {0x00, 0x00};

    mldsa_initialize_context(&pqc_ctx, bits);
    pqc_ctx.p_drbg_api = f_rng;
    pqc_ctx.p_mldsa_ctx = &mldsa_ctx_string;
    pqc_ctx.is_random_sign = PQC_BOOL_FALSE;
    
    /* Public key used to verify generated signaure in `R_PQC_MldsaSignFinal()` */
    pqc_ctx.pub_key.p_data  = ctx->public_key.key_data;
    pqc_ctx.pub_key.len     = ctx->public_key.key_len;

    pqc_ret = R_PQC_MldsaSignInit((st_pqc_data_t*)&(ctx->private_key), &pqc_ctx);
    if (PQC_RET_OK != pqc_ret)
    {
        return MBEDTLS_ERR_ERROR_GENERIC_ERROR;
    }

    pqc_ret = R_PQC_MldsaSignOperate((st_pqc_data_t*)msg, &pqc_ctx);
    if (PQC_RET_OK != pqc_ret)
    {
        return MBEDTLS_ERR_ERROR_GENERIC_ERROR;
    }

    pqc_ret = R_PQC_MldsaSignFinal(&pqc_ctx, (st_pqc_data_t*)signature);
    if (PQC_RET_OK != pqc_ret)
    {
        return MBEDTLS_ERR_ERROR_GENERIC_ERROR;
    }
    return 0;
}
                              
int mbedtls_mldsa_verify(mbedtls_mldsa_context * ctx,
                         mbedtls_mldsa_bits_t bits,
                         mbedtls_mldsa_data_t * signature,
                         mbedtls_mldsa_data_t * msg, 
                         uint32_t (*f_rng)(uint32_t, uint32_t *))
{
    pqc_ret_t pqc_ret;
    st_pqc_mldsa_ctx_t pqc_ctx;
    st_pqc_data_t mldsa_ctx_string = {0x00, 0x00};

    mldsa_initialize_context(&pqc_ctx, bits);
    pqc_ctx.p_drbg_api = f_rng;
    pqc_ctx.p_mldsa_ctx = &mldsa_ctx_string;

    pqc_ret = R_PQC_MldsaVerifyInit((st_pqc_data_t*)signature, (st_pqc_data_t*)&(ctx->public_key), &pqc_ctx);
    if (PQC_RET_OK != pqc_ret)
    {
        return MBEDTLS_ERR_ERROR_GENERIC_ERROR;
    }

    pqc_ret = R_PQC_MldsaVerifyOperate((st_pqc_data_t*)msg, &pqc_ctx);
    if (PQC_RET_OK != pqc_ret)
    {
        return MBEDTLS_ERR_ERROR_GENERIC_ERROR;
    }

    pqc_ret = R_PQC_MldsaVerifyFinal(&pqc_ctx);
    if (PQC_RET_OK != pqc_ret)
    {
        return MBEDTLS_ERR_ERROR_GENERIC_ERROR;
    }

    return 0;
}
#endif /* MBEDTLS_ML_DSA_C */
