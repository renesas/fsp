/*
 * FreeRTOS PKCS #11 V2.0.3
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://aws.amazon.com/freertos
 * http://www.FreeRTOS.org
 */

/* FreeRTOS Includes. */
#if defined(__ARMCC_VERSION)
 #pragma GCC diagnostic push
 #pragma GCC diagnostic ignored "-Wmacro-redefined"
#endif

#include "core_pkcs11.h"

#if defined(__ARMCC_VERSION)
 #pragma GCC diagnostic pop
#endif

#include "core_pkcs11_config.h"
#include "FreeRTOS.h"
#include "task.h"
#include "mbedtls/sha256.h"

/* C runtime includes. */
#include <stdio.h>
#include <string.h>

#include "rm_aws_pkcs11_pal.h"
#include "r_flash_hp.h"

#define FLASH_HP_DATA_BLOCK_NUM    (1024U)
typedef struct _pkcs_data
{
    CK_ATTRIBUTE     Label;
    uint32_t         local_storage_index;
    uint32_t         ulDataSize;
    uint32_t         status;
    CK_OBJECT_HANDLE xHandle;
} PKCS_DATA;

#define PKCS_DATA_STATUS_EMPTY                  0
#define PKCS_DATA_STATUS_REGISTERED             1
#define PKCS_DATA_STATUS_HIT                    2

#define PKCS_HANDLES_LABEL_MAX_LENGTH           40
#define PKCS_OBJECT_HANDLES_NUM                 5
#define PKCS_SHA256_LENGTH                      32

#define MAX_CHECK_DATAFLASH_AREA_RETRY_COUNT    3

typedef struct _pkcs_storage_control_block_sub
{
    // This looks like a bug; not sure why the local_storage is this large
    uint8_t local_storage[((BSP_FEATURE_FLASH_HP_DF_BLOCK_SIZE * FLASH_HP_DATA_BLOCK_NUM) / 4) -
                          (sizeof(PKCS_DATA) * PKCS_OBJECT_HANDLES_NUM) - PKCS_SHA256_LENGTH]; /* RX65N case: 8KB */
    PKCS_DATA pkcs_data[PKCS_OBJECT_HANDLES_NUM];
} PKCS_STORAGE_CONTROL_BLOCK_SUB;

typedef struct _PKCS_CONTROL_BLOCK
{
    PKCS_STORAGE_CONTROL_BLOCK_SUB data;
    uint8_t hash_sha256[PKCS_SHA256_LENGTH];
} PKCS_CONTROL_BLOCK;

enum eObjectHandles
{
    eInvalidHandle       = 0,          /* According to PKCS #11 spec, 0 is never a valid object handle. */
    eAwsDevicePrivateKey = 1,
    eAwsDevicePublicKey,
    eAwsDeviceCertificate,
    eAwsCodeSigningKey,

    // eAwsRootCertificate
};

uint8_t object_handle_dictionary[PKCS_OBJECT_HANDLES_NUM][PKCS_HANDLES_LABEL_MAX_LENGTH] =
{
    "",
    pkcs11configLABEL_DEVICE_PRIVATE_KEY_FOR_TLS,
    pkcs11configLABEL_DEVICE_PUBLIC_KEY_FOR_TLS,
    pkcs11configLABEL_DEVICE_CERTIFICATE_FOR_TLS,
    pkcs11configLABEL_CODE_VERIFICATION_KEY,

    // pkcs11configLABEL_ROOT_CERTIFICATE,
};

static PKCS_CONTROL_BLOCK pkcs_control_block_data_image =
{
    .hash_sha256 =
    {
        0x62, 0x90, 0xe6, 0x59, 0x20, 0x47, 0xec, 0x80, 0x14, 0x0a, 0x12, 0x52, 0xd3, 0x1a, 0x8b, 0xa8, 0xa3, 0x3a, // NOLINT(readability-magic-numbers)
        0x34, 0xcf, 0x57, 0x8b, 0x5c, 0x8c, 0x4a, 0x08, 0x17, 0x06, 0xb9, 0x41, 0x6f, 0xa6                          // NOLINT(readability-magic-numbers)
    },
};

