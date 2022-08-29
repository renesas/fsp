/*
 * Copyright (c) 2018-2020 Arm Limited. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "Driver_Flash.h"
#include "r_flash_hp.h"

/**
 * \file Driver_Flash.c
 *
 * \brief CMSIS Flash driver for RA flash controller
 */

#ifndef ARG_UNUSED
 #define ARG_UNUSED(arg)    (void) arg
#endif

#ifndef ARG_NOT_USED
 #define ARG_NOT_USED            0U
#endif

/* Driver version */
#define ARM_FLASH_DRV_VERSION    ARM_DRIVER_VERSION_MAJOR_MINOR(1, 0)

const ARM_DRIVER_VERSION Flash_Driver_Version =
{
    ARM_FLASH_API_VERSION,             /* Defined in the CMSIS Flash Driver header file */
    ARM_FLASH_DRV_VERSION
};

/* Instance structure to use this module. */
extern const flash_instance_t * gp_tfm_flash_instance;

/**
 * Data types values
 */
typedef enum e_driver_flash_type
{
    CODE_FLASH,
    DATA_FLASH
} driver_flash_type_t;

/**
 * Event ready values for ARM_FLASH_CAPABILITIES::event_ready
 * \ref ARM_FLASH_CAPABILITIES
 */
enum
{
    EVENT_READY_NOT_AVAILABLE = 0u,
    EVENT_READY_AVAILABLE
};

/**
 * Data width values for ARM_FLASH_CAPABILITIES::data_width
 * \ref ARM_FLASH_CAPABILITIES
 */
enum
{
    DATA_WIDTH_8BIT = 0u,
    DATA_WIDTH_16BIT,
    DATA_WIDTH_32BIT
};

/**
 * Erase chip values for ARM_FLASH_CAPABILITIES::erase_chip
 * \ref ARM_FLASH_CAPABILITIES
 */
enum
{
    CHIP_ERASE_NOT_SUPPORTED = 0u,
    CHIP_ERASE_SUPPORTED
};

/** Driver Capabilities */
static const ARM_FLASH_CAPABILITIES DriverCapabilities =
{
    .event_ready = EVENT_READY_NOT_AVAILABLE,
    .data_width  = DATA_WIDTH_8BIT,
    .erase_chip  = CHIP_ERASE_SUPPORTED
};

/**
 * \brief Flash busy values flash status  \ref ARM_FLASH_STATUS
 */
enum
{
    DRIVER_STATUS_IDLE = 0u,
    DRIVER_STATUS_BUSY
};

/**
 * \brief Flash error values flash status  \ref ARM_FLASH_STATUS
 */
enum
{
    DRIVER_STATUS_NO_ERROR = 0u,
    DRIVER_STATUS_ERROR
};

/**
 * \brief Arm Flash device structure.
 */
typedef struct _FLASHx_Resources
{
    flash_instance_t const * dev;      /*!< FLASH memory device structure */
    ARM_FLASH_INFO         * data;     /*!< FLASH memory device data */
    ARM_FLASH_STATUS       * status;
} ARM_FLASHx_Resources;

static ARM_DRIVER_VERSION ARM_Flash_GetVersion (void)
{
    return Flash_Driver_Version;
}

static ARM_FLASH_CAPABILITIES ARM_Flash_GetCapabilities (void)
{
    return DriverCapabilities;
}

