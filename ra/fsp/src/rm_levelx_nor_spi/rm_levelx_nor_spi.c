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
#include "rm_levelx_nor_spi.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* "LXNO" in ASCII, used to identify LevelX NOR SPI handle */
#define RM_LEVELX_NOR_SPI_OPEN              (0x4C584E4FU)

#define RM_LEVELX_NOR_SPI_BYTES_PER_WORD    (4U)
#define RM_LEVELX_NOR_SPI_FLASH_CLEARED     (0xFF)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global variables (to be accessed by other files)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

static fsp_err_t rm_levelx_nor_spi_wait_write_erase_complete(rm_levelx_nor_spi_instance_ctrl_t * const p_ctrl);

/***********************************************************************************************************************
 * Global Variables
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @addtogroup RM_LEVELX_NOR_SPI
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief  Initializes LevelX NOR SPI port read/write and control.
 *
 * Calls lower level SPI memory functions.
 *
 * @param[in,out]  p_ctrl               Control block for the LevelX NOR SPI instance.
 * @param[in,out]  p_cfg                Configuration for LevelX NOR SPI port.
 *
 * @retval FSP_SUCCESS                  LevelX NOR driver is successfully opened.
 * @retval FSP_ERR_ASSERTION            p_ctrl or p_cfg is NULL.
 * @retval FSP_ERR_ALREADY_OPEN         Driver is already in OPEN state.
 * @return                              See @ref Common_Error_Codes or lower level drivers for other possible return
 *                                      codes. This function calls
 *                                        * spi_flash_api_t:open
 **********************************************************************************************************************/
