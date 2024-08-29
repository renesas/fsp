/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/******************************************************************************
 * Includes   <System Includes> , "Project Includes"
 ******************************************************************************/

#include <r_usb_basic.h>
#include <r_usb_basic_api.h>
#include <r_usb_basic_cfg.h>

#include "../driver/inc/r_usb_typedef.h"
#include "../driver/inc/r_usb_extern.h"
#include "inc/r_usb_bitdefine.h"
#include "inc/r_usb_reg_access.h"

#if (BSP_CFG_RTOS == 1)
 #include "../driver/inc/r_usb_cstd_rtos.h"
 #if defined(USB_CFG_OTG_USE)
  #include "ux_api.h"
 #endif                                /* defined(USB_CFG_OTG_USE) */
#endif                                 /* #if (BSP_CFG_RTOS == 1) */

#if ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE))
 #include "inc/r_usb_dmac.h"
#endif                                 /* ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE)) */

/******************************************************************************
 * Macro definitions
 ******************************************************************************/

#if defined(USB_CFG_HHID_USE) || defined(USB_CFG_PHID_USE)
 #if USB_CFG_DTC == USB_CFG_ENABLE
  #error  In HID class, can not set USB_CFG_ENABLE to USB_CFG_DTC in r_usb_basic_cfg.h.
 #endif                                /* USB_CFG_DTC == USB_CFG_ENABLE */

#endif                                 /* defined(USB_CFG_HHID_USE) || defined(USB_CFG_PHID_USE) */

#if USB_CFG_COMPLIANCE == USB_CFG_DISABLE
 #if USB_CFG_ELECTRICAL == USB_CFG_ENABLE
  #error  Can not set USB_CFG_DISABLE to USB_CFG_COMPLIANCE when setting USB_CFG_ENABLE to USB_CFG_ELECTRICAL \
    in r_usb_basic_cfg.h.

 #endif                                /* USB_CFG_ELECTRICAL == USB_CFG_ENABLE */
#endif                                 /* USB_CFG_COMPLIANCE == USB_CFG_DISABLE */

#if USB_CFG_BC == USB_CFG_DISABLE
 #if USB_CFG_DCP == USB_CFG_ENABLE
  #error  Can not set USB_CFG_DISABLE to USB_CFG_BC when setting USB_CFG_ENABLE to USB_CFG_DCP \
    in r_usb_basic_cfg.h.

 #endif                                /* USB_CFG_DCP == USB_CFG_ENABLE */
#endif                                 /* USB_CFG_BC == USB_CFG_DISABLE */

#if USB_CFG_DMA == USB_CFG_ENABLE
 #if USB_CFG_DTC == USB_CFG_ENABLE
  #error  Can not set USB_CFG_ENABLE to the definitions (USB_CFG_DMA and USB_CFG_DTC) at the same time \
    in r_usb_basic_cfg.h.

 #endif                                /* USB_CFG_DTC == USB_CFG_ENABLE */
#endif                                 /* USB_CFG_DMA == USB_CFG_ENABLE */

#if !defined(USB_CFG_OTG_USE)
 #if USB_CFG_MODE == USB_CFG_HOST
  #if defined(USB_CFG_PCDC_USE) || defined(USB_CFG_PPRN_USE) || defined(USB_CFG_PHID_USE) || \
    defined(USB_CFG_PMSC_USE) || defined(USB_CFG_PVND_USE)
   #error                                                                                                                  \
    Can not enable these definitions(USB_CFG_PCDC_USE/USB_CFG_PPRN_USE/USB_CFG_PHID_USE/USB_CFG_PMSC_USE/USB_CFG_PVND_USE) \
    when setting USB_MODE_HOST to USB_CFG_MODE in r_usb_basic_cfg.h.

  #endif                               /* defined(USB_CFG_PCDC_USE || USB_CFG_PPRN_USE || USB_CFG_PHID_USE || USB_CFG_PMSC_USE || USB_CFG_PVND_USE) */
 #endif                                /* USB_CFG_MODE == USB_MODE_HOST */

 #if USB_CFG_MODE == USB_CFG_PERI
  #if defined(USB_CFG_HCDC_USE) || defined(USB_CFG_HHID_USE) || defined(USB_CFG_HMSC_USE) || defined(USB_CFG_HVND_USE)
   #error  Can not enable these definitions(USB_CFG_HCDC_USE/USB_CFG_HHID_USE/USB_CFG_HMSC_USE/USB_CFG_HVND_USE) \
    when setting USB_MODE_PERI to USB_CFG_MODE in r_usb_basic_cfg.h.

  #endif                               /* defined(USB_CFG_HCDC_USE || USB_CFG_HHID_USE || USB_CFG_HMSC_USE || USB_CFG_HVND_USE) */
 #endif                                /* USB_CFG_MODE == USB_MODE_PERI */
#endif                                 /* !defined(USB_CFG_OTG_USE) */

#if (!defined(USB_HIGH_SPEED_MODULE))
 #if USB_CFG_ELECTRICAL == USB_CFG_ENABLE
  #error  Can not set USB_CFG_ENABLE to USB_CFG_ELECTRICAL when using other than Hi-speed module in r_usb_basic_cfg.h.
 #endif                                /* USB_CFG_ELECTRICAL == USB_CFG_ENABLE */

#endif                                 /* (!defined(USB_HIGH_SPEED_MODULE)) */

/******************************************************************************
 * Exported global variables (to be accessed by other files)
 ******************************************************************************/
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
static usb_cfg_t * g_p_usb_cfg_ip0;
 #if defined(USB_HIGH_SPEED_MODULE)
static usb_cfg_t * g_p_usb_cfg_ip1;
 #endif                                /* defined (USB_HIGH_SPEED_MODULE) */
#endif                                 /* ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST) */

/******************************************************************************
 * Private global variables and functions
 ******************************************************************************/
