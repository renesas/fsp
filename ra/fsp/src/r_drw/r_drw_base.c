/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/**********************************************************************************************************************
 * File Name    : r_drw_base.c
 * Description  : This file defines the D/AVE D1 low-level driver basic functions.
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include <stdlib.h>

#include "bsp_api.h"

#include "r_drw_base.h"
#include "r_drw_cfg.h"

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define DRW_PRV_D2_DLISTSTART    50    /* display list start register index */

/***********************************************************************************************************************
 * Extern global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/* D1 device handle to be passed up to D2 layer */
static d1_device_flex device_d2d = {0};

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @internal
 * @addtogroup DRW_PRV Internal DRW Documentation
 * @ingroup RENESAS_INTERNAL
 * @{
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * This function initializes the D1 device handle, supplies module clock to D/AVE 2D hardware and enables the D/AVE 2D
 * interrupt. It is called by the D/AVE 2D driver function d2_inithw() to initialize the D/AVE 2D hardware.
 *
 * @param[in] flags     Reserved. Not used in this function.
 * @retval    Non-NULL  The function returns the pointer to a d1_device object if the D1 device handle was successfully
 *                      initialized.
 * @retval    NULL      The function returns NULL if the interrupt could not be successfully initialized.
 **********************************************************************************************************************/
d1_device * d1_opendevice (d1_long_t flags)
{
    d1_device_flex * handle;

    FSP_PARAMETER_NOT_USED(flags);

    /* Get new device handle. */
    handle = &device_d2d;

    /* Initialize device data. */
    handle->dlist_indirect_enable = DRW_CFG_USE_DLIST_INDIRECT;

    /* Supply clock to the D/AVE 2D hardware. */
    R_BSP_MODULE_START(FSP_IP_DRW, 0);

    /* Enable the D/AVE 2D interrupt. */
    if (d1_initirq_intern(handle) == 0)
    {
        /* If the IRQ number is invalid return NULL. */
        handle = NULL;

        /* Stop clock supply to the D/AVE 2D hardware. */
        R_BSP_MODULE_STOP(FSP_IP_DRW, 0);
    }

    /* Returns the pointer to the d1_device object. */
    return (d1_device *) handle;
}

/*******************************************************************************************************************//**
 * This function is called by the D/AVE 2D driver function d2_deinithw to de-initialize the D/AVE 2D hardware. Disables
 * the D/AVE 2D interrupt and stop the module clock supply.
 *
 * @param[in] handle    Pointer to the d1_device object.
 * @retval    1         The function returns 1.
 **********************************************************************************************************************/
d1_int_t d1_closedevice (d1_device * handle)
{
    d1_device_flex * dev = (d1_device_flex *) handle;

    /* Disable the D/AVE 2D interrupt. */
    d1_shutdownirq_intern(dev);

    /* Stop clock supply to the D/AVE 2D hardware. */
    R_BSP_MODULE_STOP(FSP_IP_DRW, 0);

    return 1;
}

/*******************************************************************************************************************//**
 * This function is used to write data to a D/AVE 2D hardware register.
 *
 * @param[in] handle    Pointer to a device handle.
 * @param[in] deviceid  D1_DAVE2D (Rendering core) or D1_DLISTINDIRECT (Lists of dlist support). Others are ignored.
 * @param[in] index     Register index (word offset from the D/AVE 2D base address).
 * @param[in] value     32-bit value to write.
 **********************************************************************************************************************/
void d1_setregister (d1_device * handle, d1_int_t deviceid, d1_int_t index, d1_long_t value)
{
    d1_device_flex * handle_flex = (d1_device_flex *) handle;

    switch (deviceid)
    {
        case D1_DAVE2D:
        {
#if DRW_CFG_USE_DLIST_INDIRECT

            /* If indirect mode is configured start processing the display list list in indirect mode */
            if ((DRW_PRV_D2_DLISTSTART == index) && (handle_flex->dlist_indirect_enable))
            {
                /* Set DLISTSTART to the address of the first display list and set pp_dlist_indirect_start to the next dlist ptr */
                uint32_t * p_dlist = (uint32_t *) value;
                R_DRW->DLISTSTART = *p_dlist;
                handle_flex->pp_dlist_indirect_start = p_dlist + 1U;
            }
            else
#endif
            {
                /* Write data to specified D/AVE 2D register. */
                ((uint32_t *) R_DRW)[index] = (uint32_t) value;
            }

            break;
        }

        case D1_DLISTINDIRECT:
        {
#if DRW_CFG_USE_DLIST_INDIRECT
            handle_flex->dlist_indirect_enable = value;
#else
            handle_flex->dlist_indirect_enable = 0;
#endif
            break;
        }

        default:
        {
            /* Not supported or Unknown device, do nothing. */
            break;
        }
    }
}

/*******************************************************************************************************************//**
 * This function is used to read data from a hardware register.
 * Reading a register from an invalid or unsupported device ID will always return 0.
 *
 * @param[in] handle    Pointer to a device handle.
 * @param[in] deviceid  D1_DAVE2D (Rendering core) or D1_DLISTINDIRECT (Lists of dlist support). Others are ignored.
 * @param[in] index     Register index (starts with 0).
 * @retval    Value     The function returns the 32-bit value of the register.
 **********************************************************************************************************************/
d1_long_t d1_getregister (d1_device * handle, d1_int_t deviceid, d1_int_t index)
{
#if DRW_CFG_USE_DLIST_INDIRECT
    d1_device_flex * handle_flex = (d1_device_flex *) handle;
#else
    FSP_PARAMETER_NOT_USED(handle);
#endif

    int32_t ret = 0;

    if (D1_DAVE2D == deviceid)
    {
        ret = (int32_t) (((uint32_t *) R_DRW)[index]);
    }

#if DRW_CFG_USE_DLIST_INDIRECT
    else if (D1_DLISTINDIRECT == deviceid)
    {
        ret = handle_flex->dlist_indirect_enable;
    }
    else
    {
    }
#endif

    return (d1_long_t) ret;
}

/*******************************************************************************************************************//**
 * Check if the specified device ID is valid for the D/AVE 2D implementation for Flex.
 * Use this function to verify that a specific hardware interface is available on the current host system.
 *
 * @param[in] handle    Pointer to a device handle.
 * @param[in] deviceid  D1_DAVE2D (Rendering core) or D1_DLISTINDIRECT (Lists of dlist support). Others are ignored.
 * @retval    0         The function returns 0 if specified device ID not supported.
 * @retval    1         The function returns 1 if specified device ID supported.
 **********************************************************************************************************************/
d1_int_t d1_devicesupported (d1_device * handle, d1_int_t deviceid)
{
    d1_int_t ret = 0;

    FSP_PARAMETER_NOT_USED(handle);

    if (deviceid == D1_DAVE2D)
    {
        ret = 1;
    }

#if DRW_CFG_USE_DLIST_INDIRECT
    else if (D1_DLISTINDIRECT == deviceid)
    {
        ret = 1;
    }
    else
    {
    }
#endif

    return ret;
}

/*******************************************************************************************************************//**
 * @}
 **********************************************************************************************************************/
