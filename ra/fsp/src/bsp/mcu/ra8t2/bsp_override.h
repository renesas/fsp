/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @addtogroup BSP_MCU_RA8T2
 * @{
 **********************************************************************************************************************/

/** @} (end addtogroup BSP_MCU_RA8T2) */

#ifndef BSP_OVERRIDE_H
#define BSP_OVERRIDE_H

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* Define overrides required for this MCU. */

#define BSP_OVERRIDE_CGC_DIVIDER_CFG_T
#define BSP_OVERRIDE_CGC_SYS_CLOCK_DIV_T
#define BSP_OVERRIDE_GROUP_IRQ_T
#define BSP_OVERRIDE_LPM_SNOOZE_CANCEL_T
#define BSP_OVERRIDE_IOPORT_PERIPHERAL_T
#define BSP_OVERRIDE_LPM_STANDBY_WAKE_SOURCE_T
#define BSP_OVERRIDE_LVD_PERIPHERAL_T
#define BSP_OVERRIDE_POEG_STATE_T
#define BSP_OVERRIDE_POEG_TRIGGER_T

/* Override definitions. */

/* Private definition to set enumeration values. */
#define IOPORT_PRV_PFS_PSEL_OFFSET    (24)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** System clock divider values - The individually selectable divider of each of the system clocks, ICLK, BCLK, FCLK,
 * PCLKS A-D.  */
typedef enum e_cgc_sys_clock_div
{
    CGC_SYS_CLOCK_DIV_1  = 0,          ///< System clock divided by 1
    CGC_SYS_CLOCK_DIV_2  = 1,          ///< System clock divided by 2
    CGC_SYS_CLOCK_DIV_4  = 2,          ///< System clock divided by 4
    CGC_SYS_CLOCK_DIV_8  = 3,          ///< System clock divided by 8
    CGC_SYS_CLOCK_DIV_16 = 4,          ///< System clock divided by 16
    CGC_SYS_CLOCK_DIV_32 = 5,          ///< System clock divided by 32
    CGC_SYS_CLOCK_DIV_64 = 6,          ///< System clock divided by 64
    CGC_SYS_CLOCK_DIV_3  = 8,          ///< System clock divided by 3
    CGC_SYS_CLOCK_DIV_6  = 9,          ///< System clock divided by 6
    CGC_SYS_CLOCK_DIV_12 = 10,         ///< System clock divided by 12
    CGC_SYS_CLOCK_DIV_24 = 11,         ///< System clock divided by 24
} cgc_sys_clock_div_t;

/** Clock configuration structure - Used as an input parameter to the @ref cgc_api_t::systemClockSet and @ref cgc_api_t::systemClockGet
 * functions. */
typedef struct st_cgc_divider_cfg
{
    union
    {
        uint32_t sckdivcr_w;                   ///< System clock Division control register

        struct
        {
            cgc_sys_clock_div_t pclkd_div : 4; ///< Divider value for PCLKD
            cgc_sys_clock_div_t pclkc_div : 4; ///< Divider value for PCLKC
            cgc_sys_clock_div_t pclkb_div : 4; ///< Divider value for PCLKB
            cgc_sys_clock_div_t pclka_div : 4; ///< Divider value for PCLKA
            cgc_sys_clock_div_t bclk_div  : 4; ///< Divider value for BCLK
            cgc_sys_clock_div_t pclke_div : 4; ///< Divider value for PCLKE
            cgc_sys_clock_div_t iclk_div  : 4; ///< Divider value for ICLK
            cgc_sys_clock_div_t fclk_div  : 4; ///< Divider value for FCLK
        } sckdivcr_b;
    };

    union
    {
        uint16_t sckdivcr2;                      ///< System clock Division control register 2

        struct
        {
            cgc_sys_clock_div_t cpuclk_div  : 4; ///< Divider value for CPUCLK0
            cgc_sys_clock_div_t cpuclk1_div : 4; ///< Divider value for CPUCLK1
            cgc_sys_clock_div_t npuclk_div  : 4; ///< Divider value for NPUCLK
            cgc_sys_clock_div_t mriclk_div  : 4; ///< Divider value for MRICLK
        } sckdivcr2_b;
    };
} cgc_divider_cfg_t;

/* Which interrupts can have callbacks registered. */
typedef enum e_bsp_grp_irq
{
    BSP_GRP_IRQ_IWDT_ERROR       = 0,  ///< IWDT underflow/refresh error has occurred
    BSP_GRP_IRQ_WDT_ERROR        = 1,  ///< WDT underflow/refresh error has occurred
    BSP_GRP_IRQ_LVD1             = 2,  ///< Voltage monitoring 1 interrupt
    BSP_GRP_IRQ_LVD2             = 3,  ///< Voltage monitoring 2 interrupt
    BSP_GRP_IRQ_SOSC_STOP_DETECT = 5,  ///< Sub Oscillation stop is detected
    BSP_GRP_IRQ_OSC_STOP_DETECT  = 6,  ///< Oscillation stop is detected
    BSP_GRP_IRQ_NMI_PIN          = 7,  ///< NMI Pin interrupt
    BSP_GRP_IRQ_MPU_BUS_TZF      = 12, ///< MPU Bus or TrustZone Filter Error
    BSP_GRP_IRQ_COMMON_MEMORY    = 13, ///< SRAM ECC or SRAM Parity Error
    BSP_GRP_IRQ_LOCAL_MEMORY     = 14, ///< Local Memory Error
    BSP_GRP_IRQ_LOCKUP           = 15, ///< LockUp Error
    BSP_GRP_IRQ_FPU              = 16, ///< FPU Exception
    BSP_GRP_IRQ_MRC              = 17, ///< MRAM Code read error
    BSP_GRP_IRQ_MRE              = 18, ///< MRAM Extra read error
    BSP_GRP_IRQ_IPC              = 20, ///< IPC Interrupt
} bsp_grp_irq_t;

/** Wake from deep sleep or standby mode sources, does not apply to sleep or deep standby modes */
typedef enum e_lpm_standby_wake_source
{
    LPM_STANDBY_WAKE_SOURCE_IRQ0    = 0x00000001ULL,         ///< IRQ0
    LPM_STANDBY_WAKE_SOURCE_IRQ1    = 0x00000002ULL,         ///< IRQ1
    LPM_STANDBY_WAKE_SOURCE_IRQ2    = 0x00000004ULL,         ///< IRQ2
    LPM_STANDBY_WAKE_SOURCE_IRQ3    = 0x00000008ULL,         ///< IRQ3
    LPM_STANDBY_WAKE_SOURCE_IRQ4    = 0x00000010ULL,         ///< IRQ4
    LPM_STANDBY_WAKE_SOURCE_IRQ5    = 0x00000020ULL,         ///< IRQ5
    LPM_STANDBY_WAKE_SOURCE_IRQ6    = 0x00000040ULL,         ///< IRQ6
    LPM_STANDBY_WAKE_SOURCE_IRQ7    = 0x00000080ULL,         ///< IRQ7
    LPM_STANDBY_WAKE_SOURCE_IRQ8    = 0x00000100ULL,         ///< IRQ8
    LPM_STANDBY_WAKE_SOURCE_IRQ9    = 0x00000200ULL,         ///< IRQ9
    LPM_STANDBY_WAKE_SOURCE_IRQ10   = 0x00000400ULL,         ///< IRQ10
    LPM_STANDBY_WAKE_SOURCE_IRQ11   = 0x00000800ULL,         ///< IRQ11
    LPM_STANDBY_WAKE_SOURCE_IRQ12   = 0x00001000ULL,         ///< IRQ12
    LPM_STANDBY_WAKE_SOURCE_IRQ13   = 0x00002000ULL,         ///< IRQ13
    LPM_STANDBY_WAKE_SOURCE_IRQ14   = 0x00004000ULL,         ///< IRQ14
    LPM_STANDBY_WAKE_SOURCE_IRQ15   = 0x00008000ULL,         ///< IRQ15
    LPM_STANDBY_WAKE_SOURCE_IWDT    = 0x00010000ULL,         ///< Independent watchdog interrupt
    LPM_STANDBY_WAKE_SOURCE_LVD1    = 0x00040000ULL,         ///< Low Voltage Detection 1 interrupt
    LPM_STANDBY_WAKE_SOURCE_LVD2    = 0x00080000ULL,         ///< Low Voltage Detection 2 interrupt
    LPM_STANDBY_WAKE_SOURCE_VBATT   = 0x00100000ULL,         ///< VBATT Monitor interrupt
    LPM_STANDBY_WAKE_SOURCE_RTCALM  = 0x01000000ULL,         ///< RTC Alarm interrupt
    LPM_STANDBY_WAKE_SOURCE_RTCPRD  = 0x02000000ULL,         ///< RTC Period interrupt
    LPM_STANDBY_WAKE_SOURCE_USBFS   = 0x08000000ULL,         ///< USB Full-speed interrupt
    LPM_STANDBY_WAKE_SOURCE_AGT1UD  = 0x10000000ULL,         ///< AGT1 Underflow interrupt
    LPM_STANDBY_WAKE_SOURCE_AGT1CA  = 0x20000000ULL,         ///< AGT1 Compare Match A interrupt
    LPM_STANDBY_WAKE_SOURCE_AGT1CB  = 0x40000000ULL,         ///< AGT1 Compare Match B interrupt
    LPM_STANDBY_WAKE_SOURCE_IIC0    = 0x80000000ULL,         ///< I2C 0 interrupt
    LPM_STANDBY_WAKE_SOURCE_COMPHS0 = 0x800000000ULL,        ///< Comparator-HS0 Interrupt
    LPM_STANDBY_WAKE_SOURCE_SOSTD   = 0x8000000000ULL,       ///< SOSTD interrupt
    LPM_STANDBY_WAKE_SOURCE_ULP0U   = 0x10000000000ULL,      ///< ULPT0 Underflow Interrupt
    LPM_STANDBY_WAKE_SOURCE_ULP0A   = 0x20000000000ULL,      ///< ULPT0 Compare Match A Interrupt
    LPM_STANDBY_WAKE_SOURCE_ULP0B   = 0x40000000000ULL,      ///< ULPT0 Compare Match B Interrupt
    LPM_STANDBY_WAKE_SOURCE_I3C0    = 0x80000000000ULL,      ///< I3C0 address match interrupt
    LPM_STANDBY_WAKE_SOURCE_ULP1U   = 0x100000000000ULL,     ///< ULPT1 Underflow Interrupt
    LPM_STANDBY_WAKE_SOURCE_ULP1A   = 0x200000000000ULL,     ///< ULPT1 Compare Match A Interrupt
    LPM_STANDBY_WAKE_SOURCE_ULP1B   = 0x400000000000ULL,     ///< ULPT1 Compare Match B Interrupt
    LPM_STANDBY_WAKE_SOURCE_IRQ16   = 0x1000000000000ULL,    ///< IRQ16
    LPM_STANDBY_WAKE_SOURCE_IRQ17   = 0x2000000000000ULL,    ///< IRQ17
    LPM_STANDBY_WAKE_SOURCE_IRQ18   = 0x4000000000000ULL,    ///< IRQ18
    LPM_STANDBY_WAKE_SOURCE_IRQ19   = 0x8000000000000ULL,    ///< IRQ19
    LPM_STANDBY_WAKE_SOURCE_IRQ20   = 0x10000000000000ULL,   ///< IRQ20
    LPM_STANDBY_WAKE_SOURCE_IRQ21   = 0x20000000000000ULL,   ///< IRQ21
    LPM_STANDBY_WAKE_SOURCE_IRQ22   = 0x40000000000000ULL,   ///< IRQ22
    LPM_STANDBY_WAKE_SOURCE_IRQ23   = 0x80000000000000ULL,   ///< IRQ23
    LPM_STANDBY_WAKE_SOURCE_IRQ24   = 0x100000000000000ULL,  ///< IRQ24
    LPM_STANDBY_WAKE_SOURCE_IRQ25   = 0x200000000000000ULL,  ///< IRQ25
    LPM_STANDBY_WAKE_SOURCE_IRQ26   = 0x400000000000000ULL,  ///< IRQ26
    LPM_STANDBY_WAKE_SOURCE_IRQ27   = 0x800000000000000ULL,  ///< IRQ27
    LPM_STANDBY_WAKE_SOURCE_IRQ28   = 0x1000000000000000ULL, ///< IRQ28
    LPM_STANDBY_WAKE_SOURCE_IRQ29   = 0x2000000000000000ULL, ///< IRQ29
    LPM_STANDBY_WAKE_SOURCE_IRQ30   = 0x4000000000000000ULL, ///< IRQ30
    LPM_STANDBY_WAKE_SOURCE_IRQ31   = 0x8000000000000000ULL, ///< IRQ31
} lpm_standby_wake_source_t;

typedef uint64_t lpm_standby_wake_source_bits_t;

/** Snooze cancel control */
typedef enum e_lpm_snooze_cancel
{
    LPM_SNOOZE_CANCEL_SOURCE_NONE = 0, ///< No snooze cancel source
} lpm_snooze_cancel_t;

/** Superset of all peripheral functions.  */
typedef enum e_ioport_peripheral
{
    /** Pin will functions as an IO pin */
    IOPORT_PERIPHERAL_IO = 0x00,

    /** Pin will function as a DEBUG pin */
    IOPORT_PERIPHERAL_DEBUG = (0x00UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as an AGT peripheral pin */
    IOPORT_PERIPHERAL_AGT = (0x01UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as an AGT peripheral pin */
    IOPORT_PERIPHERAL_AGTW = (0x01UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as an AGT peripheral pin */
    IOPORT_PERIPHERAL_AGT1 = (0x18UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a GPT peripheral pin */
    IOPORT_PERIPHERAL_GPT0 = (0x02UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a GPT peripheral pin */
    IOPORT_PERIPHERAL_GPT1 = (0x03UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as an SCI peripheral pin */
    IOPORT_PERIPHERAL_SCI0_2_4_6_8 = (0x04UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as an SCI peripheral pin */
    IOPORT_PERIPHERAL_SCI1_3_5_7_9 = (0x05UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a SPI peripheral pin */
    IOPORT_PERIPHERAL_SPI = (0x06UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a IIC peripheral pin */
    IOPORT_PERIPHERAL_IIC = (0x07UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a KEY peripheral pin */
    IOPORT_PERIPHERAL_KEY = (0x08UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a clock/comparator/RTC peripheral pin */
    IOPORT_PERIPHERAL_CLKOUT_COMP_RTC = (0x09UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a CAC/ADC peripheral pin */
    IOPORT_PERIPHERAL_CAC_AD = (0x0AUL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a BUS peripheral pin */
    IOPORT_PERIPHERAL_BUS = (0x0BUL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a CTSU peripheral pin */
    IOPORT_PERIPHERAL_CTSU = (0x0CUL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a CMPHS peripheral pin */
    IOPORT_PERIPHERAL_ACMPHS = (0x0CUL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a segment LCD peripheral pin */
    IOPORT_PERIPHERAL_LCDC = (0x0DUL << IOPORT_PRV_PFS_PSEL_OFFSET),

#if BSP_FEATURE_SCI_UART_DE_IS_INVERTED

    /** Pin will function as an SCI peripheral DEn pin */
    IOPORT_PERIPHERAL_DE_SCI1_3_5_7_9 = (0x0DUL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as an SCI DEn peripheral pin */
    IOPORT_PERIPHERAL_DE_SCI0_2_4_6_8 = (0x0EUL << IOPORT_PRV_PFS_PSEL_OFFSET),
#else

    /** Pin will function as an SCI peripheral DEn pin */
    IOPORT_PERIPHERAL_DE_SCI0_2_4_6_8 = (0x0DUL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as an SCI DEn peripheral pin */
    IOPORT_PERIPHERAL_DE_SCI1_3_5_7_9 = (0x0EUL << IOPORT_PRV_PFS_PSEL_OFFSET),
#endif

    /** Pin will function as a DALI peripheral pin */
    IOPORT_PERIPHERAL_DALI = (0x0EUL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a CEU peripheral pin */
    IOPORT_PERIPHERAL_CEU = (0x0FUL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a CAN peripheral pin */
    IOPORT_PERIPHERAL_CAN = (0x10UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a QSPI peripheral pin */
    IOPORT_PERIPHERAL_QSPI = (0x11UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as an SSI peripheral pin */
    IOPORT_PERIPHERAL_SSI = (0x12UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a USB full speed peripheral pin */
    IOPORT_PERIPHERAL_USB_FS = (0x13UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a USB high speed peripheral pin */
    IOPORT_PERIPHERAL_USB_HS = (0x14UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a GPT peripheral pin */
    IOPORT_PERIPHERAL_GPT2 = (0x14UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as an SD/MMC peripheral pin */
    IOPORT_PERIPHERAL_SDHI_MMC = (0x15UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a GPT peripheral pin */
    IOPORT_PERIPHERAL_GPT3 = (0x15UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as an Ethernet MMI peripheral pin */
    IOPORT_PERIPHERAL_ETHER_MII = (0x16UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a GPT peripheral pin */
    IOPORT_PERIPHERAL_GPT4 = (0x16UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as an Ethernet RMMI peripheral pin */
    IOPORT_PERIPHERAL_ETHER_RMII = (0x17UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a PDC peripheral pin */
    IOPORT_PERIPHERAL_PDC = (0x18UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a graphics LCD peripheral pin */
    IOPORT_PERIPHERAL_LCD_GRAPHICS = (0x19UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a CAC peripheral pin */
    IOPORT_PERIPHERAL_CAC = (0x19UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a debug trace peripheral pin */
    IOPORT_PERIPHERAL_TRACE = (0x1AUL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a OSPI peripheral pin */
    IOPORT_PERIPHERAL_OSPI = (0x1CUL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a CEC peripheral pin */
    IOPORT_PERIPHERAL_CEC = (0x1DUL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a PGAOUT peripheral pin */
    IOPORT_PERIPHERAL_PGAOUT0 = (0x1DUL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a PGAOUT peripheral pin */
    IOPORT_PERIPHERAL_PGAOUT1 = (0x1EUL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a ULPT peripheral pin */
    IOPORT_PERIPHERAL_ULPT = (0x1EUL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a MIPI DSI peripheral pin */
    IOPORT_PERIPHERAL_MIPI = (0x1FUL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a RGMII peripheral pin */
    IOPORT_PERIPHERAL_ETHER_RGMII = (0x18UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a ETHERNET slave controller peripheral pin */
    IOPORT_PERIPHERAL_ESC = (0x1AUL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a PDM peripheral pin */
    IOPORT_PERIPHERAL_PDM = (0x1BUL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a DSMIF peripheral pin */
    IOPORT_PERIPHERAL_DSMIF = (0x08UL << IOPORT_PRV_PFS_PSEL_OFFSET),
} ioport_peripheral_t;

/** The thresholds supported by each MCU are in the MCU User's Manual as well as
 *  in the r_lvd module description on the stack tab of the RA project. */
typedef enum
{
    LVD_THRESHOLD_MONITOR_LEVEL_3_86V = 0x03UL, ///< 3.86V
    LVD_THRESHOLD_MONITOR_LEVEL_3_14V = 0x04UL, ///< 3.14V
    LVD_THRESHOLD_MONITOR_LEVEL_3_10V = 0x05UL, ///< 3.10V
    LVD_THRESHOLD_MONITOR_LEVEL_3_08V = 0x06UL, ///< 3.08V
    LVD_THRESHOLD_MONITOR_LEVEL_2_85V = 0x07UL, ///< 2.85V
    LVD_THRESHOLD_MONITOR_LEVEL_2_83V = 0x08UL, ///< 2.83V
    LVD_THRESHOLD_MONITOR_LEVEL_2_80V = 0x09UL, ///< 2.80V
    LVD_THRESHOLD_MONITOR_LEVEL_2_62V = 0x0AUL, ///< 2.62V
    LVD_THRESHOLD_MONITOR_LEVEL_2_33V = 0x0BUL, ///< 2.33V
    LVD_THRESHOLD_MONITOR_LEVEL_1_90V = 0x0CUL, ///< 1.90V
    LVD_THRESHOLD_MONITOR_LEVEL_1_86V = 0x0DUL, ///< 1.86V
    LVD_THRESHOLD_MONITOR_LEVEL_1_74V = 0x0EUL, ///< 1.74V
    LVD_THRESHOLD_MONITOR_LEVEL_1_71V = 0x0FUL, ///< 1.71V
    LVD_THRESHOLD_NOT_AVAILABLE       = 0xFFUL, ///< Not Used
} lvd_threshold_t;

/** POEG states. */
typedef enum e_poeg_state
{
    POEG_STATE_NO_DISABLE_REQUEST                = 0,        ///< GPT output is not disabled by POEG
    POEG_STATE_PIN_DISABLE_REQUEST               = 1U << 0,  ///< GPT output disabled due to GTETRG pin level
    POEG_STATE_GPT_OR_COMPARATOR_DISABLE_REQUEST = 1U << 1,  ///< GPT output disabled due to high speed analog comparator or GPT
    POEG_STATE_OSCILLATION_STOP_DISABLE_REQUEST  = 1U << 2,  ///< GPT output disabled due to main oscillator stop
    POEG_STATE_SOFTWARE_STOP_DISABLE_REQUEST     = 1U << 3,  ///< GPT output disabled due to poeg_api_t::outputDisable()
    POEG_STATE_DSMIF0_DISABLE_REQUEST            = 1U << 24, ///< GPT output disabled due to DSMIF0
    POEG_STATE_DSMIF1_DISABLE_REQUEST            = 1U << 25, ///< GPT output disabled due to DSMIF1

    /** GPT output disable request active from the GTETRG pin. If a filter is used, this flag represents the state of
     * the filtered input. */
    POEG_STATE_PIN_DISABLE_REQUEST_ACTIVE = 1U << 16,
} poeg_state_t;

/** Triggers that will disable GPT output pins. */
typedef enum e_poeg_trigger
{
    /** Software disable is always supported with POEG. Select this option if no other triggers are used. */
    POEG_TRIGGER_SOFTWARE         = 0U,
    POEG_TRIGGER_PIN              = 1U << 0,  ///< Disable GPT output based on GTETRG input level
    POEG_TRIGGER_GPT_OUTPUT_LEVEL = 1U << 1,  ///< Disable GPT output based on GPT output pin levels
    POEG_TRIGGER_OSCILLATION_STOP = 1U << 2,  ///< Disable GPT output based on main oscillator stop
    POEG_TRIGGER_ACMPHS0          = 1U << 4,  ///< Disable GPT output based on ACMPHS0 comparator result
    POEG_TRIGGER_ACMPHS1          = 1U << 5,  ///< Disable GPT output based on ACMPHS1 comparator result
    POEG_TRIGGER_ACMPHS2          = 1U << 6,  ///< Disable GPT output based on ACMPHS2 comparator result
    POEG_TRIGGER_ACMPHS3          = 1U << 7,  ///< Disable GPT output based on ACMPHS3 comparator result
    POEG_TRIGGER_ACMPHS4          = 1U << 8,  ///< Disable GPT output based on ACMPHS4 comparator result
    POEG_TRIGGER_ACMPHS5          = 1U << 9,  ///< Disable GPT output based on ACMPHS5 comparator result
    POEG_TRIGGER_DSMIF0           = 1U << 22, ///< Disable GPT output based on DSMIF0 overcurrent detection window notification
    POEG_TRIGGER_DSMIF1           = 1U << 23, ///< Disable GPT output based on DSMIF1 overcurrent detection window notification
} poeg_trigger_t;

/***********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/

#endif