static const PKCS_CONTROL_BLOCK pkcs_control_block_data BSP_PLACE_IN_SECTION (".data_flash") =
{
    .hash_sha256 =
    {
        0x62, 0x90, 0xe6, 0x59, 0x20, 0x47, 0xec, 0x80, 0x14, 0x0a, 0x12, 0x52, 0xd3, 0x1a, 0x8b, 0xa8, 0xa3, 0x3a,
        0x34, 0xcf, 0x57, 0x8b, 0x5c, 0x8c, 0x4a, 0x08, 0x17, 0x06, 0xb9, 0x41, 0x6f, 0xa6
    },                                 // NOLINT(readability-magic-numbers)
};
static const PKCS_CONTROL_BLOCK pkcs_control_block_data_mirror BSP_PLACE_IN_SECTION (".data_flash") =
{
    .hash_sha256 =
    {
        0x62, 0x90, 0xe6, 0x59, 0x20, 0x47, 0xec, 0x80, 0x14, 0x0a, 0x12, 0x52, 0xd3, 0x1a, 0x8b, 0xa8, 0xa3, 0x3a,
        0x34, 0xcf, 0x57, 0x8b, 0x5c, 0x8c, 0x4a, 0x08, 0x17, 0x06, 0xb9, 0x41, 0x6f, 0xa6
    },                                 // NOLINT(readability-magic-numbers)
};

static uint32_t update_dataflash_data_from_image(flash_ctrl_t * const p_flash_ctrl);
static uint32_t update_dataflash_data_mirror_from_image(flash_ctrl_t * const p_flash_ctrl);
static uint32_t check_dataflash_area(uint32_t retry_counter, flash_ctrl_t * const p_flash_ctrl);

extern CK_RV prvMbedTLS_Initialize(void);

fsp_err_t         fsp_err;
const flash_cfg_t fsp_flash_cfg =
{
    .data_flash_bgo = false,
    .p_callback     = NULL,
    .p_context      = NULL,
    .irq            = FSP_INVALID_VECTOR,
    .err_irq        = FSP_INVALID_VECTOR,
    .err_ipl        = (BSP_IRQ_DISABLED),
    .ipl            = (BSP_IRQ_DISABLED),
};

// CK_RV C_Initialize( CK_VOID_PTR pvInitArgs )
// {
// flash_hp_instance_ctrl_t fsp_flash_ctrl = {0};

////R_FLASH_Open();
// fsp_err = R_FLASH_HP_Open (&fsp_flash_ctrl, &fsp_flash_cfg);
// if (FSP_SUCCESS != fsp_err)
// {
// return CKR_GENERAL_ERROR;
// }

////FSP_Removed
//// #if defined (BSP_MCU_RX63N) || (BSP_MCU_RX631) || (BSP_MCU_RX630)
////     flash_access_window_config_t flash_access_window_config;
////     flash_access_window_config.read_en_mask = 0xffff;
////     flash_access_window_config.write_en_mask = 0xffff;
////     R_FLASH_Control(FLASH_CMD_ACCESSWINDOW_SET, &flash_access_window_config);
//// #endif

/// * check the hash */
// check_dataflash_area(0, &fsp_flash_ctrl);

/// * copy data from storage to ram */
// memcpy(&pkcs_control_block_data_image, (void *)&pkcs_control_block_data, sizeof(pkcs_control_block_data_image));

////R_FLASH_Close();
// R_FLASH_HP_Close(&fsp_flash_ctrl);

// prvMbedTLS_Initialize();

// return CKR_OK;
// }

/*
 *  @brief Initialize the PAL.
 */
CK_RV PKCS11_PAL_Initialize ()
{
    return CKR_OK;
}

/**
 * @brief Writes a file to local storage.
 *
 * Port-specific file write for cryptographic information.
 *
 * @param[in] pxLabel       Label of the object to be saved.
 * @param[in] pucData       Data buffer to be written to file
 * @param[in] ulDataSize    Size (in bytes) of data to be saved.
 *
 * @return The file handle of the object that was stored.
 */
