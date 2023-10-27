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
#include "bsp_api.h"
#include "r_ospi_b.h"

#if OSPI_B_CFG_DMAC_SUPPORT_ENABLE
 #include "r_transfer_api.h"
 #include "r_dmac.h"
#endif

#if OSPI_B_CFG_DOTF_SUPPORT_ENABLE
 #include "hw_sce_ra_private.h"
#endif

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* "xSPI" in ASCII.  Used to determine if the control block is open. */
#define OSPI_B_PRV_OPEN                                  (0x78535049U)

#define OSPI_B_PRV_BMCTL_DEFAULT_VALUE                   (0x0C)

#define OSPI_B_PRV_CMCFG_1BYTE_VALUE_MASK                (0xFF00U)
#define OSPI_B_PRV_CMCFG_2BYTE_VALUE_MASK                (0xFFFFU)

#define OSPI_B_PRV_AUTOCALIBRATION_DATA_SIZE             (0xFU)
#define OSPI_B_PRV_AUTOCALIBRATION_LATENCY_CYCLES        (0U)

#define OSPI_B_PRV_AUTOCALIBRATION_PREAMBLE_PATTERN_0    (0xFFFF0000U)
#define OSPI_B_PRV_AUTOCALIBRATION_PREAMBLE_PATTERN_1    (0x000800FFU)
#define OSPI_B_PRV_AUTOCALIBRATION_PREAMBLE_PATTERN_2    (0x00FFF700U)
#define OSPI_B_PRV_AUTOCALIBRATION_PREAMBLE_PATTERN_3    (0xF700F708U)

#define OSPI_B_PRV_ADDRESS_REPLACE_VALUE                 (0xF0U)
#define OSPI_B_PRV_ADDRESS_REPLACE_ENABLE_BITS           (OSPI_B_PRV_ADDRESS_REPLACE_VALUE << \
                                                          R_XSPI_CMCFGCS_CMCFG0_ADDRPEN_Pos)
#define OSPI_B_PRV_ADDRESS_REPLACE_MASK                  (~(OSPI_B_PRV_ADDRESS_REPLACE_VALUE << 24))

#define OSPI_B_PRV_AUTOCALIBRATION_FRAME_INTERVAL        (0x1FU)
#define OSPI_B_PRV_AUTOCALIBRATION_NO_WRITE_CMD          (0x1U)
#define OSPI_B_PRV_AUTOCALIBRATION_SHIFT_DS_END_VALUE    (0x1FU)

#define OSPI_B_PRV_WORD_ACCESS_SIZE                      (4U)
#define OSPI_B_PRV_HALF_WORD_ACCESS_SIZE                 (2U)

#define OSPI_B_PRV_DIRECT_ADDR_AND_DATA_MASK             (7U)
#define OSPI_B_PRV_PAGE_SIZE_BYTES                       (256U)

#define OSPI_B_PRV_DIRECT_CMD_SIZE_MASK                  (0x3U)

#define OSPI_B_PRV_CDTBUF_CMD_OFFSET                     (16U)
#define OSPI_B_PRV_CDTBUF_CMD_UPPER_OFFSET               (24U)
#define OSPI_B_PRV_CDTBUF_CMD_1B_VALUE_MASK              (0xFFU)
#define OSPI_B_PRV_CDTBUF_CMD_1B_VALUE_SHIFT             (8U)
#define OSPI_B_PRV_CDTBUF_CMD_2B_VALUE_MASK              (0xFFFFU)

#define OSPI_B_PRV_BMCTL0_DISABLED_VALUE                 (0x00) // 0b0000'0000
#define OSPI_B_PRV_BMCTL0_READ_ONLY_VALUE                (0x55) // 0b0101'0101
#define OSPI_B_PRV_BMCTL0_WRITE_ONLY_VALUE               (0xAA) // 0b1010'1010
#define OSPI_B_PRV_BMCTL0_READ_WRITE_VALUE               (0xFF) // 0b1111'1111

#define OSPI_B_PRV_BMCTL1_CLEAR_PREFETCH_MASK            (0x03 << R_XSPI_BMCTL1_PBUFCLRCH_Pos)
#define OSPI_B_PRV_BMCTL1_PUSH_COMBINATION_WRITE_MASK    (0x03 << R_XSPI_BMCTL1_MWRPUSHCH_Pos)

#define OSPI_B_PRV_COMSTT_MEMACCCH_MASK                  (0x03 << R_XSPI_COMSTT_MEMACCCH_Pos)

#define OSPI_B_SOFTWARE_DELAY                            (50U)

#define OSPI_B_PRV_DOTF_REG00_RESET_VALUE                (0x22000000)

/* These are used as modulus checking, make sure they are powers of 2. */
#define OSPI_B_PRV_CPU_ACCESS_LENGTH                     (8U)
#define OSPI_B_PRV_CPU_ACCESS_ALIGNMENT                  (8U)

#define OSPI_B_PRV_PROTOCOL_USES_DS_MASK                 (0x200U)

#define OSPI_B_PRV_UINT32_BITS                           (32)

#ifndef OSPI_B_MAX_WRITE_ENABLE_LOOPS
 #define OSPI_B_MAX_WRITE_ENABLE_LOOPS                   (5)
#endif

/* Number of address bytes in 4 byte address mode. */
#define OSPI_B_4_BYTE_ADDRESS                            (4U)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
static bool      r_ospi_b_status_sub(ospi_b_instance_ctrl_t * p_instance_ctrl, uint8_t bit_pos);
static fsp_err_t r_ospi_b_protocol_specific_settings(ospi_b_instance_ctrl_t * p_instance_ctrl);
static fsp_err_t r_ospi_b_write_enable(ospi_b_instance_ctrl_t * p_instance_ctrl);
static void      r_ospi_b_direct_transfer(ospi_b_device_number_t              channel,
                                          spi_flash_direct_transfer_t * const p_transfer,
                                          spi_flash_direct_transfer_dir_t     direction);
static ospi_b_xspi_command_set_t const * r_ospi_b_command_set_get(ospi_b_instance_ctrl_t * p_instance_ctrl);

#if OSPI_B_CFG_AUTOCALIBRATION_SUPPORT_ENABLE
static fsp_err_t r_ospi_b_automatic_calibration_seq(ospi_b_instance_ctrl_t * p_instance_ctrl);

#endif

#if OSPI_B_CFG_XIP_SUPPORT_ENABLE
static void r_ospi_b_xip(ospi_b_instance_ctrl_t * p_instance_ctrl, bool is_entering);

#endif

#if OSPI_B_CFG_DOTF_SUPPORT_ENABLE
static fsp_err_t r_ospi_b_dotf_setup(ospi_b_dotf_cfg_t * p_dotf_cfg);

#endif

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/* Bit-flags specifying which channels are open so the module can be stopped when all are closed. */
static uint32_t g_ospi_b_channels_open_flags = 0;

/*******************************************************************************************************************//**
 * @addtogroup OSPI_B
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Global Variables
 **********************************************************************************************************************/

const spi_flash_api_t g_ospi_b_on_spi_flash =
{
    .open           = R_OSPI_B_Open,
    .directWrite    = R_OSPI_B_DirectWrite,
    .directRead     = R_OSPI_B_DirectRead,
    .directTransfer = R_OSPI_B_DirectTransfer,
    .spiProtocolSet = R_OSPI_B_SpiProtocolSet,
    .write          = R_OSPI_B_Write,
    .erase          = R_OSPI_B_Erase,
    .statusGet      = R_OSPI_B_StatusGet,
    .xipEnter       = R_OSPI_B_XipEnter,
    .xipExit        = R_OSPI_B_XipExit,
    .bankSet        = R_OSPI_B_BankSet,
    .close          = R_OSPI_B_Close,
    .autoCalibrate  = R_OSPI_B_AutoCalibrate,
};

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Open the xSPI device. After the driver is open, the xSPI device can be accessed like internal flash memory.
 *
 * Implements @ref spi_flash_api_t::open.
 *
 * @retval FSP_SUCCESS              Configuration was successful.
 * @retval FSP_ERR_ASSERTION        The parameter p_ctrl or p_cfg is NULL.
 * @retval FSP_ERR_ALREADY_OPEN     Driver has already been opened with the same p_ctrl.
 * @retval FSP_ERR_CALIBRATE_FAILED Failed to perform auto-calibrate.
 **********************************************************************************************************************/
