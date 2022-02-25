/***********************************************************************************************************************
 * Copyright [2020-2022] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software and documentation are supplied by Renesas Electronics America Inc. and may only be used with products
 * of Renesas Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.  Renesas products are
 * sold pursuant to Renesas terms and conditions of sale.  Purchasers are solely responsible for the selection and use
 * of Renesas products and Renesas assumes no liability.  No license, express or implied, to any intellectual property
 * right is granted by Renesas. This software is protected under all applicable laws, including copyright laws. Renesas
 * reserves the right to change or discontinue this software and/or this documentation. THE SOFTWARE AND DOCUMENTATION
 * IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND TO THE FULLEST EXTENT
 * PERMISSIBLE UNDER APPLICABLE LAW, DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY, INCLUDING WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE SOFTWARE OR
 * DOCUMENTATION.  RENESAS SHALL HAVE NO LIABILITY ARISING OUT OF ANY SECURITY VULNERABILITY OR BREACH.  TO THE MAXIMUM
 * EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE OR DOCUMENTATION
 * (OR ANY PERSON OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER, INCLUDING,
 * WITHOUT LIMITATION, ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES; ANY LOST PROFITS,
 * OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF THE POSSIBILITY
 * OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS.
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * File Name    : hw_sce_ecc_private.h
 * Description  : SCE HW procedures for ECC algorithm
 ***********************************************************************************************************************/

#ifndef HW_SCE_ECC_PRIVATE_H
#define HW_SCE_ECC_PRIVATE_H

#include "bsp_api.h"
#include "hw_sce_common.h"

#define ECC_224_PRIVATE_KEY_LENGTH_BITS                        (224U)
#define ECC_224_PUBLIC_KEY_LENGTH_WORDS                        (7U)

/* ECC P-256 */
#define ECC_256_DOMAIN_PARAMETER_WITH_ORDER_LENGTH_WORDS       (32U)
#define ECC_256_DOMAIN_PARAMETER_WITHOUT_ORDER_LENGTH_WORDS    (24U)
#define ECC_256_POINT_ON_CURVE_LENGTH_WORDS                    (16U)
#define ECC_256_GENERATOR_POINT_LENGTH_WORDS                   (16U)
#define ECC_256_PUBLIC_KEY_LENGTH_WORDS                        (16U)
#define ECC_256_PRIVATE_KEY_LENGTH_WORDS                       (8U)
#define ECC_256_PRIVATE_KEY_LENGTH_BITS                        (256U)
#define ECC_256_MESSAGE_DIGEST_LENGTH_WORDS                    (8U)
#define ECC_256_SIGNATURE_R_LENGTH_WORDS                       (8U)
#define ECC_256_SIGNATURE_S_LENGTH_WORDS                       (8U)
#define ECC_256_PRIVATE_KEY_HRK_LENGTH_WORDS                   (13U)
#define ECC_256_PRIVATE_KEY_HRK_LENGTH_BITS                    (416U)

/* ECC P-384 */
#define ECC_384_DOMAIN_PARAMETER_WITH_ORDER_LENGTH_WORDS       (48U)
#define ECC_384_DOMAIN_PARAMETER_WITHOUT_ORDER_LENGTH_WORDS    (36U)
#define ECC_384_POINT_ON_CURVE_LENGTH_WORDS                    (24U)
#define ECC_384_GENERATOR_POINT_LENGTH_WORDS                   (24U)
#define ECC_384_PUBLIC_KEY_LENGTH_WORDS                        (24U)
#define ECC_384_PRIVATE_KEY_LENGTH_WORDS                       (12U)
#define ECC_384_PRIVATE_KEY_LENGTH_BITS                        (384U)
#define ECC_384_MESSAGE_DIGEST_LENGTH_WORDS                    (12U)
#define ECC_384_SIGNATURE_R_LENGTH_WORDS                       (12U)
#define ECC_384_SIGNATURE_S_LENGTH_WORDS                       (12U)
#define ECC_384_PRIVATE_KEY_HRK_LENGTH_WORDS                   (17U)
#define ECC_384_PRIVATE_KEY_HRK_LENGTH_BITS                    (544U)

/* Function pointer declarations */
#if BSP_FEATURE_CRYPTO_HAS_SCE9
 #define ECC_PUBLIC_KEY_SIZE_BYTES(curve_size)    (curve_size * 2 + 20U)
typedef fsp_err_t (* hw_sce_ecc_scalarmultiplication_t)(const uint32_t * InData_CurveType, const uint32_t * InData_Cmd,
                                                        const uint32_t * InData_K, const uint32_t * InData_P,
                                                        uint32_t * OutData_R);
#else
typedef fsp_err_t (* hw_sce_ecc_scalarmultiplication_t)(const uint32_t * InData_DomainParam, const uint32_t * InData_K,
                                                        const uint32_t * InData_P, uint32_t * OutData_R);
#endif
typedef fsp_err_t (* hw_sce_ecc_generatekey_t)(const uint32_t * InData_DomainParam, const uint32_t * InData_G,
                                               uint32_t * OutData_PubKey, uint32_t * OutData_PrivKey);

typedef fsp_err_t (* hw_sce_ecc_generatesign_t)(const uint32_t * InData_DomainParam, const uint32_t * InData_G,
                                                const uint32_t * InData_PrivKey, const uint32_t * InData_MsgDgst,
                                                uint32_t * OutData_R, uint32_t * OutData_S);

typedef fsp_err_t (* hw_sce_ecc_verifysign_t)(const uint32_t * InData_DomainParam, const uint32_t * InData_G,
                                              const uint32_t * InData_PubKey, const uint32_t * InData_MsgDgst,
                                              const uint32_t * InData_R, const uint32_t * InData_S);