CK_OBJECT_HANDLE PKCS11_PAL_SaveObject (CK_ATTRIBUTE_PTR pxLabel, uint8_t * pucData, uint32_t ulDataSize)
{
    CK_OBJECT_HANDLE xHandle = eInvalidHandle;

    // int i;
    uint8_t                hash_sha256[PKCS_SHA256_LENGTH];
    mbedtls_sha256_context ctx;

    mbedtls_sha256_init(&ctx);
    flash_hp_instance_ctrl_t fsp_flash_ctrl = {0};

    // R_FLASH_Open();
    fsp_err = R_FLASH_HP_Open(&fsp_flash_ctrl, &fsp_flash_cfg);
    if (FSP_SUCCESS != fsp_err)
    {
        return CKR_GENERAL_ERROR;
    }

    /* check the hash */
    if (0 != check_dataflash_area(0, &fsp_flash_ctrl))
    {
        return CKR_GENERAL_ERROR;
    }

    /* copy data from storage to ram */
    memcpy(&pkcs_control_block_data_image, (void *) &pkcs_control_block_data, sizeof(pkcs_control_block_data_image));

    /* search specified label value from object_handle_dictionary */
    for (uint32_t i = 1; i < PKCS_OBJECT_HANDLES_NUM; i++)
    {
        if (!strcmp((char *) &object_handle_dictionary[i], pxLabel->pValue))
        {
            xHandle = i;
        }
    }

    if (xHandle != eInvalidHandle)
    {
        /* pre-calculate -> total stored data size : pre-calculate phase */
        uint32_t total_stored_data_size = 0;

        for (uint32_t i = 1; i < PKCS_OBJECT_HANDLES_NUM; i++)
        {
            if (pkcs_control_block_data_image.data.pkcs_data[i].status == PKCS_DATA_STATUS_REGISTERED)
            {
                total_stored_data_size += pkcs_control_block_data_image.data.pkcs_data[i].ulDataSize;
            }
        }

        /* remove current xHandle from pkcs_data */
        if (pkcs_control_block_data_image.data.pkcs_data[xHandle].status == PKCS_DATA_STATUS_REGISTERED)
        {
            uint32_t move_target_xHandle = 0;
            uint32_t move_target_index   = 0;

            uint32_t delete_target_index =
                pkcs_control_block_data_image.data.pkcs_data[xHandle].local_storage_index;
            uint32_t delete_target_data_size = pkcs_control_block_data_image.data.pkcs_data[xHandle].ulDataSize;

            /* Search move target index and handle  */
            for (uint32_t i = 1; i < PKCS_OBJECT_HANDLES_NUM; i++)
            {
                if ((pkcs_control_block_data_image.data.pkcs_data[i].status == PKCS_DATA_STATUS_REGISTERED) &&
                    (pkcs_control_block_data_image.data.pkcs_data[i].local_storage_index ==
                     (delete_target_index + delete_target_data_size)))
                {
                    move_target_xHandle = i;
                    move_target_index   = pkcs_control_block_data_image.data.pkcs_data[i].local_storage_index;
                    break;
                }
            }

            if (move_target_xHandle != 0)
            {
                /* Move target index to delete target index */
                memmove((void *) &pkcs_control_block_data_image.data.local_storage[delete_target_index],
                        (void *) &pkcs_control_block_data_image.data.local_storage[move_target_index],
                        (size_t) total_stored_data_size - move_target_index);

                /* Fix index of all moved data  */
                for (uint32_t i = 1; i < PKCS_OBJECT_HANDLES_NUM; i++)
                {
                    if (pkcs_control_block_data_image.data.pkcs_data[i].local_storage_index > delete_target_index)
                    {
                        pkcs_control_block_data_image.data.pkcs_data[i].local_storage_index -= delete_target_data_size;
                    }
                }
            }

            /* Recalculate the end of data storage  */
            total_stored_data_size -= delete_target_data_size;

            pkcs_control_block_data_image.data.pkcs_data[xHandle].local_storage_index = 0;
            pkcs_control_block_data_image.data.pkcs_data[xHandle].ulDataSize          = 0;
        }

        pkcs_control_block_data_image.data.pkcs_data[xHandle].Label.type          = pxLabel->type;
        pkcs_control_block_data_image.data.pkcs_data[xHandle].Label.ulValueLen    = pxLabel->ulValueLen;
        pkcs_control_block_data_image.data.pkcs_data[xHandle].local_storage_index = total_stored_data_size;
        pkcs_control_block_data_image.data.pkcs_data[xHandle].ulDataSize          = ulDataSize;
        pkcs_control_block_data_image.data.pkcs_data[xHandle].status              = PKCS_DATA_STATUS_REGISTERED;
        pkcs_control_block_data_image.data.pkcs_data[xHandle].xHandle             = xHandle;
        memcpy(&pkcs_control_block_data_image.data.local_storage[total_stored_data_size], pucData, ulDataSize);

        /* update the hash */
        mbedtls_sha256_starts_ret(&ctx, 0); /* 0 means SHA256 context */
        mbedtls_sha256_update_ret(&ctx, (unsigned char *) &pkcs_control_block_data_image.data,
                                  sizeof(pkcs_control_block_data.data));
        mbedtls_sha256_finish_ret(&ctx, hash_sha256);
        memcpy(pkcs_control_block_data_image.hash_sha256, hash_sha256, sizeof(hash_sha256));

        /* update data from ram to storage */
        if (update_dataflash_data_from_image(&fsp_flash_ctrl))
        {
            xHandle = eInvalidHandle;
        }
        else if (update_dataflash_data_mirror_from_image(&fsp_flash_ctrl))
        {
            xHandle = eInvalidHandle;
        }
        else
        {
            // Nothing to do
        }
    }

    R_FLASH_HP_Close(&fsp_flash_ctrl);

    return xHandle;
}