static int32_t ARM_Flashx_Initialize (ARM_FLASHx_Resources  * ARM_FLASHx_DEV,
                                      ARM_Flash_SignalEvent_t cb_event,
                                      driver_flash_type_t     flash_type)
{
    ARG_UNUSED(cb_event);
    uint32_t flash_size = 0U;
    uint32_t page_size  = 0U;

    ARM_FLASHx_DEV->dev = gp_tfm_flash_instance;

    ARM_FLASHx_DEV->status->error = DRIVER_STATUS_ERROR;
    ARM_FLASHx_DEV->status->busy  = DRIVER_STATUS_BUSY;

    R_FLASH_HP_Close(ARM_FLASHx_DEV->dev->p_ctrl);
    fsp_err_t err = R_FLASH_HP_Open(ARM_FLASHx_DEV->dev->p_ctrl, ARM_FLASHx_DEV->dev->p_cfg);
    if (FSP_SUCCESS != err)
    {
        ARM_FLASHx_DEV->status->busy = DRIVER_STATUS_IDLE;

        return ARM_DRIVER_ERROR;
    }

    flash_info_t info;
    if (FSP_SUCCESS != R_FLASH_HP_InfoGet(ARM_FLASHx_DEV->dev->p_ctrl, &info))
    {
        R_FLASH_HP_Close(ARM_FLASHx_DEV->dev->p_ctrl);
        ARM_FLASHx_DEV->status->busy = DRIVER_STATUS_IDLE;

        return ARM_DRIVER_ERROR;
    }

    if (flash_type == DATA_FLASH)
    {
        flash_size =
            (info.data_flash.p_block_array[info.data_flash.num_regions - 1U].block_section_end_addr -
             info.data_flash.p_block_array[0].block_section_st_addr + 1U);
        page_size = info.data_flash.p_block_array[info.data_flash.num_regions - 1U].block_size;
    }
    else
    {
        /* Assuming the entire flash has only 32k flash blocks, since the bootloader is using all of the 8K blocks for itself and won't be updated. */
        flash_size =
            (info.code_flash.p_block_array[info.code_flash.num_regions - 1U].block_section_end_addr -
             info.code_flash.p_block_array[0].block_section_st_addr + 1U);
        page_size = info.code_flash.p_block_array[info.code_flash.num_regions - 1U].block_size;
    }

    /* Validate hardcoded parameters of the flash */
    if ((ARM_FLASHx_DEV->data->page_size != page_size) ||
        (ARM_FLASHx_DEV->data->sector_size != page_size) ||
        (ARM_FLASHx_DEV->data->sector_count != (flash_size / page_size)))
    {
        R_FLASH_HP_Close(ARM_FLASHx_DEV->dev->p_ctrl);
        ARM_FLASHx_DEV->status->busy = DRIVER_STATUS_IDLE;

        return ARM_DRIVER_ERROR_PARAMETER;
    }

    ARM_FLASHx_DEV->status->error = DRIVER_STATUS_NO_ERROR;
    ARM_FLASHx_DEV->status->busy  = DRIVER_STATUS_IDLE;

    return ARM_DRIVER_OK;
}

static int32_t ARM_Flashx_Uninitialize (ARM_FLASHx_Resources * ARM_FLASHx_DEV)
{
    R_FLASH_HP_Close(ARM_FLASHx_DEV->dev->p_ctrl);

    return ARM_DRIVER_OK;
}

static int32_t ARM_Flashx_PowerControl (ARM_FLASHx_Resources * ARM_FLASHx_DEV, ARM_POWER_STATE state)
{
    ARG_UNUSED(ARM_FLASHx_DEV);

    switch (state)
    {
        case ARM_POWER_FULL:
        {

            /* Nothing to do */
            return ARM_DRIVER_OK;
        }

        case ARM_POWER_OFF:
        case ARM_POWER_LOW:
        {
            return ARM_DRIVER_ERROR_UNSUPPORTED;
        }

        default:

            return ARM_DRIVER_ERROR_PARAMETER;
    }
}

static int32_t ARM_Flashx_ReadData (ARM_FLASHx_Resources * ARM_FLASHx_DEV,
                                    uint32_t               addr,
                                    void                 * data,
                                    uint32_t               cnt,
                                    driver_flash_type_t    flash_type)
{
    fsp_err_t      err                = FSP_SUCCESS;
    flash_result_t blank_check_result = FLASH_RESULT_BLANK;

    ARM_FLASHx_DEV->status->error = DRIVER_STATUS_ERROR;
    ARM_FLASHx_DEV->status->busy  = DRIVER_STATUS_BUSY;

    flash_info_t info;
    if (FSP_SUCCESS != R_FLASH_HP_InfoGet(ARM_FLASHx_DEV->dev->p_ctrl, &info))
    {
        R_FLASH_HP_Close(ARM_FLASHx_DEV->dev->p_ctrl);
        ARM_FLASHx_DEV->status->busy = DRIVER_STATUS_IDLE;

        return ARM_DRIVER_ERROR;
    }

    if (flash_type == CODE_FLASH)
    {
        /* Check if range is valid */
        if ((addr + cnt) >
            ((info.code_flash.p_block_array[0].block_section_st_addr) +
             (ARM_FLASHx_DEV->data->sector_size * ARM_FLASHx_DEV->data->sector_count)))
        {
            ARM_FLASHx_DEV->status->busy = DRIVER_STATUS_IDLE;

            return ARM_DRIVER_ERROR_PARAMETER;
        }

        blank_check_result = FLASH_RESULT_NOT_BLANK;
    }
    else
    {
        /* Check if range is valid */
        if ((addr + cnt) >
            ((info.data_flash.p_block_array[0].block_section_st_addr) +
             (ARM_FLASHx_DEV->data->sector_size * ARM_FLASHx_DEV->data->sector_count)))
        {
            ARM_FLASHx_DEV->status->busy = DRIVER_STATUS_IDLE;

            return ARM_DRIVER_ERROR_PARAMETER;
        }

        err = R_FLASH_HP_BlankCheck(ARM_FLASHx_DEV->dev->p_ctrl, addr, cnt, &blank_check_result);
        if (err != FSP_SUCCESS)
        {
            if ((err == FSP_ERR_INVALID_ADDRESS) ||
                (err == FSP_ERR_INVALID_SIZE))
            {
                /* The native driver checks aligment and range */
                ARM_FLASHx_DEV->status->error = DRIVER_STATUS_NO_ERROR;
                ARM_FLASHx_DEV->status->busy  = DRIVER_STATUS_IDLE;

                return ARM_DRIVER_OK;
            }

            ARM_FLASHx_DEV->status->busy = DRIVER_STATUS_IDLE;

            return ARM_DRIVER_ERROR;
        }
    }

    /* Validate the blank check result */
    if (FLASH_RESULT_NOT_BLANK == blank_check_result)
    {
        memcpy(data, (const void *) addr, cnt);
    }
    else
    {
        memset(data, 0xFF, cnt);
    }

    ARM_FLASHx_DEV->status->error = DRIVER_STATUS_NO_ERROR;
    ARM_FLASHx_DEV->status->busy  = DRIVER_STATUS_IDLE;

    return ARM_DRIVER_OK;
}

