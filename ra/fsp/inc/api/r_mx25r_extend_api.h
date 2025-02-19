#ifndef FSP_INC_API_R_MX25R_EXTEND_API_H_
#define FSP_INC_API_R_MX25R_EXTEND_API_H_

/* Register definitions, common services and error codes. */
#include "bsp_api.h"

/** Available commands for the Macronix MX25xxx series Serial NOR Flash device */
typedef enum e_qspi_command
{
    /** Reset Operations */
    QSPI_COMMAND_RESET_ENABLE              = 0x66,         ///< Enable reset
    QSPI_COMMAND_RESET_MEMORY              = 0x99,         ///< Reset memory

    QSPI_COMMAND_DEEP_POWER_DOWN           = 0xb9,         ///< Enter deep power down mode
    QSPI_COMMAND_RELEASE_DEEP_POWER_DOWN   = 0xab,         ///< Release from deep power down mode

    /** Write Operations */
    QSPI_COMMAND_WRITE_ENABLE              = 0x06,         ///< Write Enable
    QSPI_COMMAND_WRITE_DISABLE             = 0x04,         ///< Write Disable

    /** Register Operations */
    QSPI_COMMAND_READ_STATUS_REGISTER      = 0x05,         ///< Read Status register
    QSPI_COMMAND_WRITE_STATUS_REGISTER     = 0x01,         ///< Write Status register
    QSPI_COMMAND_READ_CONFIG_REGISTER      = 0x15,         ///< Read Configuration register
    QSPI_COMMAND_READ_ID                   = 0x9F,         ///< Read the chip ID
    QSPI_COMMAND_READ_SECURITY_REGISTER    = 0x2B,         ///< Read Security register
    QSPI_COMMAND_WRITE_SECURITY_REGISTER   = 0x2F,         ///< Write Security register

} qspi_command;

typedef struct st_mx25r_status_register
{
    union
    {
        uint8_t    status;
        struct
        {
            uint8_t wip     : 1;    ///< Erase/Write in progress (busy = 1)
            uint8_t wel     : 1;    ///< Write Latch Enable (Set to 1 after write enable, 0 write disable)
            uint8_t bp      : 4;    ///< Block Protection bits (1=protected, 0= unprotected)
            uint8_t qe      : 1;    ///< Quad Enable (1= Quad enabled)
            uint8_t srwd    : 1;    ///< Status Register Write Disable Bit
         }status_b;
    };
} mx25r_status_reg;

typedef struct st_mx25R_security_register
{
    union
    {
        uint8_t    security;
        struct
        {
            uint8_t secured_OTP    : 1;    ///< Secured OTP indicator bit
            uint8_t ldso           : 1;    ///< Lock-down OTP (0=not lock-down, 1=lock-down)
            uint8_t psb            : 1;    ///< Program Suspend bit (0=not suspend, 1=suspend)
            uint8_t esb            : 1;    ///< Erase Suspend bit (0=not suspend, 1=suspend)
            uint8_t                : 1;    ///< Reverse
            uint8_t p_fial         : 1;    ///< (0=normal program succeed, 1=program failed)
            uint8_t e_fial         : 1;    ///< (0=normal erase succeed, 1=erase failed)
            uint8_t wpsel          : 1;    ///< Only for MX25Lxxx,OTP (0=BP mode, 1=advance mode)
         }security_b;
    };
} mx25R_security_reg;

typedef struct st_mx25r_configuration_register
{
   union
   {
       uint8_t   configuration1;
       struct
       {
           uint8_t         : 3;    ///< reserved
           uint8_t tb      : 1;    ///< top/bottom selected (OTP bit)
           uint8_t         : 2;    ///< reserved
           uint8_t dc      : 1;    ///< dummy cycle for 2read and 4read
           uint8_t         : 1;    ///< reserved
        }configuration1_b;
   };
   union
    {
      uint8_t   configuration2;
      struct
      {
          uint8_t        : 1;    ///< reserved
          uint8_t lhs    : 1;    ///< ultra low power mode and high performance mode switch
          uint8_t        : 6;    ///< reserved
       }configuration2_b;
    };

} mx25r_cfg_reg;


typedef struct st_mx25r_ID
{
    uint8_t   manufacturer_id;    ///< Manufacturer ID
    uint8_t   memory_type;        ///< Memory type
    uint8_t   memory_capacity;    ///< Memory capacity
} mx25r_ID;


/** QSPI functions implemented at the HAL layer follow this API. */
typedef struct st_mx25r_extend_api
{
    void (* mx25r_lowpowermode)(void);
    void (* mx25r_highperformancemode)(void);
    void (* mx25r_enter_deeppower)(void);
    void (* mx25r_exit_deeppower)(void);
    void (* mx25r_device_reset)(void);
    void (* rdid)(mx25r_ID* ID);
    void (* rdsr)(mx25r_status_reg* status);
    void (* rdscur)(mx25R_security_reg* security);
    void (* rdcr)(mx25r_cfg_reg* configuration);

} mx25r_extend_api_t;

typedef void mx25r_extend_ctrl_t;

typedef struct mx25r_extend_cfg
{
    void const              * p_extend;  ///< Pointer to hardware dependent configuration
} mx25r_extend_cfg_t;

typedef struct st_mx25r_extend_instance
{
    mx25r_extend_ctrl_t      * p_ctrl;    ///< Pointer to the control structure for this instance
	mx25r_extend_cfg_t const * p_cfg;     ///< Pointer to the configuration structure for this instance
    mx25r_extend_api_t const * p_api;     ///< Pointer to the API structure for this instance

} mx25r_extend_instance_t;

#endif /* FSP_INC_API_R_MX25R_EXTEND_API_H_ */
