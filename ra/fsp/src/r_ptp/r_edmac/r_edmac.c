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
 * Includes
 **********************************************************************************************************************/

#include "r_edmac.h"
#include "r_ptp_cfg.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define EDMAC_OPEN                  (0x45444D41U)
#define EDMAC_PCLKA_RESET_CYCLES    (64U)
#define EDMAC_FDR_VALUE             (0x0000070FU)
#define EDMAC_DESC_STATUS_ACTIVE    (1U << 31U)
#define EDMAC_TDLE                  (1U << 30U)
#define EDMAC_TD0_TFP0              (1U << 28U)
#define EDMAC_TD0_TFP1              (1U << 29U)

/***********************************************************************************************************************
 * Private function declarations
 **********************************************************************************************************************/
void r_edmac_hw_reset(edmac_instance_ctrl_t * p_ctrl);

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * This function initializes the EDMAC instance.
 *
 * This function performs the following tasks:
 * - Performs parameter checking and processes error conditions.
 * - Initialize the buffer descriptor lists to a known state.
 * - Write EDMAC configuration settings to registers.
 * - Initialize the control structure for use in other.
 *
 * @retval     FSP_SUCCESS                     The instance has been successfully configured.
 * @retval     FSP_ERR_ASSERTION               An invalid argument was given in the configuration structure.
 * @retval     FSP_ERR_ALREADY_OPEN            The EDMAC instance is already opened.
 **********************************************************************************************************************/