static int32_t ARM_Flashx_ProgramData (ARM_FLASHx_Resources * ARM_FLASHx_DEV,
                                       uint32_t               addr,
                                       const void           * data,
                                       uint32_t               cnt)
{
    fsp_err_t err = FSP_SUCCESS;

    ARM_FLASHx_DEV->status->error = DRIVER_STATUS_ERROR;
    ARM_FLASHx_DEV->status->busy  = DRIVER_STATUS_BUSY;

    __disable_irq();
    err = R_FLASH_HP_Write(ARM_FLASHx_DEV->dev->p_ctrl, (uint32_t) data, addr, cnt);
    __enable_irq();

    if (err != FSP_SUCCESS)
    {
        if ((err == FSP_ERR_INVALID_ADDRESS) ||
            (err == FSP_ERR_INVALID_SIZE))
        {
            ARM_FLASHx_DEV->status->busy = DRIVER_STATUS_IDLE;

            /* The native driver checks aligment and range */
            return ARM_DRIVER_ERROR_PARAMETER;
        }

        ARM_FLASHx_DEV->status->busy = DRIVER_STATUS_IDLE;

        return ARM_DRIVER_ERROR;
    }

    ARM_FLASHx_DEV->status->error = DRIVER_STATUS_NO_ERROR;
    ARM_FLASHx_DEV->status->busy  = DRIVER_STATUS_IDLE;

    return ARM_DRIVER_OK;
}

static int32_t ARM_Flashx_EraseSector (ARM_FLASHx_Resources * ARM_FLASHx_DEV, uint32_t addr)
{
    fsp_err_t err = FSP_SUCCESS;

    ARM_FLASHx_DEV->status->error = DRIVER_STATUS_ERROR;
    ARM_FLASHx_DEV->status->busy  = DRIVER_STATUS_BUSY;

    /* The erase function checks whether the address is within the valid flash
     * address range, and the HW will align the address to page boundary if
     * it is not aligned.
     */
    __disable_irq();
    err = R_FLASH_HP_Erase(ARM_FLASHx_DEV->dev->p_ctrl, addr, 1U);
    __enable_irq();

    if (err != FSP_SUCCESS)
    {
        if (err == FSP_ERR_INVALID_ADDRESS)
        {
            ARM_FLASHx_DEV->status->busy = DRIVER_STATUS_IDLE;

            return ARM_DRIVER_ERROR_PARAMETER;
        }

        ARM_FLASHx_DEV->status->busy = DRIVER_STATUS_IDLE;

        return ARM_DRIVER_ERROR;
    }

    ARM_FLASHx_DEV->status->error = DRIVER_STATUS_NO_ERROR;
    ARM_FLASHx_DEV->status->busy  = DRIVER_STATUS_IDLE;

    return ARM_DRIVER_OK;
}

