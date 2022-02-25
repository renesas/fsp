/***********************************************************************************************************************
 * Copyright [2020-2022] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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
 * Includes
 **********************************************************************************************************************/
#include "r_elc.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* "ELC" in ASCII, used to determine if the module is open */
#define ELC_OPEN                  (0x00454C43U)
#define ELC_CLOSED                (0x00000000U)

#define ELC_ELCR_ELCON_DISABLE    (0x00U)
#define ELC_ELCR_ELCON_ENABLE     (0x80U)

/* Steps necessary to unlock and write software event generation bits */
#define ELC_ELSEGRN_STEP1         (0x00U) /* WI = 0, WE = 0, SEG = 0 */
#define ELC_ELSEGRN_STEP2         (0x40U) /* WI = 0, WE = 1, SEG = 0 */
#define ELC_ELSEGRN_STEP3         (0x41U) /* WI = 0, WE = 1, SEG = 1 */

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

#if ELC_CFG_PARAM_CHECKING_ENABLE
static fsp_err_t r_elc_common_parameter_checking(elc_instance_ctrl_t * p_instance_ctrl);

#endif

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Global Variables
 **********************************************************************************************************************/

/** ELC API structure.  */
const elc_api_t g_elc_on_elc =
{
    .open                  = R_ELC_Open,
    .close                 = R_ELC_Close,
    .softwareEventGenerate = R_ELC_SoftwareEventGenerate,
    .linkSet               = R_ELC_LinkSet,
    .linkBreak             = R_ELC_LinkBreak,
    .enable                = R_ELC_Enable,
    .disable               = R_ELC_Disable,
};

/*******************************************************************************************************************//**
 * @addtogroup ELC
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Initialize all the links in the Event Link Controller. Implements @ref elc_api_t::open
 *
 * The configuration structure passed in to this function includes links for every event source included in the ELC
 * and sets them all at once. To set or clear an individual link use R_ELC_LinkSet and R_ELC_LinkBreak respectively.
 *
 * Example:
 * @snippet r_elc_example.c R_ELC_Open
 *
 * @retval FSP_SUCCESS             Initialization was successful
 * @retval FSP_ERR_ASSERTION       p_ctrl or p_cfg was NULL
 * @retval FSP_ERR_ALREADY_OPEN    The module is currently open
 *
 **********************************************************************************************************************/
