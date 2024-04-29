/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

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
#include "hw_sce_ra_private.h"

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

/*
 * typedef enum e_sce_oem_key_type
 * {
 *  SCE_OEM_KEY_TYPE_ENCRYPTED = 0,
 *  SCE_OEM_KEY_TYPE_PLAIN     = 1
 * } sce_oem_key_type_t;
 */

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
