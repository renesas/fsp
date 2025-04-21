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

#include "ptxPLAT.h"
#include "ptxPLAT_INT.h"
#include "ptxPLAT_TIMER.h"
#include <string.h>

/*
 * ####################################################################################################################
 * DEFINES / TYPES
 * ####################################################################################################################
 */
#define PTX_PLAT_MAXNUMOF_TXBUFF    (0x02u)
#define PTX_PLAT_MAX_PAYLOAD_LEN    (1024u)
#define PTX_PLAT_TIMEOUT_10MS       (10U)
#define PTX_PLAT_TIMEOUT_100MS      (100U)

/*
 * ####################################################################################################################
 * INTERNAL FUNCTIONS
 * ####################################################################################################################
 */

ptxPlat_t platform;

/*
 * ####################################################################################################################
 * API FUNCTIONS
 * ####################################################################################################################
 */

ptxStatus_t ptxPLAT_AllocAndInit (ptxPlat_t ** plat, ptxPLAT_ConfigPars_t * initParams)
{
    ptxStatus_t status = ptxStatus_Success;

    if ((NULL != plat) && (NULL != initParams))
    {
        (void) memset(&platform, 0, sizeof(ptxPlat_t));

        platform.CompId         = ptxStatus_Comp_PLAT;
        platform.IRQDisabledCnt = 0;

#if defined(PTX_INTF_UART)

        /* Init UART (UART always uses default speed for system initialization. After NSC_INIT_CMD speed can be updated to user defined value). */
        ptxPLAT_UARTConfigPars_t uart_pars = {0};
        uart_pars.IntfSpeed = initParams->Speed;;

        status = ptxPLAT_UART_GetInitialized(&platform.Uart, &uart_pars);
#elif defined(PTX_INTF_SPI)

        /* Init SPI. */
        ptxPLAT_SpiConfigPars_t spi_pars = {0};
        spi_pars.IntfSpeed = initParams->Speed;

        status = ptxPLAT_SPI_GetInitialized(&platform.Spi, &spi_pars);
#elif defined(PTX_INTF_I2C)

        /* Init I2C. */
        ptxPLAT_I2CConfigPars_t i2c_pars = {0};
        i2c_pars.DeviceAddress = initParams->DeviceAddress;
        i2c_pars.IntfSpeed     = initParams->Speed;

        status = ptxPLAT_I2C_GetInitialized(&platform.I2c, &i2c_pars);
#else
 #error Error - Missing or unsupported Host-Interface implementation used
#endif

        /*
         * Init SEN-pin.
         *
         * Note: GPIO-instance can be returned as NULL-value as usage of SEN-pin is optional and dependent on present HW.
         *       This is handled internally by platform-dependent GPIO-component.
         */
        if (ptxStatus_Success == status)
        {
            ptxPlatGpio_Config_t gpio_pars;
            gpio_pars.Type = GPIO_Type_SENOutPin;

            status = ptxPLAT_GPIO_GetInitialized(&platform.SENPin, &gpio_pars);
        }

        if (ptxStatus_Success == status)
        {
            *plat = &platform;
        }
    }
    else
    {
        status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InvalidParameter);
    }

    return status;
}

ptxStatus_t ptxPLAT_Deinit (ptxPlat_t * plat)
{
    ptxStatus_t status = ptxStatus_Success;

    if (PTX_COMP_CHECK(plat, ptxStatus_Comp_PLAT))
    {
#if defined(PTX_INTF_UART)
        (void) ptxPLAT_UART_Deinit(plat->Uart);
#elif defined(PTX_INTF_SPI)
        (void) ptxPLAT_SPI_Deinit(plat->Spi);
#elif defined(PTX_INTF_I2C)
        (void) ptxPLAT_I2C_Deinit(plat->I2c);
#else
 #error Error - Missing or unsupported Host-Interface implementation used
#endif

        /* Clear Platform Context. */
        (void) memset(plat, 0, sizeof(ptxPlat_t));
    }
    else
    {
        status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InvalidParameter);
    }

    return status;
}

