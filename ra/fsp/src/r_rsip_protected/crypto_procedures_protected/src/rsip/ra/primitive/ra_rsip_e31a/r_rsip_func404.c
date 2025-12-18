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
#include "r_rsip_sub_func.h"

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

RSIP_PRV_PRIMITIVE_FUNC

void r_rsip_func404 (void)
{
    r_rsip_func_sub001(0x007d005fU, 0x00230005U, 0x04040002U);

    r_rsip_func_sub001(0x00870023U, 0x00820000U, 0x0404000aU);
    r_rsip_func_sub001(0x00820023U, 0x006e0005U, 0x04040002U);

    r_rsip_func_sub001(0x00730055U, 0x002d0005U, 0x04040002U);

    r_rsip_func_sub001(0x0078005aU, 0x00320005U, 0x04040002U);

    r_rsip_func_sub001(0x002d0014U, 0x00370005U, 0x04040002U);

    r_rsip_func_sub001(0x00320037U, 0x00280005U, 0x04040002U);

    r_rsip_func_sub001(0x0028006eU, 0x00370005U, 0x04040006U);

    r_rsip_func_sub001(0x0028006eU, 0x003c0005U, 0x04040005U);

    r_rsip_func_sub001(0x003c0037U, 0x006e0005U, 0x04040002U);

    r_rsip_func_sub001(0x003c0023U, 0x00640005U, 0x04040002U);

    r_rsip_func_sub001(0x002d000fU, 0x00280005U, 0x04040002U);

    r_rsip_func_sub001(0x00280032U, 0x003c0005U, 0x04040006U);

    r_rsip_func_sub001(0x003c0064U, 0x00690005U, 0x04040002U);

    r_rsip_func_sub001(0x00370023U, 0x00280005U, 0x04040002U);

    r_rsip_func_sub001(0x005a0055U, 0x00230005U, 0x04040005U);

    r_rsip_func_sub001(0x00780073U, 0x00370005U, 0x04040005U);

    r_rsip_func_sub001(0x00370023U, 0x003c0005U, 0x04040002U);

    r_rsip_func_sub001(0x002d003cU, 0x00230005U, 0x04040006U);

    r_rsip_func_sub001(0x00320023U, 0x00370005U, 0x04040006U);

    r_rsip_func_sub001(0x00370028U, 0x00640005U, 0x04040002U);
}
