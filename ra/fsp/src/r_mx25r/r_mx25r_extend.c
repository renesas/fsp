#include <r_mx25r_extend.h>
#include "bsp_api.h"

const mx25r_extend_api_t g_mx25r_extend_on_QSPI =
{
  .mx25r_device_reset        = MX25R_Device_Reset,
  .mx25r_enter_deeppower     = MX25R_Enter_DeepPower,
  .mx25r_exit_deeppower      = MX25R_Exit_DeepPower,
  .mx25r_highperformancemode = MX25R_HighPerformanceMode,
  .mx25r_lowpowermode        = MX25R_LowPowerMode,
  .rdid                      = RDID,
  .rdcr                      = RDCR,
  .rdsr                      = RDSR,
  .rdscur                    = RDSCUR,
};

bool deepdown;

void RDID(mx25r_ID* ID)
{
    /* Check there is no serial transfer in progress */
    while (1U == R_QSPI->SFMCST_b.COMBSY)
    {
    }

    /* Enter direct communication mode */
    R_QSPI->SFMCMD = 1U;

    /* Read ID. */
    R_QSPI->SFMCOM         = QSPI_COMMAND_READ_ID;            /* Write the command */
    ID->manufacturer_id = R_QSPI->SFMCOM_b.SFMD;              /* Read manufacturer_id*/
    ID->memory_capacity = R_QSPI->SFMCOM_b.SFMD;              /* Read memory_capacity*/
    ID->memory_type     = R_QSPI->SFMCOM_b.SFMD;              /* Read memory_type*/
    R_QSPI->SFMCMD = 1U;

    /* Return to ROM access mode */
    R_QSPI->SFMCMD = 0U;
}

void RDSR(mx25r_status_reg* status)
{
    /* Check there is no serial transfer in progress */
    while (1U == R_QSPI->SFMCST_b.COMBSY)
    {
    }

    /* Enter direct communication mode */
    R_QSPI->SFMCMD = 1U;

    /* Read status register. */
    R_QSPI->SFMCOM         = QSPI_COMMAND_READ_STATUS_REGISTER;  /* Write the command */
    status->status         = R_QSPI->SFMCOM_b.SFMD;              /* Read Read status register*/
    R_QSPI->SFMCMD = 1U;

    /* Return to ROM access mode */
    R_QSPI->SFMCMD = 0U;
}

void RDSCUR(mx25R_security_reg* security)
{
    /* Check there is no serial transfer in progress */
    while (1U == R_QSPI->SFMCST_b.COMBSY)
    {
    }

    /* Enter direct communication mode */
    R_QSPI->SFMCMD = 1U;

    /* Read security register. */
    R_QSPI->SFMCOM         = QSPI_COMMAND_READ_SECURITY_REGISTER;  /* Write the command */
    security->security     = R_QSPI->SFMCOM_b.SFMD;                /* Read Read security register*/
    R_QSPI->SFMCMD = 1U;

    /* Return to ROM access mode */
    R_QSPI->SFMCMD = 0U;
}

void RDCR(mx25r_cfg_reg* configuration)
{
    /* Check there is no serial transfer in progress */
    while (1U == R_QSPI->SFMCST_b.COMBSY)
    {
    }

    /* Enter direct communication mode */
    R_QSPI->SFMCMD = 1U;

    /* Read configuration register-1 and configuration register-2. */
    R_QSPI->SFMCOM                   = QSPI_COMMAND_READ_CONFIG_REGISTER;  /* Write the command */
    configuration->configuration1    = R_QSPI->SFMCOM_b.SFMD;              /* Read Read security register*/
    configuration->configuration2    = R_QSPI->SFMCOM_b.SFMD;              /* Read Read security register*/
    R_QSPI->SFMCMD = 1U;

    /* Return to ROM access mode */
    R_QSPI->SFMCMD = 0U;
}

