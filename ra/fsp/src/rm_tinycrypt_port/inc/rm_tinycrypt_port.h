/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef RM_TINYCRYPT_PORT_H
 #define RM_TINYCRYPT_PORT_H

 #include <string.h>
 #include "bsp_api.h"
 #include "hw_sce_private.h"
 #include "hw_sce_trng_private.h"

/*******************************************************************************************************************/ /**
 * @addtogroup RM_TINYCRYPT_PORT
 * @{
 **********************************************************************************************************************/

 #ifdef __cplusplus
extern "C"
{
 #endif

fsp_err_t RM_TINCYRYPT_PORT_TRNG_Read(uint8_t * const p_rngbuf, uint32_t num_req_bytes);
fsp_err_t RM_TINCYRYPT_PORT_Init(void);

 #ifdef __cplusplus
}
 #endif

/*******************************************************************************************************************/ /**
 * @} (end addtogroup RM_TINYCRYPT_PORT)
 **********************************************************************************************************************/
#endif                                 /* RM_TINYCRYPT_PORT_H */
