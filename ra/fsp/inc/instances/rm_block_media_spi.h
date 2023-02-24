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

#ifndef RM_BLOCK_MEDIA_SPI_H
#define RM_BLOCK_MEDIA_SPI_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "r_spi_flash_api.h"
#include "rm_block_media_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/*******************************************************************************************************************//**
 * @addtogroup RM_BLOCK_MEDIA_SPI
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/* Extended configuration structure. */
typedef struct st_rm_block_media_spi_extended_cfg
{
    spi_flash_instance_t const * p_spi;

    uint32_t block_size_bytes;         ///< Block size, must be a power of 2 multiple of sector_size_bytes
    uint32_t block_count_total;        ///< Total number of blocks registered for use
    uint32_t base_address;             ///< Base address of memory mapped region. Can be offset to use subset of available flash size if desired.
} rm_block_media_spi_extended_cfg_t;

/** SPI block media instance control block. */
typedef struct st_rm_block_media_spi_instance_ctrl
{
    spi_flash_instance_t       * p_spi_flash; ///< Pointer to SPI Flash instance structure
    rm_block_media_cfg_t const * p_cfg;       ///< Low level SPI configuration structure
    uint32_t open;                            ///< Used to determine if framework is initialized.
    bool     initialized;                     ///< Initialized flag

    /* Busy flags */
    bool erase_in_progress;                   ///< Block Media SPI erase in progress
    bool read_in_progress;                    ///< Block Media SPI read in progress
    bool write_in_progress;                   ///< Block Media SPI write in progress
} rm_block_media_spi_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
extern const rm_block_media_api_t g_rm_block_media_on_spi;

/** @endcond */

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/
fsp_err_t RM_BLOCK_MEDIA_SPI_Open(rm_block_media_ctrl_t * const p_ctrl, rm_block_media_cfg_t const * const p_cfg);
fsp_err_t RM_BLOCK_MEDIA_SPI_MediaInit(rm_block_media_ctrl_t * const p_ctrl);
fsp_err_t RM_BLOCK_MEDIA_SPI_Read(rm_block_media_ctrl_t * const p_ctrl,
                                  uint8_t * const               p_dest,
                                  uint32_t const                start_block,
                                  uint32_t const                num_blocks);
fsp_err_t RM_BLOCK_MEDIA_SPI_Write(rm_block_media_ctrl_t * const p_ctrl,
                                   uint8_t const * const         p_src,
                                   uint32_t const                start_block,
                                   uint32_t const                num_blocks);
fsp_err_t RM_BLOCK_MEDIA_SPI_Erase(rm_block_media_ctrl_t * const p_ctrl,
                                   uint32_t const                start_block,
                                   uint32_t const                num_blocks);
fsp_err_t RM_BLOCK_MEDIA_SPI_CallbackSet(rm_block_media_ctrl_t * const p_ctrl,
                                         void (                      * p_callback)(
                                             rm_block_media_callback_args_t *),
                                         void const * const                     p_context,
                                         rm_block_media_callback_args_t * const p_callback_memory);
fsp_err_t RM_BLOCK_MEDIA_SPI_StatusGet(rm_block_media_ctrl_t * const p_ctrl, rm_block_media_status_t * const p_status);
fsp_err_t RM_BLOCK_MEDIA_SPI_InfoGet(rm_block_media_ctrl_t * const p_ctrl, rm_block_media_info_t * const p_info);
fsp_err_t RM_BLOCK_MEDIA_SPI_Close(rm_block_media_ctrl_t * const p_ctrl);

#endif                                 /* FSP_INC_FRAMEWORK_INSTANCES_RM_BLOCK_MEDIA_SPI_H_ */

/*******************************************************************************************************************//**
 * @} (end addtogroup RM_BLOCK_MEDIA_SPI)
 **********************************************************************************************************************/
