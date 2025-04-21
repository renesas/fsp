/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*
 * ####################################################################################################################
 * INCLUDES
 * ####################################################################################################################
 */

#include "ptxPLAT_GPIO.h"
#include "r_ioport.h"
#include "r_icu.h"
#include <string.h>

/*
 * ####################################################################################################################
 * DEFINES / TYPES
 * ####################################################################################################################
 */

extern void ptxPLAT_GPIO_IsrCallback(external_irq_callback_args_t * p_args);

/*
 * Instance of GPIO-IRQ context.
 */
ptxPlatGpio_t gpio_irq_ctx;

#ifdef SEN_PIN_CONNECTION_AVAILABLE

/*
 * Instance of PTX100x SEN-pin context.
 */
ptxPlatGpio_t sen_pin_context;
#endif

/*
 * ####################################################################################################################
 * API FUNCTIONS
 * ####################################################################################################################
 */
ptxStatus_t ptxPLAT_GPIO_Open (ioport_instance_t       * gpio_instance,
                               external_irq_instance_t * irq_instance,
                               const bsp_io_port_pin_t   interrupt_pin)
{
    ptxStatus_t status = ptxStatus_Success;

    if ((NULL != irq_instance) && (NULL != gpio_instance))
    {
        /* Initialization of the GPIO Context */
        memset(&gpio_irq_ctx, 0, sizeof(ptxPlatGpio_t));

        gpio_irq_ctx.PortInstance = gpio_instance;

        gpio_irq_ctx.PortPin = interrupt_pin;

        /* GPIO used for IRQ purpose is the following one. */
        gpio_irq_ctx.ExtIrqInstance = irq_instance;
    }
    else
    {
        status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InvalidParameter);
    }

    return status;
}

ptxStatus_t ptxPLAT_GPIO_GetInitialized (ptxPlatGpio_t ** gpio, ptxPlatGpio_Config_t * gpioPars)
{
    ptxStatus_t status = ptxStatus_Success;

    if ((NULL != gpio) && (NULL != gpioPars))
    {
        fsp_err_t r_status = FSP_SUCCESS;

        switch (gpioPars->Type)
        {
            case GPIO_Type_PTXExtIRQPin:
            {
                r_status =
                    gpio_irq_ctx.ExtIrqInstance->p_api->open(gpio_irq_ctx.ExtIrqInstance->p_ctrl,
                                                             gpio_irq_ctx.ExtIrqInstance->p_cfg);

                if (FSP_SUCCESS == r_status)
                {
                    r_status = gpio_irq_ctx.ExtIrqInstance->p_api->enable(gpio_irq_ctx.ExtIrqInstance->p_ctrl);
                }

                if (FSP_SUCCESS == r_status)
                {
                    *gpio = &gpio_irq_ctx;
                }
                else
                {
                    status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InternalError);
                }

                break;
            }

            case GPIO_Type_SENOutPin:
            {
#ifdef SEN_PIN_CONNECTION_AVAILABLE

                /* NFC_TODO: SEN pin handling */
                /* Initialization of the SEN-pin Context */
                memset(&sen_pin_context, 0, sizeof(ptxPlatGpio_t));

                sen_pin_context.PortInstance = &g_ioport;
                sen_pin_context.PortPin      = PTX_GPIO_SEN_PIN;
                *gpio = &sen_pin_context;
#else
                *gpio = NULL;
#endif
                break;
            }

            default:
            {
                status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InvalidParameter);
                break;
            }
        }
    }
    else
    {
        status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InvalidParameter);
    }

    return status;
}

ptxStatus_t ptxPLAT_GPIO_Deinit (ptxPlatGpio_t * gpio)
{
    ptxStatus_t status = ptxStatus_Success;

    if (NULL != gpio)
    {
        /* Deinit GPIO. */
        if (NULL != gpio->ExtIrqInstance)
        {
            gpio_irq_ctx.ExtIrqInstance->p_api->disable(gpio_irq_ctx.ExtIrqInstance->p_ctrl);
            gpio_irq_ctx.ExtIrqInstance->p_api->close(gpio_irq_ctx.ExtIrqInstance->p_ctrl);
        }

        /* Clear Platform Context. */
        (void) memset(gpio, 0, sizeof(ptxPlatGpio_t));
    }
    else
    {
        status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InvalidParameter);
    }

    return status;
}

ptxStatus_t ptxPLAT_GPIO_EnableInterrupt (ptxPlatGpio_t * gpio)
{
    ptxStatus_t status = ptxStatus_Success;

    if (NULL != gpio)
    {
        if (NULL != gpio->ExtIrqInstance)
        {
            fsp_err_t r_status = FSP_SUCCESS;

            r_status = gpio_irq_ctx.ExtIrqInstance->p_api->enable(gpio_irq_ctx.ExtIrqInstance->p_ctrl);

            if (FSP_SUCCESS != r_status)
            {
                status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InternalError);
            }
        }
        else
        {
            status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InvalidParameter);
        }
    }
    else
    {
        status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InvalidParameter);
    }

    return status;
}

