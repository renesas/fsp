/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef BSP_SDRAM_H
#define BSP_SDRAM_H

#if 0 != BSP_FEATURE_SDRAM_START_ADDRESS

/** Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/
void R_BSP_SdramInit(bool init_memory);
void R_BSP_SdramSelfRefreshEnable(void);
void R_BSP_SdramSelfRefreshDisable(void);

 #if 1U == BSP_CFG_CLOCKS_SECURE && (BSP_TZ_SECURE_BUILD || BSP_TZ_NONSECURE_BUILD)
BSP_CMSE_NONSECURE_ENTRY void bsp_sdram_secure_sdclk_enable(void);

 #endif

/** Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER
#endif
#endif
