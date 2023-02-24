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

/*******************************************************************************************************************//**
 * @ingroup RENESAS_INTERFACES
 * @defgroup USB_HMSC_API USB HMSC Interface
 * @brief Interface for USB HMSC functions.
 *
 * @section USB_HMSC_API_Summary Summary
 * The USB HMSC interface provides USB HMSC functionality.
 *
 * The USB HMSC interface can be implemented by:
 * - @ref USB_HMSC
 *
 * @{
 **********************************************************************************************************************/

#ifndef R_USB_HMSC_API_H
#define R_USB_HMSC_API_H

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/*****************************************************************************
 * Macro definitions
 ******************************************************************************/
#define USB_HMSC_SECTOR_SIZE    (512)

/*****************************************************************************
 * Enum definitions
 ******************************************************************************/

/** ATAPI commands */
typedef enum e_usb_atapi
{
    /*--- SFF-8070i command define ---*/
    USB_ATAPI_TEST_UNIT_READY      = 0x00U, ///< Test Unit Ready
    USB_ATAPI_REQUEST_SENSE        = 0x03U, ///< Request Sense
    USB_ATAPI_FORMAT_UNIT          = 0x04U, ///< Format Unit
    USB_ATAPI_INQUIRY              = 0x12U, ///< Inquiry
    USB_ATAPI_MODE_SELECT6         = 0x15U, ///< Mode Select6
    USB_ATAPI_MODE_SENSE6          = 0x1AU, ///< Mode Sense6
    USB_ATAPI_START_STOP_UNIT      = 0x1BU, ///< Start Stop Unit
    USB_ATAPI_PREVENT_ALLOW        = 0x1EU, ///< Prevent Allow
    USB_ATAPI_READ_FORMAT_CAPACITY = 0x23U, ///< Read Format Capacity
    USB_ATAPI_READ_CAPACITY        = 0x25U, ///< Read Capacity
    USB_ATAPI_READ10               = 0x28U, ///< Read10
    USB_ATAPI_WRITE10              = 0x2AU, ///< Write10
    USB_ATAPI_SEEK                 = 0x2BU, ///< Seek
    USB_ATAPI_WRITE_AND_VERIFY     = 0x2EU, ///< Write and Verify
    USB_ATAPI_VERIFY10             = 0x2FU, ///< Verify10
    USB_ATAPI_MODE_SELECT10        = 0x55U, ///< Mode Select10
    USB_ATAPI_MODE_SENSE10         = 0x5AU, ///< Mode Sense10
} usb_atapi_t;

/** Command Status Wrapper (CSW) */
typedef enum e_usb_csw_result
{
    USB_CSW_RESULT_SUCCESS = 0x00U,    ///< CSW was successful.
    USB_CSW_RESULT_FAIL    = 0x01U,    ///< CSW failed.
    USB_CSW_RESULT_PHASE   = 0x02U,    ///< CSW has phase error.
} usb_csw_result_t;

/*****************************************************************************
 * Typedef definitions
 ******************************************************************************/

/** USB HMSC functions implemented at the HAL layer will follow this API. */
typedef struct st_usb_hmsc_api
{
    /** Processing for MassStorage(ATAPI) command.
     * @par Implemented as
     * - @ref R_USB_HMSC_StorageCommand()
     *
     * @param[in]  p_api_ctrl   Pointer to control structure.
     * @param[in]  *buf         Pointer to the buffer area to store the transfer data.
     * @param[in]  command      ATAPI command.
     * @param[in]  destination  Represents a device address.
     */
    fsp_err_t (* storageCommand)(usb_ctrl_t * const p_api_ctrl, uint8_t * buf, uint8_t command, uint8_t destination);

    /** Get number of Storage drive.
     * @par Implemented as
     * - @ref R_USB_HMSC_DriveNumberGet()
     *
     * @param[in]  p_api_ctrl   Pointer to control structure.
     * @param[out] p_drive      Store address for Drive No.
     * @param[in]  destination  Represents a device address.
     */
    fsp_err_t (* driveNumberGet)(usb_ctrl_t * const p_api_ctrl, uint8_t * p_drive, uint8_t destination);

    /** Read sector information.
     * @par Implemented as
     * - @ref R_USB_HMSC_StorageReadSector()
     *
     * @param[in]  drive_number      Drive number.
     * @param[out] *buff             Pointer to the buffer area to store the transfer data.
     * @param[in]  sector_number     The sector number to start with.
     * @param[in]  sector_count      Transmit with the sector size of the number of times.
     */
    fsp_err_t (* storageReadSector)(uint16_t drive_number, uint8_t * const buff, uint32_t sector_number,
                                    uint16_t sector_count);

    /** Write sector information.
     * @par Implemented as
     * - @ref R_USB_HMSC_StorageWriteSector()
     *
     * @param[in] drive_number      Drive number.
     * @param[in] *buff             Pointer to the buffer area to store the transfer data.
     * @param[in] sector_number     The sector number to start with.
     * @param[in] sector_count      Transmit with the sector size of the number of times.
     */
    fsp_err_t (* storageWriteSector)(uint16_t drive_number, uint8_t const * const buff, uint32_t sector_number,
                                     uint16_t sector_count);

    /** Get Semaphore.
     * @par Implemented as
     * - @ref R_USB_HMSC_SemaphoreGet()
     *
     */
    fsp_err_t (* semaphoreGet)(void);

    /** Release Semaphore.
     * @par Implemented as
     * - @ref R_USB_HMSC_SemaphoreRelease()
     *
     */
    fsp_err_t (* semaphoreRelease)(void);
} usb_hmsc_api_t;

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 /* R_USB_HMSC_API_H */

/*******************************************************************************************************************//**
 * @} (end addtogroup USB_HMSC_API)
 **********************************************************************************************************************/
