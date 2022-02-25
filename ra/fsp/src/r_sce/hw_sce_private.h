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

/*******************************************************************************************************************//**
 * @ingroup SCE
 * @addtogroup SCE_PROC
 * @{
 ***********************************************************************************************************************/

#ifndef HW_SCE_PRIVATE_H
#define HW_SCE_PRIVATE_H

/**********************************************************************************************************************
 * Includes
 ***********************************************************************************************************************/
#include "bsp_api.h"
#include "hw_sce_common.h"
#if BSP_FEATURE_CRYPTO_HAS_SCE9
 #include "r_sce_if.h"
#endif

/**********************************************************************************************************************
 * Macro definitions
 ***********************************************************************************************************************/
#define SCE_ECC_CURVE_TYPE_NIST         (0x00000000U)
#define SCE_ECC_CURVE_TYPE_BRAINPOOL    (0x01000000U)
#define SCE_ECC_CURVE_TYPE_KOBLITZ      (0x02000000U)

/**********************************************************************************************************************
 * Typedef definitions
 ***********************************************************************************************************************/

typedef enum e_crypto_word_endian
{
    CRYPTO_WORD_ENDIAN_BIG    = 0,
    CRYPTO_WORD_ENDIAN_LITTLE = 1
} crypto_word_endian_t;

typedef enum e_sce_oem_key_type
{
    SCE_OEM_KEY_TYPE_ENCRYPTED = 0,
    SCE_OEM_KEY_TYPE_PLAIN     = 1
} sce_oem_key_type_t;

/**********************************************************************************************************************
 * Function Prototypes
 ***********************************************************************************************************************/

/**********************************************************************************************************************
 * Includes
 ***********************************************************************************************************************/

extern uint32_t S_RAM[];
extern uint32_t S_HEAP[];
extern uint32_t S_INST[];
extern uint32_t S_INST2[];
extern uint32_t INST_DATA_SIZE;
extern void HW_SCE_SoftReset(void);

extern fsp_err_t HW_SCE_Initialization1(void);

extern fsp_err_t HW_SCE_Initialization2(void);

void      HW_SCE_Initialization1_Subproc1(void);
void      HW_SCE_Initialization2_Subproc2(void);
void      SC32_Subprc03(void);
void      SC32_Subprc04(void);
void      SC32_Subprc05(void);
fsp_err_t HW_SCE_secureBoot(void);

void                 HW_SCE_EndianSetBig(void);
void                 HW_SCE_EndianSetLittle(void);
crypto_word_endian_t HW_SCE_EndianFlagGet(void);
fsp_err_t            HW_SCE_McuSpecificInit(void);

fsp_err_t HW_SCE_FW_IntegrityChk(void);
fsp_err_t HW_SCE_HUK_Load(uint32_t * InData_LC);
fsp_err_t HW_SCE_HUK_Load_LCS(void);
fsp_err_t HW_SCE_p07(uint32_t * OutData_KeyIndex);
void      HW_SCE_ChangeToLittleEndian(void);

#if !BSP_FEATURE_CRYPTO_HAS_SCE9

/* OEM Command */
typedef enum e_sce_oem_cmd
{
    SCE_OEM_CMD_AES128 = 5,
    SCE_OEM_CMD_AES192,
    SCE_OEM_CMD_AES256,
    SCE_OEM_CMD_AES128_XTS,
    SCE_OEM_CMD_AES256_XTS,
    SCE_OEM_CMD_RSA1024_PUBLIC,
    SCE_OEM_CMD_RSA1024_PRIVATE,
    SCE_OEM_CMD_RSA2048_PUBLIC,
    SCE_OEM_CMD_RSA2048_PRIVATE,
    SCE_OEM_CMD_RSA3072_PUBLIC,
    SCE_OEM_CMD_RSA3072_PRIVATE,
    SCE_OEM_CMD_RSA4096_PUBLIC,
    SCE_OEM_CMD_RSA4096_PRIVATE,
    SCE_OEM_CMD_ECC_P192_PUBLIC,
    SCE_OEM_CMD_ECC_P192_PRIVATE,
    SCE_OEM_CMD_ECC_P224_PUBLIC,
    SCE_OEM_CMD_ECC_P224_PRIVATE,
    SCE_OEM_CMD_ECC_P256_PUBLIC,
    SCE_OEM_CMD_ECC_P256_PRIVATE,
    SCE_OEM_CMD_ECC_P384_PUBLIC,
    SCE_OEM_CMD_ECC_P384_PRIVATE,
    SCE_OEM_CMD_HMAC_SHA224,
    SCE_OEM_CMD_HMAC_SHA256,
    SCE_OEM_CMD_ECC_P256R1_PUBLIC,
    SCE_OEM_CMD_ECC_P256R1_PRIVATE,
    SCE_OEM_CMD_ECC_P384R1_PUBLIC,
    SCE_OEM_CMD_ECC_P384R1_PRIVATE,
    SCE_OEM_CMD_ECC_P512R1_PUBLIC,
    SCE_OEM_CMD_ECC_P512R1_PRIVATE,
    SCE_OEM_CMD_ECC_SECP256K1_PUBLIC,
    SCE_OEM_CMD_ECC_SECP256K1_PRIVATE,
    SCE_OEM_CMD_NUM
} sce_oem_cmd_t;
#endif
fsp_err_t HW_SCE_GenerateOemKeyIndexPrivate(const sce_oem_key_type_t key_type,
                                            const sce_oem_cmd_t      cmd,
                                            const uint8_t          * encrypted_provisioning_key,
                                            const uint8_t          * iv,
                                            const uint8_t          * encrypted_oem_key,
                                            uint32_t               * key_index);

#endif                                 /* HW_SCE_PRIVATE_H */

/*******************************************************************************************************************//**
 * @} (end addtogroup SCE_PROC)
 ***********************************************************************************************************************/