/**
 * @brief Translates a PKCS #11 label into an object handle.
 *
 * Port-specific object handle retrieval.
 *
 *
 * @param[in] pxLabel         Pointer to the label of the object
 *                           who's handle should be found.
 * @param[in] usLength       The length of the label, in bytes.
 *
 * @return The object handle if operation was successful.
 * Returns eInvalidHandle if unsuccessful.
 */
CK_OBJECT_HANDLE PKCS11_PAL_FindObject (uint8_t * pxLabel, uint8_t usLength)
{
    /* Avoid compiler warnings about unused variables. */
    FSP_PARAMETER_NOT_USED(usLength);

    CK_OBJECT_HANDLE xHandle = eInvalidHandle;
    uint32_t         i;

    for (i = 1; i < PKCS_OBJECT_HANDLES_NUM; i++)
    {
        if (!strcmp((char *) &object_handle_dictionary[i], (char *) pxLabel))
        {
            if (pkcs_control_block_data_image.data.pkcs_data[i].status == PKCS_DATA_STATUS_REGISTERED)
            {
                xHandle = (CK_OBJECT_HANDLE) i;
            }
        }
    }

    return xHandle;
}

/**
 * @brief Gets the value of an object in storage, by handle.
 *
 * Port-specific file access for cryptographic information.
 *
 * This call dynamically allocates the buffer which object value
 * data is copied into.  PKCS11_PAL_GetObjectValueCleanup()
 * should be called after each use to free the dynamically allocated
 * buffer.
 *
 * @sa PKCS11_PAL_GetObjectValueCleanup
 *
 * @param[in]  xHandle      Handle of the file to be read.
 * @param[out] ppucData     Pointer to buffer for file data.
 * @param[out] pulDataSize  Size (in bytes) of data located in file.
 * @param[out] xIsPrivate   Boolean indicating if value is private (CK_TRUE)
 *                          or exportable (CK_FALSE)
 *
 * @return CKR_OK if operation was successful.  CKR_KEY_HANDLE_INVALID if
 * no such object handle was found, CKR_DEVICE_MEMORY if memory for
 * buffer could not be allocated, CKR_FUNCTION_FAILED for device driver
 * error.
 */
CK_RV PKCS11_PAL_GetObjectValue (CK_OBJECT_HANDLE xHandle,
                                 uint8_t       ** ppucData,
                                 uint32_t       * pulDataSize,
                                 CK_BBOOL       * xIsPrivate)
{
    CK_RV            xReturn        = CKR_FUNCTION_FAILED;
    CK_OBJECT_HANDLE xHandleStorage = xHandle;

    if (xHandleStorage == eAwsDevicePublicKey)
    {
        xHandleStorage = eAwsDevicePrivateKey;
    }

    if (xHandle != eInvalidHandle)
    {
        *ppucData =
            &pkcs_control_block_data_image.data.local_storage[pkcs_control_block_data_image.data.pkcs_data[
                                                                  xHandleStorage].
                                                              local_storage_index];
        *pulDataSize = pkcs_control_block_data_image.data.pkcs_data[xHandleStorage].ulDataSize;

        if (xHandle == eAwsDevicePrivateKey)
        {
            *xIsPrivate = CK_TRUE;
        }
        else
        {
            *xIsPrivate = CK_FALSE;
        }

        xReturn = CKR_OK;
    }

    return xReturn;
}

/**
 * @brief Cleanup after PKCS11_GetObjectValue().
 *
 * @param[in] pucBuffer       The buffer to free.
 *                          (*ppucData from PKCS11_PAL_GetObjectValue())
 * @param[in] ulBufferSize    The length of the buffer to free.
 *                          (*pulDataSize from PKCS11_PAL_GetObjectValue())
 */
