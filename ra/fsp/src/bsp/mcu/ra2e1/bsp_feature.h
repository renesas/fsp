/* ${REA_DISCLAIMER_PLACEHOLDER} */

#ifndef BSP_FEATURE_H
#define BSP_FEATURE_H

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/** The main oscillator drive value is based upon the oscillator frequency selected in the configuration */
#if (BSP_CFG_XTAL_HZ > (9999999))
 #define CGC_MAINCLOCK_DRIVE    (0x00U)
#else
 #define CGC_MAINCLOCK_DRIVE    (0x01U)
#endif

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global variables (to be accessed by other files)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables and functions
 **********************************************************************************************************************/

#define BSP_FEATURE_ACMPHS_MIN_WAIT_TIME_US               (0) // Feature not available on this MCU
#define BSP_FEATURE_ACMPHS_VREF                           (0) // Feature not available on this MCU

#define BSP_FEATURE_ACMPLP_HAS_COMPSEL_REGISTERS          (0)
#define BSP_FEATURE_ACMPLP_MIN_WAIT_TIME_US               (100U)

#define BSP_FEATURE_ADC_ADDITION_SUPPORTED                (1U)
#define BSP_FEATURE_ADC_CALIBRATION_REG_AVAILABLE         (0U)
#define BSP_FEATURE_ADC_CLOCK_SOURCE                      (FSP_PRIV_CLOCK_PCLKD)
#define BSP_FEATURE_ADC_GROUP_B_SENSORS_ALLOWED           (0U)
#define BSP_FEATURE_ADC_HAS_ADCER_ADPRC                   (0U)
#define BSP_FEATURE_ADC_HAS_ADCER_ADRFMT                  (1U)
#define BSP_FEATURE_BSP_HAS_CLOCK_SUPPLY_TYPEB            (1U)
#define BSP_FEATURE_ADC_HAS_PGA                           (0U)
#define BSP_FEATURE_ADC_HAS_SAMPLE_HOLD_REG               (0U)
#define BSP_FEATURE_ADC_HAS_VREFAMPCNT                    (0U)
#define BSP_FEATURE_ADC_MAX_RESOLUTION_BITS               (12U)
#define BSP_FEATURE_ADC_SENSORS_EXCLUSIVE                 (1U)
#define BSP_FEATURE_ADC_SENSOR_MIN_SAMPLING_TIME          (5000U)
#define BSP_FEATURE_ADC_TSN_CALIBRATION32_AVAILABLE       (0U)
#define BSP_FEATURE_ADC_TSN_CALIBRATION32_MASK            (0U)
#define BSP_FEATURE_ADC_TSN_CALIBRATION_AVAILABLE         (1U)
#define BSP_FEATURE_ADC_TSN_CONTROL_AVAILABLE             (0U)
#define BSP_FEATURE_ADC_TSN_SLOPE                         (-3300)
#define BSP_FEATURE_ADC_UNIT_0_CHANNELS                   (0x7E07FF) // 0 to 10, 17 to 22 in unit 0
#define BSP_FEATURE_ADC_UNIT_1_CHANNELS                   (0)
#define BSP_FEATURE_ADC_VALID_UNIT_MASK                   (1U)

#define BSP_FEATURE_AGT_VALID_CHANNEL_MASK                (0x03)
#define BSP_FEATURE_AGT_MAX_CHANNEL_NUM                   (1)

