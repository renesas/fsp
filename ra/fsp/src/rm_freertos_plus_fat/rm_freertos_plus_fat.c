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

/* Standard includes. */
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>

#if (BSP_CFG_RTOS == 2)                // FreeRTOS
 #include "FreeRTOS.h"
 #include "task.h"
 #include "semphr.h"
 #include "FreeRTOSFATConfig.h"
#endif

/* FSP includes. */
#include "rm_freertos_plus_fat.h"
#include "rm_freertos_plus_fat_cfg.h"

#if (BSP_CFG_RTOS == 2)                // FreeRTOS

 #ifndef RM_FREERTOS_PLUS_FAT_READ_TIMEOUT_TICKS
  #define RM_FREERTOS_PLUS_FAT_READ_TIMEOUT_TICKS     (portMAX_DELAY)
 #endif

 #ifndef RM_FREERTOS_PLUS_FAT_WRITE_TIMEOUT_TICKS
  #define RM_FREERTOS_PLUS_FAT_WRITE_TIMEOUT_TICKS    (portMAX_DELAY)
 #endif

#else

 #ifndef RM_FREERTOS_PLUS_FAT_READ_TIMEOUT_TICKS
  #define RM_FREERTOS_PLUS_FAT_READ_TIMEOUT_TICKS     (0)
 #endif

 #ifndef RM_FREERTOS_PLUS_FAT_WRITE_TIMEOUT_TICKS
  #define RM_FREERTOS_PLUS_FAT_WRITE_TIMEOUT_TICKS    (0)
 #endif

#endif

#define RM_FREERTOS_PLUS_FAT_MIN_SECTOR_SIZE_BYTES    (512)

/** "FFAT" in ASCII, used to determine if channel is open. */
#define RM_FREERTOS_PLUS_FAT_OPEN                     (0x70706584ULL)

int32_t rm_freertos_plus_fat_read(uint8_t * p_data, uint32_t sector, uint32_t num_sectors, FF_Disk_t * p_disk);
int32_t rm_freertos_plus_fat_write(uint8_t * p_data, uint32_t sector, uint32_t num_sectors,
                                   FF_Disk_t * p_disk);
void             rm_freertos_plus_fat_memory_callback(rm_block_media_callback_args_t * p_args);
static fsp_err_t rm_freertos_plus_fat_wait_event(rm_freertos_plus_fat_instance_ctrl_t * p_instance_ctrl,
                                                 uint32_t                               timeout);
static fsp_err_t rm_freertos_plus_fat_wait_for_device(rm_freertos_plus_fat_instance_ctrl_t * p_instance_ctrl);

/** FAT HAL API mapping for FreeRTOS_plus_FAT Controller interface */
const rm_freertos_plus_fat_api_t g_fat_on_freertos =
{
    .open       = RM_FREERTOS_PLUS_FAT_Open,
    .mediaInit  = RM_FREERTOS_PLUS_FAT_MediaInit,
    .diskInit   = RM_FREERTOS_PLUS_FAT_DiskInit,
    .diskDeinit = RM_FREERTOS_PLUS_FAT_DiskDeinit,
    .infoGet    = RM_FREERTOS_PLUS_FAT_InfoGet,
    .close      = RM_FREERTOS_PLUS_FAT_Close,
};

/*******************************************************************************************************************//**
 * @addtogroup RM_FREERTOS_PLUS_FAT
 * @{
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Initializes lower layer media device.
 *
 * Implements @ref rm_freertos_plus_fat_api_t::open().
 *
 * @retval FSP_SUCCESS              Success.
 * @retval FSP_ERR_ASSERTION        An input parameter was invalid.
 * @retval FSP_ERR_ALREADY_OPEN     Module is already open.
 * @retval FSP_ERR_OUT_OF_MEMORY    Not enough memory to create semaphore.
 *
 * @return See @ref RENESAS_ERROR_CODES or functions called by this function for other possible return codes.
 *         This function calls:
 *             * @ref rm_block_media_api_t::open
 **********************************************************************************************************************/
