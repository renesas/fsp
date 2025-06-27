/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef COMPS_PLAT_PTXPLAT_GPIO_H_
 #define COMPS_PLAT_PTXPLAT_GPIO_H_

/*
 * ####################################################################################################################
 * INCLUDES
 * ####################################################################################################################
 */

 #include "ptxStatus.h"
 #include "r_icu.h"
 #include "r_ioport_api.h"
 #include <stddef.h>

 #ifdef __cplusplus
extern "C" {
 #endif

/*
 * ####################################################################################################################
 * DEFINES / TYPES
 * ####################################################################################################################
 */

/**
 * \brief Callback function for GPIO/IRQ-line Interrupt.
 *
 */
typedef void (* pptxPlat_IRQCallBack_t)(void * ctx);

/**
 * GPIO type parameter.
 */
typedef enum ptxPlatGpio_Type
{
    GPIO_Type_PTXExtIRQPin,
    GPIO_Type_SENOutPin,
} ptxPlatGpio_Type_t;

/**
 * standard GPIO configuration parameters.
 */
typedef struct ptxPlatGpio_Config
{
    ptxPlatGpio_Type_t Type;           /*< Pin Type */
} ptxPlatGpio_Config_t;

/**
 * Platform-specific GPIO main structure.
 */
typedef struct ptxPlatGpio
{
    external_irq_instance_t * ExtIrqInstance; /*< External IRQ Instance. */
    pptxPlat_IRQCallBack_t    IrqCallBack;    /*< IRQ triggering callback */
    void * IrqCallBackCtx;                    /*< Context for IRQ triggering callback */
    const ioport_instance_t * PortInstance;   /*< Port instance on the device. */
    bsp_io_port_pin_t         PortPin;        /*< Pin identification on the device. */
} ptxPlatGpio_t;

/*
 * ####################################################################################################################
 * API FUNCTIONS
 * ####################################################################################################################
 */

ptxStatus_t ptxPLAT_GPIO_Open(ioport_instance_t       * gpio_instance,
                              external_irq_instance_t * irq_instance,
                              const bsp_io_port_pin_t   interrupt_pin);

/**
 * \brief Get an initialized GPIO context used for IRQ- or standard-usage.
 *
 * \note This function shall be successfully executed before any other call to the functions in this module.
 *       It initializes GPIOs hardware-wise.
 *
 * \param[out]       gpio              Pointer to pointer where the allocated and initialized GPIO context is going to be provided.
 * \param[in]        gpioPars          Configuration for GPIO.
 *
 * \return Status, indicating whether the operation was successful. See \typedef ptxStatus_t.
 */
ptxStatus_t ptxPLAT_GPIO_GetInitialized(ptxPlatGpio_t ** gpio, ptxPlatGpio_Config_t * gpioPars);

/**
 * \brief Deinitializes a GPIO context.
 *
 * \note This function shall be called once that the caller has finished with GPIO-IRQ.
 *
 * \param[in]       gpio             Pointer to an initialized GPIO context.
 *
 * \return Status, indicating whether the operation was successful. See \typedef ptxStatus_t.
 */
ptxStatus_t ptxPLAT_GPIO_Deinit(ptxPlatGpio_t * gpio);

/**
 * \brief Enable interrupt for the GPIO-IRQ.
 *
 * \param[in]       gpio             Pointer to an initialized GPIO context.
 *
 * \return Status, indicating whether the operation was successful. See \typedef ptxStatus_t.
 */
ptxStatus_t ptxPLAT_GPIO_EnableInterrupt(ptxPlatGpio_t * gpio);

/**
 * \brief Disable interrupt for the GPIO-IRQ.
 *
 * \param[in]       gpio             Pointer to an initialized GPIO context.
 *
 * \return Status, indicating whether the operation was successful. See \typedef ptxStatus_t.
 */
ptxStatus_t ptxPLAT_GPIO_DisableInterrupt(ptxPlatGpio_t * gpio);

/**
 * \brief Get current interrupt enable setting for the GPIO-IRQ.
 *
 * \param[in]       gpio             Pointer to an initialized GPIO context.
 * \param[out]      state            Pointer to returned value: 0 - disabled, 1 - enabled.
 *
 * \return Status, indicating whether the operation was successful. See \typedef ptxStatus_t.
 */
ptxStatus_t ptxPLAT_GPIO_GetIntEnableStatus(ptxPlatGpio_t * gpio, uint32_t * state);

/**
 * \brief Start waiting (asynchronously) for the GPIO-IRQ to be triggered.
 *
 * \note This function is not blocking. It registers the Callback to be called once
 *       that the IRQ has been triggered.
 *
 * \param[in]       gpio             Pointer to an initialized GPIO context.
 * \param[in]       irqCallBack      Callback for IRQ triggering. If NULL the callback not be called.
 * \param[in]       irqCallBackCtx   Context used by /ref irqCallBack.
 *
 * \return Status, indicating whether the operation was successful. See \typedef ptxStatus_t.
 */
ptxStatus_t ptxPLAT_GPIO_StartWaitForTrigger(ptxPlatGpio_t        * gpio,
                                             pptxPlat_IRQCallBack_t irqCallBack,
                                             void                 * irqCallBackCtx);

/**
 * \brief Stop waiting  (asynchronously) for the IRQ to be triggered.
 *
 * \note This function shall be called after /ref ptxPLAT_GPIO_StartWaitForTrigger
 *
 * \param[in]       gpio             Pointer to an initialized GPIO context.
 *
 * \return Status, indicating whether the operation was successful. See \typedef ptxStatus_t.
 */
ptxStatus_t ptxPLAT_GPIO_StopWaitForTrigger(ptxPlatGpio_t * gpio);

/**
 * \brief Reads GPIO level.
 *
 * \param[in]       gpio             Pointer to an initialized GPIO context.
 * \param[out]      value            Pointer where the state of the GPIO is going to be provided.
 *
 * \return Status, indicating whether the operation was successful. See \typedef ptxStatus_t.
 */
ptxStatus_t ptxPLAT_GPIO_ReadLevel(ptxPlatGpio_t * gpio, uint8_t * value);

/**
 * \brief Triggers Rx callback, if IRQ line is high.
 *
 * \param[in]       gpio             Pointer to an initialized GPIO context.
 *
 * \return Status, indicating whether the operation was successful. See \typedef ptxStatus_t.
 */

ptxStatus_t ptxPLAT_GPIO_TriggerRx(ptxPlatGpio_t * gpio);

/**
 * \brief Writes value/level to a GPIO.
 *
 * \param[in]       gpio             Pointer to an initialized GPIO context.
 * \param[in]       value            Value/Level to be written.
 *
 * \return Status, indicating whether the operation was successful. See \typedef ptxStatus_t.
 */
ptxStatus_t ptxPLAT_GPIO_WriteLevel(ptxPlatGpio_t * gpio, uint8_t value);

 #ifdef __cplusplus
}
 #endif

#endif                                 /* Guard */
