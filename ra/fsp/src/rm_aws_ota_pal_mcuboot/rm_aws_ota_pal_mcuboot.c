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

/* C Runtime includes. */
#include <stdio.h>
#include <stdlib.h>

/* FreeRTOS include. */
#include "FreeRTOS.h"

/* OTA library includes. */
#include "ota.h"
#include "ota_private.h"
#include "ota_os_interface.h"

/* OTA PAL Port include. */
#include "ota_pal.h"

/* OTA PAL test config file include. */
#include "ota_config.h"

#include "r_flash_api.h"

#include "rm_aws_ota_pal_mcuboot_cfg.h"
#include "ota_pal.h"
#if defined(__ARMCC_VERSION)
 #pragma GCC diagnostic push
 #pragma GCC diagnostic ignored "-Wmacro-redefined"
#endif

#include "core_pkcs11.h"

#if defined(__ARMCC_VERSION)
 #pragma GCC diagnostic pop
#endif
#include "core_pki_utils.h"
#include "mbedtls/sha256.h"

#include "bootutil/bootutil_public.h"
#include "sysflash/sysflash.h"

#define RM_AWS_OTA_PAL_MCUBOOT_OPEN             (0x414F5441U)

#ifndef RM_AWS_OTA_PAL_MCUBOOT_CFG_CALLBACK
 #define RM_AWS_OTA_PAL_MCUBOOT_CFG_CALLBACK    rm_aws_ota_pal_mcuboot_filepath_to_slot_id
uint8_t rm_aws_ota_pal_mcuboot_filepath_to_slot_id(uint8_t * file_path, uint16_t max_file_path);

uint8_t rm_aws_ota_pal_mcuboot_filepath_to_slot_id (uint8_t * file_path, uint16_t max_file_path)
{
    FSP_PARAMETER_NOT_USED(file_path);
    FSP_PARAMETER_NOT_USED(max_file_path);

    return FLASH_AREA_IMAGE_1;
}

#endif

static OtaPalStatus_t rm_aws_ota_pal_mcuboot_validate_image(uint8_t * pMappedAddress,
                                                            size_t    mappedLength,
                                                            char    * pCertificatePath,
                                                            uint8_t * pSignature,
                                                            size_t    signatureLength);

extern flash_instance_t RM_AWS_OTA_PAL_MCUBOOT_CFG_FLASH;

#define RM_AWS_OTA_PAL_INT16_NEGATIVE_MASK    (1 << 15)
const struct flash_area * gp_flash_area = NULL;

/* Specify the OTA signature algorithm we support on this platform. */
const char OTA_JsonFileSignatureKey[OTA_FILE_SIG_KEY_STR_MAX_LENGTH] =
    RM_AWS_OTA_PAL_MCUBOOT_CFG_JSON_FILE_SIGNATURE_KEY;

/*******************************************************************************************************************//**
 * Erase a region of code flash to download the new firmware to.
 * @param      pFileContext                  Pointer to the AWS OTA File context
 * @retval     OtaPalSuccess                 File created successfully.
 * @retval     OtaPalRxFileCreateFailed      Parameter checking completed without error.
 **********************************************************************************************************************/
OtaPalStatus_t otaPal_CreateFileForRx (OtaFileContext_t * const pFileContext)
{
    /* Get the slot id to download the image to. */
    uint8_t slot_id = RM_AWS_OTA_PAL_MCUBOOT_CFG_CALLBACK(pFileContext->pFilePath, pFileContext->filePathMaxSize);

    /* Open the flash area and get the address and size of the download area. */
    int flash_return = flash_area_open(slot_id, &gp_flash_area);

    if (0 != flash_return)
    {
        return OTA_PAL_COMBINE_ERR(OtaPalRxFileCreateFailed, flash_return);
    }

    /* Erase the download area. */
    flash_return = flash_area_erase(gp_flash_area, 0U, gp_flash_area->fa_size);

    if (0 != flash_return)
    {
        return OTA_PAL_COMBINE_ERR(OtaPalRxFileCreateFailed, flash_return);
    }

    pFileContext->pFile = (otaconfigOTA_FILE_TYPE *) RM_AWS_OTA_PAL_MCUBOOT_OPEN;

    return OtaPalSuccess;
}

/*******************************************************************************************************************//**
 * Abort the current download and erase the download area.
 * @param      pFileContext                  Pointer to the AWS OTA File context
 * @retval     OtaPalSuccess                 Download aborted and flash erased
 * @retval     OtaPalFileAbort               Failed to erase download area.
 **********************************************************************************************************************/