void PKCS11_PAL_GetObjectValueCleanup (uint8_t * pucBuffer, uint32_t ulBufferSize)
{
    /* Avoid compiler warnings about unused variables. */
    FSP_PARAMETER_NOT_USED(pucBuffer);
    FSP_PARAMETER_NOT_USED(ulBufferSize);
}

/*******************************************************************************************************************//**
 * This function is used to update the main block with data from provided RAM context.
 * @retval
 *       1 succeeded
 *       0 failed
 **********************************************************************************************************************/
static uint32_t update_dataflash_data_from_image (flash_ctrl_t * const p_flash_ctrl)
{
    uint32_t required_dataflash_block_num;

    // flash_err_t flash_error_code = FLASH_SUCCESS;

    required_dataflash_block_num = sizeof(PKCS_CONTROL_BLOCK) / BSP_FEATURE_FLASH_HP_DF_BLOCK_SIZE;
    if (sizeof(PKCS_CONTROL_BLOCK) % BSP_FEATURE_FLASH_HP_DF_BLOCK_SIZE)
    {
        required_dataflash_block_num++;
    }

    configPRINTF(("erase dataflash(main)...\r\n"));
    __disable_irq();
    fsp_err = R_FLASH_HP_Erase(p_flash_ctrl, (uint32_t) &pkcs_control_block_data, required_dataflash_block_num);
    __enable_irq();
    if (FSP_SUCCESS == fsp_err)
    {
        configPRINTF(("OK\r\n"));
    }
    else
    {
        configPRINTF(("NG\r\n"));
        configPRINTF(("R_FLASH_Erase() returns error code = %d.\r\n", fsp_err));

        return 1;
    }

    configPRINTF(("write dataflash(main)...\r\n"));
    __disable_irq();
    fsp_err = R_FLASH_HP_Write(p_flash_ctrl,
                               (uint32_t) &pkcs_control_block_data_image,
                               (uint32_t) &pkcs_control_block_data,
                               BSP_FEATURE_FLASH_HP_DF_BLOCK_SIZE * required_dataflash_block_num);
    __enable_irq();
    if (FSP_SUCCESS == fsp_err)
    {
        configPRINTF(("OK\r\n"));
    }
    else
    {
        configPRINTF(("NG\r\n"));
        configPRINTF(("R_FLASH_Write() returns error code = %d.\r\n", fsp_err));

        return 1;
    }

    return 0;
}

/*******************************************************************************************************************//**
 * This function is used to update the mirror with data from the main block.
 * @retval
 *       1 succeeded
 *       0 failed
 **********************************************************************************************************************/
static uint32_t update_dataflash_data_mirror_from_image (flash_ctrl_t * const p_flash_ctrl)
{
    uint32_t required_dataflash_block_num;

    // flash_err_t flash_error_code = FLASH_SUCCESS;

    required_dataflash_block_num = sizeof(PKCS_CONTROL_BLOCK) / BSP_FEATURE_FLASH_HP_DF_BLOCK_SIZE;
    if (sizeof(PKCS_CONTROL_BLOCK) % BSP_FEATURE_FLASH_HP_DF_BLOCK_SIZE)
    {
        required_dataflash_block_num++;
    }

    configPRINTF(("erase dataflash(mirror)...\r\n"));
    __disable_irq();
    fsp_err = R_FLASH_HP_Erase(p_flash_ctrl, (uint32_t) &pkcs_control_block_data_mirror, required_dataflash_block_num);
    __enable_irq();
    if (FSP_SUCCESS == fsp_err)
    {
        configPRINTF(("OK\r\n"));
    }
    else
    {
        configPRINTF(("NG\r\n"));
        configPRINTF(("R_FLASH_Erase() returns error code = %d.\r\n", fsp_err));

        return 1;
    }

    configPRINTF(("write dataflash(mirror)...\r\n"));
    __disable_irq();
    fsp_err = R_FLASH_HP_Write(p_flash_ctrl,
                               (uint32_t) &pkcs_control_block_data_image,
                               (uint32_t) &pkcs_control_block_data_mirror,
                               BSP_FEATURE_FLASH_HP_DF_BLOCK_SIZE * required_dataflash_block_num);
    __enable_irq();
    if (FSP_SUCCESS == fsp_err)
    {
        configPRINTF(("OK\r\n"));
    }
    else
    {
        configPRINTF(("NG\r\n"));
        configPRINTF(("R_FLASH_Write() returns error code = %d.\r\n", fsp_err));

        return 1;
    }

    if (!memcmp(&pkcs_control_block_data, &pkcs_control_block_data_mirror, sizeof(PKCS_CONTROL_BLOCK)))
    {
        configPRINTF(("data flash setting OK.\r\n"));
    }
    else
    {
        configPRINTF(("data flash setting NG.\r\n"));

        return 1;
    }

    return 0;
}