ptxStatus_t ptxPLAT_TRx (ptxPlat_t * plat,
                         uint8_t   * txBuf[],
                         size_t      txLen[],
                         size_t      numTxBuffers,
                         uint8_t   * rxBuf[],
                         size_t    * rxLen[],
                         size_t      numRxBuffers,
                         uint8_t     flags)
{
    ptxStatus_t  status         = ptxStatus_Success;
    const size_t numBuffers_max = 5U;
    size_t       num_buffers_tx = numTxBuffers;

    if (PTX_COMP_CHECK(plat,
                       ptxStatus_Comp_PLAT) && (num_buffers_tx < numBuffers_max) && (numRxBuffers <= numBuffers_max))
    {
#if defined(PTX_INTF_UART)
        status = ptxPLAT_UART_TRx(plat->Uart, txBuf, txLen, numTxBuffers, rxBuf, rxLen, numRxBuffers, flags);
#elif defined(PTX_INTF_SPI)
        status = ptxPLAT_SPI_TRx(plat->Spi, txBuf, txLen, numTxBuffers, rxBuf, rxLen, numRxBuffers, flags);
#elif defined(PTX_INTF_I2C)
        status = ptxPLAT_I2C_TRx(plat->I2c, txBuf, txLen, numTxBuffers, rxBuf, rxLen, numRxBuffers, flags);
#else
 #error Error - Missing or unsupported Host-Interface implementation used
#endif
    }
    else
    {
        status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InvalidParameter);
    }

    return status;
}

ptxStatus_t ptxPLAT_StartWaitForRx (ptxPlat_t * plat, pptxPlat_RxCallBack_t irqCb, void * ctxIrqCb)
{
    ptxStatus_t status = ptxStatus_Success;

    if (PTX_COMP_CHECK(plat, ptxStatus_Comp_PLAT) && (NULL != irqCb) && (NULL != ctxIrqCb))
    {
#if defined(PTX_INTF_UART)
        status = ptxPLAT_UART_StartWaitForRx(plat->Uart, irqCb, ctxIrqCb);
#elif defined(PTX_INTF_SPI)
        status = ptxPLAT_SPI_StartWaitForRx(plat->Spi, irqCb, ctxIrqCb);
#elif defined(PTX_INTF_I2C)
        status = ptxPLAT_I2C_StartWaitForRx(plat->I2c, irqCb, ctxIrqCb);
#else
 #error Error - Missing or unsupported Host-Interface implementation used
#endif
    }
    else
    {
        status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InvalidParameter);
    }

    return status;
}

ptxStatus_t ptxPLAT_StopWaitForRx (ptxPlat_t * plat)
{
    ptxStatus_t status = ptxStatus_Success;

    if (PTX_COMP_CHECK(plat, ptxStatus_Comp_PLAT))
    {
#if defined(PTX_INTF_UART)
        status = ptxPLAT_UART_StopWaitForRx(plat->Uart);
#elif defined(PTX_INTF_SPI)
        status = ptxPLAT_SPI_StopWaitForRx(plat->Spi);
#elif defined(PTX_INTF_I2C)
        status = ptxPLAT_I2C_StopWaitForRx(plat->I2c);
#else
 #error Error - Missing or unsupported Host-Interface implementation used
#endif
    }
    else
    {
        status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InvalidParameter);
    }

    return status;
}

ptxStatus_t ptxPLAT_WaitForInterrupt (ptxPlat_t * plat)
{
    ptxStatus_t status = ptxStatus_Success;

    if (PTX_COMP_CHECK(plat, ptxStatus_Comp_PLAT))
    {
        /* Wait for Interrupts */
        __DSB();
        __WFI();
        __ISB();
    }
    else
    {
        status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InvalidParameter);
    }

    return status;
}

uint8_t ptxPLAT_CheckRxActive (ptxPlat_t * plat)
{
    uint8_t rx_active = 0;

    if (PTX_COMP_CHECK(plat, ptxStatus_Comp_PLAT))
    {
#if defined(PTX_INTF_UART)
        rx_active = ptxPLAT_UART_CheckRxActive(plat->Uart);
#endif
    }

    return rx_active;
}