OtaPalStatus_t otaPal_Abort (OtaFileContext_t * const pFileContext)
{
    pFileContext->pFile = (otaconfigOTA_FILE_TYPE *) 0U;
    int flash_return = 0;

    if (NULL != gp_flash_area)
    {
        /* Erase the download area. */
        flash_return  = flash_area_erase(gp_flash_area, 0U, gp_flash_area->fa_size);
        gp_flash_area = NULL;
    }

    if (FSP_SUCCESS != flash_return)
    {
        return OTA_PAL_COMBINE_ERR(OtaPalFileAbort, flash_return);;
    }

    return OtaPalSuccess;
}

/*******************************************************************************************************************//**
 * Close the file and validate the signature
 * @param      pFileContext                  Pointer to the AWS OTA File context
 * @retval     OtaPalSuccess                 File closed and signature validated successfully.
 * @retval     OtaPalFileClose               Failed to flush pending data.
 * @retval     OtaPalBadSignerCert           Signature could not be converted to PKCS11 format
 * @retval     OtaPalSignatureCheckFailed    Signature failed to validate
 **********************************************************************************************************************/
OtaPalStatus_t otaPal_CloseFile (OtaFileContext_t * const pFileContext)
{
    int flash_return = flash_on_chip_flush(gp_flash_area);

    if (0 != flash_return)
    {
        return OTA_PAL_COMBINE_ERR(OtaPalFileClose, 0U);
    }

    OtaPalStatus_t result = rm_aws_ota_pal_mcuboot_validate_image((void *) gp_flash_area->fa_off,
                                                                  pFileContext->fileSize,
                                                                  (char *) pFileContext->pCertFilepath,
                                                                  pFileContext->pSignature->data,
                                                                  pFileContext->pSignature->size);

    pFileContext->pFile = (otaconfigOTA_FILE_TYPE *) 0U;

    return OTA_PAL_COMBINE_ERR(result, 0U);
}

/*******************************************************************************************************************//**
 * Write a block of the downloaded image
 * @param      pFileContext                  Pointer to the AWS OTA File context
 * @param      ulOffset                  Offset into the downloaded image
 * @param      pData                  Pointer to the downloaded data
 * @param      ulBlockSize                  Size of the data to write
 * @retval     FSP_SUCCESS        Parameter checking completed without error.
 * @retval     FSP_ERR_ASSERTION  Null pointer
 * @retval     FSP_ERR_NOT_OPEN   The flash module is not open.
 * @retval     FSP_ERR_IN_USE     The Flash peripheral is busy with a prior on-going transaction.
 **********************************************************************************************************************/
int16_t otaPal_WriteBlock (OtaFileContext_t * const pFileContext,
                           uint32_t                 ulOffset,
                           uint8_t * const          pData,
                           uint32_t                 ulBlockSize)
{
    FSP_PARAMETER_NOT_USED(pFileContext);

    int16_t err = (int16_t) ulBlockSize;

    int flash_return = flash_area_write(gp_flash_area, ulOffset, pData, ulBlockSize);

    if (0 != flash_return)
    {
        err = (int16_t) (RM_AWS_OTA_PAL_INT16_NEGATIVE_MASK | flash_return);
    }

    return err;
}

/*******************************************************************************************************************//**
 * Activate the new image by restting. MCUBoot will verify and swap to the new image.
 * @param      pFileContext                  Pointer to the AWS OTA File context
 **********************************************************************************************************************/
OtaPalStatus_t otaPal_ActivateNewImage (OtaFileContext_t * const pFileContext)
{
    FSP_PARAMETER_NOT_USED(pFileContext);

    __NVIC_SystemReset();
}

/*******************************************************************************************************************//**
 * Set the platform image state in MCUBoot.
 * @param      pFileContext         Pointer to the AWS OTA File context
 * @param      eState               State to set current image to
 * @retval     OtaPalSuccess        Image state was successuflly changed.
 * @retval     OtaPalCommitFailed   Failed to commit the new image
 * @retval     OtaPalRejectFailed   Failed to reject the new image.
 * @retval     OtaPalAbortFailed    Failed to abort the download.
 * @retval     OtaPalBadImageState  Unknown image state
 **********************************************************************************************************************/
