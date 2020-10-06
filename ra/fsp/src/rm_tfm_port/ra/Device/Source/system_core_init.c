/*
 * Copyright (c) 2009-2019 Arm Limited. All rights reserved.
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
 *
 * This file is derivative of CMSIS V5.01 \Device\ARM\ARMCM33\Source\system_ARMCM33.c
 * https://github.com/ARM-software/CMSIS_5/tree/5.0.1
 * Git SHA: 8a1d9d6ee18b143ae5befefa14d89fb5b3f99c75
 */
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "system_core_init.h"
#include "platform_description.h"
/*----------------------------------------------------------------------------
  Externals
 *----------------------------------------------------------------------------*/

extern void (* __init_array_start[])(void);

extern void (* __init_array_end[])(void);

/*----------------------------------------------------------------------------
  System initialization function
 *----------------------------------------------------------------------------*/
void RM_TFM_SystemInit (void)
{
    /* Initialize C runtime */
    __asm volatile("ldr    r4, =__copy_table_start__   \n"
                   "ldr    r5, =__copy_table_end__     \n"

                   ".L_loop0:                          \n"
                   "cmp    r4, r5                      \n"
                   "bge    .L_loop0_done               \n"
                   "ldr    r1, [r4]                    \n"
                   "ldr    r2, [r4, #4]                \n"
                   "ldr    r3, [r4, #8]                \n"

                   ".L_loop0_0:                        \n"
                   "subs    r3, #4                     \n"
                   "ittt    ge                         \n"
                   "ldrge    r0, [r1, r3]              \n"
                   "strge    r0, [r2, r3]              \n"
                   "bge    .L_loop0_0                  \n"

                   "adds    r4, #12                    \n"
                   "b    .L_loop0                      \n"

                   ".L_loop0_done:                     \n"
                   "nop                                \n");

    __asm volatile("ldr    r3, =__zero_table_start__   \n"
                   "ldr    r4, =__zero_table_end__     \n"

                   ".L_loop2:                          \n"
                   "cmp    r3, r4                      \n"
                   "bge    .L_loop2_done               \n"
                   "ldr    r1, [r3]                    \n"
                   "ldr    r2, [r3, #4]                \n"
                   "movs    r0, 0                      \n"

                   ".L_loop2_0:                        \n"
                   "subs    r2, #4                     \n"
                   "itt    ge                          \n"
                   "strge    r0, [r1, r2]              \n"
                   "bge    .L_loop2_0                  \n"

                   "adds    r3, #8                     \n"
                   "b    .L_loop2                      \n"
                   ".L_loop2_done:                     \n"
                   "nop                                \n");

    int32_t count = __init_array_end - __init_array_start;
    for (int32_t i = 0; i < count; i++)
    {
        __init_array_start[i]();
    }
}

