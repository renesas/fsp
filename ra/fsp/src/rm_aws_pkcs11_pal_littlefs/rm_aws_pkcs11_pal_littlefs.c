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
#include "portmacro.h"
#include "core_pkcs11_pal.h"
#include "FreeRTOS.h"
#include "task.h"
#include "mbedtls/sha256.h"

/* C runtime includes. */
#include <stdio.h>
#include <string.h>

#include "lfs.h"

extern lfs_t RM_STDIO_LITTLEFS_CFG_LFS;

enum eObjectHandles
{
    eInvalidHandle       = 0,          /* According to PKCS #11 spec, 0 is never a valid object handle. */
    eAwsDevicePrivateKey = 1,
    eAwsDevicePublicKey,
    eAwsDeviceCertificate,
    eAwsCodeSigningKey,
#if pkcs11configMAX_NUM_OBJECTS >= 6
    eAwsRootCertificate,
#endif
#if pkcs11configMAX_NUM_OBJECTS >= 7
    eAwsJitpCertificate,
#endif
};

uint8_t g_object_handle_dictionary[pkcs11configMAX_NUM_OBJECTS][pkcs11configMAX_LABEL_LENGTH + 1] =
{
    "",
    pkcs11configLABEL_DEVICE_PRIVATE_KEY_FOR_TLS,
    pkcs11configLABEL_DEVICE_PUBLIC_KEY_FOR_TLS,
    pkcs11configLABEL_DEVICE_CERTIFICATE_FOR_TLS,
    pkcs11configLABEL_CODE_VERIFICATION_KEY,
#if pkcs11configMAX_NUM_OBJECTS >= 6
    pkcs11configLABEL_ROOT_CERTIFICATE,
#endif
#if pkcs11configMAX_NUM_OBJECTS >= 7
    pkcs11configLABEL_JITP_CERTIFICATE,
#endif
};

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
CK_OBJECT_HANDLE PKCS11_PAL_SaveObject (CK_ATTRIBUTE_PTR pxLabel, CK_BYTE_PTR pucData, CK_ULONG ulDataSize)
{
    CK_OBJECT_HANDLE xHandle = eInvalidHandle;

    /* search specified label value from g_object_handle_dictionary */
    for (uint32_t i = 1; i < pkcs11configMAX_NUM_OBJECTS; i++)
    {
        if (!strcmp((char *) &g_object_handle_dictionary[i], pxLabel->pValue))
        {
            xHandle = i;
        }
    }

    if (eInvalidHandle == xHandle)
    {
        return eInvalidHandle;
    }

    lfs_file_t file;

    volatile int lfs_err = lfs_remove(&RM_STDIO_LITTLEFS_CFG_LFS, pxLabel->pValue);

    if ((LFS_ERR_NOENT != lfs_err) && (LFS_ERR_OK != lfs_err))
    {
        return eInvalidHandle;
    }

    lfs_err = lfs_file_open(&RM_STDIO_LITTLEFS_CFG_LFS, &file, pxLabel->pValue, LFS_O_WRONLY | LFS_O_CREAT);

    if (LFS_ERR_OK != lfs_err)
    {
        return eInvalidHandle;
    }

    lfs_err = lfs_file_write(&RM_STDIO_LITTLEFS_CFG_LFS, &file, pucData, ulDataSize);

    if (lfs_err < 0)
    {
        xHandle = eInvalidHandle;
    }

    lfs_file_close(&RM_STDIO_LITTLEFS_CFG_LFS, &file);

    return xHandle;
}

/**
 * @brief Translates a PKCS #11 label into an object handle.
 *
 * Port-specific object handle retrieval.
 *
 *
 * @param[in] pxLabel        Pointer to the label of the object
 *                           who's handle should be found.
 * @param[in] usLength       The length of the label, in bytes.
 *
 * @return The object handle if operation was successful.
 * Returns eInvalidHandle if unsuccessful.
 */
CK_OBJECT_HANDLE PKCS11_PAL_FindObject (CK_BYTE_PTR pxLabel, CK_ULONG usLength)
{
    /* Avoid compiler warnings about unused variables. */
    FSP_PARAMETER_NOT_USED(usLength);

    CK_OBJECT_HANDLE xHandle = eInvalidHandle;
    uint32_t         i;

    for (i = 1; i < pkcs11configMAX_NUM_OBJECTS; i++)
    {
        if (!strcmp((char *) &g_object_handle_dictionary[i], (char *) pxLabel))
        {
            lfs_file_t file;

            int lfs_err = lfs_file_open(&RM_STDIO_LITTLEFS_CFG_LFS, &file, (char *) pxLabel, LFS_O_RDONLY);

            if (LFS_ERR_OK == lfs_err)
            {
                lfs_file_close(&RM_STDIO_LITTLEFS_CFG_LFS, &file);

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
 * @param[out] pIsPrivate   Boolean indicating if value is private (CK_TRUE)
 *                          or exportable (CK_FALSE)
 *
 * @return CKR_OK if operation was successful.  CKR_KEY_HANDLE_INVALID if
 * no such object handle was found, CKR_DEVICE_MEMORY if memory for
 * buffer could not be allocated, CKR_FUNCTION_FAILED for device driver
 * error.
 */

CK_RV PKCS11_PAL_GetObjectValue (CK_OBJECT_HANDLE xHandle,
                                 CK_BYTE_PTR    * ppucData,
                                 CK_ULONG_PTR     pulDataSize,
                                 CK_BBOOL       * pIsPrivate)
{
    CK_RV            xReturn        = CKR_FUNCTION_FAILED;
    CK_OBJECT_HANDLE xHandleStorage = xHandle;

    if (xHandle != eInvalidHandle)
    {
        lfs_file_t file;

        int lfs_ret =
            lfs_file_open(&RM_STDIO_LITTLEFS_CFG_LFS,
                          &file,
                          (char *) g_object_handle_dictionary[xHandleStorage],
                          LFS_O_RDONLY);

        if (LFS_ERR_OK != lfs_ret)
        {
            return eInvalidHandle;
        }

        lfs_ret = lfs_file_size(&RM_STDIO_LITTLEFS_CFG_LFS, &file);

        *ppucData = pvPortMalloc((size_t) lfs_ret);

        if ((lfs_ret >= 0) && (NULL != *ppucData))
        {
            lfs_ret = lfs_file_read(&RM_STDIO_LITTLEFS_CFG_LFS, &file, *ppucData, (lfs_size_t) lfs_ret);

            if (lfs_ret >= 0)
            {
                *pulDataSize = (uint32_t) lfs_ret;

                xReturn = CKR_OK;
            }

            if (xHandle == eAwsDevicePrivateKey)
            {
                *pIsPrivate = CK_TRUE;
            }
            else
            {
                *pIsPrivate = CK_FALSE;
            }
        }

        lfs_file_close(&RM_STDIO_LITTLEFS_CFG_LFS, &file);
    }

    return xReturn;
}

/**
 * @brief Cleanup after PKCS11_GetObjectValue().
 *
 * @param[in] pucData       The buffer to free.
 *                          (*ppucData from PKCS11_PAL_GetObjectValue())
 * @param[in] ulDataSize    The length of the buffer to free.
 *                          (*pulDataSize from PKCS11_PAL_GetObjectValue())
 */
void PKCS11_PAL_GetObjectValueCleanup (CK_BYTE_PTR pucData, CK_ULONG ulDataSize)
{
    /* Avoid compiler warnings about unused variables. */
    FSP_PARAMETER_NOT_USED(ulDataSize);

    vPortFree(pucData);
}

/*-----------------------------------------------------------*/