#define BSP_FEATURE_BSP_FLASH_CACHE                       (0)
#define BSP_FEATURE_BSP_FLASH_CACHE_DISABLE_OPM           (1U)
#define BSP_FEATURE_BSP_FLASH_PREFETCH_BUFFER             (1)
#define BSP_FEATURE_BSP_HAS_CODE_SYSTEM_CACHE             (0)
#define BSP_FEATURE_BSP_HAS_OCTASPI_CLOCK                 (0) // Feature not available on this MCU
#define BSP_FEATURE_BSP_HAS_SCE5                          (0) // Feature not available on this MCU
#define BSP_FEATURE_BSP_HAS_SCE_ON_RA2                    (1)
#define BSP_FEATURE_CRYPTO_HAS_CTR_DRBG                   (0)
#define BSP_FEATURE_BSP_HAS_SECURITY_MPU                  (1U)
#define BSP_FEATURE_BSP_HAS_SP_MON                        (1U)
#define BSP_FEATURE_BSP_HAS_USBCKDIVCR                    (0) // Feature not available on this MCU
#define BSP_FEATURE_BSP_HAS_USB_CLOCK_DIV                 (0) // Feature not available on this MCU
#define BSP_FEATURE_BSP_HAS_USB_CLOCK_REQ                 (0) // Feature not available on this MCU
#define BSP_FEATURE_BSP_HAS_USB_CLOCK_SEL                 (0U)
#define BSP_FEATURE_BSP_HAS_USB_CLOCK_SEL_ALT             (0U)
#define BSP_FEATURE_BSP_MCU_INFO_POINTER_LOCATION         (0U)
#define BSP_FEATURE_BSP_MPU_REGION0_MASK                  (0x000FFFFFU)
#define BSP_FEATURE_BSP_MSTP_GPT_MSTPD5_MAX_CH            (0U) // Largest channel number associated with lower MSTP bit for GPT on this MCU.
#define BSP_FEATURE_BSP_MSTP_HAS_MSTPCRE                  (0)  // Feature not available on this MCU
#define BSP_FEATURE_BSP_OFS1_HOCOFRQ_MASK                 (0xFFFF8FFFU)
#define BSP_FEATURE_BSP_OFS1_HOCOFRQ_OFFSET               (12U)
#define BSP_FEATURE_BSP_OSIS_PADDING                      (1)
#define BSP_FEATURE_BSP_POWER_CHANGE_MSTP_REQUIRED        (0U)
#define BSP_FEATURE_BSP_HAS_DCDC_REGULATOR                (0U)
#define BSP_FEATURE_BSP_RESET_TRNG                        (1U)
#define BSP_FEATURE_BSP_SYS_CLOCK_FREQ_NO_RAM_WAITS       (0) // Feature not available on this MCU
#define BSP_FEATURE_BSP_SYS_CLOCK_FREQ_ONE_ROM_WAITS      (0) // Feature not available on this MCU
#define BSP_FEATURE_BSP_SYS_CLOCK_FREQ_THREE_ROM_WAITS    (0) // Feature not available on this MCU
#define BSP_FEATURE_BSP_SYS_CLOCK_FREQ_TWO_ROM_WAITS      (0) // Feature not available on this MCU
#define BSP_FEATURE_BSP_UNIQUE_ID_OFFSET                  (0U)
#define BSP_FEATURE_BSP_UNIQUE_ID_POINTER                 (0x01001C00U)
#define BSP_FEATURE_BSP_VBATT_HAS_VBTCR1_BPWSWSTP         (0U)

#define BSP_FEATURE_CAN_CHECK_PCLKB_RATIO                 (0U)                  // Feature not available on this MCU
#define BSP_FEATURE_CAN_CLOCK                             (FSP_PRIV_CLOCK_ICLK) // Feature not available on this MCU
#define BSP_FEATURE_CAN_MCLOCK_ONLY                       (0U)                  // Feature not available on this MCU
#define BSP_FEATURE_CAN_NUM_CHANNELS                      (0U)                  // Feature not available on this MCU

#define BSP_FEATURE_CGC_HAS_BCLK                          (0U)
#define BSP_FEATURE_CGC_HAS_FCLK                          (0U)
#define BSP_FEATURE_CGC_HAS_FLDWAITR                      (1U)
#define BSP_FEATURE_CGC_HAS_FLWT                          (0U)
#define BSP_FEATURE_CGC_HAS_FLL                           (0U)
#define BSP_FEATURE_CGC_HAS_HOCOWTCR                      (0U)
#define BSP_FEATURE_CGC_HAS_MEMWAIT                       (1U)
#define BSP_FEATURE_CGC_HAS_PCLKA                         (0U)
#define BSP_FEATURE_CGC_HAS_PCLKB                         (1U)
#define BSP_FEATURE_CGC_HAS_PCLKC                         (0U)
#define BSP_FEATURE_CGC_HAS_PCLKD                         (1U)
#define BSP_FEATURE_CGC_HAS_PLL                           (0U)
#define BSP_FEATURE_CGC_HAS_PLL2                          (0)  // Feature not available on this MCU
#define BSP_FEATURE_CGC_HAS_SRAMPRCR2                     (0)  // Feature not available on this MCU
#define BSP_FEATURE_CGC_HAS_SRAMWTSC                      (0U)
#define BSP_FEATURE_CGC_HOCOSF_BEFORE_OPCCR               (1U)
#define BSP_FEATURE_CGC_HOCOWTCR_64MHZ_ONLY               (0U) // Feature not available on this MCU
#define BSP_FEATURE_CGC_ICLK_DIV_RESET                    (BSP_CLOCKS_SYS_CLOCK_DIV_16)
#define BSP_FEATURE_CGC_LOCO_STABILIZATION_MAX_US         (100U)
#define BSP_FEATURE_CGC_LOW_SPEED_MAX_FREQ_HZ             (2000000U)
#define BSP_FEATURE_CGC_LOW_VOLTAGE_MAX_FREQ_HZ           (0U) // This MCU does not have Low Voltage Mode
#define BSP_FEATURE_CGC_MIDDLE_SPEED_MAX_FREQ_HZ          (24000000U)
#define BSP_FEATURE_CGC_MOCO_STABILIZATION_MAX_US         (1U)
#define BSP_FEATURE_CGC_MODRV_MASK                        (0x08U)
#define BSP_FEATURE_CGC_MODRV_SHIFT                       (0x3U)
#define BSP_FEATURE_CGC_PLLCCR_TYPE                       (0U)
#define BSP_FEATURE_CGC_PLLCCR_WAIT_US                    (0U) // This MCU does not have PLL
#define BSP_FEATURE_CGC_PLLCCR_MAX_HZ                     (0U)
#define BSP_FEATURE_CGC_SCKDIVCR_BCLK_MATCHES_PCLKB       (0U)
#define BSP_FEATURE_CGC_SODRV_MASK                        (0x03U)
#define BSP_FEATURE_CGC_SODRV_SHIFT                       (0x0U)
#define BSP_FEATURE_CGC_STARTUP_OPCCR_MODE                (1)

