/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
#ifndef HW_USB_REG_ACCESS_H
 #define HW_USB_REG_ACCESS_H

 #ifdef __cplusplus
extern "C" {
 #endif

/******************************************************************************
 * Macro definitions
 ******************************************************************************/
 #define USB_BUFSIZE_BIT     (10U)
 #define USB_SUSPEND_MODE    (1U)
 #define USB_NORMAL_MODE     (0)

 #define USB0_CFIFO8         (USB_M0->CFIFOLL)
 #define USB0_D0FIFO8        (USB_M0->D0FIFOLL)
 #define USB0_D1FIFO8        (USB_M0->D1FIFOLL)
 #define USB0_CFIFO16        (USB_M0->CFIFOL)
 #define USB0_D0FIFO16       (USB_M0->D0FIFOL)
 #define USB0_D1FIFO16       (USB_M0->D1FIFOL)

 #if USB_CFG_ENDIAN == USB_CFG_LITTLE

  #define USB1_CFIFO8        (USB_M1->CFIFOHH)
  #define USB1_D0FIFO8       (USB_M1->D0FIFOHH)
  #define USB1_D1FIFO8       (USB_M1->D1FIFOHH)
  #define USB1_CFIFO16       (USB_M1->CFIFOH)
  #define USB1_D0FIFO16      (USB_M1->D0FIFOH)
  #define USB1_D1FIFO16      (USB_M1->D1FIFOH)

 #endif                                /* USB_CFG_ENDIAN == USB_CFG_LITTLE */

 #if USB_CFG_ENDIAN == USB_CFG_BIG
  #define USB1_CFIFO8        (USB_M1->CFIFOLL)
  #define USB1_D0FIFO8       (USB_M1->D0FIFOLL)
  #define USB1_D1FIFO8       (USB_M1->D1FIFOLL)
  #define USB1_CFIFO16       (USB_M1->CFIFOL)
  #define USB1_D0FIFO16      (USB_M1->D0FIFOL)
  #define USB1_D1FIFO16      (USB_M1->D1FIFOL)

 #endif                                /* USB_CFG_ENDIAN == USB_CFG_BIG */

 #define USB1_CFIFO32        (USB_M1->CFIFO)
 #define USB1_D0FIFO32       (USB_M1->D0FIFO)
 #define USB1_D1FIFO32       (USB_M1->D1FIFO)

 #if defined(USB_LDO_REGULATOR_MODULE)
  #define USB_LDO_REGULATOR_MODULE
 #endif                                /* USB_LDO_REGULATOR_MODULE */

/****************/
/*  INITIARIZE  */
/****************/
void hw_usb_hmodule_init(uint8_t usb_ip);
void hw_usb_pmodule_init(uint8_t usb_ip);

/************/
/*  SYSCFG  */
/************/
uint16_t hw_usb_read_syscfg(usb_utr_t * ptr);
void     hw_usb_write_syscfg(usb_utr_t * ptr, uint16_t data);
void     hw_usb_clear_cnen(usb_utr_t * ptr);
void     hw_usb_set_hse(usb_utr_t * ptr);
void     hw_usb_clear_hse(usb_utr_t * ptr);
void     hw_usb_set_dcfm(usb_utr_t * p_utr);
void     hw_usb_clear_dcfm(usb_utr_t * ptr);
void     hw_usb_set_drpd(usb_utr_t * ptr);
void     hw_usb_clear_drpd(usb_utr_t * ptr);
void     hw_usb_set_usbe(usb_utr_t * ptr);
void     hw_usb_clear_usbe(usb_utr_t * ptr);

 #if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
void hw_usb_set_cnen(uint8_t usb_ip);
void hw_usb_pset_dprpu(uint8_t usb_ip);
void hw_usb_pclear_dprpu(uint8_t usb_ip);
void hw_usb_pcontrol_dprpu(uint8_t usb_ip, uint8_t state);
void hw_usb_pcontrol_dcpctr_pid(uint8_t usb_ip, uint16_t data);

 #endif                                /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */

/************/
/*  BUSWAIT */
/************/
void hw_usb_set_buswait(usb_utr_t * ptr);

/************/
/*  SYSSTS0 */
/************/
uint16_t hw_usb_read_syssts(usb_utr_t * ptr);

/**************/
/*  DVSTCTR0  */
/**************/
uint16_t hw_usb_read_dvstctr(usb_utr_t * ptr);
void     hw_usb_write_dvstctr(usb_utr_t * ptr, uint16_t data);
void     hw_usb_rmw_dvstctr(usb_utr_t * ptr, uint16_t data, uint16_t bitptn);
void     hw_usb_clear_dvstctr(usb_utr_t * ptr, uint16_t bitptn);
void     hw_usb_set_vbout(usb_utr_t * ptr);
void     hw_usb_clear_vbout(usb_utr_t * ptr);
void     hw_usb_set_hnpbtoa(usb_utr_t * p_utr);
void     hw_usb_clear_hnpbtoa(usb_utr_t * p_utr);

 #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
void hw_usb_hset_rwupe(usb_utr_t * ptr);
void hw_usb_hclear_rwupe(usb_utr_t * ptr);
void hw_usb_hset_resume(usb_utr_t * ptr);
void hw_usb_hclear_resume(usb_utr_t * ptr);
void hw_usb_hset_uact(usb_utr_t * ptr);
void hw_usb_hclear_uact(usb_utr_t * ptr);
void hw_usb_hmodule_otg_init(uint8_t usb_ip);

 #endif                                /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
 #if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
void hw_usb_pset_wkup(uint8_t usb_ip);

 #endif                                /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */

/**************/
/*  TESTMODE  */
/**************/
void hw_usb_set_utst(usb_utr_t * ptr, uint16_t data);

/***************************/
/*  CFIFO, D0FIFO, D1FIFO  */
/***************************/
uint32_t hw_usb_read_fifo32(usb_utr_t * ptr, uint16_t pipemode);
void     hw_usb_write_fifo32(usb_utr_t * ptr, uint16_t pipemode, uint32_t data);
uint16_t hw_usb_read_fifo16(usb_utr_t * ptr, uint16_t pipemode);
void     hw_usb_write_fifo16(usb_utr_t * ptr, uint16_t pipemode, uint16_t data);
void     hw_usb_write_fifo8(usb_utr_t * ptr, uint16_t pipemode, uint8_t data);

/************************************/
/*  CFIFOSEL, D0FIFOSEL, D1FIFOSEL  */
/************************************/
uint16_t hw_usb_read_fifosel(usb_utr_t * ptr, uint16_t pipemode);
void     hw_usb_rmw_fifosel(usb_utr_t * ptr, uint16_t pipemode, uint16_t data, uint16_t bitptn);
void     hw_usb_set_dclrm(usb_utr_t * ptr, uint16_t pipemode);
void     hw_usb_clear_dclrm(usb_utr_t * ptr, uint16_t pipemode);
void     hw_usb_set_dreqe(usb_utr_t * ptr, uint16_t pipemode);
void     hw_usb_clear_dreqe(usb_utr_t * ptr, uint16_t pipemode);
void     hw_usb_set_mbw(usb_utr_t * ptr, uint16_t pipemode, uint16_t data);
void     hw_usb_set_curpipe(usb_utr_t * ptr, uint16_t pipemode, uint16_t pipeno);

/**********************************/
/* CFIFOCTR, D0FIFOCTR, D1FIFOCTR */
/**********************************/
uint16_t hw_usb_read_fifoctr(usb_utr_t * ptr, uint16_t pipemode);
void     hw_usb_set_bval(usb_utr_t * ptr, uint16_t pipemode);
void     hw_usb_set_bclr(usb_utr_t * ptr, uint16_t pipemode);

/*************/
/*  INTENB0  */
/*************/
uint16_t hw_usb_ReadIntenb(usb_utr_t * ptr);
void     hw_usb_write_intenb(usb_utr_t * ptr, uint16_t data);
void     hw_usb_set_intenb(usb_utr_t * ptr, uint16_t data);
void     hw_usb_clear_enb_vbse(usb_utr_t * ptr);
void     hw_usb_clear_enb_sofe(usb_utr_t * ptr);

 #if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
void hw_usb_pset_enb_rsme(uint8_t usb_ip);
void hw_usb_pclear_enb_rsme(uint8_t usb_ip);

 #endif                                /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */

/*************/
/*  BRDYENB  */
/*************/
void hw_usb_write_brdyenb(usb_utr_t * ptr, uint16_t data);
void hw_usb_set_brdyenb(usb_utr_t * ptr, uint16_t pipeno);
void hw_usb_clear_brdyenb(usb_utr_t * ptr, uint16_t pipeno);

/*************/
/*  NRDYENB  */
/*************/
void hw_usb_write_nrdyenb(usb_utr_t * ptr, uint16_t data);
void hw_usb_set_nrdyenb(usb_utr_t * ptr, uint16_t pipeno);
void hw_usb_clear_nrdyenb(usb_utr_t * ptr, uint16_t pipeno);

/*************/
/*  BEMPENB  */
/*************/
void hw_usb_write_bempenb(usb_utr_t * ptr, uint16_t data);
void hw_usb_set_bempenb(usb_utr_t * ptr, uint16_t pipeno);
void hw_usb_clear_bempenb(usb_utr_t * ptr, uint16_t pipeno);

/*************/
/*  SOFCFG   */
/*************/
void hw_usb_set_sofcfg(usb_utr_t * ptr, uint16_t data);

 #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
void hw_usb_hset_trnensel(usb_utr_t * ptr);

 #endif                                /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */

/*************/
/*  INTSTS0  */
/*************/
void hw_usb_write_intsts(usb_utr_t * ptr, uint16_t data);
void hw_usb_clear_sts_sofr(usb_utr_t * ptr);

 #if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
uint16_t hw_usb_read_intsts(uint8_t usb_ip);
void     hw_usb_pclear_sts_resm(uint8_t usb_ip);
void     hw_usb_pclear_sts_valid(uint8_t usb_ip);

 #endif                                /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */

/************/
/* BRDYSTS  */
/************/
uint16_t hw_usb_read_brdysts(usb_utr_t * ptr);
void     hw_usb_write_brdysts(usb_utr_t * pt, uint16_t data);
void     hw_usb_clear_sts_brdy(usb_utr_t * ptr, uint16_t pipeno);

/************/
/* NRDYSTS  */
/************/
void hw_usb_write_nrdy_sts(usb_utr_t * ptr, uint16_t data);
void hw_usb_clear_status_nrdy(usb_utr_t * ptr, uint16_t pipeno);

/************/
/* BEMPSTS  */
/************/
void hw_usb_write_bempsts(usb_utr_t * ptr, uint16_t data);
void hw_usb_clear_status_bemp(usb_utr_t * ptr, uint16_t pipeno);

/************/
/* FRMNUM   */
/************/
uint16_t hw_usb_read_frmnum(usb_utr_t * ptr);

 #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)

/************/
/* USBREQ   */
/************/
void hw_usb_hwrite_usbreq(usb_utr_t * ptr, uint16_t data);

/************/
/* USBVAL   */
/************/
void hw_usb_hset_usbval(usb_utr_t * ptr, uint16_t data);

/************/
/* USBINDX  */
/************/
void hw_usb_hset_usbindx(usb_utr_t * ptr, uint16_t data);

/************/
/* USBLENG  */
/************/
void hw_usb_hset_usbleng(usb_utr_t * ptr, uint16_t data);

 #endif                                /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */

 #if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)

/************/
/* USBREQ   */
/************/
uint16_t hw_usb_read_usbreq(uint8_t usb_ip);

/************/
/* USBVAL   */
/************/
uint16_t hw_usb_read_usbval(uint8_t usb_ip);

/************/
/* USBINDX  */
/************/
uint16_t hw_usb_read_usbindx(uint8_t usb_ip);

/************/
/* USBLENG  */
/************/
uint16_t hw_usb_read_usbleng(uint8_t usb_ip);

 #else
  #if defined(USB_CFG_HUVC_USE)

/************/
/* USBREQ   */
/************/
uint16_t hw_usb_read_usbreq(uint8_t usb_ip);

  #endif
 #endif                                /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */

/************/
/* DCPCFG   */
/************/
uint16_t hw_usb_read_dcpcfg(usb_utr_t * ptr);
void     hw_usb_write_dcpcfg(usb_utr_t * ptr, uint16_t data);

/************/
/* DCPMAXP  */
/************/
uint16_t hw_usb_read_dcpmaxp(usb_utr_t * ptr);
void     hw_usb_write_dcpmxps(usb_utr_t * ptr, uint16_t data);

/************/
/* DCPCTR   */
/************/
 #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
void hw_usb_hwrite_dcpctr(usb_utr_t * ptr, uint16_t data);
void hw_usb_hset_sureq(usb_utr_t * ptr);

 #endif                                /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
 #if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
uint16_t hw_usb_read_dcpctr(uint8_t usb_ip);
void     hw_usb_pset_ccpl(uint8_t usb_ip);

 #endif                                /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */

/************/
/* PIPESEL  */
/************/
void hw_usb_write_pipesel(usb_utr_t * ptr, uint16_t data);

/************/
/* PIPECFG  */
/************/
uint16_t hw_usb_read_pipecfg(usb_utr_t * ptr);
void     hw_usb_write_pipecfg(usb_utr_t * ptr, uint16_t data);

/************/
/* PIPEBUF  */
/************/
void     hw_usb_write_pipebuf(usb_utr_t * ptr, uint16_t data);
uint16_t hw_usb_read_pipebuf(usb_utr_t * ptr);

/************/
/* PIPEMAXP */
/************/
uint16_t hw_usb_read_pipemaxp(usb_utr_t * ptr);
void     hw_usb_write_pipemaxp(usb_utr_t * ptr, uint16_t data);

/************/
/* PIPEPERI */
/************/
void hw_usb_write_pipeperi(usb_utr_t * ptr, uint16_t data);

/********************/
/* DCPCTR, PIPEnCTR */
/********************/
uint16_t hw_usb_read_pipectr(usb_utr_t * ptr, uint16_t pipeno);
void     hw_usb_write_pipectr(usb_utr_t * ptr, uint16_t pipeno, uint16_t data);
void     hw_usb_set_csclr(usb_utr_t * ptr, uint16_t pipeno);
void     hw_usb_set_aclrm(usb_utr_t * ptr, uint16_t pipeno);
void     hw_usb_clear_aclrm(usb_utr_t * ptr, uint16_t pipeno);
void     hw_usb_set_sqclr(usb_utr_t * ptr, uint16_t pipeno);
void     hw_usb_set_sqset(usb_utr_t * ptr, uint16_t pipeno);
void     hw_usb_set_pid(usb_utr_t * ptr, uint16_t pipeno, uint16_t data);
void     hw_usb_clear_pid(usb_utr_t * ptr, uint16_t pipeno, uint16_t data);

/************/
/* PIPEnTRE */
/************/
void hw_usb_set_trenb(usb_utr_t * ptr, uint16_t pipeno);
void hw_usb_clear_trenb(usb_utr_t * ptr, uint16_t pipeno);
void hw_usb_set_trclr(usb_utr_t * ptr, uint16_t pipeno);

/************/
/* PIPEnTRN */
/************/
void hw_usb_write_pipetrn(usb_utr_t * ptr, uint16_t pipeno, uint16_t data);

/************/
/* BCCTRL   */
/************/
void      hw_usb_set_bcctrl(usb_utr_t * ptr, uint16_t data);
void      hw_usb_clear_bcctrl(usb_utr_t * ptr, uint16_t data);
uint16_t  hw_usb_read_bcctrl(usb_utr_t * ptr);
void      hw_usb_set_vdmsrce(usb_utr_t * ptr);
void      hw_usb_clear_vdmsrce(usb_utr_t * ptr);
void      hw_usb_set_idpsinke(usb_utr_t * ptr);
void      hw_usb_set_suspendm(uint8_t usb_ip);
void      hw_usb_clear_suspm(uint8_t usb_ip);
void      hw_usb_clear_idpsinke(usb_utr_t * ptr);
void      hw_usb_set_vdcen(void);
void      hw_usb_clear_vdcen(void);
void      hw_usb_set_uckselc(void);
void      hw_usb_clear_uckselc(void);
fsp_err_t hw_usb_typec_module_init(void);
void      hw_usb_typec_module_uninit(void);

 #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
void hw_usb_hset_dcpmode(usb_utr_t * ptr);

 #endif                                /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */

/**********************************/
/*  DMA0CFG, DMA1CFG  for 597ASSP */
/**********************************/
void hw_usb_write_dmacfg(usb_utr_t * ptr, uint16_t pipemode, uint16_t data);

 #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)

/*************/
/*  INTENB1  */
/*************/
void hw_usb_hwrite_intenb(usb_utr_t * ptr, uint16_t data);
void hw_usb_hset_enb_ovrcre(usb_utr_t * ptr);
void hw_usb_hclear_enb_ovrcre(usb_utr_t * ptr);
void hw_usb_hset_enb_bchge(usb_utr_t * ptr);
void hw_usb_hclear_enb_bchge(usb_utr_t * ptr);
void hw_usb_hset_enb_dtche(usb_utr_t * ptr);
void hw_usb_hclear_enb_dtche(usb_utr_t * ptr);
void hw_usb_hset_enb_attche(usb_utr_t * ptr);
void hw_usb_hclear_enb_attche(usb_utr_t * ptr);
void hw_usb_hset_enb_signe(usb_utr_t * ptr);
void hw_usb_hset_enb_sacke(usb_utr_t * ptr);
void hw_usb_hset_enb_pddetinte(usb_utr_t * ptr);

/*************/
/*  INTSTS1  */
/*************/
void hw_usb_hwrite_intsts(usb_utr_t * ptr, uint16_t data);
void hw_usb_hclear_sts_ovrcr(usb_utr_t * ptr);
void hw_usb_hclear_sts_bchg(usb_utr_t * ptr);
void hw_usb_hclear_sts_dtch(usb_utr_t * ptr);
void hw_usb_hclear_sts_attch(usb_utr_t * ptr);
void hw_usb_hclear_sts_sign(usb_utr_t * ptr);
void hw_usb_hclear_sts_sack(usb_utr_t * ptr);
void hw_usb_hclear_sts_pddetint(usb_utr_t * ptr);

/************/
/* DEVADDn  */
/************/
uint16_t hw_usb_hread_devadd(usb_utr_t * ptr, uint16_t devsel);
void     hw_usb_hrmw_devadd(usb_utr_t * ptr, uint16_t devsel, uint16_t data, uint16_t width);
void     hw_usb_hset_usbspd(usb_utr_t * ptr, uint16_t devsel, uint16_t data);

 #endif                                /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */

 #ifdef __cplusplus
}
 #endif

#endif                                 /* HW_USB_REG_ACCESS_H */

/******************************************************************************
 * End of file
 ******************************************************************************/