fsp_err_t R_OSPI_B_Open (spi_flash_ctrl_t * const p_ctrl, spi_flash_cfg_t const * const p_cfg)
{
    ospi_b_instance_ctrl_t * p_instance_ctrl = (ospi_b_instance_ctrl_t *) p_ctrl;

#if OSPI_B_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_cfg);
    FSP_ASSERT(NULL != p_cfg->p_extend);
    FSP_ERROR_RETURN(OSPI_B_PRV_OPEN != p_instance_ctrl->open, FSP_ERR_ALREADY_OPEN);
#endif

    ospi_b_extended_cfg_t * p_cfg_extend = (ospi_b_extended_cfg_t *) p_cfg->p_extend;

#if OSPI_B_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN((g_ospi_b_channels_open_flags & (1U << p_cfg_extend->channel)) == 0, FSP_ERR_ALREADY_OPEN);
#endif

    /* Enable clock to the xSPI block */
    R_BSP_MODULE_START(FSP_IP_OSPI, 0U);

    /* Initialize control block. */
    p_instance_ctrl->p_cfg        = p_cfg;
    p_instance_ctrl->spi_protocol = p_cfg->spi_protocol;
    p_instance_ctrl->channel      = p_cfg_extend->channel;

#if OSPI_B_CFG_DOTF_SUPPORT_ENABLE
    if (NULL != p_cfg_extend->p_dotf_cfg)
    {
        fsp_err_t dotf_ret = r_ospi_b_dotf_setup((ospi_b_dotf_cfg_t *) p_cfg_extend->p_dotf_cfg);
        if (FSP_SUCCESS != dotf_ret)
        {
            /* If the DOTF initialization fails, stop the module if no other channels are active. */
            if (g_ospi_b_channels_open_flags == 0)
            {
                R_BSP_MODULE_STOP(FSP_IP_OSPI, 0U);
            }

            return dotf_ret;
        }
    }
#endif

#if OSPI_B_CFG_DMAC_SUPPORT_ENABLE
    transfer_instance_t const * p_transfer = p_cfg_extend->p_lower_lvl_transfer;
 #if OSPI_B_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_transfer);
 #endif

    /* Initialize transfer instance */
    p_transfer->p_api->open(p_transfer->p_ctrl, p_transfer->p_cfg);
#endif

    /* Disable memory-mapping for this slave. It will be enabled later on after initialization. */
    if (OSPI_B_DEVICE_NUMBER_0 == p_instance_ctrl->channel)
    {
        R_XSPI->BMCTL0 &= ~(R_XSPI_BMCTL0_CH0CS0ACC_Msk | R_XSPI_BMCTL0_CH1CS0ACC_Msk);
    }
    else
    {
        R_XSPI->BMCTL0 &= ~(R_XSPI_BMCTL0_CH0CS1ACC_Msk | R_XSPI_BMCTL0_CH1CS1ACC_Msk);
    }

    /* Perform xSPI Initial configuration as described in hardware manual (see Section 37.3.8
     * 'Flow of Operations' of the RA8M1 manual R01UH0994EJ0100). */

    /* Set xSPI protocol mode. */
    uint32_t liocfg = ((uint32_t) p_cfg->spi_protocol) << R_XSPI_LIOCFGCS_PRTMD_Pos;
    R_XSPI->LIOCFGCS[p_cfg_extend->channel] = liocfg;

    /* Set xSPI drive/sampling timing. */
    if (OSPI_B_DEVICE_NUMBER_0 == p_instance_ctrl->channel)
    {
        R_XSPI->WRAPCFG = ((uint32_t) p_cfg_extend->data_latch_delay_clocks << R_XSPI_WRAPCFG_DSSFTCS0_Pos) &
                          R_XSPI_WRAPCFG_DSSFTCS0_Msk;
    }
    else
    {
        R_XSPI->WRAPCFG = ((uint32_t) p_cfg_extend->data_latch_delay_clocks << R_XSPI_WRAPCFG_DSSFTCS1_Pos) &
                          R_XSPI_WRAPCFG_DSSFTCS1_Msk;
    }

    /* Set minimum cycles between xSPI frames. */
    liocfg |= ((uint32_t) p_cfg_extend->p_timing_settings->command_to_command_interval << R_XSPI_LIOCFGCS_CSMIN_Pos) &
              R_XSPI_LIOCFGCS_CSMIN_Msk;

    /* Set CS asserting extension in cycles */
    liocfg |= ((uint32_t) p_cfg_extend->p_timing_settings->cs_pulldown_lead << R_XSPI_LIOCFGCS_CSASTEX_Pos) &
              R_XSPI_LIOCFGCS_CSASTEX_Msk;

    /* Set CS releasing extension in cycles */
    liocfg |= ((uint32_t) p_cfg_extend->p_timing_settings->cs_pullup_lag << R_XSPI_LIOCFGCS_CSNEGEX_Pos) &
              R_XSPI_LIOCFGCS_CSNEGEX_Msk;

    /* Set xSPI CSn signal timings. */
    R_XSPI->LIOCFGCS[p_cfg_extend->channel] = liocfg;

    /* Set xSPI memory-mapping operation. */
    fsp_err_t ret = r_ospi_b_protocol_specific_settings(p_instance_ctrl);

    /* Return response after issuing write transaction to xSPI bus, Enable prefetch function and combination if desired. */
    const uint32_t bmcfgch = (0 << R_XSPI_BMCFGCH_WRMD_Pos) |
                             ((OSPI_B_CFG_COMBINATION_FUNCTION << R_XSPI_BMCFGCH_MWRCOMB_Pos) &
                              (R_XSPI_BMCFGCH_MWRCOMB_Msk | R_XSPI_BMCFGCH_MWRSIZE_Msk)) |
                             ((OSPI_B_CFG_PREFETCH_FUNCTION << R_XSPI_BMCFGCH_PREEN_Pos) &
                              R_XSPI_BMCFGCH_PREEN_Msk);

    /* Both of these should have the same configuration and it affects all OSPI slave channels. */
    R_XSPI->BMCFGCH[0] = bmcfgch;
    R_XSPI->BMCFGCH[1] = bmcfgch;

    /* Re-activate memory-mapped mode in Read/Write. */
    if (p_instance_ctrl->channel == 0)
    {
        R_XSPI->BMCTL0 |= R_XSPI_BMCTL0_CH0CS0ACC_Msk | R_XSPI_BMCTL0_CH1CS0ACC_Msk;
    }
    else
    {
        R_XSPI->BMCTL0 |= R_XSPI_BMCTL0_CH0CS1ACC_Msk | R_XSPI_BMCTL0_CH1CS1ACC_Msk;
    }

    if (FSP_SUCCESS == ret)
    {
        p_instance_ctrl->open         = OSPI_B_PRV_OPEN;
        g_ospi_b_channels_open_flags |= (1U << p_instance_ctrl->channel);
    }
    else if (g_ospi_b_channels_open_flags == 0)
    {
        /* If the open fails and no other channels are open, stop the module. */
        R_BSP_MODULE_STOP(FSP_IP_OSPI, 0U);
    }
    else
    {
        // Do nothing.
    }

    return ret;
}

/*******************************************************************************************************************//**
 * Writes raw data directly to the OctaFlash. API not supported. Use R_OSPI_B_DirectTransfer
 *
 * Implements @ref spi_flash_api_t::directWrite.
 *
 * @retval FSP_ERR_UNSUPPORTED         API not supported by OSPI.
 **********************************************************************************************************************/
fsp_err_t R_OSPI_B_DirectWrite (spi_flash_ctrl_t    * p_ctrl,
                                uint8_t const * const p_src,
                                uint32_t const        bytes,
                                bool const            read_after_write)
{
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(p_src);
    FSP_PARAMETER_NOT_USED(bytes);
    FSP_PARAMETER_NOT_USED(read_after_write);

    FSP_RETURN(FSP_ERR_UNSUPPORTED);
}

