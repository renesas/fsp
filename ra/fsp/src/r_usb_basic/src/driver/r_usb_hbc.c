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
/******************************************************************************
 Includes <System Includes> , "Project Includes"
 ******************************************************************************/

#include <r_usb_basic.h>
#include <r_usb_basic_api.h>

#include "inc/r_usb_typedef.h"
#include "inc/r_usb_extern.h"
#include "../hw/inc/r_usb_bitdefine.h"
#include "../hw/inc/r_usb_reg_access.h"

#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
#if USB_CFG_BC == USB_CFG_ENABLE
/******************************************************************************
 Macro definitions
 ******************************************************************************/
/* PD Detect Define */
#define USB_BC_NODET        (0x00U)
#define USB_BC_PDDET        (0x01U)

/******************************************************************************
 Typedef definitions
 ******************************************************************************/

/******************************************************************************
 Private global variables and functions
 ******************************************************************************/

/******************************************************************************
 Exported global variables and functions (to be accessed by other files)
 ******************************************************************************/
/* variables */
usb_bc_status_t g_usb_hstd_bc[2U];

/* functions */
void usb_hstd_pddetint_process(usb_utr_t *ptr);

/* BC State change function table */
void (*usb_hstd_bc_func[USB_BC_STATE_MAX][USB_BC_EVENT_MAX])(usb_utr_t *ptr) =
{
    /* VBUS_ON              ATTACH               DETACH */
    {   usb_hstd_bc_init_vb , usb_hstd_bc_err , usb_hstd_bc_err},   /* USB_BC_STATE_INIT */
    {   usb_hstd_bc_err , usb_hstd_bc_det_at , usb_hstd_bc_err},    /* USB_BC_STATE_DET */
    {   usb_hstd_bc_err , usb_hstd_bc_err , usb_hstd_bc_cdp_dt},    /* USB_BC_STATE_CDP */
    {   usb_hstd_bc_err , usb_hstd_bc_err , usb_hstd_bc_sdp_dt},    /* USB_BC_STATE_SDP */
    {   usb_hstd_bc_err , usb_hstd_bc_err , usb_hstd_bc_err}        /* USB_BC_STATE_DCP */
};


/******************************************************************************
 Renesas Abstracted USB host battery charging driver functions
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hstd_pddetint_process
 Description     : PDDETINT process
 Arguments       : usb_utr_t *ptr : Pointer to usb_utr_t structure.
 Return          : none
 ******************************************************************************/
void usb_hstd_pddetint_process(usb_utr_t *ptr)
{
    uint16_t buf[3];

    /* PDDETSTS chattering cut */
    /* WAIT_LOOP */
    do
    {
        buf[0] = hw_usb_read_bcctrl(ptr);
        usb_cpu_delay_xms(1);
        buf[1] = hw_usb_read_bcctrl(ptr);
        usb_cpu_delay_xms(1);
        buf[2] = hw_usb_read_bcctrl(ptr);
    }
    while (((buf[0] & USB_PDDETSTS) != (buf[1] & USB_PDDETSTS)) ||
            ((buf[1] & USB_PDDETSTS) != (buf[2] & USB_PDDETSTS)));

    if (USB_PDDETSTS == (buf[0] & USB_PDDETSTS)) /* VDPSRC Detect */
    {
        if (USB_VDMSRCE != (buf[0] & USB_VDMSRCE) )
        {
            hw_usb_set_vdmsrce(ptr);
        }
    }
    else
        /* VDPSRC Not detect */
    {
        if (USB_VDMSRCE == (buf[0] & USB_VDMSRCE) )
        {
            hw_usb_clear_vdmsrce(ptr);
            g_usb_hstd_bc[ptr->ip].pd_detect = USB_BC_PDDET;
        }
    }
} /* End of function usb_hstd_pddetint_process() */

/******************************************************************************
 Function Name   : usb_hstd_bc_err
 Description     : BC State change function [ERROR]
 Arguments       : usb_utr_t *ptr : Pointer to usb_utr_t structure.
 Return          : none
 ******************************************************************************/
void usb_hstd_bc_err(usb_utr_t *ptr)
{
	(void)*ptr;
} /* End of function usb_hstd_bc_err() */

/******************************************************************************
 Function Name   : usb_hstd_bc_init_vb
 Description     : BC State change function [INIT] [VbusOn]
 Arguments       : usb_utr_t *ptr : Pointer to usb_utr_t structure.
 Return          : none
 ******************************************************************************/
void usb_hstd_bc_init_vb(usb_utr_t *ptr)
{
#if USB_CFG_DCP == USB_CFG_ENABLE
        g_usb_hstd_bc[ptr->ip].state = USB_BC_STATE_DCP;
        usb_hstd_bc_dcp_entry(ptr);
#else   /* USB_CFG_DCP == USB_CFG_ENABLE */
        g_usb_hstd_bc[ptr->ip].state = USB_BC_STATE_DET;
        usb_hstd_bc_det_entry(ptr);

#endif  /* USB_CFG_DCP == USB_CFG_ENABLE */

} /* End of function usb_hstd_bc_init_vb() */

/******************************************************************************
 Function Name   : usb_hstd_bc_det_at
 Description     : BC State change function [DET] [Attach]
 Arguments       : usb_utr_t *ptr : Pointer to usb_utr_t structure.
 Return          : none
 ******************************************************************************/
