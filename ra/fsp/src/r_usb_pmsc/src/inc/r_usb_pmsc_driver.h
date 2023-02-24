/***********************************************************************************************************************
 * Copyright [2020-2023] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software and documentation are supplied by Renesas Electronics America Inc. and may only be used with products
 * of Renesas Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.  Renesas products are
 * sold pursuant to Renesas terms and conditions of sale.  Purchasers are solely responsible for the selection and use
 * of Renesas products and Renesas assumes no liability.  No license, express or implied, to any intellectual property
 * right is granted by Renesas. This software is protected under all applicable laws, including copyright laws. Renesas
 * reserves the right to change or discontinue this software and/or this documentation. THE SOFTWARE AND DOCUMENTATION
 * IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND TO THE FULLEST EXTENT
 * PERMISSIBLE UNDER APPLICABLE LAW, DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY, INCLUDING WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE SOFTWARE OR
 * DOCUMENTATION.  RENESAS SHALL HAVE NO LIABILITY ARISING OUT OF ANY SECURITY VULNERABILITY OR BREACH.  TO THE MAXIMUM
 * EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE OR DOCUMENTATION
 * (OR ANY PERSON OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER, INCLUDING,
 * WITHOUT LIMITATION, ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES; ANY LOST PROFITS,
 * OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF THE POSSIBILITY
 * OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS.
 **********************************************************************************************************************/

#ifndef R_USB_MEDIA_DRIVER_IF_H        /* Multiple inclusion prevention */
 #define R_USB_MEDIA_DRIVER_IF_H

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 ***********************************************************************************************************************/
 #include <stdint.h>
 #include <stdbool.h>

 #ifdef __cplusplus
extern "C" {
 #endif

/***********************************************************************************************************************
 * Macro definitions
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 ***********************************************************************************************************************/

/* Return values for functions */

/*
 * Definition of media driver function pointer types.
 * The media driver API interfaces to the specific media device driver functions through an abstraction layer.
 * Therefore each of the API functions has a corresponding type-defined type that consists of a pointer to a function
 * with a matching parameter list.
 */
typedef enum
{
    /* Generic ioctl command (defined for compatibility with FatFs) */
    USB_MEDIA_IOCTL_SYNC                   = 0, /* Flush media write cache. */
    USB_MEDIA_IOCTL_GET_NUM_BLOCKS         = 1, /* For use un calculating media size. */
    USB_MEDIA_IOCTL_GET_SECTOR_SIZE        = 2, /* Get sector size (for multiple sector size. (_MAX_SS >= 1024)) */
    USB_MEDIA_IOCTL_GET_BLOCK_SIZE         = 3, /* Get number of byes per block. */
    USB_MEDIA_IOCTL_CTRL_ERASE_SECTOR      = 4, /* Force erased a sector group. (for only _USE_ERASE) */
    USB_MEDIA_IOCTL_GET_WRITE_PROTECT_INFO = 5, /* Get write protect sinfo. */

/* Add more IOCTL commands starting below here. */
} usb_ioctl_cmd_t;

/* Media driver Data Structure */

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/
extern uint32_t      g_media_total_sector;
extern const uint8_t g_media_boot_sector[];
extern const uint8_t g_usb_pmsc_table1[];
extern const uint8_t g_usb_pmsc_rootdir[];

/******************************************************************************
 * Exported global functions (to be accessed by other files)
 ******************************************************************************/

/* The R_USB_media_initialize() function initializes data structures and variables that are used by the target media device
 * to support its operation for the first time.
 */
fsp_err_t r_usb_pmsc_media_initialize(void const * p_context);

/* The R_USB_media_close() function initializes the hardware registers for peripherals used by the media driver and leaves
 * the media device ready for communications.
 */
fsp_err_t r_usb_pmsc_media_close(void);

/* The R_USB_media_read() function reads one or more blocks of data from the selected media device and places it into
 * a buffer provided by the caller.
 */
fsp_err_t r_usb_pmsc_media_read(uint8_t * const p_rbuffer,           /* Pointer to read data buffer */
                                uint32_t const  start_block,         /* Start block number */
                                uint8_t const   block_count);        /* Number of blocks to read */

/* The R_USB_media_write() function writes one or more blocks of data to the selected media device from a source buffer
 * provided by the caller.
 */
fsp_err_t r_usb_pmsc_media_write(uint8_t const * const p_wbuffer,    /* Pointer to write data buffer */
                                 uint32_t const        start_block,  /* Start block number */
                                 uint8_t const         block_count); /* Number of blocks to write */

/* The R_USB_media_ioctl() function provides a generalized means to pass special command
 * and control instructions to the media driver, and for the driver to return information.
 */
void r_usb_pmsc_media_ioctl(usb_ioctl_cmd_t ioctl_cmd,               /* Control command code */
                            uint32_t      * ioctl_data);             /* Data transfer buffer */

 #ifdef __cplusplus
}
 #endif

#endif                                 /* R_USB_MEDIA_DRIVER_IF_H */
