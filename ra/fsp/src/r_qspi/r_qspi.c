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

#include "bsp_api.h"

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_qspi.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define QSPI_PRV_OPEN                         (0x51535049)

#define QSPI_PRV_MASK_UPPER_4_BITS_OF_BYTE    (0xF0U)
#define QSPI_PRV_MASK_LOWER_4_BITS_OF_BYTE    (0x0FU)

#define QSPI_PRV_LSB_NIBBLE_CLEARED           (0xEEEEEEEE)
#define QSPI_PRV_EVEN_BITS_CLEARED            (0xAAAA)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/* Number of address bytes in 4 byte address mode. */
#define QSPI_4_BYTE_ADDRESS                   (4U)

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
#if QSPI_CFG_SUPPORT_EXTENDED_SPI_MULTI_LINE_PROGRAM

static void qspi_d0_byte_write_quad_mode(uint8_t byte);

static void qspi_d0_byte_write_dual_mode(uint8_t byte);

#endif

static void qspi_d0_byte_write_standard(uint8_t byte);

static void r_qspi_direct_write_sub(uint8_t const * const p_src, uint32_t const bytes, bool const read_after_write);

static void r_qspi_direct_read_sub(uint8_t * const p_dest, uint32_t const bytes);
static bool r_qspi_status_sub(qspi_instance_ctrl_t * p_instance_ctrl);

static fsp_err_t r_qspi_xip(qspi_instance_ctrl_t * p_instance_ctrl, uint8_t code, bool enter_mode);

#if QSPI_CFG_PARAM_CHECKING_ENABLE

static fsp_err_t r_qspi_param_checking_dcom(qspi_instance_ctrl_t * p_instance_ctrl);

static fsp_err_t qspi_program_param_check(qspi_instance_ctrl_t * p_instance_ctrl,
                                          uint8_t const * const  p_src,
                                          uint8_t * const        p_dest,
                                          uint32_t               byte_count);

#endif

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

#if QSPI_CFG_SUPPORT_EXTENDED_SPI_MULTI_LINE_PROGRAM

/* Page program command.  Index by [data_lines].  data_lines is 0 for 1 data line, 1 for 2 data lines, or
 * 2 for 4 data lines. */
static void(*const gp_qspi_prv_byte_write[3]) (uint8_t byte) =
{
    qspi_d0_byte_write_standard,
    qspi_d0_byte_write_dual_mode,
    qspi_d0_byte_write_quad_mode
};
#endif

/*******************************************************************************************************************//**
 * @addtogroup QSPI
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Global Variables
 **********************************************************************************************************************/

const spi_flash_api_t g_qspi_on_spi_flash =
{
    .open           = R_QSPI_Open,
    .directWrite    = R_QSPI_DirectWrite,
    .directRead     = R_QSPI_DirectRead,
    .directTransfer = R_QSPI_DirectTransfer,
    .spiProtocolSet = R_QSPI_SpiProtocolSet,
    .write          = R_QSPI_Write,
    .erase          = R_QSPI_Erase,
    .statusGet      = R_QSPI_StatusGet,
    .xipEnter       = R_QSPI_XipEnter,
    .xipExit        = R_QSPI_XipExit,
    .bankSet        = R_QSPI_BankSet,
    .autoCalibrate  = R_QSPI_AutoCalibrate,
    .close          = R_QSPI_Close,
};

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Open the QSPI driver module. After the driver is open, the QSPI can be accessed like internal flash memory starting
 * at address 0x60000000.
 *
 * Implements @ref spi_flash_api_t::open.
 *
 * @retval FSP_SUCCESS             Configuration was successful.
 * @retval FSP_ERR_ASSERTION       The parameter p_instance_ctrl or p_cfg is NULL.
 * @retval FSP_ERR_ALREADY_OPEN    Driver has already been opened with the same p_instance_ctrl.
 **********************************************************************************************************************/
