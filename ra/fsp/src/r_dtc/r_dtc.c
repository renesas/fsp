/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include <string.h>
#include "r_dtc.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/** Driver ID (DTC in ASCII), used to identify Data Transfer Controller (DTC) configuration  */
#define DTC_OPEN                    (0x44544300)

/** Size of vector table is based on number of vectors defined in BSP. */
#define DTC_VECTOR_TABLE_ENTRIES    (BSP_ICU_VECTOR_MAX_ENTRIES)

/** The size of transfer_info_t is defined in the Hardware Manual therefore it must be 16 bytes. */
#define DTC_TRANSFER_INFO_SIZE      (16U)

/* Compiler specific macro to specify vector table section. */
#ifndef DTC_CFG_VECTOR_TABLE_SECTION_NAME
 #define DTC_SECTION_ATTRIBUTE
 #ifndef SUPPRESS_WARNING_DTC_CFG_VECTOR_TABLE_SECTION_NAME
  #warning "DTC vector table is aligned on 1K boundary. Automatic placing could lead to memory holes."
 #endif
#else
 #define DTC_SECTION_ATTRIBUTE    BSP_PLACE_IN_SECTION(DTC_CFG_VECTOR_TABLE_SECTION_NAME)
#endif

/* Used to generate a compiler error (divided by 0 error) if the assertion fails.  This is used in place of "#error"
 * for expressions that cannot be evaluated by the preprocessor like sizeof(). */
#define DTC_COMPILE_TIME_ASSERT(e)       ((void) sizeof(char[1 - 2 * !(e)]))

/* Calculate the mask bits for byte alignment from the transfer_size_t. */
#define DTC_PRV_MASK_ALIGN_N_BYTES(x)    ((1U << (x)) - 1U)

/* Counter Register A Lower Byte Mask */
#define DTC_PRV_MASK_CRAL             (0xFFU)

/* Counter Register A Upper Byte Offset */
#define DTC_PRV_OFFSET_CRAH           (8U)

/* Offset of in_progress bit in R_DTC->DTCSTS. */
#define DTC_PRV_OFFSET_IN_PROGRESS    (15U)

/* DTC Control Register RRS Enable value. */
#define DTC_PRV_RRS_ENABLE            (0x18)

/* DTC Control Register RRS Disable value. */
#define DTC_PRV_RRS_DISABLE           (0x08)

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

static fsp_err_t r_dtc_prv_enable(dtc_instance_ctrl_t * p_ctrl);
static void      r_dtc_state_initialize(void);
static void      r_dtc_block_repeat_initialize(transfer_info_t * p_info);
static void      r_dtc_set_info(dtc_instance_ctrl_t * p_ctrl, transfer_info_t * p_info);

#if DTC_CFG_PARAM_CHECKING_ENABLE
 #if BSP_CFG_ASSERT != 3
static fsp_err_t r_dtc_length_assert(transfer_info_t * p_info);

 #endif
static fsp_err_t r_dtc_source_destination_parameter_check(transfer_info_t * p_info);

#endif

static void r_dtc_wait_for_transfer_complete(dtc_instance_ctrl_t * p_ctrl);
static void r_dtc_disable_transfer(const IRQn_Type irq);

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

static transfer_info_t * gp_dtc_vector_table[DTC_VECTOR_TABLE_ENTRIES] BSP_ALIGN_VARIABLE(1024)
DTC_SECTION_ATTRIBUTE;

/***********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** DTC implementation of transfer API. */
const transfer_api_t g_transfer_on_dtc =
{
    .open          = R_DTC_Open,
    .reconfigure   = R_DTC_Reconfigure,
    .reset         = R_DTC_Reset,
    .infoGet       = R_DTC_InfoGet,
    .softwareStart = R_DTC_SoftwareStart,
    .softwareStop  = R_DTC_SoftwareStop,
    .enable        = R_DTC_Enable,
    .disable       = R_DTC_Disable,
    .reload        = R_DTC_Reload,
    .callbackSet   = R_DTC_CallbackSet,
    .close         = R_DTC_Close,
};

