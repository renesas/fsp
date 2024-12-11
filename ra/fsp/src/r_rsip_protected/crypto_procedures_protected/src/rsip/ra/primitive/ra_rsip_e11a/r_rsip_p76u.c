/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
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

void r_rsip_p76u (const uint32_t InData_PaddedMsg[], uint32_t MAX_CNT)
{
    r_rsip_func000(InData_PaddedMsg, MAX_CNT);
    r_rsip_func101(bswap_32big(0xb5be4530U), bswap_32big(0x9f7cceaeU), bswap_32big(0x964899f8U), bswap_32big(0xcecd2777U));
}
