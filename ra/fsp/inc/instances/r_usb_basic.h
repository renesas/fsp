/***********************************************************************************************************************
 * Copyright [2019] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software is supplied by Renesas Electronics America Inc. and may only be used with products of Renesas
 * Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.  This software is protected under
 * all applicable laws, including copyright laws. Renesas reserves the right to change or discontinue this software.
 * THE SOFTWARE IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND TO THE FULLEST
 * EXTENT PERMISSIBLE UNDER APPLICABLE LAW,DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY, INCLUDING
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE SOFTWARE.
 * TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE
 * (OR ANY PERSON OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER, INCLUDING,
 * WITHOUT LIMITATION, ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES; ANY LOST PROFITS,
 * OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF THE POSSIBILITY
 * OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS.
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @addtogroup USB USB
 * @{
 **********************************************************************************************************************/

#ifndef R_USB_H
#define R_USB_H

#include "bsp_api.h"
#include "r_usb_basic_cfg.h"
#include "r_usb_basic_api.h"


/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define USB_CODE_VERSION_MAJOR    (1U)
#define USB_CODE_VERSION_MINOR    (0U)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/
/** ICU private control block. DO NOT MODIFY.  Initialization occurs when R_ICU_ExternalIrqOpen is called. */
typedef struct st_usb_instance_ctrl
{
	uint8_t         module_number;   ///< USB module number (USB_IP0/USB_IP1)
    uint8_t         device_address;  ///< USB device address
    uint8_t         pipe;            ///< USB pipe number
    usb_class_t     type;            ///< USB device class etc
    uint16_t        status;          ///< USB device state etc
    usb_status_t    event;           ///< USB event
    uint32_t        data_size;       ///< Read data size
    usb_setup_t     setup;           ///< usb_setup_t structure area
    void            *p_data;         ///< Other information
    usb_cfg_t const *p_usb_cfg;
} usb_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const usb_api_t g_usb_on_usb;

/** @endcond */

/**********************************************************************************************************************
 * Public Function Prototypes
 **********************************************************************************************************************/
fsp_err_t    R_USB_Open(usb_ctrl_t * const p_api_ctrl, usb_cfg_t const * const cfg, usb_instance_transfer_t * p_api_trans);

fsp_err_t    R_USB_Close (usb_ctrl_t * const p_api_ctrl, usb_instance_transfer_t * p_api_trans);

fsp_err_t    R_USB_Read (usb_ctrl_t * const p_api_ctrl, uint8_t *p_buf, uint32_t size, usb_instance_transfer_t * p_api_trans);

fsp_err_t    R_USB_Write (usb_ctrl_t * const p_api_ctrl, uint8_t *p_buf, uint32_t size, usb_instance_transfer_t * p_api_trans);

fsp_err_t    R_USB_Stop (usb_ctrl_t * const p_api_ctrl, usb_transfer_t type, usb_instance_transfer_t * p_api_trans);

fsp_err_t    R_USB_Suspend (usb_ctrl_t * const p_api_ctrl, usb_instance_transfer_t * p_api_trans);

fsp_err_t    R_USB_Resume (usb_ctrl_t * const p_api_ctrl, usb_instance_transfer_t * p_api_trans);

fsp_err_t    R_USB_VbusSet (usb_ctrl_t * const p_api_ctrl, uint16_t state, usb_instance_transfer_t * p_api_trans);

fsp_err_t    R_USB_InfoGet (usb_ctrl_t * const p_api_ctrl, usb_info_t *p_info);

fsp_err_t    R_USB_PipeRead (usb_ctrl_t * const p_api_ctrl, uint8_t *p_buf, uint32_t size, usb_instance_transfer_t * p_api_trans);

fsp_err_t    R_USB_PipeWrite (usb_ctrl_t * const p_api_ctrl, uint8_t *p_buf, uint32_t size, usb_instance_transfer_t * p_api_trans);

fsp_err_t    R_USB_PipeStop (usb_ctrl_t * const p_api_ctrl, usb_instance_transfer_t * p_api_trans);

fsp_err_t    R_USB_UsedPipesGet (usb_ctrl_t * const p_api_ctrl, uint16_t *p_pipe);

fsp_err_t    R_USB_PipeInfoGet (usb_ctrl_t * const p_api_ctrl, usb_pipe_t *p_info);

fsp_err_t    R_USB_PullUp(uint8_t state);

#if (USB_CFG_RTOS_USE == USB_CFG_DISABLE)
fsp_err_t    R_USB_EventGet (usb_ctrl_t * const p_api_ctrl, usb_status_t *event);
#endif /* #if (USB_CFG_RTOS_USE == USB_CFG_DISABLE) */

fsp_err_t    R_USB_VersionGet (fsp_version_t * const p_version);

#if (USB_CFG_RTOS_USE == USB_CFG_ENABLE)
void         R_USB_Callback (usb_callback_t * p_callback);
#endif /* #if (USB_CFG_RTOS_USE == USB_CFG_ENABLE) */

fsp_err_t    R_USB_ModuleNumberGet(usb_ctrl_t * const p_api_ctrl, uint8_t *module_number);

fsp_err_t    R_USB_ClassTypeGet(usb_ctrl_t * const p_api_ctrl, usb_class_t *class_type);

fsp_err_t    R_USB_DeviceAddressGet(usb_ctrl_t * const p_api_ctrl, uint8_t *device_address);

fsp_err_t    R_USB_PipeNumberGet(usb_ctrl_t * const p_api_ctrl, uint8_t *pipe_number);

fsp_err_t    R_USB_DeviceStateGet(usb_ctrl_t * const p_api_ctrl, uint16_t *state);

fsp_err_t    R_USB_DataSizeGet(usb_ctrl_t * const p_api_ctrl, uint32_t *data_size);

fsp_err_t    R_USB_SetupGet(usb_ctrl_t * const p_api_ctrl, usb_setup_t *setup);


/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // R_USB_H

/*******************************************************************************************************************//**
 * @} (end addtogroup USB)
 **********************************************************************************************************************/
