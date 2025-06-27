/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef HW_SCE_HASH_PRIVATE_H
#define HW_SCE_HASH_PRIVATE_H

/**********************************************************************************************************************
 * Includes
 ***********************************************************************************************************************/
#include "bsp_api.h"
#include "hw_sce_common.h"

#define HW_SCE_LARGE_DATA_VALUE_0    (0x80000000U)
#define HW_SCE_LARGE_DATA_VALUE_1    (0x00000000U)

/*******************************************************************************************************************//**
 * Converts byte data to bit data. This function returns upper 3 digits.
 ***********************************************************************************************************************/
static inline uint32_t r_sce_byte_to_bit_convert_upper (const uint64_t bytes)
{
    return (uint32_t) (bytes >> 29);
}

/*******************************************************************************************************************//**
 * Converts byte data to bit data. This function returns lower 32 digits.
 ***********************************************************************************************************************/
static inline uint32_t r_sce_byte_to_bit_convert_lower (const uint64_t bytes)
{
    return (uint32_t) (bytes << 3);
}

fsp_err_t        HW_SCE_SHA256_UpdateHash(const uint32_t * p_source, uint32_t num_words, uint32_t * p_digest);
extern fsp_err_t HW_SCE_Sha224256GenerateMessageDigestSub(const uint32_t * InData_InitVal,
                                                          const uint32_t * InData_PaddedMsg,
                                                          const uint32_t   MAX_CNT,
                                                          uint32_t       * OutData_MsgDigest);

#if BSP_FEATURE_RSIP_RSIP_E11A_SUPPORTED
extern fsp_err_t HW_SCE_ShaGenerateMessageDigestSub(const uint32_t InData_InitVal[],
                                                    const uint32_t InData_PaddedMsg[],
                                                    uint32_t       OutData_MsgDigest[],
                                                    const uint32_t MAX_CNT);

#else
extern fsp_err_t HW_SCE_ShaGenerateMessageDigestSub(const uint32_t InData_HashType[],
                                                    const uint32_t InData_Cmd[],
                                                    const uint32_t InData_Msg[],
                                                    const uint32_t InData_MsgLen[],
                                                    const uint32_t InData_State[],
                                                    uint32_t       OutData_MsgDigest[],
                                                    uint32_t       OutData_State[],
                                                    const uint32_t MAX_CNT);

#endif
extern fsp_err_t HW_SCE_ShaGenerateMessageDigestSubGeneral(const uint32_t InData_HashType[],
                                                           const uint32_t InData_Cmd[],
                                                           const uint32_t InData_Msg[],
                                                           const uint32_t InData_MsgLen[],
                                                           const uint32_t InData_State[],
                                                           uint32_t       OutData_MsgDigest[],
                                                           uint32_t       OutData_State[],
                                                           const uint32_t MAX_CNT,
                                                           const uint32_t InData_InitVal[]);

#endif                                 /* HW_SCE_HASH_PRIVATE_H */
