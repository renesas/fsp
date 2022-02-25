#include "bootutil/image.h"
#include "bootutil/bootutil.h"

#ifndef RM_MCUBOOT_PORT_H
 #define RM_MCUBOOT_PORT_H

 #ifdef __cplusplus
extern "C" {
 #endif

void RM_MCUBOOT_PORT_BootApp(struct boot_rsp * rsp);

 #ifdef __cplusplus
}
 #endif

#endif
