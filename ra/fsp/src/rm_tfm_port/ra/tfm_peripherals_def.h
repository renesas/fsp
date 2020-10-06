/*
 * Copyright (c) 2018-2020, Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef __TFM_PERIPHERALS_DEF_H__
#define __TFM_PERIPHERALS_DEF_H__

#include "platform_irq.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Platform data is defined here:
 *
 * #define TFM_TIMER0_IRQ           (TIMER0_IRQn)
 * #define TFM_TIMER1_IRQ           (TIMER1_IRQn)
 * #define FF_TEST_UART_IRQ         (UART1_Tx_IRQn)
 * #define FF_TEST_UART_IRQ_Handler UARTTX1_Handler
 *
 * struct tfm_spm_partition_platform_data_t;
 *
 * extern struct tfm_spm_partition_platform_data_t tfm_peripheral_std_uart;
 * extern struct tfm_spm_partition_platform_data_t tfm_peripheral_timer0;

 * #define TFM_PERIPHERAL_STD_UART     (&tfm_peripheral_std_uart)
 * #define TFM_PERIPHERAL_TIMER0       (&tfm_peripheral_timer0)
 *
 */


#ifdef __cplusplus
}
#endif

#endif /* __TFM_PERIPHERALS_DEF_H__ */
