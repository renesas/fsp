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

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

#include "sc324_aes_private.h"
#include "hw_sce_private.h"
#include "hw_sce_aes_private.h"

__STATIC_INLINE void hw_sc324_aes_kernel_module_enable ()
{
    R_AES->AESMOD_b.MODEN = 1;
}

__STATIC_INLINE void hw_sc324_aes_kernel_module_disable ()
{
    R_AES->AESMOD_b.MODEN = 0;
}

__STATIC_INLINE void hw_sc324_aes_kernel_wait_com_write_ready ()
{
    // wait for com_write_ready
    while (R_AES->AESCMD_b.CWRDY == 0)
    {
        ;
    }
}

__STATIC_INLINE void hw_sc324_aes_kernel_inverse_cipher_set (hw_sc324_aes_encrypt_flag_t flag)
{
    // wait for com_write_ready
    hw_sc324_aes_kernel_wait_com_write_ready();

    // set the inverse_cipher mode to encrypt
    R_AES->AESCMD_b.INVCIP = flag;
}

__STATIC_INLINE void hw_sc324_aes_kernel_chaining_mode_set (hw_sc324_aes_modes_t aes_chaining_mode)
{
    // wait for com_write_ready
    hw_sc324_aes_kernel_wait_com_write_ready();
    R_AES->AESCMD_b.CHAIN = aes_chaining_mode;
}

static void hw_sc324_aes_endian_convert (uint32_t * p_dest, const uint32_t * p_source, uint32_t num_words)
{
    uint32_t nw;
    for (nw = 0; nw < num_words; nw++)
    {
        p_dest[nw] = __REV(p_source[nw]);
    }
}

static void hw_sc324_aes_kernel_key_set (const uint32_t * p_key, hw_sc324_aes_keysizes_t key_length)
{
    uint32_t temp[4];

    // wait for com_write_ready
    hw_sc324_aes_kernel_wait_com_write_ready();

    // set the key_length
    R_AES->AESCMD_b.KEYLN = key_length;

    // wait for key_write_ready0
    while (R_AES->AESCMD_b.KWRDY0 == 0)
    {
        ;
    }

    hw_sc324_aes_endian_convert(temp, (uint32_t *) p_key, 4);
    R_AES->AESKW0 = temp[0];
    R_AES->AESKW0 = temp[1];
    R_AES->AESKW0 = temp[2];
    R_AES->AESKW0 = temp[3];

    if (key_length == SC324_AES_KEYSIZE_128)
    {
        return;
    }

    // wait for key_write_ready1
    while (R_AES->AESCMD_b.KWRDY1 == 0)
    {
        ;
    }

    hw_sc324_aes_endian_convert(temp, (uint32_t *) p_key + 4, 4);
    R_AES->AESKW1 = temp[0];
    R_AES->AESKW1 = temp[1];
    R_AES->AESKW1 = temp[2];
    R_AES->AESKW1 = temp[3];
}

static void hw_sc324_aes_kernel_iv_set (const uint32_t * p_iv)
{
    uint32_t temp[4];

    // wait for iv_write_ready
    while (R_AES->AESCMD_b.IWRDY == 0)
    {
        ;
    }

    hw_sc324_aes_endian_convert(temp, p_iv, 4);
    R_AES->AESIVW = temp[0];
    R_AES->AESIVW = temp[1];
    R_AES->AESIVW = temp[2];
    R_AES->AESIVW = temp[3];
}

static void hw_sc324_aes_kernel_iv_get (uint32_t * p_iv)
{
    uint32_t temp[4];

    // wait for iv_read_ready
    while (R_AES->AESCMD_b.IRRDY == 0)
    {
        ;
    }

    temp[0] = R_AES->AESIVW;
    temp[1] = R_AES->AESIVW;
    temp[2] = R_AES->AESIVW;
    temp[3] = R_AES->AESIVW;

    hw_sc324_aes_endian_convert(p_iv, temp, 4);
}

static void hw_sc324_aes_kernel_data_write (const uint32_t * p_data)
{
    uint32_t temp[4];

    // wait for write_ready
    while (R_AES->AESCMD_b.DWRDY == 0)
    {
        ;
    }

    hw_sc324_aes_endian_convert(temp, (uint32_t *) p_data, 4);
    R_AES->AESDW = temp[0];
    R_AES->AESDW = temp[1];
    R_AES->AESDW = temp[2];
    R_AES->AESDW = temp[3];
}

