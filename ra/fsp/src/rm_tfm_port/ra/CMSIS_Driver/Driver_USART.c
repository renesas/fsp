/***********************************************************************************************************************
 * File Name    : driver_usart.c
 * Description  : This file contains uart driver specific API implementation.
 * ***********************************************************************************************************************/

/***********************************************************************************************************************
 * DISCLAIMER
 * This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No
 * other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
 * applicable laws, including copyright laws.
 * THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
 * THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM
 * EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES
 * SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS
 * SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 * Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of
 * this software. By using this software, you agree to the additional terms and conditions found by accessing the
 * following link:
 * http://www.renesas.com/disclaimer
 *
 * Copyright (C) 2019 Renesas Electronics Corporation. All rights reserved.
 ***********************************************************************************************************************/

#include "tfm_common_config.h"

#include <Driver_USART.h>
#include <string.h>
#include <stdint.h>

#if CFG_UART_DEBUG_ENABLE
 #include "r_sci_uart.h"
 #include "r_uart_api.h"

static volatile uart_event_t g_uart_evt = 0;
#endif

#ifndef ARG_UNUSED
 #define ARG_UNUSED(arg)    ((void) arg)
#endif

/* Driver version */
#define ARM_USART_DRV_VERSION    ARM_DRIVER_VERSION_MAJOR_MINOR(1, 0)

static volatile uint32_t g_num = 0;

extern ARM_DRIVER_USART Driver_USART;

/* Driver Version */
static ARM_DRIVER_VERSION DriverVersion =
{
    ARM_USART_API_VERSION,
    ARM_USART_DRV_VERSION
};

/* Driver Capabilities */
static ARM_USART_CAPABILITIES DriverCapabilities =
{
    1,                                 /* supports UART (Asynchronous) mode */
    0,                                 /* supports Synchronous Master mode */
    0,                                 /* supports Synchronous Slave mode */
    0,                                 /* supports UART Single-wire mode */
    0,                                 /* supports UART IrDA mode */
    0,                                 /* supports UART Smart Card mode */
    0,                                 /* Smart Card Clock generator available */
    0,                                 /* RTS Flow Control available */
    0,                                 /* CTS Flow Control available */
    0,                                 /* Transmit completed event: \ref ARM_USARTx_EVENT_TX_COMPLETE */
    0,                                 /* Signal receive character timeout event: \ref ARM_USARTx_EVENT_RX_TIMEOUT */
    0,                                 /* RTS Line: 0=not available, 1=available */
    0,                                 /* CTS Line: 0=not available, 1=available */
    0,                                 /* DTR Line: 0=not available, 1=available */
    0,                                 /* DSR Line: 0=not available, 1=available */
    0,                                 /* DCD Line: 0=not available, 1=available */
    0,                                 /* RI Line: 0=not available, 1=available */
    0,                                 /* Signal CTS change event: \ref ARM_USARTx_EVENT_CTS */
    0,                                 /* Signal DSR change event: \ref ARM_USARTx_EVENT_DSR */
    0,                                 /* Signal DCD change event: \ref ARM_USARTx_EVENT_DCD */
    0,                                 /* Signal RI change event: \ref ARM_USARTx_EVENT_RI */
    0                                  /* Reserved */
};

#if CFG_UART_DEBUG_ENABLE

/* FSP structures required by uart and flash drivers */
extern sci_uart_instance_ctrl_t g_tfm_fsp_uart_ctrl;
extern const uart_cfg_t         g_tfm_fsp_uart_cfg;
#endif

static ARM_DRIVER_VERSION ARM_USART_GetVersion (void)
{
    memset(&DriverVersion, 0, sizeof(DriverVersion));

    return DriverVersion;
}

static ARM_USART_CAPABILITIES ARM_USART_GetCapabilities (void)
{
    return DriverCapabilities;
}

static int32_t ARM_USART_Initialize (ARM_USART_SignalEvent_t cb_event)
{
    ARG_UNUSED(cb_event);
#if CFG_UART_DEBUG_ENABLE
    fsp_err_t fsp_err = FSP_SUCCESS;

    fsp_err = R_SCI_UART_Open(&g_tfm_fsp_uart_ctrl, &g_tfm_fsp_uart_cfg);
    if (FSP_SUCCESS != fsp_err)
    {
        return ARM_DRIVER_ERROR;
    }
#endif

    return ARM_DRIVER_OK;
}

