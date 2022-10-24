/**************************************************************************/

/*                                                                        */
/*       Copyright (c) Microsoft Corporation. All rights reserved.        */
/*                                                                        */
/*       This software is licensed under the Microsoft Software License   */
/*       Terms for Microsoft Azure RTOS. Full text of the license can be  */
/*       found in the LICENSE file at https://aka.ms/AzureRTOS_EULA       */
/*       and in the root directory of this software.                      */
/*                                                                        */
/**************************************************************************/

/**************************************************************************/
/**************************************************************************/
/**                                                                       */
/** ThreadX Component                                                     */
/**                                                                       */
/**   CMSIS                                                               */
/**                                                                       */
/**************************************************************************/
/**************************************************************************/

#ifndef TX_CMSIS_H
#define TX_CMSIS_H

#if defined(__GNUC__) && !defined(__ARMCC_VERSION)

/* Ignore GCC warnings in CMSIS code. */
 #pragma GCC diagnostic ignored "-Wsign-conversion"
 #pragma GCC diagnostic push
#endif

#include <stddef.h>
#include "../../src/bsp/mcu/all/bsp_arm_exceptions.h"
#include "cmsis_compiler.h"

#if   __ARM_ARCH_7EM__
 #define __MPU_PRESENT             1   /*!< MPU present or not                                                    */
 #define __NVIC_PRIO_BITS          4   /*!< Number of Bits used for Priority Levels                               */
 #define __Vendor_SysTickConfig    0   /*!< Set to 1 if different SysTick Config is used                          */
 #define __FPU_PRESENT             1   /*!< FPU present or not                                                    */
 #include "core_cm4.h"
#elif __ARM_ARCH_8M_BASE__
 #define __MPU_PRESENT             1   /*!< MPU present or not                                                    */
 #define __NVIC_PRIO_BITS          2   /*!< Number of Bits used for Priority Levels                               */
 #define __Vendor_SysTickConfig    0   /*!< Set to 1 if different SysTick Config is used                          */
 #define __FPU_PRESENT             0   /*!< FPU present or not                                                    */
 #include "core_cm23.h"                /*!< Cortex-M23 processor and core peripherals                             */
#elif __ARM_ARCH_8M_MAIN__
 #define __MPU_PRESENT             1   /*!< MPU present or not                                                    */
 #define __NVIC_PRIO_BITS          4   /*!< Number of Bits used for Priority Levels                               */
 #define __Vendor_SysTickConfig    0   /*!< Set to 1 if different SysTick Config is used                          */
 #define __FPU_PRESENT             1   /*!< FPU present or not                                                    */
 #define __DSP_PRESENT             1   /*!< DSP present or not                                                    */
 #include "core_cm33.h"
#elif __ARM_ARCH_8_1M_MAIN__
 #define __MPU_PRESENT             1   /*!< MPU present or not                                                    */
 #define __NVIC_PRIO_BITS          4   /*!< Number of Bits used for Priority Levels                               */
 #define __Vendor_SysTickConfig    0   /*!< Set to 1 if different SysTick Config is used                          */
 #define __FPU_PRESENT             1   /*!< FPU present or not                                                    */
 #define __DSP_PRESENT             1   /*!< DSP present or not                                                    */
 #include "core_cm85.h"
#else
 #error Unsupported Architecture
#endif

#if defined(__GNUC__) && !defined(__ARMCC_VERSION)

/* Restore warning settings for 'sign-conversion' to as specified on command line. */
 #pragma GCC diagnostic pop
#endif

#endif                                 /* TX_CMSIS_H */