fsp_err_t R_QSPI_Open (spi_flash_ctrl_t * p_ctrl, spi_flash_cfg_t const * const p_cfg)
{
    qspi_instance_ctrl_t * p_instance_ctrl = (qspi_instance_ctrl_t *) p_ctrl;

#if QSPI_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_cfg);
    FSP_ERROR_RETURN(QSPI_PRV_OPEN != p_instance_ctrl->open, FSP_ERR_ALREADY_OPEN);
#endif

    /* Enable clock to the QSPI block */
    R_BSP_MODULE_START(FSP_IP_QSPI, 0U);

    qspi_extended_cfg_t * p_cfg_extend = (qspi_extended_cfg_t *) p_cfg->p_extend;

    /* Initialized unused registers. */
    R_QSPI->SFMCST  = 0U;
    R_QSPI->SFMSIC  = 0U;
    R_QSPI->SFMPMD  = 0U;
    R_QSPI->SFMCNT1 = 0U;

    /* Set the initial SPI protocol. */
    R_QSPI->SFMSPC = R_QSPI_SFMSPC_SFMSDE_Msk | p_cfg->spi_protocol;

    /* Set the SPI clock rate */
    R_QSPI->SFMSKC = p_cfg_extend->qspclk_div;

    /* Set the address mode. */
    R_QSPI->SFMSAC = p_cfg->address_bytes;

    /* Set the number of dummy cycles in QSPI peripheral */
    R_QSPI->SFMSDC = p_cfg->dummy_clocks | R_QSPI_SFMSDC_SFMXD_Msk;

    /* Set configured minimum high level width for QSSL signal. */
    R_QSPI->SFMSSC = p_cfg_extend->min_qssl_deselect_cycles | R_QSPI_SFMSSC_SFMSLD_Msk | R_QSPI_SFMSSC_SFMSHD_Msk;

    /* Set the read mode based on user configuration. */
    R_QSPI->SFMSMD = R_QSPI_SFMSMD_SFMPFE_Msk | p_cfg->read_mode;

    /* Initialize control block. */
    p_instance_ctrl->p_cfg = p_cfg;

    /* This is the index into g_qspi_prv_program_command.  The index should be 0 for data on one line, 1 for data on
     * 2 lines, and 2 for data on 4 lines. */
    if (SPI_FLASH_READ_MODE_STANDARD == p_cfg->read_mode)
    {
        p_instance_ctrl->data_lines = SPI_FLASH_DATA_LINES_1;
    }
    else
    {
        p_instance_ctrl->data_lines = (spi_flash_data_lines_t) (31 - __CLZ(p_cfg->read_mode));
    }

    /* The memory size is read from the device if needed. */
    p_instance_ctrl->total_size_bytes = 0U;

    p_instance_ctrl->open = QSPI_PRV_OPEN;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Writes raw data directly to the QSPI.
 *
 * Implements @ref spi_flash_api_t::directWrite.
 *
 * @retval FSP_SUCCESS                 The flash was programmed successfully.
 * @retval FSP_ERR_ASSERTION           A required pointer is NULL.
 * @retval FSP_ERR_NOT_OPEN            Driver is not opened.
 * @retval FSP_ERR_INVALID_MODE        This function can't be called when XIP mode is enabled.
 * @retval FSP_ERR_DEVICE_BUSY         The device is busy.
 **********************************************************************************************************************/
fsp_err_t R_QSPI_DirectWrite (spi_flash_ctrl_t    * p_ctrl,
                              uint8_t const * const p_src,
                              uint32_t const        bytes,
                              bool const            read_after_write)
{
    qspi_instance_ctrl_t * p_instance_ctrl = (qspi_instance_ctrl_t *) p_ctrl;

#if QSPI_CFG_PARAM_CHECKING_ENABLE
    fsp_err_t err = r_qspi_param_checking_dcom(p_instance_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    FSP_ASSERT(NULL != p_src);
    FSP_ASSERT(bytes > 0);
#else
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
#endif

    /* Write data to QSPI. */
    r_qspi_direct_write_sub(p_src, bytes, read_after_write);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Reads raw data directly from the QSPI. This API can only be called after R_QSPI_DirectWrite with read_after_write
 * set to true.
 *
 * Implements @ref spi_flash_api_t::directRead.
 *
 * @retval FSP_SUCCESS                 The flash was programmed successfully.
 * @retval FSP_ERR_ASSERTION           A required pointer is NULL.
 * @retval FSP_ERR_NOT_OPEN            Driver is not opened.
 * @retval FSP_ERR_INVALID_MODE        This function must be called after R_QSPI_DirectWrite with read_after_write set
 *                                     to true.
 **********************************************************************************************************************/
fsp_err_t R_QSPI_DirectRead (spi_flash_ctrl_t * p_ctrl, uint8_t * const p_dest, uint32_t const bytes)
{
    qspi_instance_ctrl_t * p_instance_ctrl = (qspi_instance_ctrl_t *) p_ctrl;

#if QSPI_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);

    FSP_ASSERT(NULL != p_dest);
    FSP_ASSERT(bytes > 0);
    FSP_ERROR_RETURN(QSPI_PRV_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);

    /* This API can only be called after R_QSPI_DirectWrite with the read_after_write parameter set to true. The QSPI
     * peripheral must already be in direct communications mode. */
    FSP_ERROR_RETURN(1U == R_QSPI->SFMCMD, FSP_ERR_INVALID_MODE);
#else
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
#endif

    /* Read data from QSPI. */
    r_qspi_direct_read_sub(p_dest, bytes);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Read/Write raw data directly with the OctaFlash/OctaRAM device. Unsupported by QSPI.
 *
 * Implements @ref spi_flash_api_t::directTransfer.
 *
 * @retval FSP_ERR_UNSUPPORTED         API not supported by QSPI.
 **********************************************************************************************************************/
fsp_err_t R_QSPI_DirectTransfer (spi_flash_ctrl_t                  * p_ctrl,
                                 spi_flash_direct_transfer_t * const p_transfer,
                                 spi_flash_direct_transfer_dir_t     direction)
{
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(p_transfer);
    FSP_PARAMETER_NOT_USED(direction);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * Enters XIP (execute in place) mode.
 *
 * Implements @ref spi_flash_api_t::xipEnter.
 *
 * @retval FSP_SUCCESS                 The flash was programmed successfully.
 * @retval FSP_ERR_ASSERTION           A required pointer is NULL.
 * @retval FSP_ERR_NOT_OPEN            Driver is not opened.
 **********************************************************************************************************************/
fsp_err_t R_QSPI_XipEnter (spi_flash_ctrl_t * p_ctrl)
{
    qspi_instance_ctrl_t * p_instance_ctrl = (qspi_instance_ctrl_t *) p_ctrl;
    fsp_err_t              err;
    err = r_qspi_xip(p_instance_ctrl, p_instance_ctrl->p_cfg->xip_enter_command, true);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Exits XIP (execute in place) mode.
 *
 * Implements @ref spi_flash_api_t::xipExit.
 *
 * @retval FSP_SUCCESS                 The flash was programmed successfully.
 * @retval FSP_ERR_ASSERTION           A required pointer is NULL.
 * @retval FSP_ERR_NOT_OPEN            Driver is not opened.
 **********************************************************************************************************************/
fsp_err_t R_QSPI_XipExit (spi_flash_ctrl_t * p_ctrl)
{
    qspi_instance_ctrl_t * p_instance_ctrl = (qspi_instance_ctrl_t *) p_ctrl;
    fsp_err_t              err;
    err = r_qspi_xip(p_instance_ctrl, p_instance_ctrl->p_cfg->xip_exit_command, false);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Program a page of data to the flash.
 *
 * Implements @ref spi_flash_api_t::write.
 *
 * @retval FSP_SUCCESS                 The flash was programmed successfully.
 * @retval FSP_ERR_ASSERTION           p_instance_ctrl, p_dest or p_src is NULL, or byte_count crosses a page boundary.
 * @retval FSP_ERR_NOT_OPEN            Driver is not opened.
 * @retval FSP_ERR_INVALID_MODE        This function can't be called when XIP mode is enabled.
 * @retval FSP_ERR_DEVICE_BUSY         The device is busy.
 **********************************************************************************************************************/
fsp_err_t R_QSPI_Write (spi_flash_ctrl_t    * p_ctrl,
                        uint8_t const * const p_src,
                        uint8_t * const       p_dest,
                        uint32_t              byte_count)
{
    qspi_instance_ctrl_t * p_instance_ctrl = (qspi_instance_ctrl_t *) p_ctrl;

#if QSPI_CFG_PARAM_CHECKING_ENABLE
    fsp_err_t err = qspi_program_param_check(p_instance_ctrl, p_src, p_dest, byte_count);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#endif

    uint32_t chip_address = (uint32_t) p_dest - (uint32_t) QSPI_DEVICE_START_ADDRESS + R_QSPI->SFMCNT1;

    bool restore_spi_mode = false;
    void (* write_command)(uint8_t byte) = qspi_d0_byte_write_standard;
    void (* write_address)(uint8_t byte) = qspi_d0_byte_write_standard;

#if QSPI_CFG_SUPPORT_EXTENDED_SPI_MULTI_LINE_PROGRAM

    /* If the peripheral is in extended SPI mode, and the configuration provided in the BSP allows for programming on
     * multiple data lines, and a unique command is provided for the required mode, update the SPI protocol to send
     * data on multiple lines. */
    if ((SPI_FLASH_DATA_LINES_1 != p_instance_ctrl->data_lines) &&
        (SPI_FLASH_PROTOCOL_EXTENDED_SPI == R_QSPI->SFMSPC_b.SFMSPI))
    {
        R_QSPI->SFMSPC_b.SFMSPI = p_instance_ctrl->data_lines;

        restore_spi_mode = true;

        /* Write command in extended SPI mode on one line. */
        write_command = gp_qspi_prv_byte_write[p_instance_ctrl->data_lines];

        if (SPI_FLASH_DATA_LINES_1 == p_instance_ctrl->p_cfg->page_program_address_lines)
        {
            /* Write address in extended SPI mode on one line. */
            write_address = gp_qspi_prv_byte_write[p_instance_ctrl->data_lines];
        }
    }
#endif

    /* Enter Direct Communication mode */
    R_QSPI->SFMCMD = 1;

    /* Send command to enable writing */
    write_command(p_instance_ctrl->p_cfg->write_enable_command);

    /* Close the SPI bus cycle. Reference section 39.10.3 "Generating the SPI Bus Cycle during Direct Communication"
     * in the RA6M3 manual R01UH0886EJ0100. */
    R_QSPI->SFMCMD = 1;

    /* Send command to write data */
    write_command(p_instance_ctrl->p_cfg->page_program_command);

    /* Write the address. */
    if ((p_instance_ctrl->p_cfg->address_bytes & R_QSPI_SFMSAC_SFMAS_Msk) == SPI_FLASH_ADDRESS_BYTES_4)
    {
        /* Send the most significant byte of the address */
        write_address((uint8_t) (chip_address >> 24));
    }

    /* Send the remaining bytes of the address */
    write_address((uint8_t) (chip_address >> 16));
    write_address((uint8_t) (chip_address >> 8));
    write_address((uint8_t) (chip_address));

    /* Write the data. */
    uint32_t index = 0;
    while (index < byte_count)
    {
        /* Read the device memory into the passed in buffer */
        R_QSPI->SFMCOM = p_src[index];
        index++;
    }

    /* Close the SPI bus cycle. Reference section 39.10.3 "Generating the SPI Bus Cycle during Direct Communication"
     * in the RA6M3 manual R01UH0886EJ0100. */
    R_QSPI->SFMCMD = 1;

    /* If the SPI protocol was modified in this function, restore it. */
    if (restore_spi_mode)
    {
        /* Restore SPI mode to extended SPI mode. */
        R_QSPI->SFMSPC_b.SFMSPI = SPI_FLASH_PROTOCOL_EXTENDED_SPI;
    }

    /* Return to ROM access mode */
    R_QSPI->SFMCMD = 0;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Erase a block or sector of flash.  The byte_count must exactly match one of the erase sizes defined in spi_flash_cfg_t.
 * For chip erase, byte_count must be SPI_FLASH_ERASE_SIZE_CHIP_ERASE.
 *
 * Implements @ref spi_flash_api_t::erase.
 *
 * @retval FSP_SUCCESS                 The command to erase the flash was executed successfully.
 * @retval FSP_ERR_ASSERTION           p_instance_ctrl or p_device_address is NULL, or byte_count doesn't match an erase
 *                                     size defined in spi_flash_cfg_t, or device is in XIP mode.
 * @retval FSP_ERR_NOT_OPEN            Driver is not opened.
 * @retval FSP_ERR_INVALID_MODE        This function can't be called when XIP mode is enabled.
 * @retval FSP_ERR_DEVICE_BUSY         The device is busy.
 **********************************************************************************************************************/
fsp_err_t R_QSPI_Erase (spi_flash_ctrl_t * p_ctrl, uint8_t * const p_device_address, uint32_t byte_count)
{
    qspi_instance_ctrl_t * p_instance_ctrl = (qspi_instance_ctrl_t *) p_ctrl;

#if QSPI_CFG_PARAM_CHECKING_ENABLE
    fsp_err_t err = r_qspi_param_checking_dcom(p_instance_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    FSP_ASSERT(NULL != p_device_address);
#endif

    uint16_t erase_command = 0;
    uint32_t chip_address  = (uint32_t) p_device_address - QSPI_DEVICE_START_ADDRESS + R_QSPI->SFMCNT1;
    bool     send_address  = true;

    for (uint32_t index = 0; index < p_instance_ctrl->p_cfg->erase_command_list_length; index++)
    {
        /* If requested byte_count is supported by underlying flash, store the command. */
        if (byte_count == p_instance_ctrl->p_cfg->p_erase_command_list[index].size)
        {
            if (SPI_FLASH_ERASE_SIZE_CHIP_ERASE == byte_count)
            {
                /* Don't send address for chip erase. */
                send_address = false;
            }

            erase_command = p_instance_ctrl->p_cfg->p_erase_command_list[index].command;
            break;
        }
    }

#if QSPI_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(0U != erase_command);
#endif

    /* Enter direct communication mode */
    R_QSPI->SFMCMD = 1U;

    /* Enable write. */
    R_QSPI->SFMCOM = p_instance_ctrl->p_cfg->write_enable_command;

    /* Close the SPI bus cycle. Reference section 39.10.3 "Generating the SPI Bus Cycle during Direct Communication"
     * in the RA6M3 manual R01UH0886EJ0100. */
    R_QSPI->SFMCMD = 1U;

    /* Send erase command. */
    R_QSPI->SFMCOM = erase_command;

    /* Send address if this is not a chip erase command. */
    if (send_address)
    {
        if ((p_instance_ctrl->p_cfg->address_bytes & R_QSPI_SFMSAC_SFMAS_Msk) == SPI_FLASH_ADDRESS_BYTES_4)
        {
            R_QSPI->SFMCOM = (uint8_t) (chip_address >> 24);
        }

        R_QSPI->SFMCOM = (uint8_t) (chip_address >> 16);
        R_QSPI->SFMCOM = (uint8_t) (chip_address >> 8);
        R_QSPI->SFMCOM = (uint8_t) (chip_address);
    }

    /* Close the SPI bus cycle. Reference section 39.10.3 "Generating the SPI Bus Cycle during Direct Communication"
     * in the RA6M3 manual R01UH0886EJ0100. */
    R_QSPI->SFMCMD = 1U;

    /* Exit direct communication mode */
    R_QSPI->SFMCMD = 0U;

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
 * @retval FSP_ERR_INVALID_MODE        This function can't be called when XIP mode is enabled.
 **********************************************************************************************************************/
fsp_err_t R_QSPI_StatusGet (spi_flash_ctrl_t * p_ctrl, spi_flash_status_t * const p_status)
{
    qspi_instance_ctrl_t * p_instance_ctrl = (qspi_instance_ctrl_t *) p_ctrl;

#if QSPI_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_status);
    FSP_ERROR_RETURN(QSPI_PRV_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);

    /* Do not enter direct communication mode from XIP mode.  Reference note in section 39.10.2 "Using Direct
     * Communication Mode" in the RA6M3 manual R01UH0886EJ0100. */
    FSP_ERROR_RETURN(0U == R_QSPI->SFMSDC_b.SFMXST, FSP_ERR_INVALID_MODE);
#endif

    /* Read device status. */
    p_status->write_in_progress = r_qspi_status_sub(p_instance_ctrl);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Selects the bank to access. A bank is a 64MB sliding access window into the QSPI device flash memory space. To access
 * chip address 0x4000000, select bank 1, then read from internal flash address 0x60000000. To access chip address
 * 0x8001000, select bank 2, then read from internal flash address 0x60001000.
 *
 * This function is not required for memory devices less than or equal to 512 Mb (64MB).
 *
 * Implements @ref spi_flash_api_t::bankSet.
 *
 * @retval FSP_SUCCESS                 Bank successfully selected.
 * @retval FSP_ERR_ASSERTION           A required pointer is NULL.
 * @retval FSP_ERR_NOT_OPEN            Driver is not opened.
 **********************************************************************************************************************/
fsp_err_t R_QSPI_BankSet (spi_flash_ctrl_t * p_ctrl, uint32_t bank)
{
    qspi_instance_ctrl_t * p_instance_ctrl = (qspi_instance_ctrl_t *) p_ctrl;

#if QSPI_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(QSPI_PRV_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#else
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
#endif

    /* Select the requested bank. */
    R_QSPI->SFMCNT1 = bank << R_QSPI_SFMCNT1_QSPI_EXT_Pos;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Sets the SPI protocol.
 *
 * Implements @ref spi_flash_api_t::spiProtocolSet.
 *
 * @retval FSP_SUCCESS                SPI protocol updated on MCU peripheral.
 * @retval FSP_ERR_ASSERTION          A required pointer is NULL.
 * @retval FSP_ERR_NOT_OPEN           Driver is not opened.
 * @retval FSP_ERR_INVALID_ARGUMENT   Invalid SPI protocol requested.
 **********************************************************************************************************************/
fsp_err_t R_QSPI_SpiProtocolSet (spi_flash_ctrl_t * p_ctrl, spi_flash_protocol_t spi_protocol)
{
    qspi_instance_ctrl_t * p_instance_ctrl = (qspi_instance_ctrl_t *) p_ctrl;

#if QSPI_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(QSPI_PRV_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(SPI_FLASH_PROTOCOL_QPI >= spi_protocol, FSP_ERR_INVALID_ARGUMENT);
#else
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
#endif

    /* Update the SPI protocol. */

    /* The cast is used to prevent a warning that not all values of spi_flash_protocol_t fit in SFMSPI.  spi_protocol is
     * verified to fit in SFMSPI in parameter checking above. */
    R_QSPI->SFMSPC_b.SFMSPI = (uint32_t) spi_protocol & 3U;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Auto-calibrate the OctaRAM device using the preamble pattern. Unsupported by QSPI.
 * Implements @ref spi_flash_api_t::autoCalibrate.
 *
 * @retval FSP_ERR_UNSUPPORTED         API not supported by QSPI
 **********************************************************************************************************************/
fsp_err_t R_QSPI_AutoCalibrate (spi_flash_ctrl_t * p_ctrl)
{
    FSP_PARAMETER_NOT_USED(p_ctrl);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * Close the QSPI driver module.
 *
 * Implements @ref spi_flash_api_t::close.
 *
 * @retval FSP_SUCCESS             Configuration was successful.
 * @retval FSP_ERR_ASSERTION       p_instance_ctrl is NULL.
 * @retval FSP_ERR_NOT_OPEN        Driver is not opened.
 **********************************************************************************************************************/
fsp_err_t R_QSPI_Close (spi_flash_ctrl_t * p_ctrl)
{
    qspi_instance_ctrl_t * p_instance_ctrl = (qspi_instance_ctrl_t *) p_ctrl;

#if QSPI_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(QSPI_PRV_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    p_instance_ctrl->open = 0U;

    /* Disable clock to the QSPI block */
    R_BSP_MODULE_STOP(FSP_IP_QSPI, 0U);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup QSPI)
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Enters or exits XIP (execute in place) mode.
 *
 * @param[in]  p_instance_ctrl         Pointer to a driver handle
 * @param[in]  code                    Code to place in M7-M0
 * @param[in]  enter_mode              True to enter, false to exit
 *
 * @retval FSP_SUCCESS                 The flash was programmed successfully.
 * @retval FSP_ERR_ASSERTION           A required pointer is NULL.
 * @retval FSP_ERR_NOT_OPEN            Driver is not opened.
 **********************************************************************************************************************/
static fsp_err_t r_qspi_xip (qspi_instance_ctrl_t * p_instance_ctrl, uint8_t code, bool enter_mode)
{
#if QSPI_CFG_PARAM_CHECKING_ENABLE

    /* FSP_ASSERT(NULL != p_instance_ctrl) is optimized out when it shouldn't be.  It appears to be affected by GCC bug
     * https://gcc.gnu.org/bugzilla/show_bug.cgi?id=90949. */
    qspi_instance_ctrl_t * volatile p_volatile_ctrl = p_instance_ctrl;
    FSP_ASSERT(NULL != p_volatile_ctrl);
    FSP_ERROR_RETURN(QSPI_PRV_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    volatile uint8_t i = 0;

    FSP_PARAMETER_NOT_USED(i);

    R_QSPI->SFMSDC = (uint32_t) (code << R_QSPI_SFMSDC_SFMXD_Pos) |
                     (uint32_t) (enter_mode << R_QSPI_SFMSDC_SFMXEN_Pos) |
                     (uint32_t) p_instance_ctrl->p_cfg->dummy_clocks;

    /* Read from QSPI to send the XIP entry request. */
    i = *(volatile uint8_t *) QSPI_DEVICE_START_ADDRESS;

    /* Wait for the controller to XIP mode status to update. To confirm completion of the XIP mode enter/exit procedure,
     * read 1/0 from the SFMXST bit in the SFMSDC register. Reference section 39.8.1 "Selecting the XIP Mode" and
     * section 39.8.2 "Releasing the XIP Mode" in the RA6M3 manual R01UH0886EJ0100. */
    FSP_HARDWARE_REGISTER_WAIT(R_QSPI->SFMSDC_b.SFMXST, (uint32_t) enter_mode);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Gets device status.
 *
 * @param[in]  p_instance_ctrl         Pointer to a driver handle
 *
 * @return True if busy, false if not.
 **********************************************************************************************************************/
static bool r_qspi_status_sub (qspi_instance_ctrl_t * p_instance_ctrl)
{
    /* Enter direct communication mode */
    R_QSPI->SFMCMD = 1U;

    R_QSPI->SFMCOM = p_instance_ctrl->p_cfg->status_command;
    bool status = (R_QSPI->SFMCOM >> p_instance_ctrl->p_cfg->write_status_bit) & 1;

    /* Close the SPI bus cycle. Reference section 39.10.3 "Generating the SPI Bus Cycle during Direct Communication"
     * in the RA6M3 manual R01UH0886EJ0100. */
    R_QSPI->SFMCMD = 1U;

    /* Exit direct communication mode */
    R_QSPI->SFMCMD = 0U;

    return status;
}

/*******************************************************************************************************************//**
 * Writes raw data to QSPI.
 *
 * @param[in] p_src                    Pointer to data to write
 * @param[in] bytes                    Number of bytes to write
 * @param[in] read_after_write         Whether or not to close SPI bus cycle
 **********************************************************************************************************************/
static void r_qspi_direct_write_sub (uint8_t const * const p_src, uint32_t const bytes, bool const read_after_write)
{
    /* Enter direct communication mode */
    R_QSPI->SFMCMD = 1U;

    /* Write data to QSPI. */
    for (uint32_t i = 0; i < bytes; i++)
    {
        R_QSPI->SFMCOM = p_src[i];
    }

    if (!read_after_write)
    {
        /* Close the SPI bus cycle. Reference section 39.10.3 "Generating the SPI Bus Cycle during Direct
         * Communication" in the RA6M3 manual R01UH0886EJ0100. */
        R_QSPI->SFMCMD = 1U;

        /* Return to ROM access mode */
        R_QSPI->SFMCMD = 0U;
    }
}

/*******************************************************************************************************************//**
 * Reads raw data from QSPI.
 *
 * @param[in] p_dest                   Pointer to store data
 * @param[in] bytes                    Number of bytes to read
 **********************************************************************************************************************/
static void r_qspi_direct_read_sub (uint8_t * const p_dest, uint32_t const bytes)
{
    /* Read data from QSPI. */
    for (uint32_t i = 0; i < bytes; i++)
    {
        p_dest[i] = (uint8_t) R_QSPI->SFMCOM;
    }

    /* Close the SPI bus cycle. Reference section 39.10.3 "Generating the SPI Bus Cycle during Direct
     * Communication" in the RA6M3 manual R01UH0886EJ0100. */
    R_QSPI->SFMCMD = 1U;

    /* Return to ROM access mode */
    R_QSPI->SFMCMD = 0U;
}

#if QSPI_CFG_SUPPORT_EXTENDED_SPI_MULTI_LINE_PROGRAM

/*******************************************************************************************************************//**
 * Writes a byte in extended SPI mode when the QSPI peripheral is configured for quad mode.
 *
 * @param[in] byte         Byte to write
 **********************************************************************************************************************/
static void qspi_d0_byte_write_quad_mode (uint8_t byte)
{
    /* The LSB of each nibble ends up on D0. */
    uint32_t value = QSPI_PRV_LSB_NIBBLE_CLEARED;
    for (uint32_t i = 0U; i < 8U; i++)
    {
        uint32_t bit = ((uint32_t) (byte >> i) & 1U);

        /* Place bits in every 4th bit (bit 0, 4, 8, ... 28). */
        uint32_t bit_mask = bit << (i * 4U);

        value |= bit_mask;
    }

    R_QSPI->SFMCOM = (uint8_t) (value >> 24U);
    R_QSPI->SFMCOM = (uint8_t) (value >> 16U);
    R_QSPI->SFMCOM = (uint8_t) (value >> 8U);
    R_QSPI->SFMCOM = (uint8_t) value;
}

#endif

#if QSPI_CFG_SUPPORT_EXTENDED_SPI_MULTI_LINE_PROGRAM

/*******************************************************************************************************************//**
 * Writes a byte in extended SPI mode when the QSPI peripheral is configured for dual mode.
 *
 * @param[in] byte         Byte to write
 **********************************************************************************************************************/
static void qspi_d0_byte_write_dual_mode (uint8_t byte)
{
    /* Every other bit ends up on D0. Unused bits are set. */
    uint16_t value = QSPI_PRV_EVEN_BITS_CLEARED;
    for (uint32_t i = 0U; i < 8U; i++)
    {
        uint16_t bit = ((uint16_t) (byte >> i) & 1U);

        /* Place bits in every other bit (bit 0, 2, 4 ... 14). */
        uint16_t bit_mask = (uint16_t) (bit << (i * 2U));

        value |= bit_mask;
    }

    R_QSPI->SFMCOM = (uint8_t) (value >> 8U);
    R_QSPI->SFMCOM = (uint8_t) value;
}

#endif

/*******************************************************************************************************************//**
 * Writes a byte in the SPI mode configured in the QSPI peripheral.
 *
 * @param[in] byte         Byte to write
 **********************************************************************************************************************/
static void qspi_d0_byte_write_standard (uint8_t byte)
{
    R_QSPI->SFMCOM = byte;
}

#if QSPI_CFG_PARAM_CHECKING_ENABLE

/*******************************************************************************************************************//**
 * Parameter checking.
 *
 * @param[in]  p_instance_ctrl         Pointer to a driver handle
 *
 * @retval FSP_SUCCESS                 Device size stored in p_device_size_bytes
 * @retval FSP_ERR_ASSERTION           A required pointer is NULL.
 * @retval FSP_ERR_NOT_OPEN            Driver is not opened.
 * @retval FSP_ERR_DEVICE_BUSY         The device is busy.
 * @retval FSP_ERR_INVALID_MODE        This function can't be called when XIP mode is enabled.
 **********************************************************************************************************************/
static fsp_err_t r_qspi_param_checking_dcom (qspi_instance_ctrl_t * p_instance_ctrl)
{
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(QSPI_PRV_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);

    /* Do not enter direct communication mode from XIP mode.  Reference note in section 39.10.2 "Using Direct
     * Communication Mode" in the RA6M3 manual R01UH0886EJ0100. */
    FSP_ERROR_RETURN(0U == R_QSPI->SFMSDC_b.SFMXST, FSP_ERR_INVALID_MODE);

    /* Verify device is not busy. */
    FSP_ERROR_RETURN(!r_qspi_status_sub(p_instance_ctrl), FSP_ERR_DEVICE_BUSY);

    return FSP_SUCCESS;
}

#endif

#if QSPI_CFG_PARAM_CHECKING_ENABLE

/*******************************************************************************************************************//**
 * Parameter checking for R_QSPI_Write.
 *
 * @param[in] p_instance_ctrl          Pointer to a driver handle
 * @param[in] p_src                    The source of the data to write to QSPI
 * @param[in] p_dest                   The address in QSPI to write to
 * @param[in] byte_count               The number of bytes to write
 *
 * @retval FSP_SUCCESS                 Parameters are valid.
 * @retval FSP_ERR_ASSERTION           p_instance_ctrl,p_device_address or p_memory_address is NULL.
 * @retval FSP_ERR_NOT_OPEN            Driver is not opened.
 * @retval FSP_ERR_INVALID_MODE        This function can't be called when XIP mode is enabled.
 * @retval FSP_ERR_DEVICE_BUSY         The device is busy.
 **********************************************************************************************************************/
static fsp_err_t qspi_program_param_check (qspi_instance_ctrl_t * p_instance_ctrl,
                                           uint8_t const * const  p_src,
                                           uint8_t * const        p_dest,
                                           uint32_t               byte_count)
{
    fsp_err_t err = r_qspi_param_checking_dcom(p_instance_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    FSP_ASSERT(NULL != p_src);
    FSP_ASSERT(NULL != p_dest);

    /* Check if byte_count is valid */
    uint32_t page_size_bytes    = p_instance_ctrl->p_cfg->page_size_bytes;
    uint32_t bytes_left_in_page = page_size_bytes - ((uint32_t) p_dest % page_size_bytes);
    FSP_ASSERT(byte_count <= bytes_left_in_page);

    return FSP_SUCCESS;
}

#endif
