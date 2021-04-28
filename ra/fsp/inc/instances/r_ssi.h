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
 * @addtogroup SSI
 * @{
 **********************************************************************************************************************/

#ifndef R_SSI_H
#define R_SSI_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_i2s_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Audio clock source. */
typedef enum e_ssi_audio_clock
{
    SSI_AUDIO_CLOCK_EXTERNAL = 0,      ///< Audio clock source is the AUDIO_CLK input pin
    SSI_AUDIO_CLOCK_INTERNAL = 1,      ///< Audio clock source is internal connection to a MCU specific GPT channel output
} ssi_audio_clock_t;

/** Bit clock division ratio.  Bit clock frequency = audio clock frequency / bit clock division ratio. */
typedef enum e_ssi_clock_div
{
    SSI_CLOCK_DIV_1   = 0,             ///< Clock divisor 1
    SSI_CLOCK_DIV_2   = 1,             ///< Clock divisor 2
    SSI_CLOCK_DIV_4   = 2,             ///< Clock divisor 4
    SSI_CLOCK_DIV_6   = 8,             ///< Clock divisor 6
    SSI_CLOCK_DIV_8   = 3,             ///< Clock divisor 8
    SSI_CLOCK_DIV_12  = 9,             ///< Clock divisor 12
    SSI_CLOCK_DIV_16  = 4,             ///< Clock divisor 16
    SSI_CLOCK_DIV_24  = 10,            ///< Clock divisor 24
    SSI_CLOCK_DIV_32  = 5,             ///< Clock divisor 32
    SSI_CLOCK_DIV_48  = 11,            ///< Clock divisor 48
    SSI_CLOCK_DIV_64  = 6,             ///< Clock divisor 64
    SSI_CLOCK_DIV_96  = 12,            ///< Clock divisor 96
    SSI_CLOCK_DIV_128 = 7,             ///< Clock divisor 128
} ssi_clock_div_t;

/** Channel instance control block. DO NOT INITIALIZE.  Initialization occurs when @ref i2s_api_t::open is called. */
typedef struct st_ssi_instance_ctrl
{
    uint32_t          open;            // Whether or not this control block is initialized
    i2s_cfg_t const * p_cfg;           // Initial configurations.
    R_SSI0_Type     * p_reg;           // Pointer to SSI register base address

    /* Source buffer pointer used to fill hardware FIFO from transmit ISR. */
    void const * p_tx_src;

    /* Size of source buffer used to fill hardware FIFO from transmit ISR. */
    uint32_t tx_src_samples;

    /* Destination buffer pointer used to fill from hardware FIFO in receive ISR. */
    void * p_rx_dest;

    /* Size of destination buffer used to fill from hardware FIFO in receive ISR. */
    uint32_t        rx_dest_samples;
    transfer_size_t fifo_access_size;  // Access the FIFO as 1 byte, 2 bytes, or 4 bytes

    /* Pointer to callback and optional working memory */
    void (* p_callback)(i2s_callback_args_t *);
    i2s_callback_args_t * p_callback_memory;
    void const          * p_context;   // < User defined context passed into callback function
} ssi_instance_ctrl_t;

/** SSI configuration extension. This extension is optional. */
typedef struct st_ssi_extended_cfg
{
    ssi_audio_clock_t audio_clock;     ///< Audio clock source, default is SSI_AUDIO_CLOCK_EXTERNAL
    ssi_clock_div_t   bit_clock_div;   ///< Select bit clock division ratio
} ssi_extended_cfg_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
extern const i2s_api_t g_i2s_on_ssi;

/** @endcond */

/**********************************************************************************************************************
 * Function Prototypes
 **********************************************************************************************************************/

fsp_err_t R_SSI_Open(i2s_ctrl_t * const p_ctrl, i2s_cfg_t const * const p_cfg);
fsp_err_t R_SSI_Stop(i2s_ctrl_t * const p_ctrl);
fsp_err_t R_SSI_StatusGet(i2s_ctrl_t * const p_ctrl, i2s_status_t * const p_status);
fsp_err_t R_SSI_Write(i2s_ctrl_t * const p_ctrl, void const * const p_src, uint32_t const bytes);
fsp_err_t R_SSI_Read(i2s_ctrl_t * const p_ctrl, void * const p_dest, uint32_t const bytes);
fsp_err_t R_SSI_WriteRead(i2s_ctrl_t * const p_ctrl, void const * const p_src, void * const p_dest,
                          uint32_t const bytes);
fsp_err_t R_SSI_Mute(i2s_ctrl_t * const p_ctrl, i2s_mute_t const mute_enable);
fsp_err_t R_SSI_Close(i2s_ctrl_t * const p_ctrl);
fsp_err_t R_SSI_CallbackSet(i2s_ctrl_t * const          p_api_ctrl,
                            void (                    * p_callback)(i2s_callback_args_t *),
                            void const * const          p_context,
                            i2s_callback_args_t * const p_callback_memory);

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // R_SSI_H

/*******************************************************************************************************************//**
 * @} (end defgroup SSI)
 **********************************************************************************************************************/
