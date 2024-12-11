/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/**********************************************************************************************************************
 * File Name    : r_drw_base.h
 * Description  : D/AVE D1 low-level driver function header file.
 **********************************************************************************************************************/

#ifndef DRW_BASE_H
#define DRW_BASE_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "dave_base.h"

/** Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/
typedef long         d1_long_t;
typedef int          d1_int_t;
typedef unsigned int d1_uint_t;

/** Device handle type definition for FSP implementation. */
typedef struct _d1_device_flex
{
    volatile uint32_t * pp_dlist_indirect_start; /* Display list start address */
    int32_t             dlist_indirect_enable;   /* Set to 1 when supporting lists of dlist addresses */
} d1_device_flex;

d1_int_t d1_initirq_intern(d1_device_flex * handle);
d1_int_t d1_shutdownirq_intern(d1_device_flex * handle);

/** Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
