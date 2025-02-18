/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef __RM_NX_CRYPTO_H
 #define __RM_NX_CRYPTO_H

 #ifdef __cplusplus
extern "C"
{
 #endif

 #include "rm_netx_secure_crypto_cfg.h"
 #ifndef NX_CRYPTO_STANDALONE_ENABLE
  #include "nx_secure_user.h"
 #endif
 #include "common/nx_crypto.h"

 #ifdef __cplusplus
}
 #endif
#endif