/*******************************************************************************************************************//**
 * This function is used to determine the status of the data flash.
 * If the hash check for either the main or backup fails and cannot be restored from the other, return an error.
 * @retval
 *       1 flash is invalid
 *       0 flash is valid
 **********************************************************************************************************************/
static uint32_t check_dataflash_area (uint32_t retry_counter, flash_ctrl_t * const p_flash_ctrl)
{
    uint8_t                hash_sha256[PKCS_SHA256_LENGTH];
    mbedtls_sha256_context ctx;
    uint32_t               retval = 1;
    mbedtls_sha256_init(&ctx);

    if (retry_counter)
    {
        configPRINTF(("recover retry count = %d.\r\n", retry_counter));
        if (retry_counter == MAX_CHECK_DATAFLASH_AREA_RETRY_COUNT)
        {
            configPRINTF(("retry over the limit.\r\n"));

            return 1;
        }
    }

    configPRINTF(("data flash(main) hash check...\r\n"));
    mbedtls_sha256_starts_ret(&ctx, 0); /* 0 means SHA256 context */
    mbedtls_sha256_update_ret(&ctx,
                              (unsigned char *) &pkcs_control_block_data.data,
                              sizeof(pkcs_control_block_data.data));
    mbedtls_sha256_finish_ret(&ctx, hash_sha256);
    if (!memcmp(pkcs_control_block_data.hash_sha256, hash_sha256, sizeof(hash_sha256)))
    {
        configPRINTF(("OK\r\n"));
        configPRINTF(("data flash(mirror) hash check...\r\n"));
        mbedtls_sha256_starts_ret(&ctx, 0); /* 0 means SHA256 context */
        mbedtls_sha256_update_ret(&ctx, (unsigned char *) &pkcs_control_block_data_mirror.data,
                                  sizeof(pkcs_control_block_data_mirror.data));
        mbedtls_sha256_finish_ret(&ctx, hash_sha256);
        if (!memcmp(pkcs_control_block_data_mirror.hash_sha256, hash_sha256, sizeof(hash_sha256)))
        {
            configPRINTF(("OK\r\n"));
            retval = 0;
        }
        else
        {
            configPRINTF(("NG\r\n"));
            configPRINTF(("recover mirror from main.\r\n"));
            memcpy(&pkcs_control_block_data_image, (void *) &pkcs_control_block_data, sizeof(pkcs_control_block_data));
            update_dataflash_data_mirror_from_image(p_flash_ctrl);
            retval = check_dataflash_area(retry_counter + 1, p_flash_ctrl);
        }
    }
    else
    {
        configPRINTF(("NG\r\n"));
        configPRINTF(("data flash(mirror) hash check...\r\n"));
        mbedtls_sha256_starts_ret(&ctx, 0); /* 0 means SHA256 context */
        mbedtls_sha256_update_ret(&ctx, (unsigned char *) &pkcs_control_block_data_mirror.data,
                                  sizeof(pkcs_control_block_data_mirror.data));
        mbedtls_sha256_finish_ret(&ctx, hash_sha256);
        if (!memcmp(pkcs_control_block_data_mirror.hash_sha256, hash_sha256, sizeof(hash_sha256)))
        {
            configPRINTF(("OK\r\n"));
            configPRINTF(("recover main from mirror.\r\n"));
            memcpy(&pkcs_control_block_data_image, (void *) &pkcs_control_block_data_mirror,
                   sizeof(pkcs_control_block_data_mirror));
            update_dataflash_data_from_image(p_flash_ctrl);
            retval = check_dataflash_area(retry_counter + 1, p_flash_ctrl);
        }
        else
        {
            /* Data flash is completely broken.
             * Please erase all code flash.
             * And, write initial firmware using debugger/rom writer.
             */
            configPRINTF(("NG\r\n"));

            return 1;
        }
    }

    return retval;
}

/*-----------------------------------------------------------*/
