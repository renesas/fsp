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
/** NetX Component                                                        */
/**                                                                       */
/**   Ethernet driver for RX65N Cloud Kit family of microprocessors       */
/**                                                                       */
/**************************************************************************/
/**************************************************************************/
/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef RM_NETXDUO_WIFI_H
 #define RM_NETXDUO_WIFI_H

 #ifdef   __cplusplus

/* Yes, C++ compiler is present.  Use standard C.  */
extern   "C" {
 #endif

 #include "rm_wifi_onchip_silex.h"
 #include "nx_api.h"

/* Define global driver entry function. */

VOID rm_netxduo_wifi(NX_IP_DRIVER * driver_req_ptr);

 #ifdef   __cplusplus

/* Yes, C++ compiler is present.  Use standard C.  */
}
 #endif
#endif
