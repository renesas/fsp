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

void r_rsip_p32a (const uint32_t InData_DataA[], uint32_t MAX_CNT)
{
    r_rsip_func430(InData_DataA, MAX_CNT);

    r_rsip_func101(bswap_32big(0x303639bdU),
                   bswap_32big(0x59d3132eU),
                   bswap_32big(0x0542eebeU),
                   bswap_32big(0x0bbc9562U));
}
