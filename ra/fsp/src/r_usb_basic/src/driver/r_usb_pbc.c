/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/******************************************************************************
 * Includes <System Includes> , "Project Includes"
 ******************************************************************************/
#include <r_usb_basic.h>
#include <r_usb_basic_api.h>
#include <r_usb_basic_cfg.h>

#include "inc/r_usb_typedef.h"
#include "inc/r_usb_extern.h"
#include "../hw/inc/r_usb_bitdefine.h"
#include "../hw/inc/r_usb_reg_access.h"

#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)

 #if USB_CFG_BC == USB_CFG_ENABLE

/******************************************************************************
 * Macro definitions
 ******************************************************************************/
  #define USB_BC_DCD_TIME        (600U)
  #define USB_BC_DCD_DBNC        (11U)
  #define USB_BC_VDPSRC_ON       (42U)
  #define USB_BC_VDMSRC_DIS      (22U)
  #define USB_BC_VDMSRC_ON       (42U)

  #define USB_BC_DCD_TIMEOUT     (0U)
  #define USB_BC_DCD_COMP_SE0    (1U)

/******************************************************************************
 * Typedef definitions
 ******************************************************************************/

/* There is no typedef definition. */

/******************************************************************************
 * Exported global variables and functions (to be accessed by other files)
 ******************************************************************************/

/* variables */
uint16_t g_usb_bc_detect;

/* functions */
void usb_pstd_bc_detect_process(usb_utr_t * p_utr);

/******************************************************************************
 * Private global variables and functions
 ******************************************************************************/

/* functions */
uint8_t usb_pstd_bc_data_contact_detect(usb_utr_t * p_utr);
uint8_t usb_pstd_bc_primary_detection(usb_utr_t * p_utr);
uint8_t usb_pstd_bc_secondary_detection(usb_utr_t * p_utr);

/******************************************************************************
 * Imported global variables and functions (from other files)
 ******************************************************************************/

/******************************************************************************
 * Renesas Abstracted USB peripheral battery charging driver functions
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_pstd_bc_detect_process
 * Description     : Charging Port Detect Process
 * Arguments       : none
 * Return value    : none
 ******************************************************************************/
void usb_pstd_bc_detect_process (usb_utr_t * p_utr)
{
    usb_instance_ctrl_t ctrl;

    usb_pstd_bc_data_contact_detect(p_utr);

    if (usb_pstd_bc_primary_detection(p_utr))
    {
        if (usb_pstd_bc_secondary_detection(p_utr))
        {
            g_usb_bc_detect = USB_BCPORT_DCP;
        }
        else
        {
            g_usb_bc_detect = USB_BCPORT_CDP;
        }

        ctrl.module_number = p_utr->ip;
        usb_set_event(USB_STATUS_BC, &ctrl);
    }
    else
    {
        g_usb_bc_detect = USB_BCPORT_SDP;
    }
}                                      /* End of function usb_pstd_bc_detect_process() */

/******************************************************************************
 * Function Name   : usb_pstd_bc_data_contact_detect
 * Description     : Data Contact Detect
 * Arguments       : none
 * Return value    : uint8_t : DCD Complete Status
 ******************************************************************************/