static int32_t ARM_Flashx_EraseChip (ARM_FLASHx_Resources * ARM_FLASHx_DEV, driver_flash_type_t flash_type)
{
    fsp_err_t err        = FSP_SUCCESS;
    uint32_t  start_addr = 0U;

    ARM_FLASHx_DEV->status->error = DRIVER_STATUS_ERROR;
    ARM_FLASHx_DEV->status->busy  = DRIVER_STATUS_BUSY;

    /* The erase function checks whether the address is aligned with
     * the sector or subsector and checks the Flash memory boundaries.
     */

    flash_info_t info;
    err = R_FLASH_HP_InfoGet(ARM_FLASHx_DEV->dev->p_ctrl, &info);

    if (err != FSP_SUCCESS)
    {
        ARM_FLASHx_DEV->status->busy = DRIVER_STATUS_IDLE;

        return ARM_DRIVER_ERROR;
    }

    if (flash_type == DATA_FLASH)
    {
        start_addr = info.data_flash.p_block_array[0].block_section_st_addr;
    }
    else
    {
        start_addr = info.code_flash.p_block_array[0].block_section_st_addr;
    }

    __disable_irq();
    err = R_FLASH_HP_Erase(ARM_FLASHx_DEV->dev->p_ctrl, start_addr, ARM_FLASHx_DEV->data->sector_count);
    __enable_irq();

    if (err != FSP_SUCCESS)
    {
        ARM_FLASHx_DEV->status->busy = DRIVER_STATUS_IDLE;

        return ARM_DRIVER_ERROR;
    }

    ARM_FLASHx_DEV->status->error = DRIVER_STATUS_NO_ERROR;
    ARM_FLASHx_DEV->status->busy  = DRIVER_STATUS_IDLE;

    return ARM_DRIVER_OK;
}

static ARM_FLASH_STATUS ARM_Flashx_GetStatus (ARM_FLASHx_Resources * ARM_FLASHx_DEV)
{
    return *(ARM_FLASHx_DEV->status);
}

static ARM_FLASH_INFO * ARM_Flashx_GetInfo (ARM_FLASHx_Resources * ARM_FLASHx_DEV)
{
    return ARM_FLASHx_DEV->data;
}

static ARM_FLASH_INFO ARM_DFLASH_DEV_DATA =
{
    .sector_info  = NULL,                                                             /* Uniform sector layout */
    .sector_count = (BSP_DATA_FLASH_SIZE_BYTES / BSP_FEATURE_FLASH_HP_DF_BLOCK_SIZE), /* 8KB (data flash size) / 64B */
    .sector_size  = BSP_FEATURE_FLASH_HP_DF_BLOCK_SIZE,                               /* 64B - as there are no sectors the page size
                                                                                       *        size is used here
                                                                                       */
    .page_size    = BSP_FEATURE_FLASH_HP_DF_BLOCK_SIZE,                               /* 64B */
    .program_unit = BSP_FEATURE_FLASH_HP_DF_WRITE_SIZE,                               /* Minimum write size in bytes */
    .erased_value = 0xFF
};

static ARM_FLASH_STATUS shared_status =
{
    .busy     = DRIVER_STATUS_IDLE,
    .error    = DRIVER_STATUS_NO_ERROR,
    .reserved = 0,
};

static ARM_FLASHx_Resources ARM_DFLASH_DEV =
{
    .data   = &(ARM_DFLASH_DEV_DATA),
    .status = &shared_status,          /* Shared between DFlash and Cflash */
};

static ARM_DRIVER_VERSION ARM_DFlash_GetVersion (void)
{
    return ARM_Flash_GetVersion();
}

static ARM_FLASH_CAPABILITIES ARM_DFlash_GetCapabilities (void)
{
    return ARM_Flash_GetCapabilities();
}

static int32_t ARM_DFlash_Initialize (ARM_Flash_SignalEvent_t cb_event)
{
    return ARM_Flashx_Initialize(&ARM_DFLASH_DEV, cb_event, DATA_FLASH);
}

static int32_t ARM_DFlash_Uninitialize (void)
{
    return ARM_Flashx_Uninitialize(&ARM_DFLASH_DEV);
}

static int32_t ARM_DFlash_PowerControl (ARM_POWER_STATE state)
{
    return ARM_Flashx_PowerControl(&ARM_DFLASH_DEV, state);
}

static int32_t ARM_DFlash_ReadData (uint32_t addr, void * data, uint32_t cnt)
{
    return ARM_Flashx_ReadData(&ARM_DFLASH_DEV, addr, data, cnt, DATA_FLASH);
}

static int32_t ARM_DFlash_ProgramData (uint32_t addr, const void * data, uint32_t cnt)
{
    return ARM_Flashx_ProgramData(&ARM_DFLASH_DEV, addr, data, cnt);
}

static int32_t ARM_DFlash_EraseSector (uint32_t addr)
{
    return ARM_Flashx_EraseSector(&ARM_DFLASH_DEV, addr);
}

static int32_t ARM_DFlash_EraseChip (void)
{
    return ARM_Flashx_EraseChip(&ARM_DFLASH_DEV, DATA_FLASH);
}

