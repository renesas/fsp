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

#ifndef RM_BLOCK_MEDIA_API_H
#define RM_BLOCK_MEDIA_API_H

/*******************************************************************************************************************//**
 * @defgroup RM_BLOCK_MEDIA_API Block Media Interface
 * @ingroup RENESAS_INTERFACES
 * @brief Interface for block media memory access
 *
 * @section RM_BLOCK_MEDIA_API_SUMMARY Summary
 * The block media interface supports reading, writing, and erasing media devices. All functions are non-blocking if
 * possible. The callback is used to determine when an operation completes.
 *
 * Implemented by:
 * - @ref RM_BLOCK_MEDIA_SDMMC
 * - @ref RM_BLOCK_MEDIA_SPI
 * - @ref RM_BLOCK_MEDIA_USB
 *
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

/* Register definitions, common services and error codes. */
#include "bsp_api.h"

/* Common macro for SSP header files. There is also a corresponding SSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Events that can trigger a callback function */
typedef enum e_rm_block_media_event
{
    RM_BLOCK_MEDIA_EVENT_MEDIA_REMOVED      = 1U << 0, ///< Media removed event
    RM_BLOCK_MEDIA_EVENT_MEDIA_INSERTED     = 1U << 1, ///< Media inserted event
    RM_BLOCK_MEDIA_EVENT_OPERATION_COMPLETE = 1U << 2, ///< Read, write, or erase completed
    RM_BLOCK_MEDIA_EVENT_ERROR              = 1U << 3, ///< Error on media operation
    RM_BLOCK_MEDIA_EVENT_POLL_STATUS        = 1U << 4, ///< Poll @ref rm_block_media_api_t::statusGet for write/erase completion
    RM_BLOCK_MEDIA_EVENT_MEDIA_SUSPEND      = 1U << 5, ///< Media suspended event
    RM_BLOCK_MEDIA_EVENT_MEDIA_RESUME       = 1U << 6, ///< Media resumed event
    RM_BLOCK_MEDIA_EVENT_WAIT               = 1U << 7, ///< Indication to user that they should wait for an interrupt on a pending operation
    RM_BLOCK_MEDIA_EVENT_WAIT_END           = 1U << 8, ///< Indication to user that interrupt has been received and waiting can end
} rm_block_media_event_t;

/** Block media device information supported by the instance */
typedef struct st_rm_block_media_info
{
    uint32_t sector_size_bytes;        ///< Sector size in bytes
    uint32_t num_sectors;              ///< Total number of sectors
    bool     reentrant;                ///< True if connected block media driver is reentrant
    bool     write_protected;          ///< True if connected block media device is write protected
} rm_block_media_info_t;

/** Callback function parameter data */
typedef struct st_rm_block_media_callback_args
{
    rm_block_media_event_t event;      ///< The event can be used to identify what caused the callback
    void const           * p_context;  ///< Placeholder for user data
} rm_block_media_callback_args_t;

/** User configuration structure, used in open function */
typedef struct st_rm_block_media_cfg
{
    void (* p_callback)(rm_block_media_callback_args_t * p_args); ///< Pointer to callback function
    void const * p_context;                                       ///< User defined context passed into callback function
    void const * p_extend;                                        ///< Extension parameter for hardware specific settings
} rm_block_media_cfg_t;

/** Current status */
typedef struct st_rm_block_media_status
{
    /** False if @ref rm_block_media_api_t::mediaInit has not been called since media was inserted, true otherwise. */
    bool initialized;
    bool busy;                         ///< True if media is busy with a previous write/erase operation
    bool media_inserted;               ///< Media insertion status, true if media is not removable
} rm_block_media_status_t;

/** Block media API control block.  Allocate an instance specific control block to pass into the block media API calls.
 * @par Implemented as
 * - @ref rm_block_media_sdmmc_instance_ctrl_t
 * - @ref rm_block_media_spi_instance_ctrl_t
 * - @ref rm_block_media_usb_instance_ctrl_t
 */
typedef void rm_block_media_ctrl_t;

