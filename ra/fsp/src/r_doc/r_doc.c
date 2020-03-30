/***********************************************************************************************************************
 * Copyright [2020] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software is supplied by Renesas Electronics America Inc. and may only be used with products of Renesas
 * Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.  This software is protected under
 * all applicable laws, including copyright laws. Renesas reserves the right to change or discontinue this software.
 * THE SOFTWARE IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND TO THE FULLEST
 * EXTENT PERMISSIBLE UNDER APPLICABLE LAW,DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY, INCLUDING
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE SOFTWARE.
 * TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE
 * (OR ANY PERSON OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER, INCLUDING,
 * WITHOUT LIMITATION, ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES; ANY LOST PROFITS,
 * OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF THE POSSIBILITY
 * OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS.
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_doc_api.h"
#include "bsp_api.h"
#include "bsp_cfg.h"
#include "r_doc.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* "DOCO" in ASCII, used to identify Data Operation Circuit (DOC) configuration */
#define DOC_OPEN    (0x444F434fU)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
void doc_int_isr(void);

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/** Version data structure used by error logger macro. */
static const fsp_version_t g_doc_version =
{
    .api_version_major  = DOC_API_VERSION_MAJOR,
    .code_version_minor = DOC_CODE_VERSION_MINOR,
    .code_version_major = DOC_CODE_VERSION_MAJOR,
    .api_version_minor  = DOC_API_VERSION_MINOR,
};

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/

/* DOC implementation of DOC Driver  */

