/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef FREERTOSCONFIG_H
#define FREERTOSCONFIG_H

#define configUSE_PREEMPTION                       (0)
#define configMAX_PRIORITIES                       (5)
#define configMINIMAL_STACK_SIZE                   (128)
#define configUSE_16_BIT_TICKS                     (0)
#define configUSE_IDLE_HOOK                        (0)
#define configUSE_TICK_HOOK                        (0)
#define configNUM_THREAD_LOCAL_STORAGE_POINTERS    (5)

#endif                                 /* FREERTOSCONFIG_H */