/*******************************************************************************************************************//**
 * Reads raw data directly from the OctaFlash. API not supported. Use R_OSPI_B_DirectTransfer.
 *
 * Implements @ref spi_flash_api_t::directRead.
 *
 * @retval FSP_ERR_UNSUPPORTED         API not supported by OSPI.
 **********************************************************************************************************************/
fsp_err_t R_OSPI_B_DirectRead (spi_flash_ctrl_t * p_ctrl, uint8_t * const p_dest, uint32_t const bytes)
{
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(p_dest);
    FSP_PARAMETER_NOT_USED(bytes);

    FSP_RETURN(FSP_ERR_UNSUPPORTED);
}

/*******************************************************************************************************************//**
 * Read/Write raw data directly with the OctaFlash.
 *
 * Implements @ref spi_flash_api_t::directTransfer.
 *
 * @retval FSP_SUCCESS                 The flash was programmed successfully.
 * @retval FSP_ERR_ASSERTION           A required pointer is NULL.
 * @retval FSP_ERR_NOT_OPEN            Driver is not opened.
 **********************************************************************************************************************/
fsp_err_t R_OSPI_B_DirectTransfer (spi_flash_ctrl_t                  * p_ctrl,
                                   spi_flash_direct_transfer_t * const p_transfer,
                                   spi_flash_direct_transfer_dir_t     direction)
{
    ospi_b_instance_ctrl_t * p_instance_ctrl = (ospi_b_instance_ctrl_t *) p_ctrl;

#if OSPI_B_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_transfer);
    FSP_ASSERT(0 != p_transfer->command_length);
    FSP_ERROR_RETURN(OSPI_B_PRV_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    r_ospi_b_direct_transfer(p_instance_ctrl->channel, p_transfer, direction);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Enters XIP (execute in place) mode.
 *
 * Implements @ref spi_flash_api_t::xipEnter.
 *
 * @retval FSP_SUCCESS                 XiP mode was entered successfully.
 * @retval FSP_ERR_ASSERTION           A required pointer is NULL.
 * @retval FSP_ERR_NOT_OPEN            Driver is not opened.
 * @retval FSP_ERR_UNSUPPORTED         XiP support is not enabled.
 **********************************************************************************************************************/
fsp_err_t R_OSPI_B_XipEnter (spi_flash_ctrl_t * p_ctrl)
{
#if OSPI_B_CFG_XIP_SUPPORT_ENABLE
    ospi_b_instance_ctrl_t * p_instance_ctrl = (ospi_b_instance_ctrl_t *) p_ctrl;

 #if OSPI_B_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_instance_ctrl->p_cfg);
    FSP_ERROR_RETURN(OSPI_B_PRV_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
 #endif

    r_ospi_b_xip(p_instance_ctrl, true);

    return FSP_SUCCESS;
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);

    return FSP_ERR_UNSUPPORTED;
#endif
}

/*******************************************************************************************************************//**
 * Exits XIP (execute in place) mode.
 *
 * Implements @ref spi_flash_api_t::xipExit.
 *
 * @retval FSP_SUCCESS                 XiP mode was entered successfully.
 * @retval FSP_ERR_ASSERTION           A required pointer is NULL.
 * @retval FSP_ERR_NOT_OPEN            Driver is not opened.
 * @retval FSP_ERR_UNSUPPORTED         XiP support is not enabled.
 **********************************************************************************************************************/
fsp_err_t R_OSPI_B_XipExit (spi_flash_ctrl_t * p_ctrl)
{
#if OSPI_B_CFG_XIP_SUPPORT_ENABLE
    ospi_b_instance_ctrl_t * p_instance_ctrl = (ospi_b_instance_ctrl_t *) p_ctrl;

 #if OSPI_B_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_instance_ctrl->p_cfg);
    FSP_ERROR_RETURN(OSPI_B_PRV_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
 #endif

    r_ospi_b_xip(p_instance_ctrl, false);

    return FSP_SUCCESS;
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);

    return FSP_ERR_UNSUPPORTED;
#endif
}

/*******************************************************************************************************************//**
 * Program a page of data to the flash.
 *
 * Implements @ref spi_flash_api_t::write.
 *
 * @retval FSP_SUCCESS                 The flash was programmed successfully.
 * @retval FSP_ERR_ASSERTION           p_instance_ctrl, p_dest or p_src is NULL, or byte_count crosses a page boundary.
 * @retval FSP_ERR_NOT_OPEN            Driver is not opened.
 * @retval FSP_ERR_INVALID_SIZE        Insufficient space remaining in page or write length is not a multiple of CPU access size when not using the DMAC.
 * @retval FSP_ERR_DEVICE_BUSY         Another Write/Erase transaction is in progress.
 * @retval FSP_ERR_WRITE_FAILED        Write operation failed.
 * @retval FSP_ERR_INVALID_ADDRESS     Destination or source is not aligned to CPU access alignment when not using the DMAC.
 **********************************************************************************************************************/
fsp_err_t R_OSPI_B_Write (spi_flash_ctrl_t    * p_ctrl,
                          uint8_t const * const p_src,
                          uint8_t * const       p_dest,
                          uint32_t              byte_count)
{
    ospi_b_instance_ctrl_t * p_instance_ctrl = (ospi_b_instance_ctrl_t *) p_ctrl;
    fsp_err_t                err             = FSP_SUCCESS;
#if OSPI_B_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_src);
    FSP_ASSERT(NULL != p_dest);
    FSP_ASSERT(0 != byte_count);
    FSP_ERROR_RETURN(OSPI_B_PRV_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);

    /* Check that space remaining in page is sufficient for requested write size */
    uint32_t page_size   = p_instance_ctrl->p_cfg->page_size_bytes;
    uint32_t page_offset = (uint32_t) p_dest & (page_size - 1);
    FSP_ERROR_RETURN((page_size - page_offset) >= byte_count, FSP_ERR_INVALID_SIZE);

 #if !OSPI_B_CFG_DMAC_SUPPORT_ENABLE
    FSP_ERROR_RETURN((byte_count & (OSPI_B_PRV_CPU_ACCESS_LENGTH - 1)) == 0, FSP_ERR_INVALID_SIZE);
    FSP_ERROR_RETURN(((uint32_t) p_dest & (OSPI_B_PRV_CPU_ACCESS_ALIGNMENT - 1)) == 0, FSP_ERR_INVALID_ADDRESS);
  #if defined(__llvm__) && !defined(__ARMCC_VERSION)

    /* LLVM needs 32-bit aligned data. */
    FSP_ERROR_RETURN(((uint32_t) p_src & (0x3)) == 0, FSP_ERR_INVALID_ADDRESS);
  #endif
 #endif
#endif

    FSP_ERROR_RETURN(false == r_ospi_b_status_sub(p_instance_ctrl, p_instance_ctrl->p_cfg->write_status_bit),
                     FSP_ERR_DEVICE_BUSY);

#if OSPI_B_CFG_DMAC_SUPPORT_ENABLE
    spi_flash_cfg_t       * p_cfg        = (spi_flash_cfg_t *) p_instance_ctrl->p_cfg;
    ospi_b_extended_cfg_t * p_cfg_extend = (ospi_b_extended_cfg_t *) p_cfg->p_extend;

    /* Setup and start DMAC transfer. */
    transfer_instance_t const * p_transfer = p_cfg_extend->p_lower_lvl_transfer;

    /* Enable Octa-SPI DMA Bufferable Write */
    dmac_extended_cfg_t const * p_dmac_extend = p_transfer->p_cfg->p_extend;
    R_DMAC0_Type              * p_dma_reg     = R_DMAC0 + (sizeof(R_DMAC0_Type) * p_dmac_extend->channel);
    p_dma_reg->DMBWR = R_DMAC0_DMBWR_BWE_Msk;

    /* Update the block-mode transfer settings */
    p_transfer->p_cfg->p_info->p_src  = p_src;
    p_transfer->p_cfg->p_info->p_dest = p_dest;
    p_transfer->p_cfg->p_info->transfer_settings_word_b.size = TRANSFER_SIZE_1_BYTE;
    p_transfer->p_cfg->p_info->transfer_settings_word_b.mode = TRANSFER_MODE_NORMAL;
    p_transfer->p_cfg->p_info->length = (uint16_t) byte_count;
    err = p_transfer->p_api->reconfigure(p_transfer->p_ctrl, p_transfer->p_cfg->p_info);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    r_ospi_b_write_enable(p_instance_ctrl);

    /* Start DMA */
    err = p_transfer->p_api->softwareStart(p_transfer->p_ctrl, TRANSFER_START_MODE_REPEAT);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Wait for DMAC to complete to maintain deterministic processing and backward compatability */
    volatile transfer_properties_t transfer_properties = {0U};
    err = p_transfer->p_api->infoGet(p_transfer->p_ctrl, (transfer_properties_t *) &transfer_properties);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    while (FSP_SUCCESS == err && transfer_properties.transfer_length_remaining > 0)
    {
        err = p_transfer->p_api->infoGet(p_transfer->p_ctrl, (transfer_properties_t *) &transfer_properties);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }

    /* Disable Octa-SPI DMA Bufferable Write */
    p_dma_reg->DMBWR = 0U;

    /* If this number of bytes is less than the combination count, push the data to force a transaction. */
    if (OSPI_B_CFG_COMBINATION_FUNCTION != OSPI_B_COMBINATION_FUNCTION_DISABLE)
    {
        uint8_t combo_bytes = (uint8_t) (2U * ((uint8_t) OSPI_B_CFG_COMBINATION_FUNCTION + 1U));
        if (byte_count < combo_bytes)
        {
            R_XSPI->BMCTL1 = OSPI_B_PRV_BMCTL1_PUSH_COMBINATION_WRITE_MASK;;
        }
    }

#else
    uint64_t * p_dest64 = (uint64_t *) ((uint32_t) p_dest & ~(OSPI_B_PRV_CPU_ACCESS_ALIGNMENT - 1));
    uint64_t * p_src64  = (uint64_t *) p_src;

    err = r_ospi_b_write_enable(p_instance_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    while (sizeof(uint64_t) <= byte_count)
    {
        /* When combination function is enabled, xSPI master transmits a xSPI
         * frame with the selected size while the sequential address is incremental. Please read Section 37.3.3.3
         * Combination Function' of the RA8M1 manual R01UH0994EJ0100. So Basically Enable command should be
         * sent only once for a single burst(incremented addresses up to set combination size.). */
        *p_dest64 = *p_src64;
        p_dest64++;
        p_src64++;
        byte_count -= sizeof(uint64_t);
    }

    __DMB();

    R_XSPI->BMCTL1 = OSPI_B_PRV_BMCTL1_PUSH_COMBINATION_WRITE_MASK;
#endif

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Erase a block or sector of flash.  The byte_count must exactly match one of the erase sizes defined in spi_flash_cfg_t.
 * For chip erase, byte_count must be SPI_FLASH_ERASE_SIZE_CHIP_ERASE.
 *
 * Implements @ref spi_flash_api_t::erase.
 *
 * @retval FSP_SUCCESS                 The command to erase the flash was executed successfully.
 * @retval FSP_ERR_ASSERTION           p_instance_ctrl or p_device_address is NULL, byte_count doesn't match an erase
 *                                     size defined in spi_flash_cfg_t, or byte_count is set to 0.
 * @retval FSP_ERR_NOT_OPEN            Driver is not opened.
 * @retval FSP_ERR_DEVICE_BUSY         The device is busy.
 * @retval FSP_ERR_WRITE_FAILED        Write operation failed.
 **********************************************************************************************************************/
fsp_err_t R_OSPI_B_Erase (spi_flash_ctrl_t * p_ctrl, uint8_t * const p_device_address, uint32_t byte_count)
{
    ospi_b_instance_ctrl_t * p_instance_ctrl = (ospi_b_instance_ctrl_t *) p_ctrl;

#if OSPI_B_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_device_address);
    FSP_ASSERT(0 != byte_count);
    FSP_ERROR_RETURN(OSPI_B_PRV_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif
    spi_flash_cfg_t const * p_cfg             = p_instance_ctrl->p_cfg;
    uint16_t                erase_command     = 0;
    const uint32_t          chip_address_base = p_instance_ctrl->channel ?
                                                BSP_FEATURE_OSPI_B_DEVICE_1_START_ADDRESS :
                                                BSP_FEATURE_OSPI_B_DEVICE_0_START_ADDRESS;
    uint32_t chip_address = (uint32_t) p_device_address - chip_address_base;
    bool     send_address = true;

    ospi_b_xspi_command_set_t const * p_cmd_set = p_instance_ctrl->p_cmd_set;

    FSP_ERROR_RETURN(false == r_ospi_b_status_sub(p_instance_ctrl, p_cfg->write_status_bit), FSP_ERR_DEVICE_BUSY);

    /* Select the erase commands from either the default SPI settings or the protocol settings if provided. */
    spi_flash_erase_command_t const * p_erase_list = ((NULL != p_cmd_set) && p_cmd_set->p_erase_command_list) ?
                                                     p_cmd_set->p_erase_command_list : p_cfg->p_erase_command_list;
    const uint8_t erase_list_length = ((NULL != p_cmd_set) && p_cmd_set->p_erase_command_list) ?
                                      p_cmd_set->erase_command_list_length : p_cfg->erase_command_list_length;

    for (uint32_t index = 0; index < erase_list_length; index++)
    {
        /* If requested byte_count is supported by underlying flash, store the command. */
        if (byte_count == p_erase_list[index].size)
        {
            if (SPI_FLASH_ERASE_SIZE_CHIP_ERASE == byte_count)
            {
                /* Don't send address for chip erase. */
                send_address = false;
            }

            erase_command = p_erase_list[index].command;
            break;
        }
    }

#if OSPI_B_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(0U != erase_command);
#endif

    fsp_err_t err = r_ospi_b_write_enable(p_instance_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    spi_flash_direct_transfer_t direct_command = {0};
    direct_command.command        = erase_command;
    direct_command.address        = chip_address;
    direct_command.address_length = (!send_address) ? 0U :
                                    ((SPI_FLASH_ADDRESS_BYTES_3 == p_instance_ctrl->p_cfg->address_bytes) ? 3U : 4U);
    direct_command.command_length = (NULL != p_cmd_set) ? (uint8_t) p_cmd_set->command_bytes : 1U;

    r_ospi_b_direct_transfer(p_instance_ctrl->channel, &direct_command, SPI_FLASH_DIRECT_TRANSFER_DIR_WRITE);

    /* If prefetch is enabled, make sure the banks aren't being used and flush the prefetch caches after an erase. */
#if OSPI_B_CFG_PREFETCH_FUNCTION
    FSP_HARDWARE_REGISTER_WAIT((R_XSPI->COMSTT & OSPI_B_PRV_COMSTT_MEMACCCH_MASK), 0);
    R_XSPI->BMCTL1 = OSPI_B_PRV_BMCTL1_CLEAR_PREFETCH_MASK;
#endif

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Gets the write or erase status of the flash.
 *
 * Implements @ref spi_flash_api_t::statusGet.
 *
 * @retval FSP_SUCCESS                 The write status is in p_status.
 * @retval FSP_ERR_ASSERTION           p_instance_ctrl or p_status is NULL.
 * @retval FSP_ERR_NOT_OPEN            Driver is not opened.
 **********************************************************************************************************************/
fsp_err_t R_OSPI_B_StatusGet (spi_flash_ctrl_t * p_ctrl, spi_flash_status_t * const p_status)
{
    ospi_b_instance_ctrl_t * p_instance_ctrl = (ospi_b_instance_ctrl_t *) p_ctrl;

#if OSPI_B_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_status);
    FSP_ERROR_RETURN(OSPI_B_PRV_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Read device status. */
    p_status->write_in_progress = r_ospi_b_status_sub(p_instance_ctrl, p_instance_ctrl->p_cfg->write_status_bit);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Selects the bank to access. Use ospi_b_bank_select_t as the bank value.
 *
 * Implements @ref spi_flash_api_t::bankSet.
 *
 * @retval FSP_ERR_UNSUPPORTED           This function is unsupported.
 **********************************************************************************************************************/
fsp_err_t R_OSPI_B_BankSet (spi_flash_ctrl_t * p_ctrl, uint32_t bank)
{
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(bank);

    FSP_RETURN(FSP_ERR_UNSUPPORTED);
}

/*******************************************************************************************************************//**
 * Sets the SPI protocol.
 *
 * Implements @ref spi_flash_api_t::spiProtocolSet.
 *
 * @retval FSP_SUCCESS                SPI protocol updated on MPU peripheral.
 * @retval FSP_ERR_ASSERTION          A required pointer is NULL.
 * @retval FSP_ERR_NOT_OPEN           Driver is not opened.
 * @retval FSP_ERR_CALIBRATE_FAILED   Failed to perform auto-calibrate.
 **********************************************************************************************************************/
fsp_err_t R_OSPI_B_SpiProtocolSet (spi_flash_ctrl_t * p_ctrl, spi_flash_protocol_t spi_protocol)
{
    ospi_b_instance_ctrl_t * p_instance_ctrl = (ospi_b_instance_ctrl_t *) p_ctrl;

#if OSPI_B_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(OSPI_B_PRV_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif
    p_instance_ctrl->spi_protocol = spi_protocol;

    /* Update the SPI protocol and its associated registers. */
    return r_ospi_b_protocol_specific_settings(p_instance_ctrl);
}

/*******************************************************************************************************************//**
 * Close the OSPI driver module.
 *
 * Implements @ref spi_flash_api_t::close.
 *
 * @retval FSP_SUCCESS             Configuration was successful.
 * @retval FSP_ERR_ASSERTION       p_instance_ctrl is NULL.
 * @retval FSP_ERR_NOT_OPEN        Driver is not opened.
 **********************************************************************************************************************/
fsp_err_t R_OSPI_B_Close (spi_flash_ctrl_t * p_ctrl)
{
    ospi_b_instance_ctrl_t * p_instance_ctrl = (ospi_b_instance_ctrl_t *) p_ctrl;

#if OSPI_B_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(OSPI_B_PRV_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

#if OSPI_B_CFG_DMAC_SUPPORT_ENABLE

    /* Initialize transfer instance */
    ospi_b_extended_cfg_t     * p_cfg_extend = (ospi_b_extended_cfg_t *) (p_instance_ctrl->p_cfg->p_extend);
    transfer_instance_t const * p_transfer   = p_cfg_extend->p_lower_lvl_transfer;
    p_transfer->p_api->close(p_transfer->p_ctrl);
#endif

    p_instance_ctrl->open         = 0U;
    g_ospi_b_channels_open_flags &= ~(1U << p_instance_ctrl->channel);

    /* Disable clock to the OSPI block if all channels are closed. */
    if (g_ospi_b_channels_open_flags == 0)
    {
        R_BSP_MODULE_STOP(FSP_IP_OSPI, 0U);
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * AutoCalibrate the OSPI_B DS signal.
 *
 * Implements @ref spi_flash_api_t::autoCalibrate.
 *
 * @retval FSP_SUCCESS                 Autocalibration completed successfully.
 * @retval FSP_ERR_ASSERTION           A required pointer is NULL.
 * @retval FSP_ERR_NOT_OPEN            Driver is not opened.
 * @retval FSP_ERR_UNSUPPORTED         Autocalibration support is not enabled.
 * @retval FSP_ERR_CALIBRATE_FAILED    Failed to perform auto-calibrate.
 **********************************************************************************************************************/
fsp_err_t R_OSPI_B_AutoCalibrate (spi_flash_ctrl_t * const p_ctrl)
{
#if OSPI_B_CFG_AUTOCALIBRATION_SUPPORT_ENABLE
    ospi_b_instance_ctrl_t * p_instance_ctrl = (ospi_b_instance_ctrl_t *) p_ctrl;

 #if OSPI_B_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(OSPI_B_PRV_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
 #endif

    /* Perform Automatic Calibration to appropriately update WRAPCFG DSSFTCSn field. */
    if (0 != (OSPI_B_PRV_PROTOCOL_USES_DS_MASK & p_instance_ctrl->spi_protocol))
    {
        return r_ospi_b_automatic_calibration_seq(p_instance_ctrl);
    }

    return FSP_SUCCESS;
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);

    return FSP_ERR_UNSUPPORTED;
#endif
}

/*******************************************************************************************************************//**
 * @} (end addtogroup OSPI)
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Perform initialization based on SPI/OPI protocol
 *
 * @param[in]   p_instance_ctrl    Pointer to OSPI specific control structure
 *
 * @retval      FSP_SUCCESS                Protocol based settings completed successfully.
 * @retval      FSP_ERR_CALIBRATE_FAILED   Auto-Calibration failed.
 **********************************************************************************************************************/
static fsp_err_t r_ospi_b_protocol_specific_settings (ospi_b_instance_ctrl_t * p_instance_ctrl)
{
    spi_flash_cfg_t const       * p_cfg    = p_instance_ctrl->p_cfg;
    ospi_b_extended_cfg_t const * p_extend = (ospi_b_extended_cfg_t const *) p_cfg->p_extend;
    fsp_err_t ret = FSP_SUCCESS;

    /* Get the command set for the configured protocol and save it to the control struct. */
    ospi_b_xspi_command_set_t const * p_cmd_set = r_ospi_b_command_set_get(p_instance_ctrl);
    p_instance_ctrl->p_cmd_set = p_cmd_set;

    /* Update the SPI protocol. */
    R_XSPI->LIOCFGCS_b[p_instance_ctrl->channel].PRTMD = p_instance_ctrl->spi_protocol & R_XSPI_LIOCFGCS_PRTMD_Msk;

    /* Specifies the read/write commands and Read dummy clocks for Device
     * (see Section 37.3.8.5 'Flow of Memory-mapping' of the RA8M1 manual R01UH0994EJ0100). */
    uint32_t cmcfg0 = (OSPI_B_PRV_ADDRESS_REPLACE_ENABLE_BITS) |
                      (((uint32_t) p_cfg->address_bytes << R_XSPI_CMCFGCS_CMCFG0_ADDSIZE_Pos) &
                       R_XSPI_CMCFGCS_CMCFG0_ADDSIZE_Msk);

    /* Use profile 1.0 format always for 8D-8D-8D. */
    if (SPI_FLASH_PROTOCOL_8D_8D_8D == p_instance_ctrl->spi_protocol)
    {
        cmcfg0 |= (1U << R_XSPI_CMCFGCS_CMCFG0_FFMT_Pos);
    }

    R_XSPI->CMCFGCS[p_instance_ctrl->channel].CMCFG0 = cmcfg0;

    /* Grab the appropriate command values. */
    uint16_t read_command  = (NULL != p_cmd_set) ? p_cmd_set->read_command : p_cfg->read_command;
    uint16_t write_command = (NULL != p_cmd_set) ? p_cmd_set->page_program_command : p_cfg->page_program_command;

    /* If no length is specified or if the command byte length is 1, move the command to the upper byte. */
    if ((p_cmd_set == NULL) || (OSPI_B_COMMAND_BYTES_1 == p_cmd_set->command_bytes))
    {
        read_command =
            (uint16_t) ((read_command & OSPI_B_PRV_CDTBUF_CMD_1B_VALUE_MASK) << OSPI_B_PRV_CDTBUF_CMD_1B_VALUE_SHIFT);
        write_command =
            (uint16_t) ((write_command & OSPI_B_PRV_CDTBUF_CMD_1B_VALUE_MASK) << OSPI_B_PRV_CDTBUF_CMD_1B_VALUE_SHIFT);
    }

    const uint8_t read_dummy_cycles = (NULL != p_cmd_set) ?
                                      p_cmd_set->read_dummy_cycles : p_extend->read_dummy_cycles;
    const uint8_t write_dummy_cycles = (NULL != p_cmd_set) ?
                                       p_cmd_set->program_dummy_cycles : p_extend->program_dummy_cycles;

    R_XSPI->CMCFGCS[p_instance_ctrl->channel].CMCFG1 =
        (uint32_t) (((uint32_t) (read_command) << R_XSPI_CMCFGCS_CMCFG1_RDCMD_Pos) |
                    ((uint32_t) (read_dummy_cycles << R_XSPI_CMCFGCS_CMCFG1_RDLATE_Pos) &
                     R_XSPI_CMCFGCS_CMCFG1_RDLATE_Msk));

    R_XSPI->CMCFGCS[p_instance_ctrl->channel].CMCFG2 =
        (uint32_t) (((uint32_t) (write_command) << R_XSPI_CMCFGCS_CMCFG2_WRCMD_Pos) |
                    ((uint32_t) (write_dummy_cycles << R_XSPI_CMCFGCS_CMCFG2_WRLATE_Pos) &
                     R_XSPI_CMCFGCS_CMCFG2_WRLATE_Msk));

#if OSPI_B_CFG_AUTOCALIBRATION_SUPPORT_ENABLE
    ospi_b_extended_cfg_t * p_cfg_extend = (ospi_b_extended_cfg_t *) p_cfg->p_extend;

    /* Perform Automatic Calibration to appropriately update WRAPCFG DSSFTCSn field. */
    if ((0 == p_cfg_extend->data_latch_delay_clocks) &&
        (0 != (OSPI_B_PRV_PROTOCOL_USES_DS_MASK & p_instance_ctrl->spi_protocol)))
    {
        ret = r_ospi_b_automatic_calibration_seq(p_instance_ctrl);
    }
#endif

    return ret;
}

/*******************************************************************************************************************//**
 * Gets device status.
 *
 * @param[in]  p_instance_ctrl         Pointer to a driver handle
 * @param[in]  bit_pos                 Write-in-progress bit position
 *
 * @return True if busy, false if not.
 **********************************************************************************************************************/
static bool r_ospi_b_status_sub (ospi_b_instance_ctrl_t * p_instance_ctrl, uint8_t bit_pos)
{
    spi_flash_cfg_t const           * p_cfg          = p_instance_ctrl->p_cfg;
    spi_flash_direct_transfer_t       direct_command = {0};
    ospi_b_xspi_command_set_t const * p_cmd_set      = p_instance_ctrl->p_cmd_set;

    if (NULL == p_cmd_set)
    {
        direct_command.command        = p_cfg->status_command;
        direct_command.command_length = 1U;
        direct_command.dummy_cycles   = ((ospi_b_extended_cfg_t const *) p_cfg->p_extend)->status_dummy_cycles;
    }
    else
    {
        direct_command.command        = p_cmd_set->status_command;
        direct_command.command_length = (uint8_t) p_cmd_set->command_bytes;
        direct_command.dummy_cycles   = p_cmd_set->status_dummy_cycles;
    }

    /* Skip status check if no command was specified. */
    if (0 == direct_command.command)
    {
        return false;
    }

    /* 8D-8D-8D mode requires an address for any kind of read. */
    if (SPI_FLASH_PROTOCOL_8D_8D_8D == p_instance_ctrl->spi_protocol)
    {
        direct_command.address_length = (p_cfg->address_bytes + 1U) & OSPI_B_PRV_DIRECT_ADDR_AND_DATA_MASK;
    }

    direct_command.data_length = 1U;
    r_ospi_b_direct_transfer(p_instance_ctrl->channel, &direct_command, SPI_FLASH_DIRECT_TRANSFER_DIR_READ);

    return (direct_command.data >> bit_pos) & 1U;
}

/*******************************************************************************************************************//**
 * Send Write enable command to the OctaFlash
 *
 * @param[in]   p_instance_ctrl    Pointer to OSPI specific control structure
 *
 * @retval      FSP_SUCCESS                Write operation completed.
 * @retval      FSP_ERR_WRITE_FAILED       Write operation failed.
 **********************************************************************************************************************/
static fsp_err_t r_ospi_b_write_enable (ospi_b_instance_ctrl_t * p_instance_ctrl)
{
    spi_flash_direct_transfer_t       direct_command = {0};
    spi_flash_cfg_t const           * p_cfg          = p_instance_ctrl->p_cfg;
    ospi_b_xspi_command_set_t const * p_cmd_set      = p_instance_ctrl->p_cmd_set;

    if (NULL == p_cmd_set)
    {
        direct_command.command        = p_cfg->write_enable_command;
        direct_command.command_length = 1U;
    }
    else
    {
        direct_command.command        = p_cmd_set->write_enable_command;
        direct_command.command_length = (uint8_t) p_cmd_set->command_bytes;
    }

    /* If the command is 0x00, then skip sending the write enable. */
    if (0 == direct_command.command)
    {
        return FSP_SUCCESS;
    }

    r_ospi_b_direct_transfer(p_instance_ctrl->channel, &direct_command, SPI_FLASH_DIRECT_TRANSFER_DIR_WRITE);

    /* In case write enable is not checked, assume write is enabled. */
    bool write_enabled = true;

#if OSPI_B_MAX_WRITE_ENABLE_LOOPS > 0U

    /* Verify write is enabled. */
    for (uint32_t i = 0U; i < OSPI_B_MAX_WRITE_ENABLE_LOOPS; i++)
    {
        write_enabled = r_ospi_b_status_sub(p_instance_ctrl, p_instance_ctrl->p_cfg->write_enable_bit);
        if (write_enabled)
        {
            break;
        }
    }
#endif

    FSP_ERROR_RETURN(write_enabled, FSP_ERR_WRITE_FAILED);

    return FSP_SUCCESS;
}

#if OSPI_B_CFG_AUTOCALIBRATION_SUPPORT_ENABLE

/*******************************************************************************************************************//**
 * Perform Automatic Calibration
 *
 * @param[in]   p_instance_ctrl    Pointer to OSPI specific control structure
 *
 * @retval      FSP_SUCCESS                Auto-Calibration completed successfully.
 * @retval      FSP_ERR_CALIBRATE_FAILED   Auto-Calibration failed.
 **********************************************************************************************************************/
static fsp_err_t r_ospi_b_automatic_calibration_seq (ospi_b_instance_ctrl_t * p_instance_ctrl)
{
    fsp_err_t               ret          = FSP_SUCCESS;
    spi_flash_cfg_t       * p_cfg        = (spi_flash_cfg_t *) p_instance_ctrl->p_cfg;
    ospi_b_extended_cfg_t * p_cfg_extend = (ospi_b_extended_cfg_t *) p_cfg->p_extend;

    ospi_b_xspi_command_set_t const * p_cmd_set = p_instance_ctrl->p_cmd_set;

    ospi_b_device_number_t channel = p_instance_ctrl->channel;

    /* Check that calibration is not in progress. */
    if (0 != R_XSPI->CCCTLCS[channel].CCCTL0_b.CAEN)
    {
        ret = FSP_ERR_CALIBRATE_FAILED;
    }
    else
    {
        const uint8_t command_bytes     = (NULL != p_cmd_set) ? (uint8_t) p_cmd_set->command_bytes : 1U;
        uint16_t      read_command      = (NULL != p_cmd_set) ? p_cmd_set->read_command : p_cfg->read_command;
        const uint8_t read_dummy_cycles = (NULL != p_cmd_set) ? p_cmd_set->read_dummy_cycles : 0U;
        const uint8_t address_bytes     = (p_cfg->address_bytes == SPI_FLASH_ADDRESS_BYTES_3) ? 3U : 4U;

        /* If using 1 command byte, shift the read command over as the peripheral expects. */
        if (1U == command_bytes)
        {
            read_command =
                (uint16_t) ((read_command & OSPI_B_PRV_CDTBUF_CMD_1B_VALUE_MASK) <<
                            OSPI_B_PRV_CDTBUF_CMD_1B_VALUE_SHIFT);
        }

        R_XSPI->CCCTLCS[channel].CCCTL1 =
            (((uint32_t) command_bytes << R_XSPI_CCCTLCS_CCCTL1_CACMDSIZE_Pos) &
             R_XSPI_CCCTLCS_CCCTL1_CACMDSIZE_Msk) |
            (((uint32_t) address_bytes << R_XSPI_CCCTLCS_CCCTL1_CAADDSIZE_Pos) & R_XSPI_CCCTLCS_CCCTL1_CAADDSIZE_Msk) |
            (OSPI_B_PRV_AUTOCALIBRATION_DATA_SIZE << R_XSPI_CCCTLCS_CCCTL1_CADATASIZE_Pos) |
            (OSPI_B_PRV_AUTOCALIBRATION_LATENCY_CYCLES << R_XSPI_CCCTLCS_CCCTL1_CAWRLATE_Pos) |
            (((uint32_t) read_dummy_cycles << R_XSPI_CCCTLCS_CCCTL1_CARDLATE_Pos) &
             R_XSPI_CCCTLCS_CCCTL1_CARDLATE_Msk);

        R_XSPI->CCCTLCS[channel].CCCTL2 =
            (((uint32_t) read_command << R_XSPI_CCCTLCS_CCCTL2_CARDCMD_Pos) &
             R_XSPI_CCCTLCS_CCCTL2_CARDCMD_Msk);

        R_XSPI->CCCTLCS[channel].CCCTL3 = (uint32_t) p_cfg_extend->p_autocalibration_preamble_pattern_addr &
                                          OSPI_B_PRV_ADDRESS_REPLACE_MASK;
        R_XSPI->CCCTLCS[channel].CCCTL4 = OSPI_B_PRV_AUTOCALIBRATION_PREAMBLE_PATTERN_0;
        R_XSPI->CCCTLCS[channel].CCCTL5 = OSPI_B_PRV_AUTOCALIBRATION_PREAMBLE_PATTERN_1;
        R_XSPI->CCCTLCS[channel].CCCTL6 = OSPI_B_PRV_AUTOCALIBRATION_PREAMBLE_PATTERN_2;
        R_XSPI->CCCTLCS[channel].CCCTL7 = OSPI_B_PRV_AUTOCALIBRATION_PREAMBLE_PATTERN_3;

        R_XSPI->CCCTLCS[channel].CCCTL0 =
            (OSPI_B_PRV_AUTOCALIBRATION_NO_WRITE_CMD << R_XSPI_CCCTLCS_CCCTL0_CANOWR_Pos) |
            (OSPI_B_PRV_AUTOCALIBRATION_FRAME_INTERVAL <<
                R_XSPI_CCCTLCS_CCCTL0_CAITV_Pos) |
            (OSPI_B_PRV_AUTOCALIBRATION_SHIFT_DS_END_VALUE <<
                R_XSPI_CCCTLCS_CCCTL0_CASFTEND_Pos);

        /* Automatic Calibration Enable */
        R_XSPI->CCCTLCS[channel].CCCTL0_b.CAEN = 1;

        /* Check calibration success or failure. */
        while ((0 == ((R_XSPI->INTS >> (R_XSPI_INTS_CASUCCS_Pos + channel)) & 0x01)) &&
               (0 == ((R_XSPI->INTS >> (R_XSPI_INTS_CAFAILCS_Pos + channel)) & 0x01)))
        {
            /* Do nothing. */
        }

        /* Disable automatic calibration */
        R_XSPI->CCCTLCS[channel].CCCTL0_b.CAEN = 0;

        if (1 == ((R_XSPI->INTS >> (R_XSPI_INTS_CASUCCS_Pos + channel)) & 0x01))
        {
            /* Clear automatic calibration success status */
            R_XSPI->INTC = (uint32_t) 1 << (R_XSPI_INTS_CASUCCS_Pos + channel);
        }
        else if (1 == ((R_XSPI->INTS >> (R_XSPI_INTS_CAFAILCS_Pos + channel)) & 0x01))
        {
            ret = FSP_ERR_CALIBRATE_FAILED;

            /* Clear automatic calibration failure status */
            R_XSPI->INTC = (uint32_t) 1 << (R_XSPI_INTS_CAFAILCS_Pos + channel);
        }
        else
        {
            /* Do nothing. */
        }
    }

    return ret;
}

#endif

/*******************************************************************************************************************//**
 * Performs direct data transfer with the OctaFlash
 *
 * @param[in]   channel            Device number to send the direct transfer to
 * @param[in]   p_transfer         Pointer to transfer parameters
 * @param[in]   direction          Read/Write
 **********************************************************************************************************************/
static void r_ospi_b_direct_transfer (ospi_b_device_number_t              channel,
                                      spi_flash_direct_transfer_t * const p_transfer,
                                      spi_flash_direct_transfer_dir_t     direction)
{
    /* Setup the manual command control. Cancel any ongoing transactions, direct mode, set channel, 1 transaction. */
    R_XSPI->CDCTL0 = ((((uint32_t) channel) << R_XSPI_CDCTL0_CSSEL_Pos) & R_XSPI_CDCTL0_CSSEL_Msk);

    /* Direct Read/Write settings
     * (see RA8M1 User's Manual section "Flow of Manual-command Procedure"). */
    FSP_HARDWARE_REGISTER_WAIT(R_XSPI->CDCTL0_b.TRREQ, 0);

    uint32_t cdtbuf0 =
        (((uint32_t) p_transfer->command_length << R_XSPI_CDBUF_CDT_CMDSIZE_Pos) & R_XSPI_CDBUF_CDT_CMDSIZE_Msk) |
        (((uint32_t) p_transfer->address_length << R_XSPI_CDBUF_CDT_ADDSIZE_Pos) & R_XSPI_CDBUF_CDT_ADDSIZE_Msk) |
        (((uint32_t) p_transfer->data_length << R_XSPI_CDBUF_CDT_DATASIZE_Pos) & R_XSPI_CDBUF_CDT_DATASIZE_Msk) |
        (((uint32_t) p_transfer->dummy_cycles << R_XSPI_CDBUF_CDT_LATE_Pos) & R_XSPI_CDBUF_CDT_LATE_Msk) |
        (((uint32_t) direction << R_XSPI_CDBUF_CDT_TRTYPE_Pos) & R_XSPI_CDBUF_CDT_TRTYPE_Msk);

    cdtbuf0 |= (1 == p_transfer->command_length) ?
               ((p_transfer->command & OSPI_B_PRV_CDTBUF_CMD_1B_VALUE_MASK) << OSPI_B_PRV_CDTBUF_CMD_UPPER_OFFSET) :
               ((p_transfer->command & OSPI_B_PRV_CDTBUF_CMD_2B_VALUE_MASK) << OSPI_B_PRV_CDTBUF_CMD_OFFSET);

    R_XSPI->CDBUF[0].CDT = cdtbuf0;

    R_XSPI->CDBUF[0].CDA = p_transfer->address;

    if (SPI_FLASH_DIRECT_TRANSFER_DIR_WRITE == direction)
    {
        R_XSPI->CDBUF[0].CDD0 = (uint32_t) (p_transfer->data_u64 & UINT32_MAX);
        if (p_transfer->data_length > sizeof(uint32_t))
        {
            R_XSPI->CDBUF[0].CDD1 = (uint32_t) (p_transfer->data_u64 >> OSPI_B_PRV_UINT32_BITS);
        }
    }

    R_XSPI->CDCTL0_b.TRREQ = 1;
    FSP_HARDWARE_REGISTER_WAIT(R_XSPI->INTS_b.CMDCMP, 1);

    if (SPI_FLASH_DIRECT_TRANSFER_DIR_READ == direction)
    {
        p_transfer->data_u64 = R_XSPI->CDBUF[0].CDD0;
        if (p_transfer->data_length > sizeof(uint32_t))
        {
            p_transfer->data_u64 |= (((uint64_t) R_XSPI->CDBUF[0].CDD1) << OSPI_B_PRV_UINT32_BITS);
        }
    }

    R_XSPI->INTC = 1 << R_XSPI_INTC_CMDCMPC_Pos;
}

#if OSPI_B_CFG_XIP_SUPPORT_ENABLE

/*******************************************************************************************************************//**
 * Configures the device to enter or exit XiP mode.
 *
 * @param[in]   p_instance_ctrl    Pointer to the instance ctrl struct.
 * @param[in]   is_entering        true if entering XiP mode, false if exiting.
 **********************************************************************************************************************/
static void r_ospi_b_xip (ospi_b_instance_ctrl_t * p_instance_ctrl, bool is_entering)
{
    const spi_flash_cfg_t * p_cfg                = p_instance_ctrl->p_cfg;
    volatile uint8_t      * p_dummy_read_address = (volatile uint8_t *)
                                                   ((OSPI_B_DEVICE_NUMBER_0 == p_instance_ctrl->channel) ?
                                                    BSP_FEATURE_OSPI_B_DEVICE_0_START_ADDRESS :
                                                    BSP_FEATURE_OSPI_B_DEVICE_1_START_ADDRESS);
    volatile uint8_t dummy_read = 0;

    FSP_PARAMETER_NOT_USED(dummy_read); // Suppress variable not used error.

    /* Clear the pre-fetch buffer for this bank so the next read is guaranteed to use the XiP code. */
 #if OSPI_B_CFG_PREFETCH_FUNCTION
    R_XSPI->BMCTL1 |= 0x03U << R_XSPI_BMCTL1_PBUFCLRCH_Pos;
 #endif

    /* Wait for any on-going access to complete. */
    FSP_HARDWARE_REGISTER_WAIT((R_XSPI->COMSTT & OSPI_B_PRV_COMSTT_MEMACCCH_MASK), 0);

    if (is_entering)
    {
        /* Change memory-mapping to read-only mode. */
        R_XSPI->BMCTL0 = OSPI_B_PRV_BMCTL0_READ_ONLY_VALUE;

        /* Configure XiP codes and enable. */
        const uint32_t cmctlch = R_XSPI_CMCTLCH_XIPEN_Msk |
                                 ((uint32_t) (p_cfg->xip_enter_command << R_XSPI_CMCTLCH_XIPENCODE_Pos)) |
                                 ((uint32_t) (p_cfg->xip_exit_command << R_XSPI_CMCTLCH_XIPEXCODE_Pos));

        /* XiP enter/exit codes are configured only for memory mapped operations and affects both OSPI slave channels. */
        R_XSPI->CMCTLCH[0] = cmctlch;
        R_XSPI->CMCTLCH[1] = cmctlch;

        /* Perform a read to send the enter code. All further reads will use the enter code and will not send a read command code. */
        dummy_read = *p_dummy_read_address;

        /* Wait for the read to complete. */
        FSP_HARDWARE_REGISTER_WAIT((R_XSPI->COMSTT & OSPI_B_PRV_COMSTT_MEMACCCH_MASK), 0);
    }
    else
    {
        /* Disable XiP. */
        R_XSPI->CMCTLCH[0] &= ~R_XSPI_CMCTLCH_XIPEN_Msk;
        R_XSPI->CMCTLCH[1] &= ~R_XSPI_CMCTLCH_XIPEN_Msk;

        /* Perform a read to send the exit code. All further reads will not send an exit code. */
        dummy_read = *p_dummy_read_address;

        /* Wait for the read to complete. */
        FSP_HARDWARE_REGISTER_WAIT((R_XSPI->COMSTT & OSPI_B_PRV_COMSTT_MEMACCCH_MASK), 0);

        /* Change memory-mapping back to R/W mode. */
        R_XSPI->BMCTL0 = OSPI_B_PRV_BMCTL0_READ_WRITE_VALUE;
    }
}

#endif

/*******************************************************************************************************************//**
 * Gets the xspi command set for a protocol mode if it exists.
 *
 * @param[in]   p_instance_ctrl    Pointer to the instance ctrl struct.
 * @return Pointer to the command set, or NULL if it is normal SPI or has not been configured.
 **********************************************************************************************************************/
static ospi_b_xspi_command_set_t const * r_ospi_b_command_set_get (ospi_b_instance_ctrl_t * p_instance_ctrl)
{
    ospi_b_extended_cfg_t * p_cfg_extend = (ospi_b_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;

    if ((SPI_FLASH_PROTOCOL_EXTENDED_SPI == p_instance_ctrl->spi_protocol) ||
        (0 == p_cfg_extend->xspi_command_set_list_length))
    {

        /* Normal SPI and modes not defined fallback to the commands defined in the spi_flash_cfg_t struct. */
        return NULL;
    }

    for (uint32_t i = 0; i < p_cfg_extend->xspi_command_set_list_length; i++)
    {
        if (p_cfg_extend->p_xspi_command_set_list[i].protocol == p_instance_ctrl->spi_protocol)
        {
            return &p_cfg_extend->p_xspi_command_set_list[i];
        }
    }

    /* If the protocol isn't found, return NULL. */
    return NULL;
}

#if OSPI_B_CFG_DOTF_SUPPORT_ENABLE

/*******************************************************************************************************************//**
 * Configures the device for DOTF operation.
 *
 * @param[in]   p_dotf_cfg    Pointer to the instance ctrl struct.
 * @retval      FSP_SUCCESS                       DOTF configuration completed successfully.
 * @retval      FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL   Key initialization failed.
 * @retval      FSP_ERR_CRYPTO_SCE_FAIL           Key wrapping failed.
 * @retval      FSP_ERR_INVALID_ARGUMENT          Invalid key type argument.
 **********************************************************************************************************************/
static fsp_err_t r_ospi_b_dotf_setup (ospi_b_dotf_cfg_t * p_dotf_cfg)
{
    fsp_err_t     sce_ret = FSP_SUCCESS;
    uint32_t      seed[2] = {0};
    uint32_t      wrapped_key[HW_SCE_AES256_KEY_INDEX_WORD_SIZE] = {0};
    sce_oem_cmd_t key_cmd = SCE_OEM_CMD_AES128;

    if (OSPI_B_DOTF_AES_KEY_TYPE_128 == p_dotf_cfg->key_type)
    {
        key_cmd = SCE_OEM_CMD_AES128;
    }
    else if (OSPI_B_DOTF_AES_KEY_TYPE_192 == p_dotf_cfg->key_type)
    {
        key_cmd = SCE_OEM_CMD_AES192;
    }
    else if (OSPI_B_DOTF_AES_KEY_TYPE_256 == p_dotf_cfg->key_type)
    {
        key_cmd = SCE_OEM_CMD_AES256;
    }
    else
    {
        return FSP_ERR_INVALID_ARGUMENT;
    }

    /* Initialize the crypto engine. */
    HW_SCE_McuSpecificInit();

    /* Copnvert plaintext key to wrapped form. */
    sce_ret =
        HW_SCE_GenerateOemKeyIndexPrivate(SCE_OEM_KEY_TYPE_PLAIN,
                                          key_cmd,
                                          NULL,
                                          NULL,
                                          (uint8_t *) p_dotf_cfg->p_key,
                                          (uint32_t *) wrapped_key);
    if (FSP_SUCCESS != sce_ret)
    {
        return sce_ret;
    }

    /* Use wrapped key with DOTF AES Engine. */
    if (SCE_OEM_CMD_AES128 == key_cmd)
    {
        sce_ret = HW_SCE_Aes128OutputKeyForDotfSub(wrapped_key, seed);
    }
    else if (SCE_OEM_CMD_AES192 == key_cmd)
    {
        sce_ret = HW_SCE_Aes192OutputKeyForDotfSub(wrapped_key, seed);
    }
    else
    {
        sce_ret = HW_SCE_Aes256OutputKeyForDotfSub(wrapped_key, seed);
    }

    if (sce_ret == FSP_SUCCESS)
    {
        /* Disable byte order conversion. */
        R_DOTF->REG00 = (OSPI_B_PRV_DOTF_REG00_RESET_VALUE | R_DOTF_REG00_B09_Msk);

        /* Load the IV. */
        R_DOTF->REG03 = p_dotf_cfg->p_iv[0];
        R_DOTF->REG03 = p_dotf_cfg->p_iv[1];
        R_DOTF->REG03 = p_dotf_cfg->p_iv[2];
        R_DOTF->REG03 = p_dotf_cfg->p_iv[3];
    }

    /* Set the start and end area for DOTF conversion. */
    R_DOTF->CONVAREAST = (uint32_t) p_dotf_cfg->p_start_addr;
    R_DOTF->CONVAREAD  = (uint32_t) p_dotf_cfg->p_end_addr;

    return sce_ret;
}

#endif