void MX25R_LowPowerMode (void)
{
    mx25r_status_reg status_reg;
    mx25r_cfg_reg  cfg_reg;

    /* Check there is no serial transfer in progress */
    while (1U == R_QSPI->SFMCST_b.COMBSY)
    {
    }

    /* Enter direct communication mode */
    R_QSPI->SFMCMD = 1U;

    /* Read status register */
    R_QSPI->SFMCOM         = QSPI_COMMAND_READ_STATUS_REGISTER;  /* Write the command */
    status_reg.status      = R_QSPI->SFMCOM_b.SFMD;              /* Read status register */
    R_QSPI->SFMCMD = 1U;                                         /* Close the SPI bus cycle */

    /* Read configuration register-1 and configuration register-2. */
    R_QSPI->SFMCOM         = QSPI_COMMAND_READ_CONFIG_REGISTER;  /* Write the command */
    cfg_reg.configuration1 = R_QSPI->SFMCOM_b.SFMD;              /* Read configuration register 1*/
    cfg_reg.configuration2 = R_QSPI->SFMCOM_b.SFMD;              /* Read configuration register 2*/
    R_QSPI->SFMCMD = 1U;                                         /* Close the SPI bus cycle */

    /* set configuration register-2 lhs bit to 0 to goto ultra lower power mode*/
    cfg_reg.configuration2_b.lhs = 0U;

    R_QSPI->SFMCOM  = QSPI_COMMAND_WRITE_ENABLE;   /* Write the command */
    R_QSPI->SFMCMD_b.DCOM = 1U;                    /* Close the SPI bus cycle */

    /* Write Status Register, configuration register-1 and configuration register-2 */
    R_QSPI->SFMCOM        = QSPI_COMMAND_WRITE_STATUS_REGISTER;   /* Write the command */
    R_QSPI->SFMCOM        = status_reg.status;                    /* Write the Status Register */
    R_QSPI->SFMCOM        = cfg_reg.configuration1;               /* Write the configuration register-1 */
    R_QSPI->SFMCOM        = cfg_reg.configuration2;               /* Write the configuration register-2 */
    R_QSPI->SFMCMD_b.DCOM = 1U;                                    /* Close the SPI bus cycle */

    /* Write Status Register takes 40ms */
    R_BSP_SoftwareDelay(40U, BSP_DELAY_UNITS_MILLISECONDS);

    /* Return to ROM access mode */
    R_QSPI->SFMCMD = 0U;
}

void MX25R_HighPerformanceMode (void)
{
    mx25r_status_reg status_reg;
    mx25r_cfg_reg  cfg_reg;

    /* Check there is no serial transfer in progress */
    while (1U == R_QSPI->SFMCST_b.COMBSY)
    {
    }

    /* Enter direct communication mode */
    R_QSPI->SFMCMD = 1U;

    /* Read status register */
    R_QSPI->SFMCOM         = QSPI_COMMAND_READ_STATUS_REGISTER;  /* Write the command */
    status_reg.status      = R_QSPI->SFMCOM_b.SFMD;              /* Read status register */
    R_QSPI->SFMCMD = 1U;                                         /* Close the SPI bus cycle */

    /* Read configuration register-1 and configuration register-2. */
    R_QSPI->SFMCOM         = QSPI_COMMAND_READ_CONFIG_REGISTER;  /* Write the command */
    cfg_reg.configuration1 = R_QSPI->SFMCOM_b.SFMD;              /* Read configuration register 1*/
    cfg_reg.configuration2 = R_QSPI->SFMCOM_b.SFMD;              /* Read configuration register 2*/
    R_QSPI->SFMCMD = 1U;                                         /* Close the SPI bus cycle */

    /* set configuration register-2 lhs bit to 1 to goto high performance mode*/
    cfg_reg.configuration2_b.lhs = 1U;

    R_QSPI->SFMCOM  = QSPI_COMMAND_WRITE_ENABLE;   /* Write the command */
    R_QSPI->SFMCMD = 1U;                           /* Close the SPI bus cycle */

    /* Write Status Register, configuration register-1 and configuration register-2 */
    R_QSPI->SFMCOM        = QSPI_COMMAND_WRITE_STATUS_REGISTER;   /* Write the command */
    R_QSPI->SFMCOM        = status_reg.status;                    /* Write the Status Register */
    R_QSPI->SFMCOM        = cfg_reg.configuration1;               /* Write the configuration register-1 */
    R_QSPI->SFMCOM        = cfg_reg.configuration2;               /* Write the configuration register-2 */
    R_QSPI->SFMCMD = 1U;                                          /* Close the SPI bus cycle */

    /* Write Status Register takes 40ms */
    R_BSP_SoftwareDelay(40U, BSP_DELAY_UNITS_MILLISECONDS);

    /* Return to ROM access mode */
    R_QSPI->SFMCMD = 0U;
}

