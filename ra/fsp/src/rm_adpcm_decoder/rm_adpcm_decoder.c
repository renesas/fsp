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

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "rm_adpcm_decoder_cfg.h"
#include "rm_adpcm_decoder.h"

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define RM_ADPCM_DECODER_OPEN          (0x52414443U)

/* 90% of the max amplitude(plus) */
#define RM_ADPCM_DECODER_MAX_VPRED     29490

/* 90% of the max amplitude(minus) */
#define RM_ADPCM_DECODER_MIN_VPRED     (-29491)

#define RM_ADPCM_DECODER_MIN_INDEX3    0
#define RM_ADPCM_DECODER_MAX_INDEX3    87
#define RM_ADPCM_DECODER_MIN_INDEX4    2
#define RM_ADPCM_DECODER_MAX_INDEX4    RM_ADPCM_DECODER_MAX_INDEX3

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables and functions
 **********************************************************************************************************************/
/* Step size table(4-bit, 3-bit common use) */
static const uint16_t g_adpcm_stepsizeTable[] =
{
    5,     6,     7,     8,      9,      10,     11,     12,     14,     15,
    17,    18,    20,    22,     25,     27,     30,     33,     37,     40,
    44,    49,    54,    59,     65,     72,     79,     87,     95,     105,
    116,   127,   140,   154,    170,    187,    205,    226,    248,    273,
    301,   331,   364,   400,    440,    485,    533,    586,    645,    710,
    781,   859,   945,   1039,   1143,   1258,   1384,   1522,   1674,   1842,
    2026,  2228,  2451,  2697,   2966,   3263,   3589,   3948,   4343,   4777,
    5255,  5781,  6359,  6995,   7694,   8464,   9310,   10242,  11266,  12392,
    13632, 14995, 16494, 18144,  19958,  21954,  24150,  26565
};

/* Index table(4-bit use) */
static const int8_t adpcm_idxT4[] =
{
    -1, -1, -1, -1, 2, 4, 6, 8,
    -1, -1, -1, -1, 2, 4, 6, 8
};

static void rm_adpcm_decoder_reset (adpcm_decoder_instance_ctrl_t * p_instance_ctrl);

/***********************************************************************************************************************
 * Global Variables
 **********************************************************************************************************************/
const adpcm_decoder_api_t g_adpcm_decoder_on_adpcm_decoder =
{
    .open   = RM_ADPCM_DECODER_Open,
    .decode = RM_ADPCM_DECODER_Decode,
    .reset  = RM_ADPCM_DECODER_Reset,
    .close  = RM_ADPCM_DECODER_Close,
};

/*******************************************************************************************************************//**
 * @addtogroup RM_ADPCM_DECODER
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Initializes ADPCM audio decoder device.
 *
 * Implements @ref adpcm_decoder_api_t::open().
 *
 * @retval FSP_SUCCESS                     Module is ready for use.
 * @retval FSP_ERR_ASSERTION               An input argument is invalid.
 * @retval FSP_ERR_ALREADY_OPEN            The instance control structure has already been opened.
 **********************************************************************************************************************/
fsp_err_t RM_ADPCM_DECODER_Open (adpcm_decoder_ctrl_t * p_ctrl, adpcm_decoder_cfg_t const * const p_cfg)
{
    adpcm_decoder_instance_ctrl_t * p_instance_ctrl = (adpcm_decoder_instance_ctrl_t *) p_ctrl;
    fsp_err_t err = FSP_SUCCESS;

#if RM_ADPCM_DECODER_CFG_PARAM_CHECKING_ENABLE
    /*  Perform parameter checking */
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_cfg);

    /* Verify this unit has not already been initialized   */
    FSP_ERROR_RETURN(RM_ADPCM_DECODER_OPEN != p_instance_ctrl->opened, FSP_ERR_ALREADY_OPEN);
#endif

    /* Configuration Structure Not used */
    FSP_PARAMETER_NOT_USED (p_cfg);

    /* Reset the driver */
    rm_adpcm_decoder_reset(p_instance_ctrl);

    /* Mark driver as opened */
    p_instance_ctrl->opened = RM_ADPCM_DECODER_OPEN;

    return err;
}

/*******************************************************************************************************************//**
 * Decodes 4bit ADPCM data to 16bit PCM data. It reads ADPCM data from area pointed by inputAddr pointer,
 * decodes the number of samples specified and stores the decoded data in buffer pointed with outputAddr pointer.
 *
 * Implements @ref adpcm_decoder_api_t::decode().
 *
 * @retval FSP_SUCCESS                 Decode operation successfully completed.
 * @retval FSP_ERR_ASSERTION           An input argument is invalid.
 * @retval FSP_ERR_NOT_OPEN            Unit is not open.
 **********************************************************************************************************************/
