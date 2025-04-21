/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_rsip_primitive.h"
#include "r_rsip_reg.h"
#include "r_rsip_util.h"

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

void r_rsip_pdcu (const uint32_t InData_PaddedMsg[], uint32_t MAX_CNT)
{
    r_rsip_func000(InData_PaddedMsg, MAX_CNT);
    r_rsip_func101(bswap_32big(0x52cc5c35U), bswap_32big(0x2d523679U), bswap_32big(0x560361e9U), bswap_32big(0x99a5c085U));
}
