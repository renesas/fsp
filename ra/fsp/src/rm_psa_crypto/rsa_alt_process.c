/***********************************************************************************************************************
 * Copyright [2019] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software is supplied by Renesas Electronics America Inc. and may only be used with products of Renesas
 * Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.  This software is protected under
 * all applicable laws, including copyright laws. Renesas reserves the right to change or discontinue this software.
 * THE SOFTWARE IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND TO THE FULLEST
 * EXTENT PERMISSIBLE UNDER APPLICABLE LAW,DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY, INCLUDING
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE SOFTWARE.
 * TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE
 * (OR ANY PERSON OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER, INCLUDING,
 * WITHOUT LIMITATION, ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES; ANY LOST PROFITS,
 * OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF THE POSSIBILITY
 * OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS.
 **********************************************************************************************************************/

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#if defined(MBEDTLS_RSA_C)

#include "mbedtls/rsa.h"
#include "mbedtls/rsa_internal.h"
#include "mbedtls/oid.h"
#include "mbedtls/platform_util.h"

#include <string.h>

#if defined(MBEDTLS_PKCS1_V21)
#include "mbedtls/md.h"
#endif

#if defined(MBEDTLS_PKCS1_V15) && !defined(__OpenBSD__)
#include <stdlib.h>
#endif

#if defined(MBEDTLS_PLATFORM_C)
#include "mbedtls/platform.h"
#else
#include <stdio.h>
#define mbedtls_printf printf
#define mbedtls_calloc calloc
#define mbedtls_free   free
#endif

#if defined(MBEDTLS_RSA_ALT)
#include "hw_sce_rsa_private.h"

/* Parameter validation macros */
#define RSA_VALIDATE_RET( cond )                                       \
    MBEDTLS_INTERNAL_VALIDATE_RET( cond, MBEDTLS_ERR_RSA_BAD_INPUT_DATA )
#define RSA_VALIDATE( cond )                                           \
    MBEDTLS_INTERNAL_VALIDATE( cond )


#if defined(MBEDTLS_GENPRIME)

/**/
/*
 * Generate an RSA keypair
 */