/*******************************************************************************************************************//**
 * @addtogroup DTC
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Configure the vector table if it hasn't been configured, enable the Module and copy the pointer to the transfer info
 * into the DTC vector table. Implements @ref transfer_api_t::open.
 *
 * Example:
 * @snippet r_dtc_example.c R_DTC_Open
 *
 * @retval FSP_SUCCESS              Successful open.
 *                                      Transfer transfer info pointer copied to DTC Vector table.
 *                                      Module started.
 *                                      DTC vector table configured.
 * @retval FSP_ERR_ASSERTION        An input parameter is invalid.
 * @retval FSP_ERR_UNSUPPORTED      Address Mode Offset is selected.
 * @retval FSP_ERR_ALREADY_OPEN     The control structure is already opened.
 * @retval FSP_ERR_IN_USE           The index for this IRQ in the DTC vector table is already configured.
 * @retval FSP_ERR_IRQ_BSP_DISABLED The IRQ associated with the activation source is not enabled in the BSP.
 **********************************************************************************************************************/
fsp_err_t R_DTC_Open (transfer_ctrl_t * const p_api_ctrl, transfer_cfg_t const * const p_cfg)
{
    /* Generate a compiler error if transfer_info_t is modified. */
    DTC_COMPILE_TIME_ASSERT(sizeof(transfer_info_t) == DTC_TRANSFER_INFO_SIZE);

    dtc_instance_ctrl_t * p_ctrl = (dtc_instance_ctrl_t *) p_api_ctrl;

#if DTC_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(p_ctrl->open != DTC_OPEN, FSP_ERR_ALREADY_OPEN);
    FSP_ASSERT(NULL != p_cfg);
    FSP_ASSERT(NULL != p_cfg->p_extend);
#endif

    /* One time initialization for all DTC instances. */
    r_dtc_state_initialize();

    /* Make sure the activation source is mapped in the ICU. */
    dtc_extended_cfg_t * p_dtc_cfg = (dtc_extended_cfg_t *) p_cfg->p_extend;
    IRQn_Type            irq       = p_dtc_cfg->activation_source;
    FSP_ERROR_RETURN(irq >= (IRQn_Type) 0, FSP_ERR_IRQ_BSP_DISABLED);

    /* Make sure the activation source is not already being used by the DTC. */
    FSP_ERROR_RETURN(NULL == gp_dtc_vector_table[irq], FSP_ERR_IN_USE);

    /* irq is used to index the DTC vector table. */
    p_ctrl->irq = irq;

    /* Copy p_info into the DTC vector table. */
    if (p_cfg->p_info)
    {
#if DTC_CFG_PARAM_CHECKING_ENABLE
        fsp_err_t err = r_dtc_length_assert(p_cfg->p_info);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#endif
        r_dtc_set_info(p_ctrl, p_cfg->p_info);
    }

    /* Mark driver as open by initializing it to "DTC" in its ASCII equivalent. */
    p_ctrl->open = DTC_OPEN;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Copy pointer to transfer info into the DTC vector table and enable transfer in ICU.
 * Implements @ref transfer_api_t::reconfigure.
 *
 * @retval FSP_SUCCESS              Transfer is configured and will start when trigger occurs.
 * @retval FSP_ERR_ASSERTION        An input parameter is invalid.
 * @retval FSP_ERR_NOT_OPEN         Handle is not initialized.  Call R_DTC_Open to initialize the control block.
 * @retval FSP_ERR_NOT_ENABLED      Transfer source address is NULL or is not aligned correctly.
 *                                  Transfer destination address is NULL or is not aligned correctly.
 *
 * @note p_info must persist until all transfers are completed.
 **********************************************************************************************************************/
fsp_err_t R_DTC_Reconfigure (transfer_ctrl_t * const p_api_ctrl, transfer_info_t * p_info)
{
    dtc_instance_ctrl_t * p_ctrl = (dtc_instance_ctrl_t *) p_api_ctrl;

#if DTC_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(p_ctrl->open == DTC_OPEN, FSP_ERR_NOT_OPEN);
    FSP_ASSERT(NULL != p_info);
    FSP_ASSERT(FSP_SUCCESS == r_dtc_length_assert(p_info));
#endif

    /* Disable transfers on this activation source. */
    r_dtc_disable_transfer(p_ctrl->irq);

    /* Wait for current transfer to finish. */
    r_dtc_wait_for_transfer_complete(p_ctrl);

    /* Copy p_info into the DTC vector table. */
    r_dtc_set_info(p_ctrl, p_info);

    /* This is an exception to FSP Architecture Parameter Checking (May return an error after modifying registers). */
    /* Enable transfers on this activation source. */
    FSP_ERROR_RETURN(FSP_SUCCESS == r_dtc_prv_enable(p_ctrl), FSP_ERR_NOT_ENABLED);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Reset transfer source, destination, and number of transfers. Implements @ref transfer_api_t::reset.
 *
 * @retval FSP_SUCCESS              Transfer reset successfully (transfers are enabled).
 * @retval FSP_ERR_ASSERTION        An input parameter is invalid.
 * @retval FSP_ERR_NOT_OPEN         Handle is not initialized.  Call R_DTC_Open to initialize the control block.
 * @retval FSP_ERR_NOT_ENABLED      Transfer source address is NULL or is not aligned correctly.
 *                                  Transfer destination address is NULL or is not aligned correctly.
 **********************************************************************************************************************/
fsp_err_t R_DTC_Reset (transfer_ctrl_t * const p_api_ctrl,
                       void const * volatile   p_src,
                       void * volatile         p_dest,
                       uint16_t const          num_transfers)
{
    dtc_instance_ctrl_t * p_ctrl = (dtc_instance_ctrl_t *) p_api_ctrl;

#if DTC_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(p_ctrl->open == DTC_OPEN, FSP_ERR_NOT_OPEN);
#endif

    const IRQn_Type         irq           = p_ctrl->irq;
    transfer_info_t * const gp_dtc_vector = gp_dtc_vector_table[irq];

    /* Disable transfers on this activation source. */
    r_dtc_disable_transfer(irq);

    /* Wait for current transfer to finish. */
    r_dtc_wait_for_transfer_complete(p_ctrl);

    /* Disable read skip prior to modifying settings. It will be enabled later
     * (See DTC Section 18.4.1 of the RA6M3 manual R01UH0886EJ0100). */
#if !BSP_TZ_NONSECURE_BUILD && BSP_FEATURE_TZ_HAS_TRUSTZONE
    R_DTC->DTCCR_SEC = DTC_PRV_RRS_DISABLE;
#else
    R_DTC->DTCCR = DTC_PRV_RRS_DISABLE;
#endif

    /* Reset transfer based on input parameters. */
    if (NULL != p_src)
    {
        gp_dtc_vector->p_src = p_src;
    }

    if (NULL != p_dest)
    {
        gp_dtc_vector->p_dest = p_dest;
    }

    if (TRANSFER_MODE_BLOCK == gp_dtc_vector->transfer_settings_word_b.mode)
    {
        gp_dtc_vector->num_blocks = num_transfers;
    }
    else if (TRANSFER_MODE_NORMAL == gp_dtc_vector->transfer_settings_word_b.mode)
    {
        gp_dtc_vector->length = num_transfers;
    }
    else                               /* TRANSFER_MODE_REPEAT */
    {
        /* Do nothing. */
    }

    /* Enable read skip after all settings are written. */
#if !BSP_TZ_NONSECURE_BUILD && BSP_FEATURE_TZ_HAS_TRUSTZONE
    R_DTC->DTCCR_SEC = DTC_PRV_RRS_ENABLE;
#else
    R_DTC->DTCCR = DTC_PRV_RRS_ENABLE;
#endif

    /* This is an exception to FSP Architecture Parameter Checking (May return an error after modifying registers). */
    /* Enable transfers on this activation source. */
    FSP_ERROR_RETURN(FSP_SUCCESS == r_dtc_prv_enable(p_ctrl), FSP_ERR_NOT_ENABLED);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Placeholder for unsupported softwareStart function. Implements @ref transfer_api_t::softwareStart.
 *
 * @retval FSP_ERR_UNSUPPORTED      DTC software start is not supported.
 **********************************************************************************************************************/
fsp_err_t R_DTC_SoftwareStart (transfer_ctrl_t * const p_api_ctrl, transfer_start_mode_t mode)
{
    /* This function isn't supported.  It is defined only to implement a required function of transfer_api_t.
     * Mark the input parameter as unused since this function isn't supported. */
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(mode);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * Placeholder for unsupported softwareStop function. Implements @ref transfer_api_t::softwareStop.
 *
 * @retval FSP_ERR_UNSUPPORTED      DTC software stop is not supported.
 **********************************************************************************************************************/
fsp_err_t R_DTC_SoftwareStop (transfer_ctrl_t * const p_api_ctrl)
{
    /* This function isn't supported.  It is defined only to implement a required function of transfer_api_t.
     * Mark the input parameter as unused since this function isn't supported. */
    FSP_PARAMETER_NOT_USED(p_api_ctrl);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * Enable transfers on this activation source. Implements @ref transfer_api_t::enable.
 *
 * Example:
 * @snippet r_dtc_example.c R_DTC_Enable
 *
 * @retval FSP_SUCCESS              Transfers will be triggered by the activation source
 * @retval FSP_ERR_ASSERTION        An input parameter is invalid.
 * @retval FSP_ERR_UNSUPPORTED      Address Mode Offset is selected.
 * @retval FSP_ERR_NOT_OPEN         Handle is not initialized.  Call R_DTC_Open to initialize the control block.
 **********************************************************************************************************************/
fsp_err_t R_DTC_Enable (transfer_ctrl_t * const p_api_ctrl)
{
    dtc_instance_ctrl_t * p_ctrl = (dtc_instance_ctrl_t *) p_api_ctrl;
#if DTC_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(p_ctrl->open == DTC_OPEN, FSP_ERR_NOT_OPEN);
#endif

    return r_dtc_prv_enable(p_ctrl);
}

/*******************************************************************************************************************//**
 * Disable transfer on this activation source. Implements @ref transfer_api_t::disable.
 *
 * @retval FSP_SUCCESS              Transfers will not occur on activation events.
 * @retval FSP_ERR_NOT_OPEN         Handle is not initialized.  Call R_DTC_Open to initialize the control block.
 * @retval FSP_ERR_ASSERTION        An input parameter is invalid.
 **********************************************************************************************************************/
fsp_err_t R_DTC_Disable (transfer_ctrl_t * const p_api_ctrl)
{
    dtc_instance_ctrl_t * p_ctrl = (dtc_instance_ctrl_t *) p_api_ctrl;

#if DTC_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(p_ctrl->open == DTC_OPEN, FSP_ERR_NOT_OPEN);
#endif

    /* Disable transfer. */
    r_dtc_disable_transfer(p_ctrl->irq);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Provides information about this transfer. Implements @ref transfer_api_t::infoGet.
 *
 * @retval FSP_SUCCESS              p_info updated with current instance information.
 * @retval FSP_ERR_NOT_OPEN         Handle is not initialized. Call R_DTC_Open to initialize the control block.
 * @retval FSP_ERR_ASSERTION        An input parameter is invalid.
 **********************************************************************************************************************/
fsp_err_t R_DTC_InfoGet (transfer_ctrl_t * const p_api_ctrl, transfer_properties_t * const p_properties)
{
    dtc_instance_ctrl_t * p_ctrl = (dtc_instance_ctrl_t *) p_api_ctrl;

#if DTC_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(p_ctrl->open == DTC_OPEN, FSP_ERR_NOT_OPEN);
    FSP_ASSERT(NULL != p_properties);
#endif

    transfer_info_t * p_info = gp_dtc_vector_table[p_ctrl->irq];

    p_properties->block_count_max       = 0U;
    p_properties->block_count_remaining = 0U;

    if (TRANSFER_MODE_NORMAL != p_info->transfer_settings_word_b.mode)
    {
        /* Repeat and Block Mode */

        /* transfer_length_max is the same for Block and repeat mode. */
        p_properties->transfer_length_max       = DTC_MAX_REPEAT_TRANSFER_LENGTH;
        p_properties->transfer_length_remaining = p_info->length & DTC_PRV_MASK_CRAL;

        if (TRANSFER_MODE_BLOCK == p_info->transfer_settings_word_b.mode)
        {
            p_properties->block_count_max       = DTC_MAX_BLOCK_COUNT;
            p_properties->block_count_remaining = p_info->num_blocks;
        }
    }
    else
    {
        p_properties->transfer_length_max       = DTC_MAX_NORMAL_TRANSFER_LENGTH;
        p_properties->transfer_length_remaining = p_info->length;
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * To update next transfer information without interruption during transfer.
 *
 * @retval FSP_ERR_UNSUPPORTED        This feature is not supported.
 **********************************************************************************************************************/
fsp_err_t R_DTC_Reload (transfer_ctrl_t * const p_api_ctrl,
                        void const            * p_src,
                        void                  * p_dest,
                        uint32_t const          num_transfers)
{
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(p_src);
    FSP_PARAMETER_NOT_USED(p_dest);
    FSP_PARAMETER_NOT_USED(num_transfers);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * Placeholder for unsupported callbackset function. Implements @ref transfer_api_t::callbackSet.
 *
 * @retval FSP_ERR_UNSUPPORTED      DTC does not support direct callbacks.
 **********************************************************************************************************************/
fsp_err_t R_DTC_CallbackSet (transfer_ctrl_t * const          p_api_ctrl,
                             void (                         * p_callback)(transfer_callback_args_t *),
                             void const * const               p_context,
                             transfer_callback_args_t * const p_callback_memory)
{
    /* This function isn't supported.  It is defined only to implement a required function of transfer_api_t.
     * Mark the input parameter as unused since this function isn't supported. */
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(p_callback);
    FSP_PARAMETER_NOT_USED(p_context);
    FSP_PARAMETER_NOT_USED(p_callback_memory);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * Disables DTC activation in the ICU, then clears transfer data from the DTC vector table.
 * Implements @ref transfer_api_t::close.
 *
 * @retval FSP_SUCCESS              Successful close.
 * @retval FSP_ERR_ASSERTION        An input parameter is invalid.
 * @retval FSP_ERR_NOT_OPEN         Handle is not initialized.  Call R_DTC_Open to initialize the control block.
 **********************************************************************************************************************/
fsp_err_t R_DTC_Close (transfer_ctrl_t * const p_api_ctrl)
{
    dtc_instance_ctrl_t * p_ctrl = (dtc_instance_ctrl_t *) p_api_ctrl;
    fsp_err_t             err    = FSP_SUCCESS;

#if DTC_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(p_ctrl->open == DTC_OPEN, FSP_ERR_NOT_OPEN);
#endif

    const IRQn_Type irq = p_ctrl->irq;

    /* Clear DTC enable bit in ICU. */
    r_dtc_disable_transfer(irq);

    /* Clear pointer in vector table. */
    gp_dtc_vector_table[irq] = NULL;

    /* Mark instance as closed. */
    p_ctrl->open = 0U;

    return err;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup DTC)
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Verify that the source and destination pointers are valid then enable the DTC.
 *
 * @retval FSP_SUCCESS              Successfully enabled
 * @retval FSP_ERR_ASSERTION        An input parameter is invalid.
 * @retval FSP_ERR_UNSUPPORTED      Address Mode Offset is selected.
 **********************************************************************************************************************/
static fsp_err_t r_dtc_prv_enable (dtc_instance_ctrl_t * p_ctrl)
{
#if DTC_CFG_PARAM_CHECKING_ENABLE
    fsp_err_t err = r_dtc_source_destination_parameter_check(gp_dtc_vector_table[p_ctrl->irq]);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#endif

    /* Enable transfers on this activation source. */
#if BSP_FEATURE_ICU_HAS_IELSR
    R_ICU->IELSR_b[p_ctrl->irq].DTCE = 1U;
#else
    R_ICU->DTCENSET[(((uint32_t) p_ctrl->irq) >> 5UL)] = 1UL << ((uint32_t) p_ctrl->irq & (uint32_t) 0x1FUL);
#endif

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * One time state initialization for all DTC instances.
 **********************************************************************************************************************/
static void r_dtc_state_initialize (void)
{
    /* Stores initialization state to skip initialization in ::R_DTC_Open after the first call. */
    static bool g_dtc_state_initialized = false;

    /* DTC requires a one time initialization.  This will be handled only the first time this function
     *  is called. This initialization:
     *  -# Stores the register base addresses for DTC and ICU.
     *  -# Powers on the DTC block.
     *  -# Initializes the vector table to NULL pointers.
     *  -# Sets the vector table base address.
     *  -# Enables DTC transfers. */
    if (!g_dtc_state_initialized)
    {
        g_dtc_state_initialized = true;

        /** Power on DTC */
        R_BSP_MODULE_START(FSP_IP_DTC, 0);

        /* The DTC vector table must be cleared during initialization because it is located in
         * its own section outside of the .BSS section which is cleared during startup. */
        memset(&gp_dtc_vector_table, 0U, DTC_VECTOR_TABLE_ENTRIES * sizeof(transfer_info_t *));

        /* Set DTC vector table. */
#if !BSP_TZ_NONSECURE_BUILD && BSP_FEATURE_TZ_HAS_TRUSTZONE
        R_DTC->DTCVBR_SEC = (uint32_t) gp_dtc_vector_table;
#else
        R_DTC->DTCVBR = (uint32_t) gp_dtc_vector_table;
#endif

#if BSP_FEATURE_TZ_HAS_TRUSTZONE && BSP_TZ_NONSECURE_BUILD
        if (1 == R_CPSCU->DTCSAR_b.DTCSTSA)
        {
            /* Enable the DTC Peripheral */
            R_DTC->DTCST = 1U;
        }

#else

        /* Enable the DTC Peripheral */
        R_DTC->DTCST = 1U;
#endif
    }
}

/*******************************************************************************************************************//**
 * Configure the p_info state and write p_info to DTC vector table.
 **********************************************************************************************************************/
static void r_dtc_set_info (dtc_instance_ctrl_t * p_ctrl, transfer_info_t * p_info)
{
    /* Update internal variables. */
    r_dtc_block_repeat_initialize(p_info);

    /* Disable read skip prior to modifying settings. It will be enabled later
     * (See DTC Section 18.4.1 of the RA6M3 manual R01UH0886EJ0100). */
#if !BSP_TZ_NONSECURE_BUILD && BSP_FEATURE_TZ_HAS_TRUSTZONE
    R_DTC->DTCCR_SEC = DTC_PRV_RRS_DISABLE;
#else
    R_DTC->DTCCR = DTC_PRV_RRS_DISABLE;
#endif

    /* Update the entry in the DTC Vector table. */
    gp_dtc_vector_table[p_ctrl->irq] = p_info;

    /* Enable read skip after all settings are written. */
#if !BSP_TZ_NONSECURE_BUILD && BSP_FEATURE_TZ_HAS_TRUSTZONE
    R_DTC->DTCCR_SEC = DTC_PRV_RRS_ENABLE;
#else
    R_DTC->DTCCR = DTC_PRV_RRS_ENABLE;
#endif
}

/*******************************************************************************************************************//**
 * Configure the length setting for block and repeat mode.
 **********************************************************************************************************************/
static void r_dtc_block_repeat_initialize (transfer_info_t * p_info)
{
    uint32_t i = 0;
    do
    {
        /* Update the CRA register to the desired settings */
        if (TRANSFER_MODE_NORMAL != p_info[i].transfer_settings_word_b.mode)
        {
            uint8_t CRAL = p_info[i].length & DTC_PRV_MASK_CRAL;
            p_info[i].length = (uint16_t) ((CRAL << DTC_PRV_OFFSET_CRAH) | CRAL);
        }
    } while (TRANSFER_CHAIN_MODE_DISABLED != p_info[i++].transfer_settings_word_b.chain_mode);
}

#if DTC_CFG_PARAM_CHECKING_ENABLE

 #if BSP_CFG_ASSERT != 3

/*******************************************************************************************************************//**
 * Check to make sure that the length is valid for block and repeat mode.
 *
 * @retval FSP_SUCCESS              Parameters are valid.
 * @retval FSP_ERR_ASSERTION        Invalid length for block or repeat mode.
 * @retval FSP_ERR_UNSUPPORTED      Address Mode Offset is selected.
 *
 **********************************************************************************************************************/
static fsp_err_t r_dtc_length_assert (transfer_info_t * p_info)
{
    uint32_t i = 0;
    do
    {
        FSP_ERROR_RETURN(TRANSFER_ADDR_MODE_OFFSET != p_info[i].transfer_settings_word_b.src_addr_mode,
                         FSP_ERR_UNSUPPORTED);
        FSP_ERROR_RETURN(TRANSFER_ADDR_MODE_OFFSET != p_info[i].transfer_settings_word_b.dest_addr_mode,
                         FSP_ERR_UNSUPPORTED);

        if (TRANSFER_MODE_NORMAL != p_info[i].transfer_settings_word_b.mode)
        {
            /* transfer_length_max is the same for Block and repeat mode. */
            FSP_ASSERT(p_info[i].length <= DTC_MAX_REPEAT_TRANSFER_LENGTH);
        }
    } while (TRANSFER_CHAIN_MODE_DISABLED != p_info[i++].transfer_settings_word_b.chain_mode);

    return FSP_SUCCESS;
}

 #endif

/*******************************************************************************************************************//**
 * Check that the source and destination are not NULL and that they are aligned correctly.
 *
 * @retval FSP_SUCCESS              Parameters are valid.
 * @retval FSP_ERR_ASSERTION        An input parameter is invalid.
 * @retval FSP_ERR_UNSUPPORTED      Address Mode Offset is selected.
 *
 **********************************************************************************************************************/
static fsp_err_t r_dtc_source_destination_parameter_check (transfer_info_t * p_info)
{
    uint32_t i = 0;
    do
    {
        FSP_ERROR_RETURN(TRANSFER_ADDR_MODE_OFFSET != p_info[i].transfer_settings_word_b.src_addr_mode,
                         FSP_ERR_UNSUPPORTED);
        FSP_ERROR_RETURN(TRANSFER_ADDR_MODE_OFFSET != p_info[i].transfer_settings_word_b.dest_addr_mode,
                         FSP_ERR_UNSUPPORTED);
        FSP_ASSERT(NULL != p_info[i].p_src);
        FSP_ASSERT(NULL != p_info[i].p_dest);
        FSP_ASSERT(0U ==
                   ((uint32_t) p_info[i].p_dest & DTC_PRV_MASK_ALIGN_N_BYTES(p_info[i].transfer_settings_word_b.size)));
        FSP_ASSERT(0U ==
                   ((uint32_t) p_info[i].p_src & DTC_PRV_MASK_ALIGN_N_BYTES(p_info[i].transfer_settings_word_b.size)));
    } while (TRANSFER_CHAIN_MODE_DISABLED != p_info[i++].transfer_settings_word_b.chain_mode);

    return FSP_SUCCESS;
}

#endif

/*******************************************************************************************************************//**
 * Wait for the current DTC transfer to complete.
 **********************************************************************************************************************/
static void r_dtc_wait_for_transfer_complete (dtc_instance_ctrl_t * p_ctrl)
{
    uint32_t in_progress = (1U << DTC_PRV_OFFSET_IN_PROGRESS) | (uint32_t) p_ctrl->irq;

    /* Wait for the DTCSTS.ACT flag to be clear if the current vector is the activation source.*/
    FSP_HARDWARE_REGISTER_WAIT((FSP_STYPE3_REG16_READ(R_DTC->DTCSTS, !R_CPSCU->DTCSAR_b.DTCSTSA) == in_progress), 0);
}

/*******************************************************************************************************************//**
 * Disable transfers on activation source.
 **********************************************************************************************************************/
static void r_dtc_disable_transfer (const IRQn_Type irq)
{
#if BSP_FEATURE_ICU_HAS_IELSR
    R_ICU->IELSR_b[((uint32_t) irq)].DTCE = 0U;
#else
    R_ICU->DTCENCLR[(((uint32_t) irq) >> 5UL)] = 1UL << (((uint32_t) irq) & (uint32_t) 0x1FUL);
#endif
}
