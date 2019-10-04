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

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "bsp_cfg.h"

#include <r_usb_basic.h>
#include <r_usb_basic_api.h>
#include <string.h>

#include "src/driver/inc/r_usb_typedef.h"
#include "src/driver/inc/r_usb_extern.h"
#include "src/hw/inc/r_usb_bitdefine.h"
#include "src/hw/inc/r_usb_reg_access.h"


#if defined(USB_CFG_HCDC_USE)
#include "r_usb_hcdc_if.h"
#endif /* defined(USB_CFG_HCDC_USE) */

#if defined(USB_CFG_HHID_USE)
#include "r_usb_hhid_if.h"
#endif /* defined(USB_CFG_HHID_USE) */

#if defined(USB_CFG_HMSC_USE)
#include "r_usb_hmsc_api.h"
#include "../r_usb_hmsc/src/inc/r_usb_hmsc_driver.h"
#endif /* defined(USB_CFG_HMSC_USE) */

#if defined(USB_CFG_HVND_USE)
#include "r_usb_vendor.h"
#endif /* defined(USB_CFG_HVND_USE) */

#if defined(USB_CFG_PHID_USE)
#include "r_usb_phid_if.h"
#endif /* defined(USB_CFG_PHID_USE) */

#if defined(USB_CFG_PCDC_USE)
#include "r_usb_pcdc_api.h"
#include "r_usb_pcdc_cfg.h"
#endif /* defined(USB_CFG_PCDC_USE) */


/******************************************************************************
 Exported global variables (to be accessed by other files)
******************************************************************************/
#if (BSP_CFG_RTOS == 0)
    usb_event_t     g_usb_cstd_event;
    uint16_t        g_usb_change_device_state[USB_NUM_USBIP];
#else /*(BSP_CFG_RTOS == 0)*/
#include "src/driver/inc/r_usb_cstd_rtos.h"
    usb_instance_ctrl_t    g_usb_cstd_event[USB_EVENT_MAX];
    extern TaskHandle_t    g_hcd_tsk_hdl;
	extern TaskHandle_t    g_mgr_tsk_hdl;
	extern TaskHandle_t    g_hub_tsk_hdl;
#if defined(USB_CFG_HMSC_USE)
    extern TaskHandle_t    readtask_hdl;
#endif /* defined(USB_CFG_HMSC_USE) */
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
	extern TaskHandle_t    g_pcd_tsk_hdl;
#endif /* ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI) */
#if defined(USB_CFG_PMSC_USE)
	extern TaskHandle_t    g_pmsc_tsk_hdl;
#endif /* defined(USB_CFG_PMSC_USE) */
    usb_callback_t  *g_usb_apl_callback;

#endif /*(BSP_CFG_RTOS == 0)*/

#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
usb_utr_t       g_usb_hdata[USB_NUM_USBIP][USB_MAXPIPE_NUM + 1];

#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */

#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
usb_utr_t       g_usb_pdata[USB_MAXPIPE_NUM + 1];

#endif  /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI */

volatile uint16_t        g_usb_usbmode;
volatile uint16_t        g_usb_open_class[USB_NUM_USBIP];

/******************************************************************************
 Private global variables and functions
******************************************************************************/
static uint8_t  is_init[USB_NUM_USBIP] =
{
    USB_NO,
#if USB_NUM_USBIP == 2
    USB_NO,
#endif
};

#if (BSP_CFG_RTOS == 2)

#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
static uint8_t  gs_usb_suspend_ing[USB_NUM_USBIP] =
{
    USB_NO,
#if USB_NUM_USBIP == 2
    USB_NO,
#endif
};
#endif /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */

static uint8_t  gs_usb_resume_ing[USB_NUM_USBIP] =
{
    USB_NO,
#if USB_NUM_USBIP == 2
    USB_NO,
#endif
};
#endif /*(BSP_CFG_RTOS == 2)*/

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/
/** Version data structure used by error logger macro. */
#if BSP_CFG_ERROR_LOG != 0
const char g_module_name[] = "r_usb";
#endif

const fsp_version_t g_usb_version =
{
    .api_version_minor  = USB_API_VERSION_MINOR,
    .api_version_major  = USB_API_VERSION_MAJOR,
    .code_version_major = USB_CODE_VERSION_MAJOR,
    .code_version_minor = USB_CODE_VERSION_MINOR
};

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/

const usb_api_t g_usb_on_usb =
{
    .open             = R_USB_Open,
    .close            = R_USB_Close,
    .read             = R_USB_Read,
    .write            = R_USB_Write,
    .stop             = R_USB_Stop,
    .suspend          = R_USB_Suspend,
    .resume           = R_USB_Resume,
    .vbusSet          = R_USB_VbusSet,
	.infoGet          = R_USB_InfoGet,
	.pipeRead         = R_USB_PipeRead,
	.pipeWrite        = R_USB_PipeWrite,
	.pipeStop         = R_USB_PipeStop,
	.usedPipesGet     = R_USB_UsedPipesGet,
	.pipeInfoGet      = R_USB_PipeInfoGet,
	.versionGet       = R_USB_VersionGet,
#if (BSP_CFG_RTOS == 0)
	.eventGet         = R_USB_EventGet,
#endif
	.pullup           = R_USB_PullUp,
	.modulenumberget  = R_USB_ModuleNumberGet,
	.classtypeget     = R_USB_ClassTypeGet,
	.deviceaddressget = R_USB_DeviceAddressGet,
	.pipenumberget    = R_USB_PipeNumberGet,
	.devicestateget   = R_USB_DeviceStateGet,
	.datasizeget      = R_USB_DataSizeGet,
	.setupget         = R_USB_SetupGet,
};


