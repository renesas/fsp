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

#ifndef RM_LEVELX_NOR_SPI_H
#define RM_LEVELX_NOR_SPI_H

/*******************************************************************************************************************//**
 * @addtogroup RM_LEVELX_NOR_SPI
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 ***********************************************************************************************************************/
#include "bsp_api.h"
#include "r_spi_flash_api.h"
#include "lx_api.h"
#include "rm_levelx_nor_spi_cfg.h"

/** Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 ***********************************************************************************************************************/

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Options for the callback events. */
typedef enum e_rm_levelx_nor_spi_event
{
    RM_LEVELX_NOR_SPI_EVENT_BUSY,      ///< Pending operation, user can define their own wait functionality.
} rm_levelx_nor_spi_event_t;

/** RM_LEVELX_NOR_SPI callback arguments definitions  */
typedef struct st_rm_levelx_nor_spi_callback_args
{
    rm_levelx_nor_spi_event_t event;     ///< LevelX NOR driver callback event
    void const              * p_context; ///< Placeholder for user data
} rm_levelx_nor_spi_callback_args_t;

/** SF_EL_LX_NOR Config Block Type */
typedef struct st_rm_levelx_nor_spi_cfg
{
    spi_flash_instance_t const * p_lower_lvl;                        ///< Lower level memory pointer
    LX_NOR_FLASH               * p_lx_nor_flash;                     ///< Pointer to the LevelX nor flash instance.
    uint32_t     base_address;                                       ///< Base address of memory mapped region.
    uint32_t     address_offset;                                     ///< Offset to use subset of available flash size if desired.
    uint32_t     size;                                               ///< Size of the partitioned region.
    uint32_t     poll_status_count;                                  ///< Number of times to poll for operation complete status before returning an error.
    void const * p_context;                                          ///< Placeholder for user data. Passed to the user callback.
    void (* p_callback)(rm_levelx_nor_spi_callback_args_t * p_args); ///< Callback function
} rm_levelx_nor_spi_cfg_t;

/** SF_EL_LX_NOR Control Block Type */
typedef struct st_rm_levelx_nor_spi_instance_ctrl
{
    rm_levelx_nor_spi_cfg_t const * p_cfg;                   ///< Pointer to instance configuration.
    uint32_t start_address;                                  ///< Start address of partition to use within memory mapped region.
    uint32_t minimum_erase_size;                             ///< Minimum erase size of SPI memory
    uint8_t  page_buffer[RM_LEVELX_NOR_SPI_CFG_BUFFER_SIZE]; ///< Page buffer for situations when writing to SPI memory from a source within SPI memory
    uint32_t open;                                           ///< Used to determine if module is initialized.
} rm_levelx_nor_spi_instance_ctrl_t;

/**********************************************************************************************************************
 * Public Functions
 **********************************************************************************************************************/
fsp_err_t RM_LEVELX_NOR_SPI_Open(rm_levelx_nor_spi_instance_ctrl_t * const p_ctrl,
                                 rm_levelx_nor_spi_cfg_t const * const     p_cfg);

fsp_err_t RM_LEVELX_NOR_SPI_Read(rm_levelx_nor_spi_instance_ctrl_t * const p_ctrl,
                                 ULONG * const                             p_flash_addr,
                                 ULONG * const                             p_dest,
                                 ULONG                                     word_count);

fsp_err_t RM_LEVELX_NOR_SPI_Write(rm_levelx_nor_spi_instance_ctrl_t * const p_ctrl,
                                  ULONG * const                             p_flash_addr,
                                  ULONG * const                             p_src,
                                  ULONG                                     word_count);

fsp_err_t RM_LEVELX_NOR_SPI_BlockErase(rm_levelx_nor_spi_instance_ctrl_t * const p_ctrl, ULONG block,
                                       ULONG erase_count);

fsp_err_t RM_LEVELX_NOR_SPI_BlockErasedVerify(rm_levelx_nor_spi_instance_ctrl_t * const p_ctrl, ULONG block);

fsp_err_t RM_LEVELX_NOR_SPI_Close(rm_levelx_nor_spi_instance_ctrl_t * const p_ctrl);

/** Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

/*******************************************************************************************************************//**
 * @} (end addtogroup RM_LEVELX_NOR_SPI)
 **********************************************************************************************************************/

#endif
