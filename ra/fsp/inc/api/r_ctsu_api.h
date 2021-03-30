/***********************************************************************************************************************
 * Copyright [2020-2021] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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

/*******************************************************************************************************************//**
 * @ingroup RENESAS_INTERFACES
 * @defgroup CTSU_API CTSU Interface
 * @brief Interface for Capacitive Touch Sensing Unit (CTSU) functions.
 *
 * @section CTSU_API_Summary Summary
 * The CTSU interface provides CTSU functionality.
 *
 * The CTSU interface can be implemented by:
 * - @ref CTSU
 *
 * @{
 **********************************************************************************************************************/

#ifndef R_CTSU_API_H
#define R_CTSU_API_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

/* Register definitions, common services and error codes. */
#include "bsp_api.h"
#include "r_transfer_api.h"
#include "r_adc_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define CTSU_API_VERSION_MAJOR    (1U)     // DEPRECATED
#define CTSU_API_VERSION_MINOR    (2U)     // DEPRECATED

#define CTSU_COUNT_MAX            (0xFFFF) ///< Value of Maximum count

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** CTSU Events for callback function */
typedef enum e_ctsu_event
{
    CTSU_EVENT_SCAN_COMPLETE = 0x00,   ///< Normal end
    CTSU_EVENT_OVERFLOW      = 0x01,   ///< Sensor counter overflow (CTSUST.CTSUSOVF set)
    CTSU_EVENT_ICOMP         = 0x02,   ///< Abnormal TSCAP voltage (CTSUERRS.CTSUICOMP set)
    CTSU_EVENT_ICOMP1        = 0x04    ///< Abnormal sensor current (CTSUSR.ICOMP1 set)
} ctsu_event_t;

/** CTSU Scan Start Trigger Select */
typedef enum e_ctsu_cap
{
    CTSU_CAP_SOFTWARE,                 ///< Scan start by software trigger
    CTSU_CAP_EXTERNAL                  ///< Scan start by external trigger
} ctsu_cap_t;

/** CTSU Transmission Power Supply Select */
typedef enum e_ctsu_txvsel
{
    CTSU_TXVSEL_VCC,                   ///< VCC selected
    CTSU_TXVSEL_INTERNAL_POWER         ///< Internal logic power supply selected
} ctsu_txvsel_t;

/** CTSU Transmission Power Supply Select 2 (CTSU2 Only) */
typedef enum e_ctsu_txvsel2
{
    CTSU_TXVSEL_MODE,                  ///< Follow TXVSEL setting
    CTSU_TXVSEL_VCC_PRIVATE,           ///< VCC private selected
} ctsu_txvsel2_t;

/** CTSU Power Supply Capacity Adjustment (CTSU Only) */
typedef enum e_ctsu_atune1
{
    CTSU_ATUNE1_NORMAL,                ///< Normal output (40uA)
    CTSU_ATUNE1_HIGH                   ///< High-current output (80uA)
} ctsu_atune1_t;

/** CTSU Power Supply Capacity Adjustment (CTSU2 Only) */
typedef enum e_ctsu_atune12
{
    CTSU_ATUNE12_80UA,                 ///< High-current output (80uA)
    CTSU_ATUNE12_40UA,                 ///< Normal output (40uA)
    CTSU_ATUNE12_20UA,                 ///< Low-current output (20uA)
    CTSU_ATUNE12_160UA                 ///< Very high-current output (160uA)
} ctsu_atune12_t;

/** CTSU Measurement Mode Select */
typedef enum e_ctsu_mode
{
    CTSU_MODE_SELF_MULTI_SCAN  = 1,    ///< Self-capacitance multi scan mode
    CTSU_MODE_MUTUAL_FULL_SCAN = 3,    ///< Mutual capacitance full scan mode
    CTSU_MODE_MUTUAL_CFC_SCAN  = 7,    ///< Mutual capacitance cfc scan mode (CTSU2 Only)
    CTSU_MODE_CURRENT_SCAN     = 9,    ///< Current scan mode (CTSU2 Only)
    CTSU_MODE_CORRECTION_SCAN  = 17    ///< Correction scan mode (CTSU2 Only)
} ctsu_md_t;