int mbedtls_rsa_gen_key( mbedtls_rsa_context *ctx,
                 int (*f_rng)(void *, unsigned char *, size_t),
                 void *p_rng,
                 unsigned int nbits, int exponent )
{
    int ret = 0; // used by MBEDTLS_MPI_CHK
    RSA_VALIDATE_RET( ctx != NULL );
    (void)f_rng;
    (void)p_rng;
    uint8_t *p_rsa_private_exponent = NULL;
    uint8_t *p_rsa_public_modulus = NULL;
    uint8_t *p_rsa2048_domain_parameters = NULL;
    
    /*calloc pointers created to remove clang warnings */
    uint32_t *p_calloc_rsa_private_exponent = NULL; 
    uint32_t *p_calloc_rsa_public_modulus = NULL;
    uint32_t *p_calloc_rsa2048_domain_parameters = NULL;

    uint8_t  rsa_public_exponent[4] = {0x00, 0x01, 0x00, 0x01};

    if(exponent != RSA_PUBLIC_EXPONENT_BE)
    {
    	return( MBEDTLS_ERR_RSA_BAD_INPUT_DATA );
    }

    /* We only support RSA2048 now*/
    if (nbits != RSA_2048_BITS)
    {
        return( MBEDTLS_ERR_RSA_BAD_INPUT_DATA);
    }


    /*obtain a 32-bit aligned block of memory to be used by the SCE fore key generation*/
    p_calloc_rsa_private_exponent = (uint32_t *)mbedtls_calloc(RSA_MODULUS_SIZE_BYTES(2048)/4, sizeof(uint32_t));
    p_calloc_rsa_public_modulus = (uint32_t *)mbedtls_calloc(RSA_MODULUS_SIZE_BYTES(2048)/4, sizeof(uint32_t));
    p_calloc_rsa2048_domain_parameters = (uint32_t *)mbedtls_calloc(RSA_PLAIN_TEXT_CRT_KEY_SIZE_BYTES(2048)/4, sizeof(uint32_t));

    p_rsa_private_exponent = (uint8_t *)p_calloc_rsa_private_exponent;
    p_rsa_public_modulus = (uint8_t *)p_calloc_rsa_public_modulus;
    p_rsa2048_domain_parameters = (uint8_t *)p_calloc_rsa2048_domain_parameters;


    if ((p_rsa_private_exponent == NULL) || (p_rsa_public_modulus == NULL) || (p_rsa2048_domain_parameters == NULL))
    {
        mbedtls_free(p_calloc_rsa_private_exponent);
        mbedtls_free(p_calloc_rsa_public_modulus);
        mbedtls_free(p_calloc_rsa2048_domain_parameters);
        return MBEDTLS_ERR_MPI_ALLOC_FAILED;;
    }

    if (FSP_SUCCESS != HW_SCE_RSA_2048KeyGenerate (SCE_RSA_NUM_TRIES_10240,
            (uint32_t *)p_rsa_private_exponent,
            (uint32_t *)p_rsa_public_modulus,
            (uint32_t*)p_rsa2048_domain_parameters))
    {
        mbedtls_free(p_calloc_rsa_private_exponent);
        mbedtls_free(p_calloc_rsa_public_modulus);
        mbedtls_free(p_calloc_rsa2048_domain_parameters);
        return( MBEDTLS_ERR_RSA_KEY_GEN_FAILED );
    }

    /*Copy the public key data into the context*/
    if (0 != mbedtls_mpi_read_binary(&ctx->N, p_rsa_public_modulus, RSA_MODULUS_SIZE_BYTES(2048)))
    {
        ret = MBEDTLS_ERR_MPI_ALLOC_FAILED;
    }
    /*Copy the public exponent into the context*/
    else if (0 !=mbedtls_mpi_read_binary(&ctx->E, (unsigned char *)&rsa_public_exponent, 4))
    {
        ret = MBEDTLS_ERR_MPI_ALLOC_FAILED;
    }
    /*Copy the private key into the context*/
    else if (0 != mbedtls_mpi_read_binary(&ctx->D, p_rsa_private_exponent, RSA_MODULUS_SIZE_BYTES(2048)))
    {
        ret = MBEDTLS_ERR_MPI_ALLOC_FAILED;
    }
    /* The generated domain parameters are in the format:
     * d mod (q-1) || q || d mod (p-1) || p || (1/q) mod p
     * Import these elements into the mbedtlk_rsa_context structure */
    else if (0 != mbedtls_mpi_read_binary(&ctx->DQ, p_rsa2048_domain_parameters + (0), RSA_PARAMETERS_SIZE_BYTES(2048)))
    {
        ret = MBEDTLS_ERR_MPI_ALLOC_FAILED;
    }
    else if (0 != mbedtls_mpi_read_binary(&ctx->Q,  p_rsa2048_domain_parameters + (1 * RSA_PARAMETERS_SIZE_BYTES(2048)), RSA_MODULUS_SIZE_BYTES(2048)))
    {
        ret = MBEDTLS_ERR_MPI_ALLOC_FAILED;
    }
    else if (0 != mbedtls_mpi_read_binary(&ctx->DP, p_rsa2048_domain_parameters + (2 * RSA_PARAMETERS_SIZE_BYTES(2048)), RSA_MODULUS_SIZE_BYTES(2048)))
    {
        ret = MBEDTLS_ERR_MPI_ALLOC_FAILED;
    }
    else if (0 != mbedtls_mpi_read_binary(&ctx->P,  p_rsa2048_domain_parameters + (3 * RSA_PARAMETERS_SIZE_BYTES(2048)), RSA_MODULUS_SIZE_BYTES(2048)))
    {
        ret = MBEDTLS_ERR_MPI_ALLOC_FAILED;
    }
    else if (0 != mbedtls_mpi_read_binary(&ctx->QP, p_rsa2048_domain_parameters + (4 * RSA_PARAMETERS_SIZE_BYTES(2048)), RSA_MODULUS_SIZE_BYTES(2048)))
    {
        ret = MBEDTLS_ERR_MPI_ALLOC_FAILED;
    }
    else
    {
        ret = 0;
    }

    /*Clear out the generated private key from memory*/
    memset(p_rsa_private_exponent, 0, RSA_MODULUS_SIZE_BYTES(2048));
    /*Clear out the generated domain parameters from memory*/
    memset(p_rsa2048_domain_parameters, 0, RSA_PLAIN_TEXT_CRT_KEY_SIZE_BYTES(2048));
    /*Free the allocated memory*/
    mbedtls_free(p_calloc_rsa_private_exponent);
    mbedtls_free(p_calloc_rsa_public_modulus);
    mbedtls_free(p_calloc_rsa2048_domain_parameters);
    
    ctx->len = mbedtls_mpi_size( &ctx->N );

    if( ret != 0 )
    {
        mbedtls_rsa_free( ctx );
        return( ret);
    }
    return( 0 );
}