/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @addtogroup USB USB
 * @{
 **********************************************************************************************************************/

/*************************************************************************//**
 * @brief Returns the version of this module. 
 *
 * The version number is encoded such
 * that the top two bytes are the major version number and the bottom
 * two bytes are the minor version number.
 *
 * @retval FSP_SUCCESS        Success.
 * @retval FSP_ERR_ASSERTION  Failed in acquiring version information.
 ******************************************************************************/
fsp_err_t R_USB_VersionGet (fsp_version_t * const p_version)
{
#if USB_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_version);
#endif

    p_version->version_id = g_usb_version.version_id;

    return FSP_SUCCESS;
}

#if (BSP_CFG_RTOS == 0)
/**************************************************************************//**
 * @brief Obtains completed USB related events.
 * 
 * In USB host mode, the device address value of the USB device that completed
 * an event is specified in the usb_ctrl_t structure member (address) specified
 * by the event's argument.
 * In USB peripheral mode, USB_NULL is specified in member (address).
 *
 * @retval FSP_SUCCESS        Event Get Success.
 ******************************************************************************/
fsp_err_t R_USB_EventGet(usb_ctrl_t * const p_api_ctrl, usb_status_t *event)
{
	(*event) = USB_STATUS_NONE;
    usb_instance_ctrl_t * p_ctrl = (usb_instance_ctrl_t *) p_api_ctrl;

    usb_cstd_usb_task();
    if ( g_usb_cstd_event.write_pointer != g_usb_cstd_event.read_pointer )
    {
        *p_ctrl = g_usb_cstd_event.ctrl[g_usb_cstd_event.read_pointer];
        (*event) = g_usb_cstd_event.code[g_usb_cstd_event.read_pointer];
        g_usb_cstd_event.read_pointer++;
        if (g_usb_cstd_event.read_pointer >= USB_EVENT_MAX)
        {
            g_usb_cstd_event.read_pointer = 0;
        }
    }
    return FSP_SUCCESS;
}  /* End of function R_USB_EventGet() */
#endif

#if  (BSP_CFG_RTOS == 2)
/******************************************************************************
Function Name   : R_USB_Callback
Description     : Registration of the callback function
Arguments       : usb_callback_t    *p_callback : Pointer to the callback function for the application
Return value    : None
******************************************************************************/
void    R_USB_Callback(usb_callback_t *p_callback)
{
    g_usb_apl_callback = p_callback;
} /* End of function R_USB_Callback() */
#endif /* (BSP_CFG_RTOS == 2)*/

/**************************************************************************//**
 * @brief Applies power to the USB module specified in the argument (p_ctrl).
 *
 * @retval FSP_SUCCESS         Success in open.
 * @retval FSP_ERR_USB_BUSY    Specified USB module now in use.
 * @retval FSP_ERR_ASSERTION   Parameter error.
 ******************************************************************************/
fsp_err_t R_USB_Open( usb_ctrl_t * const p_api_ctrl, usb_cfg_t const * const p_cfg, usb_instance_transfer_t * p_api_trans)
{
    fsp_err_t   err = FSP_SUCCESS;
#if (BSP_CFG_RTOS == 2)
    usb_rtos_err_t os_err;
#endif

    usb_instance_ctrl_t * p_ctrl = (usb_instance_ctrl_t *) p_api_ctrl;

#if ( (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST )
    usb_utr_t   utr;
#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */

#if USB_CFG_PARAM_CHECKING_ENABLE == BSP_CFG_PARAM_CHECKING_ENABLE

    FSP_ASSERT(USB_NULL != p_api_ctrl)
    FSP_ASSERT(USB_NULL != p_api_trans)

    /* Argument Checking */
    FSP_ASSERT(!((USB_IP0 != p_api_trans->module_number) && (USB_IP1 != p_api_trans->module_number)))

    FSP_ASSERT(!((( USB_SPEED_HS != p_cfg->usb_speed ) && ( USB_SPEED_FS != p_cfg->usb_speed )) && ( USB_SPEED_LS != p_cfg->usb_speed )
            && (USB_HOST != p_cfg->usb_mode)))

#if defined(BSP_MCU_GROUP_RA2A1)
    FSP_ASSERT (USB_IP1 != p_api_trans->module_number)
#endif /* defined(BSP_MCU_GROUP_RA2A1) */

    switch (p_api_trans->type)
    {
        case USB_CLASS_PCDC:
        case USB_CLASS_PHID:
        case USB_CLASS_PVND:
        case USB_CLASS_PMSC:
        	FSP_ASSERT(USB_PERI == p_cfg->usb_mode)

			FSP_ASSERT(!((USB_SPEED_LS == p_cfg->usb_speed) || (USB_NULL == p_cfg->p_usb_reg)))

#if defined(BSP_MCU_GROUP_RA6M3)
 #if USB_IP0 == USB_CFG_USE_USBIP
            FSP_ASSERT(USB_SPEED_HS != p_cfg->usb_speed)
 #endif  /* USB_IP1 == USB_CFG_USE_USBIP */
#else   /* defined(BSP_MCU_GROUP_RA6M3) */
            FSP_ASSERT( USB_SPEED_HS != p_cfg->usb_speed )
#endif  /* defined(BSP_MCU_GROUP_RA6M3) */
        break;

        /* Host */
        case USB_CLASS_HCDC:
        case USB_CLASS_HHID:
        case USB_CLASS_HVND:
        case USB_CLASS_HMSC:
#if defined(BSP_MCU_GROUP_RA2A1)
            return FSP_ERR_ASSERTION;
#else  /* defined(BSP_MCU_GROUP_RA2A1) */
            FSP_ASSERT(USB_HOST == p_cfg->usb_mode)
#if defined(BSP_MCU_GROUP_RA6M3)
            FSP_ASSERT(!((USB_SPEED_HS == p_cfg->usb_speed) && (USB_IP1 != p_api_trans->module_number)))
#else  /* defined(BSP_MCU_GROUP_RA6M3) */
			FSP_ASSERT(USB_SPEED_HS != p_cfg->usb_speed )
#endif /* defined(BSP_MCU_GROUP_RA6M3) */
#endif  /* defined(BSP_MCU_GROUP_RA2A1) */
        break;

        default:
            return FSP_ERR_ASSERTION;
        break;
    }
#endif /* USB_CFG_PARAM_CHECKING_ENABLE == BSP_CFG_PARAM_CHECKING_ENABLE */

    p_ctrl->module_number = p_api_trans->module_number;
    p_ctrl->type = p_api_trans->type;
    p_ctrl->device_address = p_api_trans->device_address;
    p_ctrl->pipe = p_api_trans->pipe;
    p_ctrl->setup = p_api_trans->setup;
    p_ctrl->p_usb_cfg = p_cfg;

    if (USB_YES == is_init[p_ctrl->module_number])
    {
        return FSP_ERR_USB_BUSY;
    }

#if (BSP_CFG_RTOS == 2)
    os_err = usb_rtos_configuration();
    if (UsbRtos_Success != os_err)
    {
        return FSP_ERR_ASSERTION;
    }
#endif

#if USB_NUM_USBIP == 2
    if ((USB_NO == is_init[USB_IP0]) && (USB_NO == is_init[USB_IP1]))
    {
#endif /* USB_NUM_USBIP == 2 */

    memset((void *)&g_usb_cstd_event, 0, sizeof(g_usb_cstd_event));

#if USB_NUM_USBIP == 2
    }
#endif /* USB_NUM_USBIP == 2 */

    is_init[p_ctrl->module_number] = USB_YES;

    g_usb_open_class[p_ctrl->module_number] = 0;

#if (BSP_CFG_RTOS == 0)
    g_usb_change_device_state[p_ctrl->module_number] = 0;
#endif  /* (BSP_CFG_RTOS == 0) */

#if ( (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST )
    g_usb_hstd_use_pipe[p_ctrl->module_number] = 0;
    memset((void *)&g_usb_hdata[p_ctrl->module_number], 0, sizeof(usb_utr_t));
#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */

#if ( (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI )
    memset((void *)&g_usb_pdata, 0, ((USB_MAXPIPE_NUM+1) * sizeof(usb_utr_t)));
#endif  /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */

    if (USB_HOST == p_cfg->usb_mode)
    {
#if ( (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST )
        g_usb_usbmode = USB_HOST;

        utr.ip  = p_ctrl->module_number;
        utr.ipp = usb_hstd_get_usb_ip_adr( (uint16_t)p_ctrl->module_number  );    /* Get the USB IP base address. */

        err = usb_module_start( (uint8_t)utr.ip );
        if (FSP_SUCCESS == err)
        {
            /* USB driver initialization */
            usb_hdriver_init( &utr, p_cfg );

            /* Setting MCU(USB interrupt init) register */
            usb_cpu_usbint_init((uint8_t)utr.ip, p_cfg);

            /* Setting USB relation register  */
            hw_usb_hmodule_init(p_ctrl); /* MCU */

#if defined(USB_CFG_HHID_USE)
            if (USB_CLASS_HHID == p_ctrl->type)
            {
                hw_usb_hset_trnensel(&utr);
            }
#endif  /* defined(USB_CFG_HHID_USE) */

#if USB_CFG_TYPEC == USB_CFG_DISABLE
            usb_hstd_vbus_control(&utr, (uint16_t)USB_VBON);
#if USB_CFG_BC == USB_CFG_DISABLE
//            usb_cpu_delay_xms((uint16_t)100);    /* 100ms wait */

  #endif /*  USB_CFG_BC == USB_CFG_DISABLE */
#else   /*  USB_CFG_TYPEC == USB_CFG_DISABLE */
            usb_hstd_vbus_control(&utr, (uint16_t)USB_VBOFF);

#endif /*  USB_CFG_TYPEC == USB_CFG_DISABLE */
        }

#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }
    else
    {
#if ( (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI )
        g_usb_usbmode = USB_PERI;
        p_ctrl->module_number = USB_CFG_USE_USBIP;

        /* USB module start setting */
        err = usb_module_start(USB_CFG_USE_USBIP);
        if (FSP_SUCCESS == err)
        {
            /* USB driver initialization */
            usb_pdriver_init( p_ctrl, p_cfg );

            /* Setting MCU(USB interrupt init) register */
            usb_cpu_usbint_init(USB_CFG_USE_USBIP, p_cfg);

            /* Setting USB relation register  */
            hw_usb_pmodule_init();

#if defined(BSP_MCU_GROUP_RA6M3)
            if (USB_SPEED_HS == p_cfg->usb_speed)
            {
                hw_usb_set_hse(USB_NULL);
            }
#endif  /* defined(BSP_MCU_GROUP_RA6M3) */
            if ( USB_ATTACH == usb_pstd_chk_vbsts() )
            {
#if defined(BSP_MCU_GROUP_RA6M3)
                hw_usb_set_cnen();
#endif  /* defined(BSP_MCU_GROUP_RA6M3) */
                usb_cpu_delay_xms((uint16_t)10);
                hw_usb_pset_dprpu();
            }
        }
#endif  /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */
    }

    if (FSP_SUCCESS == err)
    {
        g_usb_open_class[p_ctrl->module_number] |= (uint16_t)(1 << p_ctrl->type);      /* Set USB Open device class */
        if (USB_CLASS_PCDC == p_ctrl->type)
        {
            g_usb_open_class[p_ctrl->module_number] |= (1 << USB_CLASS_PCDCC);   /* Set USB Open device class */
        }
        if (USB_CLASS_HCDC == p_ctrl->type)
        {
            g_usb_open_class[p_ctrl->module_number] |= (1 << USB_CLASS_HCDCC);   /* Set USB Open device class */
        }
    }

    return err;
}

/**************************************************************************//**
 * @brief Terminates power to the USB module specified in argument (p_ctrl).
 * USB0 module stops when USB_IP0 is specified to the member (module),
 * USB1 module stops when USB_IP1 is specified to the member (module).
 *
 * @retval FSP_SUCCESS           Success.
 * @retval FSP_ERR_USB_FAILED    The function could not be completed successfully.
 * @retval FSP_ERR_USB_NOT_OPEN  USB module is not open.
 * @retval FSP_ERR_ASSERTION     Parameter error.
 * @retval FSP_ERR_USB_PARAMETER USB IP type is wrong.
 ******************************************************************************/
fsp_err_t R_USB_Close(usb_ctrl_t * const p_api_ctrl, usb_instance_transfer_t * p_api_trans)
{
    fsp_err_t   ret_code;

    usb_instance_ctrl_t * p_ctrl = (usb_instance_ctrl_t *) p_api_ctrl;

#if ( (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST )
    usb_info_t  info;
    uint8_t    ip;
    uint8_t    dev_addr;
    usb_instance_ctrl_t  ctrl;
    usb_utr_t   utr;
    uint8_t     class_code = USB_IFCLS_CDC;

    info.class_type = 0;
    info.speed = 0;
#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */

#if USB_CFG_PARAM_CHECKING_ENABLE == BSP_CFG_PARAM_CHECKING_ENABLE

    FSP_ASSERT(USB_NULL != p_api_ctrl )

    FSP_ASSERT(USB_NULL != p_api_trans )

#endif /* USB_CFG_PARAM_CHECKING_ENABLE == BSP_CFG_PARAM_CHECKING_ENABLE */

#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
    if (USB_PERI == g_usb_usbmode)
    {
    	p_api_trans->module_number = USB_CFG_USE_USBIP;
    }
#endif  /* USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI */

#if USB_CFG_PARAM_CHECKING_ENABLE == BSP_CFG_PARAM_CHECKING_ENABLE

    /* Argument Checking */
    FSP_ASSERT(!((USB_IP0 != p_api_trans->module_number) && (USB_IP1 != p_api_trans->module_number)))

#if defined(BSP_BOARD_GROUP_RA2A1)
	FSP_ASSERT (USB_IP1 != p_api_trans->module_number)
#endif  /* #if defined(BSP_BOARD_GROUP_RA2A1) */

    if (USB_HOST == g_usb_usbmode)
    {
#if ( (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST )
        switch(p_api_trans->type)
        {
            case USB_CLASS_HCDC:
                class_code = (uint8_t)USB_IFCLS_CDC;
            break;

            case USB_CLASS_HHID:
                class_code = (uint8_t)USB_IFCLS_HID;
            break;

            case USB_CLASS_HMSC:
                class_code = (uint8_t)USB_IFCLS_MAS;
            break;

            case USB_CLASS_HVND:
                class_code = (uint8_t)USB_IFCLS_VEN;
            break;

            default:
                return FSP_ERR_ASSERTION;
            break;
        }
#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }
#endif  /* USB_CFG_PARAM_CHECKING_ENABLE == BSP_CFG_PARAM_CHECKING_ENABLE */

    p_ctrl->module_number = p_api_trans->module_number;
    p_ctrl->type = p_api_trans->type;
    p_ctrl->device_address = p_api_trans->device_address;
    p_ctrl->pipe = p_api_trans->pipe;
    p_ctrl->setup = p_api_trans->setup;

    ret_code = usb_module_stop(p_ctrl->module_number);
    if (FSP_SUCCESS == ret_code)
    {
        is_init[p_ctrl->module_number] = USB_NO;

        if (USB_HOST == g_usb_usbmode)
        {
#if ( (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST )
            utr.ip = p_ctrl->module_number;
            utr.ipp = usb_hstd_get_usb_ip_adr(utr.ip);

            usb_hstd_driver_release(&utr, class_code);

            /* WAIT_LOOP */
            for (ip =0; ip <USB_NUM_USBIP; ip++)
            {
                for (dev_addr =1; dev_addr< (USB_MAXDEVADDR + 1); dev_addr++)
                {
                    ctrl.module_number = ip;
                    ctrl.device_address = dev_addr;
                    ctrl.type = p_ctrl->type;
                    R_USB_InfoGet(&ctrl, &info);
                    if ((USB_NULL != info.speed) && (ctrl.type == info.class_type))
                    {
                        usb_hstd_clr_pipe_table (ip, dev_addr);
                    }
                }
            }
#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
        }
        else
        {
#if ( (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI )
        usb_pstd_driver_release();   /* Clear the information registered in the structure usb_pcdreg_t. */
        usb_pstd_clr_pipe_table();
#endif  /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI */
        }

        g_usb_open_class[p_ctrl->module_number] = (uint16_t)(g_usb_open_class[p_ctrl->module_number] & (~(1 << p_ctrl->type)));     /* Clear USB Open device class */

#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        if (USB_CLASS_PCDC == p_ctrl->type)
        {
            g_usb_open_class[p_ctrl->module_number] = (uint16_t)(g_usb_open_class[p_ctrl->module_number] & (~(1 << USB_CLASS_PCDCC)));    /* Clear USB Open device class */
        }
#endif  /* USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI */

#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        if (USB_CLASS_HCDC == p_ctrl->type)
        {
            g_usb_open_class[p_ctrl->module_number] = (uint16_t)(g_usb_open_class[p_ctrl->module_number] & (~(1 << USB_CLASS_HCDCC)));    /* Clear USB Open device class */
        }
#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }
    else
    {
        ret_code = FSP_ERR_USB_NOT_OPEN;
    }
#if (BSP_CFG_RTOS == 2)
    usb_rtos_delete();
#endif

    return ret_code;
}

/**************************************************************************//**
 * @brief Bulk/interrupt data transfer and control data transfer
 * 
 * 1. Bulk/interrupt data transfer
 *   Requests USB data read (bulk/interrupt transfer).
 *   The read data is stored in the area specified by argument (p_buf).
 *   After data read is completed, confirm the operation by checking the return value
 *   (USB_STATUS_READ_COMPLETE) of the R_USB_GetEvent function. The received data size is set in member
 *   (size) of the usb_ctrl_t structure. To figure out the size of the data when a read is complete,
 *   check the return value (USB_STATUS_READ_COMPLETE) of the R_USB_GetEvent function, and then
 *   refer to the member (size) of the usb_crtl_t structure.
 *
 * 2. Control data transfer
 *   The R_USB_Read function is used to receive data in the data stage and the
 *   R_USB_Write function is used to send data to the USB host.
 *
 * @retval FSP_SUCCESS           Successfully completed (Data read request completed).
 * @retval FSP_ERR_USB_FAILED    The function could not be completed successfully.
 * @retval FSP_ERR_USB_BUSY      Data receive request already in process for
 *                               USB device with same device address.
 * @retval FSP_ERR_ASSERTION     Parameter error.
 ******************************************************************************/
fsp_err_t R_USB_Read(usb_ctrl_t * const p_api_ctrl, uint8_t *p_buf, uint32_t size, usb_instance_transfer_t * p_api_trans)
{

    usb_info_t  info;
    usb_er_t    err;
    fsp_err_t   result = FSP_ERR_USB_FAILED;

    usb_instance_ctrl_t * p_ctrl = (usb_instance_ctrl_t *) p_api_ctrl;

#if USB_CFG_PARAM_CHECKING_ENABLE == BSP_CFG_PARAM_CHECKING_ENABLE

    FSP_ASSERT(USB_NULL != p_api_ctrl)

    FSP_ASSERT(USB_NULL != p_api_trans)

#endif /* USB_CFG_PARAM_CHECKING_ENABLE == BSP_CFG_PARAM_CHECKING_ENABLE */

#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
    if (USB_PERI == g_usb_usbmode)
    {
    	p_api_trans->module_number= USB_CFG_USE_USBIP;
    }
#endif  /* USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI */

#if USB_CFG_PARAM_CHECKING_ENABLE == BSP_CFG_PARAM_CHECKING_ENABLE

    FSP_ASSERT (!(((USB_NULL == p_buf)) || (USB_NULL == size)))

    /* Argument Checking */
    FSP_ASSERT (!((USB_IP0 != p_api_trans->module_number) && (USB_IP1 != p_api_trans->module_number) && ( USB_HOST == g_usb_usbmode)))

#if defined(BSP_BOARD_GROUP_RA2A1)
    FSP_ASSERT (USB_IP1 != p_api_trans->module_number)
#endif

	FSP_ASSERT(!((USB_CLASS_PCDCC == p_api_trans->type) || (USB_CLASS_PVND == p_api_trans->type)
                || (USB_CLASS_HVND == p_api_trans->type)|| (USB_CLASS_HMSC == p_api_trans->type)
                || (USB_CLASS_PMSC == p_api_trans->type)))

    if (USB_CLASS_REQUEST != p_api_trans->type)
    {
    	FSP_ASSERT (USB_NULL != (g_usb_open_class[p_api_trans->module_number] & (1 << p_api_trans->type))) /* Check USB Open device class */
    }

#endif  /* USB_CFG_PARAM_CHECKING_ENABLE == BSP_CFG_PARAM_CHECKING_ENABLE */

    p_ctrl->module_number = p_api_trans->module_number;
    p_ctrl->type = p_api_trans->type;
    p_ctrl->device_address = p_api_trans->device_address;
    p_ctrl->pipe = p_api_trans->pipe;
    p_ctrl->setup = p_api_trans->setup;

    (void)R_USB_InfoGet(p_ctrl, &info);
    if(USB_STATUS_CONFIGURED == info.device_status)
    {
        if (USB_CLASS_REQUEST == p_ctrl->type)
        {
            err = usb_ctrl_read( p_ctrl, p_buf, size );
        }
        else
        {
            err = usb_data_read( p_ctrl, p_buf, size );
        }

        if (USB_OK == err)
        {
        	result = FSP_SUCCESS;
        }
        else if (USB_QOVR == err)
        {
        	result = FSP_ERR_USB_BUSY;
        }
        else
        {
        	/* Noting */
        }
    }
    return result;
}

/**************************************************************************//**
 * @brief Bulk/Interrupt data transfer and control data transfer
 *
 * 1. Bulk/Interrupt data transfer
 *   Requests USB data write (bulk/interrupt transfer).
 *   Stores write data in area specified by argument (p_buf).
 *   Set the device class type in usb_ctrl_t structure member (type).
 *   Confirm after data write is completed by checking the return value (USB_STATUS_WRITE_COMPLETE)
 *   of the R_USB_GetEvent function.
 *   To request the transmission of a NULL packet, assign USB_NULL(0) to the third argument (size).
 *
 * 2. Control data transfer
 *   The R_USB_Read function is used to receive data in the data stage and
 *   the R_USB_Write function is used to send data to the USB host.
 *
 * @retval FSP_SUCCESS           Successfully completed. (Data write request completed)
 * @retval FSP_ERR_USB_FAILED    The function could not be completed successfully.
 * @retval FSP_ERR_USB_BUSY      Data write request already in process for
 *                               USB device with same device address.
 * @retval FSP_ERR_ASSERTION     Parameter error.
 ******************************************************************************/
fsp_err_t R_USB_Write(usb_ctrl_t * const p_api_ctrl, uint8_t *p_buf, uint32_t size, usb_instance_transfer_t * p_api_trans)
{
    usb_info_t  info;
    usb_er_t    err;
    fsp_err_t   result = FSP_ERR_USB_FAILED;

    usb_instance_ctrl_t * p_ctrl = (usb_instance_ctrl_t *) p_api_ctrl;

#if USB_CFG_PARAM_CHECKING_ENABLE == BSP_CFG_PARAM_CHECKING_ENABLE

    FSP_ASSERT (USB_NULL != p_api_ctrl)

    FSP_ASSERT (USB_NULL != p_api_trans)

#endif /* USB_CFG_PARAM_CHECKING_ENABLE == BSP_CFG_PARAM_CHECKING_ENABLE */

#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
    if (USB_PERI == g_usb_usbmode)
    {
    	p_api_trans->module_number= USB_CFG_USE_USBIP;
    }
#endif  /* USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI */

#if USB_CFG_PARAM_CHECKING_ENABLE == BSP_CFG_PARAM_CHECKING_ENABLE

    FSP_ASSERT (!((USB_NULL == p_buf) && (0 != size)))

    /* Argument Checking */
    FSP_ASSERT (!((USB_IP0 != p_api_trans->module_number) && (USB_IP1 != p_api_trans->module_number) && ( USB_HOST == g_usb_usbmode)))

#if defined(BSP_BOARD_GROUP_RA2A1)
	FSP_ASSERT (USB_IP1 != p_api_trans->module_number)
#endif

	FSP_ASSERT (!((USB_CLASS_HCDCC == p_api_trans->type) || (USB_CLASS_PVND == p_api_trans->type)
                || (USB_CLASS_HVND == p_api_trans->type) || (USB_CLASS_HMSC == p_api_trans->type)
                || (USB_CLASS_PMSC == p_api_trans->type)))

    if (USB_CLASS_REQUEST != p_api_trans->type)
    {
    	FSP_ASSERT (USB_NULL != (g_usb_open_class[p_api_trans->module_number] & (1 << p_api_trans->type)))      /* Check USB Open device class */
    }

#endif  /* USB_CFG_PARAM_CHECKING_ENABLE == BSP_CFG_PARAM_CHECKING_ENABLE */

    p_ctrl->module_number = p_api_trans->module_number;
    p_ctrl->type = p_api_trans->type;
    p_ctrl->device_address = p_api_trans->device_address;
    p_ctrl->pipe = p_api_trans->pipe;
    p_ctrl->setup = p_api_trans->setup;

    (void)R_USB_InfoGet(p_ctrl, &info);
    if (USB_STATUS_CONFIGURED == info.device_status)
    {
        if (USB_CLASS_REQUEST == p_ctrl->type)
        {
            err = usb_ctrl_write( p_ctrl, p_buf, size );
        }
        else
        {
            err = usb_data_write( p_ctrl, p_buf, size );
        }

        if (USB_OK == err)
        {
            result = FSP_SUCCESS;
        }
        else if (USB_QOVR == err)
        {
        	result = FSP_ERR_USB_BUSY;
        }
        else
        {
        	/* Noting */
        }
    }
    return result;
}

/**************************************************************************//**
 * @brief Requests a data read/write transfer be terminated
 * when a data read/write transfer is being performed.
 *
 * To stop a data read, set USB_TRANSFER_READ as the argument (type); to stop a data write,
 * specify USB_WRITE as the argument (type).
 *
 * @retval FSP_SUCCESS           Successfully completed. (stop completed)
 * @retval FSP_ERR_USB_FAILED    The function could not be completed successfully.
 * @retval FSP_ERR_ASSERTION     Parameter error.
 * @retval FSP_ERR_USB_BUSY      Stop processing is called multiple times.
 ******************************************************************************/
fsp_err_t    R_USB_Stop(usb_ctrl_t * const p_api_ctrl, usb_transfer_t type, usb_instance_transfer_t * p_api_trans)
{
    usb_info_t  info;
    usb_er_t    err;
	fsp_err_t   result = FSP_ERR_USB_FAILED;

    usb_instance_ctrl_t * p_ctrl = (usb_instance_ctrl_t *) p_api_ctrl;

#if USB_CFG_PARAM_CHECKING_ENABLE == BSP_CFG_PARAM_CHECKING_ENABLE

    FSP_ASSERT (USB_NULL != p_api_ctrl)

    FSP_ASSERT (USB_NULL != p_api_trans)

#endif /* USB_CFG_PARAM_CHECKING_ENABLE == BSP_CFG_PARAM_CHECKING_ENABLE */

#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
    if (USB_PERI == g_usb_usbmode)
    {
    	p_api_trans->module_number = USB_CFG_USE_USBIP;
    }
#endif  /* USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI */

#if USB_CFG_PARAM_CHECKING_ENABLE == BSP_CFG_PARAM_CHECKING_ENABLE


    FSP_ASSERT (!((USB_TRANSFER_WRITE != type) && (USB_TRANSFER_READ != type)))

    /* Argument Checking */
    FSP_ASSERT (!((USB_IP0 != p_api_trans->module_number) && (USB_IP1 != p_api_trans->module_number) && ( USB_HOST == g_usb_usbmode)))

#if defined(BSP_BOARD_GROUP_RA2A1)
	FSP_ASSERT (USB_IP1 != p_api_trans->module_number)
#endif

	FSP_ASSERT (!((USB_CLASS_PVND == p_api_trans->type) || (USB_CLASS_HVND == p_api_trans->type)
        || (USB_CLASS_HMSC == p_api_trans->type) || (USB_CLASS_PMSC == p_api_trans->type)))

	FSP_ASSERT (!(((USB_CLASS_HCDCC == p_api_trans->type) && (USB_TRANSFER_WRITE == type))   ||
        ((USB_CLASS_PCDCC == p_api_trans->type ) && (USB_TRANSFER_READ == type))))

#endif  /* USB_CFG_PARAM_CHECKING_ENABLE == BSP_CFG_PARAM_CHECKING_ENABLE */

    p_ctrl->module_number = p_api_trans->module_number;
    p_ctrl->type = p_api_trans->type;
    p_ctrl->device_address = p_api_trans->device_address;
    p_ctrl->pipe = p_api_trans->pipe;
    p_ctrl->setup = p_api_trans->setup;

    (void)R_USB_InfoGet(p_ctrl, &info);
    FSP_ERROR_RETURN (USB_STATUS_CONFIGURED == info.device_status, FSP_ERR_USB_FAILED)

    if (USB_CLASS_REQUEST == p_ctrl->type)
    {
        err = usb_ctrl_stop( p_ctrl);
    }
    else
    {
        err = usb_data_stop( p_ctrl, type);
    }

    if (USB_OK == err)
    {
    	result = FSP_SUCCESS;
    }
    else if (USB_QOVR == err)
    {
    	result = FSP_ERR_USB_BUSY;
    }
    else
    {
    	/* Nothing */
    }

    return result;
}

/**************************************************************************//**
 * @brief Sends a SUSPEND signal from the USB module assigned to the member
 * (module) of the usb_crtl_t structure.
 *
 * After the suspend request is completed, confirm the operation with the return value
 * (USB_STATUS_SUSPEND) of the R_USB_EventGet function.
 *
 * @retval FSP_SUCCESS           Successfully completed.
 * @retval FSP_ERR_USB_FAILED    The function could not be completed successfully.
 * @retval FSP_ERR_USB_BUSY      During a suspend request to the specified USB module,
 *                               or when the USB module is already in the suspended state.
 * @retval FSP_ERR_ASSERTION     Parameter error.
 ******************************************************************************/
fsp_err_t    R_USB_Suspend(usb_ctrl_t * const p_api_ctrl, usb_instance_transfer_t * p_api_trans)
{
#if USB_CFG_MODE == USB_CFG_PERI

    FSP_PARAMETER_NOT_USED(*p_api_trans);
    FSP_PARAMETER_NOT_USED(p_api_ctrl);

    return FSP_ERR_USB_FAILED;              /* Support Host only. */

#else /* USB_CFG_MODE == USB_CFG_PERI */
    fsp_err_t   ret_code = FSP_SUCCESS;

    usb_instance_ctrl_t * p_ctrl = (usb_instance_ctrl_t *) p_api_ctrl;

    FSP_PARAMETER_NOT_USED(*p_ctrl);
#if ( (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST )
    usb_utr_t   utr;
    usb_info_t  info;
    usb_er_t    err;
#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */

    FSP_ERROR_RETURN (USB_PERI != g_usb_usbmode, FSP_ERR_USB_FAILED)

#if USB_CFG_PARAM_CHECKING_ENABLE == BSP_CFG_PARAM_CHECKING_ENABLE

    /* Argument Checking */
    FSP_ASSERT (!((USB_IP0 != p_api_trans->module_number) && (USB_IP1 != p_api_trans->module_number)))

#if defined(BSP_BOARD_GROUP_RA2A1)
    FSP_ASSERT (USB_IP1 != p_api_trans->module_number)
#endif

#endif  /* USB_CFG_PARAM_CHECKING_ENABLE == BSP_CFG_PARAM_CHECKING_ENABLE */
    p_ctrl->module_number = p_api_trans->module_number;
    p_ctrl->type = p_api_trans->type;
    p_ctrl->device_address = p_api_trans->device_address;
    p_ctrl->pipe = p_api_trans->pipe;
    p_ctrl->setup = p_api_trans->setup;


#if ( (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST )

#if USB_CFG_PARAM_CHECKING_ENABLE == BSP_CFG_PARAM_CHECKING_ENABLE

	FSP_ASSERT (USB_NULL != p_api_ctrl)

#endif  /* USB_CFG_PARAM_CHECKING_ENABLE == BSP_CFG_PARAM_CHECKING_ENABLE */

    p_ctrl->device_address = USB_DEVICEADDR;

    ret_code = R_USB_InfoGet(p_ctrl, &info);
    FSP_ERROR_RETURN(USB_STATUS_CONFIGURED == info.device_status, FSP_ERR_USB_FAILED)
    
    utr.ip = p_ctrl->module_number;
    utr.ipp = usb_hstd_get_usb_ip_adr(utr.ip);
#if (BSP_CFG_RTOS == 0)
    if (USB_NULL != (g_usb_change_device_state[p_ctrl->module_number] & (1 << USB_STATUS_SUSPEND)))
    {
        return FSP_ERR_USB_BUSY;
    }

    err = usb_hstd_change_device_state(&utr, (usb_cb_t)&usb_hstd_suspend_complete,
                                       USB_DO_GLOBAL_SUSPEND, USB_DEVICEADDR);

    if (USB_OK == err)
    {
        g_usb_change_device_state[p_ctrl->module_number] |= (1 << USB_STATUS_SUSPEND);
    }
    else
    {
        ret_code = FSP_ERR_USB_FAILED;
    }
#else   /* (BSP_CFG_RTOS == 0) */
    if (USB_YES == gs_usb_suspend_ing[p_ctrl->module_number])
    {
    	ret_code = FSP_ERR_USB_BUSY;
    }
    else
    {
        gs_usb_suspend_ing[p_ctrl->module_number] = USB_YES;
    }

    err = usb_hstd_change_device_state(&utr, (usb_cb_t)&usb_hstd_suspend_complete,
                                       USB_DO_GLOBAL_SUSPEND, USB_DEVICEADDR);

    if (USB_OK != err)
    {
        ret_code = FSP_ERR_USB_FAILED;
    }

    gs_usb_suspend_ing[p_ctrl->module_number] = USB_NO;
#endif  /* (BSP_CFG_RTOS == 0) */

#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */

    return ret_code;
#endif /* USB_CFG_MODE == USB_CFG_PERI */
}

/**************************************************************************//**
 * @brief Sends a RESUME signal from the USB module assigned to the
 * member (module) of the usb_ctrl_tstructure.
 *
 * After the resume request is completed, confirm the operation with the return
 * value (USB_STATUS_RESUME) of the R_USB_EventGet function
 *
 * @retval FSP_SUCCESS              Successfully completed.
 * @retval FSP_ERR_USB_FAILED       The function could not be completed successfully.
 * @retval FSP_ERR_USB_BUSY         Resume already requested for same device address.
 *                                  (USB host mode only)
 * @retval FSP_ERR_USB_NOT_SUSPEND  USB device is not in the SUSPEND state.
 * @retval FSP_ERR_ASSERTION        Parameter error.
 ******************************************************************************/
fsp_err_t    R_USB_Resume(usb_ctrl_t * const p_api_ctrl, usb_instance_transfer_t * p_api_trans)
{
    usb_instance_ctrl_t * p_ctrl = (usb_instance_ctrl_t *) p_api_ctrl;

#if ( (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST )
    usb_utr_t   utr;
    usb_er_t    err;
#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    fsp_err_t   ret_code = FSP_SUCCESS;
    usb_info_t  info;

#if USB_CFG_PARAM_CHECKING_ENABLE == BSP_CFG_PARAM_CHECKING_ENABLE

    FSP_ASSERT (USB_NULL != p_api_ctrl)

#endif /* USB_CFG_PARAM_CHECKING_ENABLE == BSP_CFG_PARAM_CHECKING_ENABLE */

#if ( (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI )
    if (USB_PERI == g_usb_usbmode)
    {
        p_ctrl->module_number = USB_CFG_USE_USBIP;
    }
#endif  /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI */

#if USB_CFG_PARAM_CHECKING_ENABLE == BSP_CFG_PARAM_CHECKING_ENABLE

    FSP_ASSERT (USB_NULL != p_api_trans)

    /* Argument Checking */
    FSP_ASSERT (!((USB_IP0 != p_api_trans->module_number) && (USB_IP1 != p_api_trans->module_number) && ( USB_HOST == g_usb_usbmode)))

#if defined(BSP_BOARD_GROUP_RA2A1)
	FSP_ASSERT (USB_IP1 != p_api_trans->module_number)
#endif

    if (USB_HOST == g_usb_usbmode)
    {
    	p_api_trans->device_address = USB_DEVICEADDR;
    }
    else
    {
    	FSP_ASSERT (USB_CLASS_PHID == p_api_trans->type)
    }

#endif  /* USB_CFG_PARAM_CHECKING_ENABLE == BSP_CFG_PARAM_CHECKING_ENABLE */

    p_ctrl->module_number = p_api_trans->module_number;
    p_ctrl->type = p_api_trans->type;
    p_ctrl->device_address = p_api_trans->device_address;
    p_ctrl->pipe = p_api_trans->pipe;
    p_ctrl->setup = p_api_trans->setup;

    ret_code = R_USB_InfoGet(p_ctrl, &info);
    FSP_ERROR_RETURN(USB_STATUS_SUSPEND == info.device_status, FSP_ERR_USB_NOT_SUSPEND)

    if (USB_HOST == g_usb_usbmode)
    {
#if ( (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST )
        utr.ip = p_ctrl->module_number;
        utr.ipp = usb_hstd_get_usb_ip_adr(utr.ip);

#if (BSP_CFG_RTOS == 0)
        if (USB_NULL != (g_usb_change_device_state[p_ctrl->module_number] & (1 << USB_STATUS_RESUME)))
        {
            return FSP_ERR_USB_BUSY;
        }

        err = usb_hstd_change_device_state(&utr, (usb_cb_t)&usb_hstd_resume_complete,
                                         USB_DO_GLOBAL_RESUME, p_ctrl->device_address);
        if (USB_OK == err)
        {
            g_usb_change_device_state[p_ctrl->module_number] |= (1 << USB_STATUS_RESUME);
        }
        else
        {
            ret_code = FSP_ERR_USB_FAILED;
        }
#else   /* (BSP_CFG_RTOS == 0) */
        if (USB_YES == gs_usb_resume_ing[p_ctrl->module_number])
        {
        	ret_code = FSP_ERR_USB_BUSY;
        }
        else
        {
            gs_usb_resume_ing[p_ctrl->module_number] = USB_YES;
        }

        if(FSP_ERR_USB_BUSY == ret_code)
        {
        	return ret_code;
        }

        err = usb_hstd_change_device_state(&utr, (usb_cb_t)&usb_hstd_resume_complete,
                                         USB_DO_GLOBAL_RESUME, p_ctrl->device_address);
        if (USB_OK != err)
        {
            ret_code = FSP_ERR_USB_FAILED;
        }

        gs_usb_resume_ing[p_ctrl->module_number] = USB_NO;

#endif  /* (BSP_CFG_RTOS == 0) */
#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }
    else
    {
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
#if (BSP_CFG_RTOS == 0)

        /* Support remote wakeup ? */
        if (USB_TRUE == g_usb_pstd_remote_wakeup)
        {
            usb_pstd_change_device_state(USB_DO_REMOTEWAKEUP, USB_NULL, (usb_cb_t)usb_pstd_dummy_function);
            switch (g_usb_pstd_remote_wakeup_state)
            {
                case USB_OK:
                    ret_code = FSP_SUCCESS;
                break;

                case USB_QOVR:
                    ret_code = FSP_ERR_USB_NOT_SUSPEND;
                break;

                case USB_ERROR:
                default:
                    ret_code = FSP_ERR_USB_FAILED;
                break;
            }
        }
        else
        {
            ret_code = FSP_ERR_USB_FAILED;
        }
#else   /* (BSP_CFG_RTOS == 0) */

        if (USB_YES == gs_usb_resume_ing[USB_CFG_USE_USBIP])
        {
            ret_code = FSP_ERR_USB_BUSY;
        }
        else
        {
            gs_usb_resume_ing[USB_CFG_USE_USBIP] = USB_YES;
        }

        /* When the device is in the resume state. */
        if( ret_code == FSP_ERR_USB_BUSY)
        {
        	return ret_code;
        }

        /* Support remote wakeup ? */
        if (USB_TRUE == g_usb_pstd_remote_wakeup)
        {
            usb_pstd_change_device_state(USB_DO_REMOTEWAKEUP, USB_NULL, (usb_cb_t)usb_pstd_dummy_function);
            switch (g_usb_pstd_remote_wakeup_state)
            {
                case USB_OK:
                    ret_code = FSP_SUCCESS;
                break;

                case USB_QOVR:
                    ret_code = FSP_ERR_USB_NOT_SUSPEND;
                break;

                case USB_ERROR:
                default:
                    ret_code = FSP_ERR_USB_FAILED;
                break;
            }
        }
        else
        {
            ret_code = FSP_ERR_USB_FAILED;
        }
        gs_usb_resume_ing[USB_CFG_USE_USBIP] = USB_NO;

#endif  /* (BSP_CFG_RTOS == 0) */
#else   /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_PERI */
        ret_code = FSP_ERR_USB_FAILED;
#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_PERI */
    }

    return ret_code;
}

/**************************************************************************//**
 * @brief Specifies starting or stopping the VBUS supply.
 *
 * @retval FSP_SUCCESS              Successful completion. (VBUS supply start/stop completed)
 * @retval FSP_ERR_USB_FAILED       The function could not be completed successfully.
 * @retval FSP_ERR_ASSERTION        Parameter error.
 ******************************************************************************/
fsp_err_t   R_USB_VbusSet( usb_ctrl_t * const p_api_ctrl, uint16_t state, usb_instance_transfer_t * p_api_trans)
{
    usb_instance_ctrl_t * p_ctrl = (usb_instance_ctrl_t *) p_api_ctrl;

#if (USB_CFG_MODE == USB_CFG_PERI)

    FSP_PARAMETER_NOT_USED(state);
    FSP_PARAMETER_NOT_USED(*p_api_trans);
    FSP_PARAMETER_NOT_USED(*p_ctrl);

    return FSP_ERR_USB_FAILED;
#else
    usb_utr_t   utr;

    FSP_ERROR_RETURN(USB_PERI != g_usb_usbmode, FSP_ERR_USB_FAILED)

#if USB_CFG_PARAM_CHECKING_ENABLE == BSP_CFG_PARAM_CHECKING_ENABLE

    /* Argument Checking */
    FSP_ASSERT (!((USB_IP0 != p_api_trans->module_number) && (USB_IP1 != p_api_trans->module_number)))

#if defined(BSP_BOARD_GROUP_RA2A1)
    FSP_ASSERT (USB_IP1 != p_api_trans->module_number)
#endif /* defined(BSP_BOARD_GROUP_RA2A1)  */

	FSP_ASSERT (USB_NULL != p_api_ctrl)

	FSP_ASSERT (!((USB_ON != state) && (USB_OFF != state)))

#endif  /* USB_CFG_PARAM_CHECKING_ENABLE == BSP_CFG_PARAM_CHECKING_ENABLE */

    p_ctrl->module_number = p_api_trans->module_number;
    p_ctrl->type = p_api_trans->type;
    p_ctrl->device_address = p_api_trans->device_address;
    p_ctrl->pipe = p_api_trans->pipe;
    p_ctrl->setup = p_api_trans->setup;

    utr.ip = p_ctrl->module_number;
    utr.ipp = usb_hstd_get_usb_ip_adr(utr.ip);

    if (USB_ON == state)
    {
        usb_hstd_vbus_control(&utr, (uint16_t)USB_VBON);
    }
    else
    {
        usb_hstd_vbus_control(&utr, (uint16_t)USB_VBOFF);
    }

    return FSP_SUCCESS;
#endif /* (USB_CFG_MODE == USB_CFG_PERI) */
}

/**************************************************************************//**
 * @brief Obtains completed USB-related events.
 *
 * @retval FSP_SUCCESS              Successful completion. (VBUS supply start/stop completed)
 * @retval FSP_ERR_ASSERTION        Parameter error.
 * @retval FSP_ERR_USB_FAILED       The function could not be completed successfully.
 ******************************************************************************/
fsp_err_t   R_USB_InfoGet( usb_ctrl_t * const p_api_ctrl, usb_info_t *p_info)
{
    fsp_err_t   ret_code = FSP_SUCCESS;
    usb_instance_ctrl_t * p_ctrl = (usb_instance_ctrl_t *) p_api_ctrl;

#if ( (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST )
    usb_utr_t   utr;
#elif ( (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI )
    uint32_t    status;
#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */

#if USB_CFG_PARAM_CHECKING_ENABLE == BSP_CFG_PARAM_CHECKING_ENABLE

    FSP_ASSERT (USB_NULL != p_api_ctrl)

#endif /* USB_CFG_PARAM_CHECKING_ENABLE == BSP_CFG_PARAM_CHECKING_ENABLE */

#if ( (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI )
    if (USB_PERI == g_usb_usbmode)
    {
        p_ctrl->module_number = USB_CFG_USE_USBIP;
    }
#endif  /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI */

#if USB_CFG_PARAM_CHECKING_ENABLE == BSP_CFG_PARAM_CHECKING_ENABLE
    /* Argument Checking */
    FSP_ASSERT (!((USB_IP0 != p_ctrl->module_number) && (USB_IP1 != p_ctrl->module_number) && ( USB_HOST == g_usb_usbmode)))

#if defined(BSP_BOARD_GROUP_RA2A1)
    FSP_ASSERT (USB_IP1 != p_ctrl->module_number)
#endif

	FSP_ASSERT (USB_NULL != p_info)

    p_info->device_status = USB_STATUS_DETACH;  /* Initialized for warning measures. */

#else   /* USB_CFG_PARAM_CHECKING_ENABLE == BSP_CFG_PARAM_CHECKING_ENABLE */
    FSP_PARAMETER_NOT_USED(*p_ctrl);

    p_info->device_status = USB_STATUS_DETACH;  /* Initialized for warning measures. */
#endif  /* USB_CFG_PARAM_CHECKING_ENABLE == BSP_CFG_PARAM_CHECKING_ENABLE */

    FSP_ERROR_RETURN(0 != g_usb_open_class[p_ctrl->module_number], FSP_ERR_USB_FAILED)

    if (USB_HOST == g_usb_usbmode)
    {
#if ( (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST )

#if USB_CFG_PARAM_CHECKING_ENABLE == BSP_CFG_PARAM_CHECKING_ENABLE
    	FSP_ASSERT (USB_NULL != p_ctrl)

#endif  /* USB_CFG_PARAM_CHECKING_ENABLE == BSP_CFG_PARAM_CHECKING_ENABLE */

        utr.ip = p_ctrl->module_number;
        utr.ipp = usb_hstd_get_usb_ip_adr(utr.ip);

        /* Set USB Device class */
        switch (g_usb_hstd_device_info[utr.ip][p_ctrl->device_address][3])
        {
            case USB_IFCLS_CDC:
                p_info->class_type   = USB_CLASS_PCDC;
                break;
            case USB_IFCLS_HID:
                p_info->class_type   = USB_CLASS_PHID;
                break;
            case USB_IFCLS_MAS:
                p_info->class_type   = USB_CLASS_PMSC;
                break;
            case USB_IFCLS_VEN:
                p_info->class_type   = USB_CLASS_PVND;
                break;
            default:
                p_info->class_type   = USB_NULL;
                break;
        }

        /* Set USB connect speed */
        switch(g_usb_hstd_device_info[utr.ip][p_ctrl->device_address][4])
        {
            case USB_NOCONNECT:
                p_info->speed  = USB_NULL;
                break;
            case USB_HSCONNECT:
                p_info->speed  = USB_SPEED_HS;
                break;
            case USB_FSCONNECT:
                p_info->speed  = USB_SPEED_FS;
                break;
            case USB_LSCONNECT:
                p_info->speed  = USB_SPEED_LS;
                break;
            default:
                p_info->speed  = USB_NULL;
                break;
        }

        /* Set USB device state */
        switch (g_usb_hstd_device_info[utr.ip][p_ctrl->device_address][1])
        {
            case USB_POWERED:                           /* Power state  */
                p_info->device_status = USB_STATUS_POWERED;
                break;
            case USB_DEFAULT:                           /* Default state  */
                p_info->device_status = USB_STATUS_DEFAULT;
                break;
            case USB_ADDRESS:                           /* Address state  */
                p_info->device_status = USB_STATUS_ADDRESS;
                break;
            case USB_CONFIGURED:                        /* Configured state  */
                p_info->device_status = USB_STATUS_CONFIGURED;
                break;
            case USB_SUSPENDED:                         /* Suspend state */
                p_info->device_status = USB_STATUS_SUSPEND;
                break;
            case USB_DETACHED:                          /* Disconnect(VBUSon) state */
                p_info->device_status = USB_STATUS_DETACH;
                break;
            default:                                    /* Error */
                p_info->device_status = USB_NULL;
                break;
        }

        /* Set USB Peri BC port state */
#if USB_CFG_BC == USB_CFG_ENABLE
        if (USB_DEVICEADDR == p_ctrl->device_address)          /* Check Root port address */
        {
            if (USB_BC_STATE_CDP == g_usb_hstd_bc[utr.ip].state)
            {
                p_info->bcport   = USB_BCPORT_CDP;
            }
            else
            {
                p_info->bcport   = USB_BCPORT_SDP;               /* USB_SDP/USB_CDP/USB_DCP */
            }
        }
        else
        {
            p_info->bcport   = USB_BCPORT_SDP;                   /* USB_SDP/USB_CDP/USB_DCP */
        }

#else   /* #if USB_CFG_BC == USB_CFG_ENABLE */
        p_info->bcport   = USB_BCPORT_SDP;  /* USB_SDP/USB_CDP/USB_DCP */

#endif  /* #if USB_CFG_BC == USB_CFG_ENABLE */
#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }
    else
    {
#if ( (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI )

        p_info->class_type   = USB_NULL;              /* Device class */
        switch(usb_cstd_port_speed(USB_NULL))
        {
            case USB_NOCONNECT:
                p_info->speed  = USB_NULL;
            break;
            case USB_HSCONNECT:
                p_info->speed  = USB_SPEED_HS;
            break;
            case USB_FSCONNECT:
                p_info->speed  = USB_SPEED_FS;
            break;
            case USB_LSCONNECT:
                p_info->speed  = USB_SPEED_LS;
            break;
            default:
                p_info->speed  = USB_NULL;
            break;
        }
        status = hw_usb_read_intsts();
        switch ((uint16_t)(status & USB_DVSQ))
        {
            case USB_DS_POWR:                           /* Power state  */
                p_info->device_status = USB_STATUS_DETACH;
            break;
            case USB_DS_DFLT:                           /* Default state  */
                p_info->device_status = USB_STATUS_DEFAULT;
            break;
            case USB_DS_ADDS:                           /* Address state  */
                p_info->device_status = USB_STATUS_ADDRESS;
            break;
            case USB_DS_CNFG:                           /* Configured state  */
                p_info->device_status = USB_STATUS_CONFIGURED;
            break;
            case USB_DS_SPD_POWR:                       /* Power suspend state */
            case USB_DS_SPD_DFLT:                       /* Default suspend state */
            case USB_DS_SPD_ADDR:                       /* Address suspend state */
            case USB_DS_SPD_CNFG:                       /* Configured Suspend state */
                p_info->device_status = USB_STATUS_SUSPEND;
            break;
            default:                                    /* Error */
            break;                                      /* p_info->device_status = USB_STS_ERROR; */
        }
#if USB_CFG_BC == USB_CFG_ENABLE
        p_info->bcport   = (uint8_t)g_usb_bc_detect;           /* USB_SDP/USB_CDP/USB_DCP */
#else   /* USB_CFG_BC == USB_CFG_ENABLE */
        p_info->bcport   = USB_BCPORT_SDP;                   /* USB_SDP */
#endif  /* USB_CFG_BC == USB_CFG_ENABLE */
        ret_code = FSP_SUCCESS;

#endif  /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI */
    }

    return ret_code;
}

/**************************************************************************//**
 * @brief Requests a data read (bulk/interrupt transfer) via the pipe specified in the argument.
 *
 * The read data is stored in the area specified in the argument (p_buf).
 * After the data read is completed, confirm the operation with the R_USB_GetEvent function
 * return value(USB_STATUS_READ_COMPLETE).
 * To figure out the size of the data when a read is complete, check the return
 * value (USB_STATUS_READ_COMPLETE) of the R_USB_GetEvent function, and then
 * refer to the member (size) of the usb_crtl_t structure.
 *
 * @retval FSP_SUCCESS              Successfully completed.
 * @retval FSP_ERR_USB_BUSY         Specified pipe now handling data receive/send request.
 * @retval FSP_ERR_USB_FAILED       The function could not be completed successfully.
 * @retval FSP_ERR_ASSERTION        Parameter error.
 ******************************************************************************/
fsp_err_t  R_USB_PipeRead(usb_ctrl_t * const p_api_ctrl, uint8_t *p_buf, uint32_t size, usb_instance_transfer_t * p_api_trans)
{
    usb_instance_ctrl_t * p_ctrl = (usb_instance_ctrl_t *) p_api_ctrl;

#if !defined(USB_CFG_HVND_USE) && !defined(USB_CFG_PVND_USE)

    FSP_PARAMETER_NOT_USED(*p_ctrl);
    FSP_PARAMETER_NOT_USED(*p_buf);
    FSP_PARAMETER_NOT_USED(size);
    FSP_PARAMETER_NOT_USED(*p_api_trans);

    return FSP_ERR_USB_FAILED;
#else   /* !defined(USB_CFG_HVND_USE) && !defined(USB_CFG_PVND_USE) */

    fsp_err_t   ret_code = FSP_ERR_USB_FAILED;
    usb_utr_t   *p_tran_data;
#if (BSP_CFG_RTOS == 2)
    usb_utr_t   tran_data;
#endif /* (BSP_CFG_RTOS == 2) */

    usb_er_t    err;
    usb_info_t  info;

#if USB_CFG_PARAM_CHECKING_ENABLE == BSP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT (USB_NULL != p_api_ctrl)

    FSP_ASSERT (USB_NULL != p_api_trans)
#endif /* USB_CFG_PARAM_CHECKING_ENABLE == BSP_CFG_PARAM_CHECKING_ENABLE */

#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
    if (USB_PERI == g_usb_usbmode)
    {
    	p_api_trans->module = USB_CFG_USE_USBIP;
    }
#endif  /* USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI */

#if USB_CFG_PARAM_CHECKING_ENABLE == BSP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT (((USB_PIPE0 != p_api_trans->pipe)) || (USB_MAXPIPE_NUM < p_api_trans->pipe))

    FSP_ASSERT (!((USB_NULL == p_buf) || (USB_NULL == size)))

    /* Argument Checking */
    FSP_ASSERT (!((USB_IP0 != p_api_trans->module_number) && (USB_IP1 != p_api_trans->module_number) && ( USB_HOST == g_usb_usbmode)))

	FSP_ASSERT(USB_NULL != (g_usb_open_class[p_api_trans->module_numner] & (1 << p_api_trans->type))) /* Check USB Open device class */

#endif  /* USB_CFG_PARAM_CHECKING_ENABLE == BSP_CFG_PARAM_CHECKING_ENABLE */

    p_ctrl->module_number = p_api_trans->module_number;
    p_ctrl->type = p_api_trans->type;
    p_ctrl->device_address = p_api_trans->device_address;
    p_ctrl->pipe = p_api_trans->pipe;
    p_ctrl->setup = p_api_trans->setup;

    ret_code = R_USB_InfoGet(p_ctrl, &info);
    if (USB_STATUS_CONFIGURED == info.device_status)
    {
        /* PIPE Transfer set */
        if (USB_HOST == g_usb_usbmode)
        {
    #if defined(USB_CFG_HVND_USE)
      #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)

#if (BSP_CFG_RTOS == 2)
            p_tran_data = (usb_utr_t *)&tran_data;
#else  /* (BSP_CFG_RTOS == 2) */
            p_tran_data = (usb_utr_t *)&g_usb_hdata[p_ctrl->module][p_ctrl->pipe];
#endif /* (BSP_CFG_RTOS == 2) */

            p_tran_data->ip = p_ctrl->module;
            p_tran_data->ipp = usb_hstd_get_usb_ip_adr(p_tran_data->ip);
            p_tran_data->keyword     = p_ctrl->pipe;             /* Pipe No */
            p_tran_data->p_tranadr   = buf;                      /* Data address */
            p_tran_data->tranlen     = size;                     /* Data Size */
            p_tran_data->p_setup     = 0;
            p_tran_data->complete    = usb_hvnd_read_complete;   /* Callback function */
            p_tran_data->segment     = USB_TRAN_END;
            *(uint32_t *)p_tran_data->p_usr_data = p_ctrl->device_address;
            p_tran_data->read_req_len= size;                     /* Data Size */

            err = usb_hstd_transfer_start(p_tran_data);        /* USB Transfer Start */
            if (USB_OK == err)
            {
                ret_code = FSP_SUCCESS;
            }
            else if (USB_QOVR == err)
            {
                ret_code = FSP_ERR_USB_BUSY;
            }
            else
            {
            }
      #endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    #endif /* #if defined(USB_CFG_HVND_USE) */
        }
        else
        {
    #if defined(USB_CFG_PVND_USE)
      #if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)

#if (BSP_CFG_RTOS == 2)
            p_tran_data = (usb_utr_t *)&tran_data;
#else  /* (BSP_CFG_RTOS == 2) */
            p_tran_data = (usb_utr_t *)&g_usb_pdata[p_ctrl->pipe];
#endif /* (BSP_CFG_RTOS == 2) */

            p_tran_data->keyword    = p_ctrl->pipe;        /* Pipe No */
            p_tran_data->p_tranadr  = buf;                 /* Data address */
            p_tran_data->tranlen    = size;                /* Data Size */
            p_tran_data->complete   = (usb_cb_t)&usb_pvnd_read_complete;   /* Callback function */
            p_tran_data->read_req_len= size;                     /* Data Size */
            err = usb_pstd_transfer_start(p_tran_data);   /* USB Transfer Start */
            if (USB_OK == err)
            {
                ret_code = FSP_SUCCESS;
            }
            else if (USB_QOVR == err)
            {
                ret_code = FSP_ERR_USB_BUSY;
            }
            else
            {
            }
      #endif  /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI */
    #endif  /* defined(USB_CFG_PVND_USE) */
        }
    }

    return ret_code;
#endif  /* !defined(USB_CFG_HVND_USE) && !defined(USB_CFG_PVND_USE) */

}

/**************************************************************************//**
 * @brief Requests a data write (bulk/interrupt transfer).
 *
 * The write data is stored in the area specified in the argument (p_buf).
 * After data write is completed, confirm the operation with the return value
 * (USB_STATUS_WRITE_COMPLETE) of the EventGet function.
 * To request the transmission of a NULL packet, assign USB_NULL (0) to the third argument (size).
 *
 * @retval FSP_SUCCESS              Successfully completed.
 * @retval FSP_ERR_USB_BUSY         Specified pipe now handling data receive/send request.
 * @retval FSP_ERR_USB_FAILED       The function could not be completed successfully.
 * @retval FSP_ERR_ASSERTION        Parameter error.
 ******************************************************************************/
fsp_err_t  R_USB_PipeWrite(usb_ctrl_t * const p_api_ctrl, uint8_t *p_buf, uint32_t size, usb_instance_transfer_t * p_api_trans)
{
    usb_instance_ctrl_t * p_ctrl = (usb_instance_ctrl_t *) p_api_ctrl;

#if !defined(USB_CFG_HVND_USE) && !defined(USB_CFG_PVND_USE)

    FSP_PARAMETER_NOT_USED(*p_ctrl);
    FSP_PARAMETER_NOT_USED(*p_buf);
    FSP_PARAMETER_NOT_USED(size);
    FSP_PARAMETER_NOT_USED(*p_api_trans);

    return FSP_ERR_USB_FAILED;
#else

    usb_er_t    err;
    fsp_err_t   ret_code;
    usb_info_t  info;
    usb_utr_t   *p_tran_data;
#if (BSP_CFG_RTOS == 2)
    usb_utr_t   tran_data;
#endif /* (BSP_CFG_RTOS == 2) */

#if USB_CFG_PARAM_CHECKING_ENABLE == BSP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT (USB_NULL != p_api_ctrl)

    FSP_ASSERT (USB_NULL != p_api_trans)
#endif /* USB_CFG_PARAM_CHECKING_ENABLE == BSP_CFG_PARAM_CHECKING_ENABLE */

#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
    if (USB_PERI == g_usb_usbmode)
    {
    	p_api_trans->module = USB_CFG_USE_USBIP;
    }
#endif  /* USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI */

#if USB_CFG_PARAM_CHECKING_ENABLE == BSP_CFG_PARAM_CHECKING_ENABLE
        /* Argument Checking */
    FSP_ASSERT (!((USB_IP0 != p_api_trans->module_number) && (USB_IP1 != p_api_trans->module_number) && ( USB_HOST == g_usb_usbmode)))

	FSP_ASSERT (((USB_NULL != p_buf) 0|| (USB_PIPE0 != p_api_trans->pipe)) || (USB_MAXPIPE_NUM > p_api_trans->pipe))

#if ( (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI )
    if (USB_PERI == g_usb_usbmode)
    {
    	FSP_ASSERT ((USB_NULL != p_buf) && (USB_NULL == size))
    }
#endif  /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI */

    FSP_ASSERT (USB_NULL == (g_usb_open_class[p_api_trans->module_number] & (1 << p_api_trans->type)))      /* Check USB Open device class */

#endif  /* USB_CFG_PARAM_CHECKING_ENABLE == BSP_CFG_PARAM_CHECKING_ENABLE */

    p_ctrl->module_number = p_api_trans->module_number;
    p_ctrl->type = p_api_trans->type;
    p_ctrl->device_address = p_api_trans->device_address;
    p_ctrl->pipe = p_api_trans->pipe;
    p_ctrl->setup = p_api_trans->setup;

    ret_code = R_USB_InformationGet(p_ctrl, &info);
    if (USB_STS_CONFIGURED == info.device_status)
    {
        /* PIPE Transfer set */
        if (USB_HOST == g_usb_usbmode)
        {
    #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
      #if defined(USB_CFG_HVND_USE)

#if (BSP_CFG_RTOS == 2)
            p_tran_data = (usb_utr_t *)&tran_data;
#else  /* (BSP_CFG_RTOS == 2) */
            p_tran_data = (usb_utr_t *)&g_usb_hdata[p_ctrl->module_number][p_ctrl->pipe];
#endif /* (BSP_CFG_RTOS == 2) */

            p_tran_data->ip                                     = p_ctrl->module_number;
            p_tran_data->ipp                                    = usb_hstd_get_usb_ip_adr((uint8_t) p_ctrl->module_number);
            p_tran_data->keyword                                = p_ctrl->pipe;                 /* Pipe No */
            p_tran_data->p_tranadr                              = buf;                          /* Data address */
            p_tran_data->tranlen                                = size;                         /* Data Size */
            p_tran_data->complete                               = usb_hvnd_write_complete;   /* Callback function */
            p_tran_data->segment                                = USB_TRAN_END;
            err = usb_hstd_transfer_start(p_tran_data);
            if (USB_OK == err)
            {
                ret_code = FSP_SUCCESS;
            }
            else if (USB_QOVR == err)
            {
                ret_code = FSP_ERR_USB_BUSY;
            }
            else
            {
            }
      #endif  /* defined(USB_CFG_HVND_USE) */
    #endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
        }
        else
        {
    #if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        #if defined(USB_CFG_PVND_USE)

#if (BSP_CFG_RTOS == 2)
            p_tran_data = (usb_utr_t *)&tran_data;
#else  /* (BSP_CFG_RTOS == 2) */
            p_tran_data = (usb_utr_t *)&g_usb_pdata[p_ctrl->pipe];
#endif /* (BSP_CFG_RTOS == 2) */

            p_tran_data->keyword                = p_ctrl->pipe;                         /* Pipe No */
            p_tran_data->p_tranadr              = buf;                                  /* Data address */
            p_tran_data->tranlen                = size;                                 /* Data Size */
            p_tran_data->complete               = usb_pvnd_write_complete;              /* Callback function */
            err = usb_pstd_transfer_start(p_tran_data);

            if (USB_OK == err)
            {
                ret_code = FSP_SUCCESS;
            }
            else if (USB_QOVR == err)
            {
                ret_code = FSP_ERR_USB_BUSY;
            }
            else
            {
            }
        #endif  /* defined(USB_CFG_PVND_USE) */
    #endif  /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI */
        }
    }
    return ret_code;
#endif /* #if !defined(USB_CFG_HVND_USE) && !defined(USB_CFG_PVND_USE) */

}

/**************************************************************************//**
 * @brief Terminates a data read/write operation.
 *
 * @retval FSP_SUCCESS              Successfully completed. (stop request completed)
 * @retval FSP_ERR_USB_FAILED       The function could not be completed successfully.
 * @retval FSP_ERR_ASSERTION        Parameter error.
 ******************************************************************************/
fsp_err_t    R_USB_PipeStop(usb_ctrl_t * const p_api_ctrl, usb_instance_transfer_t * p_api_trans)
{
    usb_instance_ctrl_t * p_ctrl = (usb_instance_ctrl_t *) p_api_ctrl;

#if !defined(USB_CFG_HVND_USE) && !defined(USB_CFG_PVND_USE)

    FSP_PARAMETER_NOT_USED(*p_ctrl);
    FSP_PARAMETER_NOT_USED(*p_api_trans);

    return FSP_ERR_USB_FAILED;
#else

    usb_er_t    err = FSP_ERR_USB_FAILED;
    fsp_err_t   ret_code = FSP_ERR_USB_FAILED;
    usb_info_t  info;

#if ( (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST )
    usb_utr_t   utr;

    if (USB_HOST == g_usb_usbmode)
    {
        utr.ip = p_ctrl->module_number;
        utr.ipp = usb_hstd_get_usb_ip_adr(utr.ip);
    }

#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */

#if USB_CFG_PARAM_CHECKING_ENABLE == BSP_CFG_PARAM_CHECKING_ENABLE
    /* Argument Checking */
    FSP_ASSERT (!((USB_IP0 != p_api_trans->module_number) && (USB_IP1 != p_api_trans->module_number) && ( USB_HOST == g_usb_usbmode)))

	FSP_ASSERT (((USB_NULL != p_api_ctrl) || (USB_PIPE0 != p_api_trans->pipe) || (USB_MAXPIPE_NUM > p_api_trans->pipe))

	FSP_ASSERT (USB_NULL != (g_usb_open_class[p_api_trans->module_number] & (1 << p_api_trans->type)))      /* Check USB Open device class */

#endif  /* USB_CFG_PARAM_CHECKING_ENABLE == BSP_CFG_PARAM_CHECKING_ENABLE */

    p_ctrl->module_number = p_api_trans->module_number;
    p_ctrl->type = p_api_trans->type;
    p_ctrl->device_address = p_api_trans->device_address;
    p_ctrl->pipe = p_api_trans->pipe;
    p_ctrl->setup = p_api_trans->setup;

    err = R_USB_InfoGet(p_ctrl, &info);
    FSP_ERROR_RETURN (USB_STS_CONFIGURED == info.device_status, FSP_ERR_USB_FAILED)
    if (USB_HOST == g_usb_usbmode)
    {
#if ( (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST )
        err = usb_hstd_transfer_end(&utr, p_ctrl->pipe, (uint16_t)USB_DATA_STOP);

#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }
    else
    {
#if ( (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI )
        err = usb_pstd_transfer_end(p_ctrl->pipe);

#endif  /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI */
    }
    if (USB_OK == err)
    {
        ret_code = FSP_SUCCESS;
    }

    return ret_code;
#endif /* !defined(USB_CFG_HVND_USE) && !defined(USB_CFG_PVND_USE) */
}

/**************************************************************************//**
 * @brief Gets the selected pipe number (number of the pipe that has completed initalization) via bit map information.
 *
 * The bit map information is stored in the area specified in argument (p_pipe).
 * Based on the information (module member and address member) assigned to the usb_ctrl_t structure,
 * obtains the PIPE information of that USB device.
 *
 * @retval FSP_SUCCESS              Successfully completed.
 * @retval FSP_ERR_USB_FAILED       The function could not be completed successfully.
 * @retval FSP_ERR_ASSERTION        Parameter error.
 ******************************************************************************/
fsp_err_t    R_USB_UsedPipesGet(usb_ctrl_t * const p_api_ctrl, uint16_t *p_pipe)
{
    usb_instance_ctrl_t * p_ctrl = (usb_instance_ctrl_t *) p_api_ctrl;

    usb_info_t  info;
    uint32_t    pipe_no;

    info.device_status = 0;

    FSP_PARAMETER_NOT_USED(*p_ctrl);
#if ( (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST )
    usb_utr_t   utr;
#endif /* ( (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST ) */

#if USB_CFG_PARAM_CHECKING_ENABLE == BSP_CFG_PARAM_CHECKING_ENABLE

    FSP_ASSERT (!((USB_NULL == p_ctrl) && (USB_HOST == g_usb_usbmode)))

    /* Argument Checking */
    FSP_ASSERT (!((USB_IP0 != p_ctrl->module_number) && (USB_IP1 != p_ctrl->module_number) && (USB_HOST == g_usb_usbmode)))

#if defined(BSP_BOARD_GROUP_RA2A1) 
    FSP_ASSERT (USB_IP1 != p_ctrl->module_number)
#endif /* defined(BSP_BOARD_GROUP_RA2A1)  */

#endif /* USB_CFG_PARAM_CHECKING_ENABLE == BSP_CFG_PARAM_CHECKING_ENABLE */

#if ( (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST )
    utr.ip = p_ctrl->module_number;
    utr.ipp = usb_hstd_get_usb_ip_adr(utr.ip);
#endif /* ( (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST ) */

    R_USB_InfoGet(p_ctrl, &info);
    FSP_ERROR_RETURN (USB_STATUS_CONFIGURED == info.device_status,FSP_ERR_USB_FAILED)

    /* Get PIPE Number from Endpoint address */
    *p_pipe = ((uint16_t)1 << USB_PIPE0);
    if (USB_HOST == g_usb_usbmode)
    {
#if ( (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST )
        for (pipe_no = USB_MIN_PIPE_NO; pipe_no < (USB_MAX_PIPE_NO +1); pipe_no++)
        {
            if (USB_TRUE == g_usb_pipe_table[utr.ip][pipe_no].use_flag)
            {
                if ((p_ctrl->device_address << USB_DEVADDRBIT) == (uint8_t)(g_usb_pipe_table[utr.ip][pipe_no].pipe_maxp & USB_DEVSEL))
                {
                    (*p_pipe) = (uint16_t)((*p_pipe) | (uint16_t)1 << pipe_no);
                }
            }
        }

#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }
    else
    {
#if ( (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI )
        for (pipe_no = USB_MIN_PIPE_NO; pipe_no < (USB_MAX_PIPE_NO +1); pipe_no++)
        {
            if (USB_TRUE == g_usb_pipe_table[USB_CFG_USE_USBIP][pipe_no].use_flag)
            {
            	(*p_pipe) = (uint16_t)((*p_pipe) | (uint16_t)(1 << pipe_no));
            }
        }

#endif  /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI */
    }

    return FSP_SUCCESS;
}

/**************************************************************************//**
 * @brief Gets the following pipe information regarding the pipe specified in the
 * argument (p_ctrl) member (pipe): endpoint number, transfer type,
 * transfer direction and maximum packet size.
 *
 * The obtained pipe information is stored in the area specified in the argument (p_info).
 *
 * @retval FSP_SUCCESS              Successfully completed.
 * @retval FSP_ERR_USB_FAILED       The function could not be completed successfully.
 * @retval FSP_ERR_ASSERTION        Parameter error.
 ******************************************************************************/
fsp_err_t    R_USB_PipeInfoGet(usb_ctrl_t * const p_api_ctrl, usb_pipe_t *p_info)
{
    usb_instance_ctrl_t * p_ctrl = (usb_instance_ctrl_t *) p_api_ctrl;

    usb_info_t  info;
    uint32_t    pipe_type;
    fsp_err_t   result = FSP_ERR_ASSERTION;

#if ( (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST )
    usb_utr_t   utr;
#endif /* #if ( (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST ) */

#if USB_CFG_PARAM_CHECKING_ENABLE == BSP_CFG_PARAM_CHECKING_ENABLE

    FSP_ASSERT (USB_NULL != p_api_ctrl)

    /* Argument Checking */
    FSP_ASSERT (!((USB_IP0 != p_ctrl->module_number) && (USB_IP1 != p_ctrl->module_number) && (USB_HOST == g_usb_usbmode)))

    FSP_ASSERT (!(((USB_NULL == p_ctrl) || (0 == p_ctrl->pipe)) || (USB_MAXPIPE_NUM < p_ctrl->pipe)))

#if defined(BSP_BOARD_GROUP_RA2A1)
	FSP_ASSERT (!((USB_IP1 == p_ctrl->module_number) && (USB_HOST == g_usb_usbmode)))
#endif

#endif  /* USB_CFG_PARAM_CHECKING_ENABLE == BSP_CFG_PARAM_CHECKING_ENABLE */


#if ( (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST )

    if (USB_HOST == g_usb_usbmode)
    {
        utr.ip = p_ctrl->module_number;
        utr.ipp = usb_hstd_get_usb_ip_adr(utr.ip);
    }

#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */

    R_USB_InfoGet(p_ctrl, &info);
    FSP_ERROR_RETURN (USB_STATUS_CONFIGURED == info.device_status, FSP_ERR_USB_FAILED)

    if (USB_HOST == g_usb_usbmode)
    {
#if ( (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST )
        p_info->endpoint = usb_hstd_pipe_to_epadr(&utr, p_ctrl->pipe);
        pipe_type = usb_cstd_get_pipe_type(&utr, p_ctrl->pipe);

        switch (pipe_type)
        {
            case USB_TYPFIELD_ISO:
                p_info->transfer_type = USB_TRANSFER_TYPE_ISO;                              /* Set Isochronous */
            break;
            case USB_TYPFIELD_BULK:
                p_info->transfer_type = USB_TRANSFER_TYPE_BULK;                             /* Set Bulk */
            break;
            case USB_TYPFIELD_INT:
                p_info->transfer_type = USB_TRANSFER_TYPE_INT;                              /* Set Interrupt */
            break;
            default:
            	result = FSP_ERR_USB_FAILED;
            break;
        }
        if(FSP_ERR_USB_FAILED != result)
        {
            p_info->maxpacketsize = usb_cstd_get_maxpacket_size(&utr, p_ctrl->pipe);     /* Set Max packet size */
            result = FSP_SUCCESS;
        }

#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }
    else
    {
#if ( (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI )
        /* Get PIPE Number from Endpoint address */
        p_info->endpoint   = (uint8_t)(g_usb_pipe_table[USB_CFG_USE_USBIP][p_ctrl->pipe].pipe_cfg & USB_EPNUMFIELD);  /* Set EP num. */
        if (USB_DIR_P_IN == (g_usb_pipe_table[USB_CFG_USE_USBIP][p_ctrl->pipe].pipe_cfg & USB_DIRFIELD))        /* Check dir */
        {
            p_info->endpoint |= USB_EP_DIR_IN;                            /* Set DIR IN */
        }
        pipe_type = usb_cstd_get_pipe_type(USB_NULL, p_ctrl->pipe);
        switch (pipe_type)
        {
            case USB_TYPFIELD_ISO:
                p_info->transfer_type = USB_TRANSFER_TYPE_ISO;                                 /* Set Isochronous */
            break;

            case USB_TYPFIELD_BULK:
                p_info->transfer_type = USB_TRANSFER_TYPE_BULK;                                /* Set Bulk */
            break;

            case USB_TYPFIELD_INT:
                p_info->transfer_type = USB_TRANSFER_TYPE_INT;                                 /* Set Interrupt */
            break;

            default:
            	result = FSP_ERR_USB_FAILED;
            break;
        }
        if(FSP_ERR_USB_FAILED != result)
        {
            p_info->maxpacketsize = usb_cstd_get_maxpacket_size(USB_NULL, p_ctrl->pipe); /* Set Max packet size */
            result = FSP_SUCCESS;
        }

#endif  /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI */
    }
    return result;
}

/**************************************************************************//**
 * @brief This API enables or disables pull-up of D+/D- line.
 *
 * @retval FSP_SUCCESS              Successful completion. (Pull-up enable/disable setting completed)
 * @retval FSP_ERR_USB_FAILED       The function could not be completed successfully.
 * @retval FSP_ERR_ASSERTION        Parameter error.
 ******************************************************************************/
fsp_err_t   R_USB_PullUp(uint8_t state)
{

#if (USB_CFG_MODE == USB_CFG_HOST)
	FSP_PARAMETER_NOT_USED(state);
    return FSP_ERR_USB_FAILED;
#else /* USB_CFG_MODE == USB_CFG_HOST */

    FSP_ERROR_RETURN(!(USB_HOST == g_usb_usbmode), FSP_ERR_USB_FAILED) /* Support Peri only. */

    /* Argument Checking */
    FSP_ASSERT(!((USB_ON != state) && (USB_OFF != state)))

    if (USB_ON == state)
    {
        hw_usb_pset_dprpu();
    }
    else
    {
        hw_usb_pclear_dprpu();
    }

    return FSP_SUCCESS;
#endif /* USB_CFG_MODE == USB_CFG_HOST */
} /* End of function R_USB_PullUp */

/**************************************************************************//**
 * @brief This API gets the module number.
 *
 * @retval FSP_SUCCESS              Successful completion.
 ******************************************************************************/
fsp_err_t R_USB_ModuleNumberGet(usb_ctrl_t * const p_api_ctrl, uint8_t *module_number)
{
    usb_instance_ctrl_t * p_ctrl = (usb_instance_ctrl_t *) p_api_ctrl;

    *module_number = p_ctrl->module_number;

    return FSP_SUCCESS;
}

/**************************************************************************//**
 * @brief This API gets the class type.
 *
 * @retval FSP_SUCCESS              Successful completion.
 ******************************************************************************/
fsp_err_t R_USB_ClassTypeGet(usb_ctrl_t * const p_api_ctrl, usb_class_t *class_type)
{
    usb_instance_ctrl_t * p_ctrl = (usb_instance_ctrl_t *) p_api_ctrl;

    *class_type = p_ctrl->type;

    return FSP_SUCCESS;
}

/**************************************************************************//**
 * @brief This API gets the device address.
 *
 * @retval FSP_SUCCESS              Successful completion.
 ******************************************************************************/
fsp_err_t R_USB_DeviceAddressGet(usb_ctrl_t * const p_api_ctrl, uint8_t *device_address)
{
    usb_instance_ctrl_t * p_ctrl = (usb_instance_ctrl_t *) p_api_ctrl;

    *device_address = p_ctrl->device_address;

    return FSP_SUCCESS;
}

/**************************************************************************//**
 * @brief This API gets the pipe number.
 *
 * @retval FSP_SUCCESS              Successful completion.
 ******************************************************************************/
fsp_err_t R_USB_PipeNumberGet(usb_ctrl_t * const p_api_ctrl, uint8_t *pipe_number)
{
    usb_instance_ctrl_t * p_ctrl = (usb_instance_ctrl_t *) p_api_ctrl;

    *pipe_number = p_ctrl->pipe;

    return FSP_SUCCESS;
}

/**************************************************************************//**
 * @brief This API gets the state of the device.
 *
 * @retval FSP_SUCCESS              Successful completion.
 ******************************************************************************/
fsp_err_t R_USB_DeviceStateGet(usb_ctrl_t * const p_api_ctrl, uint16_t *state)
{
    usb_instance_ctrl_t * p_ctrl = (usb_instance_ctrl_t *) p_api_ctrl;

    *state = p_ctrl->status;

    return FSP_SUCCESS;
}

/**************************************************************************//**
 * @brief This API gets the data size.
 *
 * @retval FSP_SUCCESS              Successful completion.
 ******************************************************************************/
fsp_err_t R_USB_DataSizeGet(usb_ctrl_t * const p_api_ctrl, uint32_t *data_size)
{
    usb_instance_ctrl_t * p_ctrl = (usb_instance_ctrl_t *) p_api_ctrl;

    *data_size = p_ctrl->data_size;

    return FSP_SUCCESS;
}

/**************************************************************************//**
 * @brief This API gets the setup type.
 *
 * @retval FSP_SUCCESS              Successful completion.
 ******************************************************************************/
fsp_err_t R_USB_SetupGet(usb_ctrl_t * const p_api_ctrl, usb_setup_t *setup)
{
    usb_instance_ctrl_t * p_ctrl = (usb_instance_ctrl_t *) p_api_ctrl;

    *setup = p_ctrl->setup;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup USB)
 **********************************************************************************************************************/