#define BSP_FEATURE_CRYPTO_HAS_AES                        (1) // skipped for now
#define BSP_FEATURE_CRYPTO_HAS_AES_WRAPPED                (0) //
#define BSP_FEATURE_CRYPTO_HAS_ECC                        (0) //
#define BSP_FEATURE_CRYPTO_HAS_ECC_WRAPPED                (0) //
#define BSP_FEATURE_CRYPTO_HAS_HASH                       (0) //
#define BSP_FEATURE_CRYPTO_HAS_RSA                        (0) //
#define BSP_FEATURE_CRYPTO_HAS_RSA_WRAPPED                (0) //

#define BSP_FEATURE_CTSU_CTSUCHAC_REGISTER_COUNT          (5U)
#define BSP_FEATURE_CTSU_CTSUCHTRC_REGISTER_COUNT         (5U)
#define BSP_FEATURE_CTSU_HAS_TXVSEL                       (1)
#define BSP_FEATURE_CTSU_VERSION                          (2)

#define BSP_FEATURE_DAC8_HAS_CHARGEPUMP                   (0)           // Feature not available on this MCU
#define BSP_FEATURE_DAC8_HAS_DA_AD_SYNCHRONIZE            (0)           // Feature not available on this MCU
#define BSP_FEATURE_DAC8_HAS_REALTIME_MODE                (0)           // Feature not available on this MCU
#define BSP_FEATURE_DAC8_MAX_CHANNELS                     (0)           // Feature not available on this MCU

#define BSP_FEATURE_DAC_HAS_CHARGEPUMP                    (0U)          // Feature not available on this MCU
#define BSP_FEATURE_DAC_HAS_DAVREFCR                      (0U)          // Feature not available on this MCU
#define BSP_FEATURE_DAC_HAS_OUTPUT_AMPLIFIER              (0U)          // Feature not available on this MCU
#define BSP_FEATURE_DAC_MAX_CHANNELS                      (0U)          // Feature not available on this MCU

#define BSP_FEATURE_DMAC_MAX_CHANNEL                      (0)           // Feature not available on this MCU

#define BSP_FEATURE_DWT_CYCCNT                            (0U)

#define BSP_FEATURE_ELC_PERIPHERAL_MASK                   (0x0004C30FU) // Positions of event link set registers (ELSRs) available on this MCU

#define BSP_FEATURE_ETHER_FIFO_DEPTH                      (0)           // Feature not available on this MCU
#define BSP_FEATURE_ETHER_MAX_CHANNELS                    (0)           // Feature not available on this MCU