OtaPalStatus_t otaPal_SetPlatformImageState (OtaFileContext_t * const pFileContext, OtaImageState_t eState)
{
    OtaPalStatus_t result = OtaPalSuccess;

    if (otaPal_GetPlatformImageState(pFileContext) == OtaPalImageStatePendingCommit)
    {
        /* Device in test mode */
        switch (eState)
        {
            case OtaImageStateAccepted:
            {
                FSP_ERROR_RETURN(pFileContext->pFile == (otaconfigOTA_FILE_TYPE *) 0U,
                                 OTA_PAL_COMBINE_ERR(OtaPalCommitFailed, 0U));

                if (0 != boot_set_confirmed())
                {
                    /* Override result code by a state specific one */
                    result = OtaPalCommitFailed;
                }

                break;
            }

            case OtaImageStateRejected:
            {
                /* Override result code by a state specific one */
                result = OtaPalRejectFailed;
                break;
            }

            case OtaImageStateAborted:
            {
                /* Override result code by a state specific one */
                result = OtaPalAbortFailed;

                break;
            }

            case OtaImageStateTesting:
            {
                result = OtaPalSuccess;
                break;
            }

            default:
            {
                result = OtaPalBadImageState;
                break;
            }
        }
    }
    else
    {
        /* Normal mode */
        switch (eState)
        {
            case OtaImageStateAccepted:
            {
                FSP_ERROR_RETURN(pFileContext->pFile == (otaconfigOTA_FILE_TYPE *) 0U,
                                 OTA_PAL_COMBINE_ERR(OtaPalCommitFailed, 0U));

                if (0 != boot_set_pending(1))
                {
                    /* Override result code by a state specific one */
                    result = OtaPalCommitFailed;
                }

                break;
            }

            case OtaImageStateRejected:
            {
                result = OtaPalRejectFailed;
                break;
            }

            case OtaImageStateAborted:
            {
                result = OtaPalAbortFailed;
                break;
            }

            case OtaImageStateTesting:
            {
                FSP_ERROR_RETURN(pFileContext->pFile == (otaconfigOTA_FILE_TYPE *) 0U,
                                 OTA_PAL_COMBINE_ERR(OtaPalCommitFailed, 0U));

                /* Request the bootloader to switch the image temporarily */
                if (0 != boot_set_pending(0))
                {
                    /* Override result code by a state specific one */
                    result = OtaPalCommitFailed;
                }

                break;
            }

            default:
            {
                result = OtaPalBadImageState;
                break;
            }
        }
    }

    return OTA_PAL_COMBINE_ERR(result, 0U);
}

/*******************************************************************************************************************//**
 * Get the platform image state from MCUBoot.
 * @param      pFileContext                    Pointer to the AWS OTA File context
 * @retval     OtaPalImageStateInvalid         Invalid image state
 * @retval     OtaPalImageStateUnknown         Image state unknown
 * @retval     OtaPalImageStateValid           Running image is confirmed
 * @retval     OtaPalImageStatePendingCommit   Running image is pending confirmation
 **********************************************************************************************************************/
OtaPalImageState_t otaPal_GetPlatformImageState (OtaFileContext_t * const pFileContext)
{
    FSP_PARAMETER_NOT_USED(pFileContext);
    OtaPalImageState_t image_state;

    int swap_type = boot_swap_type();

    FSP_ERROR_RETURN(0 <= swap_type, OtaPalImageStateInvalid);

    switch (swap_type)
    {
        case BOOT_SWAP_TYPE_NONE:
        {
            image_state = OtaPalImageStateUnknown;
            break;
        }

        case BOOT_SWAP_TYPE_PERM:
        {
            image_state = OtaPalImageStateValid;
            break;
        }

        case BOOT_SWAP_TYPE_TEST:
        {
            image_state = OtaPalImageStatePendingCommit;
            break;
        }

        default:
        {
            image_state = OtaPalImageStateInvalid;
            break;
        }
    }

    return image_state;
}

/*******************************************************************************************************************//**
 * Reset the device to allow MCUBoot to switch to the new firmware.
 * @param      pFileContext                  Pointer to the AWS OTA File context
 **********************************************************************************************************************/
OtaPalStatus_t otaPal_ResetDevice (OtaFileContext_t * const pFileContext)
{
    FSP_PARAMETER_NOT_USED(pFileContext);

    __NVIC_SystemReset();
}

/*******************************************************************************************************************//**
 * Validates the signature of the downloaded image.
 * @param      pMappedAddress                Pointer to the start of the downloaded image
 * @param      mappedLength                  Length of the downloaded image
 * @param      pCertificatePath              Certificate path to use to validate image
 * @param      pSignature                    Expected signature of the downloaded image
 * @param      signatureLength               Signature length
 * @retval     OtaPalSuccess                 Signature validated successfully.
 * @retval     OtaPalBadSignerCert           Signature could not be converted to PKCS11 format
 * @retval     OtaPalSignatureCheckFailed    Signature failed to validate
 **********************************************************************************************************************/