void usbfs_interrupt_handler(void);
void usbfs_resume_handler(void);
void usbfs_d0fifo_handler(void);
void usbfs_d1fifo_handler(void);
void usbhs_interrupt_handler(void);
void usbhs_d0fifo_handler(void);
void usbhs_d1fifo_handler(void);

#if (USB_CFG_TYPEC_FEATURE == USB_CFG_ENABLE)
void usb_typec_interrupt_handler(void);

#endif                                 /* USB_CFG_TYPEC_FEATURE == USB_CFG_ENABLE */

#if defined(USB_CFG_OTG_USE)
static usb_utr_t g_usb_irq_otg_msg;
static usb_utr_t g_usb_otg_detach_msg;
static uint16_t  g_usb_otg_frmnum_prev        = 0;
volatile uint8_t g_usb_otg_chattering_counter = 0;
volatile uint8_t g_usb_otg_hnp_counter        = 0;
#endif                                 /* defined(USB_CFG_OTG_USE) */

#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
static uint16_t g_usb_hstd_m0_reg_intenb0;
static uint16_t g_usb_hstd_m0_reg_intenb1;
 #if defined(USB_HIGH_SPEED_MODULE)
static uint16_t g_usb_hstd_m1_reg_intenb0;
static uint16_t g_usb_hstd_m1_reg_intenb1;
 #endif                                /* defined(USB_HIGH_SPEED_MODULE) */
#endif                                 /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */

#if (USB_CFG_TYPEC_FEATURE == USB_CFG_ENABLE)
uint32_t g_usb_typec_reg_tcs;
#endif                                 /* USB_CFG_TYPEC_FEATURE == USB_CFG_ENABLE */

/******************************************************************************
 * Renesas Abstracted RSK functions
 ******************************************************************************/

/**************************************************************************//**
 * @brief This function stops USB module.
 *
 * @retval FSP_SUCCESS           Success.
 * @retval FSP_ERR_USB_BUSY      USB is in use.
 ******************************************************************************/
fsp_err_t usb_module_start (uint8_t ip_type)
{
    if (USB_IP0 == ip_type)
    {
        FSP_ERROR_RETURN(0 != R_MSTP->MSTPCRB_b.MSTPB11, FSP_ERR_USB_BUSY)

        /* Enable power for USB0 */
        R_BSP_MODULE_START(FSP_IP_USBFS, 0);
    }
    else
    {
#if defined(USB_HIGH_SPEED_MODULE)
        FSP_ERROR_RETURN(0 != R_MSTP->MSTPCRB_b.MSTPB12, FSP_ERR_USB_BUSY)

        /* Enable power for USBA */
        R_BSP_MODULE_START(FSP_IP_USBHS, 0);
#else                                  /* defined (USB_HIGH_SPEED_MODULE) */
        FSP_ERROR_RETURN(0 != R_MSTP->MSTPCRB_b.MSTPB12, FSP_ERR_USB_BUSY)

        /* Enable power for USBA */
        R_BSP_MODULE_START(FSP_IP_USBFS, 0);
#endif                                 /* defined (USB_HIGH_SPEED_MODULE) */
    }

    return FSP_SUCCESS;
}

/******************************************************************************
 * End of function usb_module_start
 ******************************************************************************/

/**************************************************************************//**
 * @brief This function clear USB module register.
 *
 * @retval FSP_SUCCESS           Success.
 ******************************************************************************/
