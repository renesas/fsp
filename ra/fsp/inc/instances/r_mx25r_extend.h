#ifndef FSP_INC_INSTANCES_R_MX25R_EXTEND_H_
#define FSP_INC_INSTANCES_R_MX25R_EXTEND_H_

#include <r_mx25r_extend_api.h>
#include <r_spi_flash_api.h>

/** User configuration structure, used in open function */
typedef struct st_mx25r_extend_flash_cfg
{
    spi_flash_instance_t const * p_flash;  ///< Pointer to a QSPI flash instance
} mx25r_extend_flash_cfg_t;

/** Instance control block.  This is private to the FSP and should not be used or modified by the application. */
typedef struct st_mx25r_extend_instance_ctrl
{
    mx25r_extend_cfg_t const * p_cfg;
} mx25r_extend_instance_ctrl_t;

extern const mx25r_extend_api_t g_mx25r_extend_on_QSPI;

extern bool deepdown;

void MX25R_LowPowerMode(void);
void MX25R_HighPerformanceMode(void);
void MX25R_Enter_DeepPower(void);
void MX25R_Exit_DeepPower(void);
void MX25R_Device_Reset(void);
void RDID(mx25r_ID* ID);
void RDSR(mx25r_status_reg* status);
void RDSCUR(mx25R_security_reg* security);
void RDCR(mx25r_cfg_reg* configuration);

fsp_err_t setNormalMode();
fsp_err_t setHighPerformanceMode();
fsp_err_t setLowPowerMode();
fsp_err_t setSuperLowPowerMode();
fsp_err_t setDeepPowerDownMode();
fsp_err_t power_init();

#endif /* FSP_INC_INSTANCES_R_MX25R_EXTEND_H_ */
