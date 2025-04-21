/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "rm_ocrypto_port_aes_helpers.h"
#include "hw_sce_ra_private.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Global Variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/
void ocrypto_aes_helper_init (size_t aes_size, const uint32_t * sce_cmd, const uint32_t * xkey, const uint32_t * iv)
{
    uint32_t key_type = 0;
    if (SIZE_AES_192BIT_KEYLEN_BYTES == aes_size)
    {
        /* Not supported */
        HW_SCE_Aes192EncryptDecryptInitSub(sce_cmd, xkey, iv);
    }
    else if (SIZE_AES_256BIT_KEYLEN_BYTES == aes_size)
    {
        HW_SCE_Aes256EncryptDecryptInitSubAdaptor(&key_type, sce_cmd, xkey, 0, iv);
    }
    else
    {
        HW_SCE_Aes128EncryptDecryptInitSubAdaptor(&key_type, sce_cmd, xkey, 0, iv);
    }
}

void ocrypto_aes_helper_update (size_t aes_size, const uint32_t * in_data, uint32_t * out_data,
                                const uint32_t data_size)
{
    if (SIZE_AES_192BIT_KEYLEN_BYTES == aes_size)
    {
        /* Not supported */
        HW_SCE_Aes192EncryptDecryptUpdateSub(in_data, out_data, data_size);
    }
    else if (SIZE_AES_256BIT_KEYLEN_BYTES == aes_size)
    {
        HW_SCE_Aes256EncryptDecryptUpdateSub(in_data, out_data, data_size);
    }
    else
    {
        HW_SCE_Aes128EncryptDecryptUpdateSub(in_data, out_data, data_size);
    }
}