static OtaPalStatus_t rm_aws_ota_pal_mcuboot_validate_image (uint8_t * pMappedAddress,
                                                             size_t    mappedLength,
                                                             char    * pCertificatePath,
                                                             uint8_t * pSignature,
                                                             size_t    signatureLength)
{
    FSP_PARAMETER_NOT_USED(signatureLength);
    OtaPalStatus_t    status    = OtaPalSuccess;
    CK_SESSION_HANDLE p_session = CKR_SESSION_HANDLE_INVALID;
    CK_OBJECT_HANDLE  certHandle;

    uint8_t pkcs11Signature[pkcs11ECDSA_P256_SIGNATURE_LENGTH] = {0};

    /* Convert the signature into one for use with PKCS11. */
    if (PKI_mbedTLSSignatureToPkcs11Signature(pkcs11Signature, pSignature) != 0)
    {
        status = OtaPalBadSignerCert;
    }

    if (status == OtaPalSuccess)
    {
        /* Find the certificate */
        CK_RV                xResult;
        CK_FUNCTION_LIST_PTR xFunctionList;
        CK_SLOT_ID           xSlotId;
        CK_BBOOL             xFindInit = CK_FALSE;

        /* The buffer used to hold the calculated SHA25 digest of the image. */
        CK_BYTE  digestResult[pkcs11SHA256_DIGEST_LENGTH] = {0};
        CK_ULONG digestLength = pkcs11SHA256_DIGEST_LENGTH;

        xResult = C_GetFunctionList(&xFunctionList);

        /* Initialize the PKCS11 session. */
        if (CKR_OK == xResult)
        {
            xResult = xFunctionList->C_Initialize(NULL);
        }

        if ((CKR_OK == xResult) || (CKR_CRYPTOKI_ALREADY_INITIALIZED == xResult))
        {
            CK_ULONG xCount = 1;
            xResult = xFunctionList->C_GetSlotList(CK_TRUE, &xSlotId, &xCount);
        }

        /* Open the PKCS11 session. */
        if (CKR_OK == xResult)
        {
            xResult = xFunctionList->C_OpenSession(xSlotId, CKF_SERIAL_SESSION, NULL, NULL, &p_session);
        }

        /* Get the certificate handle. */
        if (CKR_OK == xResult)
        {
            CK_ATTRIBUTE xTemplate;
            xTemplate.type       = CKA_LABEL;
            xTemplate.ulValueLen = strlen(pCertificatePath) + 1;
            xTemplate.pValue     = pCertificatePath;
            xResult              = xFunctionList->C_FindObjectsInit(p_session, &xTemplate, 1);
        }

        if (CKR_OK == xResult)
        {
            CK_ULONG ulCount = 0;
            xFindInit = CK_TRUE;
            xResult   = xFunctionList->C_FindObjects(p_session, &certHandle, 1, &ulCount);
        }

        if ((CK_TRUE == xFindInit) && (xResult == 0))
        {
            xResult = xFunctionList->C_FindObjectsFinal(p_session);
        }

        /* Calculate the hash of the downloaded image. */
        if (xResult == CKR_OK)
        {
            CK_MECHANISM xDigestMechanism = {CKM_SHA256, NULL, 0};
            xResult = xFunctionList->C_DigestInit(p_session, &xDigestMechanism);
        }

        if (xResult == CKR_OK)
        {
            xResult = xFunctionList->C_DigestUpdate(p_session, pMappedAddress, mappedLength);
        }

        if (xResult == CKR_OK)
        {
            xResult = xFunctionList->C_DigestFinal(p_session, digestResult, &digestLength);
        }

        /* Verify the signature of the downloaded image. */
        if (xResult == CKR_OK)
        {
            /* The ECDSA mechanism will be used to verify the message digest. */
            CK_MECHANISM xVerifyMechanism = {CKM_ECDSA, NULL, 0};
            xResult = xFunctionList->C_VerifyInit(p_session, &xVerifyMechanism, certHandle);
        }

        if (xResult == CKR_OK)
        {
            xResult = xFunctionList->C_Verify(p_session,
                                              digestResult,
                                              digestLength,
                                              pkcs11Signature,
                                              pkcs11ECDSA_P256_SIGNATURE_LENGTH);
        }

        if (xResult != CKR_OK)
        {
            status = OtaPalSignatureCheckFailed;
        }

        /* Close the PKCS11 session. */
        if (p_session != CKR_SESSION_HANDLE_INVALID)
        {
            (void) xFunctionList->C_CloseSession(p_session);
        }
    }

    return status;
}
