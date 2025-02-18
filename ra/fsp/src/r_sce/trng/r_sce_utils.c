/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
#include "bsp_api.h"
#include "hw_sce_private.h"

/*******************************************************************************************************************//**
 * Initialize the crypto engine
 * @retval FSP_SUCCESS      The operation completed successfully.
 **********************************************************************************************************************/

fsp_err_t HW_SCE_McuSpecificInit (void)
{
    // power on the SCE module
    HW_SCE_PowerOn();

    return FSP_SUCCESS;
}
