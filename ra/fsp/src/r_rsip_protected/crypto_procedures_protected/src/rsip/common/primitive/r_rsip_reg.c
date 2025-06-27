/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_rsip_reg.h"

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/

#if defined(__GNUC__)
uintptr_t const gs_rsip_addr_0000h = RSIP_PRV_ADDR_VAL_0000H;
uintptr_t const gs_rsip_addr_1000h = RSIP_PRV_ADDR_VAL_1000H;
uintptr_t const gs_rsip_addr_2000h = RSIP_PRV_ADDR_VAL_2000H;

uintptr_t const gs_rsip_addr_1420h = RSIP_PRV_ADDR_VAL_1420H;
uintptr_t const gs_rsip_addr_1440h = RSIP_PRV_ADDR_VAL_1440H;
uintptr_t const gs_rsip_addr_1600h = RSIP_PRV_ADDR_VAL_1600H;
#endif                                 /* defined(__GNUC__) */
