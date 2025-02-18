/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/////////////////////////////////////////////////////////////////////////
// <SC32#4 AES-128 Encryption with CBC Mode>                           //
// Procedure number: 06                                                //
// File name      : SC324_p06.prc                                      //
// State Diagram  : main(FSM1)                                         //
// Start State    : main03                                             //
// End State      : main03                                             //
// Input Data     : InData_Key[4]                                      //
// : InData_IV[4]                                       //
// : InData_Text[MAX_CNT]                               //
// Output Data    : OutData_Text[MAX_CNT]                              //
// : (MAX_CNT is Multiples of four.)                    //
// OutData_IV[4]                                      //
// Return Value   : Pass, Fail or Resource_Conflict                    //
// ---------------------------------------------------------------------//
// total cycle    : polling + write access + read access               //
// polling        : 329 + (MAX_CNT/4-1)*44 cycle                       //
// polling access :  12 + (MAX_CNT/4-1)*2  times                       //
// write access   :  50 + (MAX_CNT-4) times                            //
// read  access   :   4 + (MAX_CNT-4) times                            //
/////////////////////////////////////////////////////////////////////////

#include "sc324_aes_private.h"

#include "hw_sce_aes_private.h"

/*******************************************************************************************************************//**
 * Encryption with AES 128-bit key in CBC chaining mode.
 *
 * @param[in]  InData_Key      In data key
 * @param[in]  InData_IV       In data iv
 * @param[in]  num_words       The number words
 * @param[in]  InData_Text     In data text
 * @param      OutData_Text    The out data text
 * @param      OutData_IV      The out data iv
 *
 * @retval FSP_SUCCESS          The operation completed successfully.
 * @retval FSP_ERR_CRYPTO_INVALID_SIZE          The size of the data must be multiples of 4 WORDS / 16 bytes.
 **********************************************************************************************************************/
fsp_err_t HW_SCE_AES_128CbcEncrypt (const uint32_t * InData_Key,
                                    const uint32_t * InData_IV,
                                    const uint32_t   num_words,
                                    const uint32_t * InData_Text,
                                    uint32_t       * OutData_Text,
                                    uint32_t       * OutData_IV)
{
    hw_sc324_aes_ctrl_t aesCtrl;

    aesCtrl.encrypt_flag = SC324_AES_ENCRYPT;
    aesCtrl.keysize      = SC324_AES_KEYSIZE_128;
    aesCtrl.mode         = SC324_AES_CBC;

    return hw_sc324_aes_kernel_process_data(&aesCtrl,
                                            InData_Key,
                                            InData_IV,
                                            num_words,
                                            InData_Text,
                                            OutData_Text,
                                            OutData_IV);
}