#define BSP_FEATURE_FLASH_DATA_FLASH_START                (0x40100000U)
#define BSP_FEATURE_FLASH_HP_CF_REGION0_BLOCK_SIZE        (0)           // Feature not available on this MCU
#define BSP_FEATURE_FLASH_HP_CF_REGION0_SIZE              (0)           // Feature not available on this MCU
#define BSP_FEATURE_FLASH_HP_CF_REGION1_BLOCK_SIZE        (0)           // Feature not available on this MCU
#define BSP_FEATURE_FLASH_HP_CF_WRITE_SIZE                (0)           // Feature not available on this MCU
#define BSP_FEATURE_FLASH_HP_DF_BLOCK_SIZE                (0)           // Feature not available on this MCU
#define BSP_FEATURE_FLASH_HP_DF_WRITE_SIZE                (0)           // Feature not available on this MCU
#define BSP_FEATURE_FLASH_HP_HAS_FMEPROT                  (0)           // Feature not available on this MCU
#define BSP_FEATURE_FLASH_HP_VERSION                      (0)           // Feature not available on this MCU
#define BSP_FEATURE_FLASH_LP_AWS_FAW_MASK                 (0x7FFU)
#define BSP_FEATURE_FLASH_LP_AWS_FAW_SHIFT                (11)
#define BSP_FEATURE_FLASH_LP_CF_BLOCK_SIZE                (0x800U)
#define BSP_FEATURE_FLASH_LP_CF_WRITE_SIZE                (4)
#define BSP_FEATURE_FLASH_LP_DF_BLOCK_SIZE                (0x400U)
#define BSP_FEATURE_FLASH_LP_DF_WRITE_SIZE                (1)
#define BSP_FEATURE_FLASH_LP_FLASH_CLOCK_SRC              ((fsp_priv_clock_t) FSP_PRIV_CLOCK_ICLK) // RA2E1 Flash uses ICLK
#define BSP_FEATURE_FLASH_LP_VERSION                      (4)
#define BSP_FEATURE_FLASH_SUPPORTS_ACCESS_WINDOW          (1)
#define BSP_FEATURE_FLASH_SUPPORTS_ID_CODE                (1)

#define BSP_FEATURE_GPTEH_CHANNEL_MASK                    (0)

#define BSP_FEATURE_GPTE_CHANNEL_MASK                     (0)

#define BSP_FEATURE_GPT_32BIT_CHANNEL_MASK                (0x1)
#define BSP_FEATURE_GPT_VALID_CHANNEL_MASK                (0x3F1)

#define BSP_FEATURE_ICU_HAS_WUPEN1                        (0) // Feature not available on this MCU
#define BSP_FEATURE_ICU_IRQ_CHANNELS_MASK                 (0x0FU)
#define BSP_FEATURE_ICU_WUPEN_MASK                        (0xF38F00FFU)

#define BSP_FEATURE_IIC_FAST_MODE_PLUS                    (0U)
#define BSP_FEATURE_IIC_VALID_CHANNEL_MASK                (1)

#define BSP_FEATURE_IOPORT_ELC_PORTS                      (2)
#define BSP_FEATURE_IOPORT_HAS_ETHERNET                   (0U)

#define BSP_FEATURE_LPM_CHANGE_MSTP_ARRAY                 (0) // Feature not available on this MCU
#define BSP_FEATURE_LPM_CHANGE_MSTP_REQUIRED              (0U)
#define BSP_FEATURE_LPM_DPSIEGR_MASK                      (0) // Feature not available on this MCU
#define BSP_FEATURE_LPM_DPSIER_MASK                       (0) // Feature not available on this MCU
#define BSP_FEATURE_LPM_HAS_DEEP_STANDBY                  (0U)
#define BSP_FEATURE_LPM_HAS_SBYCR_OPE                     (0U)
#define BSP_FEATURE_LPM_HAS_SNZEDCR1                      (0) // Feature not available on this MCU
#define BSP_FEATURE_LPM_HAS_SNZREQCR1                     (0) // Feature not available on this MCU
#define BSP_FEATURE_LPM_HAS_STCONR                        (0) // Feature not available on this MCU
#define BSP_FEATURE_LPM_SBYCR_WRITE1_B14                  (0)
#define BSP_FEATURE_LPM_SNZEDCR_MASK                      (0x0000009FU)
#define BSP_FEATURE_LPM_SNZREQCR_MASK                     (0x738200FFU)

#define BSP_FEATURE_LVD_HAS_DIGITAL_FILTER                (0U)
#define BSP_FEATURE_LVD_HAS_LVDLVLR                       (1)
#define BSP_FEATURE_LVD_MONITOR_1_HI_THRESHOLD            (LVD_THRESHOLD_MONITOR_1_LEVEL_4_29V) // 4.29V
#define BSP_FEATURE_LVD_MONITOR_1_LOW_THRESHOLD           (LVD_THRESHOLD_MONITOR_1_LEVEL_1_65V) // 1.65V
#define BSP_FEATURE_LVD_MONITOR_2_HI_THRESHOLD            (LVD_THRESHOLD_MONITOR_2_LEVEL_4_29V) // 4.29V
#define BSP_FEATURE_LVD_MONITOR_2_LOW_THRESHOLD           (LVD_THRESHOLD_MONITOR_2_LEVEL_3_84V) // 3.84V
#define BSP_FEATURE_LVD_STABILIZATION_TIME_US             (300U)                                // Time in microseconds required for LVD to stabilize