const doc_api_t g_doc_on_doc =
{
    .open       = R_DOC_Open,
    .close      = R_DOC_Close,
    .statusGet  = R_DOC_StatusGet,
    .write      = R_DOC_Write,
    .versionGet = R_DOC_VersionGet,
};

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @addtogroup DOC
 * @{
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Opens and configures the Data Operation Circuit (DOC) in comparison, addition or subtraction mode and sets
 * initial data for addition or subtraction, or reference data for comparison.
 *
 * Example:
 * @snippet r_doc_example.c R_DOC_Open
 *
 * @retval FSP_SUCCESS                  DOC successfully configured.
 * @retval FSP_ERR_ALREADY_OPEN         Module already open.
 * @retval FSP_ERR_ASSERTION            One or more pointers point to NULL or callback is NULL or the interrupt vector
 *                                      is invalid.
 *
 ***********************************************************************************************************************/
fsp_err_t R_DOC_Open (doc_ctrl_t * const p_api_ctrl, doc_cfg_t const * const p_cfg)
{
    doc_instance_ctrl_t * p_ctrl = (doc_instance_ctrl_t *) p_api_ctrl;

    /* Validate the parameters and check if the module is initialized */
#if DOC_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_cfg);
    FSP_ASSERT(p_cfg->p_callback != NULL);
    FSP_ASSERT(p_cfg->irq >= (IRQn_Type) 0);
    FSP_ERROR_RETURN(DOC_OPEN != p_ctrl->open, FSP_ERR_ALREADY_OPEN);
#endif

    /* save pointers for later use */
    p_ctrl->p_cfg = p_cfg;

    /* Power on the DOC module. */
    R_BSP_MODULE_START(FSP_IP_DOC, 0);

    /* Clear the hardware status flag and Configure the DOC using DOCR register. */
    R_DOC->DOCR = (uint8_t) (R_DOC_DOCR_DOPCFCL_Msk | p_cfg->event);

    /* write initial data for comparison/ addition/subtraction to DODSR register */
    R_DOC->DODSR = p_ctrl->p_cfg->doc_data;

    /* Set valid interrupt contexts and user provided priority. Enable the interrupt at the NVIC  */
    R_BSP_IrqCfgEnable(p_ctrl->p_cfg->irq, p_cfg->ipl, p_ctrl);

    /* Mark driver as open by initializing it to "DOCO" in its ASCII equivalent. */
    p_ctrl->open = DOC_OPEN;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Closes the module driver. Enables module stop mode.
 *
 * @retval FSP_SUCCESS          Module successfully closed.
 * @retval FSP_ERR_NOT_OPEN     Driver not open.
 * @retval FSP_ERR_ASSERTION    Pointer pointing to NULL.
 *
 * @note This function will disable the DOC interrupt in the NVIC.
 **********************************************************************************************************************/
fsp_err_t R_DOC_Close (doc_ctrl_t * const p_api_ctrl)
{
    doc_instance_ctrl_t * p_ctrl = (doc_instance_ctrl_t *) p_api_ctrl;

    /* Validate the parameter and check if the module is initialized */
#if DOC_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(DOC_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Disable the IRQ in the NVIC in case it has been left enabled. */
    if (p_ctrl->p_cfg->irq >= 0)
    {
        R_BSP_IrqDisable(p_ctrl->p_cfg->irq);
        R_FSP_IsrContextSet(p_ctrl->p_cfg->irq, NULL);
    }

    R_BSP_MODULE_STOP(FSP_IP_DOC, 0);

    /* Mark driver as closed.  */
    p_ctrl->open = 0U;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Returns the result of addition/subtraction.
 *
 * Example:
 * @snippet r_doc_example.c R_DOC_StatusGet
 *
 * @retval FSP_SUCCESS          Status successfully read.
 * @retval FSP_ERR_NOT_OPEN     Driver not open.
 * @retval FSP_ERR_ASSERTION    One or more pointers point to NULL.
 *
 **********************************************************************************************************************/
fsp_err_t R_DOC_StatusGet (doc_ctrl_t * const p_api_ctrl, doc_status_t * const p_status)
{
    doc_instance_ctrl_t * p_ctrl = (doc_instance_ctrl_t *) p_api_ctrl;

    FSP_PARAMETER_NOT_USED(p_ctrl);

    /* Validate the parameters and check if the module is intialized */
#if DOC_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_status);
    FSP_ERROR_RETURN(DOC_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /*Read the result of addition or subtraction operation from the register and store in the user supplied location */
    p_status->result = R_DOC->DODSR;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Writes to the DODIR - DOC Input Register.
 *
 * Example:
 * @snippet r_doc_example.c R_DOC_Write
 *
 * @retval FSP_SUCCESS          Values successfully written to the registers.
 * @retval FSP_ERR_NOT_OPEN     Driver not open.
 * @retval FSP_ERR_ASSERTION    One or more pointers point to NULL.
 *
 **********************************************************************************************************************/
fsp_err_t R_DOC_Write (doc_ctrl_t * const p_api_ctrl, uint16_t data)
{
    doc_instance_ctrl_t * p_ctrl = (doc_instance_ctrl_t *) p_api_ctrl;

    FSP_PARAMETER_NOT_USED(p_ctrl);

    /* Validate the parameters and check if the module is initialized */
#if DOC_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(DOC_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Writes the user supplied data to the DODIR register for data operation in Comparison, Addition and subtraction modes */
    R_DOC->DODIR = data;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Returns DOC HAL driver version.
 *
 * @retval FSP_SUCCESS          Version information successfully read.
 * @retval FSP_ERR_ASSERTION    Pointer pointing to NULL.
 *
 **********************************************************************************************************************/
fsp_err_t R_DOC_VersionGet (fsp_version_t * const p_version)
{
    /* Validate the parameter */
#if DOC_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_version);
#endif

    /* Store the version id from version data structure to the user supplied location */
    p_version->version_id = g_doc_version.version_id;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup DOC)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * DOC ISR.
 *
 * Saves context if RTOS is used, clears interrupts, calls callback if one was provided in the open function
 * and restores context if RTOS is used.
 **********************************************************************************************************************/
void doc_int_isr (void)
{
    /* Save context if RTOS is used. */
    FSP_CONTEXT_SAVE

    IRQn_Type irq = R_FSP_CurrentIrqGet();

    doc_instance_ctrl_t * p_ctrl = (doc_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    /* Call the callback */
    doc_callback_args_t cb_data;

    /* Set data to identify callback to the user. */
    cb_data.p_context = p_ctrl->p_cfg->p_context;

    /* Call the callback.  */
    p_ctrl->p_cfg->p_callback(&cb_data);

    /* clear DOPCF flag */
    R_DOC->DOCR = (uint8_t) (R_DOC_DOCR_DOPCFCL_Msk | (p_ctrl->p_cfg->event));

    /* Clear the IR flag in the ICU */
    R_BSP_IrqStatusClear(irq);

    /* Restore context if RTOS is used. */
    FSP_CONTEXT_RESTORE
}