ptxStatus_t ptxPLAT_IsRxPending (ptxPlat_t * plat, uint8_t * isRxPending)
{
    ptxStatus_t status = ptxStatus_Success;

    if ((NULL != plat) && (NULL != isRxPending))
    {
#ifdef PTX_INTF_UART
        *isRxPending = ptxPLAT_UART_CheckRxActive(plat->Uart);
#elif defined(PTX_INTF_SPI)
        status = ptxPLAT_GPIO_ReadLevel(plat->Spi->Gpio, isRxPending);
#elif defined(PTX_INTF_I2C)
        status = ptxPLAT_GPIO_ReadLevel(plat->I2c->Gpio, isRxPending);
#else
 #error Error - Missing or unsupported Host-Interface implementation used
#endif
    }
    else
    {
        status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InvalidParameter);
    }

    return status;
}

ptxStatus_t ptxPLAT_TriggerRx (ptxPlat_t * plat)
{
    ptxStatus_t status = ptxStatus_Success;

    if (PTX_COMP_CHECK(plat, ptxStatus_Comp_PLAT))
    {
#ifdef PTX_INTF_UART
        status = ptxPLAT_UART_TriggerRx(plat->Uart);
        if (PTX_GET_STATUS(status) == ptxStatus_InterfaceError)
        {
            /** Uart interface error reported. Try to recover. */
            (void) ptxPLAT_UART_Reset(plat->Uart);
        }

#elif defined(PTX_INTF_SPI)
        status = ptxPLAT_GPIO_TriggerRx(plat->Spi->Gpio);
#elif defined(PTX_INTF_I2C)
        status = ptxPLAT_GPIO_TriggerRx(plat->I2c->Gpio);
#else
 #error Error - Missing or unsupported Host-Interface implementation used
#endif
    }
    else
    {
        status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InvalidParameter);
    }

    return status;
}

ptxStatus_t ptxPLAT_Sleep (ptxPlat_t * plat, uint32_t sleep_ms)
{
    ptxStatus_t status = ptxStatus_Success;

    if (PTX_COMP_CHECK(plat, ptxStatus_Comp_PLAT))
    {
        ptxPlatTimer_t * avail_timer = NULL;

        /* Get Timer. */
        status = ptxPLAT_TIMER_GetInitializedTimer(&avail_timer);

        if ((ptxStatus_Success == status) && (NULL != avail_timer))
        {
            /* Start Timer (Blocking) */
            status = ptxPLAT_TIMER_Start(avail_timer, sleep_ms, 1U, NULL, NULL);

            /* Stop timer. */
            (void) ptxPLAT_TIMER_Stop(avail_timer);

            /* DeInit and release timer. */
            (void) ptxPLAT_TIMER_Deinit(avail_timer);
        }
    }
    else
    {
        status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InvalidParameter);
    }

    (void) sleep_ms;

    return status;
}

void ptxPLAT_DisableInterrupts (ptxPlat_t * plat)
{
    if (NULL != plat)
    {
        /* Disable interrupts */
        __disable_irq();

        /* Increase number of disable interrupt function calls */
        plat->IRQDisabledCnt++;
    }
}

void ptxPLAT_EnableInterrupts (ptxPlat_t * plat)
{
    if (NULL != plat)
    {
        /* Decrease number of disable interrupt function calls */
        if (0 != plat->IRQDisabledCnt)
        {
            plat->IRQDisabledCnt--;
        }

        /* Check if we are ready to enable interrupts */
        if (0 == plat->IRQDisabledCnt)
        {
            /* Enable interrupts */
            __enable_irq();
        }
    }
}

ptxStatus_t ptxPLAT_ResetChip (ptxPlat_t * plat)
{
    ptxStatus_t status = ptxStatus_Success;

    if (PTX_COMP_CHECK(plat, ptxStatus_Comp_PLAT))
    {
        if (NULL != plat->SENPin)
        {
            status = ptxPLAT_GPIO_WriteLevel(plat->SENPin, 0);

            if (ptxStatus_Success == status)
            {
                (void) ptxPLAT_Sleep(plat, PTX_PLAT_TIMEOUT_10MS);
                status = ptxPLAT_GPIO_WriteLevel(plat->SENPin, 1U);
                (void) ptxPLAT_Sleep(plat, PTX_PLAT_TIMEOUT_100MS);
            }
        }
        else
        {
            /* This status shall be set if the SEN-pin is not connected to any GPIO */
            status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_NotImplemented);
        }
    }
    else
    {
        status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InvalidParameter);
    }

    return status;
}