fsp_err_t R_EDMAC_Open (edmac_instance_ctrl_t * const p_ctrl, edmac_cfg_t const * const p_cfg)
{
#if PTP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(EDMAC_OPEN != p_ctrl->open, FSP_ERR_ALREADY_OPEN);
    FSP_ASSERT(NULL != p_cfg);
    FSP_ASSERT(p_cfg->edmac_irq >= 0);
    FSP_ASSERT(0 < p_cfg->num_rx_desc);
    FSP_ASSERT(0 < p_cfg->num_tx_desc);
    FSP_ASSERT(NULL != p_cfg->p_rx_descriptors);
    FSP_ASSERT(NULL != p_cfg->p_tx_descriptors);
#endif

    p_ctrl->p_reg = NULL;
    if (PTPC_EDMAC_CHANNEL == p_cfg->channel)
    {
        p_ctrl->p_reg = R_PTP_EDMAC;
    }
    else if (ETHERC_EDMAC_CHANNEL == p_cfg->channel)
    {
        p_ctrl->p_reg = R_ETHERC_EDMAC;
    }
    else
    {
        return FSP_ERR_ASSERTION;
    }

    /* Mark the driver as open. */
    p_ctrl->open = EDMAC_OPEN;

    /* Save the configuration structure. */
    p_ctrl->p_cfg = p_cfg;

    /* Clear the rx an tx descriptor lists. */
    memset(p_cfg->p_rx_descriptors, 0U, p_cfg->num_rx_desc * sizeof(edmac_desc_t));
    memset(p_cfg->p_tx_descriptors, 0U, p_cfg->num_tx_desc * sizeof(edmac_desc_t));

    /*
     * TBL must be set to a value greater than or equal to 1
     * (See section 31.3.1.1 of the RA6M3 manual R01UH0886EJ0100).
     */
    for (uint32_t i = 0; i < p_cfg->num_tx_desc; i++)
    {
        p_cfg->p_tx_descriptors[i].buffer_size = 1;
    }

    /* Mark the last descriptor in the tx and rx descriptor lists. */
    p_cfg->p_rx_descriptors[p_cfg->num_rx_desc - 1U].status.raw = EDMAC_TDLE;
    p_cfg->p_tx_descriptors[p_cfg->num_tx_desc - 1U].status.raw = EDMAC_TDLE;

    /* Reset the EDMAC peripheral. */
    r_edmac_hw_reset(p_ctrl);

    /* Set little endian mode. */
    p_ctrl->p_reg->EDMR = R_ETHERC_EDMAC_EDMR_DE_Msk;

    /* Set pointer to transmit descriptor list. */
    p_ctrl->p_reg->TDLAR = (uint32_t) p_cfg->p_tx_descriptors;

    /* Set pointer to receive descriptor list. */
    p_ctrl->p_reg->RDLAR = (uint32_t) p_cfg->p_rx_descriptors;

    /*
     * Set the fifo depth register acording to the hardware manual
     * (Reference section 31.2.13 FIFO Depth Register (FDR) in the RA6M3 manual R01UH0886EJ0100).
     */
    p_ctrl->p_reg->FDR = EDMAC_FDR_VALUE;

    /* Set RNR so that the EDRRR.RR is not cleared after receiving a single ethernet frame. */
    p_ctrl->p_reg->RMCR = 1U;

    /* Enable the frame receive interrupt request and frame transfer complete interrupt request. */
    p_ctrl->p_reg->EESIPR = R_ETHERC_EDMAC_EESIPR_FRIP_Msk | R_ETHERC_EDMAC_EESIPR_TCIP_Msk;

    /* Enable the EDMAC interrupt. */
    R_BSP_IrqCfgEnable(p_cfg->edmac_irq, p_cfg->edmac_ipl, p_ctrl);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Updates the buffer address of a descriptor.
 * If it is a reveive descriptor, re-enable receive requests.
 * If it is a transmit descriptor, re-enable transmit requests.
 *
 * @retval     FSP_SUCCESS                     The buffer descriptor has been updated.
 * @retval     FSP_ERR_NOT_OPEN                The instance has not been opened.
 * @retval     FSP_ERR_ASSERTION               An argument is invalid or NULL.
 **********************************************************************************************************************/
fsp_err_t R_EDMAC_DescriptorUpdate (edmac_instance_ctrl_t * const p_ctrl,
                                    edmac_desc_type_t             type,
                                    uint32_t                      index,
                                    uint8_t * const               p_buffer,
                                    uint16_t                      length)
{
#if PTP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(EDMAC_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ASSERT(NULL != p_buffer);
    FSP_ASSERT(0 < length);

    if (EDMAC_DESC_RECEIVE == type)
    {
        FSP_ASSERT(index < p_ctrl->p_cfg->num_rx_desc);
    }
    else
    {
        FSP_ASSERT(index < p_ctrl->p_cfg->num_tx_desc);
    }
#endif

    if (EDMAC_DESC_RECEIVE == type)
    {
        p_ctrl->p_cfg->p_rx_descriptors[index].p_buffer            = p_buffer;
        p_ctrl->p_cfg->p_rx_descriptors[index].buffer_size         = length;
        p_ctrl->p_cfg->p_rx_descriptors[index].status.raw         &= EDMAC_TDLE;
        p_ctrl->p_cfg->p_rx_descriptors[index].status.raw_b.active = 1U;

        /* Re-enable the receive request register in case it was cleared. */
        if (0U == p_ctrl->p_reg->EDRRR)
        {
            p_ctrl->p_reg->EDRRR = 1U;
        }
    }
    else
    {
        p_ctrl->p_cfg->p_tx_descriptors[index].p_buffer    = p_buffer;
        p_ctrl->p_cfg->p_tx_descriptors[index].buffer_size = length;
        p_ctrl->p_cfg->p_tx_descriptors[index].status.raw &= EDMAC_TDLE;
        p_ctrl->p_cfg->p_tx_descriptors[index].status.raw |= EDMAC_DESC_STATUS_ACTIVE | EDMAC_TD0_TFP1 | EDMAC_TD0_TFP0;

        /* Re-enable the transmit request register in case it was cleared. */
        if (0U == p_ctrl->p_reg->EDTRR)
        {
            p_ctrl->p_reg->EDTRR = 1U;
        }
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Get a pointer to a descriptor.
 *
 * @retval     FSP_SUCCESS                     The address of the descriptor at the index has been written to p_desc.
 * @retval     FSP_ERR_NOT_OPEN                The instance has not been opened.
 * @retval     FSP_ERR_ASSERTION               An argument is invalid or NULL.
 **********************************************************************************************************************/
fsp_err_t R_EDMAC_DescriptorGet (edmac_instance_ctrl_t * const p_ctrl,
                                 edmac_desc_type_t             type,
                                 uint32_t                      index,
                                 edmac_desc_t ** const         p_desc)
{
#if PTP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(EDMAC_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ASSERT(NULL != p_desc);
    if (EDMAC_DESC_RECEIVE == type)
    {
        FSP_ASSERT(index < p_ctrl->p_cfg->num_rx_desc);
    }
    else
    {
        FSP_ASSERT(index < p_ctrl->p_cfg->num_tx_desc);
    }
#endif

    if (EDMAC_DESC_RECEIVE == type)
    {
        *p_desc = &p_ctrl->p_cfg->p_rx_descriptors[index];
    }
    else
    {
        *p_desc = &p_ctrl->p_cfg->p_tx_descriptors[index];
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Disable an EDMAC instance and mark it as closed.
 *
 * @retval     FSP_SUCCESS                     The instance has been closed.
 * @retval     FSP_ERR_NOT_OPEN                The instance has not been opened.
 * @retval     FSP_ERR_ASSERTION               An argument is invalid or NULL.
 **********************************************************************************************************************/
fsp_err_t R_EDMAC_Close (edmac_instance_ctrl_t * const p_ctrl)
{
#if PTP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(EDMAC_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Reset the EDMAC peripheral. */
    r_edmac_hw_reset(p_ctrl);

    /* Disable the EDMAC interrupt. */
    R_BSP_IrqDisable(p_ctrl->p_cfg->edmac_irq);

    /* Mark the driver as close. */
    p_ctrl->open = 0U;

    return FSP_SUCCESS;
}

void r_edmac_hw_reset (edmac_instance_ctrl_t * p_ctrl)
{
    /* Reset the EDMAC peripheral. */
    p_ctrl->p_reg->EDMR = 1U;

    uint32_t pclka_freq = SystemCoreClock << R_SYSTEM->SCKDIVCR_b.ICK;
    pclka_freq >>= R_SYSTEM->SCKDIVCR_b.PCKA;

    uint32_t delay_microseconds = EDMAC_PCLKA_RESET_CYCLES * BSP_DELAY_UNITS_SECONDS / pclka_freq + 1U;

    /* Wait 64 cycles of PCLKA for the EDMAC peripheral to reset
     * (See section 31.2.1 of the RA6M3 manual R01UH0886EJ0100). */
    R_BSP_SoftwareDelay(delay_microseconds, BSP_DELAY_UNITS_MICROSECONDS);
}

void edmac_eint_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE;

    IRQn_Type               irq             = R_FSP_CurrentIrqGet();
    edmac_instance_ctrl_t * p_instance_ctrl = (edmac_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    edmac_callback_args_t callback_args;

    /* Read the status flags. */
    callback_args.status = p_instance_ctrl->p_reg->EESR;

    /* Clear all status flags. */
    p_instance_ctrl->p_reg->EESR = callback_args.status;

    callback_args.p_context = p_instance_ctrl->p_cfg->p_context;

    /* Call user callback. */
    p_instance_ctrl->p_cfg->p_callback(&callback_args);

    /* Clear interrupt request. */
    R_BSP_IrqStatusClear(irq);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE;
}