fsp_err_t RM_ADPCM_DECODER_Decode (adpcm_decoder_ctrl_t * const p_ctrl,
                                   void const * p_src, void * p_dest, uint32_t src_len_bytes)
{
    adpcm_decoder_instance_ctrl_t * p_instance_ctrl = (adpcm_decoder_instance_ctrl_t *) p_ctrl;

    /* Perform parameter checking */
#if RM_ADPCM_DECODER_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_src);
    FSP_ASSERT(NULL != p_dest);

    /* Length should be greater than 0 */
    FSP_ASSERT(src_len_bytes > 0);

    FSP_ERROR_RETURN(RM_ADPCM_DECODER_OPEN == p_instance_ctrl->opened, FSP_ERR_NOT_OPEN);
#endif

    /* Set the pointer to input buffer */
    uint8_t const * p_input = (uint8_t const *) (p_src);

    /* Set the pointer to output buffer */
    int16_t * p_output = (int16_t *) (p_dest);

    /* Set the number of actual ADPCM samples to be decoded */
    uint32_t  num_samples = (uint32_t) (src_len_bytes * 2);

    int16_t          vdif;
    uint16_t step;
    unsigned char  code;

    /* Go through all samples and decode each sample to 16 bit PCM data */
    for (uint32_t i = 0; i < num_samples; i++)
    {
        /* Read step */
        step = g_adpcm_stepsizeTable[p_instance_ctrl->id];

        /* Read compressed (ADPCM) data */
        if (i & 1)
        {
            code = (uint8_t) ((*p_input) & 0xF);
            p_input++;
        }
        else
        {
            code = (uint8_t) (((*p_input) >> 4) & 0xF);
        }

        /* Find vdiff value based on step size and previous PCM sample value */
        vdif = (int16_t) (step >> 3);
        if (code & 4)
        {
            vdif = (int16_t) (vdif + step);
        }

        if (code & 2)
        {
            vdif = (int16_t) (vdif + (step >> 1));
        }

        if (code & 1)
        {
            vdif = (int16_t) (vdif + (step >> 2));
        }

        if (code & 8)
        {
            vdif = (int16_t) (-vdif);
        }

        /* Add or subtract vdiff value to the previous PCM sample value */
        p_instance_ctrl->vp = (int16_t) (p_instance_ctrl->vp + vdif);

        if (p_instance_ctrl->vp < RM_ADPCM_DECODER_MIN_VPRED)
        {
            p_instance_ctrl->vp = RM_ADPCM_DECODER_MIN_VPRED;
        }

        if (p_instance_ctrl->vp > RM_ADPCM_DECODER_MAX_VPRED)
        {
            p_instance_ctrl->vp = RM_ADPCM_DECODER_MAX_VPRED;
        }

        /* Write PCM data to destination buffer */
        *p_output = p_instance_ctrl->vp;
        p_output++;

        /* Update step size */
        int8_t id = p_instance_ctrl->id;
        id = (int8_t) (id + adpcm_idxT4[code]);

        if (id < RM_ADPCM_DECODER_MIN_INDEX4)
        {
            id = RM_ADPCM_DECODER_MIN_INDEX4;
        }

        if (id > RM_ADPCM_DECODER_MAX_INDEX4)
        {
            id = RM_ADPCM_DECODER_MAX_INDEX4;
        }

        p_instance_ctrl->id = id;
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * This function resets the ADPCM decoder device.
 *
 * Implements @ref adpcm_decoder_api_t::reset().
 *
 * @retval FSP_SUCCESS                 Module closed.
 * @retval FSP_ERR_ASSERTION           An input argument is invalid.
 * @retval FSP_ERR_NOT_OPEN            Unit is not open.
 **********************************************************************************************************************/
fsp_err_t RM_ADPCM_DECODER_Reset (adpcm_decoder_ctrl_t * p_ctrl)
{
    adpcm_decoder_instance_ctrl_t * p_instance_ctrl = (adpcm_decoder_instance_ctrl_t *) p_ctrl;

#if RM_ADPCM_DECODER_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(RM_ADPCM_DECODER_OPEN == p_instance_ctrl->opened, FSP_ERR_NOT_OPEN);
#endif

    /* Reset the driver */
    rm_adpcm_decoder_reset(p_instance_ctrl);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * This function closes the ADPCM decoder device.
 *
 * Implements @ref adpcm_decoder_api_t::close().
 *
 * @retval FSP_SUCCESS                 Module closed.
 * @retval FSP_ERR_ASSERTION           An input argument is invalid.
 * @retval FSP_ERR_NOT_OPEN            Unit is not open.
 **********************************************************************************************************************/
fsp_err_t RM_ADPCM_DECODER_Close (adpcm_decoder_ctrl_t * p_ctrl)
{
    adpcm_decoder_instance_ctrl_t * p_instance_ctrl = (adpcm_decoder_instance_ctrl_t *) p_ctrl;

#if RM_ADPCM_DECODER_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(RM_ADPCM_DECODER_OPEN == p_instance_ctrl->opened, FSP_ERR_NOT_OPEN);
#endif

    /* Mark driver as closed */
    p_instance_ctrl->opened = 0U;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup RM_ADPCM_DECODER)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Subroutine to reset the ADPCM driver.
 *
 * @param[in]  p_instance_ctrl             Pointer to control structure
 *
 * @retval void
 **********************************************************************************************************************/
static void rm_adpcm_decoder_reset(adpcm_decoder_instance_ctrl_t * p_instance_ctrl)
{
    /* Set Initial Value for previous sample value to 0 */
    p_instance_ctrl->vp = 0;

    /* Set initial index for stepsizeTable to 2 */
    p_instance_ctrl->id = (int8_t) RM_ADPCM_DECODER_MIN_INDEX4;
}

