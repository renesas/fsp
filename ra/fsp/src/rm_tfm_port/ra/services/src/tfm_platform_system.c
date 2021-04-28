/*
 * Copyright (c) 2018-2020, Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include <stdbool.h>
#include "tfm_platform_system.h"
#include "platform_description.h"
#include "target_cfg.h"
#include "psa/client.h"
#include "tfm_ioctl_api.h"
#include "Driver_Flash.h"
#include "region_defs.h"

/**
 * \brief Flash busy values flash status  \ref ARM_FLASH_STATUS
 */
enum
{
    DRIVER_STATUS_IDLE = 0u,
    DRIVER_STATUS_BUSY
};

extern ARM_DRIVER_FLASH Driver_CFLASH;

void tfm_platform_hal_system_reset (void)
{
    __disable_irq();

    NVIC->ICPR[0] = UINT32_MAX;        /* Clear all pending interrupts */
    NVIC->ICPR[1] = UINT32_MAX;        /* Clear all pending interrupts */
    NVIC->ICPR[2] = UINT32_MAX;        /* Clear all pending interrupts */
    NVIC->ICPR[3] = UINT32_MAX;        /* Clear all pending interrupts */
    NVIC->ICPR[4] = UINT32_MAX;        /* Clear all pending interrupts */
    NVIC->ICPR[5] = UINT32_MAX;        /* Clear all pending interrupts */
    NVIC->ICPR[6] = UINT32_MAX;        /* Clear all pending interrupts */
    NVIC->ICPR[7] = UINT32_MAX;        /* Clear all pending interrupts */

    NVIC_SystemReset();
}

static enum tfm_platform_err_t tfm_platform_hal_flash_service_write (struct tfm_flash_service_args_t * args,
                                                                     struct tfm_flash_service_out_t  * out)
{
    out->u.result = 0;
    uint32_t   flash_address          = args->u.flash_write.flash_addr;
    uint32_t   count                  = args->u.flash_write.count;
    uint32_t * source_address         = (uint32_t *) args->u.flash_write.src_addr;
    uint32_t * checked_source_address = cmse_check_pointed_object(source_address, CMSE_AU_NONSECURE);

    /* The flash service limits writes to only the non-secure area or to the secure image update area.*/
    if ((flash_address < (RM_TFM_PORT_SECURE_UPDATE_ADDRESS + (2 * RM_TFM_PORT_SECURE_IMAGE_SIZE) - 1)))
    {
        /* If the write is to the secure area then verify that the write address and range are within to the secure image update area. */
        if ((flash_address < RM_TFM_PORT_SECURE_UPDATE_ADDRESS) ||
            ((flash_address + count) > (RM_TFM_PORT_SECURE_UPDATE_ADDRESS + RM_TFM_PORT_SECURE_IMAGE_SIZE - 1)) ||
            (checked_source_address != source_address))
        {
            return TFM_PLATFORM_ERR_INVALID_PARAM;
        }
    }

    out->u.result = Driver_CFLASH.ProgramData(flash_address, source_address, count);

    return TFM_PLATFORM_ERR_SUCCESS;
}

static enum tfm_platform_err_t tfm_platform_hal_flash_service_erase (struct tfm_flash_service_args_t * args,
                                                                     struct tfm_flash_service_out_t  * out)
{
    ARM_FLASH_INFO * info;
    info = Driver_CFLASH.GetInfo();
    uint32_t flash_address = args->u.flash_erase.addr;
    uint32_t sector_size   = info->sector_size;
    flash_address = flash_address & ~(sector_size - 1);
    uint32_t size = ((args->u.flash_erase.count) * sector_size);

    /* The flash service limits erase to only the non-secure area or to the secure image update area.*/
    if ((flash_address < (RM_TFM_PORT_SECURE_UPDATE_ADDRESS + (2 * RM_TFM_PORT_SECURE_IMAGE_SIZE) - 1)))
    {
        /* If the erase is to the secure area then verify that the erase address and range are within to the secure image update area. */
        if ((flash_address < RM_TFM_PORT_SECURE_UPDATE_ADDRESS) ||
            ((flash_address + size) > (RM_TFM_PORT_SECURE_UPDATE_ADDRESS + RM_TFM_PORT_SECURE_IMAGE_SIZE - 1)))
        {
            return TFM_PLATFORM_ERR_INVALID_PARAM;
        }
    }

    for (uint32_t i = 0; i < args->u.flash_erase.count; i++)
    {
        out->u.result |= Driver_CFLASH.EraseSector(flash_address);
        flash_address += sector_size;
    }

    return TFM_PLATFORM_ERR_SUCCESS;
}

static enum tfm_platform_err_t tfm_platform_hal_flash_service (const psa_invec * in_vec, const psa_outvec * out_vec)
{
    struct tfm_flash_service_args_t * args;
    struct tfm_flash_service_out_t  * out;

    if ((in_vec->len != sizeof(struct tfm_flash_service_args_t)) ||
        (out_vec->len != sizeof(struct tfm_flash_service_out_t)))
    {
        return TFM_PLATFORM_ERR_INVALID_PARAM;
    }

    ARM_FLASH_STATUS status = Driver_CFLASH.GetStatus();
    if (status.busy != DRIVER_STATUS_IDLE)
    {
        return TFM_PLATFORM_ERR_SYSTEM_ERROR;
    }

    args = (struct tfm_flash_service_args_t *) in_vec->base;
    out  = (struct tfm_flash_service_out_t *) out_vec->base;
    switch (args->type)
    {
        case TFM_FLASH_SERVICE_TYPE_INIT:
        {
            out->u.result = Driver_CFLASH.Initialize(NULL);
            break;
        }

        case TFM_FLASH_SERVICE_TYPE_ERASE:
        {
            return tfm_platform_hal_flash_service_erase(args, out);
            break;
        }

        case TFM_FLASH_SERVICE_TYPE_WRITE:
        {
            return tfm_platform_hal_flash_service_write(args, out);
            break;
        }

        default:
        {
            out->u.result = 1;
            break;
        }
    }

    return TFM_PLATFORM_ERR_SUCCESS;
}

enum tfm_platform_err_t tfm_platform_hal_ioctl (tfm_platform_ioctl_req_t request,
                                                psa_invec              * in_vec,
                                                psa_outvec             * out_vec)
{
    switch (request)
    {
        case TFM_PLATFORM_IOCTL_PIN_SERVICE:
        {
            return TFM_PLATFORM_ERR_NOT_SUPPORTED;
        }

        case TFM_PLATFORM_IOCTL_GPIO_SERVICE:
        {
            return TFM_PLATFORM_ERR_NOT_SUPPORTED;
        }

        case TFM_PLATFORM_IOCTL_FLASH_SERVICE:
        {
            return tfm_platform_hal_flash_service(in_vec, out_vec);
        }

        default:

            return TFM_PLATFORM_ERR_NOT_SUPPORTED;
    }
}