fsp_err_t usb_module_register_clear (uint8_t usb_ip)
{
    if (USB_IP0 == usb_ip)
    {
#if defined(USB_CFG_OTG_USE)
        USB_M0->DVSTCTR0    = (uint16_t) (USB_M0->DVSTCTR0 & (USB_EXICEN | USB_VBUSEN));
        USB_M0->DCPCTR      = USB_SQSET;
        USB_M0->PIPE_CTR[0] = 0;
        USB_M0->PIPE_CTR[1] = 0;
        USB_M0->PIPE_CTR[2] = 0;
        USB_M0->PIPE_CTR[3] = 0;
        USB_M0->PIPE_CTR[4] = 0;
        USB_M0->PIPE_CTR[5] = 0;
        USB_M0->PIPE_CTR[6] = 0;
        USB_M0->PIPE_CTR[7] = 0;
        USB_M0->PIPE_CTR[8] = 0;
        USB_M0->BRDYENB     = 0;
        USB_M0->NRDYENB     = 0;
        USB_M0->BEMPENB     = 0;
        USB_M0->INTENB0     = 0;
        USB_M0->INTENB1     = 0;
        USB_M0->BRDYSTS     = 0;
        USB_M0->NRDYSTS     = 0;
        USB_M0->BEMPSTS     = 0;
#else                                  /* defined(USB_CFG_OTG_USE) */
        USB_M0->DVSTCTR0    = 0;
        USB_M0->DCPCTR      = USB_SQSET;
        USB_M0->PIPE_CTR[0] = 0;
        USB_M0->PIPE_CTR[1] = 0;
        USB_M0->PIPE_CTR[2] = 0;
        USB_M0->PIPE_CTR[3] = 0;
        USB_M0->PIPE_CTR[4] = 0;
        USB_M0->PIPE_CTR[5] = 0;
        USB_M0->PIPE_CTR[6] = 0;
        USB_M0->PIPE_CTR[7] = 0;
        USB_M0->PIPE_CTR[8] = 0;
        USB_M0->BRDYENB     = 0;
        USB_M0->NRDYENB     = 0;
        USB_M0->BEMPENB     = 0;
        USB_M0->INTENB0     = 0;
        USB_M0->INTENB1     = 0;
        USB_M0->BRDYSTS     = 0;
        USB_M0->NRDYSTS     = 0;
        USB_M0->BEMPSTS     = 0;
        USB_M0->SYSCFG      = (uint16_t) (USB_M0->SYSCFG & (~USB_DPRPU));
        USB_M0->SYSCFG      = (uint16_t) (USB_M0->SYSCFG & (~USB_DRPD));
        USB_M0->SYSCFG      = (uint16_t) (USB_M0->SYSCFG & (~USB_DCFM));
        USB_M0->SYSCFG      = (uint16_t) (USB_M0->SYSCFG & (~USB_USBE));
#endif                                 /* defined(USB_CFG_OTG_USE) */
    }
    else
    {
#if defined(USB_CFG_OTG_USE)
        USB_M1->DVSTCTR0    = (uint16_t) (USB_M0->DVSTCTR0 & (USB_EXICEN | USB_VBUSEN));
        USB_M1->DCPCTR      = USB_SQSET;
        USB_M1->PIPE_CTR[0] = 0;
        USB_M1->PIPE_CTR[1] = 0;
        USB_M1->PIPE_CTR[2] = 0;
        USB_M1->PIPE_CTR[3] = 0;
        USB_M1->PIPE_CTR[4] = 0;
        USB_M1->PIPE_CTR[5] = 0;
        USB_M1->PIPE_CTR[6] = 0;
        USB_M1->PIPE_CTR[7] = 0;
        USB_M1->PIPE_CTR[8] = 0;
        USB_M1->BRDYENB     = 0;
        USB_M1->NRDYENB     = 0;
        USB_M1->BEMPENB     = 0;
        USB_M1->INTENB0     = 0;
        USB_M1->INTENB1     = 0;
        USB_M1->BRDYSTS     = 0;
        USB_M1->NRDYSTS     = 0;
        USB_M1->BEMPSTS     = 0;
#else                                  /* defined(USB_CFG_OTG_USE) */
        USB_M1->DVSTCTR0    = 0;
        USB_M1->DCPCTR      = USB_SQSET;
        USB_M1->PIPE_CTR[0] = 0;
        USB_M1->PIPE_CTR[1] = 0;
        USB_M1->PIPE_CTR[2] = 0;
        USB_M1->PIPE_CTR[3] = 0;
        USB_M1->PIPE_CTR[4] = 0;
        USB_M1->PIPE_CTR[5] = 0;
        USB_M1->PIPE_CTR[6] = 0;
        USB_M1->PIPE_CTR[7] = 0;
        USB_M1->PIPE_CTR[8] = 0;
        USB_M1->BRDYENB     = 0;
        USB_M1->NRDYENB     = 0;
        USB_M1->BEMPENB     = 0;
        USB_M1->INTENB0     = 0;
        USB_M1->INTENB1     = 0;
        USB_M1->BRDYSTS     = 0;
        USB_M1->NRDYSTS     = 0;
        USB_M1->BEMPSTS     = 0;
        USB_M1->SYSCFG      = (uint16_t) (USB_M1->SYSCFG & (~USB_DPRPU));
        USB_M1->SYSCFG      = (uint16_t) (USB_M1->SYSCFG & (~USB_DRPD));
        USB_M1->SYSCFG      = (uint16_t) (USB_M1->SYSCFG & (~USB_DCFM));
        USB_M1->SYSCFG      = (uint16_t) (USB_M1->SYSCFG & (~USB_USBE));
        USB_M1->LPSTS       = 0;
#endif                                 /* defined(USB_CFG_OTG_USE) */
    }

    return FSP_SUCCESS;
}

/**************************************************************************//**
 * @brief This function stops USB module.
 *
 * @retval FSP_SUCCESS           Success.
 * @retval FSP_ERR_USB_FAILED    The function could not be completed successfully.
 * @retval FSP_ERR_USB_NOT_OPEN  USB module is not open.
 * @retval FSP_ERR_USB_PARAMETER USB IP type is wrong.
 ******************************************************************************/
fsp_err_t usb_module_stop (uint8_t ip_type)
{
    usb_module_register_clear(ip_type);

    if (USB_IP0 == ip_type)
    {
        FSP_ERROR_RETURN(1 != R_MSTP->MSTPCRB_b.MSTPB11, FSP_ERR_USB_FAILED)
        FSP_ERROR_RETURN(0 == R_MSTP->MSTPCRB_b.MSTPB11, FSP_ERR_USB_NOT_OPEN)

        /* Disable power for USB0 */
        R_BSP_MODULE_STOP(FSP_IP_USBFS, 0);
    }
    else if (USB_IP1 == ip_type)
    {
#if defined(USB_HIGH_SPEED_MODULE)
        FSP_ERROR_RETURN(1 != R_MSTP->MSTPCRB_b.MSTPB12, FSP_ERR_USB_FAILED)
        FSP_ERROR_RETURN(0 == R_MSTP->MSTPCRB_b.MSTPB12, FSP_ERR_USB_NOT_OPEN)

        /* Enable power for USBA */
        R_BSP_MODULE_STOP(FSP_IP_USBHS, 0);
#endif                                 /* defined (USB_HIGH_SPEED_MODULE) */
    }
    else
    {
        return FSP_ERR_USB_PARAMETER;
    }

    return FSP_SUCCESS;
}

/******************************************************************************
 * End of function usb_module_stop
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_cpu_usbint_init
 * Description     : USB interrupt Initialize
 * Arguments       : uint8_t ip_type  : USB_IP0/USB_IP1
 * Return value    : void
 ******************************************************************************/
