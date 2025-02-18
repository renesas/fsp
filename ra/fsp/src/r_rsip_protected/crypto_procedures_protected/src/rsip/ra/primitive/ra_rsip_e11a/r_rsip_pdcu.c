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
    r_rsip_func101(bswap_32big(0xb07f8862U), bswap_32big(0x0d2c9451U), bswap_32big(0x2bd5ec7cU), bswap_32big(0x752a67adU));
}