void MX25R_Enter_DeepPower (void)
{
    /* Check there is no serial transfer in progress */
    while (1U == R_QSPI->SFMCST_b.COMBSY){}

    /* enter direct communication mode */
    R_QSPI->SFMCMD = 1U;

    R_QSPI->SFMCOM        = QSPI_COMMAND_DEEP_POWER_DOWN;  /* Write the command */
    R_QSPI->SFMCMD = 1U;                                   /* Close the SPI bus cycle */

    /* As soon as CS# goes high, a maximum delay of 10us is required before entering the Deep Power-down mode*/
    R_BSP_SoftwareDelay(10U, BSP_DELAY_UNITS_MICROSECONDS);

    /* Return to ROM access mode */
    R_QSPI->SFMCMD = 0U;
}

void MX25R_Exit_DeepPower (void)
{
    /* Check there is no serial transfer in progress */
    while (1U == R_QSPI->SFMCST_b.COMBSY)
    {
    }

    /* enter direct communication mode */
    R_QSPI->SFMCMD = 1U;

    /** For MX25Rxx: flash chip doesn't have RDP command, so using using CS# go low and then go high method
     *  to release from deep power down mode */
    /* 1) CS# keeps high for minimum 30us */
    R_BSP_SoftwareDelay(30U, BSP_DELAY_UNITS_MICROSECONDS);

    /* 2) CS# keeps low for minimum 20ns, MCU highest frequency is 240MhZ, 20ns at least need 4 instructions */
    R_QSPI->SFMCOM = 0x00U;      /* used to keep CS# low */
    R_QSPI->SFMCOM = 0x00U;      /* used to keep CS# low */
    R_QSPI->SFMCOM = 0x00U;      /* used to keep CS# low */
    R_QSPI->SFMCOM = 0x00U;      /* used to keep CS# low */
    R_QSPI->SFMCMD = 1U;         /* Close the SPI bus cycle */

    /* 3) As soon as CS# goes high, a maximum delay of 35us is required before releasing from Deep Power-down mode */
    R_BSP_SoftwareDelay(35U, BSP_DELAY_UNITS_MICROSECONDS);

    /* Return to ROM access mode */
    R_QSPI->SFMCMD = 0U;

}

void MX25R_Device_Reset (void)
{
    /* 1) Check there is no serial transfer in progress */
    while (1U == R_QSPI->SFMCST_b.COMBSY)
    {
    }

    /* enter direct communication mode */
    R_QSPI->SFMCMD = 1U;

    /* 2) Reset the flash device. */
    R_QSPI->SFMCOM        = QSPI_COMMAND_RESET_ENABLE; /* Write the command */
    R_QSPI->SFMCMD = 1U;                               /* Close the SPI bus cycle */
    R_QSPI->SFMCOM        = QSPI_COMMAND_RESET_MEMORY; /* Write the command */
    R_QSPI->SFMCMD = 1U;                               /* Close the SPI bus cycle */

    /* 3) Reset takes maximum 80us */
    R_BSP_SoftwareDelay(80U, BSP_DELAY_UNITS_MICROSECONDS);

    R_QSPI->SFMCMD = 1U;                               /* enter direct communication mode */

    R_QSPI->SFMCMD = 0U;                               /* Return to ROM access mode */

}

fsp_err_t setNormalMode()
{
	return FSP_ERR_UNSUPPORTED;
}

fsp_err_t setHighPerformanceMode()
{
    if(deepdown){
        MX25R_Exit_DeepPower();
    }

	MX25R_HighPerformanceMode();
	return FSP_SUCCESS;
}

fsp_err_t setLowPowerMode()
{
    if(deepdown){
        MX25R_Exit_DeepPower();
    }

	MX25R_LowPowerMode();
	return FSP_SUCCESS;
}

fsp_err_t setSuperLowPowerMode()
{
	return FSP_ERR_UNSUPPORTED;
}

fsp_err_t setDeepPowerDownMode()
{
	MX25R_Enter_DeepPower();
	deepdown = true;
	return FSP_SUCCESS;
}

fsp_err_t power_init()
{
    deepdown = false;
	return FSP_SUCCESS;
}


