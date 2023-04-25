/*
 * Copyright (c) 2021-2022, Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
/***********{{utilities.donotedit_warning}}***********/

#ifndef __CONFIG_IMPL_H__
#define __CONFIG_IMPL_H__

#include "config_tfm.h"

/* Backends */
/* Backends */
#define CONFIG_TFM_SPM_BACKEND_IPC                               1
#define CONFIG_TFM_SPM_BACKEND_SFN                               0

/* API calls */
#define CONFIG_TFM_PSA_API_SFN_CALL                              0
#define CONFIG_TFM_PSA_API_CROSS_CALL                            0
#define CONFIG_TFM_PSA_API_SUPERVISOR_CALL                       1

#define CONFIG_TFM_CONNECTION_BASED_SERVICE_API                  1
#define CONFIG_TFM_MMIO_REGION_ENABLE                            0
#define CONFIG_TFM_FLIH_API                                      0
#define CONFIG_TFM_SLIH_API                                      1

#if CONFIG_TFM_SPM_BACKEND_IPC == 1
/* Trustzone NS agent working stack size. */
#if defined(TFM_FIH_PROFILE_ON) && TFM_LVL == 1
#define CONFIG_TFM_NS_AGENT_TZ_STACK_SIZE    1256
#else
#define CONFIG_TFM_NS_AGENT_TZ_STACK_SIZE    1024
#endif

/* SPM re-uses Trustzone NS agent stack. */
#define CONFIG_TFM_SPM_THREAD_STACK_SIZE                             \
            CONFIG_TFM_NS_AGENT_TZ_STACK_SIZE

#elif CONFIG_TFM_SPM_BACKEND_SFN == 1

#define CONFIG_TFM_NS_AGENT_TZ_STK_SIZE_SHIFT_FACTOR             1
#define CONFIG_TFM_NS_AGENT_TZ_STACK_SIZE                         \
    (((0x6220 >> CONFIG_TFM_NS_AGENT_TZ_STK_SIZE_SHIFT_FACTOR) + 0x7) & (~0x7))

#endif /* CONFIG_TFM_SPM_BACKEND_IPC == 1 */

#endif /* __CONFIG_IMPL_H__ */