void usb_cpu_usbint_init (uint8_t ip_type, usb_cfg_t const * const cfg)
{
    if (USB_IP0 == ip_type)
    {
#if (!defined(USB_LDO_REGULATOR_MODULE))

        /* Deep standby USB monitor register
         * b0      SRPC0    USB0 single end control
         * b1      PRUE0    DP Pull-Up Resistor control
         *         (Use this bit during operation in Deep Software Standby mode.)
         * b2      Reserved 0
         * b3      DRPD0    DP/DM Pull-Down Resistor control
         *         (Use this bit during operation in Deep Software Standby mode.)
         * b4      FIXPHY0  USB0 transceiver output fix
         * b15-b5   Reserved 0
         * b16     DP0      USB0 DP input
         * b17     DM0      USB0 DM input
         * b19-b18 Reserved 0
         * b20     DOVCA0   USB0 OVRCURA input
         * b21     DOVCB0   USB0 OVRCURB input
         * b22     Reserved 0
         * b23     DVBSTS0  USB1 VBUS input
         * b31-b24 Reserved 0
         */
        USB_M0->DPUSR0R_FS_b.FIXPHY0 = 0U; /* USB0 Transceiver Output fixed */
#endif /* !defined(USB_LDO_REGULATOR_MODULE) */

        /* Interrupt enable register
         * b0 IEN0 Interrupt enable bit
         * b1 IEN1 Interrupt enable bit
         * b2 IEN2 Interrupt enable bit
         * b3 IEN3 Interrupt enable bit
         * b4 IEN4 Interrupt enable bit
         * b5 IEN5 Interrupt enable bit
         * b6 IEN6 Interrupt enable bit
         * b7 IEN7 Interrupt enable bit
         */
#if ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE))
        if (cfg->irq_d0 >= 0)
        {
            R_BSP_IrqCfgEnable(cfg->irq_d0, cfg->ipl_d0, (void *) cfg); /* Enable D0FIFO interrupt */
        }

        if (cfg->irq_d1 >= 0)
        {
            R_BSP_IrqCfgEnable(cfg->irq_d1, cfg->ipl_d1, (void *) cfg); /* Enable D1FIFO interrupt */
        }
#endif  /* ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE)) */

        if (cfg->irq_r >= 0)
        {
            R_BSP_IrqCfgEnable(cfg->irq_r, cfg->ipl_r, (void *) cfg); /* USBR enable */
        }

        if (cfg->irq >= 0)
        {
            R_BSP_IrqCfgEnable(cfg->irq, cfg->ipl, (void *) cfg); /* USBI enable */
        }

#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        g_p_usb_cfg_ip0 = (usb_cfg_t *) cfg;
#endif                                 /*((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)*/
    }

    if (ip_type == USB_IP1)
    {
#if defined(USB_HIGH_SPEED_MODULE)

        /* Interrupt enable register
         * b0 IEN0 Interrupt enable bit
         * b1 IEN1 Interrupt enable bit
         * b2 IEN2 Interrupt enable bit
         * b3 IEN3 Interrupt enable bit
         * b4 IEN4 Interrupt enable bit
         * b5 IEN5 Interrupt enable bit
         * b6 IEN6 Interrupt enable bit
         * b7 IEN7 Interrupt enable bit
         */
 #if ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE))
        if (cfg->hsirq_d0 >= 0)
        {
            R_BSP_IrqCfgEnable(cfg->hsirq_d0, cfg->hsipl_d0, (void *) cfg); /* Enable D0FIFO interrupt */
        }

        if (cfg->hsirq_d1 >= 0)
        {
            R_BSP_IrqCfgEnable(cfg->hsirq_d1, cfg->hsipl_d1, (void *) cfg); /* Enable D1FIFO interrupt */
        }
 #endif /* ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE)) */

        if (cfg->hsirq >= 0)
        {
            R_BSP_IrqCfgEnable(cfg->hsirq, cfg->hsipl, (void *) cfg); /* USBIR enable */
        }

 #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        g_p_usb_cfg_ip1 = (usb_cfg_t *) cfg;
 #endif                                /*((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)*/
#endif                                 /* defined (USB_HIGH_SPEED_MODULE) */
    }

#if (USB_CFG_TYPEC_FEATURE == USB_CFG_ENABLE)
    if (cfg->irq_typec >= 0)
    {
        R_BSP_IrqCfgEnable(cfg->irq_typec, cfg->ipl_typec, (void *) cfg); /* USBCC CCI enable */
    }
#endif /* USB_CFG_TYPEC_FEATURE == USB_CFG_ENABLE */
}

/******************************************************************************
 * End of function usb_cpu_usbint_init
 ******************************************************************************/

/******************************************************************************
 * TIMER function
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_cpu_delay_1us
 * Description     : 1us Delay timer
 * Arguments       : uint16_t  time        ; Delay time(*1us)
 * Return value    : none
 * Note            : Please change for your MCU
 ******************************************************************************/
void usb_cpu_delay_1us (uint16_t time)
{
    R_BSP_SoftwareDelay((uint32_t) time, BSP_DELAY_UNITS_MICROSECONDS);
}

/******************************************************************************
 * End of function usb_cpu_delay_1us
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_cpu_delay_xms
 * Description     : xms Delay timer
 * Arguments       : uint16_t  time        ; Delay time(*1ms)
 * Return value    : void
 * Note            : Please change for your MCU
 ******************************************************************************/
void usb_cpu_delay_xms (uint16_t time)
{
#if (BSP_CFG_RTOS == 0)
    R_BSP_SoftwareDelay((uint32_t) time, BSP_DELAY_UNITS_MILLISECONDS);
#elif (BSP_CFG_RTOS == 1)
    tx_thread_sleep(time);
#elif (BSP_CFG_RTOS == 2)
    vTaskDelay((TickType_t) (time / portTICK_PERIOD_MS));
#endif                                 /* #if (BSP_CFG_RTOS == 0) */
}

/******************************************************************************
 * End of function usb_cpu_delay_xms
 ******************************************************************************/

#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)

/******************************************************************************
 * Function Name   : usb_cpu_int_enable
 * Description     : USB Interrupt Enable
 * Arguments       : none
 * Return value    : none
 ******************************************************************************/
