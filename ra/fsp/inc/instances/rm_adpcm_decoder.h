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

#ifndef RM_ADPCM_DECODER_H
#define RM_ADPCM_DECODER_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include <stdlib.h>

/* Fixed width integer support. */
#include <stdint.h>

/* bool support */
#include <stdbool.h>

#include "bsp_api.h"
#include "rm_adpcm_decoder_cfg.h"
#include "rm_adpcm_decoder_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/*******************************************************************************************************************//**
 * @addtogroup RM_ADPCM_DECODER
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** RM_ADPCM_DECODER instance control block. DO NOT INITIALIZE.
 * Initialized in @ref adpcm_decoder_api_t::open(). */
typedef struct st_adpcm_decoder_instance_ctrl
{
    int8_t    id;                        // Step size
    int16_t   vp;                        // Variable to hold last PCM sample value
    uint32_t    opened;                  // Flag to determine if the device is open
} adpcm_decoder_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Interface Structure for user access */
extern const adpcm_decoder_api_t g_adpcm_decoder_on_adpcm_decoder;

/** @endcond */

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/
fsp_err_t RM_ADPCM_DECODER_Open(adpcm_decoder_ctrl_t * p_ctrl, adpcm_decoder_cfg_t const * const p_cfg);
fsp_err_t RM_ADPCM_DECODER_Decode(adpcm_decoder_ctrl_t * const p_ctrl, void const * p_src, void * p_dest,
        uint32_t src_len_bytes);
fsp_err_t RM_ADPCM_DECODER_Reset(adpcm_decoder_ctrl_t * p_ctrl);
fsp_err_t RM_ADPCM_DECODER_Close(adpcm_decoder_ctrl_t * p_ctrl);

/*******************************************************************************************************************//**
 * @} (end defgroup RM_ADPCM_DECODER)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