static ARM_FLASH_STATUS ARM_DFlash_GetStatus (void)
{
    return ARM_Flashx_GetStatus(&ARM_DFLASH_DEV);
}

static ARM_FLASH_INFO * ARM_DFlash_GetInfo (void)
{
    return ARM_Flashx_GetInfo(&ARM_DFLASH_DEV);
}

ARM_DRIVER_FLASH Driver_DFLASH =
{
    ARM_DFlash_GetVersion,
    ARM_DFlash_GetCapabilities,
    ARM_DFlash_Initialize,
    ARM_DFlash_Uninitialize,
    ARM_DFlash_PowerControl,
    ARM_DFlash_ReadData,
    ARM_DFlash_ProgramData,
    ARM_DFlash_EraseSector,
    ARM_DFlash_EraseChip,
    ARM_DFlash_GetStatus,
    ARM_DFlash_GetInfo
};

static ARM_FLASH_INFO ARM_CFLASH_DEV_DATA =
{
    .sector_info  = NULL,                                                    /* Uniform sector layout */
    .sector_count =
        ((BSP_ROM_SIZE_BYTES) / BSP_FEATURE_FLASH_HP_CF_REGION1_BLOCK_SIZE), /* (flash size of 32k blocks only) / 32kB */
    .sector_size  = BSP_FEATURE_FLASH_HP_CF_REGION1_BLOCK_SIZE,              /* 32kB - as there are no sectors the page size
                                                                              *        size is used here
                                                                              */
    .page_size    = BSP_FEATURE_FLASH_HP_CF_REGION1_BLOCK_SIZE,              /* 32kB */
    .program_unit = BSP_FEATURE_FLASH_HP_CF_WRITE_SIZE,                      /* Minimum write size in bytes */
    .erased_value = 0xFF
};

static ARM_FLASHx_Resources ARM_CFLASH_DEV =
{
    .data   = &ARM_CFLASH_DEV_DATA,
    .status = &shared_status,          /* Shared between DFlash and Cflash */
};

static ARM_DRIVER_VERSION ARM_CFlash_GetVersion (void)
{
    return ARM_Flash_GetVersion();
}

static ARM_FLASH_CAPABILITIES ARM_CFlash_GetCapabilities (void)
{
    return ARM_Flash_GetCapabilities();
}

static int32_t ARM_CFlash_Initialize (ARM_Flash_SignalEvent_t cb_event)
{
    return ARM_Flashx_Initialize(&ARM_CFLASH_DEV, cb_event, CODE_FLASH);
}

static int32_t ARM_CFlash_Uninitialize (void)
{
    return ARM_Flashx_Uninitialize(&ARM_CFLASH_DEV);
}

static int32_t ARM_CFlash_PowerControl (ARM_POWER_STATE state)
{
    return ARM_Flashx_PowerControl(&ARM_CFLASH_DEV, state);
}

static int32_t ARM_CFlash_ReadData (uint32_t addr, void * data, uint32_t cnt)
{
    return ARM_Flashx_ReadData(&ARM_CFLASH_DEV, addr, data, cnt, CODE_FLASH);
}

static int32_t ARM_CFlash_ProgramData (uint32_t addr, const void * data, uint32_t cnt)
{
    return ARM_Flashx_ProgramData(&ARM_CFLASH_DEV, addr, data, cnt);
}

static int32_t ARM_CFlash_EraseSector (uint32_t addr)
{
    return ARM_Flashx_EraseSector(&ARM_CFLASH_DEV, addr);
}

static int32_t ARM_CFlash_EraseChip (void)
{
    return ARM_Flashx_EraseChip(&ARM_CFLASH_DEV, CODE_FLASH);
}

static ARM_FLASH_STATUS ARM_CFlash_GetStatus (void)
{
    return ARM_Flashx_GetStatus(&ARM_CFLASH_DEV);
}

static ARM_FLASH_INFO * ARM_CFlash_GetInfo (void)
{
    return ARM_Flashx_GetInfo(&ARM_CFLASH_DEV);
}

ARM_DRIVER_FLASH Driver_CFLASH =
{
    ARM_CFlash_GetVersion,
    ARM_CFlash_GetCapabilities,
    ARM_CFlash_Initialize,
    ARM_CFlash_Uninitialize,
    ARM_CFlash_PowerControl,
    ARM_CFlash_ReadData,
    ARM_CFlash_ProgramData,
    ARM_CFlash_EraseSector,
    ARM_CFlash_EraseChip,
    ARM_CFlash_GetStatus,
    ARM_CFlash_GetInfo
};