#define BSP_FEATURE_OPAMP_BASE_ADDRESS                    (0)                                   // Feature not available on this MCU
#define BSP_FEATURE_OPAMP_HAS_MIDDLE_SPEED                (0)                                   // Feature not available on this MCU
#define BSP_FEATURE_OPAMP_HAS_SWITCHES                    (0)                                   // Feature not available on this MCU
#define BSP_FEATURE_OPAMP_HAS_THIRD_CHANNEL               (0)                                   // Feature not available on this MCU
#define BSP_FEATURE_OPAMP_MIN_WAIT_TIME_HS_US             (4U)
#define BSP_FEATURE_OPAMP_MIN_WAIT_TIME_LP_US             (100U)                                // This information comes from the Electrical Characteristics chapter of the hardware manual.
#define BSP_FEATURE_OPAMP_MIN_WAIT_TIME_MS_US             (10U)
#define BSP_FEATURE_OPAMP_TRIM_CAPABLE                    (0)                                   // Feature not available on this MCU
#define BSP_FEATURE_OPAMP_VARIANT_CHANNEL_MASK            (0)                                   // Feature not available on this MCU

#define BSP_FEATURE_OSPI_DEVICE_0_START_ADDRESS           (0x0U)
#define BSP_FEATURE_OSPI_DEVICE_1_START_ADDRESS           (0x0U)

#define BSP_FEATURE_POEG_CHANNEL_MASK                     (0x3U)

#define BSP_FEATURE_SCI_ADDRESS_MATCH_CHANNELS            (BSP_FEATURE_SCI_CHANNELS) // Feature not available on this MCU
#define BSP_FEATURE_SCI_CHANNELS                          (0x207U)
#define BSP_FEATURE_SCI_CLOCK                             (FSP_PRIV_CLOCK_PCLKB)
#define BSP_FEATURE_SCI_UART_FIFO_CHANNELS                (0x1U)
#define BSP_FEATURE_SCI_UART_FIFO_DEPTH                   (16U)

#define BSP_FEATURE_SDHI_HAS_CARD_DETECTION               (0) // Feature not available on this MCU
#define BSP_FEATURE_SDHI_SUPPORTS_8_BIT_MMC               (0) // Feature not available on this MCU
#define BSP_FEATURE_SDHI_VALID_CHANNEL_MASK               (0) // Feature not available on this MCU
#define BSP_FEATURE_SDHI_CLOCK                            (FSP_PRIV_CLOCK_PCLKA)
#define BSP_FEATURE_SDHI_MIN_CLOCK_DIVISION_SHIFT         (0) // Feature not available on this MCU

#define BSP_FEATURE_SDRAM_START_ADDRESS                   (0x0U)

#define BSP_FEATURE_SLCDC_HAS_8_TIME_SLICE                (0) // Feature not available on this MCU
#define BSP_FEATURE_SLCDC_HAS_INTERNAL_VOLT_GEN           (0) // Feature not available on this MCU
#define BSP_FEATURE_SLCDC_MAX_NUM_SEG                     (0) // Feature not available on this MCU

#define BSP_FEATURE_SPI_CLK                               (FSP_PRIV_CLOCK_PCLKB)
#define BSP_FEATURE_SPI_HAS_BYTE_SWAP                     (1U)
#define BSP_FEATURE_SPI_HAS_SPCR3                         (0) // Feature not available on this MCU
#define BSP_FEATURE_SPI_HAS_SSL_LEVEL_KEEP                (0U)
#define BSP_FEATURE_SPI_MAX_CHANNEL                       (1U)

#define BSP_FEATURE_SSI_FIFO_NUM_STAGES                   (0) // Feature not available on this MCU
#define BSP_FEATURE_SSI_VALID_CHANNEL_MASK                (0) // Feature not available on this MCU

#define BSP_FEATURE_TRNG_HAS_MODULE_STOP                  (1U)

#define BSP_FEATURE_TZ_HAS_TRUSTZONE                      (0) // Feature not available on this MCU

#endif
