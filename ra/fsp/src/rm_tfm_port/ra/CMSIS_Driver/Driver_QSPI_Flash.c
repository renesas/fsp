/*
 * Copyright (c) 2013-2020 Arm Limited. All rights reserved.
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

#include <stdbool.h>
#include "flash_layout.h"


#ifndef ARG_UNUSED
#define ARG_UNUSED(arg)  ((void)arg)
#endif

/* Driver version */
#define ARM_FLASH_DRV_VERSION   ARM_DRIVER_VERSION_MAJOR_MINOR(1, 0)

static const ARM_DRIVER_VERSION DriverVersion = {
    ARM_FLASH_API_VERSION,  /* Defined in the CMSIS Flash Driver header file */
    ARM_FLASH_DRV_VERSION
};

/**
 * \brief Flash driver capability macro definitions \ref ARM_FLASH_CAPABILITIES
 */
/* Flash Ready event generation capability values */
#define EVENT_READY_NOT_AVAILABLE   (0u)
#define EVENT_READY_AVAILABLE       (1u)
/* Data access size values */
#define DATA_WIDTH_8BIT             (0u)
#define DATA_WIDTH_16BIT            (1u)
#define DATA_WIDTH_32BIT            (2u)
/* Chip erase capability values */
#define CHIP_ERASE_NOT_SUPPORTED    (0u)
#define CHIP_ERASE_SUPPORTED        (1u)

/* Driver Capabilities */
static const ARM_FLASH_CAPABILITIES DriverCapabilities = {
    EVENT_READY_NOT_AVAILABLE,
    DATA_WIDTH_32BIT,
    CHIP_ERASE_SUPPORTED,
    0
};

/**
 * \brief Flash status macro definitions \ref ARM_FLASH_STATUS
 */
/* Busy status values of the Flash driver */
#define DRIVER_STATUS_IDLE      (0u)
#define DRIVER_STATUS_BUSY      (1u)
/* Error status values of the Flash driver */
#define DRIVER_STATUS_NO_ERROR  (0u)
#define DRIVER_STATUS_ERROR     (1u)

/**
 * \brief Arm Flash device structure.
 */
struct arm_flash_dev_t {
    ARM_FLASH_INFO *data;       /*!< FLASH memory device data */
};

static ARM_FLASH_INFO ARM_FLASH0_DEV_DATA = {
    .sector_info    = NULL,     /* Uniform sector layout */
    .sector_count   = QSPI_FLASH_TOTAL_SIZE / 0x1000,
    .sector_size    = 0x1000,
    .page_size      = 0x100000,
    .program_unit   = 1u,       /* Minimum write size in bytes */
    .erased_value   = 0xFF
};

static struct arm_flash_dev_t ARM_FLASH0_DEV = {
    .data   = &(ARM_FLASH0_DEV_DATA)
};

/* Flash Status */
static ARM_FLASH_STATUS ARM_FLASH0_STATUS = {0, 0, 0};

static ARM_DRIVER_VERSION ARM_Flash_GetVersion(void)
{
    return DriverVersion;
}

static ARM_FLASH_CAPABILITIES ARM_Flash_GetCapabilities(void)
{
    return DriverCapabilities;
}

static int32_t ARM_Flash_Initialize(ARM_Flash_SignalEvent_t cb_event)
{
    ARG_UNUSED(cb_event);
    return ARM_DRIVER_ERROR_UNSUPPORTED;
}

static int32_t ARM_Flash_Uninitialize(void)
{
    return ARM_DRIVER_ERROR_UNSUPPORTED;
}

static int32_t ARM_Flash_PowerControl(ARM_POWER_STATE state)
{
    switch(state) {
    case ARM_POWER_FULL:
        /* Nothing to be done */
        return ARM_DRIVER_OK;
    case ARM_POWER_OFF:
    case ARM_POWER_LOW:
        return ARM_DRIVER_ERROR_UNSUPPORTED;
    default:
        return ARM_DRIVER_ERROR_PARAMETER;
    }
}

static int32_t ARM_Flash_ReadData(uint32_t addr, void *data, uint32_t cnt)
{
    ARG_UNUSED(addr);
    ARG_UNUSED(data);
    ARG_UNUSED(cnt);
    return ARM_DRIVER_ERROR_UNSUPPORTED;
}

static int32_t ARM_Flash_ProgramData(uint32_t addr,
                                     const void *data, uint32_t cnt)
{
    ARG_UNUSED(addr);
    ARG_UNUSED(data);
    ARG_UNUSED(cnt);
    return ARM_DRIVER_ERROR_UNSUPPORTED;
}

static int32_t ARM_Flash_EraseSector(uint32_t addr)
{
    ARG_UNUSED(addr);
    return ARM_DRIVER_ERROR_UNSUPPORTED;
}

static int32_t ARM_Flash_EraseChip(void)
{
    return ARM_DRIVER_ERROR_UNSUPPORTED;
}

static ARM_FLASH_STATUS ARM_Flash_GetStatus(void)
{
    return ARM_FLASH0_STATUS;
}

static ARM_FLASH_INFO * ARM_Flash_GetInfo(void)
{
    return ARM_FLASH0_DEV.data;
}

ARM_DRIVER_FLASH Driver_QSPI_FLASH0 = {
    ARM_Flash_GetVersion,
    ARM_Flash_GetCapabilities,
    ARM_Flash_Initialize,
    ARM_Flash_Uninitialize,
    ARM_Flash_PowerControl,
    ARM_Flash_ReadData,
    ARM_Flash_ProgramData,
    ARM_Flash_EraseSector,
    ARM_Flash_EraseChip,
    ARM_Flash_GetStatus,
    ARM_Flash_GetInfo
};

