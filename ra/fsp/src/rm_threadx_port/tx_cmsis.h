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

/* Workarounds for LLVM and CM85 are already defined in renesas.h. */
#include "bsp_api.h"

#if defined(__GNUC__) && !defined(__ARMCC_VERSION)

/* Restore warning settings for 'sign-conversion' to as specified on command line. */
 #pragma GCC diagnostic pop
#endif

#endif                                 /* TX_CMSIS_H */
