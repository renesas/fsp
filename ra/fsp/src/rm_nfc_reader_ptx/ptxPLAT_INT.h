/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef COMPS_PLAT_PTXPLAT_INT_H_
 #define COMPS_PLAT_PTXPLAT_INT_H_

 #include "ptxStatus.h"
 #include "ptxPLAT.h"

 #if defined(PTX_INTF_UART)
  #include "ptxPLAT_UART.h"
 #elif defined(PTX_INTF_SPI)
  #include "ptxPLAT_SPI.h"
 #elif defined(PTX_INTF_I2C)
  #include "ptxPLAT_I2C.h"
 #else
  #error Error - Missing or unsupported Host-Interface implementation used
 #endif

 #ifdef __cplusplus
extern "C" {
 #endif

/**
 * Forward declarations.
 */
struct ptxPlatGpio;

/**
 * Platform-specific configuration parameters.
 */
typedef struct ptxPlat
{
    ptxStatus_Comps_t CompId;          /**< Component Id. */

 #if defined(PTX_INTF_UART)
    ptxPLAT_UART_t * Uart;             /**< Pointer to UART Context. Platform dependent. */
 #elif defined(PTX_INTF_SPI)
    ptxPLAT_Spi_t * Spi;               /**< Pointer to SPI Context. Platform dependent. */
 #elif defined(PTX_INTF_I2C)
    ptxPLAT_I2C_t * I2c;               /**< Pointer to I2C Context. Platform dependent. */
 #else
  #error Error - Missing or unsupported Host-Interface implementation used
 #endif

    struct ptxPlatGpio * SENPin;       /**< Connection to SEN-pin (optional). */

    pptxPlat_RxCallBack_t RxCb;        /**< Callback function */
    void                * CtxRxCb;     /**< Callback Context */

    uint16_t IRQDisabledCnt;           /**< IRQ Enable/Disable Protection */
} ptxPlat_t;

 #ifdef __cplusplus
}
 #endif

#endif                                 /* Guard */