uint8_t usb_pstd_bc_data_contact_detect (usb_utr_t * p_utr)
{
    uint16_t buf;
    uint16_t timer = 0;

  #if defined(USB_HIGH_SPEED_MODULE)
    hw_usb_set_cnen(p_utr->ip);
    hw_usb_set_bcctrl(p_utr, USB_IDPSRCE);
  #endif                               /* defined (USB_HIGH_SPEED_MODULE) */
    usb_cpu_delay_xms((uint16_t) 5);   /* wait stabilization */

    /* WAIT_LOOP */
    while (timer < USB_BC_DCD_TIME)    /* [BC1.2 Spec] DCD_TIMEOUT (300-900ms) */
    {
        buf = hw_usb_read_syssts(p_utr);
        if (USB_SE0 == (buf & USB_LNST))
        {
            usb_cpu_delay_xms((uint16_t) USB_BC_DCD_DBNC); /* [BC1.2 Spec] DCD_DBNC (min:10ms) */
            timer = (uint16_t) (timer + USB_BC_DCD_DBNC);
            buf   = hw_usb_read_syssts(p_utr);
            if (USB_SE0 == (buf & USB_LNST))
            {
  #if defined(USB_HIGH_SPEED_MODULE)
                hw_usb_clear_bcctrl(p_utr, USB_IDPSRCE);
  #endif                                    /* defined (USB_HIGH_SPEED_MODULE) */

                return USB_BC_DCD_COMP_SE0; /* Connected Data Line */
            }
        }

        usb_cpu_delay_xms((uint16_t) 1);
        timer++;
    }

  #if defined(USB_HIGH_SPEED_MODULE)
    hw_usb_clear_bcctrl(p_utr, USB_IDPSRCE);
  #endif                               /* defined (USB_HIGH_SPEED_MODULE) */

    return USB_BC_DCD_TIMEOUT;         /* DCD Timeout */
}                                      /* End of function usb_pstd_bc_data_contact_detect() */

/******************************************************************************
 * Function Name   : usb_pstd_bc_primary_detection
 * Description     : Primary Detection
 * Arguments       : none
 * Return value    : uint8_t : Detection Port
 ******************************************************************************/
uint8_t usb_pstd_bc_primary_detection (usb_utr_t * p_utr)
{
    uint16_t buf;
    uint8_t  detect_port = 0;
  #if defined(USB_HIGH_SPEED_MODULE)
    hw_usb_set_bcctrl(p_utr, (USB_VDPSRCE | USB_IDMSINKE));
  #endif                                             /* defined (USB_HIGH_SPEED_MODULE) */

    usb_cpu_delay_xms((uint16_t) USB_BC_VDPSRC_ON);  /* [BC1.2 Spec] TVDPSRC_ON (min:40ms) */
    buf = hw_usb_read_bcctrl(p_utr);
  #if defined(USB_HIGH_SPEED_MODULE)
    hw_usb_clear_bcctrl(p_utr, (USB_VDPSRCE | USB_IDMSINKE));
  #endif                                             /* defined (USB_HIGH_SPEED_MODULE) */
    usb_cpu_delay_xms((uint16_t) USB_BC_VDMSRC_DIS); /* [BC1.2 Spec] TVDMSRC_DIS (max:20ms) */

    if (buf & USB_CHGDETSTS)
    {
        detect_port = 1;                             /* Detected Charging Port */
    }
    else
    {
        detect_port = 0;                             /* Detected SDP */
    }

    return detect_port;
}                                                    /* End of function usb_pstd_bc_primary_detection() */

/******************************************************************************
 * Function Name   : usb_pstd_secondary_detection
 * Description     : Secondary Detection
 * Arguments       : none
 * Return value    : uint8_t : Detection Port
 ******************************************************************************/
uint8_t usb_pstd_bc_secondary_detection (usb_utr_t * p_utr)
{
    uint16_t buf;
    uint8_t  detect_port = 0;

  #if defined(USB_HIGH_SPEED_MODULE)
    hw_usb_set_bcctrl(p_utr, (USB_VDMSRCE | USB_IDPSINKE));
  #endif                                            /* defined (USB_HIGH_SPEED_MODULE) */
    usb_cpu_delay_xms((uint16_t) USB_BC_VDMSRC_ON); /* [BC1.2 Spec] TVDMSRC_ON (min:40ms) */
    buf = hw_usb_read_bcctrl(p_utr);
  #if defined(USB_HIGH_SPEED_MODULE)
    hw_usb_clear_bcctrl(p_utr, (USB_VDMSRCE | USB_IDPSINKE));
  #endif                                            /* defined (USB_HIGH_SPEED_MODULE) */

    if (buf & USB_PDDETSTS)
    {
        detect_port = 1;                            /* Detected DCP */
    }
    else
    {
        detect_port = 0;                            /* Detected CDP */
    }

    return detect_port;
}                                                   /* End of function usb_pstd_secondary_detection() */

 #endif /* USB_CFG_BC == USB_CFG_ENABLE */

#endif  /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */

/******************************************************************************
 * End of file
 ******************************************************************************/
