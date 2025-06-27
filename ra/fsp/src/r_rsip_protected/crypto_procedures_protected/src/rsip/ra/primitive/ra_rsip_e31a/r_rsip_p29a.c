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

void r_rsip_p29a (const uint32_t InData_DataA[], uint32_t MAX_CNT)
{
    r_rsip_func430(InData_DataA, MAX_CNT);

    r_rsip_func101(bswap_32big(0x2346bd10U),
                   bswap_32big(0xa8b5a390U),
                   bswap_32big(0x5c821909U),
                   bswap_32big(0x56f62e49U));
}