/** Block media interface API. */
typedef struct st_rm_block_media_api
{
    /** Initialize block media device. @ref rm_block_media_api_t::mediaInit must be called to complete the
     * initialization procedure.
     * @par Implemented as
     * - @ref RM_BLOCK_MEDIA_SDMMC_Open
     * - @ref RM_BLOCK_MEDIA_SPI_Open
     * - @ref RM_BLOCK_MEDIA_USB_Open
     *
     * @param[in]   p_ctrl              Pointer to control block. Must be declared by user. Elements set here.
     * @param[in]   p_cfg               Pointer to configuration structure. All elements of this structure must be set by user.
     */
    fsp_err_t (* open)(rm_block_media_ctrl_t * const p_ctrl, rm_block_media_cfg_t const * const p_cfg);

    /** Initializes a media device.  If the device is removable, it must be plugged in prior to calling this API.
     * This function blocks until media initialization is complete.
     * @par Implemented as
     * - @ref RM_BLOCK_MEDIA_SDMMC_MediaInit
     * - @ref RM_BLOCK_MEDIA_SPI_MediaInit
     * - @ref RM_BLOCK_MEDIA_USB_MediaInit
     *
     * @param[in]   p_ctrl              Control block set in @ref rm_block_media_api_t::open call.
     */
    fsp_err_t (* mediaInit)(rm_block_media_ctrl_t * const p_ctrl);

    /** Reads blocks of data from the specified memory device address to the location specified by the caller.
     * @par Implemented as
     * - @ref RM_BLOCK_MEDIA_SDMMC_Read
     * - @ref RM_BLOCK_MEDIA_SPI_Read
     * - @ref RM_BLOCK_MEDIA_USB_Read
     *
     * @param[in]   p_ctrl              Control block set in @ref rm_block_media_api_t::open call.
     * @param[out]  p_dest_address      Destination to read the data into.
     * @param[in]   block_address       Block address to read the data from.
     * @param[in]   num_blocks          Number of blocks of data to read.
     */
    fsp_err_t (* read)(rm_block_media_ctrl_t * const p_ctrl, uint8_t * const p_dest_address,
                       uint32_t const block_address, uint32_t const num_blocks);

    /** Writes blocks of data to the specified device memory address.
     * @par Implemented as
     * - @ref RM_BLOCK_MEDIA_SDMMC_Write
     * - @ref RM_BLOCK_MEDIA_SPI_Write
     * - @ref RM_BLOCK_MEDIA_USB_Write
     *
     * @param[in]   p_ctrl             Control block set in @ref rm_block_media_api_t::open call.
     * @param[in]   p_src_address      Address to read the data to be written.
     * @param[in]   block_address      Block address to write the data to.
     * @param[in]   num_blocks         Number of blocks of data to write.
     */
    fsp_err_t (* write)(rm_block_media_ctrl_t * const p_ctrl, uint8_t const * const p_src_address,
                        uint32_t const block_address, uint32_t const num_blocks);

    /** Erases blocks of data from the memory device.
     * @par Implemented as
     * - @ref RM_BLOCK_MEDIA_SDMMC_Erase
     * - @ref RM_BLOCK_MEDIA_SPI_Erase
     * - @ref RM_BLOCK_MEDIA_USB_Erase
     *
     * @param[in]   p_ctrl             Control block set in @ref rm_block_media_api_t::open call.
     * @param[in]   block_address      Block address to start the erase process at.
     * @param[in]   num_blocks         Number of blocks of data to erase.
     */
    fsp_err_t (* erase)(rm_block_media_ctrl_t * const p_ctrl, uint32_t const block_address, uint32_t const num_blocks);

    /** Specify callback function and optional context pointer and working memory pointer.
     * @par Implemented as
     * - @ref RM_BLOCK_MEDIA_SDMMC_CallbackSet()
     *
     * @param[in]   p_ctrl                   Control block set in @ref rm_block_media_api_t::open call.
     * @param[in]   p_callback               Callback function to register
     * @param[in]   p_context                Pointer to send to callback function
     * @param[in]   p_working_memory         Pointer to volatile memory where callback structure can be allocated.
     *                                       Callback arguments allocated here are only valid during the callback.
     */
    fsp_err_t (* callbackSet)(rm_block_media_ctrl_t * const          p_ctrl,
                              void (                               * p_callback)(rm_block_media_callback_args_t *),
                              void const * const                     p_context,
                              rm_block_media_callback_args_t * const p_callback_memory);

    /** Get status of connected device.
     *
     * @par Implemented as
     * - @ref RM_BLOCK_MEDIA_SDMMC_StatusGet
     * - @ref RM_BLOCK_MEDIA_SPI_StatusGet
     * - @ref RM_BLOCK_MEDIA_USB_StatusGet
     *
     * @param[in]   p_ctrl             Control block set in @ref rm_block_media_api_t::open call.
     * @param[out]  p_status           Pointer to store current status.
     */
    fsp_err_t (* statusGet)(rm_block_media_ctrl_t * const p_ctrl, rm_block_media_status_t * const p_status);

    /** Returns information about the block media device.
     * @par Implemented as
     * - @ref RM_BLOCK_MEDIA_SDMMC_InfoGet
     * - @ref RM_BLOCK_MEDIA_SPI_InfoGet
     * - @ref RM_BLOCK_MEDIA_USB_InfoGet
     *
     * @param[in]   p_ctrl             Control block set in @ref rm_block_media_api_t::open call.
     * @param[out]  p_info             Pointer to information structure. All elements of this structure will be set by the
     *                                 function.
     */
    fsp_err_t (* infoGet)(rm_block_media_ctrl_t * const p_ctrl, rm_block_media_info_t * const p_info);

    /** Closes the module.
     * @par Implemented as
     * - @ref RM_BLOCK_MEDIA_SDMMC_Close
     * - @ref RM_BLOCK_MEDIA_SPI_Close
     * - @ref RM_BLOCK_MEDIA_USB_Close
     *
     * @param[in]   p_ctrl             Control block set in @ref rm_block_media_api_t::open call.
     */
    fsp_err_t (* close)(rm_block_media_ctrl_t * const p_ctrl);
} rm_block_media_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_rm_block_media_instance
{
    rm_block_media_ctrl_t      * p_ctrl; ///< Pointer to the control structure for this instance
    rm_block_media_cfg_t const * p_cfg;  ///< Pointer to the configuration structure for this instance
    rm_block_media_api_t const * p_api;  ///< Pointer to the API structure for this instance
} rm_block_media_instance_t;

/* Common macro for SSP header files. There is also a corresponding SSP_HEADER macro at the top of this file. */
FSP_FOOTER

/*******************************************************************************************************************//**
 * @} (end defgroup RM_BLOCK_MEDIA_API)
 **********************************************************************************************************************/

#endif                                 /* RM_BLOCK_MEDIA_API_H */