void usb_cpu_int_enable (void)
{
    /* Interrupt enable register (USB0 USBIO enable)
     * b0 IEN0 Interrupt enable bit
     * b1 IEN1 Interrupt enable bit
     * b2 IEN2 Interrupt enable bit
     * b3 IEN3 Interrupt enable bit
     * b4 IEN4 Interrupt enable bit
     * b5 IEN5 Interrupt enable bit
     * b6 IEN6 Interrupt enable bit
     * b7 IEN7 Interrupt enable bit
     */
    if (USB_NULL != g_p_usb_cfg_ip0)
    {
        if (USB_MODE_HOST == g_p_usb_cfg_ip0->usb_mode)
        {
            if (g_p_usb_cfg_ip0->irq >= 0)
            {
                R_BSP_IrqCfgEnable(g_p_usb_cfg_ip0->irq, g_p_usb_cfg_ip0->ipl, g_p_usb_cfg_ip0); /* USBI enable */
            }

            USB_M0->INTENB0 = g_usb_hstd_m0_reg_intenb0;
            USB_M0->INTENB1 = g_usb_hstd_m0_reg_intenb1;
        }
    }

 #if defined(USB_HIGH_SPEED_MODULE)

    /* Interrupt enable register (USB1 USBIO enable)
     * b0 IEN0 Interrupt enable bit
     * b1 IEN1 Interrupt enable bit
     * b2 IEN2 Interrupt enable bit
     * b3 IEN3 Interrupt enable bit
     * b4 IEN4 Interrupt enable bit
     * b5 IEN5 Interrupt enable bit
     * b6 IEN6 Interrupt enable bit
     * b7 IEN7 Interrupt enable bit
     */
    if (USB_NULL != g_p_usb_cfg_ip1)
    {
        if (USB_MODE_HOST == g_p_usb_cfg_ip1->usb_mode)
        {
            if (g_p_usb_cfg_ip1->hsirq >= 0)
            {
                R_BSP_IrqCfgEnable(g_p_usb_cfg_ip1->hsirq, g_p_usb_cfg_ip1->hsipl, g_p_usb_cfg_ip1); /* USBIR enable */
            }

            USB_M1->INTENB0 = g_usb_hstd_m1_reg_intenb0;
            USB_M1->INTENB1 = g_usb_hstd_m1_reg_intenb1;
        }
    }
 #endif                                /* defined (USB_HIGH_SPEED_MODULE) */
}

/******************************************************************************
 * End of function usb_cpu_int_enable
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_cpu_int_disable
 * Description     : USB Interrupt disable
 * Arguments       : none
 * Return value    : none
 ******************************************************************************/
void usb_cpu_int_disable (void)
{
    /* Interrupt enable register (USB0 USBIO disable)
     * b0 IEN0 Interrupt enable bit
     * b1 IEN1 Interrupt enable bit
     * b2 IEN2 Interrupt enable bit
     * b3 IEN3 Interrupt enable bit
     * b4 IEN4 Interrupt enable bit
     * b5 IEN5 Interrupt enable bit
     * b6 IEN6 Interrupt enable bit
     * b7 IEN7 Interrupt enable bit
     */
    if (USB_NULL != g_p_usb_cfg_ip0)
    {
        if (USB_MODE_HOST == g_p_usb_cfg_ip0->usb_mode)
        {
            g_usb_hstd_m0_reg_intenb0 = USB_M0->INTENB0;
            g_usb_hstd_m0_reg_intenb1 = USB_M0->INTENB1;
            USB_M0->INTENB0           = 0;
            USB_M0->INTENB1           = 0;

            R_BSP_IrqDisable(g_p_usb_cfg_ip0->irq); /* USBI enable */
        }
    }

 #if defined(USB_HIGH_SPEED_MODULE)

    /* Interrupt enable register (USB1 USBIO disable)
     * b0 IEN0 Interrupt enable bit
     * b1 IEN1 Interrupt enable bit
     * b2 IEN2 Interrupt enable bit
     * b3 IEN3 Interrupt enable bit
     * b4 IEN4 Interrupt enable bit
     * b5 IEN5 Interrupt enable bit
     * b6 IEN6 Interrupt enable bit
     * b7 IEN7 Interrupt enable bit
     */
    if (USB_NULL != g_p_usb_cfg_ip1)
    {
        if (USB_MODE_HOST == g_p_usb_cfg_ip1->usb_mode)
        {
            g_usb_hstd_m1_reg_intenb0 = USB_M1->INTENB0;
            g_usb_hstd_m1_reg_intenb1 = USB_M1->INTENB1;
            USB_M1->INTENB0           = 0;
            USB_M1->INTENB1           = 0;

            R_BSP_IrqDisable(g_p_usb_cfg_ip1->hsirq); /* USBIR enable */
        }
    }
 #endif /* defined (USB_HIGH_SPEED_MODULE) */
}

/******************************************************************************
 * End of function usb_cpu_int_disable
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_chattaring
 * Description     : Remove chattaring processing
 * Arguments       : uint16_t *syssts : SYSSTS register value
 * Return value    : LNST bit value
 ******************************************************************************/
uint16_t usb_chattaring (uint16_t * syssts)
{
    uint16_t lnst[4];

    /* WAIT_LOOP */
    while (1)
    {
        lnst[0] = (*syssts) & USB_LNST;
        usb_cpu_delay_xms((uint16_t) 1); /* 1ms wait */
        lnst[1] = (*syssts) & USB_LNST;
        usb_cpu_delay_xms((uint16_t) 1); /* 1ms wait */
        lnst[2] = (*syssts) & USB_LNST;
        if ((lnst[0] == lnst[1]) && (lnst[0] == lnst[2]))
        {
            break;
        }
    }

    return lnst[0];
}

/******************************************************************************
 * End of function usb_chattaring
 ******************************************************************************/

#endif                                 /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */

#if (BSP_CFG_RTOS == 1)
 #if defined(USB_CFG_OTG_USE)

/*******************************************************************************
 * Function Name: usb_otg_irq_callback
 * Description  : IRQ Interrupt service for attaching and detaching OTG A-device of USB_IP0
 * Arguments    : none
 * Return Value : none
 *******************************************************************************/
