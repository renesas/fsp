/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "bootutil/image.h"
#include "bootutil/bootutil.h"

#ifndef RM_MCUBOOT_PORT_H
 #define RM_MCUBOOT_PORT_H

 #ifdef __cplusplus
extern "C" {
 #endif

void RM_MCUBOOT_PORT_BootApp(struct boot_rsp * rsp);

 #ifdef __cplusplus
}
 #endif

#endif
