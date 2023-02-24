/***********************************************************************************************************************
 * Copyright [2020-2023] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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

#ifndef SC324_AES_PRIVATE_H
#define SC324_AES_PRIVATE_H

#include <stdint.h>
#include "bsp_api.h"

typedef enum e_hw_sc324_aes_modes
{
    SC324_AES_ECB = 0,
    SC324_AES_CBC = 1,
    SC324_AES_CTR = 2,
} hw_sc324_aes_modes_t;

typedef enum e_hw_sc324_aes_keysize
{
    SC324_AES_KEYSIZE_128 = 0,
    SC324_AES_KEYSIZE_256 = 1
} hw_sc324_aes_keysizes_t;

typedef enum e_hw_sc324_aes_encrypt_flag
{
    SC324_AES_ENCRYPT = 0,
    SC324_AES_DECRYPT = 1
} hw_sc324_aes_encrypt_flag_t;

typedef struct st_hw_sc324_aes_cfg
{
    hw_sc324_aes_keysizes_t keysize;
    hw_sc324_aes_modes_t    mode;
} hw_sc324_aes_cfg_t;

typedef struct st_hw_sc324_aes_ctrl
{
    hw_sc324_aes_keysizes_t     keysize;
    hw_sc324_aes_modes_t        mode;
    hw_sc324_aes_encrypt_flag_t encrypt_flag;
} hw_sc324_aes_ctrl_t;

fsp_err_t hw_sc324_aes_kernel_process_data(hw_sc324_aes_ctrl_t * p_ctrl,
                                           const uint32_t      * InData_Key,
                                           const uint32_t      * InData_IV,
                                           const uint32_t        num_words,
                                           const uint32_t      * InData_Text,
                                           uint32_t            * OutData_Text,
                                           uint32_t            * OutData_IV);

#endif                                 /* SC324_AES_PRIVATE_H */