void usb_otg_irq_callback (external_irq_callback_args_t * p_args)
{
    usb_er_t    err;
    usb_utr_t * p_utr;
    uint16_t    syssts;

    (void) p_args;

    p_utr                        = &g_usb_irq_otg_msg;
    p_utr->msghead               = (usb_mh_t) USB_NULL;
    g_usb_otg_chattering_counter = 0;
    while (g_usb_otg_chattering_counter != 5)
    {
        ;
    }

    p_utr->ip = USB_IP0;
    syssts    = hw_usb_read_syssts(p_utr);
    if (USB_IDMON != (syssts & USB_IDMON))
    {
        /* For attaching */
        if (USB_MODE_PERI == g_usb_usbmode[0])
        {
            p_utr->msginfo = USB_MSG_HCD_INT;
            p_utr->keyword = USB_INT_OTG_HOST_INIT;
            err            = USB_SND_MSG(USB_HCD_MBX, (usb_msg_t *) p_utr);
        }
        else
        {
            return;
        }
    }
    else
    {
        /* For Detaching */
        /* Don't set "USB_NO" to "g_is_A_device[]" */
        tx_timer_deactivate(&g_usb_otg_detach_timer);
        g_is_A_cable_detach[0] = USB_YES;
        _ux_system_otg->ux_system_otg_device_type = UX_OTG_DEVICE_IDLE;
        (*g_p_otg_callback[0])(UX_OTG_MODE_IDLE);
        if (USB_MODE_PERI == g_usb_usbmode[0])
        {
            p_utr->msginfo = USB_MSG_PCD_INT;
            p_utr->keyword = USB_INT_VBINT;
            err            = USB_SND_MSG(USB_PCD_MBX, (usb_msg_t *) p_utr);
        }
        else
        {
            p_utr->keyword = USB_INT_DTCH0;
            err            = USB_SND_MSG(USB_HCD_MBX, (usb_msg_t *) p_utr);
        }
    }

    if (USB_OK != err)
    {
        USB_PRINTF1("### IRQ Interrupt for OTG snd_msg error (%ld)\n", err);
    }
}

  #if USB_NUM_USBIP == 2

/*******************************************************************************
 * Function Name: usb_otg_irq_callback
 * Description  : IRQ Interrupt service for attaching and detaching OTG A-device of USB_IP1
 * Arguments    : none
 * Return Value : none
 *******************************************************************************/
void usb2_otg_irq_callback (external_irq_callback_args_t * p_args)
{
    usb_er_t    err;
    usb_utr_t * p_utr;
    uint16_t    syssts;

    (void) p_args;

    p_utr          = &g_usb_irq_otg_msg;
    p_utr->msghead = (usb_mh_t) USB_NULL;

    g_usb_otg_chattering_counter = 0;
    while (g_usb_otg_chattering_counter != 5)
    {
        ;
    }

    p_utr->ip = USB_IP1;
    syssts    = hw_usb_read_syssts(p_utr);
    if (USB_IDMON != (syssts & USB_IDMON))
    {
        /* For attaching */
        if (USB_MODE_PERI == g_usb_usbmode[1])
        {
            p_utr->msginfo = USB_MSG_HCD_INT;
            p_utr->keyword = USB_INT_OTG_HOST_INIT;
            err            = USB_SND_MSG(USB_HCD_MBX, (usb_msg_t *) p_utr);
        }
        else
        {
            return;
        }
    }
    else
    {
        /* For Detaching */
        /* Don't set "USB_NO" to "g_is_A_device[]" */
        tx_timer_deactivate(&g_usb_otg_detach_timer);
        g_is_A_cable_detach[1] = USB_YES;
        _ux_system_otg->ux_system_otg_device_type = UX_OTG_DEVICE_IDLE;
        (*g_p_otg_callback[1])(UX_OTG_MODE_IDLE);
        if (USB_MODE_PERI == g_usb_usbmode[1])
        {
            p_utr->msginfo = USB_MSG_PCD_INT;
            p_utr->keyword = USB_INT_VBINT;
            err            = USB_SND_MSG(USB_PCD_MBX, (usb_msg_t *) p_utr);
        }
        else
        {
            p_utr->keyword = USB_INT_DTCH0;
            err            = USB_SND_MSG(USB_HCD_MBX, (usb_msg_t *) p_utr);
        }
    }

    if (USB_OK != err)
    {
        USB_PRINTF1("### IRQ Interrupt for OTG snd_msg error (%ld)\n", err);
    }
}

  #endif                               /* USB_NUM_USBIP == 2 */

/*******************************************************************************
 * Function Name: usb_otg_detach_timer (5ms interval)
 * Description  : The timer to detect that USB B-cable is detached when A device is Peripheral mode for USB IP0
 * Arguments    : args  : No use
 * Return Value : none
 *******************************************************************************/
VOID usb_otg_detach_timer (ULONG args)
{
    uint16_t    frmnum;
    usb_utr_t * p_utr;
    usb_er_t    err;

    (void) args;
    p_utr     = &g_usb_otg_detach_msg;
    p_utr->ip = USB_IP0;

    if (USB_MODE_PERI == g_usb_usbmode[0])
    {
        frmnum  = hw_usb_read_frmnum(p_utr);
        frmnum &= USB_FRNM;

        if ((g_usb_otg_frmnum_prev == frmnum) && (0 != frmnum))
        {
            g_usb_otg_frmnum_prev = 0;

            /* Detect the B-cable detaching */
            p_utr->ip      = USB_IP0;
            p_utr->msghead = (usb_mh_t) USB_NULL;
            p_utr->msginfo = USB_MSG_PCD_INT;

            p_utr->keyword = USB_INT_VBINT;
            err            = USB_SND_MSG(USB_PCD_MBX, (usb_msg_t *) p_utr);
            if (USB_OK != err)
            {
                USB_PRINTF1("### IRQ Interrupt for OTG isnd_msg error (%ld)\n", err);
            }
        }
        else
        {
            g_usb_otg_frmnum_prev = frmnum;
        }
    }
}