fsp_err_t R_ELC_Open (elc_ctrl_t * const p_ctrl, elc_cfg_t const * const p_cfg)
{
    uint32_t i;
    uint32_t i_shift = 1;

    elc_instance_ctrl_t * p_instance_ctrl = (elc_instance_ctrl_t *) p_ctrl;

#if ELC_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_cfg);
    FSP_ERROR_RETURN(ELC_OPEN != p_instance_ctrl->open, FSP_ERR_ALREADY_OPEN);
#endif

    /* Power on ELC */
    R_BSP_MODULE_START(FSP_IP_ELC, 0);

    /* Loop through all links and set or clear them in the ELC block */
    for (i = 0; i < ELC_PERIPHERAL_NUM; i++)
    {
        /* Check to ensure the MCU we are using actually has this event link option */
        if (BSP_FEATURE_ELC_PERIPHERAL_MASK & i_shift)
        {
            R_ELC->ELSR[i].HA = (uint16_t) p_cfg->link[i];
        }

        i_shift <<= 1;
    }

    /* Set driver status to open */
    p_instance_ctrl->open = ELC_OPEN;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Globally disable ELC linking. Implements @ref elc_api_t::close
 *
 * @retval FSP_SUCCESS             The ELC was successfully disabled
 * @retval FSP_ERR_ASSERTION       p_ctrl was NULL
 * @retval FSP_ERR_NOT_OPEN        The module has not been opened
 *
 **********************************************************************************************************************/
fsp_err_t R_ELC_Close (elc_ctrl_t * const p_ctrl)
{
    elc_instance_ctrl_t * p_instance_ctrl = (elc_instance_ctrl_t *) p_ctrl;

#if ELC_CFG_PARAM_CHECKING_ENABLE
    fsp_err_t err = r_elc_common_parameter_checking(p_instance_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#endif

    /* Set state to closed */
    p_instance_ctrl->open = ELC_CLOSED;

    /* Globally disable the operation of the Event Link Controller */
    R_ELC->ELCR = ELC_ELCR_ELCON_DISABLE;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Generate a software event in the Event Link Controller. Implements @ref elc_api_t::softwareEventGenerate
 *
 * Example:
 * @snippet r_elc_example.c R_ELC_SoftwareEventGenerate
 *
 * @retval FSP_SUCCESS             Initialization was successful
 * @retval FSP_ERR_ASSERTION       Invalid event number or p_ctrl was NULL
 * @retval FSP_ERR_NOT_OPEN        The module has not been opened
 **********************************************************************************************************************/
fsp_err_t R_ELC_SoftwareEventGenerate (elc_ctrl_t * const p_ctrl, elc_software_event_t event_number)
{
#if ELC_CFG_PARAM_CHECKING_ENABLE
    elc_instance_ctrl_t * p_instance_ctrl = (elc_instance_ctrl_t *) p_ctrl;
    fsp_err_t             err             = r_elc_common_parameter_checking(p_instance_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#endif

    FSP_PARAMETER_NOT_USED(p_ctrl);

    /* Set the ELSEGR bits in the correct order (see Section 19.2.2 "Event Link Software Event Generation Register n
     * (ELSEGRn) (n = 0, 1)" of the RA6M3 manual R01UH0886EJ0100) */

    /* Step 1. enable the ELSEGR0 register for writing */
    R_ELC->ELSEGR[event_number].BY = ELC_ELSEGRN_STEP1;

    /* Step 2. Enable the SEG bit for writing */
    R_ELC->ELSEGR[event_number].BY = ELC_ELSEGRN_STEP2;

    /* Step 3. Set the SEG bit which causes the software event generation */
    R_ELC->ELSEGR[event_number].BY = ELC_ELSEGRN_STEP3;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Create a single event link. Implements @ref elc_api_t::linkSet
 *
 * Example:
 * @snippet r_elc_example.c R_ELC_LinkSet
 *
 * @retval FSP_SUCCESS             Initialization was successful
 * @retval FSP_ERR_ASSERTION       p_ctrl was NULL
 * @retval FSP_ERR_NOT_OPEN        The module has not been opened
 *
 **********************************************************************************************************************/
fsp_err_t R_ELC_LinkSet (elc_ctrl_t * const p_ctrl, elc_peripheral_t peripheral, elc_event_t signal)
{
#if ELC_CFG_PARAM_CHECKING_ENABLE
    elc_instance_ctrl_t * p_instance_ctrl = (elc_instance_ctrl_t *) p_ctrl;
    fsp_err_t             err             = r_elc_common_parameter_checking(p_instance_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
#endif

    /* Set the event link register for the corresponding peripheral to the given signal */
    R_ELC->ELSR[(uint32_t) peripheral].HA = (uint16_t) signal;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Break an event link. Implements @ref elc_api_t::linkBreak
 *
 * @retval FSP_SUCCESS             Event link broken
 * @retval FSP_ERR_ASSERTION       p_ctrl was NULL
 * @retval FSP_ERR_NOT_OPEN        The module has not been opened
 *
 **********************************************************************************************************************/
fsp_err_t R_ELC_LinkBreak (elc_ctrl_t * const p_ctrl, elc_peripheral_t peripheral)
{
#if ELC_CFG_PARAM_CHECKING_ENABLE
    elc_instance_ctrl_t * p_instance_ctrl = (elc_instance_ctrl_t *) p_ctrl;
    fsp_err_t             err             = r_elc_common_parameter_checking(p_instance_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
#endif

    /* Clear the corresponding peripheral event link register to break the link */
    R_ELC->ELSR[(uint32_t) peripheral].HA = ELC_EVENT_NONE;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Enable the operation of the Event Link Controller. Implements @ref elc_api_t::enable
 *
 * @retval FSP_SUCCESS           ELC enabled.
 * @retval FSP_ERR_ASSERTION     p_ctrl was NULL
 * @retval FSP_ERR_NOT_OPEN      The module has not been opened
 *
 **********************************************************************************************************************/
fsp_err_t R_ELC_Enable (elc_ctrl_t * const p_ctrl)
{
#if ELC_CFG_PARAM_CHECKING_ENABLE
    elc_instance_ctrl_t * p_instance_ctrl = (elc_instance_ctrl_t *) p_ctrl;
    fsp_err_t             err             = r_elc_common_parameter_checking(p_instance_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
#endif

    /* Globally enable ELC function */
    R_ELC->ELCR = ELC_ELCR_ELCON_ENABLE;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Disable the operation of the Event Link Controller. Implements @ref elc_api_t::disable
 *
 * @retval FSP_SUCCESS           ELC disabled.
 * @retval FSP_ERR_ASSERTION     p_ctrl was NULL
 * @retval FSP_ERR_NOT_OPEN      The module has not been opened
 *
 **********************************************************************************************************************/
fsp_err_t R_ELC_Disable (elc_ctrl_t * const p_ctrl)
{
#if ELC_CFG_PARAM_CHECKING_ENABLE
    elc_instance_ctrl_t * p_instance_ctrl = (elc_instance_ctrl_t *) p_ctrl;
    fsp_err_t             err             = r_elc_common_parameter_checking(p_instance_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
#endif

    /* Globally disable ELC function */
    R_ELC->ELCR = ELC_ELCR_ELCON_DISABLE;

    return FSP_SUCCESS;
}

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @} (end addtogroup ELC)
 **********************************************************************************************************************/

#if ELC_CFG_PARAM_CHECKING_ENABLE

/*******************************************************************************************************************//**
 * Verifies the control structure is not NULL and the module is open. This reduces code size when the error logger is
 * used.
 *
 * @param[in]  p_instance_ctrl          Pointer to instance control structure.
 *
 * @retval FSP_SUCCESS                  No error detected.
 * @retval FSP_ERR_ASSERTION            Invalid input argument.
 * @retval FSP_ERR_NOT_OPEN             Module is not open.
 **********************************************************************************************************************/
static fsp_err_t r_elc_common_parameter_checking (elc_instance_ctrl_t * p_instance_ctrl)
{
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(ELC_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);

    return FSP_SUCCESS;
}

#endif
