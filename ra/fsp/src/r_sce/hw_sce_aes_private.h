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

/*******************************************************************************************************************//**
 * @ingroup SCE_PROC
 * @addtogroup SCE_PROC_AES
 * @{
 ***********************************************************************************************************************/

#ifndef HW_SCE_AES_PRIVATE_H
#define HW_SCE_AES_PRIVATE_H

#include <stdint.h>
#include "bsp_api.h"

typedef struct st_sce_data
{
    uint32_t   length;
    uint32_t * p_data;
} r_sce_data_t;

extern fsp_err_t HW_SCE_AES_128EcbEncrypt(const uint32_t * InData_Key,
                                          const uint32_t   num_words,
                                          const uint32_t * InData_Text,
                                          uint32_t       * OutData_Text);

extern fsp_err_t HW_SCE_AES_128EcbDecrypt(const uint32_t * InData_Key,
                                          const uint32_t   num_words,
                                          const uint32_t * InData_Text,
                                          uint32_t       * OutData_Text);

extern fsp_err_t HW_SCE_AES_128CbcEncrypt(const uint32_t * InData_Key,
                                          const uint32_t * InData_IV,
                                          const uint32_t   num_words,
                                          const uint32_t * InData_Text,
                                          uint32_t       * OutData_Text,
                                          uint32_t       * OutData_IV);

extern fsp_err_t HW_SCE_AES_128CbcDecrypt(const uint32_t * InData_Key,
                                          const uint32_t * InData_IV,
                                          const uint32_t   num_words,
                                          const uint32_t * InData_Text,
                                          uint32_t       * OutData_Text,
                                          uint32_t       * OutData_IV);

extern fsp_err_t HW_SCE_AES_128CtrEncrypt(const uint32_t * InData_Key,
                                          const uint32_t * InData_IV,
                                          const uint32_t   num_words,
                                          const uint32_t * InData_Text,
                                          uint32_t       * OutData_Text,
                                          uint32_t       * OutData_IV);

extern fsp_err_t HW_SCE_AES_128XtsEncrypt(const uint32_t * InData_Key,
                                          const uint32_t * InData_IV,
                                          const uint32_t * InData_Len,
                                          const uint32_t * InData_Text,
                                          uint32_t       * OutData_Text,
                                          uint32_t       * OutData_IV);

extern fsp_err_t HW_SCE_AES_128XtsDecrypt(const uint32_t * InData_Key,
                                          const uint32_t * InData_IV,
                                          const uint32_t * InData_Len,
                                          const uint32_t * InData_Text,
                                          uint32_t       * OutData_Text,
                                          uint32_t       * OutData_IV);

extern fsp_err_t HW_SCE_AES_256EcbEncrypt(const uint32_t * InData_Key,
                                          const uint32_t   num_words,
                                          const uint32_t * InData_Text,
                                          uint32_t       * OutData_Text);

extern fsp_err_t HW_SCE_AES_256EcbDecrypt(const uint32_t * InData_Key,
                                          const uint32_t   num_words,
                                          const uint32_t * InData_Text,
                                          uint32_t       * OutData_Text);

extern fsp_err_t HW_SCE_AES_256CbcEncrypt(const uint32_t * InData_Key,
                                          const uint32_t * InData_IV,
                                          const uint32_t   num_words,
                                          const uint32_t * InData_Text,
                                          uint32_t       * OutData_Text,
                                          uint32_t       * OutData_IV);

extern fsp_err_t HW_SCE_AES_256CbcDecrypt(const uint32_t * InData_Key,
                                          const uint32_t * InData_IV,
                                          const uint32_t   num_words,
                                          const uint32_t * InData_Text,
                                          uint32_t       * OutData_Text,
                                          uint32_t       * OutData_IV);

extern fsp_err_t HW_SCE_AES_256CtrEncrypt(const uint32_t * InData_Key,
                                          const uint32_t * InData_IV,
                                          const uint32_t   num_words,
                                          const uint32_t * InData_Text,
                                          uint32_t       * OutData_Text,
                                          uint32_t       * OutData_IV);

extern fsp_err_t HW_SCE_AES_256XtsEncrypt(const uint32_t * InData_Key,
                                          const uint32_t * InData_IV,
                                          const uint32_t * InData_Len,
                                          const uint32_t * InData_Text,
                                          uint32_t       * OutData_Text,
                                          uint32_t       * OutData_IV);

extern fsp_err_t HW_SCE_AES_256XtsDecrypt(const uint32_t * InData_Key,
                                          const uint32_t * InData_IV,
                                          const uint32_t * InData_Len,
                                          const uint32_t * InData_Text,
                                          uint32_t       * OutData_Text,
                                          uint32_t       * OutData_IV);

#endif                                 /* HW_SCE_AES_PRIVATE_H */

/*******************************************************************************************************************//**
 * @}
 **********************************************************************************************************************/