/*******************************************************************************
 * Function Name: usb_otg_chattering_timer (5ms interval)
 * Description  : The timer to detect that USB B-cable is detached when A device is Peripheral mode for USB IP0
 * Arguments    : args  : No use
 * Return Value : none
 *******************************************************************************/
VOID usb_otg_chattering_timer (ULONG args)
{
    (void) args;
    g_usb_otg_chattering_counter++;
}

/*******************************************************************************
 * Function Name: usb_otg_hnp_timer (10ms interval)
 * Description  : The timer to detect that USB B-cable is detached when A device is Peripheral mode for USB IP0
 * Arguments    : args  : No use
 * Return Value : none
 *******************************************************************************/
VOID usb_otg_hnp_timer (ULONG args)
{
    (void) args;
    g_usb_otg_hnp_counter++;
}

  #if USB_NUM_USBIP == 2

/*******************************************************************************
 * Function Name: usb2_otg_detach_timer (5ms interval)
 * Description  : The timer to detect that USB B-cable is detached when A device is Peripheral mode for USB IP1
 * Arguments    : args  : No use
 * Return Value : none
 *******************************************************************************/
VOID usb2_otg_detach_timer (ULONG args)
{
    uint16_t    frmnum;
    usb_utr_t * p_utr;
    usb_er_t    err;

    (void) args;
    p_utr = &g_usb_otg_detach_msg;

    p_utr->ip = USB_IP1;
    if (USB_MODE_PERI == g_usb_usbmode[1])
    {
        frmnum  = hw_usb_read_frmnum(p_utr);
        frmnum &= USB_FRNM;

        if ((g_usb_otg_frmnum_prev == frmnum) && (0 != frmnum))
        {
            /* Detect the B-cable detaching */
            p_utr->ip      = USB_IP1;
            p_utr->msghead = (usb_mh_t) USB_NULL;
            p_utr->msginfo = USB_MSG_PCD_INT;

            p_utr->keyword = USB_INT_VBINT;
            err            = USB_SND_MSG(USB_PCD_MBX, (usb_msg_t *) p_utr);
            if (USB_OK != err)
            {
                USB_PRINTF1("### IRQ Interrupt for OTG isnd_msg error (%ld)\n", err);
            }
        }
        else
        {
            g_usb_otg_frmnum_prev = frmnum;
        }
    }
}

  #endif                               /* USB_NUM_USBIP == 2 */

 #endif                                /* defined(USB_CFG_OTG_USE) */
#endif                                 /* if (BSP_CFG_RTOS == 1) */

/*******************************************************************************
 * Function Name: usbfs_usbi_isr
 * Description  : Interrupt service routine of USBF
 * Arguments    : none
 * Return Value : none
 *******************************************************************************/