#endif /* MBEDTLS_GENPRIME */

/*
 * Do an RSA public key operation
 */

int mbedtls_rsa_public( mbedtls_rsa_context *ctx,
                const unsigned char *input,
                unsigned char *output )
{
   uint32_t temp_E= {RSA_PUBLIC_EXPONENT_LE};
   uint8_t *p_temp_buff_N;
   uint8_t *p_temp_CtxN;
   uint8_t *p_temp_N;
   uint32_t i = 0;
   fsp_err_t iret; 
   p_temp_CtxN = (uint8_t *)ctx->N.p;
   p_temp_CtxN += RSA_MODULUS_SIZE_BYTES(2048) - 1;
    /*calloc pointer created to remove clang warnings */
    uint32_t *p_calloc_temp_buff_N = NULL; 

   //If the size of N is not equal to the modulus size, then that is because of the leading 00 (sign field) from the ASN1 import
   // Use openssl asn1parse -in private1.pem (in !test folder) to see asn1 format of key
   if (ctx->N.n != (RSA_MODULUS_SIZE_BYTES(2048)/(sizeof (mbedtls_mpi_uint))))
   {
       // There should be only 1 extra value (00) at the beginning; otherwise the key is in an unexpected format
       if ((ctx->N.n - 1 ) != (RSA_MODULUS_SIZE_BYTES(2048)/(sizeof (mbedtls_mpi_uint))))
       {
           return MBEDTLS_ERR_RSA_BAD_INPUT_DATA;
       }
   }

   /*Only 65537 public exponent is valid*/
   if (*ctx->E.p != RSA_PUBLIC_EXPONENT_BE)
   {
       return MBEDTLS_ERR_RSA_BAD_INPUT_DATA;
   }

   /*obtain a 32-bit aligned block of memory to be used by the SCE fore key generation*/
   p_calloc_temp_buff_N = (uint32_t *)mbedtls_calloc(RSA_MODULUS_SIZE_BYTES(2048)/4, sizeof(uint32_t));
   if (p_calloc_temp_buff_N == NULL)
   {
       mbedtls_free(p_calloc_temp_buff_N);
       return MBEDTLS_ERR_MPI_ALLOC_FAILED;;
   }

   p_temp_buff_N =  (uint8_t *)p_calloc_temp_buff_N;
   p_temp_N = p_temp_buff_N;

    /* Reverse the byte order */
   for (i = 0; i <RSA_MODULUS_SIZE_BYTES(2048); i++ )
   {
       *p_temp_N = *p_temp_CtxN;
       p_temp_CtxN--;
       p_temp_N++;
   }

    iret =FSP_ERR_CRYPTO_CONTINUE;
    for ( ; FSP_ERR_CRYPTO_CONTINUE == iret; )
    {
        iret = HW_SCE_RSA_2048PublicKeyEncrypt((uint32_t *)input, &temp_E, (uint32_t *)p_temp_buff_N, (uint32_t *)output);
    }

    /*Free the allocated buffer*/
    mbedtls_free(p_calloc_temp_buff_N);
    if (0 != iret)
    {
    	return( MBEDTLS_ERR_RSA_PUBLIC_FAILED);
    }

    return( 0 );
}

/*
 * Do an RSA private key operation
 */

