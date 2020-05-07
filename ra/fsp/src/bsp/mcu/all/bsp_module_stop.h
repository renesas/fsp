/***********************************************************************************************************************
 * Copyright [2020] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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

#ifndef BSP_MODULE_H
#define BSP_MODULE_H

/** Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/*******************************************************************************************************************//**
 * @addtogroup BSP_MCU
 * @{
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Cancels the module stop state.
 *
 * @param      ip       fsp_ip_t enum value for the module to be stopped
 * @param      channel  The channel. Use channel 0 for modules without channels.
 **********************************************************************************************************************/
#define R_BSP_MODULE_START(ip, channel)         {FSP_CRITICAL_SECTION_DEFINE;                          \
                                                 FSP_CRITICAL_SECTION_ENTER;                           \
                                                 BSP_MSTP_REG_ ## ip &= ~BSP_MSTP_BIT_ ## ip(channel); \
                                                 FSP_CRITICAL_SECTION_EXIT;}

/*******************************************************************************************************************//**
 * Enables the module stop state.
 *
 * @param      ip       fsp_ip_t enum value for the module to be stopped
 * @param      channel  The channel. Use channel 0 for modules without channels.
 **********************************************************************************************************************/
#define R_BSP_MODULE_STOP(ip, channel)          {FSP_CRITICAL_SECTION_DEFINE;                         \
                                                 FSP_CRITICAL_SECTION_ENTER;                          \
                                                 BSP_MSTP_REG_ ## ip |= BSP_MSTP_BIT_ ## ip(channel); \
                                                 FSP_CRITICAL_SECTION_EXIT;}

/** @} (end addtogroup BSP_MCU) */

#define BSP_MSTP_REG_FSP_IP_GPT        R_MSTP->MSTPCRD
#define BSP_MSTP_BIT_FSP_IP_GPT(channel)        ((BSP_FEATURE_BSP_MSTP_GPT_MSTPD5_MAX_CH >= \
                                                  channel) ? (1U << 5U) : (1U << 6U));