static void usbfs_usbi_isr (void)
{
    /* Call USB interrupt routine */
    if (USB_MODE_HOST == g_usb_usbmode[USB_IP0])
    {
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        usb_hstd_usb_handler();        /* Call interrupt routine */
#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }
    else
    {
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        usb_pstd_usb_handler();        /* Call interrupt routine */
#endif  /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */
    }
}

/******************************************************************************
 * End of function usbfs_usbi_isr
 ******************************************************************************/

#if (USB_CFG_TYPEC_FEATURE == USB_CFG_ENABLE)

/*******************************************************************************
 * Function Name: usb_typec_isr
 * Description  : Interrupt service routine of USB TypeC
 * Arguments    : none
 * Return Value : none
 *******************************************************************************/
static void usb_typec_isr (void)
{
    if (USB_TYPEC_IES_ISCN == (R_USBCC->IES & USB_TYPEC_IES_ISCN))
    {
        R_USBCC->IES        = (R_USBCC->IES | USB_TYPEC_IES_ISCN);
        g_usb_typec_reg_tcs = R_USBCC->TCS;
        USB_M0->INTENB0    |= USB_VBSE;
    }
}

/******************************************************************************
 * End of function usb_typec_isr
 ******************************************************************************/
#endif                                 /* USB_CFG_TYPEC_FEATURE == USB_CFG_ENABLE */

#if defined(USB_HIGH_SPEED_MODULE)

/*******************************************************************************
 * Function Name: usbhs_usbir_isr
 * Description  : Interrupt service routine of USBF
 * Arguments    : none
 * Return Value : none
 *******************************************************************************/
static void usbhs_usbir_isr (void)
{
    /* Condition compilation by the difference of USB function */
    if (USB_MODE_HOST == g_usb_usbmode[USB_IP1])
    {
 #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
  #if USB_NUM_USBIP == 2
        usb2_hstd_usb_handler();       /* Call interrupt routine */
  #endif /* USB_NUM_USBIP == 2 */
 #endif /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }
    else
    {
 #if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        usb_pstd_usb_handler();
 #endif                                /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */
    }
}

/******************************************************************************
 * End of function usbhs_usbir_isr
 ******************************************************************************/
#endif                                 /* defined (USB_HIGH_SPEED_MODULE)*/

#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)

/******************************************************************************
 * Function Name   : usb_cpu_usb_int_hand_isr
 * Description     :
 * Arguments       : none
 * Return value    : none
 ******************************************************************************/
static void usb_cpu_usb_int_hand_isr (uint8_t usb_ip)
{
    hw_usb_pclear_sts_resm(usb_ip);
}                                      /* End of function usb_cpu_usb_int_hand_isr */

#endif  /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */

#if USB_CFG_DTC == USB_CFG_ENABLE

/******************************************************************************
 * Function Name   : usb_cpu_d0fifo_int_hand
 * Description     : D0FIFO interrupt Handler
 * Arguments       : none
 * Return value    : none
 ******************************************************************************/
static void usb_cpu_d0fifo_int_hand (void)
{
    usb_cstd_dma_send_complete(USB_IP0, USB_D0USE);
}

/******************************************************************************
 * End of function usb_cpu_d0fifo_int_hand
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_cpu_d1fifo_int_hand
 * Description     : D0FIFO interrupt Handler
 * Arguments       : none
 * Return value    : none
 ******************************************************************************/
static void usb_cpu_d1fifo_int_hand (void)
{
    usb_cstd_dma_send_complete(USB_IP0, USB_D1USE);
}

/******************************************************************************
 * End of function usb_cpu_d1fifo_int_hand
 ******************************************************************************/

 #if defined(USB_HIGH_SPEED_MODULE)

/******************************************************************************
 * Function Name   : usb2_cpu_d0fifo_int_hand
 * Description     : D0FIFO interrupt Handler
 * Arguments       : none
 * Return value    : none
 ******************************************************************************/
static void usb2_cpu_d0fifo_int_hand (void)
{
    usb_cstd_dma_send_complete(USB_IP1, USB_D0USE);
}

/******************************************************************************
 * End of function usb2_cpu_d0fifo_int_hand
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb2_cpu_d1fifo_int_hand
 * Description     : D0FIFO interrupt Handler
 * Arguments       : none
 * Return value    : none
 ******************************************************************************/
static void usb2_cpu_d1fifo_int_hand (void)
{
    usb_cstd_dma_send_complete(USB_IP1, USB_D1USE);
}

/******************************************************************************
 * End of function usb2_cpu_d1fifo_int_hand
 ******************************************************************************/
 #endif                                /* defined (USB_HIGH_SPEED_MODULE) */

#endif                                 /* USB_CFG_DTC == USB_CFG_ENABLE */

/******************************************************************************
 * Function Name   : usb_check_use_usba_module
 * Description     :
 * Arguments       : usb_utr_t *ptr     : Pointer to usb_utr_t structure
 * Return value    :
 ******************************************************************************/
bool usb_check_use_usba_module (usb_utr_t * ptr)
{
    bool ret_code = false;

    FSP_PARAMETER_NOT_USED(ptr);
#if defined(USB_HIGH_SPEED_MODULE)
    if (USB_IP1 == ptr->ip)
    {
        ret_code = true;
    }
#endif                                 /* defined (USB_HIGH_SPEED_MODULE) */

    return ret_code;
}                                      /* End of function usb_check_use_usba_module */

#if defined(USB_CFG_OTG_USE)
IRQn_Type g_otg_usb_fs_irq;
#endif /* defined(USB_CFG_OTG_USE) */

void usbfs_interrupt_handler (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type irq = R_FSP_CurrentIrqGet();
    R_BSP_IrqStatusClear(irq);
#if defined(USB_CFG_OTG_USE)
    g_otg_usb_fs_irq = irq;
#endif                                 /* defined(USB_CFG_OTG_USE) */

    usbfs_usbi_isr();

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

void usbfs_resume_handler (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type irq = R_FSP_CurrentIrqGet();
    R_BSP_IrqStatusClear(irq);

#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
    usb_cfg_t * p_cfg;

    p_cfg = (usb_cfg_t *) R_FSP_IsrContextGet(irq);
    usb_cpu_usb_int_hand_isr(p_cfg->module_number);
#endif                                 /* ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI) */

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

void usbfs_d0fifo_handler (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type irq = R_FSP_CurrentIrqGet();
    R_BSP_IrqStatusClear(irq);

#if USB_CFG_DTC == USB_CFG_ENABLE
    usb_cpu_d0fifo_int_hand();
#endif                                 /* USB_CFG_DTC == USB_CFG_ENABLE */

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

void usbfs_d1fifo_handler (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type irq = R_FSP_CurrentIrqGet();
    R_BSP_IrqStatusClear(irq);

#if USB_CFG_DTC == USB_CFG_ENABLE
    usb_cpu_d1fifo_int_hand();
#endif                                 /* USB_CFG_DTC == USB_CFG_ENABLE */

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

void usbhs_interrupt_handler (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type irq = R_FSP_CurrentIrqGet();
    R_BSP_IrqStatusClear(irq);

#if defined(USB_HIGH_SPEED_MODULE)
    usbhs_usbir_isr();
#endif                                 /* defined  (USB_HIGH_SPEED_MODULE) */

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

void usbhs_d0fifo_handler (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type irq = R_FSP_CurrentIrqGet();
    R_BSP_IrqStatusClear(irq);

#if USB_CFG_DTC == USB_CFG_ENABLE
 #if defined(USB_HIGH_SPEED_MODULE)
    usb2_cpu_d0fifo_int_hand();
 #endif                                /* defined (USB_HIGH_SPEED_MODULE) */
#endif                                 /* USB_CFG_DTC == USB_CFG_ENABLE */

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

void usbhs_d1fifo_handler (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type irq = R_FSP_CurrentIrqGet();
    R_BSP_IrqStatusClear(irq);

#if USB_CFG_DTC == USB_CFG_ENABLE
 #if defined(USB_HIGH_SPEED_MODULE)
    usb2_cpu_d1fifo_int_hand();
 #endif                                /* defined (USB_HIGH_SPEED_MODULE) */
#endif                                 /* USB_CFG_DTC == USB_CFG_ENABLE */

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

#if (USB_CFG_TYPEC_FEATURE == USB_CFG_ENABLE)
void usb_typec_interrupt_handler (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type irq = R_FSP_CurrentIrqGet();
    R_BSP_IrqStatusClear(irq);

    usb_typec_isr();

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

#endif                                 /* USB_CFG_TYPEC_FEATURE == USB_CFG_ENABLE */

/******************************************************************************
 * End  Of File
 ******************************************************************************/