int mbedtls_rsa_private( mbedtls_rsa_context *ctx,
                 int (*f_rng)(void *, unsigned char *, size_t),
                 void *p_rng,
                 const unsigned char *input,
                 unsigned char *output )
{

   uint32_t i;
   (void) f_rng;
   (void) p_rng;
   uint8_t *p_temp_buff_D;
   uint8_t *p_temp_buff_N;
   uint8_t *p_temp_CtxD;
   uint8_t *p_temp_CtxN;
   uint8_t *p_temp_D;
   uint8_t *p_temp_N;
   fsp_err_t iret;
       /*calloc 32-bit pointer created to remove clang warnings */
   uint32_t *p_calloc_temp_buff_N = NULL; 
   uint32_t *p_calloc_temp_buff_D = NULL; 

   RSA_VALIDATE_RET( ctx != NULL );
   RSA_VALIDATE_RET( input != NULL );
   RSA_VALIDATE_RET( output != NULL );

   /*Set pointer to end of D and N in the context*/
   p_temp_CtxD = (uint8_t *)ctx->D.p;
   p_temp_CtxD += RSA_MODULUS_SIZE_BYTES(2048) - 1;
   p_temp_CtxN = (uint8_t *)ctx->N.p;
   p_temp_CtxN += RSA_MODULUS_SIZE_BYTES(2048) - 1;

   //If the size of N is not equal to the modulus size, then that is because of the leading 00 (sign field) from the ASN1 import
   // Use openssl asn1parse -in private1.pem to see asn1 format of a .pem key
   if (ctx->N.n != (RSA_MODULUS_SIZE_BYTES(2048)/(sizeof (mbedtls_mpi_uint))))
   {
       // There should be only 1 extra value (00) at the beginning; otherwise the key is in an unexpected format
       if ((ctx->N.n -1 ) != (RSA_MODULUS_SIZE_BYTES(2048)/(sizeof (mbedtls_mpi_uint))))
       {
           return MBEDTLS_ERR_RSA_BAD_INPUT_DATA;
       }
   }

   /*Obtain a 32-bit aligned block of memory to be used by the SCE fore key generation
    * Assuming RSA2048 key this is the max size of each field: N D P Q*/
   p_calloc_temp_buff_N = (uint32_t *)mbedtls_calloc(RSA_MODULUS_SIZE_BYTES(2048)/4, sizeof(uint32_t));
   p_calloc_temp_buff_D = (uint32_t *)mbedtls_calloc(RSA_MODULUS_SIZE_BYTES(2048)/4, sizeof(uint32_t));
   if ((p_calloc_temp_buff_N == NULL) || (p_calloc_temp_buff_D == NULL))
   {
       mbedtls_free(p_calloc_temp_buff_N);
       mbedtls_free(p_calloc_temp_buff_D);
       return MBEDTLS_ERR_MPI_ALLOC_FAILED;;
   }
   p_temp_buff_N = (uint8_t *)p_calloc_temp_buff_N;
   p_temp_buff_D = (uint8_t *)p_calloc_temp_buff_D;
   
   p_temp_D = p_temp_buff_D;
   p_temp_N = p_temp_buff_N;

    /* Reverse the byte order */
   for (i = 0; i <RSA_MODULUS_SIZE_BYTES(2048); i++ )
   {
       *p_temp_D = *p_temp_CtxD;
       *p_temp_N = *p_temp_CtxN;
       p_temp_CtxD--;
       p_temp_CtxN--;
       p_temp_D++;
       p_temp_N++;
   }

    iret =FSP_ERR_CRYPTO_CONTINUE;
    for ( ; FSP_ERR_CRYPTO_CONTINUE == iret; )
    {
        iret = HW_SCE_RSA_2048PrivateKeyDecrypt((uint32_t *)input, (uint32_t *)p_temp_buff_D, (uint32_t *)p_temp_buff_N, (uint32_t *)output);
    }

    mbedtls_free(p_calloc_temp_buff_N);
    mbedtls_free(p_calloc_temp_buff_D);

    if (iret != 0)
    {
        return MBEDTLS_ERR_RSA_PRIVATE_FAILED;
    }
    return (0);
}

#endif /* !MBEDTLS_RSA_ALT */

#endif /* MBEDTLS_RSA_C */
