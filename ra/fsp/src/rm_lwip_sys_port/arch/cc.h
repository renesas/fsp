#ifndef LWIP_HDR_CC_H
#define LWIP_HDR_CC_H

#include "bsp_api.h"

/* Platform specific assertion handling. */
#ifndef LWIP_PLATFORM_ASSERT
 #define LWIP_PLATFORM_ASSERT(x)    do {FSP_LOG_PRINT(x); BSP_CFG_HANDLE_UNRECOVERABLE_ERROR(0);} while (0)
#endif

/* Support packed structures for IAR. */
#if defined(__ICCARM__)
 #define PACK_STRUCT_BEGIN    __packed
#endif

#endif                                 /* LWIP_HDR_CC_H */
