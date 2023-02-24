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

#ifndef RM_FILEX_BLOCK_MEDIA_API_H
 #define RM_FILEX_BLOCK_MEDIA_API_H

/*******************************************************************************************************************//**
 * @ingroup RENESAS_INTERFACES
 * @defgroup RM_FILEX_BLOCK_MEDIA_API FileX Block Media Port Interface
 * @brief Interface for FileX Block Media port.
 *
 * @section RM_FILEX_BLOCK_MEDIA_SUMMARY Summary
 * The FileX block media port provides notifications for insertion and removal of removable media and provides
 * initialization functions required by FileX.
 *
 * The FileX Block media interface can be implemented by:
 * @ref RM_FILEX_BLOCK_MEDIA
 *
 * @{
 **********************************************************************************************************************/

 #ifdef __cplusplus
extern "C" {
 #endif

 #include "bsp_api.h"
 #include "rm_block_media_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Partitions that can be selected to use FileX with */
typedef enum e_rm_filex_block_media_partition
{
    RM_FILEX_BLOCK_MEDIA_PARTITION0 = 0, ///< Partition 0 (0x01BE) in Master Boot Record Partition Table
    RM_FILEX_BLOCK_MEDIA_PARTITION1 = 1, ///< Partition 1 (0x01CE) in Master Boot Record Partition Table
    RM_FILEX_BLOCK_MEDIA_PARTITION2 = 2, ///< Partition 2 (0x01DE) in Master Boot Record Partition Table
    RM_FILEX_BLOCK_MEDIA_PARTITION3 = 3, ///< Partition 3 (0x01EE) in Master Boot Record Partition Table
} rm_filex_block_media_partition_t;

/** Callback function parameter data */
typedef struct st_rm_filex_block_media_callback_args
{
    rm_block_media_event_t event;      ///< The event can be used to identify what caused the callback.
    void const           * p_context;  ///< Placeholder for user data.
} rm_filex_block_media_callback_args_t;

/** Block media configuration structure */
typedef struct st_rm_filex_block_media_cfg
{
    rm_block_media_instance_t      * p_lower_lvl_block_media;           ///< Lower level block media pointer
    rm_filex_block_media_partition_t partition;                         ///< Partition to use for partitioned media
    void (* p_callback)(rm_filex_block_media_callback_args_t * p_args); ///< Pointer to callback function
    void * p_extend;
} rm_filex_block_media_cfg_t;

/** Block media control structure */
typedef void rm_filex_block_media_ctrl_t;

/** FileX block media functions implemented at the HAL layer will follow this API. */
typedef struct st_rm_filex_block_media_api
{
    /** Open media device.
     * @par Implemented as
     * - @ref RM_FILEX_BLOCK_MEDIA_Open()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_cfg        Pointer to configuration structure.
     */
    fsp_err_t (* open)(rm_filex_block_media_ctrl_t * const p_ctrl, rm_filex_block_media_cfg_t const * const p_cfg);

    /** Close media device.
     * @par Implemented as
     * - @ref RM_FILEX_BLOCK_MEDIA_Close()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* close)(rm_filex_block_media_ctrl_t * const p_ctrl);
} rm_filex_block_media_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_rm_filex_block_media_instance
{
    rm_filex_block_media_ctrl_t            * p_ctrl; ///< Pointer to the control structure for this instance
    rm_filex_block_media_cfg_t const * const p_cfg;  ///< Pointer to the configuration structure for this instance
    rm_filex_block_media_api_t const       * p_api;  ///< Pointer to the API structure for this instance
} rm_filex_block_media_instance_t;

 #ifdef __cplusplus
} /* extern "C" */
 #endif

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 /* RM_FILEX_BLOCK_MEDIA_API_H */

/*******************************************************************************************************************//**
 * @} (end addtogroup RM_FILEX_BLOCK_MEDIA_API)
 **********************************************************************************************************************/
