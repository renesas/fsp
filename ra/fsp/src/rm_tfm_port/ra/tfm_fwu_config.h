#ifndef __FWU_CONFIG_H__
#define __FWU_CONFIG_H__

/* This file contains device specific configurations in FWU partition based
 * on MCUboot.
 */

/* Components if the device. When porting a specific bootloader to FWU partition,
 * the bootloader specific image types can be defined here.
 */
#if MCUBOOT_IMAGE_NUMBER > 1
#define FWU_COMPONENT_ID_SECURE           0x00U
#define FWU_COMPONENT_ID_NONSECURE        0x01U
#else
#define FWU_COMPONENT_ID_FULL             0x00U
#endif
#define FWU_COMPONENT_NUMBER              MCUBOOT_IMAGE_NUMBER

/* The maximum size of an image digest in bytes. This is dependent
 * on the hash algorithm used.
 */
#define TFM_FWU_MAX_DIGEST_SIZE              32

/* The maximum permitted size for block in psa_fwu_write(), in bytes. */
#define TFM_CONFIG_FWU_MAX_WRITE_SIZE        1024

/* The maximum permitted size for manifest in psa_fwu_start(), in bytes. */
#define TFM_CONFIG_FWU_MAX_MANIFEST_SIZE     0


#endif /* __FWU_CONFIG_H__ */