fsp_err_t RM_LEVELX_NOR_SPI_Open (rm_levelx_nor_spi_instance_ctrl_t * const p_ctrl,
                                  rm_levelx_nor_spi_cfg_t const * const     p_cfg)
{
    fsp_err_t err = FSP_SUCCESS;

#if RM_LEVELX_NOR_SPI_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_cfg);
    FSP_ASSERT(NULL != p_cfg->p_lower_lvl);
    FSP_ASSERT(NULL != p_cfg->p_lx_nor_flash);
    FSP_ERROR_RETURN(RM_LEVELX_NOR_SPI_OPEN != p_ctrl->open, FSP_ERR_ALREADY_OPEN);
    FSP_ASSERT(RM_LEVELX_NOR_SPI_CFG_BUFFER_SIZE >= p_cfg->p_lower_lvl->p_cfg->page_size_bytes);
#endif

    /** Update the instance control block */
    p_ctrl->p_cfg              = p_cfg;
    p_ctrl->start_address      = p_cfg->base_address + p_cfg->address_offset;
    p_ctrl->minimum_erase_size = UINT32_MAX;

    /* Set minimum erase size */
    spi_flash_cfg_t * spi_memory_cfg = (spi_flash_cfg_t *) p_cfg->p_lower_lvl->p_cfg;
    for (uint8_t i = 0; i < spi_memory_cfg->erase_command_list_length; i++)
    {
        uint32_t erase_size = spi_memory_cfg->p_erase_command_list[i].size;
        if (erase_size < p_ctrl->minimum_erase_size)
        {
            p_ctrl->minimum_erase_size = erase_size;
        }
    }

    /** Open the underlying SPI memory instance */
    err = p_cfg->p_lower_lvl->p_api->open(p_cfg->p_lower_lvl->p_ctrl, p_cfg->p_lower_lvl->p_cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /** Setup the base address of the flash memory.  */
    p_cfg->p_lx_nor_flash->lx_nor_flash_base_address = (ULONG *) p_ctrl->start_address;

    /** Setup geometry of the flash.  */
    p_cfg->p_lx_nor_flash->lx_nor_flash_total_blocks = p_cfg->size / p_ctrl->minimum_erase_size;

    p_cfg->p_lx_nor_flash->lx_nor_flash_words_per_block = p_ctrl->minimum_erase_size /
                                                          RM_LEVELX_NOR_SPI_BYTES_PER_WORD;

    /** Mark control block open so subsequent calls know the device is open. */
    p_ctrl->open = RM_LEVELX_NOR_SPI_OPEN;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief  LevelX NOR driver "read sector" service.
 *
 * This is responsible for reading a specific sector in a specific block of the NOR flash. All error checking and
 * correcting logic is the responsibility of this service.
 *
 * @param[in]      p_ctrl               Control block for the LevelX NOR SPI instance.
 * @param[in]      p_flash_addr              Specifies the address of a logical sector within a NOR flash block of memory.
 * @param[in,out]  p_dest               Specifies where to place the sector contents.
 * @param[in]      word_count           Specifies how many 32-bit words to read.
 *
 * @retval FSP_SUCCESS                  LevelX NOR flash sector read successful.
 * @retval FSP_ERR_ASSERTION            p_ctrl, p_flash_addr or p_dest is NULL.
 * @retval FSP_ERR_NOT_OPEN             Driver not in OPEN state for reading.
 * @return                              See @ref Common_Error_Codes or lower level drivers for other possible return
 *                                      codes.
 **********************************************************************************************************************/
fsp_err_t RM_LEVELX_NOR_SPI_Read (rm_levelx_nor_spi_instance_ctrl_t * const p_ctrl,
                                  ULONG * const                             p_flash_addr,
                                  ULONG * const                             p_dest,
                                  ULONG                                     word_count)
{
#if RM_LEVELX_NOR_SPI_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_flash_addr);
    FSP_ASSERT(NULL != p_dest);
    FSP_ERROR_RETURN(RM_LEVELX_NOR_SPI_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
#endif

    uint32_t byte_count = word_count * RM_LEVELX_NOR_SPI_BYTES_PER_WORD;

    /* Read data from SPI flash */
    memcpy((uint8_t *) p_dest, (uint8_t *) p_flash_addr, byte_count);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief  LevelX NOR driver "write sector" service.
 *
 * This is responsible for writing a specific sector into a block of the NOR flash. All error checking is the
 * responsibility of the this service.
 *
 * @param[in]      p_ctrl               Control block for the LevelX NOR SPI instance.
 * @param[in,out]  p_flash_addr              Specifies the address of a logical sector within a NOR flash block of memory.
 * @param[in]      p_src                Specifies the source of the write.
 * @param[in]      word_count           Specifies how many 32-bit words to write.
 *
 * @retval FSP_SUCCESS                  LevelX NOR flash sector write successful.
 * @retval FSP_ERR_ASSERTION            p_ctrl, p_flash_addr or p_src is NULL.
 * @retval FSP_ERR_NOT_OPEN             Driver not in OPEN state for writing.
 * @retval FSP_ERR_TIMEOUT              Timeout occurred while waiting for operation to complete.
 * @retval FSP_ERR_WRITE_FAILED         Verification of Write operation failed.
 * @retval FSP_ERR_INVALID_ADDRESS      Write address or size falls outside of flash memory range.
 * @return                              See @ref Common_Error_Codes or lower level drivers for other possible return
 *                                      codes. This function calls
 *                                        * spi_flash_api_t:write
 **********************************************************************************************************************/
fsp_err_t RM_LEVELX_NOR_SPI_Write (rm_levelx_nor_spi_instance_ctrl_t * const p_ctrl,
                                   ULONG * const                             p_flash_addr,
                                   ULONG * const                             p_src,
                                   ULONG                                     word_count)
{
    fsp_err_t err;
    bool      read_from_spi      = false;
    uint32_t  current_write_size = 0;
    uint8_t * p_local_src_address;

#if RM_LEVELX_NOR_SPI_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_flash_addr);
    FSP_ASSERT(NULL != p_src);
    FSP_ERROR_RETURN(RM_LEVELX_NOR_SPI_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    spi_flash_instance_t * p_spi_flash_instance = (spi_flash_instance_t *) p_ctrl->p_cfg->p_lower_lvl;
    uint32_t               page_size            = p_spi_flash_instance->p_cfg->page_size_bytes;

    uint32_t byte_count = word_count * RM_LEVELX_NOR_SPI_BYTES_PER_WORD;

    /* The QSPI hardware is unable to write data correctly when the source address lies within the QSPI NOR itself
     * This limitation is overcome by copying the source data into local buffer and passing its address as
     * parameter to low level page program write API. LevelX can attempt to perform this sort of operation
     * if LX_DIRECT_READ is enabled */
    if (((uint32_t) p_src >= p_ctrl->start_address) &&
        ((uint32_t) p_src <= (p_ctrl->start_address + p_ctrl->p_cfg->size)))
    {
        if (((uint32_t) p_src + byte_count) > (p_ctrl->start_address + p_ctrl->p_cfg->size))
        {
            return FSP_ERR_INVALID_ADDRESS;
        }

        read_from_spi = true;
    }

    for (uint32_t offset = 0U; offset < byte_count; offset += current_write_size)
    {
        /* Calculate current write size */
        current_write_size = page_size - (((uint32_t) p_flash_addr + offset) % page_size);

        if (current_write_size > (byte_count - offset))
        {
            current_write_size = byte_count - offset;
        }

        /* Check whether the source address refers to address space of SPI NOR device */
        if (true == read_from_spi)
        {
            p_local_src_address = p_ctrl->page_buffer;

            /* Copy data from source address to a buffer for write if the source address is within address range of SPI NOR */
            memcpy(p_ctrl->page_buffer, (void *) ((uint32_t) p_src + offset), current_write_size);
        }
        else
        {
            p_local_src_address = (uint8_t *) ((uint32_t) p_src + offset);
        }

        /* Program using underlying SPI memory driver */
        err = p_spi_flash_instance->p_api->write(p_spi_flash_instance->p_ctrl,
                                                 p_local_src_address,
                                                 (uint8_t *) p_flash_addr + offset,
                                                 current_write_size);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

        err = rm_levelx_nor_spi_wait_write_erase_complete(p_ctrl);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }

#if RM_LEVELX_NOR_SPI_CFG_VERIFY_AFTER_WRITE

    /* Verify data was written */
    FSP_ERROR_RETURN(!memcmp(p_flash_addr, p_src, byte_count), FSP_ERR_WRITE_FAILED);
#endif

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief  LevelX NOR driver "block erase" service.
 *
 * This is responsible for erasing the specified block of the NOR flash.
 *
 * @param[in]      p_ctrl               Control block for the LevelX NOR SPI instance.
 * @param[in]      block                Specifies which NOR block to erase.
 * @param[in]      erase_count          Provided for diagnostic purposes(currently unused).
 *
 * @retval FSP_SUCCESS                  LevelX NOR flash block erase successful.
 * @retval FSP_ERR_ASSERTION            p_ctrl is NULL.
 * @retval FSP_ERR_NOT_OPEN             Driver not in OPEN state for erasing.
 * @retval FSP_ERR_TIMEOUT              Timeout occurred while waiting for operation to complete.
 * @return                              See @ref Common_Error_Codes or lower level drivers for other possible return
 *                                      codes. This function calls
 *                                        * spi_flash_api_t:erase
 **********************************************************************************************************************/
fsp_err_t RM_LEVELX_NOR_SPI_BlockErase (rm_levelx_nor_spi_instance_ctrl_t * const p_ctrl, ULONG block,
                                        ULONG erase_count)
{
    fsp_err_t              err;
    spi_flash_instance_t * p_spi_flash_instance;
    uint32_t               block_address;

    FSP_PARAMETER_NOT_USED(erase_count);

#if RM_LEVELX_NOR_SPI_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_ctrl);
    FSP_ERROR_RETURN(RM_LEVELX_NOR_SPI_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    p_spi_flash_instance = (spi_flash_instance_t *) p_ctrl->p_cfg->p_lower_lvl;

    /* Calculate the block address */
    block_address = p_ctrl->start_address + ((uint32_t) block * p_ctrl->minimum_erase_size);

    /* Erase using underlying API */
    err = p_spi_flash_instance->p_api->erase(p_spi_flash_instance->p_ctrl,
                                             (uint8_t *) block_address,
                                             p_ctrl->minimum_erase_size);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    err = rm_levelx_nor_spi_wait_write_erase_complete(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief  LevelX NOR driver "block erased verify" service.
 *
 * This is responsible for verifying the specified block of the NOR flash is erased.
 *
 * @param[in]      p_ctrl               Control block for the LevelX NOR SPI instance.
 * @param[in]      block                Specifies which block to verify that it is erased.
 *
 * @retval FSP_SUCCESS                  LevelX flash block erase verification successful.
 * @retval FSP_ERR_ASSERTION            p_ctrl or lower level driver is NULL.
 * @retval FSP_ERR_NOT_OPEN             Driver not in OPEN state for verifying.
 * @retval FSP_ERR_NOT_ERASED           The block is not erased properly.
 * @return                              See @ref Common_Error_Codes or lower level drivers for other possible return
 *                                      codes.
 **********************************************************************************************************************/
fsp_err_t RM_LEVELX_NOR_SPI_BlockErasedVerify (rm_levelx_nor_spi_instance_ctrl_t * const p_ctrl, ULONG block)
{
    uint8_t * read_address;

#if RM_LEVELX_NOR_SPI_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_ctrl);
    FSP_ERROR_RETURN(RM_LEVELX_NOR_SPI_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    read_address = (uint8_t *) (p_ctrl->start_address + (block * p_ctrl->minimum_erase_size));

    /* Loop to check if the block is erased.  */
    for (uint32_t offset = 0U; offset < p_ctrl->minimum_erase_size; offset++)
    {
        if (RM_LEVELX_NOR_SPI_FLASH_CLEARED != read_address[offset])
        {
            return FSP_ERR_NOT_ERASED;
        }
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief  LevelX NOR driver close service.
 *
 * This is responsible for closing the driver properly.
 *
 * @param[in]      p_ctrl               Control block for the LevelX NOR SPI instance.
 *
 * @retval FSP_SUCCESS                  LevelX flash is available and is now open for read, write, and control access.
 * @retval FSP_ERR_ASSERTION            p_ctrl is NULL.
 * @retval FSP_ERR_NOT_OPEN             Driver not in OPEN state for closing.
 * @return                              See @ref Common_Error_Codes or lower level drivers for other possible return
 *                                      codes. This function calls
 *                                        * spi_flash_api_t:close
 **********************************************************************************************************************/
fsp_err_t RM_LEVELX_NOR_SPI_Close (rm_levelx_nor_spi_instance_ctrl_t * const p_ctrl)
{
    spi_flash_instance_t * p_spi_flash_instance;

#if RM_LEVELX_NOR_SPI_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_ctrl);
    FSP_ERROR_RETURN(RM_LEVELX_NOR_SPI_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Reset OPEN state */
    p_ctrl->open = 0U;

    p_spi_flash_instance = (spi_flash_instance_t *) p_ctrl->p_cfg->p_lower_lvl;

    /* Close underlying API */
    p_spi_flash_instance->p_api->close(p_spi_flash_instance->p_ctrl);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup RM_LEVELX_NOR_SPI)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief      Wait until the current program or erase operation completes.
 * @param      p_ctrl                   The instance control block
 * @retval     FSP_SUCCESS              Successfully waited.
 * @retval     FSP_ERR_TIMEOUT          Wait timed out.
 * @return                              See @ref Common_Error_Codes or HAL driver for other possible return codes or
 *                                      causes.
 *                                      This function calls
 *                                          * spi_flash_api_t::statusGet
 **********************************************************************************************************************/
static fsp_err_t rm_levelx_nor_spi_wait_write_erase_complete (rm_levelx_nor_spi_instance_ctrl_t * const p_ctrl)
{
    spi_flash_status_t                status;
    fsp_err_t                         err;
    rm_levelx_nor_spi_callback_args_t args;
    spi_flash_instance_t            * p_spi_flash_instance = (spi_flash_instance_t *) p_ctrl->p_cfg->p_lower_lvl;
    uint32_t status_polls_remaining = p_ctrl->p_cfg->poll_status_count;

    status.write_in_progress = true;

    /* While the SPI driver is busy call the delay callback if defined. If timeout return error. */
    do
    {
        err = p_spi_flash_instance->p_api->statusGet(p_spi_flash_instance->p_ctrl, &status);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

        /* If write in progress call the user defined callback function. */
        if (status.write_in_progress)
        {
            if (NULL != p_ctrl->p_cfg->p_callback)
            {
                args.event     = RM_LEVELX_NOR_SPI_EVENT_BUSY;
                args.p_context = p_ctrl->p_cfg->p_context;
                p_ctrl->p_cfg->p_callback(&args);
            }

            status_polls_remaining--;
        }
    } while (status.write_in_progress && (status_polls_remaining > 0U));

    /* Check whether write completed */
    FSP_ERROR_RETURN(!status.write_in_progress, FSP_ERR_TIMEOUT);

    return FSP_SUCCESS;
}