#define BSP_MSTP_REG_FSP_IP_DMAC       R_SYSTEM->MSTPCRA
#define BSP_MSTP_BIT_FSP_IP_DMAC(channel)       (1U << (22U));
#define BSP_MSTP_REG_FSP_IP_DTC        R_SYSTEM->MSTPCRA
#define BSP_MSTP_BIT_FSP_IP_DTC(channel)        (1U << (22U));
#define BSP_MSTP_REG_FSP_IP_CAN        R_MSTP->MSTPCRB
#define BSP_MSTP_BIT_FSP_IP_CAN(channel)        (1U << (2U - channel));
#define BSP_MSTP_REG_FSP_IP_IRDA       R_MSTP->MSTPCRB
#define BSP_MSTP_BIT_FSP_IP_IRDA(channel)       (1U << (5U - channel));
#define BSP_MSTP_REG_FSP_IP_QSPI       R_MSTP->MSTPCRB
#define BSP_MSTP_BIT_FSP_IP_QSPI(channel)       (1U << (6U - channel));
#define BSP_MSTP_REG_FSP_IP_IIC        R_MSTP->MSTPCRB
#define BSP_MSTP_BIT_FSP_IP_IIC(channel)        (1U << (9U - channel));
#define BSP_MSTP_REG_FSP_IP_USBFS      R_MSTP->MSTPCRB
#define BSP_MSTP_BIT_FSP_IP_USBFS(channel)      (1U << (11U - channel));
#define BSP_MSTP_REG_FSP_IP_USBHS      R_MSTP->MSTPCRB
#define BSP_MSTP_BIT_FSP_IP_USBHS(channel)      (1U << (12U - channel));
#define BSP_MSTP_REG_FSP_IP_EPTPC      R_MSTP->MSTPCRB
#define BSP_MSTP_BIT_FSP_IP_EPTPC(channel)      (1U << (13U - channel));
#define BSP_MSTP_REG_FSP_IP_ETHER      R_MSTP->MSTPCRB
#define BSP_MSTP_BIT_FSP_IP_ETHER(channel)      (1U << (15U - channel));
#define BSP_MSTP_REG_FSP_IP_SPI        R_MSTP->MSTPCRB
#define BSP_MSTP_BIT_FSP_IP_SPI(channel)        (1U << (19U - channel));
#define BSP_MSTP_REG_FSP_IP_SCI        R_MSTP->MSTPCRB
#define BSP_MSTP_BIT_FSP_IP_SCI(channel)        (1U << (31U - channel));
#define BSP_MSTP_REG_FSP_IP_CAC        R_MSTP->MSTPCRC
#define BSP_MSTP_BIT_FSP_IP_CAC(channel)        (1U << (0U - channel));
#define BSP_MSTP_REG_FSP_IP_CRC        R_MSTP->MSTPCRC
#define BSP_MSTP_BIT_FSP_IP_CRC(channel)        (1U << (1U - channel));
#define BSP_MSTP_REG_FSP_IP_PDC        R_MSTP->MSTPCRC
#define BSP_MSTP_BIT_FSP_IP_PDC(channel)        (1U << (2U - channel));
#define BSP_MSTP_REG_FSP_IP_CTSU       R_MSTP->MSTPCRC
#define BSP_MSTP_BIT_FSP_IP_CTSU(channel)       (1U << (3U - channel));
#define BSP_MSTP_REG_FSP_IP_SLCDC      R_MSTP->MSTPCRC
#define BSP_MSTP_BIT_FSP_IP_SLCDC(channel)      (1U << (4U - channel));
#define BSP_MSTP_REG_FSP_IP_GLCDC      R_MSTP->MSTPCRC
#define BSP_MSTP_BIT_FSP_IP_GLCDC(channel)      (1U << (4U - channel));
#define BSP_MSTP_REG_FSP_IP_JPEG       R_MSTP->MSTPCRC
#define BSP_MSTP_BIT_FSP_IP_JPEG(channel)       (1U << (5U - channel));
#define BSP_MSTP_REG_FSP_IP_DRW        R_MSTP->MSTPCRC
#define BSP_MSTP_BIT_FSP_IP_DRW(channel)        (1U << (6U - channel));
#define BSP_MSTP_REG_FSP_IP_SSI        R_MSTP->MSTPCRC
#define BSP_MSTP_BIT_FSP_IP_SSI(channel)        (1U << (8U - channel));
#define BSP_MSTP_REG_FSP_IP_SRC        R_MSTP->MSTPCRC
#define BSP_MSTP_BIT_FSP_IP_SRC(channel)        (1U << (9U - channel));
#define BSP_MSTP_REG_FSP_IP_SDHIMMC    R_MSTP->MSTPCRC
#define BSP_MSTP_BIT_FSP_IP_SDHIMMC(channel)    (1U << (12U - channel));
#define BSP_MSTP_REG_FSP_IP_DOC        R_MSTP->MSTPCRC
#define BSP_MSTP_BIT_FSP_IP_DOC(channel)        (1U << (13U - channel));
#define BSP_MSTP_REG_FSP_IP_ELC        R_MSTP->MSTPCRC
#define BSP_MSTP_BIT_FSP_IP_ELC(channel)        (1U << (14U - channel));
#define BSP_MSTP_REG_FSP_IP_TRNG       R_MSTP->MSTPCRC
#define BSP_MSTP_BIT_FSP_IP_TRNG(channel)       (1U << (28U - channel));
#define BSP_MSTP_REG_FSP_IP_SCE        R_MSTP->MSTPCRC
#define BSP_MSTP_BIT_FSP_IP_SCE(channel)        (1U << (31U - channel));
#define BSP_MSTP_REG_FSP_IP_AES        R_MSTP->MSTPCRC
#define BSP_MSTP_BIT_FSP_IP_AES(channel)        (1U << (31U - channel));
#define BSP_MSTP_REG_FSP_IP_AGT        R_MSTP->MSTPCRD
#define BSP_MSTP_BIT_FSP_IP_AGT(channel)        (1U << (3U - channel));
#define BSP_MSTP_REG_FSP_IP_POEG       R_MSTP->MSTPCRD
#define BSP_MSTP_BIT_FSP_IP_POEG(channel)       (1U << (14U));
#define BSP_MSTP_REG_FSP_IP_ADC        R_MSTP->MSTPCRD
#define BSP_MSTP_BIT_FSP_IP_ADC(channel)        (1U << (16U - channel));
#define BSP_MSTP_REG_FSP_IP_SDADC      R_MSTP->MSTPCRD
#define BSP_MSTP_BIT_FSP_IP_SDADC(channel)      (1U << (17U - channel));
#define BSP_MSTP_REG_FSP_IP_DAC8       R_MSTP->MSTPCRD
#define BSP_MSTP_BIT_FSP_IP_DAC8(channel)       (1U << (19U - channel));
#define BSP_MSTP_REG_FSP_IP_DAC        R_MSTP->MSTPCRD
#define BSP_MSTP_BIT_FSP_IP_DAC(channel)        (1U << (20U));
#define BSP_MSTP_REG_FSP_IP_TSN        R_MSTP->MSTPCRD
#define BSP_MSTP_BIT_FSP_IP_TSN(channel)        (1U << (22U - channel));
#define BSP_MSTP_REG_FSP_IP_ACMPHS     R_MSTP->MSTPCRD
#define BSP_MSTP_BIT_FSP_IP_ACMPHS(channel)     (1U << (28U - channel));
#define BSP_MSTP_REG_FSP_IP_ACMPLP     R_MSTP->MSTPCRD
#define BSP_MSTP_BIT_FSP_IP_ACMPLP(channel)     (1U << 29U);
#define BSP_MSTP_REG_FSP_IP_OPAMP      R_MSTP->MSTPCRD
#define BSP_MSTP_BIT_FSP_IP_OPAMP(channel)      (1U << (31U - channel));

/** Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