ptxStatus_t ptxPLAT_GPIO_DisableInterrupt (ptxPlatGpio_t * gpio)
{
    ptxStatus_t status = ptxStatus_Success;

    if (NULL != gpio)
    {
        if (NULL != gpio->ExtIrqInstance)
        {
            fsp_err_t r_status = FSP_SUCCESS;
            r_status = gpio_irq_ctx.ExtIrqInstance->p_api->disable(gpio_irq_ctx.ExtIrqInstance->p_ctrl);

            if (FSP_SUCCESS != r_status)
            {
                status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InternalError);
            }
        }
        else
        {
            status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InvalidParameter);
        }
    }
    else
    {
        status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InvalidParameter);
    }

    return status;
}

ptxStatus_t ptxPLAT_GPIO_GetIntEnableStatus (ptxPlatGpio_t * gpio, uint32_t * state)
{
    ptxStatus_t status = ptxStatus_Success;

    if (NULL != gpio)
    {
        if (NULL != gpio->ExtIrqInstance)
        {
            icu_instance_ctrl_t * p_ctrl = (icu_instance_ctrl_t *) gpio_irq_ctx.ExtIrqInstance->p_ctrl;

            uint32_t value = NVIC_GetEnableIRQ(p_ctrl->irq);
            if ((1U == value) || (0 == value))
            {
                *state = value;
            }
            else
            {
                status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InternalError);
            }
        }
        else
        {
            status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InvalidParameter);
        }
    }
    else
    {
        status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InvalidParameter);
    }

    return status;
}

ptxStatus_t ptxPLAT_GPIO_StartWaitForTrigger (ptxPlatGpio_t        * gpio,
                                              pptxPlat_IRQCallBack_t irqCallBack,
                                              void                 * irqCallBackCtx)
{
    ptxStatus_t status = ptxStatus_Success;

    if (NULL != gpio)
    {
        gpio->IrqCallBack    = irqCallBack;
        gpio->IrqCallBackCtx = irqCallBackCtx;
        status               = ptxPLAT_GPIO_EnableInterrupt(gpio);
    }
    else
    {
        status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InvalidParameter);
    }

    return status;
}

ptxStatus_t ptxPLAT_GPIO_StopWaitForTrigger (ptxPlatGpio_t * gpio)
{
    ptxStatus_t status = ptxStatus_Success;

    if (NULL != gpio)
    {
        status               = ptxPLAT_GPIO_DisableInterrupt(gpio);
        gpio->IrqCallBack    = NULL;
        gpio->IrqCallBackCtx = NULL;
    }
    else
    {
        status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InvalidParameter);
    }

    return status;
}

ptxStatus_t ptxPLAT_GPIO_ReadLevel (ptxPlatGpio_t * gpio, uint8_t * value)
{
    ptxStatus_t status = ptxStatus_Success;

    if ((NULL != gpio) && (NULL != value))
    {
        fsp_err_t      r_status    = FSP_SUCCESS;
        bsp_io_level_t p_pin_value = BSP_IO_LEVEL_LOW;

        r_status = R_IOPORT_PinRead(gpio->PortInstance->p_ctrl, gpio->PortPin, &p_pin_value);

        if (FSP_SUCCESS == r_status)
        {
            *value = (uint8_t) p_pin_value;
        }
        else
        {
            status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InternalError);
        }
    }
    else
    {
        status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InvalidParameter);
    }

    return status;
}

ptxStatus_t ptxPLAT_GPIO_TriggerRx (ptxPlatGpio_t * gpio)
{
    ptxStatus_t status = ptxStatus_Success;

    if (NULL != gpio)
    {
        uint8_t value;
        status = ptxPLAT_GPIO_ReadLevel(gpio, &value);

        if ((ptxStatus_Success == status) && (1U == value))
        {
            if ((gpio_irq_ctx.IrqCallBack != NULL) && (gpio_irq_ctx.IrqCallBackCtx != NULL))
            {
                (void) gpio_irq_ctx.IrqCallBack(gpio_irq_ctx.IrqCallBackCtx);
            }
        }
    }
    else
    {
        status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InvalidParameter);
    }

    return status;
}

ptxStatus_t ptxPLAT_GPIO_WriteLevel (ptxPlatGpio_t * gpio, uint8_t value)
{
    ptxStatus_t status = ptxStatus_Success;

    if ((NULL != gpio))
    {
        if (NULL == gpio->ExtIrqInstance)
        {
            fsp_err_t      r_status;
            bsp_io_level_t p_pin_value;

            p_pin_value = (0 == value) ? BSP_IO_LEVEL_LOW : BSP_IO_LEVEL_HIGH;

            r_status = R_IOPORT_PinWrite(gpio->PortInstance->p_ctrl, gpio->PortPin, p_pin_value);

            if (FSP_SUCCESS != r_status)
            {
                status = PTX_STATUS(ptxStatus_Comp_PERIPH, ptxStatus_InternalError);
            }
        }
        else
        {
            status = PTX_STATUS(ptxStatus_Comp_PERIPH, ptxStatus_InvalidParameter);
        }
    }
    else
    {
        status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InvalidParameter);
    }

    return status;
}

/*
 * ####################################################################################################################
 * INTERRUPT HANDLERS
 * ####################################################################################################################
 */
void ptxPLAT_GPIO_IsrCallback (external_irq_callback_args_t * p_args)
{
    /* NFC_TODO: Add functionality to GPIO interrupt */
    (void) p_args;
}