fsp_err_t RM_FREERTOS_PLUS_FAT_Open (rm_freertos_plus_fat_ctrl_t * const      p_ctrl,
                                     rm_freertos_plus_fat_cfg_t const * const p_cfg)
{
    rm_freertos_plus_fat_instance_ctrl_t * p_instance_ctrl = (rm_freertos_plus_fat_instance_ctrl_t *) p_ctrl;

#if RM_FREERTOS_PLUS_FAT_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_cfg);
    FSP_ERROR_RETURN(RM_FREERTOS_PLUS_FAT_OPEN != p_instance_ctrl->open, FSP_ERR_ALREADY_OPEN);
#endif

#if 2 == BSP_CFG_RTOS

    /* The semaphore will be used to protect critical sections in
     * the +FAT disk, and also to avoid concurrent calls to Read()/Write()
     * from different tasks. */
    p_instance_ctrl->p_mutex = (void *) xSemaphoreCreateRecursiveMutex();
    FSP_ERROR_RETURN(NULL != p_instance_ctrl->p_mutex, FSP_ERR_OUT_OF_MEMORY);
#endif

    /* Open lower layer. */
    fsp_err_t err = p_cfg->p_block_media->p_api->open(p_cfg->p_block_media->p_ctrl, p_cfg->p_block_media->p_cfg);

#if 2 == BSP_CFG_RTOS
    if (FSP_SUCCESS != err)
    {
        /* If open fails, clean up mutex. */
        vSemaphoreDelete(p_instance_ctrl->p_mutex);
        p_instance_ctrl->p_mutex = NULL;
    }
#endif
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Initialize control structure. */
    p_instance_ctrl->p_cfg = p_cfg;
    p_instance_ctrl->open  = RM_FREERTOS_PLUS_FAT_OPEN;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Initializes the media device. This function blocks until all identification and configuration commands are complete.
 *
 * Implements @ref rm_freertos_plus_fat_api_t::mediaInit().
 *
 * @retval     FSP_SUCCESS               Module is initialized and ready to access the memory device.
 * @retval     FSP_ERR_ASSERTION         An input parameter is invalid.
 * @retval     FSP_ERR_NOT_OPEN          Module has not been initialized.
 *
 * @return See @ref RENESAS_ERROR_CODES or functions called by this function for other possible return codes.
 *         This function calls:
 *             * @ref rm_block_media_api_t::mediaInit
 *             * @ref rm_block_media_api_t::infoGet
 **********************************************************************************************************************/
fsp_err_t RM_FREERTOS_PLUS_FAT_MediaInit (rm_freertos_plus_fat_ctrl_t * const   p_ctrl,
                                          rm_freertos_plus_fat_device_t * const p_device)
{
    rm_freertos_plus_fat_instance_ctrl_t * p_instance_ctrl = (rm_freertos_plus_fat_instance_ctrl_t *) p_ctrl;

#if RM_FREERTOS_PLUS_FAT_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(RM_FREERTOS_PLUS_FAT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    fsp_err_t fsp_err = p_instance_ctrl->p_cfg->p_block_media->p_api->mediaInit(
        p_instance_ctrl->p_cfg->p_block_media->p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == fsp_err, fsp_err);

    rm_block_media_info_t info;
    fsp_err =
        p_instance_ctrl->p_cfg->p_block_media->p_api->infoGet(p_instance_ctrl->p_cfg->p_block_media->p_ctrl, &info);
    FSP_ERROR_RETURN(FSP_SUCCESS == fsp_err, fsp_err);
    p_instance_ctrl->reentrant = info.reentrant;

    if (NULL != p_device)
    {
        p_device->sector_count      = info.num_sectors;
        p_device->sector_size_bytes = info.sector_size_bytes;
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Initializes a FreeRTOS+FAT disk structure.  This function calls FF_CreateIOManger.
 *
 * Implements @ref rm_freertos_plus_fat_api_t::diskInit().
 *
 * @retval     FSP_SUCCESS               Module is initialized and ready to access the memory device.
 * @retval     FSP_ERR_ASSERTION         An input parameter is invalid.
 * @retval     FSP_ERR_NOT_OPEN          Module has not been initialized.
 * @retval     FSP_ERR_INTERNAL          Call to FF_CreateIOManger failed.
 **********************************************************************************************************************/
fsp_err_t RM_FREERTOS_PLUS_FAT_DiskInit (rm_freertos_plus_fat_ctrl_t * const           p_ctrl,
                                         rm_freertos_plus_fat_disk_cfg_t const * const p_disk_cfg,
                                         FF_Disk_t * const                             p_disk)
{
    rm_freertos_plus_fat_instance_ctrl_t * p_instance_ctrl = (rm_freertos_plus_fat_instance_ctrl_t *) p_ctrl;

#if RM_FREERTOS_PLUS_FAT_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_disk_cfg);
    FSP_ASSERT(NULL != p_disk);
    FSP_ERROR_RETURN(RM_FREERTOS_PLUS_FAT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);

    /* Sector size must be a multiple of 512 bytes. */
    FSP_ASSERT(0U == p_disk_cfg->device.sector_size_bytes % RM_FREERTOS_PLUS_FAT_MIN_SECTOR_SIZE_BYTES);

    /* Cache size must be multple of sector size and at least 2 * sector size. */
    FSP_ASSERT(0U == p_disk_cfg->cache_size_bytes % p_disk_cfg->device.sector_size_bytes);
    FSP_ASSERT(p_disk_cfg->cache_size_bytes >= 2 * p_disk_cfg->device.sector_size_bytes);
#endif

    /* Initialise the disk structure. memset used to clear unused bitfields. */
    memset(p_disk, '\0', sizeof(FF_Disk_t));
    p_disk->ulNumberOfSectors        = p_disk_cfg->device.sector_count;
    p_disk->xStatus.bPartitionNumber = p_disk_cfg->partition_number;
    p_disk->pvTag = p_instance_ctrl;

    FF_CreationParameters_t xParameters;
    xParameters.pucCacheMemory          = p_disk_cfg->p_cache;
    xParameters.ulMemorySize            = p_disk_cfg->cache_size_bytes;
    xParameters.ulSectorSize            = (BaseType_t) p_disk_cfg->device.sector_size_bytes;
    xParameters.fnWriteBlocks           = rm_freertos_plus_fat_write;
    xParameters.fnReadBlocks            = rm_freertos_plus_fat_read;
    xParameters.pxDisk                  = p_disk;
    xParameters.xBlockDeviceIsReentrant = p_instance_ctrl->reentrant;

#if 2 == BSP_CFG_RTOS
    xParameters.pvSemaphore = p_instance_ctrl->p_mutex;
#else
    xParameters.pvSemaphore = NULL;
#endif

    FF_Error_t xFFError;
    p_disk->pxIOManager = FF_CreateIOManger(&xParameters, &xFFError);
    FSP_ERROR_RETURN(FF_ERR_NONE == xFFError, FSP_ERR_INTERNAL);

    p_disk->xStatus.bIsInitialised = 1U;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Deinitializes a FreeRTOS+FAT disk structure.  This function calls FF_DeleteIOManger.
 *
 * Implements @ref rm_freertos_plus_fat_api_t::diskDeinit().
 *
 * @retval     FSP_SUCCESS               Module is initialized and ready to access the memory device.
 * @retval     FSP_ERR_ASSERTION         An input parameter is invalid.
 * @retval     FSP_ERR_NOT_OPEN          Module has not been initialized.
 **********************************************************************************************************************/
fsp_err_t RM_FREERTOS_PLUS_FAT_DiskDeinit (rm_freertos_plus_fat_ctrl_t * const p_ctrl, FF_Disk_t * const p_disk)
{
    rm_freertos_plus_fat_instance_ctrl_t * p_instance_ctrl = (rm_freertos_plus_fat_instance_ctrl_t *) p_ctrl;

#if RM_FREERTOS_PLUS_FAT_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_disk);
    FSP_ERROR_RETURN(RM_FREERTOS_PLUS_FAT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#else
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
#endif

    FF_DeleteIOManager(p_disk->pxIOManager);
    p_disk->pxIOManager            = NULL;
    p_disk->xStatus.bIsInitialised = 0U;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Get partition information. This function can only be called after rm_freertos_plus_fat_api_t::diskInit().
 *
 * Implements @ref rm_freertos_plus_fat_api_t::infoGet().
 *
 * @retval FSP_SUCCESS           Information stored in p_info.
 * @retval FSP_ERR_ASSERTION     An input parameter was invalid.
 * @retval FSP_ERR_NOT_OPEN      Module not open.
 * @retval FSP_ERR_NOT_FOUND     The value of p_iomanager is NULL.
 **********************************************************************************************************************/
fsp_err_t RM_FREERTOS_PLUS_FAT_InfoGet (rm_freertos_plus_fat_ctrl_t * const p_ctrl,
                                        FF_Disk_t * const                   p_disk,
                                        rm_freertos_plus_fat_info_t * const p_info)
{
    rm_freertos_plus_fat_instance_ctrl_t * p_instance_ctrl = (rm_freertos_plus_fat_instance_ctrl_t *) p_ctrl;

#if RM_FREERTOS_PLUS_FAT_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_disk);
    FSP_ASSERT(NULL != p_info);
    FSP_ERROR_RETURN(RM_FREERTOS_PLUS_FAT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#else
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
#endif

    FF_IOManager_t * p_iomanager = p_disk->pxIOManager;

    p_info->type = (rm_freertos_plus_fat_type_t) p_iomanager->xPartition.ucType;

    if (0U == p_disk->xStatus.bIsInitialised)
    {
        return FSP_ERR_NOT_FOUND;
    }

    FF_Error_t ff_error;
    FF_GetFreeSize(p_iomanager, &ff_error);

    uint64_t free_sectors = (p_iomanager->xPartition.ulFreeClusterCount * p_iomanager->xPartition.ulSectorsPerCluster);
    p_info->sector_size         = p_iomanager->usSectorSize;
    p_info->free_sectors        = (uint32_t) free_sectors;
    p_info->sectors_per_cluster = p_iomanager->xPartition.ulSectorsPerCluster;
    p_info->total_sectors       = p_iomanager->xPartition.ulTotalSectors;
    p_info->p_volume_label      = (uint8_t *) p_iomanager->xPartition.pcVolumeLabel;
    p_info->partition_number    = p_disk->xStatus.bPartitionNumber;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Closes media device.
 *
 * Implements @ref rm_freertos_plus_fat_api_t::close().
 *
 * @retval FSP_SUCCESS           Media device closed.
 * @retval FSP_ERR_ASSERTION     An input parameter was invalid.
 * @retval FSP_ERR_NOT_OPEN      Module not open.
 *
 * @return See @ref RENESAS_ERROR_CODES or functions called by this function for other possible return codes.
 *         This function calls:
 *             * @ref rm_block_media_api_t::close
 **********************************************************************************************************************/
fsp_err_t RM_FREERTOS_PLUS_FAT_Close (rm_freertos_plus_fat_ctrl_t * const p_ctrl)
{
    rm_freertos_plus_fat_instance_ctrl_t * p_instance_ctrl = (rm_freertos_plus_fat_instance_ctrl_t *) p_ctrl;
#if RM_FREERTOS_PLUS_FAT_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(RM_FREERTOS_PLUS_FAT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    p_instance_ctrl->open = 0;
    p_instance_ctrl->p_cfg->p_block_media->p_api->close(p_instance_ctrl->p_cfg->p_block_media->p_ctrl);
#if 2 == BSP_CFG_RTOS
    vSemaphoreDelete(p_instance_ctrl->p_mutex);
#endif

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup FREERTOS_PLUS_FAT)
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Writes sectors to block media device.
 *
 * @param[in] p_data                   Buffer to store read data.
 * @param[in] sector                   Sector to read from.
 * @param[in] num_sectors              Number of sectors to read.
 * @param[in] p_disk                   Pointer to FreeRTOS+FAT disk structure.
 *
 * @retval     FF_ERR_NONE             Read is complete.
 * @retval     FF_ERR_IOMAN_DRIVER_FATAL_ERROR    Error reported by block media driver during read.
 **********************************************************************************************************************/
int32_t rm_freertos_plus_fat_read (uint8_t * p_data, uint32_t sector, uint32_t num_sectors, FF_Disk_t * p_disk) {
    fsp_err_t err;
    int32_t   lReturnCode = (int32_t) (FF_ERR_IOMAN_OUT_OF_BOUNDS_READ | FF_ERRFLAG);

    rm_freertos_plus_fat_instance_ctrl_t * p_instance_ctrl = (rm_freertos_plus_fat_instance_ctrl_t *) p_disk->pvTag;

#if 2 == BSP_CFG_RTOS

    /* Store the handle of the calling task. */
    p_instance_ctrl->current_task = xTaskGetCurrentTaskHandle();
#else
    p_instance_ctrl->event_ready = false;
#endif

    p_instance_ctrl->last_event = (rm_block_media_event_t) 0;

    err = p_instance_ctrl->p_cfg->p_block_media->p_api->read(p_instance_ctrl->p_cfg->p_block_media->p_ctrl,
                                                             p_data,
                                                             sector,
                                                             num_sectors);
    if (FSP_SUCCESS == err)
    {
        err = rm_freertos_plus_fat_wait_event(p_instance_ctrl, RM_FREERTOS_PLUS_FAT_READ_TIMEOUT_TICKS);
    }

    if (FSP_SUCCESS != err)
    {
        return (int32_t) (FF_ERR_IOMAN_DRIVER_FATAL_ERROR | FF_ERRFLAG);
    }

    lReturnCode = FF_ERR_NONE;

    return lReturnCode;
}

/*******************************************************************************************************************//**
 * Writes sectors to block media device.
 *
 * @param[in] p_data                   Data to write.
 * @param[in] sector                   Sector to write to.
 * @param[in] num_sectors              Number of sectors to write.
 * @param[in] p_disk                   Pointer to FreeRTOS+FAT disk structure.
 *
 * @retval     FF_ERR_NONE             Write is complete.
 * @retval     FF_ERR_IOMAN_DRIVER_FATAL_ERROR    Error reported by block media driver during write.
 **********************************************************************************************************************/
int32_t rm_freertos_plus_fat_write (uint8_t * p_data, uint32_t sector, uint32_t num_sectors, FF_Disk_t * p_disk) {
    fsp_err_t err;
    int32_t   lReturnCode = (int32_t) (FF_ERR_IOMAN_OUT_OF_BOUNDS_READ | FF_ERRFLAG);

    rm_freertos_plus_fat_instance_ctrl_t * p_instance_ctrl = (rm_freertos_plus_fat_instance_ctrl_t *) p_disk->pvTag;

#if 2 == BSP_CFG_RTOS

    /* Store the handle of the calling task. */
    p_instance_ctrl->current_task = xTaskGetCurrentTaskHandle();
#else
    p_instance_ctrl->event_ready = false;
#endif

    p_instance_ctrl->last_event = (rm_block_media_event_t) 0;

    err = p_instance_ctrl->p_cfg->p_block_media->p_api->write(p_instance_ctrl->p_cfg->p_block_media->p_ctrl,
                                                              p_data,
                                                              sector,
                                                              num_sectors);
    if (FSP_SUCCESS == err)
    {
        err = rm_freertos_plus_fat_wait_event(p_instance_ctrl, RM_FREERTOS_PLUS_FAT_WRITE_TIMEOUT_TICKS);
    }

    if (FSP_SUCCESS != err)
    {
        return (int32_t) (FF_ERR_IOMAN_DRIVER_FATAL_ERROR | FF_ERRFLAG);
    }

    lReturnCode = FF_ERR_NONE;

    return lReturnCode;
}

/*******************************************************************************************************************//**
 * Notifies task of event completion.
 *
 * @param[in] p_args     Pointer to block media callback structure.
 **********************************************************************************************************************/
void rm_freertos_plus_fat_memory_callback (rm_block_media_callback_args_t * p_args)
{
    /* Pass the event up to the application layer. */
    rm_freertos_plus_fat_instance_ctrl_t * p_instance_ctrl = (rm_freertos_plus_fat_instance_ctrl_t *) p_args->p_context;

    if ((RM_BLOCK_MEDIA_EVENT_MEDIA_REMOVED | RM_BLOCK_MEDIA_EVENT_MEDIA_INSERTED |
         RM_BLOCK_MEDIA_EVENT_MEDIA_SUSPEND | RM_BLOCK_MEDIA_EVENT_MEDIA_RESUME) & p_args->event)
    {
        if (NULL != p_instance_ctrl->p_cfg->p_callback)
        {
            /* Pass insertion and removal events up to the application. */
            rm_freertos_plus_fat_callback_args_t args;
            args.event     = (rm_freertos_plus_fat_event_t) p_args->event;
            args.p_context = p_instance_ctrl->p_cfg->p_context;
            p_instance_ctrl->p_cfg->p_callback(&args);
        }
    }

    if ((RM_BLOCK_MEDIA_EVENT_OPERATION_COMPLETE | RM_BLOCK_MEDIA_EVENT_POLL_STATUS |
         RM_BLOCK_MEDIA_EVENT_ERROR) & p_args->event)
    {
        p_instance_ctrl->last_event |= p_args->event;

#if 2 == BSP_CFG_RTOS

        /* Notify the task that the transmission is complete. */
        if (NULL != p_instance_ctrl->current_task)
        {
            BaseType_t xHigherPriorityTaskWoken = pdFALSE;
            vTaskNotifyGiveFromISR(p_instance_ctrl->current_task, &xHigherPriorityTaskWoken);

            /* There are no transmissions in progress, so no tasks to notify. */
            p_instance_ctrl->current_task = NULL;

            /* If xHigherPriorityTaskWoken is now set to pdTRUE then a context switch
             * should be performed to ensure the interrupt returns directly to the highest
             * priority task.  The macro used for this purpose is dependent on the port in
             * use and may be called portEND_SWITCHING_ISR(). */
            portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
        }

#else
        p_instance_ctrl->event_ready = true;
#endif
    }
}

/*******************************************************************************************************************//**
 * Waits for block media transfer complete event.
 *
 * @param[in] p_instance_ctrl          Pointer to instance control structure.
 * @param[in] timeout                  Timeout in RTOS ticks (unused if RTOS is not used)
 *
 * @retval     FSP_SUCCESS             Media device no longer busy.
 * @retval     FSP_ERR_TIMEOUT         Timeout occurred waiting for device.
 * @retval     FSP_ERR_INTERNAL        Error reported by lower layer driver callback.
 **********************************************************************************************************************/
static fsp_err_t rm_freertos_plus_fat_wait_event (rm_freertos_plus_fat_instance_ctrl_t * p_instance_ctrl,
                                                  uint32_t                               timeout)
{
#if (BSP_CFG_RTOS == 2)                // FreeRTOS

    /* Wait to be notified that the transmission is complete.  Note the first
     * parameter is pdTRUE, which has the effect of clearing the task's notification
     * value back to 0, making the notification value act like a binary (rather than
     * a counting) semaphore.  */
    uint32_t ulNotificationValue = ulTaskNotifyTake(pdTRUE, timeout);
    FSP_ERROR_RETURN(1U == ulNotificationValue, FSP_ERR_TIMEOUT);
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
#else
    while (!p_instance_ctrl->event_ready)
    {
        ;
    }
    FSP_PARAMETER_NOT_USED(timeout);
#endif

    FSP_ERROR_RETURN(0U == (RM_BLOCK_MEDIA_EVENT_ERROR & p_instance_ctrl->last_event), FSP_ERR_INTERNAL);

    if (RM_BLOCK_MEDIA_EVENT_POLL_STATUS & p_instance_ctrl->last_event)
    {
        return rm_freertos_plus_fat_wait_for_device(p_instance_ctrl);
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Waits for SD/MMC device to release the BUSY signal on DAT0.
 *
 * @param[in] p_instance_ctrl          Pointer to instance control structure.
 *
 * @retval     FSP_SUCCESS             SD/MMC device no longer BUSY.
 **********************************************************************************************************************/
static fsp_err_t rm_freertos_plus_fat_wait_for_device (rm_freertos_plus_fat_instance_ctrl_t * p_instance_ctrl)
{
    rm_block_media_instance_t const * const p_block_media = p_instance_ctrl->p_cfg->p_block_media;
    rm_block_media_status_t                 status;
    do
    {
        fsp_err_t err = p_block_media->p_api->statusGet(p_block_media->p_ctrl, &status);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
        if (!status.busy)
        {
            break;
        }

        if (NULL != p_instance_ctrl->p_cfg->p_busy_callback)
        {
            err = p_instance_ctrl->p_cfg->p_busy_callback(p_instance_ctrl->p_cfg->p_busy_context);
            FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
        }
    } while (true);

    return FSP_SUCCESS;
}
