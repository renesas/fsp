/***********************************************************************************************************************
 * Copyright [2015] Renesas Electronics Corporation and/or its licensors. All Rights Reserved.
 *
 * This file is part of Renesas RA Flex Software Package (FSP)
 *
 * The contents of this file (the "contents") are proprietary and confidential to Renesas Electronics Corporation
 * and/or its licensors ("Renesas") and subject to statutory and contractual protections.
 *
 * This file is subject to a Renesas FSP license agreement. Unless otherwise agreed in an FSP license agreement with
 * Renesas: 1) you may not use, copy, modify, distribute, display, or perform the contents; 2) you may not use any name
 * or mark of Renesas for advertising or publicity purposes or in connection with your use of the contents; 3) RENESAS
 * MAKES NO WARRANTY OR REPRESENTATIONS ABOUT THE SUITABILITY OF THE CONTENTS FOR ANY PURPOSE; THE CONTENTS ARE PROVIDED
 * "AS IS" WITHOUT ANY EXPRESS OR IMPLIED WARRANTY, INCLUDING THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE, AND NON-INFRINGEMENT; AND 4) RENESAS SHALL NOT BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, OR
 * CONSEQUENTIAL DAMAGES, INCLUDING DAMAGES RESULTING FROM LOSS OF USE, DATA, OR PROJECTS, WHETHER IN AN ACTION OF
 * CONTRACT OR TORT, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THE CONTENTS. Third-party contents
 * included in this file may be subject to different terms.
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * File Name    : bsp_qspi.c
 * Description  : QSPI initialization.
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @addtogroup BSP_EK_RA6M3_QSPI
 * @brief QSPI initialization
 *
 * This file contains code that initializes the QSPI flash controller connected to a MX25L12835F
 * Maxonic NOR Flash/ N25Q256A Micron Serial NOR Flash Memory mounted on a EK-RA6M3 evaluation board.
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "board_qspi.h"
#include "board.h"

#if defined(BOARD_RA6M3_EK)

static struct
{
    uint8_t manufacturer_id;
    uint8_t memory_type;
    uint8_t memory_capacity;
} qspi_device;

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief   Initializes QSPI.
 *
 * This function initializes QSPI and Micron Serial Flash Memory device on the board.
 *
 * @note This function is executed once after reset.
 **********************************************************************************************************************/
void bsp_qspi_init (void)
{
    R_MSTP->MSTPCRB_b.MSTPB6 = 0u;     // release QSPI from module stop
    while (0 != R_MSTP->MSTPCRB_b.MSTPB6)
    {
        ;                              // wait for module stop bit to become 0
    }

    /* Exit Quad mode in serial Flash device if any:
     * The steps below are to make sure that both serial flash device and QSPI controller are started in SPI mode
     * whether it is power-on reset or MCU reset
     * *//* Setting QSPI protocol to Quad mode */
    R_QSPI->SFMSPC_b.SFMSPI = QSPI_QUAD_SPI_PROTOCOL;

    /* Enter direct comm mode */
    R_QSPI->SFMCMD = 1u;

    /* Exit Quad mode in serial flash device if any
     * This enabling RESET function of RESET#/SIO3 pin
     */
    R_QSPI->SFMCOM = QSPI_COMMAND_EXIT_QPI;

    /* Close SPI bus cycle */
    R_QSPI->SFMCMD = 1u;

    /* Reset QSPI flash device using RESET#/SIO3 pin */
    R_BSP_PinAccessEnable();

    /* Set P310 as I/O port function and driving it low for the specified time to rest QSPI flash device */
    R_PFS->PORT[3].PIN[10].PmnPFS_b.PMR  = 0u;
    R_PFS->PORT[3].PIN[10].PmnPFS_b.PODR = 0u;
    R_PFS->PORT[3].PIN[10].PmnPFS_b.PDR  = 1u;

    /* Keep RESET line low for 50us */
    R_BSP_SoftwareDelay(50u, BSP_DELAY_UNITS_MICROSECONDS);

    /* Set P310 pin back to QSPI function */
    R_PFS->PORT[3].PIN[10].PmnPFS_b.PMR = 1u;

    R_BSP_PinAccessDisable();

    /* Exit direct comm mode to update SPI mode */
    R_QSPI->SFMCMD = 0u;

    /* Setting QSPI protocol in extended SPI mode, now both QSPI controller and serial flash device are in SPI mode*/
    R_QSPI->SFMSPC_b.SFMSPI = QSPI_EXTENDED_SPI_PROTOCOL;

    R_QSPI->SFMCMD = 1u;

    /* Identify the QSPI device */
    R_QSPI->SFMCOM              = QSPI_COMMAND_READ_ID;
    qspi_device.manufacturer_id = (uint8_t) R_QSPI->SFMCOM;
    qspi_device.memory_type     = (uint8_t) R_QSPI->SFMCOM;
    qspi_device.memory_capacity = (uint8_t) R_QSPI->SFMCOM;
    R_QSPI->SFMCMD              = 1u;

    if ((BSP_PRV_MX25_QSPI_MANUFACTURER_ID == qspi_device.manufacturer_id) &&
        (BSP_PRV_MX25_QSPI_MEMORY_TYPE == qspi_device.memory_type) &&
        (BSP_PRV_MX25_QSPI_MEMORY_CAPACITY == qspi_device.memory_capacity))
    {
        /* Enable Quad mode in serial flash device */
        R_QSPI->SFMCOM = QSPI_COMMAND_ENABLE_QPI;

        /* Close SPI Bus cycle */
        R_QSPI->SFMCMD = 1u;

        /* Exit direct comm mode and enter ROM Access mode to set QSPI registers.
         * Now both QSPI Flash controller and serial flash device are in Quad mode */
        R_QSPI->SFMCMD = 0u;

        R_QSPI->SFMSPC = (uint32_t) ((BSP_QSPI_VAL_SFMSDE << 4) | BSP_QSPI_VAL_SFMSPI);
        R_QSPI->SFMSKC = (uint32_t) ((BSP_QSPI_VAL_SFMDTY << 5) | BSP_QSPI_VAL_SFMDV);
        R_QSPI->SFMSDC = (uint32_t) ((BSP_QSPI_VAL_SFMXD << 8) | (BSP_QSPI_VAL_SFMXEN << 7) | \
                                     (BSP_QSPI_VAL_SFMXST << 6) | (BSP_QSPI_VAL_SFMDN));
        R_QSPI->SFMSSC = (uint32_t) ((BSP_QSPI_VAL_SFMSLD << 5) | (BSP_QSPI_VAL_SFMSHD << 4) | \
                                     (BSP_QSPI_VAL_SFMSW));
        R_QSPI->SFMSMD = (uint32_t) ((BSP_QSPI_VAL_SFMPFE << 6) | (BSP_QSPI_VAL_SFMRM));

        /* Enter ROM access mode */
        R_QSPI->SFMCMD = 0u;
    }
    else
    {
        /* Not Macronix MX25L12845G, disable QSPI */
        R_MSTP->MSTPCRB_b.MSTPB6 = 1u; // set QSPI from module stop
    }
}

#endif

/** @} (end addtogroup BSP_EK_RA6M3_QSPI) */