/** CTSU Non-Measured Channel Output Select (CTSU2 Only) */
typedef enum e_ctsu_posel
{
    CTSU_POSEL_LOW_GPIO,               ///< Output low through GPIO
    CTSU_POSEL_HI_Z,                   ///< Hi-Z
    CTSU_POSEL_LOW,                    ///< Output low through the power setting by the TXVSEL[1:0] bits
    CTSU_POSEL_SAME_PULSE              ///< Same phase pulse output as transmission channel through the power setting by the TXVSEL[1:0] bits
} ctsu_posel_t;

/** CTSU Spectrum Diffusion Frequency Division Setting (CTSU Only) */
typedef enum e_ctsu_ssdiv
{
    CTSU_SSDIV_4000,                   ///< 4.00 <= Base clock frequency (MHz)
    CTSU_SSDIV_2000,                   ///< 2.00 <= Base clock frequency (MHz) < 4.00
    CTSU_SSDIV_1330,                   ///< 1.33 <= Base clock frequency (MHz) < 2.00
    CTSU_SSDIV_1000,                   ///< 1.00 <= Base clock frequency (MHz) < 1.33
    CTSU_SSDIV_0800,                   ///< 0.80 <= Base clock frequency (MHz) < 1.00
    CTSU_SSDIV_0670,                   ///< 0.67 <= Base clock frequency (MHz) < 0.80
    CTSU_SSDIV_0570,                   ///< 0.57 <= Base clock frequency (MHz) < 0.67
    CTSU_SSDIV_0500,                   ///< 0.50 <= Base clock frequency (MHz) < 0.57
    CTSU_SSDIV_0440,                   ///< 0.44 <= Base clock frequency (MHz) < 0.50
    CTSU_SSDIV_0400,                   ///< 0.40 <= Base clock frequency (MHz) < 0.44
    CTSU_SSDIV_0360,                   ///< 0.36 <= Base clock frequency (MHz) < 0.40
    CTSU_SSDIV_0330,                   ///< 0.33 <= Base clock frequency (MHz) < 0.36
    CTSU_SSDIV_0310,                   ///< 0.31 <= Base clock frequency (MHz) < 0.33
    CTSU_SSDIV_0290,                   ///< 0.29 <= Base clock frequency (MHz) < 0.31
    CTSU_SSDIV_0270,                   ///< 0.27 <= Base clock frequency (MHz) < 0.29
    CTSU_SSDIV_0000                    ///< 0.00 <= Base clock frequency (MHz) < 0.27
} ctsu_ssdiv_t;

/** Callback function parameter data */
typedef struct st_ctsu_callback_args
{
    ctsu_event_t event;                ///< The event can be used to identify what caused the callback.
    void const * p_context;            ///< Placeholder for user data. Set in ctsu_api_t::open function in ::ctsu_cfg_t.
} ctsu_callback_args_t;

/** CTSU Control block. Allocate an instance specific control block to pass into the API calls.
 * @par Implemented as
 * - ctsu_instance_ctrl_t
 */
typedef void ctsu_ctrl_t;

/** CTSU Configuration parameters. */
/** Element Configuration */
typedef struct st_ctsu_element
{
    ctsu_ssdiv_t ssdiv;                ///< CTSU Spectrum Diffusion Frequency Division Setting (CTSU Only)
    uint16_t     so;                   ///< CTSU Sensor Offset Adjustment
    uint8_t      snum;                 ///< CTSU Measurement Count Setting
    uint8_t      sdpa;                 ///< CTSU Base Clock Setting
} ctsu_element_cfg_t;