ptxStatus_t ptxPLAT_GetInitializedTimer (ptxPlat_t * plat, struct ptxPlatTimer ** timer)
{
    ptxStatus_t status = ptxStatus_Success;

    if (PTX_COMP_CHECK(plat, ptxStatus_Comp_PLAT))
    {
        status = ptxPLAT_TIMER_GetInitializedTimer(timer);
    }
    else
    {
        status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InvalidParameter);
    }

    return status;
}

ptxStatus_t ptxPLAT_TimerStart (ptxPlat_t              * plat,
                                struct ptxPlatTimer    * timer,
                                uint32_t                 ms,
                                uint8_t                  isBlock,
                                pptxPlat_TimerCallBack_t fnISRCb,
                                void                   * ISRCxt)
{
    ptxStatus_t status = ptxStatus_Success;

    if (PTX_COMP_CHECK(plat, ptxStatus_Comp_PLAT))
    {
        status = ptxPLAT_TIMER_Start(timer, ms, isBlock, fnISRCb, ISRCxt);
    }
    else
    {
        status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InvalidParameter);
    }

    return status;
}

ptxStatus_t ptxPLAT_TimerIsElapsed (ptxPlat_t * plat, struct ptxPlatTimer * timer, uint8_t * isElapsed)
{
    ptxStatus_t status = ptxStatus_Success;

    if (PTX_COMP_CHECK(plat, ptxStatus_Comp_PLAT))
    {
        status = ptxPLAT_TIMER_IsElapsed(timer, isElapsed);
    }
    else
    {
        status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InvalidParameter);
    }

    return status;
}

ptxStatus_t ptxPLAT_TimerDeinit (ptxPlat_t * plat, struct ptxPlatTimer * timer)
{
    ptxStatus_t status = ptxStatus_Success;

    if (PTX_COMP_CHECK(plat, ptxStatus_Comp_PLAT))
    {
        status = ptxPLAT_TIMER_Deinit(timer);
    }
    else
    {
        status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InvalidParameter);
    }

    return status;
}

#if defined(PTX_INTF_UART)
ptxStatus_t ptxPLAT_SetIntfSpeed (ptxPlat_t * plat, uint32_t speed)
{
    ptxStatus_t status = ptxStatus_Success;

    if (PTX_COMP_CHECK(plat, ptxStatus_Comp_PLAT))
    {
        status = ptxPLAT_UART_SetIntfSpeed(plat->Uart, speed);
    }
    else
    {
        status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InvalidParameter);
    }

    return status;
}

uint32_t ptxPLAT_GetIntfSpeed (ptxPlat_t * plat)
{
    uint32_t speed = 0;

    if (PTX_COMP_CHECK(plat, ptxStatus_Comp_PLAT))
    {
        speed = plat->Uart->IntfSpeed;
    }

    return speed;
}

ptxStatus_t ptxPLAT_SetCleanStateRx (ptxPlat_t * plat)
{
    ptxStatus_t status = ptxStatus_Success;

    if (PTX_COMP_CHECK(plat, ptxStatus_Comp_PLAT))
    {
        status = ptxPLAT_UART_SetCleanStateRx(plat->Uart);
    }
    else
    {
        status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InvalidParameter);
    }

    return status;
}

ptxStatus_t ptxPLAT_GetReceivedMessage (ptxPlat_t * plat, uint8_t * rxMessageBuffer, size_t * rxMessageBufferLen)
{
    ptxStatus_t status = ptxStatus_Success;

    if (PTX_COMP_CHECK(plat, ptxStatus_Comp_PLAT))
    {
        status = ptxPLAT_UART_GetReceivedMessage(plat->Uart, rxMessageBuffer, rxMessageBufferLen);
    }
    else
    {
        status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InvalidParameter);
    }

    return status;
}

#endif