void usb_hstd_bc_det_at(usb_utr_t *ptr)
{
    usb_hstd_bc_det_exit(ptr);

    if (g_usb_hstd_bc[ptr->ip].pd_detect)
    {
        g_usb_hstd_bc[ptr->ip].state = USB_BC_STATE_CDP;
        usb_hstd_bc_cdp_entry(ptr);
    }
    else
    {
        g_usb_hstd_bc[ptr->ip].state = USB_BC_STATE_SDP;
        usb_hstd_bc_sdp_entry(ptr);
    }
} /* End of function usb_hstd_bc_det_at() */

/******************************************************************************
 Function Name   : usb_hstd_bc_cdp_dt
 Description     : BC State change function [CDP] [Detach]
 Arguments       : usb_utr_t *ptr : Pointer to usb_utr_t structure.
 Return          : none
 ******************************************************************************/
void usb_hstd_bc_cdp_dt(usb_utr_t *ptr)
{
    usb_hstd_bc_cdp_exit(ptr);
    g_usb_hstd_bc[ptr->ip].state = USB_BC_STATE_DET;
    usb_hstd_bc_det_entry(ptr);
} /* End of function usb_hstd_bc_cdp_dt() */

/******************************************************************************
 Function Name   : usb_hstd_bc_sdp_dt
 Description     : BC State change function [SDP] [Detach]
 Arguments       : usb_utr_t *ptr : Pointer to usb_utr_t structure.
 Return          : none
 ******************************************************************************/
void usb_hstd_bc_sdp_dt(usb_utr_t *ptr)
{
    usb_hstd_bc_sdp_exit(ptr);
    g_usb_hstd_bc[ptr->ip].state = USB_BC_STATE_DET;
    usb_hstd_bc_det_entry(ptr);
} /* End of function usb_hstd_bc_sdp_dt() */

/******************************************************************************
 Function Name   : usb_hstd_bc_det_entry
 Description     : BC State entry function [DET]
 Arguments       : usb_utr_t *ptr : Pointer to usb_utr_t structure.
 Return          : none
 ******************************************************************************/
void usb_hstd_bc_det_entry(usb_utr_t *ptr)
{
    hw_usb_set_idpsinke(ptr);
    hw_usb_hclear_sts_pddetint(ptr);
    hw_usb_hset_enb_pddetinte(ptr);
} /* End of function usb_hstd_bc_det_entry() */

/******************************************************************************
 Function Name   : usb_hstd_bc_det_exit
 Description     : BC State exit function [DET]
 Arguments       : usb_utr_t *ptr : Pointer to usb_utr_t structure.
 Return          : none
 ******************************************************************************/
void usb_hstd_bc_det_exit(usb_utr_t *ptr)
{
    hw_usb_hset_enb_pddetinte(ptr);
    hw_usb_hclear_sts_pddetint(ptr);
    hw_usb_clear_idpsinke(ptr);
} /* End of function usb_hstd_bc_det_exit() */

/******************************************************************************
 Function Name   : usb_hstd_bc_cdp_entry
 Description     : BC State entry function [CDP]
 Arguments       : usb_utr_t *ptr : Pointer to usb_utr_t structure.
                 : uint16_t  port : Port number.
 Return          : none
 ******************************************************************************/
void usb_hstd_bc_cdp_entry(usb_utr_t *ptr)
{
	(void)*ptr;
} /* End of function usb_hstd_bc_cdp_entry() */

/******************************************************************************
 Function Name   : usb_hstd_bc_cdp_exit
 Description     : BC State exit function [CDP]
 Arguments       : usb_utr_t *ptr : Pointer to usb_utr_t structure.
 Return          : none
 ******************************************************************************/
void usb_hstd_bc_cdp_exit(usb_utr_t *ptr)
{
    g_usb_hstd_bc[ptr->ip].pd_detect = USB_BC_NODET;
} /* End of function usb_hstd_bc_cdp_exit() */

/******************************************************************************
 Function Name   : usb_hstd_bc_sdp_entry
 Description     : BC State entry function [SDP]
 Arguments       : usb_utr_t *ptr : Pointer to usb_utr_t structure.
 Return          : none
 ******************************************************************************/
void usb_hstd_bc_sdp_entry(usb_utr_t *ptr)
{
	(void)*ptr;
} /* End of function usb_hstd_bc_sdp_entry() */

/******************************************************************************
 Function Name   : usb_hstd_bc_sdp_exit
 Description     : BC State exit function [SDP]
 Arguments       : usb_utr_t *ptr : Pointer to usb_utr_t structure.
 Return          : none
 ******************************************************************************/
void usb_hstd_bc_sdp_exit(usb_utr_t *ptr)
{
	(void)*ptr;
} /* End of function usb_hstd_bc_sdp_exit() */

/******************************************************************************
 Function Name   : usb_hstd_bc_dcp_entry
 Description     : BC State entry function [DCP]
 Arguments       : usb_utr_t *ptr : Pointer to usb_utr_t structure.
 Return          : none
 ******************************************************************************/
void usb_hstd_bc_dcp_entry(usb_utr_t *ptr)
{
    hw_usb_clear_drpd(ptr);
    hw_usb_hset_dcpmode(ptr);
} /* End of function usb_hstd_bc_dcp_entry() */

#endif  /* USB_CFG_BC == USB_CFG_ENABLE */
#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */

/******************************************************************************
 End of file
 ******************************************************************************/