/* ECC - 256 HW Procedure definitions */
fsp_err_t HW_SCE_ECC_256ScalarMultiplication(const uint32_t * InData_DomainParam,
                                             const uint32_t * InData_K,
                                             const uint32_t * InData_P,
                                             uint32_t       * OutData_R);

fsp_err_t HW_SCE_ECC_256GenerateKey(const uint32_t * InData_DomainParam,
                                    const uint32_t * InData_G,
                                    uint32_t       * OutData_PubKey,
                                    uint32_t       * OutData_PrivKey);

fsp_err_t HW_SCE_ECC_256GenerateSign(const uint32_t * InData_DomainParam,
                                     const uint32_t * InData_G,
                                     const uint32_t * InData_PrivKey,
                                     const uint32_t * InData_MsgDgst,
                                     uint32_t       * OutData_R,
                                     uint32_t       * OutData_S);

fsp_err_t HW_SCE_ECC_256VerifySign(const uint32_t * InData_DomainParam,
                                   const uint32_t * InData_G,
                                   const uint32_t * InData_PubKey,
                                   const uint32_t * InData_MsgDgst,
                                   const uint32_t * InData_R,
                                   const uint32_t * InData_S);

/* ECC - 256 Wrapped key HW Procedure definitions */
fsp_err_t HW_SCE_ECC_256HrkGenerateKey(const uint32_t * InData_DomainParam,
                                       const uint32_t * InData_G,
                                       uint32_t       * OutData_KeyIndex,
                                       uint32_t       * OutData_PubKey);

fsp_err_t HW_SCE_ECC_256HrkGenerateSign(const uint32_t * InData_DomainParam,
                                        const uint32_t * InData_G,
                                        const uint32_t * InData_KeyIndex,
                                        const uint32_t * InData_MsgDgst,
                                        uint32_t       * OutData_R,
                                        uint32_t       * OutData_S);

fsp_err_t HW_SCE_ECC_256HrkScalarMultiplication(const uint32_t * InData_DomainParam,
                                                const uint32_t * InData_KeyIndex,
                                                const uint32_t * InData_P,
                                                uint32_t       * OutData_R);

fsp_err_t HW_SCE_ECC_256WrappedScalarMultiplication(const uint32_t * InData_CurveType,
                                                    const uint32_t * InData_Cmd,
                                                    const uint32_t * InData_KeyIndex,
                                                    const uint32_t * InData_P,
                                                    uint32_t       * OutData_R);

/* ECC - 384 HW Procedure definitions */
fsp_err_t HW_SCE_ECC_384ScalarMultiplication(const uint32_t * InData_DomainParam,
                                             const uint32_t * InData_K,
                                             const uint32_t * InData_P,
                                             uint32_t       * OutData_R);

fsp_err_t HW_SCE_ECC_384GenerateKey(const uint32_t * InData_DomainParam,
                                    const uint32_t * InData_G,
                                    uint32_t       * OutData_PubKey,
                                    uint32_t       * OutData_PrivKey);

fsp_err_t HW_SCE_ECC_384GenerateSign(const uint32_t * InData_DomainParam,
                                     const uint32_t * InData_G,
                                     const uint32_t * InData_PrivKey,
                                     const uint32_t * InData_MsgDgst,
                                     uint32_t       * OutData_R,
                                     uint32_t       * OutData_S);

fsp_err_t HW_SCE_ECC_384VerifySign(const uint32_t * InData_DomainParam,
                                   const uint32_t * InData_G,
                                   const uint32_t * InData_PubKey,
                                   const uint32_t * InData_MsgDgst,
                                   const uint32_t * InData_R,
                                   const uint32_t * InData_S);

/* ECC - 384 Wrapped key HW Procedure definitions */
fsp_err_t HW_SCE_ECC_384HrkGenerateKey(const uint32_t * InData_DomainParam,
                                       const uint32_t * InData_G,
                                       uint32_t       * OutData_KeyIndex,
                                       uint32_t       * OutData_PubKey);

fsp_err_t HW_SCE_ECC_384HrkGenerateSign(const uint32_t * InData_DomainParam,
                                        const uint32_t * InData_G,
                                        const uint32_t * InData_KeyIndex,
                                        const uint32_t * InData_MsgDgst,
                                        uint32_t       * OutData_R,
                                        uint32_t       * OutData_S);

fsp_err_t HW_SCE_ECC_384HrkScalarMultiplication(const uint32_t * InData_DomainParam,
                                                const uint32_t * InData_KeyIndex,
                                                const uint32_t * InData_P,
                                                uint32_t       * OutData_R);
fsp_err_t HW_SCE_ECC_384WrappedScalarMultiplication(const uint32_t * InData_CurveType,
                                                    const uint32_t * InData_Cmd,
                                                    const uint32_t * InData_KeyIndex,
                                                    const uint32_t * InData_P,
                                                    uint32_t       * OutData_R);

/* ECC - 224 HW Procedure definitions */
fsp_err_t HW_SCE_ECC_224GenerateSign(const uint32_t * InData_DomainParam,
                                     const uint32_t * InData_G,
                                     const uint32_t * InData_PrivKey,
                                     const uint32_t * InData_MsgDgst,
                                     uint32_t       * OutData_R,
                                     uint32_t       * OutData_S);

fsp_err_t HW_SCE_ECC_224VerifySign(const uint32_t * InData_DomainParam,
                                   const uint32_t * InData_G,
                                   const uint32_t * InData_PubKey,
                                   const uint32_t * InData_MsgDgst,
                                   const uint32_t * InData_R,
                                   const uint32_t * InData_S);

#endif                                 /* HW_SCE_ECC_PRIVATE_H */
