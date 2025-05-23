/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * File Name    : bsp_init.c
 * Description  : This module calls any initialization code specific to this BSP.
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @addtogroup BOARD_EK_RA6M2_INIT
 *
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include "bsp_api.h"

#if defined(BOARD_RA6M2_EK)

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global variables (to be accessed by other files)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables and functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief      Performs any initialization specific to this BSP.
 *
 * @param[in]  p_args         Pointer to arguments of the user's choice.
 **********************************************************************************************************************/
void bsp_init (void * p_args)
{
    FSP_PARAMETER_NOT_USED(p_args);
}

#endif

/** @} (end addtogroup BOARD_EK_RA6M2_INIT) */