static int32_t ARM_USART_Uninitialize (void)
{
#if CFG_UART_DEBUG_ENABLE
    fsp_err_t fsp_err = FSP_SUCCESS;

    fsp_err = R_SCI_UART_Close(&g_tfm_fsp_uart_ctrl);
    if (FSP_SUCCESS != fsp_err)
    {
        return ARM_DRIVER_ERROR;
    }
#endif

    return ARM_DRIVER_OK;
}

static int32_t ARM_USART_PowerControl (ARM_POWER_STATE state)
{
    ARG_UNUSED(state);                 /* Not used, avoid warning */

    /* Nothing to be done */
    return ARM_DRIVER_OK;
}

static uint32_t ARM_USART_GetTxCount (void)
{
    /* Return the last successfully transmitted data count.
     * This implementation will not work in a multithreaded environment. */
    return g_num;
}

static int32_t ARM_USART_Control (uint32_t control, uint32_t arg)
{
    ARG_UNUSED(arg);                   /* Not used, avoid warning */
    ARG_UNUSED(control);               /* Not used, avoid warning */

    /* Nothing to be done */
    return ARM_DRIVER_OK;
}

static ARM_USART_STATUS ARM_USART_GetStatus (void)
{
    /* Nothing to be done */
    ARM_USART_STATUS status = {0, 0, 0, 0, 0, 0, 0, 0};

    return status;
}

static int32_t ARM_USART_Send (const void * data, uint32_t num)
{
    ARG_UNUSED(data);
#if CFG_UART_DEBUG_ENABLE
    fsp_err_t fsp_err = FSP_SUCCESS;

    if ((num == 0) || (data == NULL))
    {
        return ARM_DRIVER_ERROR;
    }

    g_uart_evt = 0;

    fsp_err = R_SCI_UART_Write(&g_tfm_fsp_uart_ctrl, data, num);
    if (FSP_SUCCESS != fsp_err)
    {
        return ARM_DRIVER_ERROR;
    }

    /* Wait for UART Tx to complete */
    while (!g_uart_evt)
    {
        ;
    }

    if ((g_uart_evt != UART_EVENT_TX_DATA_EMPTY))
    {
        g_num = 0;

        return ARM_DRIVER_ERROR;
    }
#endif

    /*Save the transmitted number to be used in ARM_USART_GetTxCount*/
    g_num = num;

    return ARM_DRIVER_OK;
}

static int32_t ARM_USART_Receive (void * data, uint32_t num)
{
#if CFG_UART_DEBUG_ENABLE
    fsp_err_t fsp_err = FSP_SUCCESS;

    if (data == NULL)
    {
        return ARM_DRIVER_ERROR;
    }

    g_uart_evt = 0;

    fsp_err = R_SCI_UART_Read(&g_tfm_fsp_uart_ctrl, data, num);
    if (FSP_SUCCESS != fsp_err)
    {
        return ARM_DRIVER_ERROR;
    }

    /* Wait for UART Rx to complete */
    while (!g_uart_evt)
    {
        ;
    }

    if (g_uart_evt != UART_EVENT_RX_COMPLETE)
    {
        return ARM_DRIVER_ERROR;
    }

    return ARM_DRIVER_OK;
#else
    ARG_UNUSED(data);
    ARG_UNUSED(num);

    return ARM_DRIVER_ERROR;
#endif
}

#if CFG_UART_DEBUG_ENABLE
void user_uart_callback (uart_callback_args_t * p_args)
{
    if (NULL != p_args)
    {
        g_uart_evt = p_args->event;
    }
}

#endif

ARM_DRIVER_USART Driver_USART =
{
    ARM_USART_GetVersion,
    ARM_USART_GetCapabilities,
    ARM_USART_Initialize,
    ARM_USART_Uninitialize,
    ARM_USART_PowerControl,
    ARM_USART_Send,
    ARM_USART_Receive,
    NULL,
    ARM_USART_GetTxCount,
    NULL,
    ARM_USART_Control,
    ARM_USART_GetStatus,
    NULL,
    NULL
};
