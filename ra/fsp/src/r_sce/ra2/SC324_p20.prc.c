/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/////////////////////////////////////////////////////////////////////////
// <SC32#4 AES-256 Encryption ECB Mode>                                //
// Procedure number: 20                                                //
// File name      : SC324_p20.prc                                      //
// State Diagram  : main(FSM1)                                         //
// Start State    : main03                                             //
// End State      : main03                                             //
// Input Data     : InData_Key[8]                                      //
// : InData_Text[MAX_CNT]                               //
// Output Data    : OutData_Text[MAX_CNT]                              //
// : (MAX_CNT is Multiples of four.)                    //
// Return Value   : Pass, Fail or Resource_Conflict                    //
// ---------------------------------------------------------------------//
// total cycle    : polling + write access + read access               //
// polling        :                                                    //
// polling access :                                                    //
// write access   :                                                    //
// read  access   :                                                    //
/////////////////////////////////////////////////////////////////////////

#include "sc324_aes_private.h"

#include "hw_sce_aes_private.h"

/*******************************************************************************************************************//**
 * AES-256 Encryption ECB Mode
 *
 * @param[in]  InData_Key      In data key
 * @param[in]  num_words       The number words
 * @param[in]  InData_Text     In data text
 * @param      OutData_Text    The out data text
 *
 * @retval FSP_SUCCESS          The operation completed successfully.
 * @retval FSP_ERR_CRYPTO_INVALID_SIZE          The size of the data must be multiples of 4 WORDS / 16 bytes.
 **********************************************************************************************************************/
fsp_err_t HW_SCE_AES_256EcbEncrypt (const uint32_t * InData_Key,
                                    const uint32_t   num_words,
                                    const uint32_t * InData_Text,
                                    uint32_t       * OutData_Text)
{
    hw_sc324_aes_ctrl_t aesCtrl;

    aesCtrl.encrypt_flag = SC324_AES_ENCRYPT;
    aesCtrl.keysize      = SC324_AES_KEYSIZE_256;
    aesCtrl.mode         = SC324_AES_ECB;

    return hw_sc324_aes_kernel_process_data(&aesCtrl, InData_Key, NULL, num_words, InData_Text, OutData_Text, NULL);
}