static void hw_sc324_aes_kernel_data_read (uint32_t * p_data)
{
    uint32_t temp[4];

    // wait for read_ready
    while (R_AES->AESCMD_b.DRRDY == 0)
    {
        ;
    }

    temp[0] = R_AES->AESDW;
    temp[1] = R_AES->AESDW;
    temp[2] = R_AES->AESDW;
    temp[3] = R_AES->AESDW;
    hw_sc324_aes_endian_convert(p_data, temp, 4);
}

/*******************************************************************************************************************//**
 * Helper routine to process AES encryption and Decryption.
 *
 * @param      p_ctrl          The control
 * @param[in]  InData_Key      In data key
 * @param[in]  InData_IV       In data iv
 * @param[in]  num_words       The number words
 * @param[in]  InData_Text     In data text
 * @param      OutData_Text    The out data text
 * @param      OutData_IV      The out data iv
 *
 * @retval FSP_SUCCESS                          The operation completed successfully.
 * @retval FSP_ERR_CRYPTO_INVALID_SIZE          The size of the data must be multiples of 4 WORDS / 16 bytes.
 *
 **********************************************************************************************************************/
fsp_err_t hw_sc324_aes_kernel_process_data (hw_sc324_aes_ctrl_t * p_ctrl,
                                            const uint32_t      * InData_Key,
                                            const uint32_t      * InData_IV,
                                            const uint32_t        num_words,
                                            const uint32_t      * InData_Text,
                                            uint32_t            * OutData_Text,
                                            uint32_t            * OutData_IV)
{
    // truncate the number of words to process to multiples of 16 bytes (1 block of data)
    if ((0 == num_words) || (0 != (num_words % SIZE_AES_BLOCK_WORDS)))
    {
        return FSP_ERR_CRYPTO_INVALID_SIZE;
    }

    // 1. Enable AES Module (set the AESMOD.module_en to 1)
    hw_sc324_aes_kernel_module_enable();

    // 2. Write the key to key_register0 or key_register1
    // When writing to the key-register0, write 1 word (32 bits) to AESKW0
    // after confirmation of key_write_ready0 = 1
    // When writing to the key-register1, write 1 word (32 bits) to AESKW1
    // after confirmation of key_write_ready1 = 1
    hw_sc324_aes_kernel_key_set(InData_Key, p_ctrl->keysize);

    // 3. In CBC or CTR mode, write IV data to iv-register
    // When writing to iv-register, you must write the whole 4 words of data.
    hw_sc324_aes_kernel_chaining_mode_set(p_ctrl->mode);
    if (InData_IV)
    {
        hw_sc324_aes_kernel_iv_set(InData_IV);
    }

    // 4. Write the setting data to AESCMD
    // When writing to the AESCMD, check if the AESCMD.com_write_ready is 1
    hw_sc324_aes_kernel_inverse_cipher_set(p_ctrl->encrypt_flag);

    for (uint32_t indx = 0; indx < num_words; indx += SIZE_AES_BLOCK_WORDS)
    {
        // 5. Write data to data-register (one block (128 bits) of data).
        // When writing to data-register, write 1 word (32 bits) to AESDW after confirmation of write_ready=1
        // When you write to the data-register, you write the whole 4 words of data.
        hw_sc324_aes_kernel_data_write(InData_Text + indx);

        // 6. When encrypt (decrypt) is completed, read_ready will be 1. The read_request will be asserted
        // and you will be able to read the data on which encrypt (decrypt) was done. Please read
        // 1 word (32 bits) from AESDW.
        // When reading iv_data, read 1 word (32 bits) from AESIVW after confirmation of iv_read_ready=1
        // When you read the iv-window, you must read the whole 4 words of data.
        hw_sc324_aes_kernel_data_read(OutData_Text + indx);

        // 7. When encrypt (decrypt) is completed, write_ready will be 1. The write_request will be
        // asserted. When continuing encrypting (decrypting), write 1 block of data (128 bits) to
        // data-register.
        // When you write to the data-window, you must write the whole 4 words of data.
        // When writing to data-register, write 1 word (32 bits) to AESDW after confirmation of write_ready=1
        continue;
    }

    if (OutData_IV)
    {
        hw_sc324_aes_kernel_iv_get(OutData_IV);
    }

    // 8. When ending use of a AES module, please write 0 to mode-register.module_en
    hw_sc324_aes_kernel_module_disable();

    return FSP_SUCCESS;
}
