/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef RM_TFM_PORT_H
#define RM_TFM_PORT_H

#include "tfm_common_config.h"
#include "tfm_arch.h"
#include "system_core_init.h"
#include "mbedtls/platform.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

extern void tfm_main(void);

extern void R_BSP_WarmStart(bsp_warm_start_event_t event);

/** Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 /* RM_TFM_PORT_H */