/** User configuration structure, used in open function */
typedef struct st_ctsu_cfg
{
    ctsu_cap_t                 cap;                     ///< CTSU Scan Start Trigger Select
    ctsu_txvsel_t              txvsel;                  ///< CTSU Transmission Power Supply Select
    ctsu_txvsel2_t             txvsel2;                 ///< CTSU Transmission Power Supply Select 2 (CTSU2 Only)
    ctsu_atune1_t              atune1;                  ///< CTSU Power Supply Capacity Adjustment (CTSU Only)
    ctsu_atune12_t             atune12;                 ///< CTSU Power Supply Capacity Adjustment (CTSU2 Only)
    ctsu_md_t                  md;                      ///< CTSU Measurement Mode Select
    ctsu_posel_t               posel;                   ///< CTSU Non-Measured Channel Output Select (CTSU2 Only)
    uint8_t                    ctsuchac0;               ///< TS00-TS07 enable mask
    uint8_t                    ctsuchac1;               ///< TS08-TS15 enable mask
    uint8_t                    ctsuchac2;               ///< TS16-TS23 enable mask
    uint8_t                    ctsuchac3;               ///< TS24-TS31 enable mask
    uint8_t                    ctsuchac4;               ///< TS32-TS39 enable mask
    uint8_t                    ctsuchtrc0;              ///< TS00-TS07 mutual-tx mask
    uint8_t                    ctsuchtrc1;              ///< TS08-TS15 mutual-tx mask
    uint8_t                    ctsuchtrc2;              ///< TS16-TS23 mutual-tx mask
    uint8_t                    ctsuchtrc3;              ///< TS24-TS31 mutual-tx mask
    uint8_t                    ctsuchtrc4;              ///< TS32-TS39 mutual-tx mask
    ctsu_element_cfg_t const * p_elements;              ///< Pointer to elements configuration array
    uint8_t                    num_rx;                  ///< Number of receive terminals
    uint8_t                    num_tx;                  ///< Number of transmit terminals
    uint16_t                   num_moving_average;      ///< Number of moving average for measurement data
    bool tunning_enable;                                ///< Initial offset tuning flag
    bool judge_multifreq_disable;                       ///< Disable to judge multi frequency
    void (* p_callback)(ctsu_callback_args_t * p_args); ///< Callback provided when CTSUFN ISR occurs.
    transfer_instance_t const * p_transfer_tx;          ///< DTC instance for transmit at CTSUWR. Set to NULL if unused.
    transfer_instance_t const * p_transfer_rx;          ///< DTC instance for receive at CTSURD. Set to NULL if unused.
    adc_instance_t const      * p_adc_instance;         ///< ADC instance for temperature correction.
    IRQn_Type    write_irq;                             ///< CTSU_CTSUWR interrupt vector
    IRQn_Type    read_irq;                              ///< CTSU_CTSURD interrupt vector
    IRQn_Type    end_irq;                               ///< CTSU_CTSUFN interrupt vector
    void const * p_context;                             ///< User defined context passed into callback function.
    void const * p_extend;                              ///< Pointer to extended configuration by instance of interface.
} ctsu_cfg_t;

/** Functions implemented at the HAL layer will follow this API. */
typedef struct st_ctsu_api
{
    /** Open driver.
     * @par Implemented as
     * - @ref R_CTSU_Open()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_cfg        Pointer to pin configuration structure.
     */
    fsp_err_t (* open)(ctsu_ctrl_t * const p_ctrl, ctsu_cfg_t const * const p_cfg);

    /** Scan start.
     * @par Implemented as
     * - @ref R_CTSU_ScanStart()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* scanStart)(ctsu_ctrl_t * const p_ctrl);

    /** Data get.
     * @par Implemented as
     * - @ref R_CTSU_DataGet()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[out] p_data       Pointer to get data array.
     */
    fsp_err_t (* dataGet)(ctsu_ctrl_t * const p_ctrl, uint16_t * p_data);

    /** Specify callback function and optional context pointer and working memory pointer.
     * @par Implemented as
     * - @ref R_CTSU_CallbackSet()
     *
     * @param[in]   p_ctrl                   Pointer to the CTSU control block.
     * @param[in]   p_callback               Callback function
     * @param[in]   p_context                Pointer to send to callback function
     * @param[in]   p_working_memory         Pointer to volatile memory where callback structure can be allocated.
     *                                       Callback arguments allocated here are only valid during the callback.
     */
    fsp_err_t (* callbackSet)(ctsu_ctrl_t * const p_api_ctrl, void (* p_callback)(ctsu_callback_args_t *),
                              void const * const p_context, ctsu_callback_args_t * const p_callback_memory);

    /** Close driver.
     * @par Implemented as
     * - @ref R_CTSU_Close()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* close)(ctsu_ctrl_t * const p_ctrl);

    /* DEPRECATED Return the version of the driver.
     * @par Implemented as
     * - @ref R_CTSU_VersionGet()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[out] p_data       Memory address to return version information to.
     */
    fsp_err_t (* versionGet)(fsp_version_t * const p_data);
} ctsu_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_ctsu_instance
{
    ctsu_ctrl_t      * p_ctrl;         ///< Pointer to the control structure for this instance
    ctsu_cfg_t const * p_cfg;          ///< Pointer to the configuration structure for this instance
    ctsu_api_t const * p_api;          ///< Pointer to the API structure for this instance
} ctsu_instance_t;

/** Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 /* R_CTSU_API_H */

/*******************************************************************************************************************//**
 * @} (end addtogroup CTSU_API)
 **********************************************************************************************************************/
