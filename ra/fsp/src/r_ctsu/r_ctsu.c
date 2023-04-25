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
#ifdef QE_TOUCH_CONFIGURATION
 #include "qe_touch_define.h"
#endif
#include "r_ctsu.h"
#include "r_ioport.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/** "CTSU" in ASCII, used to determine if device is open. */
#define CTSU_OPEN                            (0x43545355U)

/* Macro definitions for register setting */
#define CTSU_PON_OFF                         (0)    // CTSU hardware macro power off
#define CTSU_PON_ON                          (1)    // CTSU hardware macro power on
#define CTSU_CSW_OFF                         (0)    // Capacitance switch turned off
#define CTSU_CSW_ON                          (1)    // Capacitance switch turned on

#define CTSU_CR1_MODIFY_BIT                  (0xC8) // MD1, MD0, ATUNE1
#define CTSU_SOVF                            (0x20) // Overflow bit
#define CTSU_CORRECTION_AVERAGE              (32)
#define CTSU_SHIFT_AMOUNT                    (15)

#define CTSU_PCLKB_FREQ_MHZ                  (1000000)
#define CTSU_PCLKB_FREQ_RANGE1               (32)
#define CTSU_PCLKB_FREQ_RANGE2               (64)
#define CTSU_PCLKB_FREQ_RANGE3               (128)
#define CTSU_WAIT_TIME                       (500)

/* Macro definitions for initial offset tuning */
#define CTSU_TUNING_MAX                      (0x03FF)
#define CTSU_TUNING_MIN                      (0x0000)
#define CTSU_TUNING_VALUE_SELF               (15360)
#define CTSU_TUNING_VALUE_MUTUAL             (10240)

#define CTSU_CFG_DECIMAL_POINT               (16)
#define CTSU_CFG_DECIMAL_POINT_MASK          (0x0000FFFF)

#if (BSP_FEATURE_CTSU_VERSION == 2)
 #define CTSU_SST_RECOMMEND                  (0x1F) // The recommend value of SST
 #define CTSU_SST_RECOMMEND_CURRENT          (0x3F) // The recommend value of SST with current
 #define CTSU_SNUM_RECOMMEND                 (0x07) // The value of SNUM should be fixed
 #define CTSU_SNUM_MAX                       (0xFF) // The maximum value of SNUM
 #define CTSU_ICOMP0                         (0x80) // ICOMP0 bit
 #define CTSU_ICOMP1                         (0x40) // ICOMP1 bit
 #define CTSU_ICOMPRST                       (0x20) // ICOMPRST bit
 #define CTSU_CR0_MODIFY_BIT                 (0xC0) // TXVSEL
 #define CTSU_CR2_MODIFY_BIT                 (0x33) // POSEL, ATUNE2, MD2
 #define CTSU_SUADJ_MAX                      (0xFF) // The maximum value of SUADJx
 #define CTSU_SUADJ_SSCNT_ADJ                (0x20) // The value of Adjusting SCADJx by SSCNT
 #define CTSU_MUTUAL_BUF_SIZE                (CTSU_CFG_NUM_SUMULTI * 2)

/* Macro definitions for correction */
 #if (CTSU_CFG_LOW_VOLTAGE_MODE == 0)
  #define CTSU_CORRECTION_STD_VAL            (19200) // 20UC standard value
  #define CTSU_CORRECTION_STD_UNIT           (1920)  // 2UC value
  #define CTSU_CORRECTION_STD_EXREG          (14400) // External registance standard value
  #define CTSU_CORRECTION_OFFSET_UNIT        (120)   // (7680 / 64)
 #else
  #define CTSU_CORRECTION_STD_VAL            (15360) // 20UC standard value * 0.8
  #define CTSU_CORRECTION_STD_UNIT           (1536)  // 2UC value * 0.8
  #define CTSU_CORRECTION_STD_EXREG          (11520) // External registance standard value
  #define CTSU_CORRECTION_OFFSET_UNIT        (96)    // (7680 / 64) * 0.8
 #endif
 #define CTSU_CORRECTION_SUMULTI             (0x20)  // SUMULTI step
 #define CTSU_CORRECTION_TRIMB_MAX           (0xFF)
 #define CTSU_CORRECTION_TRIMB_SIGN_BIT      (0x80)
 #define CTSU_CORRECTION_RTRIM_THRESHOLD1    (0xA0)
 #define CTSU_CORRECTION_RTRIM_THRESHOLD2    (0x50)
 #define CTSU_CORRECTION_TRIMB_THRESHOLD1    (0xC0)
 #define CTSU_CORRECTION_TRIMB_THRESHOLD2    (0x3F)
 #define CTSU_CORRECTION_BIT16               (0x10000)
 #define CTSU_CORRECTION_BIT10               (0x0400)
 #define CTSU_CORRECTION_BIT9                (0x0200)
 #define CTSU_CORRECTION_BIT8                (0x0100)
 #define CTSU_CORRECTION_BIT7                (0x0080)

 #if (CTSU_CFG_NUM_CFC != 0)
  #define CTSU_CORRCFC_CENTER_POINT          ((CTSU_CORRCFC_POINT_NUM - 1) / 2) // number of center point
  #define CTSU_CORRCFC_TS_MAX                (36)                               // Maximum number of TS terminal
  #define CTSU_CORRCFC_SHIFT8                (8)                                // Definition of 8bit shift
 #endif

 #if (CTSU_CFG_CALIB_RTRIM_SUPPORT == 1)
  #if (CTSU_CFG_LOW_VOLTAGE_MODE == 0)
   #define CTSU_CALIB_REF                    ((6144000 * 10) / CTSU_CFG_VCC_MV) // 1.5V Reference value (4096 * 1500 * 10)
  #else
   #define CTSU_CALIB_REF                    ((4915200 * 10) / CTSU_CFG_VCC_MV) // 1.2V Reference value (4096 * 1200 * 10)
  #endif
  #define CTSU_CALIB_AVERAGE_TIME            (64)                               // ADC average time
  #define CTSU_CALIB_THRESHOLD               ((0x1000 * 4) / CTSU_CFG_VCC_MV)   // RTRIM calib threshold
  #define CTSU_CALIB_CTSUSO                  (0x3C0)                            // 150uA offset
  #define CTSU_CALIB_ADSSTRL                 (0x3F)                             // Sampling time
 #endif

#endif
#if (BSP_FEATURE_CTSU_VERSION == 1)
 #define CTSU_TXVSEL                         (0x80) // TXVSEL bit
 #define CTSU_SST_RECOMMEND                  (0x10) // The value of SST should be fixed to 00010000b
 #define CTSU_SNUM_MAX                       (0x3F) // The maximum value of SNUM
 #define CTSU_SDPA_MAX                       (0x1F) // The maximum value of SDPA
 #define CTSU_PRRATIO_RECOMMEND              (3)    // Recommended setting value
 #define CTSU_PRMODE_62_PULSES               (2)    // 62 pulses (recommended setting value)
 #define CTSU_SOFF_ON                        (0)    // High-pass noise reduction function turned on
 #define CTSU_SSMOD                          (0)    // The value of SSMOD should be fixed to 00b
 #define CTSU_SSCNT                          (3)    // The value of SSCNT should be fixed to 11b
 #define CTSU_RICOA_RECOMMEND                (0x0F) // Recommended setting value
 #define CTSU_ICOG_100                       (0)    // ICOG = 100%
 #define CTSU_ICOG_66                        (1)    // ICOG = 66%
 #define CTSU_ICOG_50                        (2)    // ICOG = 50%
 #define CTSU_ICOG_40                        (3)    // ICOG = 40%
 #define CTSU_MUTUAL_BUF_SIZE                (1)

/* Macro definitions for correction */
 #if (BSP_CFG_MCU_PART_SERIES == 2) || (BSP_CFG_MCU_PART_SERIES == 4)
  #if (CTSU_CFG_LOW_VOLTAGE_MODE == 0)
   #define CTSU_CORRECTION_1ST_STD_VAL       (40960UL)       // ICOG = 66%
   #define CTSU_CORRECTION_2ND_STD_VAL       (24824)         // ICOG = 40%, (x = 40960 * 40 / 66)
  #else
   #define CTSU_CORRECTION_1ST_STD_VAL       (32768UL)       // ICOG = 66%
   #define CTSU_CORRECTION_2ND_STD_VAL       (19859)         // ICOG = 40%, (x = 40960 * 40 / 66)
  #endif
  #define CTSU_WAFER_PARAMETER               (0.96523525)
  #define CTSU_ICOG_RECOMMEND                (CTSU_ICOG_66)  // Recommended setting value
 #endif
 #if (BSP_CFG_MCU_PART_SERIES == 6)
  #define CTSU_CORRECTION_1ST_STD_VAL        (27306UL)       // ICOG = 66%, (x = 40960 * 66 / 100)
  #define CTSU_CORRECTION_2ND_STD_VAL        (16384)         // ICOG = 40%, (x = 40960 * 40 / 100)
  #define CTSU_WAFER_PARAMETER               (1)
  #define CTSU_ICOG_RECOMMEND                (CTSU_ICOG_100) // Recommended setting value
 #endif
#endif

#if (BSP_FEATURE_CTSU_VERSION == 1)
 #if (CTSU_CFG_DIAG_SUPPORT_ENABLE == 1)

  #define CTSU_DIAG_DAC_1UC             (0x10)  // 0x10 for so dac value
  #define CTSU_DIAG_DAC_2UC             (0x20)  // 0x20 for so dac value
  #define CTSU_DIAG_DAC_4UC             (0x40)  // 0x40 for so dac value
  #define CTSU_DIAG_DAC_8UC             (0x80)  // 0x80 for so dac value
  #define CTSU_DIAG_DAC_16UC            (0x100) // 0x100 for so dac value

  #define CTSU_DIAG_DAC_SO_MAX          (0x3FF) // so dac max

  #define CTSU_DIAG_DAC_INIT_VALUE      (241)   // SO value of dac test
  #define CTSU_DIAG_DAC_TARGET_VALUE    (15360) // 6UC value dac test target
  #define CTSU_DIAG_DAC_START_VALUE     (0x100) // so value dac test tuning
  #define CTSU_DAC_TEST_ATUNE1          (0x08)  // ATUNE1 bit 1
 #endif
#endif

#if (BSP_FEATURE_CTSU_VERSION == 2)
 #if (CTSU_CFG_DIAG_SUPPORT_ENABLE == 1)
  #define CTSU_DIAG_ADSSTRL             (0xff)   // ADC scan ADSSTAL register
  #define CTSU_DIAG_DAC_INIT_0          (0x0)    // so dac Lower current source0 init
  #define CTSU_DIAG_DAC_INIT_1          (0x100)  // so dac Lower current source1 init
  #define CTSU_DIAG_DAC_INIT_2          (0x200)  // so dac Lower current source2 init
  #define CTSU_DIAG_DAC_INIT_3          (0x300)  // so dac Lower current source3 init

  #define CTSU_DIAG_DAC_DATA_MAX_0      (0x0ff)  // so dac Lower current source0 max num
  #define CTSU_DIAG_DAC_DATA_MAX_1      (0x1ff)  // so dac Lower current source1 max num
  #define CTSU_DIAG_DAC_DATA_MAX_2      (0x2ff)  // so dac Lower current source2 max num
  #define CTSU_DIAG_DAC_DATA_MAX_3      (0x3ff)  // so dac Lower current source3 max num

  #define CTSU_DIAG_CURRENT_CLIB_REG    (0x818)  // current test calib register

  #define CTSU_DIAG_DELAY_MS            (5)      // delay time (ms)
  #define CTSU_DIAG_SUCLK0_REG1         (0xff00) // cco gain test SUCLK0
  #define CTSU_DIAG_SUCLK0_REG2         (0x20)   // cco gain test SUCLK0
  #define CTSU_DIAG_STCLK_FREQ          (500)    // stclk freqency (Hz)
  #define CTSU_DIAG_LVM_MASK            (0x400)  // LVmode mask
  #define CTSU_DIAG_CFC_SDPA_REG        (0x3F)   // cfc scan sdpa
  #define CTSU_DIAG_CHACA_TSMAX         (32)     // ts max chaca byte

  #define CTSU_DIAG_DAC_0BIT            (0x1)    // 0x1 for SO register
  #define CTSU_DIAG_DAC_1BIT            (0x2)    // 0x2 for SO register
  #define CTSU_DIAG_DAC_2BIT            (0x4)    // 0x4 for SO register
  #define CTSU_DIAG_DAC_3BIT            (0x8)    // 0x8 for SO register
  #define CTSU_DIAG_DAC_4BIT            (0x10)   // 0x10 for SO register
  #define CTSU_DIAG_DAC_5BIT            (0x20)   // 0x20 for SO register
  #define CTSU_DIAG_DAC_6BIT            (0x40)   // 0x40 for SO register
  #define CTSU_DIAG_DAC_7BIT            (0x80)   // 0x80 for SO register

 #endif
#endif

#if (BSP_FEATURE_CTSU_VERSION == 2)
 #if (CTSU_CFG_DTC_SUPPORT_ENABLE == 1)
  #define CTSU_TRANSFER_TUNING_CH_REG_MAX_NUM    (32)
 #endif
#endif

/***********************************************************************************************************************
 * Typedef definitions
 ***********************************************************************************************************************/
typedef struct st_ctsu_correction_calc
{
    ctsu_range_t range;
    uint16_t     snum;
    uint16_t     sdpa;
    uint16_t     cfc;
    ctsu_md_t    md;
} ctsu_correction_calc_t;

typedef struct st_ctsu_correction_multi
{
    uint16_t pri[CTSU_CFG_NUM_SUMULTI];
    uint16_t snd[CTSU_CFG_NUM_SUMULTI];
    uint32_t offset[CTSU_CFG_NUM_SUMULTI];
    uint8_t  selected_freq;
} ctsu_correction_multi_t;

#if (BSP_FEATURE_CTSU_VERSION == 1)
 #if (CTSU_CFG_DIAG_SUPPORT_ENABLE == 1)
typedef struct st_ctsu_diag_save_reg
{
    uint8_t  ctsucr0;
    uint8_t  ctsucr1;
    uint8_t  ctsusdprs;
    uint8_t  ctsusst;
    uint8_t  ctsuchac0;
    uint8_t  ctsuchac1;
    uint8_t  ctsuchac2;
    uint8_t  ctsuchtrc0;
    uint8_t  ctsuchtrc1;
    uint8_t  ctsuchtrc2;
    uint8_t  ctsudclkc;
    uint16_t ctsuerrs;
} ctsu_diag_save_reg_t;
 #endif
#endif

#if (BSP_FEATURE_CTSU_VERSION == 2)
 #if (CTSU_CFG_DIAG_SUPPORT_ENABLE == 1)
typedef struct st_ctsu_diag_save_reg
{
    uint32_t ctsucra;
    uint32_t ctsucrb;
    uint32_t ctsuchaca;
    uint32_t ctsuchacb;
    uint32_t ctsuchtrca;
    uint32_t ctsuchtrcb;
    uint32_t ctsumch;
    uint32_t ctsucalib;
    uint32_t ctsusuclka;
    uint32_t ctsusuclkb;
} ctsu_diag_save_reg_t;
 #endif
#endif

#if defined(__ARMCC_VERSION) || defined(__ICCARM__)
typedef void (BSP_CMSE_NONSECURE_CALL * ctsu_prv_ns_callback)(ctsu_callback_args_t * p_args);
#elif defined(__GNUC__)
typedef BSP_CMSE_NONSECURE_CALL void (*volatile ctsu_prv_ns_callback)(ctsu_callback_args_t * p_args);
#endif

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
#if (CTSU_CFG_DTC_SUPPORT_ENABLE == 1)
static fsp_err_t ctsu_transfer_open(ctsu_instance_ctrl_t * const p_instance_ctrl);
static fsp_err_t ctsu_transfer_close(ctsu_instance_ctrl_t * const p_instance_ctrl);
static fsp_err_t ctsu_transfer_configure(ctsu_instance_ctrl_t * const p_instance_ctrl);

 #if (BSP_FEATURE_CTSU_VERSION == 2)
  #if (CTSU_CFG_NUM_MUTUAL_ELEMENTS != 0)
static void ctsu_transer_count_element(uint32_t element_mask, uint16_t * num_element);

  #endif
 #endif
#endif
static void ctsu_initial_offset_tuning(ctsu_instance_ctrl_t * const p_instance_ctrl);
static void ctsu_moving_average(ctsu_data_t * p_average, uint16_t new_data, uint16_t average_num);
void        ctsu_write_isr(void);
void        ctsu_read_isr(void);
void        ctsu_end_isr(void);
void        ctsu_end_interrupt(ctsu_instance_ctrl_t * const p_instance_ctrl);
static void ctsu_correction_process(ctsu_instance_ctrl_t * const p_instance_ctrl);
static void ctsu_correction_measurement(ctsu_instance_ctrl_t * const p_instance_ctrl, uint16_t * data);
static void ctsu_correction_calc(uint16_t * correction_data, uint16_t raw_data, ctsu_correction_calc_t * p_calc);
static void ctsu_correction_exec(ctsu_instance_ctrl_t * const p_instance_ctrl);

#if (BSP_FEATURE_CTSU_VERSION == 2)
static void ctsu_correction_fleq(ctsu_correction_multi_t * p_multi, uint16_t * p_pri, uint16_t * p_snd);
static void ctsu_correction_multi(ctsu_correction_multi_t * p_multi, uint16_t * p_pri, uint16_t * p_snd);

 #if (CTSU_CFG_TEMP_CORRECTION_SUPPORT == 1)
static void      ctsu_correction_scan_start(void);
static fsp_err_t ctsu_correction_data_get(ctsu_instance_ctrl_t * const p_instance_ctrl, uint16_t * p_data);

  #if (CTSU_CFG_CALIB_RTRIM_SUPPORT == 1)
static fsp_err_t ctsu_correction_calib_rtrim(ctsu_instance_ctrl_t * const p_instance_ctrl, uint16_t * p_data);

  #endif
 #endif
 #if (CTSU_CFG_NUM_CFC != 0)
static void ctsu_corrcfc_process(ctsu_instance_ctrl_t * const p_instance_ctrl);
static void ctsu_corrcfc_measurement(ctsu_instance_ctrl_t * const p_instance_ctrl, uint16_t * data, uint8_t point_num);

 #endif
#endif

#if (BSP_FEATURE_CTSU_VERSION == 1)
 #if (CTSU_CFG_DIAG_SUPPORT_ENABLE == 1)
static void ctsu_diag_dac_initial_tuning(void);

static void ctsu_diag_ldo_over_voltage_scan_start(void);
static void ctsu_diag_oscillator_high_scan_start(void);
static void ctsu_diag_oscillator_low_scan_start(void);
static void ctsu_diag_sscg_scan_start(void);
static void ctsu_diag_dac_scan_start(ctsu_instance_ctrl_t * const p_instance_ctrl);

static void ctsu_diag_ldo_over_voltage_data_get(void);
static void ctsu_diag_oscillator_high_data_get(void);
static void ctsu_diag_oscillator_low_data_get(void);
static void ctsu_diag_sscg_data_get(void);
static void ctsu_diag_dac_data_get(void);

static fsp_err_t ctsu_diag_ldo_over_voltage_result(void);
static fsp_err_t ctsu_diag_oscillator_high_result(void);
static fsp_err_t ctsu_diag_oscillator_low_result(void);
static fsp_err_t ctsu_diag_sscg_result(void);
static fsp_err_t ctsu_diag_dac_result(void);

static void      ctsu_diag_scan_start1(ctsu_instance_ctrl_t * const p_instance_ctrl);
static fsp_err_t ctsu_diag_data_get1(void);

 #endif
#endif

#if (BSP_FEATURE_CTSU_VERSION == 2)
 #if (CTSU_CFG_DIAG_SUPPORT_ENABLE == 1)

static void ctsu_diag_regi_store2(void);
static void ctsu_diag_regi_restore2(void);

static fsp_err_t ctsu_diag_output_voltage_scan_start(ctsu_instance_ctrl_t * const p_instance_ctrl);
static fsp_err_t ctsu_diag_output_voltage_result(void);

static void      ctsu_diag_over_voltage_scan_start(void);
static fsp_err_t ctsu_diag_over_voltage_result(void);

static void      ctsu_diag_over_current_scan_start(void);
static fsp_err_t ctsu_diag_over_current_result(void);

static void      ctsu_diag_load_resistance_scan_start(void);
static void      ctsu_diag_load_resistance_data_get(void);
static fsp_err_t ctsu_diag_load_resistance_result(void);

static void      ctsu_diag_current_source_scan_start(void);
static void      ctsu_diag_current_source_data_get(void);
static fsp_err_t ctsu_diag_current_source_result(void);

static void      ctsu_diag_cco_gain_scan_start(void);
static void      ctsu_diag_cco_gain_data_get(void);
static fsp_err_t ctsu_diag_cco_gain_result(void);

static void      ctsu_diag_clock_recovery_scan_start(void);
static void      ctsu_diag_clock_recovery_data_get(void);
static fsp_err_t ctsu_diag_clock_recovery_result(void);

  #if (CTSU_CFG_NUM_CFC != 0)
static fsp_err_t ctsu_diag_cfc_gain_result(void);
static void      ctsu_diag_cfc_gain_scan_start(void);
static void      ctsu_diag_cfc_gain_data_get(void);

  #endif

static fsp_err_t ctsu_diag_scan_start2(ctsu_instance_ctrl_t * const p_instance_ctrl);
static fsp_err_t ctsu_diag_data_get2(uint16_t * p_data);

 #endif
#endif

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

static uint16_t g_ctsu_element_index = 0;
static uint8_t  g_ctsu_element_complete_flag[CTSU_CFG_NUM_SELF_ELEMENTS + CTSU_CFG_NUM_MUTUAL_ELEMENTS];
#if (BSP_FEATURE_CTSU_VERSION == 2)
static uint8_t g_ctsu_frequency_complete_flag[CTSU_CFG_NUM_SELF_ELEMENTS + CTSU_CFG_NUM_MUTUAL_ELEMENTS];
#endif
static int32_t       g_ctsu_tuning_diff[CTSU_CFG_NUM_SELF_ELEMENTS + CTSU_CFG_NUM_MUTUAL_ELEMENTS];
static ctsu_ctsuwr_t g_ctsu_ctsuwr[(CTSU_CFG_NUM_SELF_ELEMENTS + CTSU_CFG_NUM_MUTUAL_ELEMENTS) * CTSU_CFG_NUM_SUMULTI];
#if (CTSU_CFG_NUM_SELF_ELEMENTS != 0)
static uint16_t        g_ctsu_self_element_index = 0;
static ctsu_self_buf_t g_ctsu_self_raw[CTSU_CFG_NUM_SELF_ELEMENTS * CTSU_CFG_NUM_SUMULTI];
static uint16_t        g_ctsu_self_corr[CTSU_CFG_NUM_SELF_ELEMENTS * CTSU_CFG_NUM_SUMULTI];
static ctsu_data_t     g_ctsu_self_data[CTSU_CFG_NUM_SELF_ELEMENTS];
#endif
#if (CTSU_CFG_NUM_MUTUAL_ELEMENTS != 0)
static uint16_t          g_ctsu_mutual_element_index = 0;
static ctsu_mutual_buf_t g_ctsu_mutual_raw[CTSU_CFG_NUM_MUTUAL_ELEMENTS * CTSU_MUTUAL_BUF_SIZE];
static uint16_t          g_ctsu_mutual_pri_corr[CTSU_CFG_NUM_MUTUAL_ELEMENTS * CTSU_CFG_NUM_SUMULTI];
static uint16_t          g_ctsu_mutual_snd_corr[CTSU_CFG_NUM_MUTUAL_ELEMENTS * CTSU_CFG_NUM_SUMULTI];
static ctsu_data_t       g_ctsu_mutual_pri_data[CTSU_CFG_NUM_MUTUAL_ELEMENTS];
static ctsu_data_t       g_ctsu_mutual_snd_data[CTSU_CFG_NUM_MUTUAL_ELEMENTS];
#endif
static ctsu_correction_info_t g_ctsu_correction_info;

#if (BSP_FEATURE_CTSU_VERSION == 1)
 #if (CTSU_CFG_DIAG_SUPPORT_ENABLE == 1)
static ctsu_diag_info_t     g_ctsu_diag_info;
static ctsu_diag_save_reg_t g_ctsu_diag_reg;
 #endif
#endif

#if (BSP_FEATURE_CTSU_VERSION == 2)
 #if (CTSU_CFG_NUM_CFC != 0)
static ctsu_corrcfc_info_t g_ctsu_corrcfc_info;
 #endif

 #if (CTSU_CFG_DIAG_SUPPORT_ENABLE == 1)
static ctsu_diag_info_t     g_ctsu_diag_info;
static ctsu_diag_save_reg_t g_ctsu_diag_reg;
 #endif
 #if (CTSU_CFG_TEMP_CORRECTION_SUPPORT == 1)
static uint32_t g_ctsu_temp_reg_ctsucra;
 #endif
 #if (BSP_FEATURE_CTSU_VERSION == 2)
  #if (CTSU_CFG_NUM_SELF_ELEMENTS != 0)
uint8_t g_ctsu_selected_freq_self[CTSU_CFG_NUM_SELF_ELEMENTS];
  #endif
  #if (CTSU_CFG_NUM_MUTUAL_ELEMENTS != 0)
uint8_t g_ctsu_selected_freq_mutual[CTSU_CFG_NUM_MUTUAL_ELEMENTS];
  #endif
 #endif
#endif

static ioport_instance_ctrl_t g_ctsu_tscap_ioport_ctrl;
static ioport_pin_cfg_t       g_ctsu_tscap_pin_cfg_data =
{
    .pin = (bsp_io_port_pin_t) CTSU_CFG_TSCAP_PORT,
};
static const ioport_cfg_t g_ctsu_tscap_pin_cfg =
{
    .number_of_pins = 1,
    .p_pin_cfg_data = &g_ctsu_tscap_pin_cfg_data,
};

#if (BSP_FEATURE_CTSU_VERSION == 1)
 #if (CTSU_CFG_DIAG_SUPPORT_ENABLE == 1)
static const uint16_t dac_oscil_table[6][2] =
{
    {CTSU_CFG_DIAG_DAC1_MAX, CTSU_CFG_DIAG_DAC1_MIN},
    {CTSU_CFG_DIAG_DAC2_MAX, CTSU_CFG_DIAG_DAC2_MIN},
    {CTSU_CFG_DIAG_DAC3_MAX, CTSU_CFG_DIAG_DAC3_MIN},
    {CTSU_CFG_DIAG_DAC4_MAX, CTSU_CFG_DIAG_DAC4_MIN},
    {CTSU_CFG_DIAG_DAC5_MAX, CTSU_CFG_DIAG_DAC5_MIN},
    {CTSU_CFG_DIAG_DAC6_MAX, CTSU_CFG_DIAG_DAC6_MIN},
};
 #endif
#endif

#if (BSP_FEATURE_CTSU_VERSION == 2)
 #if (CTSU_CFG_DIAG_SUPPORT_ENABLE == 1)
static const uint16_t cco_gain_table[12][2] =
{
    {CTSU_CFG_DIAG_DAC1_MIN,  CTSU_CFG_DIAG_DAC1_MAX   },
    {CTSU_CFG_DIAG_DAC2_MIN,  CTSU_CFG_DIAG_DAC2_MAX   },
    {CTSU_CFG_DIAG_DAC3_MIN,  CTSU_CFG_DIAG_DAC3_MAX   },
    {CTSU_CFG_DIAG_DAC4_MIN,  CTSU_CFG_DIAG_DAC4_MAX   },
    {CTSU_CFG_DIAG_DAC5_MIN,  CTSU_CFG_DIAG_DAC5_MAX   },
    {CTSU_CFG_DIAG_DAC6_MIN,  CTSU_CFG_DIAG_DAC6_MAX   },
    {CTSU_CFG_DIAG_DAC7_MIN,  CTSU_CFG_DIAG_DAC7_MAX   },
    {CTSU_CFG_DIAG_DAC8_MIN,  CTSU_CFG_DIAG_DAC8_MAX   },
    {CTSU_CFG_DIAG_DAC9_MIN,  CTSU_CFG_DIAG_DAC9_MAX   },
    {CTSU_CFG_DIAG_DAC10_MIN, CTSU_CFG_DIAG_DAC10_MAX  },
    {CTSU_CFG_DIAG_DAC11_MIN, CTSU_CFG_DIAG_DAC11_MAX  },
    {CTSU_CFG_DIAG_DAC12_MIN, CTSU_CFG_DIAG_DAC12_MAX  },
};

static const uint16_t cco_gain_diff_table[11][2] =
{
    {CTSU_CFG_DIAG_DAC1_2_DIFF_MIN,   CTSU_CFG_DIAG_DAC1_2_DIFF_MAX      },
    {CTSU_CFG_DIAG_DAC2_3_DIFF_MIN,   CTSU_CFG_DIAG_DAC2_3_DIFF_MAX      },
    {CTSU_CFG_DIAG_DAC3_4_DIFF_MIN,   CTSU_CFG_DIAG_DAC3_4_DIFF_MAX      },
    {CTSU_CFG_DIAG_DAC4_5_DIFF_MIN,   CTSU_CFG_DIAG_DAC4_5_DIFF_MAX      },
    {CTSU_CFG_DIAG_DAC5_6_DIFF_MIN,   CTSU_CFG_DIAG_DAC5_6_DIFF_MAX      },
    {CTSU_CFG_DIAG_DAC6_7_DIFF_MIN,   CTSU_CFG_DIAG_DAC6_7_DIFF_MAX      },
    {CTSU_CFG_DIAG_DAC7_8_DIFF_MIN,   CTSU_CFG_DIAG_DAC7_8_DIFF_MAX      },
    {CTSU_CFG_DIAG_DAC8_9_DIFF_MIN,   CTSU_CFG_DIAG_DAC8_9_DIFF_MAX      },
    {CTSU_CFG_DIAG_DAC9_10_DIFF_MIN,  CTSU_CFG_DIAG_DAC9_10_DIFF_MAX     },
    {CTSU_CFG_DIAG_DAC10_11_DIFF_MIN, CTSU_CFG_DIAG_DAC10_11_DIFF_MAX    },
    {CTSU_CFG_DIAG_DAC11_12_DIFF_MIN, CTSU_CFG_DIAG_DAC11_12_DIFF_MAX    },
};
 #endif
#endif

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/
const ctsu_api_t g_ctsu_on_ctsu =
{
    .open            = R_CTSU_Open,
    .scanStart       = R_CTSU_ScanStart,
    .dataGet         = R_CTSU_DataGet,
    .scanStop        = R_CTSU_ScanStop,
    .diagnosis       = R_CTSU_Diagnosis,
    .close           = R_CTSU_Close,
    .callbackSet     = R_CTSU_CallbackSet,
    .specificDataGet = R_CTSU_SpecificDataGet,
    .dataInsert      = R_CTSU_DataInsert,
};

/*******************************************************************************************************************//**
 * @addtogroup CTSU
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief Opens and configures the CTSU driver module. Implements @ref ctsu_api_t::open.
 *
 * Example:
 * @snippet r_ctsu_example.c R_CTSU_Open
 *
 * @retval FSP_SUCCESS              CTSU successfully configured.
 * @retval FSP_ERR_ASSERTION        Null pointer, or one or more configuration options is invalid.
 * @retval FSP_ERR_ALREADY_OPEN     Module is already open.  This module can only be opened once.
 * @retval FSP_ERR_INVALID_ARGUMENT Configuration parameter error.
 *
 * @note In the first Open, measurement for correction works, and it takes several tens of milliseconds.
 **********************************************************************************************************************/
fsp_err_t R_CTSU_Open (ctsu_ctrl_t * const p_ctrl, ctsu_cfg_t const * const p_cfg)
{
    ctsu_instance_ctrl_t     * p_instance_ctrl = (ctsu_instance_ctrl_t *) p_ctrl;
    fsp_err_t                  err             = FSP_SUCCESS;
    uint16_t                   element_id;
    const ctsu_element_cfg_t * element_cfgs;
#if (BSP_FEATURE_CTSU_VERSION == 2)
    uint16_t i;
    uint32_t pclkb_mhz;
    uint16_t suadj[3];
#endif

#if (CTSU_CFG_PARAM_CHECKING_ENABLE == 1)
    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_cfg);
#endif
    FSP_ERROR_RETURN(CTSU_OPEN != p_instance_ctrl->open, FSP_ERR_ALREADY_OPEN);

    /* Check element number */
#if (CTSU_CFG_NUM_SELF_ELEMENTS != 0)
    if (CTSU_MODE_SELF_MULTI_SCAN == (CTSU_MODE_MUTUAL_FULL_SCAN & p_cfg->md))
    {
        FSP_ERROR_RETURN(CTSU_CFG_NUM_SELF_ELEMENTS >=
                         (uint8_t) (g_ctsu_self_element_index + p_cfg->num_rx),
                         FSP_ERR_INVALID_ARGUMENT);
    }
#endif
#if (CTSU_CFG_NUM_MUTUAL_ELEMENTS != 0)
    if (CTSU_MODE_MUTUAL_FULL_SCAN == (CTSU_MODE_MUTUAL_FULL_SCAN & p_cfg->md))
    {
        FSP_ERROR_RETURN(CTSU_CFG_NUM_MUTUAL_ELEMENTS >=
                         (uint8_t) (g_ctsu_mutual_element_index + (p_cfg->num_rx * p_cfg->num_tx)),
                         FSP_ERR_INVALID_ARGUMENT);
    }
#endif
    p_instance_ctrl->state = CTSU_STATE_INIT;

    /* Save configurations. */
    p_instance_ctrl->p_ctsu_cfg = p_cfg;

    /* Initialize driver control structure (address setting) */
#if (CTSU_CFG_NUM_SELF_ELEMENTS != 0)
    if (CTSU_MODE_SELF_MULTI_SCAN == (CTSU_MODE_MUTUAL_FULL_SCAN & p_cfg->md))
    {
        p_instance_ctrl->p_self_raw   = &g_ctsu_self_raw[g_ctsu_self_element_index * CTSU_CFG_NUM_SUMULTI];
        p_instance_ctrl->p_self_corr  = &g_ctsu_self_corr[g_ctsu_self_element_index * CTSU_CFG_NUM_SUMULTI];
        p_instance_ctrl->p_self_data  = &g_ctsu_self_data[g_ctsu_self_element_index];
        p_instance_ctrl->num_elements = p_cfg->num_rx;
 #if (BSP_FEATURE_CTSU_VERSION == 2)
        p_instance_ctrl->p_selected_freq_self = &g_ctsu_selected_freq_self[g_ctsu_self_element_index];
 #endif
        g_ctsu_self_element_index        = (uint8_t) (g_ctsu_self_element_index + p_instance_ctrl->num_elements);
        p_instance_ctrl->self_elem_index = g_ctsu_self_element_index;

 #if (CTSU_CFG_NUM_MUTUAL_ELEMENTS != 0)
        p_instance_ctrl->p_mutual_raw      = &g_ctsu_mutual_raw[0];
        p_instance_ctrl->p_mutual_pri_corr = &g_ctsu_mutual_pri_corr[0];
        p_instance_ctrl->p_mutual_snd_corr = &g_ctsu_mutual_snd_corr[0];
        p_instance_ctrl->p_mutual_pri_data = &g_ctsu_mutual_pri_data[0];
        p_instance_ctrl->p_mutual_snd_data = &g_ctsu_mutual_snd_data[0];
 #endif
    }
#endif
#if (CTSU_CFG_NUM_MUTUAL_ELEMENTS != 0)
    if (CTSU_MODE_MUTUAL_FULL_SCAN == (CTSU_MODE_MUTUAL_FULL_SCAN & p_cfg->md))
    {
        p_instance_ctrl->p_mutual_raw      = &g_ctsu_mutual_raw[g_ctsu_mutual_element_index * CTSU_MUTUAL_BUF_SIZE];
        p_instance_ctrl->p_mutual_pri_corr =
            &g_ctsu_mutual_pri_corr[g_ctsu_mutual_element_index * CTSU_CFG_NUM_SUMULTI];
        p_instance_ctrl->p_mutual_snd_corr =
            &g_ctsu_mutual_snd_corr[g_ctsu_mutual_element_index * CTSU_CFG_NUM_SUMULTI];
        p_instance_ctrl->p_mutual_pri_data =
            &g_ctsu_mutual_pri_data[g_ctsu_mutual_element_index];
        p_instance_ctrl->p_mutual_snd_data =
            &g_ctsu_mutual_snd_data[g_ctsu_mutual_element_index];
        p_instance_ctrl->num_elements = (uint8_t) (p_cfg->num_rx * p_cfg->num_tx);
 #if (BSP_FEATURE_CTSU_VERSION == 2)
        p_instance_ctrl->p_selected_freq_mutual = &g_ctsu_selected_freq_mutual[g_ctsu_mutual_element_index * 2];
 #endif
        g_ctsu_mutual_element_index        = (uint8_t) (g_ctsu_mutual_element_index + p_instance_ctrl->num_elements);
        p_instance_ctrl->mutual_elem_index = g_ctsu_mutual_element_index;

 #if (CTSU_CFG_NUM_SELF_ELEMENTS != 0)
        p_instance_ctrl->p_self_raw  = &g_ctsu_self_raw[0];
        p_instance_ctrl->p_self_corr = &g_ctsu_self_corr[0];
        p_instance_ctrl->p_self_data = &g_ctsu_self_data[0];
 #endif
    }
#endif
    p_instance_ctrl->p_element_complete_flag = &g_ctsu_element_complete_flag[g_ctsu_element_index];
#if (BSP_FEATURE_CTSU_VERSION == 2)
    p_instance_ctrl->p_frequency_complete_flag = &g_ctsu_frequency_complete_flag[g_ctsu_element_index];
#endif
    p_instance_ctrl->p_tuning_diff   = &g_ctsu_tuning_diff[g_ctsu_element_index];
    p_instance_ctrl->p_ctsuwr        = &g_ctsu_ctsuwr[g_ctsu_element_index * CTSU_CFG_NUM_SUMULTI];
    g_ctsu_element_index             = (uint8_t) (g_ctsu_element_index + p_instance_ctrl->num_elements);
    p_instance_ctrl->ctsu_elem_index = g_ctsu_element_index;

    /* Set Value */
    p_instance_ctrl->cap                = p_cfg->cap;
    p_instance_ctrl->num_moving_average = p_cfg->num_moving_average;
    p_instance_ctrl->average            = 0;
    if (true == p_cfg->tunning_enable)
    {
        p_instance_ctrl->tuning = CTSU_TUNING_INCOMPLETE;
    }
    else
    {
        p_instance_ctrl->tuning = CTSU_TUNING_COMPLETE;
    }

#if (BSP_FEATURE_CTSU_VERSION == 2)
 #if (CTSU_CFG_NUM_CFC != 0)
    if (CTSU_MODE_MUTUAL_CFC_SCAN == p_cfg->md)
    {
        p_instance_ctrl->tuning = CTSU_TUNING_COMPLETE;
    }
 #endif

    if (CTSU_MODE_CURRENT_SCAN == p_cfg->md)
    {
        p_instance_ctrl->tuning = CTSU_TUNING_COMPLETE;
    }
#endif

#if (BSP_FEATURE_CTSU_VERSION == 1)
    p_instance_ctrl->ctsucr1 = (uint8_t) (p_cfg->atune1 << 3);
#endif
#if (BSP_FEATURE_CTSU_VERSION == 2)
    p_instance_ctrl->ctsucr1 = (uint8_t) ((p_cfg->atune12 & 0x01) << 3);
#endif
    p_instance_ctrl->ctsucr1 |= (uint8_t) (p_cfg->md << 6);

    p_instance_ctrl->txvsel  = p_instance_ctrl->p_ctsu_cfg->txvsel;
    p_instance_ctrl->txvsel2 = p_instance_ctrl->p_ctsu_cfg->txvsel2;

    p_instance_ctrl->ctsuchac0 = p_instance_ctrl->p_ctsu_cfg->ctsuchac0;
    p_instance_ctrl->ctsuchac1 = p_instance_ctrl->p_ctsu_cfg->ctsuchac1;
    p_instance_ctrl->ctsuchac2 = p_instance_ctrl->p_ctsu_cfg->ctsuchac2;
    p_instance_ctrl->ctsuchac3 = p_instance_ctrl->p_ctsu_cfg->ctsuchac3;
    p_instance_ctrl->ctsuchac4 = p_instance_ctrl->p_ctsu_cfg->ctsuchac4;

    p_instance_ctrl->ctsuchtrc0 = p_instance_ctrl->p_ctsu_cfg->ctsuchtrc0;
    p_instance_ctrl->ctsuchtrc1 = p_instance_ctrl->p_ctsu_cfg->ctsuchtrc1;
    p_instance_ctrl->ctsuchtrc2 = p_instance_ctrl->p_ctsu_cfg->ctsuchtrc2;
    p_instance_ctrl->ctsuchtrc3 = p_instance_ctrl->p_ctsu_cfg->ctsuchtrc3;
    p_instance_ctrl->ctsuchtrc4 = p_instance_ctrl->p_ctsu_cfg->ctsuchtrc4;

    p_instance_ctrl->md = p_instance_ctrl->p_ctsu_cfg->md;

#if (BSP_FEATURE_CTSU_VERSION == 2)
    p_instance_ctrl->ctsucr2  = (uint8_t) (p_cfg->atune12 & 0x02);
    p_instance_ctrl->ctsucr2 |= (uint8_t) ((p_cfg->md & 0x04) >> 2);
    p_instance_ctrl->ctsucr2 |= (uint8_t) (p_cfg->posel << 4);

    if (CTSU_ATUNE12_80UA == p_cfg->atune12)
    {
        p_instance_ctrl->range = CTSU_RANGE_80UA;
    }
    else if (CTSU_ATUNE12_40UA == p_cfg->atune12)
    {
        p_instance_ctrl->range = CTSU_RANGE_40UA;
    }
    else if (CTSU_ATUNE12_20UA == p_cfg->atune12)
    {
        p_instance_ctrl->range = CTSU_RANGE_20UA;
    }
    else if (CTSU_ATUNE12_160UA == p_cfg->atune12)
    {
        p_instance_ctrl->range = CTSU_RANGE_160UA;
    }
    else
    {
    }
#endif
    for (element_id = 0; element_id < p_instance_ctrl->num_elements; element_id++)
    {
        p_instance_ctrl->p_element_complete_flag[element_id] = 0;
#if (BSP_FEATURE_CTSU_VERSION == 2)
        p_instance_ctrl->p_frequency_complete_flag[element_id] = 0;
#endif
        p_instance_ctrl->p_tuning_diff[element_id] = 0;
        element_cfgs = (p_cfg->p_elements + element_id);
#if (BSP_FEATURE_CTSU_VERSION == 2)
        if (CTSU_MODE_CURRENT_SCAN == p_cfg->md)
        {
            /* Current scan does not run multiple frequency */
            p_instance_ctrl->p_ctsuwr[element_id].ctsuso =
                (uint32_t) (((uint32_t) element_cfgs->sdpa << (uint32_t) 24) |
                            ((uint32_t) element_cfgs->snum << (uint32_t) 10) | element_cfgs->so);
        }
        else
        {
            if (CTSU_MODE_MUTUAL_CFC_SCAN != p_cfg->md)
            {
                p_instance_ctrl->p_ctsuwr[element_id * CTSU_CFG_NUM_SUMULTI].ctsuso =
                    (uint32_t) (((uint32_t) element_cfgs->sdpa << (uint32_t) 24) |
                                ((uint32_t) element_cfgs->snum << (uint32_t) 10) | element_cfgs->so);
            }

 #if (CTSU_CFG_NUM_CFC != 0)
            else
            {
                /* CFC scan does not use CTSUSO */
                p_instance_ctrl->p_ctsuwr[element_id * CTSU_CFG_NUM_SUMULTI].ctsuso =
                    (uint32_t) (((uint32_t) element_cfgs->sdpa << (uint32_t) 24) |
                                ((uint32_t) element_cfgs->snum << (uint32_t) 10));
            }
 #endif

            for (i = 1; i < CTSU_CFG_NUM_SUMULTI; i++)
            {
                p_instance_ctrl->p_ctsuwr[(element_id * CTSU_CFG_NUM_SUMULTI) + i].ctsuso =
                    p_instance_ctrl->p_ctsuwr[element_id * CTSU_CFG_NUM_SUMULTI].ctsuso;
            }
        }
#endif
#if (BSP_FEATURE_CTSU_VERSION == 1)
        p_instance_ctrl->p_ctsuwr[element_id].ctsussc = (uint16_t) (element_cfgs->ssdiv << 8);
        p_instance_ctrl->p_ctsuwr[element_id].ctsuso0 = (uint16_t) ((element_cfgs->snum << 10) | element_cfgs->so);
        p_instance_ctrl->p_ctsuwr[element_id].ctsuso1 =
            (uint16_t) ((CTSU_ICOG_RECOMMEND << 13) | (element_cfgs->sdpa << 8) | CTSU_RICOA_RECOMMEND);
#endif
    }

    p_instance_ctrl->write_irq = p_cfg->write_irq;
    p_instance_ctrl->read_irq  = p_cfg->read_irq;
    p_instance_ctrl->end_irq   = p_cfg->end_irq;

    /* Enable interrupts for CTSUWR, CTSURD, CTSUFN */
    R_BSP_IrqCfgEnable(p_cfg->write_irq, CTSU_CFG_INT_PRIORITY_LEVEL, p_instance_ctrl);
    R_BSP_IrqCfgEnable(p_cfg->read_irq, CTSU_CFG_INT_PRIORITY_LEVEL, p_instance_ctrl);
    R_BSP_IrqCfgEnable(p_cfg->end_irq, CTSU_CFG_INT_PRIORITY_LEVEL, p_instance_ctrl);

    p_instance_ctrl->interrupt_reverse_flag = 0;

    if (p_instance_ctrl->num_elements == g_ctsu_element_index)
    {
        /* TSCAP discharge process */
        g_ctsu_tscap_pin_cfg_data.pin_cfg =
            ((uint32_t) IOPORT_CFG_PORT_DIRECTION_OUTPUT | (uint32_t) IOPORT_CFG_PORT_OUTPUT_LOW);
        R_IOPORT_Open(&g_ctsu_tscap_ioport_ctrl, &g_ctsu_tscap_pin_cfg);
        R_BSP_SoftwareDelay(10, BSP_DELAY_UNITS_MICROSECONDS);
        g_ctsu_tscap_pin_cfg_data.pin_cfg =
            ((uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_CTSU);
        R_IOPORT_PinsCfg(&g_ctsu_tscap_ioport_ctrl, &g_ctsu_tscap_pin_cfg);
        R_IOPORT_Close(&g_ctsu_tscap_ioport_ctrl);

        /* Get CTSU out of stop state (supply power/clock) */
        R_BSP_MODULE_START(FSP_IP_CTSU, 0);

#if (CTSU_CFG_DTC_SUPPORT_ENABLE == 1)
        err = ctsu_transfer_open(p_instance_ctrl);
#endif
#if (BSP_FEATURE_CTSU_VERSION == 2)
        R_CTSU->CTSUCRA_b.ATUNE0 = CTSU_CFG_LOW_VOLTAGE_MODE;
        R_CTSU->CTSUCRA_b.PUMPON = 1;

        pclkb_mhz = R_FSP_SystemClockHzGet(FSP_PRIV_CLOCK_PCLKB) / CTSU_PCLKB_FREQ_MHZ;

        if (CTSU_PCLKB_FREQ_RANGE1 >= pclkb_mhz)
        {
            R_CTSU->CTSUCRA_b.CLK = 0;
            R_CTSU->CTSUCR3       = (uint8_t) (pclkb_mhz - 1);
        }
        else if ((CTSU_PCLKB_FREQ_RANGE1 < pclkb_mhz) && (CTSU_PCLKB_FREQ_RANGE2 >= pclkb_mhz))
        {
            R_CTSU->CTSUCRA_b.CLK = 1;
            R_CTSU->CTSUCR3       = (uint8_t) ((pclkb_mhz >> 1) - 1);
        }
        else if ((CTSU_PCLKB_FREQ_RANGE2 < pclkb_mhz) && (CTSU_PCLKB_FREQ_RANGE3 >= pclkb_mhz))
        {
            R_CTSU->CTSUCRA_b.CLK = 2;
            R_CTSU->CTSUCR3       = (uint8_t) ((pclkb_mhz >> 2) - 1);
        }
        else
        {
            R_CTSU->CTSUCRA_b.CLK = 3;
            R_CTSU->CTSUCR3       = (uint8_t) ((pclkb_mhz >> 3) - 1);
        }
#endif
#if (BSP_FEATURE_CTSU_VERSION == 1)

        /* Set power on */
        R_CTSU->CTSUCR1 = ((CTSU_CFG_LOW_VOLTAGE_MODE << 2) | (CTSU_CSW_ON << 1) | CTSU_PON_ON);

        /* Synchronous Noise Reduction Setting */
        R_CTSU->CTSUSDPRS = ((CTSU_SOFF_ON << 6) | (CTSU_PRMODE_62_PULSES << 4) | CTSU_PRRATIO_RECOMMEND);

        /* High Pass Noise Reduction- ALWAYS 0x30 as per HW Manual */
        R_CTSU->CTSUDCLKC = ((CTSU_SSCNT << 4) | CTSU_SSMOD);

        /* Sensor Stabilization- ALWAYS 0x10 as per HW Manual */
        R_CTSU->CTSUSST = (CTSU_SST_RECOMMEND);

        if (CTSU_CORRECTION_INIT == g_ctsu_correction_info.status)
        {
            ctsu_correction_process(p_instance_ctrl);
        }

        /* Since CLK is rewritten by correction, set here. */
        R_CTSU->CTSUCR1 |= (uint8_t) (CTSU_CFG_PCLK_DIVISION << 4);
#endif
    }

#if (BSP_FEATURE_CTSU_VERSION == 2)
    if (CTSU_MODE_MUTUAL_CFC_SCAN != p_cfg->md)
    {
        /* Set power on */
        R_CTSU->CTSUCRA_b.CSW = CTSU_CSW_ON;
        R_CTSU->CTSUCRA_b.PON = CTSU_PON_ON;
        R_BSP_SoftwareDelay(30, BSP_DELAY_UNITS_MICROSECONDS);
    }

 #if (CTSU_CFG_NUM_CFC != 0)
    else
    {
        R_CTSU->CTSUCALIB_b.CFCRDMD = 1;
        R_CTSU->CTSUCRA_b.CFCON     = 1;
        R_BSP_SoftwareDelay(30, BSP_DELAY_UNITS_MICROSECONDS);
    }
 #endif

    /* High resolution pulse mode  */
    R_CTSU->CTSUCRA_b.SDPSEL    = 1;
    R_CTSU->CTSUCRA_b.PCSEL     = 1;
    R_CTSU->CTSUSST             = CTSU_SST_RECOMMEND;
    R_CTSU->CTSUCALIB_b.CCOCLK  = 0;
    R_CTSU->CTSUCALIB_b.SUCLKEN = 0;

    if (CTSU_MODE_MUTUAL_CFC_SCAN != p_cfg->md)
    {
 #if (CTSU_CFG_TEMP_CORRECTION_SUPPORT == 1)
        if (CTSU_MODE_CORRECTION_SCAN == p_cfg->md)
        {
            g_ctsu_correction_info.scan_index = CTSU_CORRECTION_POINT_NUM;
        }
 #endif
        if (CTSU_CORRECTION_INIT == g_ctsu_correction_info.status)
        {
            ctsu_correction_process(p_instance_ctrl);
        }
    }

 #if (CTSU_CFG_NUM_CFC != 0)
    else
    {
        ctsu_corrcfc_process(p_instance_ctrl);
    }
    p_instance_ctrl->p_corrcfc_info = &g_ctsu_corrcfc_info;
 #endif

    R_CTSU->CTSUCRA_b.LOAD       = 1;
    R_CTSU->CTSUCRB_b.SSCNT      = 1;
    R_CTSU->CTSUCALIB_b.SUCARRY  = 0;
    R_CTSU->CTSUCALIB_b.CCOCALIB = 0;
    R_CTSU->CTSUCALIB_b.CCOCLK   = 1;
    R_CTSU->CTSUCALIB_b.TSOC     = 0;
    R_CTSU->CTSUCALIB_b.SUCLKEN  = 1;

    /* Read SUADJD byte */
    suadj[0] = R_CTSUTRIM->CTSUTRIMA_b.SUADJD;

    /* Adjust multi freq */
    suadj[1] = (uint16_t) ((suadj[0] * (CTSU_CFG_SUMULTI1 + 1)) / (CTSU_CFG_SUMULTI0 + 1));
    suadj[2] = (uint16_t) ((suadj[0] * (CTSU_CFG_SUMULTI2 + 1)) / (CTSU_CFG_SUMULTI0 + 1));

    /* Adjust SSCNT setting */
    suadj[0] = (uint16_t) (suadj[0] - (CTSU_SUADJ_SSCNT_ADJ * R_CTSU->CTSUCRB_b.SSCNT));
    suadj[1] = (uint16_t) (suadj[1] - (CTSU_SUADJ_SSCNT_ADJ * R_CTSU->CTSUCRB_b.SSCNT));
    suadj[2] = (uint16_t) (suadj[2] - (CTSU_SUADJ_SSCNT_ADJ * R_CTSU->CTSUCRB_b.SSCNT));

    /* Set CTSUSUCLK register */
    R_CTSU->CTSUCRA_b.SDPSEL = 0;
    R_CTSU->CTSUSUCLK0       = (uint16_t) (CTSU_CFG_SUMULTI0 << 8) | suadj[0];
    R_CTSU->CTSUSUCLK1       = (uint16_t) (CTSU_CFG_SUMULTI1 << 8) | suadj[1];
    R_CTSU->CTSUSUCLK2       = (uint16_t) (CTSU_CFG_SUMULTI2 << 8) | suadj[2];
    R_CTSU->CTSUCRA_b.SDPSEL = 1;
#endif

#if (BSP_FEATURE_CTSU_VERSION == 1)
 #if (CTSU_CFG_DIAG_SUPPORT_ENABLE == 1)
    if (CTSU_MODE_DIAGNOSIS_SCAN == p_instance_ctrl->md)
    {
        /* Initialize diagnosis information */
        p_instance_ctrl->p_diag_info    = &g_ctsu_diag_info;
        g_ctsu_diag_info.state          = CTSU_DIAG_INIT;
        g_ctsu_diag_info.ctsuwr.ctsussc = 0;
        g_ctsu_diag_info.ctsuwr.ctsuso0 = 0;
        g_ctsu_diag_info.ctsuwr.ctsuso1 = 0;
        g_ctsu_diag_info.loop_count     = 0;
        g_ctsu_diag_info.scanbuf.sen    = 0;
        g_ctsu_diag_info.scanbuf.ref    = 0;
        g_ctsu_diag_info.correct_data   = 0;
        g_ctsu_diag_info.icomp          = 0;
        g_ctsu_diag_info.cco_high       = 0;
        g_ctsu_diag_info.cco_low        = 0;
        g_ctsu_diag_info.sscg           = 0;
        g_ctsu_diag_info.dac_cnt[0]     = 0;
        g_ctsu_diag_info.dac_cnt[1]     = 0;
        g_ctsu_diag_info.dac_cnt[2]     = 0;
        g_ctsu_diag_info.dac_cnt[3]     = 0;
        g_ctsu_diag_info.dac_cnt[4]     = 0;
        g_ctsu_diag_info.dac_cnt[5]     = 0;
        g_ctsu_diag_info.so0_4uc_val    = 0;
        g_ctsu_diag_info.dac_init       = 0;
        g_ctsu_diag_info.tuning         = CTSU_TUNING_INCOMPLETE;
        g_ctsu_diag_info.tuning_diff    = 0;
    }
 #endif
#endif

#if (BSP_FEATURE_CTSU_VERSION == 2)
 #if (CTSU_CFG_DIAG_SUPPORT_ENABLE == 1)
    if (CTSU_MODE_DIAGNOSIS_SCAN == p_instance_ctrl->md)
    {
        p_instance_ctrl->p_diag_info = &g_ctsu_diag_info;
        g_ctsu_diag_info.lvmode      = CTSU_CFG_LOW_VOLTAGE_MODE;
        g_ctsu_diag_info.state       = CTSU_DIAG_INIT;
    }
    else
    {
        /* Once chac is set, it will not be set after that */
        if ((0 == g_ctsu_diag_info.chaca) && (0 == g_ctsu_diag_info.chacb))
        {
            /* From the CHAC information configured in the normal measurement,                                  */
            /* find the minimum TS pin on the CTSU peripheral for the OverCuurent test and clock recovery test. */

            /* Get CHACA register info */
            ((uint8_t *) &(g_ctsu_diag_info.chaca))[0] = p_instance_ctrl->p_ctsu_cfg->ctsuchac0;
            ((uint8_t *) &(g_ctsu_diag_info.chaca))[1] = p_instance_ctrl->p_ctsu_cfg->ctsuchac1;
            ((uint8_t *) &(g_ctsu_diag_info.chaca))[2] = p_instance_ctrl->p_ctsu_cfg->ctsuchac2;
            ((uint8_t *) &(g_ctsu_diag_info.chaca))[3] = p_instance_ctrl->p_ctsu_cfg->ctsuchac3;

            /* Get CHACB register info */
            g_ctsu_diag_info.chacb = (uint32_t) (p_instance_ctrl->p_ctsu_cfg->ctsuchac4);

            /* Get the number of measurable elements from enabled CHACA */
            if (0 != g_ctsu_diag_info.chaca)
            {
                /* Get the number of measurable elements from enabled CHACA */
                for (i = 0; i < CTSU_DIAG_CHACA_TSMAX; i++)
                {
                    if ((g_ctsu_diag_info.chaca >> i) & (uint32_t) 0x00000001)
                    {
                        g_ctsu_diag_info.chaca = (uint32_t) (0x00000001 << i);
                        g_ctsu_diag_info.chacb = 0;
                        break;
                    }
                }
            }
            else                       /* Check the measurable elements from enabled CHACB. */
            {
                for (i = 0; i < 8; i++)
                {
                    /* Get the number of measurable elements from enabled CHACB */
                    if ((g_ctsu_diag_info.chacb >> i) & (uint32_t) 0x00000001)
                    {
                        g_ctsu_diag_info.chaca = 0;
                        g_ctsu_diag_info.chacb = (uint32_t) (0x00000001 << i);
                        break;
                    }
                }
            }
        }
    }
 #endif
#endif

    p_instance_ctrl->p_correction_info = &g_ctsu_correction_info;
    p_instance_ctrl->rd_index          = 0;
    p_instance_ctrl->wr_index          = 0;
    p_instance_ctrl->state             = CTSU_STATE_IDLE;

    p_instance_ctrl->p_callback        = p_cfg->p_callback;
    p_instance_ctrl->p_context         = p_cfg->p_context;
    p_instance_ctrl->p_callback_memory = NULL;

    p_instance_ctrl->serial_tuning_enable     = 0;
    p_instance_ctrl->serial_tuning_mutual_cnt = 0;

#if defined(CTSU_CFG_TARGET_VALUE_QE_SUPPORT)
    p_instance_ctrl->tuning_self_target_value   = p_cfg->tuning_self_target_value;
    p_instance_ctrl->tuning_mutual_target_value = p_cfg->tuning_mutual_target_value;
#else
    p_instance_ctrl->tuning_self_target_value   = CTSU_TUNING_VALUE_SELF;
    p_instance_ctrl->tuning_mutual_target_value = CTSU_TUNING_VALUE_MUTUAL;
#endif

    /* Mark driver as open */
    p_instance_ctrl->open = CTSU_OPEN;

    return err;
}

/*******************************************************************************************************************//**
 * @brief This function should be called each time a periodic timer expires.
 * If initial offset tuning is enabled, The first several calls are used to tuning for the sensors.
 * Before starting the next scan, first get the data with R_CTSU_DataGet().
 * If a different control block scan should be run, check the scan is complete before executing.
 * Implements @ref ctsu_api_t::scanStart.
 *
 * Example:
 * @snippet r_ctsu_example.c R_CTSU_ScanStart
 *
 * @retval FSP_SUCCESS              CTSU successfully configured.
 * @retval FSP_ERR_ASSERTION        Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 * @retval FSP_ERR_CTSU_SCANNING    Scanning this instance or other.
 * @retval FSP_ERR_CTSU_NOT_GET_DATA    The previous data has not been retrieved by DataGet.
 **********************************************************************************************************************/
fsp_err_t R_CTSU_ScanStart (ctsu_ctrl_t * const p_ctrl)
{
    fsp_err_t              err             = FSP_SUCCESS;
    ctsu_instance_ctrl_t * p_instance_ctrl = (ctsu_instance_ctrl_t *) p_ctrl;
    uint8_t                temp;
#if (BSP_FEATURE_CTSU_VERSION == 2)
    uint8_t txvsel;
#endif

#if (CTSU_CFG_PARAM_CHECKING_ENABLE == 1)
    FSP_ASSERT(p_instance_ctrl);
    FSP_ERROR_RETURN(CTSU_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif
    if (CTSU_CAP_SOFTWARE == p_instance_ctrl->cap)
    {
        /* Can be checked if the previous measurement was a software trigger */
        if (0 == (0x02 & R_CTSU->CTSUCR0))
        {
            FSP_ERROR_RETURN(0x01 != (R_CTSU->CTSUCR0 & 0x01), FSP_ERR_CTSU_SCANNING);
        }
    }

    FSP_ERROR_RETURN(CTSU_STATE_SCANNED != p_instance_ctrl->state, FSP_ERR_CTSU_NOT_GET_DATA);

    R_FSP_IsrContextSet(p_instance_ctrl->write_irq, p_instance_ctrl);
    R_FSP_IsrContextSet(p_instance_ctrl->read_irq, p_instance_ctrl);
    R_FSP_IsrContextSet(p_instance_ctrl->end_irq, p_instance_ctrl);

#if (CTSU_CFG_DTC_SUPPORT_ENABLE == 1)
    err = ctsu_transfer_configure(p_instance_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#endif

    if (CTSU_CAP_SOFTWARE == p_instance_ctrl->cap)
    {
        R_CTSU->CTSUCR0 &= (uint8_t) ~0x06; // specify Software trigger usage
    }
    else
    {
        R_CTSU->CTSUCR0 |= 0x06;            // specify external trigger usage and enable power saving
        R_CTSU->CTSUCR0 &= (uint8_t) ~0x01; // To write CTSUCR1
    }

    /* Write CTSU Control Register 1 and save mode */
#if (BSP_FEATURE_CTSU_VERSION == 2)
    if ((CTSU_MODE_CORRECTION_SCAN != p_instance_ctrl->md) &&
        (CTSU_MODE_DIAGNOSIS_SCAN != p_instance_ctrl->md))
    {
        txvsel =
            (uint8_t) ((p_instance_ctrl->txvsel2 << 6) | (p_instance_ctrl->txvsel << 7));
        temp            = (uint8_t) (R_CTSU->CTSUCR0 & ~(CTSU_CR0_MODIFY_BIT));
        R_CTSU->CTSUCR0 = (uint8_t) (temp | (txvsel & CTSU_CR0_MODIFY_BIT));                   // TXVSEL
        temp            = (uint8_t) (R_CTSU->CTSUCR1 & ~(CTSU_CR1_MODIFY_BIT));
        R_CTSU->CTSUCR1 = (uint8_t) (temp | (p_instance_ctrl->ctsucr1 & CTSU_CR1_MODIFY_BIT)); // MD1, MD0, ATUNE1
        temp            = (uint8_t) (R_CTSU->CTSUCR2 & ~(CTSU_CR2_MODIFY_BIT));
        R_CTSU->CTSUCR2 = (uint8_t) (temp | (p_instance_ctrl->ctsucr2 & CTSU_CR2_MODIFY_BIT)); // POSEL, ATUNE2, MD2
        if (CTSU_MODE_CURRENT_SCAN == p_instance_ctrl->md)
        {
            R_CTSU->CTSUSST          = CTSU_SST_RECOMMEND_CURRENT;
            R_CTSU->CTSUCRA_b.DCMODE = 1;
            R_CTSU->CTSUCRA_b.DCBACK = 1;
            R_CTSU->CTSUMCH_b.MCA0   = 1;
            R_CTSU->CTSUMCH_b.MCA1   = 0;
            R_CTSU->CTSUMCH_b.MCA2   = 0;
            R_CTSU->CTSUMCH_b.MCA3   = 0;
        }
        else
        {
            R_CTSU->CTSUSST          = CTSU_SST_RECOMMEND;
            R_CTSU->CTSUCRA_b.DCMODE = 0;
            R_CTSU->CTSUCRA_b.DCBACK = 0;
            R_CTSU->CTSUMCH_b.MCA0   = 1;
 #if (CTSU_CFG_NUM_SUMULTI >= 2)
            R_CTSU->CTSUMCH_b.MCA1 = 1;
 #endif
 #if (CTSU_CFG_NUM_SUMULTI >= 3)
            R_CTSU->CTSUMCH_b.MCA2 = 1;
 #endif
        }

        /* Write Channel setting */
        R_CTSU->CTSUCHAC0  = p_instance_ctrl->ctsuchac0;
        R_CTSU->CTSUCHAC1  = p_instance_ctrl->ctsuchac1;
        R_CTSU->CTSUCHAC2  = p_instance_ctrl->ctsuchac2;
        R_CTSU->CTSUCHAC3  = p_instance_ctrl->ctsuchac3;
        R_CTSU->CTSUCHAC4  = p_instance_ctrl->ctsuchac4;
        R_CTSU->CTSUCHTRC0 = p_instance_ctrl->ctsuchtrc0;
        R_CTSU->CTSUCHTRC1 = p_instance_ctrl->ctsuchtrc1;
        R_CTSU->CTSUCHTRC2 = p_instance_ctrl->ctsuchtrc2;
        R_CTSU->CTSUCHTRC3 = p_instance_ctrl->ctsuchtrc3;
        R_CTSU->CTSUCHTRC4 = p_instance_ctrl->ctsuchtrc4;
    }

 #if (CTSU_CFG_DIAG_SUPPORT_ENABLE == 1)
    if (CTSU_MODE_DIAGNOSIS_SCAN == p_instance_ctrl->md)
    {
        err = ctsu_diag_scan_start2(p_instance_ctrl);
    }
 #endif
 #if (CTSU_CFG_TEMP_CORRECTION_SUPPORT == 1)
    if (CTSU_MODE_CORRECTION_SCAN == p_instance_ctrl->md)
    {
        R_CTSU->CTSUSST = CTSU_SST_RECOMMEND;
        ctsu_correction_scan_start();
    }
 #endif
    p_instance_ctrl->state = CTSU_STATE_SCANNING;
#endif
#if (BSP_FEATURE_CTSU_VERSION == 1)
    if (CTSU_MODE_DIAGNOSIS_SCAN != p_instance_ctrl->md)
    {
        temp            = (uint8_t) (R_CTSU->CTSUCR1 & ~(CTSU_CR1_MODIFY_BIT));
        R_CTSU->CTSUCR1 = (uint8_t) (temp | (p_instance_ctrl->ctsucr1 & CTSU_CR1_MODIFY_BIT)); // MD1, MD0, ATUNE1

 #if BSP_FEATURE_CTSU_HAS_TXVSEL
        R_CTSU->CTSUCR0 =
            (uint8_t) ((R_CTSU->CTSUCR0 & ~(CTSU_TXVSEL)) | (p_instance_ctrl->txvsel & CTSU_TXVSEL));
 #endif

        /* Write Channel setting */
        R_CTSU->CTSUCHAC[0] = p_instance_ctrl->ctsuchac0;
        R_CTSU->CTSUCHAC[1] = p_instance_ctrl->ctsuchac1;
 #if (BSP_FEATURE_CTSU_CTSUCHAC_REGISTER_COUNT >= 3)
        R_CTSU->CTSUCHAC[2] = p_instance_ctrl->ctsuchac2;
 #endif
 #if (BSP_FEATURE_CTSU_CTSUCHAC_REGISTER_COUNT >= 4)
        R_CTSU->CTSUCHAC[3] = p_instance_ctrl->ctsuchac3;
 #endif
 #if (BSP_FEATURE_CTSU_CTSUCHAC_REGISTER_COUNT >= 5)
        R_CTSU->CTSUCHAC[4] = p_instance_ctrl->ctsuchac4;
 #endif

 #if (CTSU_CFG_NUM_MUTUAL_ELEMENTS != 0)
        R_CTSU->CTSUCHTRC[0] = p_instance_ctrl->ctsuchtrc0;
        R_CTSU->CTSUCHTRC[1] = p_instance_ctrl->ctsuchtrc1;
  #if (BSP_FEATURE_CTSU_CTSUCHTRC_REGISTER_COUNT >= 3)
        R_CTSU->CTSUCHTRC[2] = p_instance_ctrl->ctsuchtrc2;
  #endif
  #if (BSP_FEATURE_CTSU_CTSUCHTRC_REGISTER_COUNT >= 4)
        R_CTSU->CTSUCHTRC[3] = p_instance_ctrl->ctsuchtrc3;
  #endif
  #if (BSP_FEATURE_CTSU_CTSUCHTRC_REGISTER_COUNT >= 5)
        R_CTSU->CTSUCHTRC[4] = p_instance_ctrl->ctsuchtrc4;
  #endif
 #endif
    }

 #if (CTSU_CFG_DIAG_SUPPORT_ENABLE == 1)
    if (CTSU_MODE_DIAGNOSIS_SCAN == p_instance_ctrl->md)
    {
        ctsu_diag_scan_start1(p_instance_ctrl);
    }
 #endif
#endif

    p_instance_ctrl->state = CTSU_STATE_SCANNING;

    /* Set CTSU_STRT bit to start scan */
    R_CTSU->CTSUCR0 |= 0x01;           ///< CTSU_STRT

    return err;
}

/*******************************************************************************************************************//**
 * @brief This function gets the sensor values as scanned by the CTSU.
 * If initial offset tuning is enabled, The first several calls are used to tuning for the sensors.
 * Implements @ref ctsu_api_t::dataGet.
 *
 * Example:
 * @snippet r_ctsu_example.c R_CTSU_DataGet
 *
 * @retval FSP_SUCCESS              CTSU successfully configured.
 * @retval FSP_ERR_ASSERTION        Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 * @retval FSP_ERR_CTSU_SCANNING    Scanning this instance.
 * @retval FSP_ERR_CTSU_INCOMPLETE_TUNING      Incomplete initial offset tuning.
 * @retval FSP_ERR_CTSU_DIAG_NOT_YET      Diagnosis of data collected no yet.
 * @retval FSP_ERR_ABORTED                Operate error of Diagnosis ADC data collection ,since ADC use other
 **********************************************************************************************************************/
fsp_err_t R_CTSU_DataGet (ctsu_ctrl_t * const p_ctrl, uint16_t * p_data)
{
    fsp_err_t              err             = FSP_SUCCESS;
    ctsu_instance_ctrl_t * p_instance_ctrl = (ctsu_instance_ctrl_t *) p_ctrl;
    uint16_t               element_id;

#if (CTSU_CFG_PARAM_CHECKING_ENABLE == 1)
    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_data);
    FSP_ERROR_RETURN(CTSU_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif
    FSP_ERROR_RETURN(CTSU_STATE_SCANNING != p_instance_ctrl->state, FSP_ERR_CTSU_SCANNING);

#if (BSP_FEATURE_CTSU_VERSION == 2)
 #if (CTSU_CFG_TEMP_CORRECTION_SUPPORT == 1)
    if (CTSU_MODE_CORRECTION_SCAN == p_instance_ctrl->md)
    {
        err = ctsu_correction_data_get(p_instance_ctrl, p_data);
        p_instance_ctrl->state = CTSU_STATE_IDLE;

        return err;
    }
 #endif

 #if (CTSU_CFG_DIAG_SUPPORT_ENABLE == 1)
    if (CTSU_MODE_DIAGNOSIS_SCAN == p_instance_ctrl->md)
    {
        err = ctsu_diag_data_get2(p_data);
        p_instance_ctrl->state = CTSU_STATE_IDLE;
        if (FSP_ERR_CTSU_DIAG_NOT_YET == err)
        {
            err = FSP_ERR_CTSU_DIAG_NOT_YET;
        }
        else if (FSP_ERR_ABORTED == err)
        {
            err = FSP_ERR_ABORTED;
        }
        else
        {
            err = FSP_SUCCESS;
        }

        return err;
    }
 #endif
#endif

#if (BSP_FEATURE_CTSU_VERSION == 1)
 #if (CTSU_CFG_DIAG_SUPPORT_ENABLE == 1)
    if (CTSU_MODE_DIAGNOSIS_SCAN == p_instance_ctrl->md)
    {
        err = ctsu_diag_data_get1();
        p_instance_ctrl->state = CTSU_STATE_IDLE;
        if (FSP_ERR_CTSU_DIAG_NOT_YET == err)
        {
            err = FSP_ERR_CTSU_DIAG_NOT_YET;
        }
        else
        {
            err = FSP_SUCCESS;
        }

        return err;
    }
 #endif
#endif

    if (CTSU_STATE_SCANNED == p_instance_ctrl->state)
    {
        if (CTSU_TUNING_COMPLETE == p_instance_ctrl->tuning)
        {
            if (p_instance_ctrl->average == p_instance_ctrl->num_moving_average)
            {
                /* Do nothing */
            }
            else if (p_instance_ctrl->average < p_instance_ctrl->num_moving_average)
            {
                (p_instance_ctrl->average)++;
            }
            else
            {
                p_instance_ctrl->average = p_instance_ctrl->num_moving_average;
            }
        }

        ctsu_correction_exec(p_instance_ctrl);

        if (CTSU_TUNING_INCOMPLETE == p_instance_ctrl->tuning)
        {
            if ((CTSU_MODE_SELF_MULTI_SCAN == p_instance_ctrl->md) ||
                (CTSU_MODE_MUTUAL_FULL_SCAN == p_instance_ctrl->md))
            {
                ctsu_initial_offset_tuning(p_instance_ctrl);
            }
        }

        p_instance_ctrl->state = CTSU_STATE_IDLE;
    }

    FSP_ERROR_RETURN(0 < p_instance_ctrl->average, FSP_ERR_CTSU_INCOMPLETE_TUNING);

#if (CTSU_CFG_NUM_SELF_ELEMENTS != 0)
    if (CTSU_MODE_SELF_MULTI_SCAN == (CTSU_MODE_MUTUAL_FULL_SCAN & p_instance_ctrl->md))
    {
        for (element_id = 0; element_id < p_instance_ctrl->num_elements; element_id++)
        {
            *p_data = (p_instance_ctrl->p_self_data + element_id)->int_data;
            p_data++;
        }
    }
#endif
#if (CTSU_CFG_NUM_MUTUAL_ELEMENTS != 0)
    if (CTSU_MODE_MUTUAL_FULL_SCAN == (CTSU_MODE_MUTUAL_FULL_SCAN & p_instance_ctrl->md))
    {
        for (element_id = 0; element_id < p_instance_ctrl->num_elements; element_id++)
        {
            *p_data = (p_instance_ctrl->p_mutual_pri_data + element_id)->int_data;
            p_data++;
            *p_data = (p_instance_ctrl->p_mutual_snd_data + element_id)->int_data;
            p_data++;
        }
    }
#endif

    return err;
}

/*******************************************************************************************************************//**
 * @brief This function tunes the offset register(SO). Call after the measurement is completed.
 * If the return value is FSP_ERR_CTSU_INCOMPLETE_TUNING, tuning is not complete.
 * Execute the measurement and this function call routine until the return value becomes FSP_SUCCESS.
 * It is recommended to run this routine after R_CTSU_Open().
 * It can be recalled and tuned again.
 * When the automatic judgement is enabled, after the offset tuning is completed,the baseline initialization bit flag is set.
 * Implements @ref ctsu_api_t::offsetTuning.
 *
 * Example:
 * @snippet r_ctsu_example.c R_CTSU_OffsetTuning
 *
 * @retval FSP_SUCCESS              CTSU successfully configured.
 * @retval FSP_ERR_ASSERTION        Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 * @retval FSP_ERR_CTSU_SCANNING    Scanning this instance.
 * @retval FSP_ERR_CTSU_INCOMPLETE_TUNING      Incomplete initial offset tuning.
 **********************************************************************************************************************/
fsp_err_t R_CTSU_OffsetTuning (ctsu_ctrl_t * const p_ctrl)
{
    fsp_err_t              err             = FSP_SUCCESS;
    ctsu_instance_ctrl_t * p_instance_ctrl = (ctsu_instance_ctrl_t *) p_ctrl;
    uint16_t               element_id;

#if (CTSU_CFG_PARAM_CHECKING_ENABLE == 1)
    FSP_ASSERT(p_instance_ctrl);
    FSP_ERROR_RETURN(CTSU_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif
    FSP_ERROR_RETURN(CTSU_STATE_SCANNING != p_instance_ctrl->state, FSP_ERR_CTSU_SCANNING);

    if (CTSU_TUNING_COMPLETE == p_instance_ctrl->tuning)
    {
        for (element_id = 0; element_id < p_instance_ctrl->num_elements; element_id++)
        {
            /* Counter clear for re-offset tuning */
            *(p_instance_ctrl->p_element_complete_flag + element_id) = 0;
#if (BSP_FEATURE_CTSU_VERSION == 2)
            *(p_instance_ctrl->p_frequency_complete_flag + element_id) = 0;
#endif
            *(p_instance_ctrl->p_tuning_diff + element_id) = 0;
        }
    }

    p_instance_ctrl->tuning = CTSU_TUNING_INCOMPLETE;

    if (CTSU_STATE_SCANNED == p_instance_ctrl->state)
    {
        ctsu_correction_exec(p_instance_ctrl);

        if (CTSU_TUNING_INCOMPLETE == p_instance_ctrl->tuning)
        {
            if ((CTSU_MODE_SELF_MULTI_SCAN == p_instance_ctrl->md) ||
                (CTSU_MODE_MUTUAL_FULL_SCAN == p_instance_ctrl->md))
            {
                ctsu_initial_offset_tuning(p_instance_ctrl);
            }
        }

        p_instance_ctrl->state = CTSU_STATE_IDLE;
    }

    FSP_ERROR_RETURN(CTSU_TUNING_COMPLETE == p_instance_ctrl->tuning, FSP_ERR_CTSU_INCOMPLETE_TUNING);

    return err;
}

/*******************************************************************************************************************//**
 * @brief This function scan stops the sensor as scanning by the CTSU.
 * Implements @ref ctsu_api_t::scanStop.
 * @retval FSP_SUCCESS              CTSU successfully scan stop.
 * @retval FSP_ERR_ASSERTION        Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t R_CTSU_ScanStop (ctsu_ctrl_t * const p_ctrl)
{
    fsp_err_t              err             = FSP_SUCCESS;
    ctsu_instance_ctrl_t * p_instance_ctrl = (ctsu_instance_ctrl_t *) p_ctrl;
#if (CTSU_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_ctrl);
    FSP_ERROR_RETURN(CTSU_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    if (CTSU_STATE_SCANNING == p_instance_ctrl->state)
    {
#if (BSP_FEATURE_CTSU_VERSION == 2)
        R_CTSU->CTSUCRA ^= 0x11;
#else
        R_CTSU->CTSUCR0 ^= 0x11;
#endif

        R_BSP_IrqStatusClear(p_instance_ctrl->p_ctsu_cfg->write_irq);
        R_BSP_IrqStatusClear(p_instance_ctrl->p_ctsu_cfg->read_irq);
        R_BSP_IrqStatusClear(p_instance_ctrl->p_ctsu_cfg->end_irq);

        p_instance_ctrl->state    = CTSU_STATE_IDLE;
        p_instance_ctrl->wr_index = 0;
        p_instance_ctrl->rd_index = 0;
    }

    return err;
}

/*******************************************************************************************************************//**
 * Updates the user callback and has option of providing memory for callback structure.
 * Implements ctsu_api_t::callbackSet
 *
 * @retval  FSP_SUCCESS                  Callback updated successfully.
 * @retval  FSP_ERR_ASSERTION            A required pointer is NULL.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened.
 * @retval  FSP_ERR_NO_CALLBACK_MEMORY   p_callback is non-secure and p_callback_memory is either secure or NULL.
 **********************************************************************************************************************/
fsp_err_t R_CTSU_CallbackSet (ctsu_ctrl_t * const          p_api_ctrl,
                              void (                     * p_callback)(ctsu_callback_args_t *),
                              void const * const           p_context,
                              ctsu_callback_args_t * const p_callback_memory)
{
    ctsu_instance_ctrl_t * p_ctrl = (ctsu_instance_ctrl_t *) p_api_ctrl;

#if (CTSU_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_ctrl);
    FSP_ASSERT(p_callback);
    FSP_ERROR_RETURN(CTSU_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

#if BSP_TZ_SECURE_BUILD

    /* Get security state of p_callback */
    bool callback_is_secure =
        (NULL == cmse_check_address_range((void *) p_callback, sizeof(void *), CMSE_AU_NONSECURE));

 #if CTSU_CFG_PARAM_CHECKING_ENABLE

    /* In secure projects, p_callback_memory must be provided in non-secure space if p_callback is non-secure */
    ctsu_callback_args_t * const p_callback_memory_checked = cmse_check_pointed_object(p_callback_memory,
                                                                                       CMSE_AU_NONSECURE);
    FSP_ERROR_RETURN(callback_is_secure || (NULL != p_callback_memory_checked), FSP_ERR_NO_CALLBACK_MEMORY);
 #endif
#endif

    /* Store callback and context */
#if BSP_TZ_SECURE_BUILD
    p_ctrl->p_callback = callback_is_secure ? p_callback :
                         (void (*)(ctsu_callback_args_t *))cmse_nsfptr_create(p_callback);
#else
    p_ctrl->p_callback = p_callback;
#endif
    p_ctrl->p_context         = p_context;
    p_ctrl->p_callback_memory = p_callback_memory;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Disables specified CTSU control block. Implements @ref ctsu_api_t::close.
 *
 * @retval FSP_SUCCESS              CTSU successfully configured.
 * @retval FSP_ERR_ASSERTION        Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t R_CTSU_Close (ctsu_ctrl_t * const p_ctrl)
{
    fsp_err_t              err             = FSP_SUCCESS;
    ctsu_instance_ctrl_t * p_instance_ctrl = (ctsu_instance_ctrl_t *) p_ctrl;

    FSP_ASSERT(p_instance_ctrl);
    FSP_ERROR_RETURN(CTSU_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);

    g_ctsu_element_index = (uint8_t) (g_ctsu_element_index - p_instance_ctrl->num_elements);
#if (CTSU_CFG_NUM_SELF_ELEMENTS != 0)
    if (CTSU_MODE_SELF_MULTI_SCAN == (CTSU_MODE_MUTUAL_FULL_SCAN & p_instance_ctrl->md))
    {
        g_ctsu_self_element_index = (uint8_t) (g_ctsu_self_element_index - p_instance_ctrl->num_elements);
    }
#endif
#if (CTSU_CFG_NUM_MUTUAL_ELEMENTS != 0)
    if (CTSU_MODE_MUTUAL_FULL_SCAN == (CTSU_MODE_MUTUAL_FULL_SCAN & p_instance_ctrl->md))
    {
        g_ctsu_mutual_element_index = (uint8_t) (g_ctsu_mutual_element_index - p_instance_ctrl->num_elements);
    }
#endif
    if (0 == g_ctsu_element_index)
    {
#if (CTSU_CFG_DTC_SUPPORT_ENABLE == 1)
        err = ctsu_transfer_close(p_instance_ctrl);
#endif
    }

    p_instance_ctrl->state = CTSU_STATE_INIT;
    p_instance_ctrl->open  = false;

    return err;
}

/*******************************************************************************************************************//**
 * @brief This function gets the sensor specific data values as scanned by the CTSU.
 * Call this function after calling the R_CTSU_DataGet() function.
 *
 * By setting the third argument to CTSU_SPECIFIC_RAW_DATA,
 * RAW data can be output from the second argument.
 *
 * By setting the third argument to CTSU_SPECIFIC_CORRECTION_DATA,
 * the corrected data can be output from the second argument.
 *
 * By setting the third argument to CTSU_SPECIFIC_SELECTED_DATA,
 * Get bitmap of the frequency values used in majority decision from the second argument.
 * The bitmap is shown as follows.
 *
 * | 2bit                | 1bit                | 0bit                |
 * |---------------------|---------------------|---------------------|
 * | 3rd frequency value | 2nd frequency value | 1st frequency value |
 *
 * Implements @ref ctsu_api_t::specificDataGet.
 *
 * Example:
 * @snippet r_ctsu_example.c R_CTSU_SpecificDataGet
 *
 *
 * @retval FSP_SUCCESS              CTSU successfully configured.
 * @retval FSP_ERR_ASSERTION        Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 * @retval FSP_ERR_CTSU_SCANNING    Scanning this instance.
 * @retval FSP_ERR_CTSU_INCOMPLETE_TUNING      Incomplete initial offset tuning.
 * @retval FSP_ERR_NOT_ENABLED      CTSU_SPECIFIC_SELECTED_FREQ is not enabled in CTSU1.(CTSU2 Only)
 **********************************************************************************************************************/
fsp_err_t R_CTSU_SpecificDataGet (ctsu_ctrl_t * const       p_ctrl,
                                  uint16_t                * p_specific_data,
                                  ctsu_specific_data_type_t specific_data_type)
{
    fsp_err_t err = FSP_SUCCESS;
    uint16_t  element_id;
    uint16_t  i;
#if (BSP_FEATURE_CTSU_VERSION == 2)
    uint32_t                ctsuso;
    ctsu_correction_multi_t multi;
    uint32_t                snum;
    int32_t                 offset_unit;
#endif
    ctsu_instance_ctrl_t * p_instance_ctrl = (ctsu_instance_ctrl_t *) p_ctrl;

#if (CTSU_CFG_PARAM_CHECKING_ENABLE == 1)
    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_specific_data);
    FSP_ERROR_RETURN(CTSU_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif
    FSP_ERROR_RETURN(CTSU_STATE_SCANNING != p_instance_ctrl->state, FSP_ERR_CTSU_SCANNING);
    FSP_ERROR_RETURN(CTSU_TUNING_INCOMPLETE != p_instance_ctrl->tuning, FSP_ERR_CTSU_INCOMPLETE_TUNING);

#if (BSP_FEATURE_CTSU_VERSION == 1)
    FSP_ERROR_RETURN(CTSU_SPECIFIC_SELECTED_FREQ != specific_data_type, FSP_ERR_NOT_ENABLED);
#endif

    if (CTSU_SPECIFIC_RAW_DATA == specific_data_type)
    {
#if (CTSU_CFG_NUM_SELF_ELEMENTS != 0)
        if (CTSU_MODE_SELF_MULTI_SCAN == p_instance_ctrl->md)
        {
            for (element_id = 0; element_id < p_instance_ctrl->num_elements; element_id++)
            {
 #if (BSP_FEATURE_CTSU_VERSION == 1)
                *p_specific_data = (p_instance_ctrl->p_self_raw + element_id)->sen;
                p_specific_data++;
 #endif
 #if (BSP_FEATURE_CTSU_VERSION == 2)
                for (i = 0; i < CTSU_CFG_NUM_SUMULTI; i++)
                {
                    *p_specific_data = *(p_instance_ctrl->p_self_raw + (element_id * CTSU_CFG_NUM_SUMULTI) + i);
                    p_specific_data++;
                }
 #endif
            }
        }
#endif
#if (CTSU_CFG_NUM_MUTUAL_ELEMENTS != 0)
        if (CTSU_MODE_MUTUAL_FULL_SCAN == (CTSU_MODE_MUTUAL_FULL_SCAN & p_instance_ctrl->md))
        {
            for (element_id = 0; element_id < p_instance_ctrl->num_elements; element_id++)
            {
 #if (BSP_FEATURE_CTSU_VERSION == 1)
                *p_specific_data = (p_instance_ctrl->p_mutual_raw + element_id)->pri_sen;
                p_specific_data++;
                *p_specific_data = (p_instance_ctrl->p_mutual_raw + element_id)->snd_sen;
                p_specific_data++;
 #endif
 #if (BSP_FEATURE_CTSU_VERSION == 2)
                for (i = 0; i < CTSU_CFG_NUM_SUMULTI; i++)
                {
                    *p_specific_data =
                        *(p_instance_ctrl->p_mutual_raw + (element_id * CTSU_CFG_NUM_SUMULTI * 2) + (i * 2));
                    p_specific_data++;
                    *p_specific_data =
                        *(p_instance_ctrl->p_mutual_raw + (element_id * CTSU_CFG_NUM_SUMULTI * 2) + (i * 2) + 1);
                    p_specific_data++;
                }
 #endif
            }
        }
#endif
    }
    else if (CTSU_SPECIFIC_CORRECTION_DATA == specific_data_type)
    {
#if (CTSU_CFG_NUM_SELF_ELEMENTS != 0)
        if (CTSU_MODE_SELF_MULTI_SCAN == p_instance_ctrl->md)
        {
            for (element_id = 0; element_id < (p_instance_ctrl->num_elements); element_id++)
            {
 #if (BSP_FEATURE_CTSU_VERSION == 2)
                for (i = 0; i < CTSU_CFG_NUM_SUMULTI; i++)
                {
                    ctsuso =
                        (p_instance_ctrl->p_ctsuwr[(element_id * CTSU_CFG_NUM_SUMULTI) + i].ctsuso & CTSU_TUNING_MAX);
                    snum = (p_instance_ctrl->p_ctsuwr[(element_id * CTSU_CFG_NUM_SUMULTI)].ctsuso >> 10) &
                           CTSU_SNUM_MAX;
                    offset_unit =
                        (int32_t) ((CTSU_CORRECTION_OFFSET_UNIT * (snum + 1)) / (CTSU_SNUM_RECOMMEND + 1));
                    multi.offset[i] = (ctsuso * (uint32_t) (offset_unit >> (p_instance_ctrl->range)));

                    multi.pri[i] = *(p_instance_ctrl->p_self_corr + (element_id * CTSU_CFG_NUM_SUMULTI) + i);
                    multi.snd[i] = 0;
                }
                ctsu_correction_fleq(&multi, (p_instance_ctrl->p_self_corr + (element_id * CTSU_CFG_NUM_SUMULTI)),
                                     NULL);
 #endif
                for (i = 0; i < CTSU_CFG_NUM_SUMULTI; i++)
                {
                    *p_specific_data = *(p_instance_ctrl->p_self_corr + (element_id * CTSU_CFG_NUM_SUMULTI) + i);
                    p_specific_data++;
                }
            }
        }
#endif
#if (CTSU_CFG_NUM_MUTUAL_ELEMENTS != 0)
        if (CTSU_MODE_MUTUAL_FULL_SCAN == (CTSU_MODE_MUTUAL_FULL_SCAN & p_instance_ctrl->md))
        {
            for (element_id = 0; element_id < (p_instance_ctrl->num_elements); element_id++)
            {
 #if (BSP_FEATURE_CTSU_VERSION == 2)
                for (i = 0; i < CTSU_CFG_NUM_SUMULTI; i++)
                {
                    ctsuso =
                        (p_instance_ctrl->p_ctsuwr[(element_id * CTSU_CFG_NUM_SUMULTI) + i].ctsuso & CTSU_TUNING_MAX);
                    snum = (p_instance_ctrl->p_ctsuwr[(element_id * CTSU_CFG_NUM_SUMULTI)].ctsuso >> 10) &
                           CTSU_SNUM_MAX;
                    offset_unit =
                        (int32_t) ((CTSU_CORRECTION_OFFSET_UNIT * (snum + 1)) / (CTSU_SNUM_RECOMMEND + 1));
                    multi.offset[i] = (ctsuso * (uint32_t) (offset_unit >> (p_instance_ctrl->range)));

                    multi.pri[i] = *(p_instance_ctrl->p_mutual_pri_corr + (element_id * CTSU_CFG_NUM_SUMULTI) + i);
                    multi.snd[i] = *(p_instance_ctrl->p_mutual_snd_corr + (element_id * CTSU_CFG_NUM_SUMULTI) + i);
                }
                ctsu_correction_fleq(&multi,
                                     (p_instance_ctrl->p_mutual_pri_corr + (element_id * CTSU_CFG_NUM_SUMULTI)),
                                     (p_instance_ctrl->p_mutual_snd_corr + (element_id * CTSU_CFG_NUM_SUMULTI)));
 #endif
                for (i = 0; i < CTSU_CFG_NUM_SUMULTI; i++)
                {
                    *p_specific_data = *(p_instance_ctrl->p_mutual_pri_corr + (element_id * CTSU_CFG_NUM_SUMULTI) + i);
                    p_specific_data++;
                    *p_specific_data = *(p_instance_ctrl->p_mutual_snd_corr + (element_id * CTSU_CFG_NUM_SUMULTI) + i);
                    p_specific_data++;
                }
            }
        }
#endif
    }

#if (BSP_FEATURE_CTSU_VERSION == 2)
    else if (CTSU_SPECIFIC_SELECTED_FREQ == specific_data_type)
    {
 #if (CTSU_CFG_NUM_SELF_ELEMENTS != 0)
        if (CTSU_MODE_SELF_MULTI_SCAN == p_instance_ctrl->md)
        {
            for (element_id = 0; element_id < (p_instance_ctrl->num_elements); element_id++)
            {
                *p_specific_data = *(p_instance_ctrl->p_selected_freq_self + element_id);
                p_specific_data++;
            }
        }
 #endif
 #if (CTSU_CFG_NUM_MUTUAL_ELEMENTS != 0)
        if (CTSU_MODE_MUTUAL_FULL_SCAN == (CTSU_MODE_MUTUAL_FULL_SCAN & p_instance_ctrl->md))
        {
            for (element_id = 0; element_id < (p_instance_ctrl->num_elements); element_id++)
            {
                *p_specific_data = *(p_instance_ctrl->p_selected_freq_mutual + element_id);
                p_specific_data++;
            }
        }
 #endif
    }
#endif
    else
    {
    }

    return err;
}

/*******************************************************************************************************************//**
 * @brief This function inserts the value of the second argument as the measurement result value.
 * Call this function after calling the R_CTSU_DataInsert() function.
 * Implements @ref ctsu_api_t::dataInsert.
 *
 * Example:
 * @snippet r_ctsu_example.c R_CTSU_DataInsert
 *
 * @retval FSP_SUCCESS              CTSU successfully configured.
 * @retval FSP_ERR_ASSERTION        Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 * @retval FSP_ERR_CTSU_SCANNING    Scanning this instance.
 * @retval FSP_ERR_CTSU_INCOMPLETE_TUNING      Incomplete initial offset tuning.
 **********************************************************************************************************************/
fsp_err_t R_CTSU_DataInsert (ctsu_ctrl_t * const p_ctrl, uint16_t * p_insert_data)
{
    fsp_err_t              err             = FSP_SUCCESS;
    ctsu_instance_ctrl_t * p_instance_ctrl = (ctsu_instance_ctrl_t *) p_ctrl;
    uint16_t               element_id;

#if (CTSU_CFG_PARAM_CHECKING_ENABLE == 1)
    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_insert_data);
    FSP_ERROR_RETURN(CTSU_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif
    FSP_ERROR_RETURN(CTSU_STATE_SCANNING != p_instance_ctrl->state, FSP_ERR_CTSU_SCANNING);
    FSP_ERROR_RETURN(CTSU_TUNING_INCOMPLETE != p_instance_ctrl->tuning, FSP_ERR_CTSU_INCOMPLETE_TUNING);

#if (CTSU_CFG_NUM_SELF_ELEMENTS != 0)
    if (CTSU_MODE_SELF_MULTI_SCAN == (CTSU_MODE_MUTUAL_FULL_SCAN & p_instance_ctrl->md))
    {
        /* Data output */
        for (element_id = 0; element_id < p_instance_ctrl->num_elements; element_id++)
        {
            (p_instance_ctrl->p_self_data + element_id)->int_data = *p_insert_data;
            p_insert_data++;
        }
    }
#endif
#if (CTSU_CFG_NUM_MUTUAL_ELEMENTS != 0)
    if (CTSU_MODE_MUTUAL_FULL_SCAN == (CTSU_MODE_MUTUAL_FULL_SCAN & p_instance_ctrl->md))
    {
        for (element_id = 0; element_id < p_instance_ctrl->num_elements; element_id++)
        {
            (p_instance_ctrl->p_mutual_pri_data + element_id)->int_data = *p_insert_data;
            p_insert_data++;
            (p_instance_ctrl->p_mutual_snd_data + element_id)->int_data = *p_insert_data;
            p_insert_data++;
        }
    }
#endif

    return err;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup CTSU)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Internal ctsu private function.
 **********************************************************************************************************************/

#if (CTSU_CFG_DTC_SUPPORT_ENABLE == 1)

/***********************************************************************************************************************
 * ctsu_transfer_open
 ***********************************************************************************************************************/
fsp_err_t ctsu_transfer_open (ctsu_instance_ctrl_t * const p_instance_ctrl)
{
    fsp_err_t err;
    transfer_instance_t const * p_transfer;
    transfer_info_t           * p_info;
    transfer_cfg_t              cfg;

    /* CTSUWR setting */
    p_transfer = p_instance_ctrl->p_ctsu_cfg->p_transfer_tx;
    p_info     = p_transfer->p_cfg->p_info;
    cfg        = *(p_transfer->p_cfg);

    p_info->transfer_settings_word_b.chain_mode    = TRANSFER_CHAIN_MODE_DISABLED;
    p_info->transfer_settings_word_b.src_addr_mode = TRANSFER_ADDR_MODE_INCREMENTED;
    p_info->transfer_settings_word_b.irq           = TRANSFER_IRQ_END;
 #if (BSP_FEATURE_CTSU_VERSION == 2)
    p_info->transfer_settings_word_b.dest_addr_mode = TRANSFER_ADDR_MODE_FIXED;
    p_info->transfer_settings_word_b.size           = TRANSFER_SIZE_4_BYTE;
    p_info->p_dest = (void *) &R_CTSU->CTSUSO;
    p_info->transfer_settings_word_b.mode        = TRANSFER_MODE_BLOCK;
    p_info->transfer_settings_word_b.repeat_area = TRANSFER_REPEAT_AREA_DESTINATION;
    p_info->length = 1;
 #endif
 #if (BSP_FEATURE_CTSU_VERSION == 1)
    p_info->transfer_settings_word_b.dest_addr_mode = TRANSFER_ADDR_MODE_INCREMENTED;
    p_info->transfer_settings_word_b.size           = TRANSFER_SIZE_2_BYTE;
    p_info->p_dest = (void *) &R_CTSU->CTSUSSC;
    p_info->transfer_settings_word_b.mode        = TRANSFER_MODE_BLOCK;
    p_info->transfer_settings_word_b.repeat_area = TRANSFER_REPEAT_AREA_DESTINATION;
    p_info->length = 3;
 #endif
    p_info->p_src = p_instance_ctrl->p_ctsuwr;

    err = p_transfer->p_api->open(p_transfer->p_ctrl, &cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    err = p_transfer->p_api->enable(p_transfer->p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* CTSURD setting */
    p_transfer = p_instance_ctrl->p_ctsu_cfg->p_transfer_rx;
    p_info     = p_transfer->p_cfg->p_info;
    cfg        = *(p_transfer->p_cfg);

    p_info->transfer_settings_word_b.chain_mode     = TRANSFER_CHAIN_MODE_DISABLED;
    p_info->transfer_settings_word_b.dest_addr_mode = TRANSFER_ADDR_MODE_INCREMENTED;
    p_info->transfer_settings_word_b.irq            = TRANSFER_IRQ_END;
 #if (BSP_FEATURE_CTSU_VERSION == 2)
    p_info->transfer_settings_word_b.src_addr_mode = TRANSFER_ADDR_MODE_FIXED;
    p_info->transfer_settings_word_b.size          = TRANSFER_SIZE_2_BYTE;
    p_info->p_dest = p_instance_ctrl->p_mutual_raw;
    p_info->transfer_settings_word_b.mode        = TRANSFER_MODE_BLOCK;
    p_info->transfer_settings_word_b.repeat_area = TRANSFER_REPEAT_AREA_SOURCE;
    p_info->length = 1;
 #endif
 #if (BSP_FEATURE_CTSU_VERSION == 1)
    p_info->transfer_settings_word_b.src_addr_mode = TRANSFER_ADDR_MODE_INCREMENTED;
    p_info->transfer_settings_word_b.size          = TRANSFER_SIZE_2_BYTE;
    p_info->transfer_settings_word_b.mode          = TRANSFER_MODE_BLOCK;
    p_info->transfer_settings_word_b.repeat_area   = TRANSFER_REPEAT_AREA_SOURCE;
    p_info->length = 2;
 #endif
    p_info->p_src  = (void *) &R_CTSU->CTSUSC;
    p_info->p_dest = p_instance_ctrl->p_self_raw;
 #if (CTSU_CFG_NUM_MUTUAL_ELEMENTS != 0)
    if (CTSU_MODE_MUTUAL_FULL_SCAN == (CTSU_MODE_MUTUAL_FULL_SCAN & p_instance_ctrl->md))
    {
        p_info->p_dest = p_instance_ctrl->p_mutual_raw;
    }
 #endif

    err = p_transfer->p_api->open(p_transfer->p_ctrl, &cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    err = p_transfer->p_api->enable(p_transfer->p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/***********************************************************************************************************************
 * ctsu_transfer_close
 ***********************************************************************************************************************/
fsp_err_t ctsu_transfer_close (ctsu_instance_ctrl_t * const p_instance_ctrl)
{
    fsp_err_t err;
    transfer_instance_t const * p_transfer;

    /* CTSUWR setting */
    p_transfer = p_instance_ctrl->p_ctsu_cfg->p_transfer_tx;
    err        = p_transfer->p_api->close(p_transfer->p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* CTSURD setting */
    p_transfer = p_instance_ctrl->p_ctsu_cfg->p_transfer_rx;
    err        = p_transfer->p_api->close(p_transfer->p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/***********************************************************************************************************************
 * ctsu_transfer_configure
 ***********************************************************************************************************************/
fsp_err_t ctsu_transfer_configure (ctsu_instance_ctrl_t * const p_instance_ctrl)
{
    fsp_err_t err;
    transfer_instance_t const * p_transfer;
    transfer_info_t           * p_info;
 #if (BSP_FEATURE_CTSU_VERSION == 2)
  #if (CTSU_CFG_NUM_MUTUAL_ELEMENTS != 0)
    uint16_t transfer_mutual_num_elements;
  #endif
 #endif

    /* CTSUWR setting */
    p_transfer = p_instance_ctrl->p_ctsu_cfg->p_transfer_tx;
    p_info     = p_transfer->p_cfg->p_info;
 #if (BSP_FEATURE_CTSU_VERSION == 2)
    p_info->length = 1;
    if (CTSU_CORRECTION_RUN == g_ctsu_correction_info.status)
    {
        p_info->num_blocks = 1;
        p_info->p_src      = (void *) &(g_ctsu_correction_info.ctsuwr);
    }

  #if (CTSU_CFG_NUM_CFC != 0)
    else if (CTSU_CORRECTION_RUN == g_ctsu_corrcfc_info.status)
    {
        p_info->num_blocks = 1;
        p_info->p_src      = (void *) &(g_ctsu_corrcfc_info.ctsuwr);
    }
  #endif
  #if (CTSU_CFG_DIAG_SUPPORT_ENABLE == 1)
    else if (CTSU_MODE_DIAGNOSIS_SCAN == p_instance_ctrl->md)
    {
        if (CTSU_DIAG_CLOCK_RECOVERY == g_ctsu_diag_info.state)
        {
            p_info->transfer_settings_word_b.src_addr_mode = TRANSFER_ADDR_MODE_FIXED;
            p_info->num_blocks = 3;
        }
        else if ((CTSU_DIAG_INIT == g_ctsu_diag_info.state) || (CTSU_DIAG_OUTPUT_VOLTAGE == g_ctsu_diag_info.state) ||
                 (CTSU_DIAG_OVER_VOLTAGE == g_ctsu_diag_info.state) ||
                 (CTSU_DIAG_OVER_CURRENT == g_ctsu_diag_info.state))
        {
            p_info->transfer_settings_word_b.src_addr_mode = TRANSFER_ADDR_MODE_FIXED;
            p_info->num_blocks = 2;
        }
        else
        {
            p_info->transfer_settings_word_b.src_addr_mode = TRANSFER_ADDR_MODE_INCREMENTED;
            p_info->num_blocks = 1;
        }

        p_info->p_src = (void *) &(g_ctsu_diag_info.ctsuwr);
    }
  #endif
    else
    {
        p_info->transfer_settings_word_b.src_addr_mode = TRANSFER_ADDR_MODE_INCREMENTED;

        if (CTSU_MODE_CURRENT_SCAN == p_instance_ctrl->md)
        {
            p_info->num_blocks = p_instance_ctrl->num_elements;
        }
        else
        {
            p_info->num_blocks = (uint16_t) (p_instance_ctrl->num_elements * CTSU_CFG_NUM_SUMULTI);

  #if (CTSU_CFG_NUM_MUTUAL_ELEMENTS != 0)
            if (CTSU_MODE_MUTUAL_FULL_SCAN == (CTSU_MODE_MUTUAL_FULL_SCAN & p_instance_ctrl->md))
            {
                if (true == p_instance_ctrl->serial_tuning_enable)
                {
                    if (0 == ((p_instance_ctrl->ctsucr1 >> 7) & 0x01))
                    {
                        transfer_mutual_num_elements = 0;
                        ctsu_transer_count_element(p_instance_ctrl->ctsuchac0, &transfer_mutual_num_elements);
                        ctsu_transer_count_element(p_instance_ctrl->ctsuchac1, &transfer_mutual_num_elements);
                        ctsu_transer_count_element(p_instance_ctrl->ctsuchac2, &transfer_mutual_num_elements);
                        ctsu_transer_count_element(p_instance_ctrl->ctsuchac3, &transfer_mutual_num_elements);
                        ctsu_transer_count_element(p_instance_ctrl->ctsuchac4, &transfer_mutual_num_elements);

                        p_info->num_blocks = transfer_mutual_num_elements * CTSU_CFG_NUM_SUMULTI;
                    }
                }
            }
  #endif
        }

        p_info->p_src = p_instance_ctrl->p_ctsuwr;
    }
 #endif
 #if (BSP_FEATURE_CTSU_VERSION == 1)
    p_info->length = 3;
    if (CTSU_CORRECTION_RUN == g_ctsu_correction_info.status)
    {
        p_info->num_blocks = 1;
        p_info->p_src      = (void *) &(g_ctsu_correction_info.ctsuwr);
    }

  #if (CTSU_CFG_DIAG_SUPPORT_ENABLE == 1)
    else if (CTSU_MODE_DIAGNOSIS_SCAN == p_instance_ctrl->md)
    {
        p_info->num_blocks = 1;
        p_info->p_src      = (void *) &(g_ctsu_diag_info.ctsuwr);
    }
  #endif
    else if ((CTSU_CORRECTION_RUN != g_ctsu_correction_info.status) &&
             (CTSU_MODE_DIAGNOSIS_SCAN != p_instance_ctrl->md))
    {
        p_info->num_blocks = p_instance_ctrl->num_elements;
        p_info->p_src      = p_instance_ctrl->p_ctsuwr;
  #if (CTSU_CFG_NUM_MUTUAL_ELEMENTS != 0)
        if (CTSU_MODE_MUTUAL_FULL_SCAN == (CTSU_MODE_MUTUAL_FULL_SCAN & p_instance_ctrl->md))
        {
            if (true == p_instance_ctrl->serial_tuning_enable)
            {
                if (0 == ((p_instance_ctrl->ctsucr1 >> 7) & 0x01))
                {
                    p_info->num_blocks = p_instance_ctrl->num_elements * 2;
                }
            }
        }
  #endif
    }
    else
    {
    }
 #endif
    err = p_transfer->p_api->reconfigure(p_transfer->p_ctrl, p_info);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* CTSURD setting */
    p_transfer = p_instance_ctrl->p_ctsu_cfg->p_transfer_rx;
    p_info     = p_transfer->p_cfg->p_info;
 #if (BSP_FEATURE_CTSU_VERSION == 2)
    p_info->length = 1;
    if (CTSU_CORRECTION_RUN == g_ctsu_correction_info.status)
    {
        p_info->transfer_settings_word_b.size = TRANSFER_SIZE_2_BYTE;
        p_info->num_blocks = 1;
        p_info->p_dest     = (void *) &g_ctsu_correction_info.scanbuf;
        p_info->p_src      = (void *) &R_CTSU->CTSUSC;
    }

  #if (CTSU_CFG_NUM_CFC != 0)
    else if (CTSU_CORRECTION_RUN == g_ctsu_corrcfc_info.status)
    {
        p_info->transfer_settings_word_b.size = TRANSFER_SIZE_2_BYTE;
        p_info->length     = g_ctsu_corrcfc_info.num_ts;
        p_info->num_blocks = 1;
        p_info->p_dest     = (void *) g_ctsu_corrcfc_info.scanbuf;
        p_info->p_src      = (void *) &R_CTSU->CTSUCFCCNT;
    }
  #endif
  #if (CTSU_CFG_DIAG_SUPPORT_ENABLE == 1)
    else if (CTSU_MODE_DIAGNOSIS_SCAN == p_instance_ctrl->md)
    {
        p_info->transfer_settings_word_b.size = TRANSFER_SIZE_4_BYTE;
        if (CTSU_DIAG_CLOCK_RECOVERY == g_ctsu_diag_info.state)
        {
            p_info->num_blocks = 3;
        }
        else if ((CTSU_DIAG_INIT == g_ctsu_diag_info.state) || (CTSU_DIAG_OUTPUT_VOLTAGE == g_ctsu_diag_info.state) ||
                 (CTSU_DIAG_OVER_VOLTAGE == g_ctsu_diag_info.state) ||
                 (CTSU_DIAG_OVER_CURRENT == g_ctsu_diag_info.state))
        {
            p_info->num_blocks = 2;
        }
        else
        {
            p_info->num_blocks = 1;
        }

        p_info->p_dest = (void *) &g_ctsu_diag_info.ctsuscnt;
        if (CTSU_DIAG_CFC == g_ctsu_diag_info.state)
        {
            p_info->p_src = (void *) &R_CTSU->CTSUCFCCNT;
        }
        else
        {
            p_info->p_src = (void *) &R_CTSU->CTSUSCNT;
        }
    }
  #endif
    else
    {
        p_info->transfer_settings_word_b.size = TRANSFER_SIZE_2_BYTE;

        if (CTSU_MODE_CURRENT_SCAN == p_instance_ctrl->md)
        {
            p_info->num_blocks = p_instance_ctrl->num_elements;
        }
        else
        {
            p_info->num_blocks = (uint16_t) (p_instance_ctrl->num_elements * CTSU_CFG_NUM_SUMULTI);
        }

        p_info->p_dest = p_instance_ctrl->p_self_raw;
        p_info->p_src  = (void *) &R_CTSU->CTSUSC;
  #if (CTSU_CFG_NUM_MUTUAL_ELEMENTS != 0)
        if (CTSU_MODE_MUTUAL_FULL_SCAN == (CTSU_MODE_MUTUAL_FULL_SCAN & p_instance_ctrl->md))
        {
            p_info->p_dest     = p_instance_ctrl->p_mutual_raw;
            p_info->num_blocks = (uint16_t) (p_info->num_blocks * 2); ///< Primary and Secondary
        }

   #if (CTSU_CFG_NUM_CFC != 0)
        if (CTSU_MODE_MUTUAL_CFC_SCAN == p_instance_ctrl->md)
        {
            p_info->length     = p_instance_ctrl->p_ctsu_cfg->num_rx;
            p_info->num_blocks = (uint16_t) (p_info->num_blocks / p_instance_ctrl->p_ctsu_cfg->num_rx);
            p_info->p_src      = (void *) &R_CTSU->CTSUCFCCNT;
        }
   #endif
  #endif
    }
 #endif
 #if (BSP_FEATURE_CTSU_VERSION == 1)
    p_info->length = 2;
    if (CTSU_CORRECTION_RUN == g_ctsu_correction_info.status)
    {
        p_info->num_blocks = 1;
        p_info->p_dest     = (void *) &g_ctsu_correction_info.scanbuf;
    }

  #if (CTSU_CFG_DIAG_SUPPORT_ENABLE == 1)
    else if (CTSU_MODE_DIAGNOSIS_SCAN == p_instance_ctrl->md)
    {
        p_info->num_blocks = 1;
        p_info->p_dest     = (void *) &g_ctsu_diag_info.scanbuf;
    }
  #endif
    else if ((CTSU_CORRECTION_RUN != g_ctsu_correction_info.status) &&
             (CTSU_MODE_DIAGNOSIS_SCAN != p_instance_ctrl->md))
    {
        p_info->num_blocks = p_instance_ctrl->num_elements;
        p_info->p_dest     = p_instance_ctrl->p_self_raw;
  #if (CTSU_CFG_NUM_MUTUAL_ELEMENTS != 0)
        if (CTSU_MODE_MUTUAL_FULL_SCAN == (CTSU_MODE_MUTUAL_FULL_SCAN & p_instance_ctrl->md))
        {
            p_info->p_dest     = p_instance_ctrl->p_mutual_raw;
            p_info->num_blocks = (uint16_t) (p_info->num_blocks * 2); ///< Primary and Secondary

            if (true == p_instance_ctrl->serial_tuning_enable)
            {
                if (0 == ((p_instance_ctrl->ctsucr1 >> 7) & 0x01))
                {
                    p_info->num_blocks = p_instance_ctrl->num_elements * 2;
                }
            }
        }
  #endif
    }
    else
    {
    }
 #endif
    err = p_transfer->p_api->reconfigure(p_transfer->p_ctrl, p_info);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

 #if (BSP_FEATURE_CTSU_VERSION == 2)
  #if (CTSU_CFG_NUM_MUTUAL_ELEMENTS != 0)
static void ctsu_transer_count_element (uint32_t element_mask, uint16_t * num_element)
{
    uint8_t n;

    /* Get the number of measurable elements from enabled CHAC or CHTRC  */
    for (n = 0; n < CTSU_TRANSFER_TUNING_CH_REG_MAX_NUM; n++)
    {
        if (0x00000001 == ((element_mask >> n) & 0x00000001))
        {
            (*num_element)++;
        }
    }
}

  #endif
 #endif

#endif

/***********************************************************************************************************************
 * ctsu_initial_offset_tuning
 ***********************************************************************************************************************/
void ctsu_initial_offset_tuning (ctsu_instance_ctrl_t * const p_instance_ctrl)
{
    uint16_t element_id;
    int32_t  diff          = 0;
    uint32_t complete_flag = 0;
    uint32_t num_complete  = 0;
    uint16_t target_val;
#if (BSP_FEATURE_CTSU_VERSION == 1)
    uint16_t               ctsuso;
    ctsu_correction_calc_t calc;
#endif
#if (BSP_FEATURE_CTSU_VERSION == 2)
    uint16_t i;
    uint16_t element_top;
    uint16_t corr_data[CTSU_CFG_NUM_SUMULTI];
    int32_t  ctsuso;
    uint32_t snum;
    int32_t  offset_unit;
#endif

    /* element_id through each element for control block */
    for (element_id = 0; element_id < p_instance_ctrl->num_elements; element_id++)
    {
        if (0 == *(p_instance_ctrl->p_element_complete_flag + element_id))
        {
#if (BSP_FEATURE_CTSU_VERSION == 1)
            if (CTSU_MODE_SELF_MULTI_SCAN == p_instance_ctrl->md)
            {
                target_val = (p_instance_ctrl->tuning_self_target_value);
            }
            else
            {
                target_val = (p_instance_ctrl->tuning_mutual_target_value);
            }

            calc.snum  = (p_instance_ctrl->p_ctsuwr[element_id].ctsuso0 >> 10) & CTSU_SNUM_MAX;
            calc.sdpa  = (p_instance_ctrl->p_ctsuwr[element_id].ctsuso1 >> 8) & CTSU_SDPA_MAX;
            target_val = (uint16_t) (target_val *
                                     (uint32_t) ((calc.snum + 1) * (calc.sdpa + 1)) /
                                     g_ctsu_correction_info.ctsu_clock);
 #if (CTSU_CFG_NUM_SELF_ELEMENTS != 0)
            if (CTSU_MODE_SELF_MULTI_SCAN == p_instance_ctrl->md)
            {
                diff = (p_instance_ctrl->p_self_data + element_id)->int_data - target_val;
            }
 #endif
 #if (CTSU_CFG_NUM_MUTUAL_ELEMENTS != 0)
            if (CTSU_MODE_MUTUAL_FULL_SCAN == p_instance_ctrl->md)
            {
                diff = (p_instance_ctrl->p_mutual_pri_data + element_id)->int_data - target_val;
            }
 #endif
            ctsuso = (p_instance_ctrl->p_ctsuwr[element_id].ctsuso0 & CTSU_TUNING_MAX);
            if (0 < diff)
            {
                if (*(p_instance_ctrl->p_tuning_diff + element_id) < 0)
                {
                    if ((-diff) > *(p_instance_ctrl->p_tuning_diff + element_id))
                    {
                        ctsuso++;      ///< Decrease count
                    }

                    complete_flag = 1;
                }
                else
                {
                    if (CTSU_TUNING_MAX == ctsuso) /* CTSUSO limit check    */
                    {
                        complete_flag = 1;
                    }
                    else
                    {
                        ctsuso++;                                                ///< Decrease count
                        (*(p_instance_ctrl->p_tuning_diff + element_id)) = diff; ///< Plus
                    }
                }
            }
            else if (0 == diff)
            {
                complete_flag = 1;
            }
            else
            {
                if (*(p_instance_ctrl->p_tuning_diff + element_id) > 0)
                {
                    if ((-diff) > *(p_instance_ctrl->p_tuning_diff + element_id))
                    {
                        ctsuso--;      ///< Increase count
                    }

                    complete_flag = 1;
                }
                else
                {
                    if (CTSU_TUNING_MIN == ctsuso) /* CTSUSO limit check    */
                    {
                        complete_flag = 1;
                    }
                    else
                    {
                        ctsuso--;                                                ///< Increase count
                        (*(p_instance_ctrl->p_tuning_diff + element_id)) = diff; ///< Minus
                    }
                }
            }

            p_instance_ctrl->p_ctsuwr[element_id].ctsuso0 &= (uint16_t) (~CTSU_TUNING_MAX);
            p_instance_ctrl->p_ctsuwr[element_id].ctsuso0 |= ctsuso;
#endif
#if (BSP_FEATURE_CTSU_VERSION == 2)
            element_top = (uint16_t) (element_id * CTSU_CFG_NUM_SUMULTI);
            for (i = 0; i < CTSU_CFG_NUM_SUMULTI; i++)
            {
                /* Adjust only frequencies for which offset tuning is not completed */
                if (0 == (p_instance_ctrl->p_frequency_complete_flag[element_id] & (1 << i)))
                {
                    if (CTSU_MODE_SELF_MULTI_SCAN == p_instance_ctrl->md)
                    {
                        target_val = (p_instance_ctrl->tuning_self_target_value / 2);
                    }
                    else
                    {
                        target_val = (p_instance_ctrl->tuning_mutual_target_value / 2);
                    }

                    if (CTSU_MODE_SELF_MULTI_SCAN == p_instance_ctrl->md)
                    {
                        corr_data[i] = p_instance_ctrl->p_self_corr[element_top + i];
                    }
                    else
                    {
                        corr_data[i] = p_instance_ctrl->p_mutual_pri_corr[element_top + i];
                    }

                    snum = (p_instance_ctrl->p_ctsuwr[(element_id * CTSU_CFG_NUM_SUMULTI)].ctsuso >> 10) &
                           CTSU_SNUM_MAX;
                    target_val  = (uint16_t) (((uint32_t) target_val * (snum + 1)) / (CTSU_SNUM_RECOMMEND + 1));
                    offset_unit = (int32_t) ((CTSU_CORRECTION_OFFSET_UNIT * (snum + 1)) / (CTSU_SNUM_RECOMMEND + 1));

                    /* Calculate CTSUSO equivalent difference between current value and target value */
                    diff = (int32_t) ((int32_t) corr_data[i] - (int32_t) target_val) /
                           (offset_unit >> p_instance_ctrl->range);

                    ctsuso  = (int32_t) (p_instance_ctrl->p_ctsuwr[element_top + i].ctsuso & CTSU_TUNING_MAX);
                    ctsuso += diff;

                    /* If the CTSUSO exceeds the minimum value or the maximum value, tuning complete */
                    if (ctsuso < 0)
                    {
                        ctsuso = 0;
                        p_instance_ctrl->p_frequency_complete_flag[element_id] += (uint8_t) (1 << i);
                    }
                    else if (ctsuso > CTSU_TUNING_MAX)
                    {
                        ctsuso = CTSU_TUNING_MAX;
                        p_instance_ctrl->p_frequency_complete_flag[element_id] += (uint8_t) (1 << i);
                    }
                    else
                    {
                        /* If the difference is large, tuning value may not be able to match, so create the next opportunity */
                        if (0 == diff)
                        {
                            p_instance_ctrl->p_frequency_complete_flag[element_id] += (uint8_t) (1 << i);
                        }
                    }

                    /* Set the result of the calculated CTSUSO */
                    p_instance_ctrl->p_ctsuwr[element_top + i].ctsuso &= (uint32_t) (~CTSU_TUNING_MAX);
                    p_instance_ctrl->p_ctsuwr[element_top + i].ctsuso |= (uint32_t) ctsuso;
                }

                /* Add completion status for each frequency */
                complete_flag += ((p_instance_ctrl->p_frequency_complete_flag[element_id] >> i) & 1);
            }
#endif
        }
        else
        {
            complete_flag = CTSU_CFG_NUM_SUMULTI;
        }

        if (CTSU_CFG_NUM_SUMULTI == complete_flag)
        {
            num_complete++;
            *(p_instance_ctrl->p_element_complete_flag + element_id) = 1;
        }

        complete_flag = 0;
    }

    if (num_complete == p_instance_ctrl->num_elements)
    {
        p_instance_ctrl->tuning = CTSU_TUNING_COMPLETE;
    }
}

/***********************************************************************************************************************
 * ctsu_moving_average
 ***********************************************************************************************************************/
void ctsu_moving_average (ctsu_data_t * p_average, uint16_t new_data, uint16_t average_num)
{
    uint32_t work;

    work  = (uint32_t) (((uint32_t) p_average->int_data << CTSU_CFG_DECIMAL_POINT) + p_average->decimal_point_data);
    work -= (uint32_t) (work / average_num);
    work += (uint32_t) (((uint32_t) new_data << CTSU_CFG_DECIMAL_POINT) / average_num);

    p_average->int_data           = (uint16_t) (work >> CTSU_CFG_DECIMAL_POINT);
    p_average->decimal_point_data = (uint16_t) (work & CTSU_CFG_DECIMAL_POINT_MASK);
}

/***********************************************************************************************************************
 * CTSUWR interrupt handler. This service routine sets the tuning for the next element to be scanned by hardware.
 ***********************************************************************************************************************/
void ctsu_write_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

#if (CTSU_CFG_DTC_SUPPORT_ENABLE == 1)

    /** Clear the BSP IRQ Flag     */
    R_BSP_IrqStatusClear(R_FSP_CurrentIrqGet());

#else
    IRQn_Type irq = R_FSP_CurrentIrqGet();
    ctsu_instance_ctrl_t * p_instance_ctrl = (ctsu_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    /** Clear the BSP IRQ Flag     */
    R_BSP_IrqStatusClear(R_FSP_CurrentIrqGet());

    /* Write settings for current element */
    if (CTSU_CORRECTION_RUN == g_ctsu_correction_info.status)
    {
 #if (BSP_FEATURE_CTSU_VERSION == 2)
        R_CTSU->CTSUSO = g_ctsu_correction_info.ctsuwr.ctsuso;
 #endif
 #if (BSP_FEATURE_CTSU_VERSION == 1)
        R_CTSU->CTSUSSC = g_ctsu_correction_info.ctsuwr.ctsussc;
        R_CTSU->CTSUSO0 = g_ctsu_correction_info.ctsuwr.ctsuso0;
        R_CTSU->CTSUSO1 = g_ctsu_correction_info.ctsuwr.ctsuso1;
 #endif
    }

 #if (BSP_FEATURE_CTSU_VERSION == 2)
  #if (CTSU_CFG_NUM_CFC != 0)
    else if ((CTSU_CORRECTION_RUN == g_ctsu_corrcfc_info.status))
    {
        R_CTSU->CTSUSO = g_ctsu_corrcfc_info.ctsuwr.ctsuso;
    }
  #endif
 #endif
    else if (CTSU_MODE_DIAGNOSIS_SCAN == p_instance_ctrl->md)
    {
 #if (BSP_FEATURE_CTSU_VERSION == 2)
  #if (CTSU_CFG_DIAG_SUPPORT_ENABLE == 1)
        R_CTSU->CTSUSO = g_ctsu_diag_info.ctsuwr.ctsuso;
        p_instance_ctrl->wr_index++;
  #endif
 #endif
 #if (BSP_FEATURE_CTSU_VERSION == 1)
  #if (CTSU_CFG_DIAG_SUPPORT_ENABLE == 1)
        R_CTSU->CTSUSSC = g_ctsu_diag_info.ctsuwr.ctsussc;
        R_CTSU->CTSUSO0 = g_ctsu_diag_info.ctsuwr.ctsuso0;
        R_CTSU->CTSUSO1 = g_ctsu_diag_info.ctsuwr.ctsuso1;
  #endif
 #endif
    }
    else
    {
 #if (BSP_FEATURE_CTSU_VERSION == 2)
        R_CTSU->CTSUSO = p_instance_ctrl->p_ctsuwr[p_instance_ctrl->wr_index].ctsuso;
 #endif
 #if (BSP_FEATURE_CTSU_VERSION == 1)
        R_CTSU->CTSUSSC = p_instance_ctrl->p_ctsuwr[p_instance_ctrl->wr_index].ctsussc;
        R_CTSU->CTSUSO0 = p_instance_ctrl->p_ctsuwr[p_instance_ctrl->wr_index].ctsuso0;
        R_CTSU->CTSUSO1 = p_instance_ctrl->p_ctsuwr[p_instance_ctrl->wr_index].ctsuso1;
 #endif
        p_instance_ctrl->wr_index++;
    }
#endif

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

/***********************************************************************************************************************
 * CTSURD interrupt handler. This service routine reads the sensor count and reference counter for
 * the current element and places the value in the scan data buffer. Note that the reference counter
 * does not work properly but is saved anyway for backward compatibility and potential future use.
 * Additionally, the SC register cannot be read again until RC is read.
 ***********************************************************************************************************************/
void ctsu_read_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

#if (CTSU_CFG_DTC_SUPPORT_ENABLE == 1)

    /** Clear the BSP IRQ Flag     */
    R_BSP_IrqStatusClear(R_FSP_CurrentIrqGet());

#else
    IRQn_Type irq = R_FSP_CurrentIrqGet();
    ctsu_instance_ctrl_t * p_instance_ctrl = (ctsu_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    /** Clear the BSP IRQ Flag     */
    R_BSP_IrqStatusClear(R_FSP_CurrentIrqGet());

    /* read current channel/element value */
    /* Store the reference counter for possible future use. Register must be read or scan will hang. */

 #if (BSP_FEATURE_CTSU_VERSION == 1)
    if (CTSU_CORRECTION_RUN == g_ctsu_correction_info.status)
    {
        g_ctsu_correction_info.scanbuf.sen = R_CTSU->CTSUSC;
        g_ctsu_correction_info.scanbuf.ref = R_CTSU->CTSURC;
    }

  #if (BSP_FEATURE_CTSU_VERSION == 1)
   #if (CTSU_CFG_DIAG_SUPPORT_ENABLE == 1)
    else if (CTSU_MODE_DIAGNOSIS_SCAN == p_instance_ctrl->md)
    {
        g_ctsu_diag_info.scanbuf.sen = R_CTSU->CTSUSC;
        g_ctsu_diag_info.scanbuf.ref = R_CTSU->CTSURC;
    }
   #endif
  #endif
    else
    {
  #if (CTSU_CFG_NUM_SELF_ELEMENTS != 0)
        if (CTSU_MODE_SELF_MULTI_SCAN == p_instance_ctrl->md)
        {
            (p_instance_ctrl->p_self_raw + p_instance_ctrl->rd_index)->sen = R_CTSU->CTSUSC;
            (p_instance_ctrl->p_self_raw + p_instance_ctrl->rd_index)->ref = R_CTSU->CTSURC;
            p_instance_ctrl->rd_index++;
        }
  #endif
  #if (CTSU_CFG_NUM_MUTUAL_ELEMENTS != 0)
        if (CTSU_MODE_MUTUAL_FULL_SCAN == p_instance_ctrl->md)
        {
            if (false == p_instance_ctrl->serial_tuning_enable)
            {
                if (1 == R_CTSU->CTSUST_b.CTSUPS)
                {
                    (p_instance_ctrl->p_mutual_raw + p_instance_ctrl->rd_index)->pri_sen = R_CTSU->CTSUSC;
                    (p_instance_ctrl->p_mutual_raw + p_instance_ctrl->rd_index)->pri_ref = R_CTSU->CTSURC;
                }
                else
                {
                    (p_instance_ctrl->p_mutual_raw + p_instance_ctrl->rd_index)->snd_sen = R_CTSU->CTSUSC;
                    (p_instance_ctrl->p_mutual_raw + p_instance_ctrl->rd_index)->snd_ref = R_CTSU->CTSURC;
                    p_instance_ctrl->rd_index++;
                }
            }
            else
            {
                p_instance_ctrl->serial_tuning_mutual_cnt++;
                if (p_instance_ctrl->serial_tuning_mutual_cnt % 2)
                {
                    (p_instance_ctrl->p_mutual_raw + p_instance_ctrl->rd_index)->pri_sen = R_CTSU->CTSUSC;
                    (p_instance_ctrl->p_mutual_raw + p_instance_ctrl->rd_index)->pri_ref = R_CTSU->CTSURC;
                }
                else
                {
                    (p_instance_ctrl->p_mutual_raw + p_instance_ctrl->rd_index)->snd_sen = R_CTSU->CTSUSC;
                    (p_instance_ctrl->p_mutual_raw + p_instance_ctrl->rd_index)->snd_ref = R_CTSU->CTSURC;
                    p_instance_ctrl->rd_index++;
                }
            }
        }
  #endif
    }
 #endif

 #if (BSP_FEATURE_CTSU_VERSION == 2)
  #if (CTSU_CFG_NUM_CFC != 0)
    uint16_t i;
  #endif
    if (CTSU_CORRECTION_RUN == g_ctsu_correction_info.status)
    {
        g_ctsu_correction_info.scanbuf = R_CTSU->CTSUSC;
    }

  #if (CTSU_CFG_NUM_CFC != 0)
    else if (CTSU_CORRECTION_RUN == g_ctsu_corrcfc_info.status)
    {
        for (i = 0; i < g_ctsu_corrcfc_info.num_ts; i++)
        {
            g_ctsu_corrcfc_info.scanbuf[i] = R_CTSU->CTSUCFCCNT_b.CFCCNT;
        }
    }
  #endif
  #if (CTSU_CFG_DIAG_SUPPORT_ENABLE == 1)
    else if (CTSU_MODE_DIAGNOSIS_SCAN == p_instance_ctrl->md)
    {
        if (CTSU_DIAG_CFC == g_ctsu_diag_info.state)
        {
            g_ctsu_diag_info.ctsuscnt[p_instance_ctrl->rd_index] = R_CTSU->CTSUCFCCNT;
            p_instance_ctrl->rd_index++;
        }
        else
        {
            g_ctsu_diag_info.ctsuscnt[p_instance_ctrl->rd_index] = R_CTSU->CTSUSCNT;
            p_instance_ctrl->rd_index++;
        }
    }
  #endif
    else
    {
  #if (CTSU_CFG_NUM_SELF_ELEMENTS != 0)
        if (CTSU_MODE_SELF_MULTI_SCAN == (CTSU_MODE_MUTUAL_FULL_SCAN & p_instance_ctrl->md))
        {
            p_instance_ctrl->p_self_raw[p_instance_ctrl->rd_index] = R_CTSU->CTSUSC;
            p_instance_ctrl->rd_index++;

            /* Interim */
            if (0 == p_instance_ctrl->rd_index % 3)
            {
                R_CTSU->CTSUSR_b.MFC = 0;
            }
        }
  #endif
  #if (CTSU_CFG_NUM_MUTUAL_ELEMENTS != 0)
        if (CTSU_MODE_MUTUAL_FULL_SCAN == p_instance_ctrl->md)
        {
            p_instance_ctrl->p_mutual_raw[p_instance_ctrl->rd_index] = R_CTSU->CTSUSC;
            p_instance_ctrl->rd_index++;
        }

   #if (CTSU_CFG_NUM_CFC != 0)
        if (CTSU_MODE_MUTUAL_CFC_SCAN == p_instance_ctrl->md)
        {
            for (i = 0; i < p_instance_ctrl->p_ctsu_cfg->num_rx; i++)
            {
                p_instance_ctrl->p_mutual_raw[p_instance_ctrl->rd_index] = R_CTSU->CTSUCFCCNT_b.CFCCNT;
                p_instance_ctrl->rd_index++;
            }
        }
   #endif
  #endif
    }
 #endif
    if (1 == p_instance_ctrl->interrupt_reverse_flag)
    {
        p_instance_ctrl->interrupt_reverse_flag = 0;

        ctsu_end_interrupt(p_instance_ctrl);
    }
#endif

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

/***********************************************************************************************************************
 * CTSUFN interrupt handler. This service routine occurs when all elements have been scanned (finished).
 * The user's callback function is called if available.
 ***********************************************************************************************************************/
void ctsu_end_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type              irq             = R_FSP_CurrentIrqGet();
    ctsu_instance_ctrl_t * p_instance_ctrl = (ctsu_instance_ctrl_t *) R_FSP_IsrContextGet(irq);
    uint16_t               rd_index;

    /** Clear the BSP IRQ Flag     */
    R_BSP_IrqStatusClear(R_FSP_CurrentIrqGet());

    /* In CTSU1 and CTSU2 self-capacity and current measurement mode and diagnostic mode, */
    /* rd_index has the same value as wr_index.                                           */
    rd_index = p_instance_ctrl->rd_index;

#if (BSP_FEATURE_CTSU_VERSION == 1)
    if (CTSU_MODE_MUTUAL_FULL_SCAN == p_instance_ctrl->md)
    {
        if (true == p_instance_ctrl->serial_tuning_enable)
        {
            if (0 == ((p_instance_ctrl->ctsucr1 >> 7) & 0x01))
            {
                rd_index = p_instance_ctrl->serial_tuning_mutual_cnt;
            }
        }
    }
#endif

#if (BSP_FEATURE_CTSU_VERSION == 2)
 #if (CTSU_CFG_NUM_MUTUAL_ELEMENTS != 0)
    if (CTSU_MODE_MUTUAL_FULL_SCAN == p_instance_ctrl->md)
    {
        if (true == p_instance_ctrl->serial_tuning_enable)
        {
            if (0 == ((p_instance_ctrl->ctsucr1 >> 7) & 0x01))
            {
                rd_index = p_instance_ctrl->rd_index;
            }
            else
            {
                rd_index = p_instance_ctrl->rd_index / 2;
            }
        }
        else
        {
            /* In the mutual capacity of CTSU2, the value of rd_index is twice the value of wr_index. */
            rd_index = p_instance_ctrl->rd_index / 2;
        }
    }

  #if (CTSU_CFG_NUM_CFC != 0)
    if (CTSU_MODE_MUTUAL_CFC_SCAN == p_instance_ctrl->md)
    {
        if (true == p_instance_ctrl->serial_tuning_enable)
        {
            if (0 == ((p_instance_ctrl->ctsucr1 >> 7) & 0x01))
            {
                rd_index = p_instance_ctrl->rd_index;
            }
            else
            {
                rd_index = (uint16_t) (p_instance_ctrl->rd_index / (p_instance_ctrl->p_ctsu_cfg->num_rx * 2));
            }
        }
        else
        {
            /* In the CFC mutual capacity of CTSU2, rd_index is twice the number of RX terminals in each wr_index. */
            rd_index = (uint16_t) (p_instance_ctrl->rd_index / (p_instance_ctrl->p_ctsu_cfg->num_rx * 2));
        }
    }
  #endif
 #endif
#endif

    /* Countermeasure for the problem that RD interrupt and FN interrupt are reversed. */
    if (rd_index != p_instance_ctrl->wr_index)
    {
        p_instance_ctrl->interrupt_reverse_flag = 1;

        return;
    }

    ctsu_end_interrupt(p_instance_ctrl);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

void ctsu_end_interrupt (ctsu_instance_ctrl_t * const p_instance_ctrl)
{
    ctsu_callback_args_t args;

    /* Store callback arguments in memory provided by user if available.  This allows callback arguments to be
     * stored in non-secure memory so they can be accessed by a non-secure callback function. */
    ctsu_callback_args_t * p_args = p_instance_ctrl->p_callback_memory;
    if (NULL == p_args)
    {
        /* Store on stack */
        p_args = &args;
    }
    else
    {
        /* Save current arguments on the stack in case this is a nested interrupt. */
        args = *p_args;
    }

#if (BSP_FEATURE_CTSU_VERSION == 1)
 #if (CTSU_CFG_DIAG_SUPPORT_ENABLE == 1)
    if (CTSU_DIAG_OVER_VOLTAGE == g_ctsu_diag_info.state)
    {
        if (R_CTSU->CTSUERRS_b.CTSUICOMP == 1)
        {
            g_ctsu_diag_info.icomp = 1;
        }
    }
 #endif
#endif

#if (BSP_FEATURE_CTSU_VERSION == 2)
 #if (CTSU_CFG_DIAG_SUPPORT_ENABLE == 1)
    if (CTSU_MODE_DIAGNOSIS_SCAN == p_instance_ctrl->md)
    {
        if (CTSU_DIAG_OVER_CURRENT == g_ctsu_diag_info.state)
        {
            if (R_CTSU->CTSUSR0 & CTSU_ICOMP1)
            {
                g_ctsu_diag_info.icomp1_value = R_CTSU->CTSUSR_b.ICOMP1;
            }
        }
    }
 #endif
#endif

    p_args->event = CTSU_EVENT_SCAN_COMPLETE;

    if (R_CTSU->CTSUST & CTSU_SOVF)
    {
        p_args->event  |= CTSU_EVENT_OVERFLOW;
        R_CTSU->CTSUST &= (uint8_t) (~CTSU_SOVF);
    }

#if (BSP_FEATURE_CTSU_VERSION == 2)
    if (R_CTSU->CTSUSR0 & (CTSU_ICOMP0 | CTSU_ICOMP1))
    {
        if (R_CTSU->CTSUSR0 & CTSU_ICOMP0)
        {
            p_args->event |= CTSU_EVENT_ICOMP;
        }

        if (R_CTSU->CTSUSR0 & CTSU_ICOMP1)
        {
            p_args->event |= CTSU_EVENT_ICOMP1;
        }

        R_CTSU->CTSUSR0 |= CTSU_ICOMPRST;
    }
#endif
#if (BSP_FEATURE_CTSU_VERSION == 1)
    if (R_CTSU->CTSUERRS_b.CTSUICOMP == 1)
    {
        R_CTSU->CTSUCR1 &= (uint8_t) (~0x01);
        __NOP();
        __NOP();
        R_CTSU->CTSUCR1 |= 0x01;
        p_args->event   |= CTSU_EVENT_ICOMP;
    }
#endif
#if (BSP_FEATURE_CTSU_VERSION == 2)
 #if (CTSU_CFG_TEMP_CORRECTION_SUPPORT == 1)
    if (CTSU_CORRECTION_RUN != g_ctsu_correction_info.status)
    {
        if (CTSU_MODE_CORRECTION_SCAN == p_instance_ctrl->md)
        {
            R_CTSU->CTSUCRA_b.SDPSEL     = 0;
            R_CTSU->CTSUSUCLK0           = (uint16_t) ((CTSU_CFG_SUMULTI0 << 8) | g_ctsu_correction_info.suadj0);
            R_CTSU->CTSUCRB_b.SSCNT      = 1;
            R_CTSU->CTSUCALIB_b.SUCARRY  = 0;
            R_CTSU->CTSUCALIB_b.CCOCALIB = 0;
            R_CTSU->CTSUCALIB_b.CCOCLK   = 1;
            R_CTSU->CTSUCALIB_b.TSOC     = 0;
            R_CTSU->CTSUCRA_b.SDPSEL     = 1;
        }
    }
 #endif
#endif

    p_instance_ctrl->state        = CTSU_STATE_SCANNED;
    p_instance_ctrl->error_status = args.event;
    p_args->p_context             = p_instance_ctrl->p_context;

    /* If a callback was provided, call it with the argument */
    if (NULL != p_instance_ctrl->p_callback)
    {
#if BSP_TZ_SECURE_BUILD

        /* p_callback can point to a secure function or a non-secure function. */
        if (!cmse_is_nsfptr(p_instance_ctrl->p_callback))
        {
            /* If p_callback is secure, then the project does not need to change security state. */
            p_instance_ctrl->p_callback(p_args);
        }
        else
        {
            /* If p_callback is Non-secure, then the project must change to Non-secure state in order to call the callback. */
            ctsu_prv_ns_callback p_callback = (ctsu_prv_ns_callback) (p_instance_ctrl->p_callback);
            p_callback(p_args);
        }

#else

        /* If the project is not Trustzone Secure, then it will never need to change security state in order to call the callback. */
        p_instance_ctrl->p_callback(p_args);
#endif
    }

    if (NULL != p_instance_ctrl->p_callback_memory)
    {
        /* Restore callback memory in case this is a nested interrupt. */
        *p_instance_ctrl->p_callback_memory = args;
    }

    /* reset indexes */
    p_instance_ctrl->wr_index = 0;
    p_instance_ctrl->rd_index = 0;
#if (CTSU_CFG_NUM_MUTUAL_ELEMENTS != 0)
    p_instance_ctrl->serial_tuning_mutual_cnt = 0;
#endif
}

/***********************************************************************************************************************
 * ctsu_correction_process
 ***********************************************************************************************************************/
void ctsu_correction_process (ctsu_instance_ctrl_t * const p_instance_ctrl)
{
#if (BSP_FEATURE_CTSU_VERSION == 2)
    uint32_t i;
    uint32_t j;
    uint16_t error_registance[CTSU_RANGE_NUM];
    uint32_t trimb;
    uint8_t  trimb_byte;
    uint8_t  rtrim;
    uint16_t base_value;
    uint16_t base_conv_dac;
    uint32_t ref_include_error;
    int32_t  x0;
    int32_t  x1;
    int32_t  y0;

    g_ctsu_correction_info.status = CTSU_CORRECTION_RUN;

    R_CTSU->CTSUCRA_b.MD0  = 1;
    R_CTSU->CTSUCRA_b.MD1  = 0;
    R_CTSU->CTSUCRA_b.MD2  = 0;
    R_CTSU->CTSUMCH_b.MCA0 = 1;
    R_CTSU->CTSUMCH_b.MCA1 = 0;
    R_CTSU->CTSUMCH_b.MCA2 = 0;
    R_CTSU->CTSUMCH_b.MCA3 = 0;
    R_CTSU->CTSUCRA_b.LOAD = 1;

    /* Setting time of measurement */
    g_ctsu_correction_info.ctsuwr.ctsuso = (CTSU_SNUM_RECOMMEND << 10);

    /* Step1 : Get resistance value from TRIMB register. */
    trimb = R_CTSUTRIM->CTSUTRIMB;
    rtrim = R_CTSUTRIM->CTSUTRIMA_b.RTRIM;
    for (i = 0; i < CTSU_RANGE_NUM; i++)
    {
        trimb_byte          = (trimb >> (i * 8)) & CTSU_CORRECTION_TRIMB_MAX;
        error_registance[i] = (uint16_t) (trimb_byte & (uint8_t) (~CTSU_CORRECTION_TRIMB_SIGN_BIT));
        if (trimb_byte & CTSU_CORRECTION_TRIMB_SIGN_BIT)
        {
            if ((rtrim > CTSU_CORRECTION_RTRIM_THRESHOLD1) && (trimb_byte >= CTSU_CORRECTION_TRIMB_THRESHOLD1))
            {
                /* Minus2 : bit8(0.50) set 1 */
                error_registance[i] = (error_registance[i] | CTSU_CORRECTION_BIT8);
            }
            else
            {
                /* Plus   : bit9(1.00) set 1 */
                error_registance[i] = (error_registance[i] | CTSU_CORRECTION_BIT9);
            }
        }
        else
        {
            if ((rtrim < CTSU_CORRECTION_RTRIM_THRESHOLD2) && (trimb_byte <= CTSU_CORRECTION_TRIMB_THRESHOLD2))
            {
                /* Plus2  : bit7(0.25) and bit9(1.00) set 1 */
                error_registance[i] = (error_registance[i] | CTSU_CORRECTION_BIT7 | CTSU_CORRECTION_BIT9);
            }
            else
            {
                /* Minus : bit8(0.50) and bit7(0.25) set 1 */
                error_registance[i] = (error_registance[i] | CTSU_CORRECTION_BIT7 | CTSU_CORRECTION_BIT8);
            }
        }

        /* 6-bit left shift, 512 to 32768 */
        error_registance[i] = (uint16_t) (error_registance[i] << (CTSU_SHIFT_AMOUNT - 9));

 #if (CTSU_CFG_DIAG_SUPPORT_ENABLE == 1)
        g_ctsu_diag_info.error_registance[i] = error_registance[i];
 #endif
    }

    /* Step2-a : Measure the current input to the ICO by passing current through the internal resistance */
    /*           in each range. The theoretical value of the current is 12.5uA. */
    R_CTSU->CTSUCHACA        = 1;
    R_CTSU->CTSUCHACB        = 0;
    R_CTSU->CTSUCALIB_b.TSOC = 1;
    for (i = 0; i < CTSU_RANGE_NUM; i++)
    {
        if (CTSU_RANGE_20UA == i)
        {
            R_CTSU->CTSUCRA_b.ATUNE1 = 0;
            R_CTSU->CTSUCRA_b.ATUNE2 = 1;
        }
        else if (CTSU_RANGE_40UA == i)
        {
            R_CTSU->CTSUCRA_b.ATUNE1 = 1;
            R_CTSU->CTSUCRA_b.ATUNE2 = 0;
        }
        else if (CTSU_RANGE_80UA == i)
        {
            R_CTSU->CTSUCRA_b.ATUNE1 = 0;
            R_CTSU->CTSUCRA_b.ATUNE2 = 0;
        }
        else
        {
            R_CTSU->CTSUCRA_b.ATUNE1 = 1;
            R_CTSU->CTSUCRA_b.ATUNE2 = 1;
        }

        R_CTSU->CTSUCRA_b.LOAD = 3;
        ctsu_correction_measurement(p_instance_ctrl, &g_ctsu_correction_info.base_value[i]);
        R_CTSU->CTSUCRA_b.LOAD = 1;
    }

    /* Step3 : Measure by inputting each constant current from internal DAC to ICO. */
    R_CTSU->CTSUCRB_b.SSCNT      = 0;
    R_CTSU->CTSUCALIB_b.CCOCLK   = 0;
    R_CTSU->CTSUCALIB_b.CCOCALIB = 1;

    /* 1.25uA * (j + 1), SUCARRY is required for greater than 10uA */
    for (j = 0; j < CTSU_CORRECTION_POINT_NUM; j++)
    {
        R_CTSU->CTSUCRA_b.SDPSEL = 0;
        if (8 > j)
        {
            R_CTSU->CTSUSUCLK0 = (uint16_t) (((j + 1) * CTSU_CORRECTION_SUMULTI) - 1);
        }
        else
        {
            R_CTSU->CTSUCRB_b.SSCNT     = 3;
            R_CTSU->CTSUCALIB_b.SUCARRY = 1;
            R_CTSU->CTSUSUCLK0          = (uint16_t) (((j - 3) * CTSU_CORRECTION_SUMULTI) - 1);
        }

        R_CTSU->CTSUCRA_b.SDPSEL = 1;
        ctsu_correction_measurement(p_instance_ctrl, &g_ctsu_correction_info.dac_value[j]);
    }

    /* Step4 : Calculate the coefficient between step2 and step3. */
    for (i = 0; i < CTSU_RANGE_NUM; i++)
    {
        /* Linear interpolation calculation */
        base_value = g_ctsu_correction_info.base_value[i];
        j          = 1;
        while (1)
        {
            if ((base_value < g_ctsu_correction_info.dac_value[j]) || ((CTSU_CORRECTION_POINT_NUM - 1) == j))
            {
                y0 = (uint16_t) (CTSU_CORRECTION_STD_UNIT * (j + 1));
                x0 = g_ctsu_correction_info.dac_value[j];
                x1 = g_ctsu_correction_info.dac_value[j - 1];
                break;
            }

            j++;
        }

        base_conv_dac = (uint16_t) (y0 - ((CTSU_CORRECTION_STD_UNIT * (x0 - base_value)) / (x0 - x1)));

        /* Error rate calculation */
        ref_include_error = (uint32_t) (CTSU_CORRECTION_STD_VAL * (CTSU_CORRECTION_BIT16 - error_registance[i]));
        g_ctsu_correction_info.error_rate[i] = (uint16_t) (ref_include_error / base_conv_dac);

        for (j = 0; j < CTSU_CORRECTION_POINT_NUM; j++)
        {
            g_ctsu_correction_info.ref_value[i][j] =
                (uint16_t) ((CTSU_CORRECTION_STD_UNIT * (j + 1) * g_ctsu_correction_info.error_rate[i]) >>
                            CTSU_SHIFT_AMOUNT);
        }
    }

    for (i = 0; i < CTSU_RANGE_NUM - 1; i++)
    {
        g_ctsu_correction_info.range_ratio[i] =
            (uint16_t) (((uint32_t) g_ctsu_correction_info.error_rate[i] << CTSU_SHIFT_AMOUNT) /
                        g_ctsu_correction_info.error_rate[CTSU_RANGE_160UA]);
    }
    g_ctsu_correction_info.status = CTSU_CORRECTION_COMPLETE;
#endif
#if (BSP_FEATURE_CTSU_VERSION == 1)
    uint16_t second_std_val;
    uint32_t ctsu_sdpa;
    uint32_t pclkb_mhz;

 #if BSP_FEATURE_CTSU_HAS_TRMR
    uint8_t ctsutrimr_def;
 #endif

    g_ctsu_correction_info.status = CTSU_CORRECTION_RUN;

    pclkb_mhz = R_FSP_SystemClockHzGet(FSP_PRIV_CLOCK_PCLKB) / CTSU_PCLKB_FREQ_MHZ;
    if (CTSU_PCLKB_FREQ_RANGE1 >= pclkb_mhz)
    {
        R_CTSU->CTSUCR1 |= (0 << 4);
        ctsu_sdpa        = pclkb_mhz - 1;
    }
    else if ((CTSU_PCLKB_FREQ_RANGE1 < pclkb_mhz) && (CTSU_PCLKB_FREQ_RANGE2 >= pclkb_mhz))
    {
        R_CTSU->CTSUCR1 |= (1 << 4);
        ctsu_sdpa        = (pclkb_mhz / 2) - 1;
    }
    else
    {
        R_CTSU->CTSUCR1 |= (2 << 4);
        ctsu_sdpa        = (pclkb_mhz / 4) - 1;
    }

    g_ctsu_correction_info.ctsu_clock = pclkb_mhz >> CTSU_CFG_PCLK_DIVISION;

    R_CTSU->CTSUCR1    |= (CTSU_MODE_SELF_MULTI_SCAN << 6);
    R_CTSU->CTSUCHAC[0] = 0x01;

    g_ctsu_correction_info.ctsuwr.ctsussc = (CTSU_SSDIV_0500 << 8);
    g_ctsu_correction_info.ctsuwr.ctsuso0 = 0x0000;

    /* Set CTSUSO1 */
    g_ctsu_correction_info.ctsuwr.ctsuso1 = (uint16_t) ((CTSU_ICOG_66 << 13) | (ctsu_sdpa << 8) | CTSU_RICOA_RECOMMEND);

    /* Correction measurement setting */
    R_CTSU->CTSUERRS_b.CTSUSPMD = 2;
    R_CTSU->CTSUERRS_b.CTSUTSOC = 1;
    R_BSP_SoftwareDelay(CTSU_WAIT_TIME, BSP_DELAY_UNITS_MICROSECONDS);

    /* First value measurement */
    ctsu_correction_measurement(p_instance_ctrl, &g_ctsu_correction_info.first_val);

    /* Second standard value create */
 #if BSP_FEATURE_CTSU_HAS_TRMR
    uint32_t work;

    /*                       ctsutrimr_def + 273            ((ctsutrimr_def + 273) * 2560 * 128)      */
    /*    second_std_val  =  ------------------- * 40960 =  ------------------------------------ + 64 */
    /*                               528                                   33 * 128                   */

    work           = (ctsutrimr_def + 273) * 9930 + 64;
    second_std_val = (uint16_t) (work >> 7);

    /* Current trimming value storage */
    ctsutrimr_def = CTSU.CTSUTRMR;

    /* 0xFF set in the current trimming register */
    CTSU.CTSUTRMR = 0xFF;
 #else
    second_std_val = (uint16_t) (CTSU_CORRECTION_2ND_STD_VAL * CTSU_WAFER_PARAMETER);
    g_ctsu_correction_info.ctsuwr.ctsuso1 |= (uint16_t) (CTSU_ICOG_40 << 13); /* ICO gain  66% -> 40% */
 #endif

    /* Second value measurement */
    ctsu_correction_measurement(p_instance_ctrl, &g_ctsu_correction_info.second_val);
 #if BSP_FEATURE_CTSU_HAS_TRMR

    /* Return the current trimming register to the initial value */
    CTSU.CTSUTRMR = ctsutrimr_def;
 #endif

    /* Normal measurement setting */
    R_CTSU->CTSUERRS_b.CTSUTSOC = 0;
    R_CTSU->CTSUERRS_b.CTSUSPMD = 0;

    R_BSP_SoftwareDelay(CTSU_WAIT_TIME, BSP_DELAY_UNITS_MICROSECONDS);

    if ((0 != g_ctsu_correction_info.first_val) && (0 != g_ctsu_correction_info.second_val))
    {
        if (g_ctsu_correction_info.second_val < g_ctsu_correction_info.first_val)
        {
            /* 1st coefficient create */
            g_ctsu_correction_info.first_coefficient = (CTSU_CORRECTION_1ST_STD_VAL << CTSU_SHIFT_AMOUNT) /
                                                       g_ctsu_correction_info.first_val;

            /* 2nd coefficient create */
            g_ctsu_correction_info.second_coefficient = ((uint32_t) second_std_val << CTSU_SHIFT_AMOUNT) /
                                                        g_ctsu_correction_info.second_val;

            g_ctsu_correction_info.status = CTSU_CORRECTION_COMPLETE;
        }
        else
        {
            g_ctsu_correction_info.status = CTSU_CORRECTION_ERROR;
        }
    }
    else
    {
        g_ctsu_correction_info.status = CTSU_CORRECTION_ERROR;
    }
#endif
}

/***********************************************************************************************************************
 * ctsu_correction_measurement
 ***********************************************************************************************************************/
void ctsu_correction_measurement (ctsu_instance_ctrl_t * const p_instance_ctrl, uint16_t * data)
{
    uint16_t i;
    uint32_t sum = 0;

    for (i = 0; i < CTSU_CORRECTION_AVERAGE; i++)
    {
#if (CTSU_CFG_DTC_SUPPORT_ENABLE == 1)
        ctsu_transfer_configure(p_instance_ctrl);
#else
        FSP_PARAMETER_NOT_USED(p_instance_ctrl);
#endif
        p_instance_ctrl->state = CTSU_STATE_SCANNING;
        R_CTSU->CTSUCR0       |= 0x01;
        while (p_instance_ctrl->state != CTSU_STATE_SCANNED)
        {
        }

#if (BSP_FEATURE_CTSU_VERSION == 2)
        sum += g_ctsu_correction_info.scanbuf;
#endif
#if (BSP_FEATURE_CTSU_VERSION == 1)
        sum += g_ctsu_correction_info.scanbuf.sen;
#endif
    }

    *data = (uint16_t) (sum / CTSU_CORRECTION_AVERAGE);
}

#if (BSP_FEATURE_CTSU_VERSION == 2)
 #if (CTSU_CFG_TEMP_CORRECTION_SUPPORT == 1)

/***********************************************************************************************************************
 * ctsu_correction_scan_start
 ***********************************************************************************************************************/
void ctsu_correction_scan_start (void)
{
    g_ctsu_temp_reg_ctsucra = R_CTSU->CTSUCRA;

    R_CTSU->CTSUCRA_b.MD0  = 1;
    R_CTSU->CTSUCRA_b.MD1  = 0;
    R_CTSU->CTSUCRA_b.MD2  = 0;
    R_CTSU->CTSUMCH_b.MCA0 = 1;
    R_CTSU->CTSUMCH_b.MCA1 = 0;
    R_CTSU->CTSUMCH_b.MCA2 = 0;
    R_CTSU->CTSUMCH_b.MCA3 = 0;

    /* Setting time of measurement */
    g_ctsu_correction_info.ctsuwr.ctsuso = (CTSU_SNUM_RECOMMEND << 10);
    g_ctsu_correction_info.suadj0        = (uint8_t) (R_CTSU->CTSUSUCLK0 & CTSU_SUADJ_MAX);

    if (g_ctsu_correction_info.scan_index < CTSU_CORRECTION_POINT_NUM)
    {
        /* Dummy setting */
        R_CTSU->CTSUCHACA = 1;
        R_CTSU->CTSUCHACB = 0;

        /* Step3 : Measure by inputting each constant current from internal DAC to ICO. */
        R_CTSU->CTSUCRB_b.SSCNT      = 0;
        R_CTSU->CTSUCALIB_b.CCOCLK   = 0;
        R_CTSU->CTSUCALIB_b.CCOCALIB = 1;
        R_CTSU->CTSUCALIB_b.TSOC     = 1;

        R_CTSU->CTSUCRA_b.SDPSEL = 0;
        if (8 > g_ctsu_correction_info.scan_index)
        {
            R_CTSU->CTSUSUCLK0 = (uint16_t) (((g_ctsu_correction_info.scan_index + 1) * CTSU_CORRECTION_SUMULTI) - 1);
        }
        else
        {
            /* SUCARRY is required for greater than 10uA */
            R_CTSU->CTSUCRB_b.SSCNT     = 3;
            R_CTSU->CTSUCALIB_b.SUCARRY = 1;
            R_CTSU->CTSUSUCLK0          =
                (uint16_t) (((g_ctsu_correction_info.scan_index - 3) * CTSU_CORRECTION_SUMULTI) - 1);
        }

        R_CTSU->CTSUCRA_b.SDPSEL = 1;
    }
    else
    {
        /* Step2-b : Measure the current input to the ICO by passing current through the external resistance. */
        /*           The theoretical value of the current is 9.375uA. */
        R_CTSU->CTSUCRA_b.ATUNE1 = 1;
        R_CTSU->CTSUCRA_b.ATUNE2 = 1;
  #if (CTSU_CFG_TEMP_CORRECTION_TS < 32)
        R_CTSU->CTSUCHACA = (uint32_t) (1 << CTSU_CFG_TEMP_CORRECTION_TS);
        R_CTSU->CTSUCHACB = 0;
  #else
        R_CTSU->CTSUCHACA = 0;
        R_CTSU->CTSUCHACB = (uint32_t) (1 << (CTSU_CFG_TEMP_CORRECTION_TS - 32));
  #endif
        R_CTSU->CTSUCRA_b.DCMODE = 1;
        R_CTSU->CTSUCRA_b.DCBACK = 1;
        R_CTSU->CTSUSO_b.SO      = 0;
    }
}

/***********************************************************************************************************************
 * ctsu_correction_data_get
 ***********************************************************************************************************************/
fsp_err_t ctsu_correction_data_get (ctsu_instance_ctrl_t * const p_instance_ctrl, uint16_t * p_data)
{
  #if (CTSU_CFG_CALIB_RTRIM_SUPPORT == 1)
    adc_instance_t const * p_adc = p_instance_ctrl->p_ctsu_cfg->p_adc_instance;
  #endif
    uint32_t    i;
    uint32_t    j;
    uint16_t    base_value;
    uint16_t    base_conv_dac;
    int32_t     x0;
    int32_t     x1;
    int32_t     y0;
    ctsu_data_t temp_avg_data = {0, 0};
    fsp_err_t   err           = FSP_SUCCESS;

    if (g_ctsu_correction_info.scan_index < CTSU_CORRECTION_POINT_NUM)
    {
        temp_avg_data.int_data = g_ctsu_correction_info.dac_value[g_ctsu_correction_info.scan_index];
        ctsu_moving_average(&temp_avg_data, *p_instance_ctrl->p_self_raw, 4);
        g_ctsu_correction_info.dac_value[g_ctsu_correction_info.scan_index] = temp_avg_data.int_data;
        g_ctsu_correction_info.scan_index++;
    }
    else
    {
        if (0 == g_ctsu_correction_info.ex_base_value)
        {
            g_ctsu_correction_info.ex_base_value  = *p_instance_ctrl->p_self_raw;
            g_ctsu_correction_info.update_counter = CTSU_CFG_TEMP_CORRECTION_TIME;
        }
        else
        {
            temp_avg_data.int_data = g_ctsu_correction_info.ex_base_value;
            ctsu_moving_average(&temp_avg_data, *p_instance_ctrl->p_self_raw, 4);
            g_ctsu_correction_info.ex_base_value = temp_avg_data.int_data;
        }

        g_ctsu_correction_info.scan_index = 0;
        g_ctsu_correction_info.update_counter++;
    }

    /* Step4 : Calculate the coefficient between step2 and step3. */
    if (g_ctsu_correction_info.update_counter > CTSU_CFG_TEMP_CORRECTION_TIME)
    {
        /* Linear interpolation calculation */
        base_value = g_ctsu_correction_info.ex_base_value;
        j          = 1;
        while (1)
        {
            if ((base_value < g_ctsu_correction_info.dac_value[j]) || ((CTSU_CORRECTION_POINT_NUM - 1) == j))
            {
                y0 = (uint16_t) (CTSU_CORRECTION_STD_UNIT * (j + 1));
                x0 = g_ctsu_correction_info.dac_value[j];
                x1 = g_ctsu_correction_info.dac_value[j - 1];
                break;
            }

            j++;
        }

        base_conv_dac = (uint16_t) (y0 - ((CTSU_CORRECTION_STD_UNIT * (x0 - base_value)) / (x0 - x1)));

        /* Error rate calculation */
        g_ctsu_correction_info.error_rate[CTSU_RANGE_160UA] =
            (uint16_t) ((CTSU_CORRECTION_STD_EXREG << CTSU_SHIFT_AMOUNT) / base_conv_dac);

        for (j = 0; j < CTSU_CORRECTION_POINT_NUM; j++)
        {
            g_ctsu_correction_info.ref_value[CTSU_RANGE_160UA][j] =
                (uint16_t) ((CTSU_CORRECTION_STD_UNIT * (j + 1) *
                             g_ctsu_correction_info.error_rate[CTSU_RANGE_160UA]) >> CTSU_SHIFT_AMOUNT);
            for (i = 0; i < CTSU_RANGE_NUM - 1; i++)
            {
                g_ctsu_correction_info.ref_value[i][j] =
                    (uint16_t) ((g_ctsu_correction_info.ref_value[CTSU_RANGE_160UA][j] *
                                 g_ctsu_correction_info.range_ratio[i]) >> CTSU_SHIFT_AMOUNT);
            }
        }

        g_ctsu_correction_info.update_counter = 0;
  #if (CTSU_CFG_CALIB_RTRIM_SUPPORT == 1)
        err = ctsu_correction_calib_rtrim(p_instance_ctrl, p_data);
        if (FSP_ERR_ALREADY_OPEN != err)
        {
            p_adc->p_api->close(p_adc->p_ctrl);
        }

        if (FSP_SUCCESS != err)
        {
            err = FSP_ERR_ABORTED;
        }
  #endif
    }
    else
    {
        /* Indicates that ADC measurement was not performed. */
        *p_data = CTSU_COUNT_MAX;
    }

    R_CTSU->CTSUCRA = g_ctsu_temp_reg_ctsucra;

    return err;
}

  #if (CTSU_CFG_CALIB_RTRIM_SUPPORT == 1)

/***********************************************************************************************************************
 * ctsu_correction_calib_rtrim
 ***********************************************************************************************************************/
fsp_err_t ctsu_correction_calib_rtrim (ctsu_instance_ctrl_t * const p_instance_ctrl, uint16_t * p_data)
{
    adc_status_t           status;
    adc_instance_t const * p_adc = p_instance_ctrl->p_ctsu_cfg->p_adc_instance;
    uint16_t               i;
    uint16_t               adctdr_result;
    uint16_t               adctdr_ave;
    uint32_t               adctdr_sum;
    int16_t                diff;
    int16_t                dir  = 0;
    uint16_t               comp = 0;
    fsp_err_t              err;

    /* Initialize ADC for CTSU TSCAP */
    err = p_adc->p_api->open(p_adc->p_ctrl, p_adc->p_cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    err = p_adc->p_api->scanCfg(p_adc->p_ctrl, p_adc->p_channel_cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    R_ADC0->ADSSTRL = CTSU_CALIB_ADSSTRL;

    /* Self single scan mode */
    R_CTSU->CTSUCRA_b.LOAD = 1;
    R_CTSU->CTSUCRA_b.MD0  = 0;
    R_CTSU->CTSUCRA_b.MD1  = 0;
    R_CTSU->CTSUCRA_b.MD2  = 0;

    /* Set Channel */
   #if (CTSU_CFG_TEMP_CORRECTION_TS < 32)
    R_CTSU->CTSUCHACA  |= (uint32_t) (1 << CTSU_CFG_TEMP_CORRECTION_TS);
    R_CTSU->CTSUCHTRCA &= (uint32_t) ~(1 << CTSU_CFG_TEMP_CORRECTION_TS);
   #else
    R_CTSU->CTSUCHACB  |= (uint32_t) (1 << (CTSU_CFG_TEMP_CORRECTION_TS - 32));
    R_CTSU->CTSUCHTRCB &= (uint32_t) ~(1 << (CTSU_CFG_TEMP_CORRECTION_TS - 32));
   #endif
    R_CTSU->CTSUMCH0 = CTSU_CFG_TEMP_CORRECTION_TS;

    /* 150uA current measurement */
    R_CTSU->CTSUCRA_b.DCMODE = 1;
    R_CTSU->CTSUCRA_b.DCBACK = 1;
    R_CTSU->CTSUSO_b.SO      = CTSU_CALIB_CTSUSO;
    R_CTSU->CTSUCRA_b.CSW    = 0;
    R_CTSU->CTSUCALIB_b.DRV  = 1;

    /* ADC scan */
    while (!comp)
    {
        adctdr_sum = 0;
        for (i = 0; i < CTSU_CALIB_AVERAGE_TIME; i++)
        {
            /* Software trigger start scan */
            err = p_adc->p_api->scanStart(p_adc->p_ctrl);
            FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

            /* Wait for conversion to complete. */
            status.state = ADC_STATE_SCAN_IN_PROGRESS;
            while (ADC_STATE_SCAN_IN_PROGRESS == status.state)
            {
                err = p_adc->p_api->scanStatusGet(p_adc->p_ctrl, &status);
                FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
            }

            /* Read A/D data then scan normal end */
            err = p_adc->p_api->read(p_adc->p_ctrl, ADC_CHANNEL_16, &adctdr_result);
            FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
            adctdr_sum += adctdr_result;
        }

        adctdr_ave = (uint16_t) ((adctdr_sum * 10) / CTSU_CALIB_AVERAGE_TIME);
        diff       = (int16_t) ((adctdr_ave - CTSU_CALIB_REF) / 10);

        /* The change unit of the voltage by the RTRIM register is about 4mV (4096 * 4) = 16.384 */
        if (diff > CTSU_CALIB_THRESHOLD)
        {
            if (0 <= dir)
            {
                R_CTSUTRIM->CTSUTRIMA_b.RTRIM = (uint8_t) (R_CTSUTRIM->CTSUTRIMA_b.RTRIM + 1);
                dir = 1;
            }
            else
            {
                comp = 1;
            }
        }
        else if (diff < -(CTSU_CALIB_THRESHOLD))
        {
            if (0 >= dir)
            {
                R_CTSUTRIM->CTSUTRIMA_b.RTRIM = (uint8_t) (R_CTSUTRIM->CTSUTRIMA_b.RTRIM - 1);
                dir = -1;
            }
            else
            {
                comp = 1;
            }
        }
        else
        {
            comp = 1;
        }
    }

    /* Restore register settings */
    R_CTSU->CTSUCALIB_b.DRV  = 0;
    R_CTSU->CTSUCRA_b.CSW    = 1;
    R_CTSU->CTSUCRA_b.DCMODE = 0;
    R_CTSU->CTSUCRA_b.DCBACK = 0;

    /* Indicates that ADC measurement was performed  */
    *p_data = R_CTSUTRIM->CTSUTRIMA_b.RTRIM;

    /* Close ADC for CTSU TSCAP */
    p_adc->p_api->close(p_adc->p_ctrl);

    return err;
}

  #endif
 #endif
#endif

/***********************************************************************************************************************
 * ctsu_correction_calc
 ***********************************************************************************************************************/
void ctsu_correction_calc (uint16_t * correction_data, uint16_t raw_data, ctsu_correction_calc_t * p_calc)
{
    uint32_t answer;
    int32_t  cmp_data;
    uint8_t  calc_flag = 0;
#if (BSP_FEATURE_CTSU_VERSION == 1)
    uint16_t diff_val;
    int32_t  diff_coefficient;
    int32_t  mul_diffcoff_diff1valsval;
    uint32_t mul_coff1val_diffcorr;
    uint16_t coefficient;
#endif
#if (BSP_FEATURE_CTSU_VERSION == 2)
    int64_t  y0 = 0;
    int64_t  y1 = 0;
    int64_t  x0 = 0;
    int64_t  x1 = 0;
    uint16_t i;
#endif

#if (BSP_FEATURE_CTSU_VERSION == 2)
 #if (CTSU_CFG_NUM_CFC != 0)
    if ((CTSU_CORRECTION_COMPLETE == g_ctsu_correction_info.status) ||
        (CTSU_CORRECTION_COMPLETE == g_ctsu_corrcfc_info.status))
    {
        calc_flag = 1;
    }

 #else
    if (CTSU_CORRECTION_COMPLETE == g_ctsu_correction_info.status)
    {
        calc_flag = 1;
    }
 #endif
#endif
#if (BSP_FEATURE_CTSU_VERSION == 1)
    if (CTSU_CORRECTION_COMPLETE == g_ctsu_correction_info.status)
    {
        calc_flag = 1;
    }
#endif

    if (calc_flag)
    {
#if (BSP_FEATURE_CTSU_VERSION == 1)

        /* Since the correction coefficient table is created with the recommended measurement time, */
        /* If the measurement time is different, adjust the value level. */
        cmp_data = (int32_t) ((raw_data * g_ctsu_correction_info.ctsu_clock) /
                              (uint32_t) ((p_calc->snum + 1) * (p_calc->sdpa + 1)));

        /*               g_mul_coff1val_diffcorr - g_diff_cofficient * (g_ctsu_correction_info.first_val - raw_data) */
        /*  coefficient= ------------------------------------------------------------------------------------------  */
        /*                                      g_diff_correct_val                                                   */
        /*                                                                                                           */

        diff_val = (uint16_t) (g_ctsu_correction_info.first_val - g_ctsu_correction_info.second_val);

        /* Get multiplication of g_ctsu_correction_info.first_coefficient and difference of Correction value */
        mul_coff1val_diffcorr = g_ctsu_correction_info.first_coefficient * diff_val;

        /* Get difference of Correction coefficient */
        diff_coefficient =
            (int32_t) (g_ctsu_correction_info.first_coefficient - g_ctsu_correction_info.second_coefficient);

        /* Get multiplication of  g_diff_cofficient  and (g_ctsu_correction_info.first_val - raw_data_coff) */
        mul_diffcoff_diff1valsval = (diff_coefficient * (int32_t) (g_ctsu_correction_info.first_val - cmp_data));

        /* Get correction coefficient of scan data */
        coefficient = (uint16_t) (((int32_t) mul_coff1val_diffcorr - mul_diffcoff_diff1valsval) / diff_val);

        /* Get output count data */
        answer = (uint32_t) (((uint32_t) raw_data * (uint32_t) coefficient) >> CTSU_SHIFT_AMOUNT);
#endif
#if (BSP_FEATURE_CTSU_VERSION == 2)

        /* Since the correction coefficient table is created with the recommended measurement time, */
        /* If the measurement time is different, adjust the value level. */
        if (CTSU_SNUM_RECOMMEND == p_calc->snum)
        {
            cmp_data = raw_data;
        }
        else
        {
            cmp_data = (int32_t) (((int32_t) raw_data * (CTSU_SNUM_RECOMMEND + 1)) / (p_calc->snum + 1));
        }

        /* y = y0 + (y1 - y0) * (x - x0) / (x1 - x0);    [y=coefficient, x=value] */
        if (CTSU_MODE_MUTUAL_CFC_SCAN != p_calc->md)
        {
            i = 0;
            while (1)
            {
                if ((cmp_data < g_ctsu_correction_info.dac_value[i]) || ((CTSU_CORRECTION_POINT_NUM - 1) == i))
                {
                    y0 = g_ctsu_correction_info.ref_value[p_calc->range][i];
                    x0 = g_ctsu_correction_info.dac_value[i];
                    if (0 == i)
                    {
                        x1 = 0;
                        y1 = 0;
                    }
                    else
                    {
                        x1 = g_ctsu_correction_info.dac_value[i - 1];
                        y1 = g_ctsu_correction_info.ref_value[p_calc->range][i - 1];
                    }

                    break;
                }

                i++;
            }
        }

 #if (CTSU_CFG_NUM_CFC != 0)
        else
        {
            i = 0;
            while (1)
            {
                if ((cmp_data < g_ctsu_corrcfc_info.dac_value[p_calc->cfc][i]) || ((CTSU_CORRCFC_POINT_NUM - 1) == i))
                {
                    y0 = g_ctsu_corrcfc_info.ref_value[p_calc->cfc][i];
                    x0 = g_ctsu_corrcfc_info.dac_value[p_calc->cfc][i];
                    if (0 == i)
                    {
                        x1 = 0;
                        y1 = 0;
                    }
                    else
                    {
                        x1 = g_ctsu_corrcfc_info.dac_value[p_calc->cfc][i - 1];
                        y1 = g_ctsu_corrcfc_info.ref_value[p_calc->cfc][i - 1];
                    }

                    break;
                }

                i++;
            }
        }
 #endif
        if (CTSU_SNUM_RECOMMEND != p_calc->snum)
        {
            x0 = (int64_t) ((x0 * (p_calc->snum + 1)) / (CTSU_SNUM_RECOMMEND + 1));
            y0 = (int64_t) ((y0 * (p_calc->snum + 1)) / (CTSU_SNUM_RECOMMEND + 1));
            x1 = (int64_t) ((x1 * (p_calc->snum + 1)) / (CTSU_SNUM_RECOMMEND + 1));
            y1 = (int64_t) ((y1 * (p_calc->snum + 1)) / (CTSU_SNUM_RECOMMEND + 1));
        }
        answer = (uint32_t) (y0 - (((y0 - y1) * (x0 - raw_data)) / (x0 - x1)));
#endif

        /* Value Overflow Check */
        if (CTSU_COUNT_MAX < answer)
        {
            *correction_data = CTSU_COUNT_MAX;
        }
        else
        {
            *correction_data = (uint16_t) answer;
        }
    }
    else
    {
        *correction_data = raw_data;
    }
}

/***********************************************************************************************************************
 * ctsu_correction_exec
 ***********************************************************************************************************************/
void ctsu_correction_exec (ctsu_instance_ctrl_t * const p_instance_ctrl)
{
    uint16_t element_id;

    ctsu_correction_calc_t calc;
#if (BSP_FEATURE_CTSU_VERSION == 1)
 #if (CTSU_CFG_NUM_SELF_ELEMENTS != 0)
    ctsu_data_t * p_self_data;
    ctsu_data_t   average_self = {0, 0};
 #endif
 #if (CTSU_CFG_NUM_MUTUAL_ELEMENTS != 0)
    ctsu_data_t * p_pri_data;
    ctsu_data_t * p_snd_data;
    ctsu_data_t   average_pri = {0, 0};
    ctsu_data_t   average_snd = {0, 0};
 #endif

    for (element_id = 0; element_id < p_instance_ctrl->num_elements; element_id++)
    {
        calc.snum = (p_instance_ctrl->p_ctsuwr[element_id].ctsuso0 >> 10) & CTSU_SNUM_MAX;
        calc.sdpa = (p_instance_ctrl->p_ctsuwr[element_id].ctsuso1 >> 8) & CTSU_SDPA_MAX;
 #if (CTSU_CFG_NUM_SELF_ELEMENTS != 0)
        if (CTSU_MODE_SELF_MULTI_SCAN == p_instance_ctrl->md)
        {
            p_self_data  = (p_instance_ctrl->p_self_data + element_id);
            average_self = *p_self_data;
            ctsu_correction_calc((p_instance_ctrl->p_self_corr + element_id),
                                 (p_instance_ctrl->p_self_raw + element_id)->sen,
                                 &calc);
            p_self_data->int_data = *(p_instance_ctrl->p_self_corr + element_id);
            if (1 < p_instance_ctrl->average)
            {
                ctsu_moving_average(&average_self, p_self_data->int_data, p_instance_ctrl->average);
                *p_self_data = average_self;
            }
        }
 #endif
 #if (CTSU_CFG_NUM_MUTUAL_ELEMENTS != 0)
        p_pri_data = (p_instance_ctrl->p_mutual_pri_data + element_id);
        p_snd_data = (p_instance_ctrl->p_mutual_snd_data + element_id);
        if (CTSU_MODE_MUTUAL_FULL_SCAN == p_instance_ctrl->md)
        {
            average_pri = *p_pri_data;
            average_snd = *p_snd_data;
            ctsu_correction_calc((p_instance_ctrl->p_mutual_pri_corr + element_id),
                                 (p_instance_ctrl->p_mutual_raw + element_id)->pri_sen, &calc);
            ctsu_correction_calc((p_instance_ctrl->p_mutual_snd_corr + element_id),
                                 (p_instance_ctrl->p_mutual_raw + element_id)->snd_sen, &calc);
            p_pri_data->int_data = *(p_instance_ctrl->p_mutual_pri_corr + element_id);
            p_snd_data->int_data = *(p_instance_ctrl->p_mutual_snd_corr + element_id);

            if (1 < p_instance_ctrl->average)
            {
                ctsu_moving_average(&average_pri, p_pri_data->int_data, p_instance_ctrl->average);
                ctsu_moving_average(&average_snd, p_snd_data->int_data, p_instance_ctrl->average);
                *p_pri_data = average_pri;
                *p_snd_data = average_snd;
            }
        }
 #endif
    }
#endif

#if (BSP_FEATURE_CTSU_VERSION == 2)
    uint16_t                i;
    uint32_t                ctsuso;
    uint32_t                snum;
    int32_t                 offset_unit;
    ctsu_correction_multi_t multi;
 #if (CTSU_CFG_NUM_SELF_ELEMENTS != 0)
    ctsu_data_t * p_self_data;
    ctsu_data_t   average_self = {0, 0};
 #endif
 #if (CTSU_CFG_NUM_MUTUAL_ELEMENTS != 0)
    ctsu_data_t * p_pri_data;
    ctsu_data_t * p_snd_data;
    ctsu_data_t   average_pri = {0, 0};
    ctsu_data_t   average_snd = {0, 0};

  #if (CTSU_CFG_NUM_CFC != 0)
    uint8_t  ts_id;
    uint8_t  table_id;
    uint8_t  cfc_ts_table[CTSU_CFG_NUM_CFC];
    uint16_t offset = 0;
    uint16_t cfc_id = 0;
    uint16_t num_rx = 0;

    /* By inspection, calc.cfc is only used when calc.md == CTSU_MODE_MUTUAL_CFC_SCAN. It is initialized in this case.
     * However, GCC expects calc.cfc to be initialized before calling ctsu_correction_calc regardless of calc.md to
     * avoid the warning -Werror=maybe-uninitialized. */
    calc.cfc = 0;

    /* Create CFC-Rx table in ascending order at this instance */
    for (ts_id = 0; ts_id < CTSU_CORRCFC_TS_MAX; ts_id++)
    {
        if (1 == ((p_instance_ctrl->cfc_rx_bitmap >> ts_id) & 1))
        {
            for (table_id = 0; table_id < CTSU_CFG_NUM_CFC; table_id++)
            {
                if (g_ctsu_corrcfc_info.ts_table[table_id] == ts_id)
                {
                    cfc_ts_table[cfc_id] = table_id;
                    cfc_id++;
                }
            }
        }
    }
  #endif
 #endif
    calc.range = p_instance_ctrl->range;
    calc.md    = p_instance_ctrl->md;

    for (element_id = 0; element_id < p_instance_ctrl->num_elements; element_id++)
    {
        calc.snum = (p_instance_ctrl->p_ctsuwr[(element_id * CTSU_CFG_NUM_SUMULTI)].ctsuso >> 10) & CTSU_SNUM_MAX;
        for (i = 0; i < CTSU_CFG_NUM_SUMULTI; i++)
        {
            ctsuso =
                (p_instance_ctrl->p_ctsuwr[(element_id * CTSU_CFG_NUM_SUMULTI) + i].ctsuso & CTSU_TUNING_MAX);
            snum = (p_instance_ctrl->p_ctsuwr[(element_id * CTSU_CFG_NUM_SUMULTI)].ctsuso >> 10) &
                   CTSU_SNUM_MAX;
            offset_unit = ((int32_t) (CTSU_CORRECTION_OFFSET_UNIT * (snum + 1))) /
                          ((int32_t) (CTSU_SNUM_RECOMMEND + 1));
            multi.offset[i] = (ctsuso * (uint32_t) (offset_unit >> calc.range));
        }

        if (CTSU_MODE_SELF_MULTI_SCAN == p_instance_ctrl->md)
        {
 #if (CTSU_CFG_NUM_SELF_ELEMENTS != 0)
            for (i = 0; i < CTSU_CFG_NUM_SUMULTI; i++)
            {
                ctsu_correction_calc(&p_instance_ctrl->p_self_corr[(element_id * CTSU_CFG_NUM_SUMULTI) + i],
                                     p_instance_ctrl->p_self_raw[(element_id * CTSU_CFG_NUM_SUMULTI) + i],
                                     &calc);

                multi.pri[i] = p_instance_ctrl->p_self_corr[(element_id * CTSU_CFG_NUM_SUMULTI) + i];

                multi.snd[i] = 0;
            }

            p_self_data = (p_instance_ctrl->p_self_data + element_id);

            if (0 == p_instance_ctrl->average)
            {
                /* Store corrected data in p_pri_data[i] for initial offset tuning */
            }
            else
            {
                /* Store last moving averaged data */
                average_self.int_data           = p_self_data->int_data;
                average_self.decimal_point_data = p_self_data->decimal_point_data;

                /* Matching values */
                ctsu_correction_fleq(&multi, multi.pri, NULL);
                ctsu_correction_multi(&multi, &(p_self_data->int_data), NULL);

                *(p_instance_ctrl->p_selected_freq_self + element_id) = multi.selected_freq;

                /* Update moving averaged data */
                ctsu_moving_average(&average_self, p_self_data->int_data, p_instance_ctrl->average);
                *p_self_data = average_self;
            }
        }
        else if (CTSU_MODE_CURRENT_SCAN == p_instance_ctrl->md)
        {
            p_self_data = (p_instance_ctrl->p_self_data + (element_id * CTSU_CFG_NUM_SUMULTI));

            /* Store last moving averaged data */
            average_self = *p_self_data;

            /* Correction */
            ctsu_correction_calc(&(p_self_data->int_data), p_instance_ctrl->p_self_raw[element_id], &calc);

            /* Update moving averaged data */
            if (1 < p_instance_ctrl->average)
            {
                ctsu_moving_average(&average_self, p_self_data->int_data, p_instance_ctrl->average);
                *p_self_data = average_self;
            }
 #endif
        }
        else if (CTSU_MODE_MUTUAL_FULL_SCAN == p_instance_ctrl->md)
        {
 #if (CTSU_CFG_NUM_MUTUAL_ELEMENTS != 0)
            for (i = 0; i < CTSU_CFG_NUM_SUMULTI; i++)
            {
                ctsu_correction_calc(&p_instance_ctrl->p_mutual_pri_corr[(element_id * CTSU_CFG_NUM_SUMULTI) + i],
                                     p_instance_ctrl->p_mutual_raw[(element_id * CTSU_MUTUAL_BUF_SIZE) + (i * 2)],
                                     &calc);

                multi.pri[i] = p_instance_ctrl->p_mutual_pri_corr[(element_id * CTSU_CFG_NUM_SUMULTI) + i];

                ctsu_correction_calc(&p_instance_ctrl->p_mutual_snd_corr[(element_id * CTSU_CFG_NUM_SUMULTI) + i],
                                     p_instance_ctrl->p_mutual_raw[(element_id * CTSU_MUTUAL_BUF_SIZE) + (i * 2) + 1],
                                     &calc);

                multi.snd[i] = p_instance_ctrl->p_mutual_snd_corr[(element_id * CTSU_CFG_NUM_SUMULTI) + i];
            }

            p_pri_data = (p_instance_ctrl->p_mutual_pri_data + element_id);
            p_snd_data = (p_instance_ctrl->p_mutual_snd_data + element_id);

            if (0 == p_instance_ctrl->average)
            {
                /* Store corrected data in p_pri_data[i] for initial offset tuning */
            }
            else
            {
                /* Store last moving averaged data */
                average_pri = *p_pri_data;
                average_snd = *p_snd_data;

                /* Matching values */
                ctsu_correction_fleq(&multi, multi.pri, multi.snd);
                ctsu_correction_multi(&multi, &(p_pri_data->int_data), &(p_snd_data->int_data));
                *(p_instance_ctrl->p_selected_freq_mutual + element_id) = multi.selected_freq;

                /* Update moving averaged data */
                ctsu_moving_average(&average_pri, p_pri_data->int_data, p_instance_ctrl->average);
                *p_pri_data = average_pri;
                ctsu_moving_average(&average_snd, p_snd_data->int_data, p_instance_ctrl->average);
                *p_snd_data = average_snd;
            }
 #endif
        }
        else if (CTSU_MODE_MUTUAL_CFC_SCAN == p_instance_ctrl->md)
        {
 #if (CTSU_CFG_NUM_MUTUAL_ELEMENTS != 0)
  #if (CTSU_CFG_NUM_CFC != 0)
            if (CTSU_MODE_MUTUAL_CFC_SCAN == p_instance_ctrl->md)
            {
                num_rx = p_instance_ctrl->p_ctsu_cfg->num_rx;
                cfc_id = (uint16_t) (element_id % num_rx);
                if (0 == cfc_id)
                {
                    if (0 == element_id)
                    {
                        offset = 0;
                    }
                    else
                    {
                        offset = (uint16_t) (offset + (num_rx * CTSU_MUTUAL_BUF_SIZE));
                    }
                }
            }

            calc.cfc = cfc_ts_table[cfc_id];

            for (i = 0; i < CTSU_CFG_NUM_SUMULTI; i++)
            {
                ctsu_correction_calc(&p_instance_ctrl->p_mutual_pri_corr[(element_id * CTSU_CFG_NUM_SUMULTI) + i],
                                     p_instance_ctrl->p_mutual_raw[offset + cfc_id + (num_rx * i * 2)],
                                     &calc);

                multi.pri[i] = p_instance_ctrl->p_mutual_pri_corr[(element_id * CTSU_CFG_NUM_SUMULTI) + i];

                ctsu_correction_calc(&p_instance_ctrl->p_mutual_snd_corr[(element_id * CTSU_CFG_NUM_SUMULTI) + i],
                                     p_instance_ctrl->p_mutual_raw[offset + cfc_id + (num_rx * i * 2) + num_rx],
                                     &calc);

                multi.snd[i] = p_instance_ctrl->p_mutual_snd_corr[(element_id * CTSU_CFG_NUM_SUMULTI) + i];
            }

            p_pri_data = (p_instance_ctrl->p_mutual_pri_data + element_id);
            p_snd_data = (p_instance_ctrl->p_mutual_snd_data + element_id);

            if (0 == p_instance_ctrl->average)
            {
                /* Store corrected data in p_pri_data[i] for initial offset tuning */
                for (i = 0; i < CTSU_CFG_NUM_SUMULTI; i++)
                {
                    p_pri_data[i].int_data = multi.pri[i];
                }
            }
            else
            {
                /* Store last moving averaged data */
                average_pri = *p_pri_data;
                average_snd = *p_snd_data;

                /* Matching values */
                ctsu_correction_fleq(&multi, multi.pri, multi.snd);
                ctsu_correction_multi(&multi, &(p_pri_data->int_data), &(p_snd_data->int_data));
                *(p_instance_ctrl->p_selected_freq_mutual + element_id) = multi.selected_freq;

                /* Update moving averaged data */
                ctsu_moving_average(&average_pri, p_pri_data->int_data, p_instance_ctrl->average);
                *p_pri_data = average_pri;
                ctsu_moving_average(&average_snd, p_snd_data->int_data, p_instance_ctrl->average);
                *p_snd_data = average_snd;
            }
  #endif
 #endif
        }
        else
        {
        }
    }
#endif
}

#if (BSP_FEATURE_CTSU_VERSION == 2)

/***********************************************************************************************************************
 * ctsu_correction_multi
 ***********************************************************************************************************************/
void ctsu_correction_fleq (ctsu_correction_multi_t * p_multi, uint16_t * p_pri, uint16_t * p_snd)
{
    uint32_t i;
    int32_t  sumulti[CTSU_CFG_NUM_SUMULTI];
    int32_t  pri_calc[CTSU_CFG_NUM_SUMULTI];
    int32_t  snd_calc[CTSU_CFG_NUM_SUMULTI];
    int32_t  pri_total;
    int32_t  snd_total;

    sumulti[0] = CTSU_CFG_SUMULTI0 + 1;
 #if CTSU_CFG_NUM_SUMULTI >= 2
    sumulti[1] = CTSU_CFG_SUMULTI1 + 1;
 #endif
 #if CTSU_CFG_NUM_SUMULTI >= 3
    sumulti[2] = CTSU_CFG_SUMULTI2 + 1;
 #endif

    for (i = 1; i < CTSU_CFG_NUM_SUMULTI; i++)
    {
        pri_total   = (int32_t) (p_multi->pri[i] + p_multi->offset[i]);
        pri_calc[i] = (int32_t) (((pri_total * sumulti[0]) / sumulti[i]) - (int32_t) p_multi->offset[0]);
        p_pri[i]    = (uint16_t) pri_calc[i];
    }

    if (NULL == p_snd)
    {
        for (i = 0; i < CTSU_CFG_NUM_SUMULTI; i++)
        {
            p_multi->snd[i] = 0;
        }
    }
    else
    {
        for (i = 1; i < CTSU_CFG_NUM_SUMULTI; i++)
        {
            snd_total   = (int32_t) (p_multi->snd[i] + p_multi->offset[i]);
            snd_calc[i] = (int32_t) (((snd_total * sumulti[0]) / sumulti[i]) - (int32_t) p_multi->offset[0]);
            p_snd[i]    = (uint16_t) snd_calc[i];
        }
    }
}

void ctsu_correction_multi (ctsu_correction_multi_t * p_multi, uint16_t * p_pri, uint16_t * p_snd)
{
    int32_t add_pri;
    int32_t add_snd;
 #if CTSU_CFG_NUM_SUMULTI >= 3
    uint32_t i;
    int32_t  pri_calc[CTSU_CFG_NUM_SUMULTI];
    int32_t  snd_calc[CTSU_CFG_NUM_SUMULTI];
    int32_t  diff[CTSU_CFG_NUM_SUMULTI];
 #endif

 #if CTSU_CFG_NUM_SUMULTI == 1
    add_pri = p_multi->pri[0];
    add_snd = p_multi->snd[0];
 #endif
 #if CTSU_CFG_NUM_SUMULTI == 2
    add_pri = p_multi->pri[0] + p_multi->pri[1];
    add_snd = p_multi->snd[0] + p_multi->snd[1];
 #endif
 #if CTSU_CFG_NUM_SUMULTI >= 3
    for (i = 0; i < CTSU_CFG_NUM_SUMULTI; i++)
    {
        pri_calc[i] = (int32_t) p_multi->pri[i];
        if (NULL == p_snd)
        {
            snd_calc[i] = 0;
        }
        else
        {
            snd_calc[i] = (int32_t) p_multi->snd[i];
        }
    }

    diff[0] = (snd_calc[1] - pri_calc[1]) - (snd_calc[0] - pri_calc[0]);
    diff[1] = (snd_calc[2] - pri_calc[2]) - (snd_calc[0] - pri_calc[0]);
    diff[2] = (snd_calc[2] - pri_calc[2]) - (snd_calc[1] - pri_calc[1]);

    for (i = 0; i < CTSU_CFG_NUM_SUMULTI; i++)
    {
        if (diff[i] < 0)
        {
            diff[i] = -diff[i];
        }
    }

    /* Normally select freq0 and freq1 addition */
    /* If the following conditions are false, it is estimated to be a noise environment. */
    /* Compare with the combination with the other frequency difference (including margin). */
    if ((diff[0] < (diff[1] * 2)) && (diff[0] < ((diff[2] * 3) / 2)))
    {
        add_pri = pri_calc[0] + pri_calc[1];
        add_snd = snd_calc[0] + snd_calc[1];

        p_multi->selected_freq = 0x3;
    }
    else
    {
        if (diff[1] < diff[2])
        {
            add_pri = pri_calc[0] + pri_calc[2];
            add_snd = snd_calc[0] + snd_calc[2];

            p_multi->selected_freq = 0x5;
        }
        else
        {
            add_pri = pri_calc[1] + pri_calc[2];
            add_snd = snd_calc[1] + snd_calc[2];

            p_multi->selected_freq = 0x6;
        }
    }
 #endif

    if (CTSU_COUNT_MAX < add_pri)
    {
        *p_pri = CTSU_COUNT_MAX;
    }
    else
    {
        *p_pri = (uint16_t) add_pri;
    }

    if (NULL != p_snd)
    {
        if (CTSU_COUNT_MAX < add_snd)
        {
            *p_snd = CTSU_COUNT_MAX;
        }
        else
        {
            *p_snd = (uint16_t) add_snd;
        }
    }
}

 #if (CTSU_CFG_NUM_CFC != 0)

/***********************************************************************************************************************
 * ctsu_correction_process
 ***********************************************************************************************************************/
void ctsu_corrcfc_process (ctsu_instance_ctrl_t * const p_instance_ctrl)
{
    uint8_t            i;
    uint8_t            j;
    uint8_t            ts_id;
    uint8_t            index;
    uint64_t           new_bitmap;
    ctsu_cfg_t const * p_cfg;
    uint16_t           base_value;
    uint16_t           base_conv_dac;
    int32_t            x0;
    int32_t            x1;
    int32_t            y0;

    g_ctsu_corrcfc_info.status = CTSU_CORRECTION_RUN;

    p_cfg = p_instance_ctrl->p_ctsu_cfg;
    index = g_ctsu_corrcfc_info.index;

    /* Get CFC-Rx bitmap at this instance. */
    p_instance_ctrl->cfc_rx_bitmap =
        ((uint64_t) (p_cfg->ctsuchac0 & (~p_cfg->ctsuchtrc0)) |
         ((uint64_t) (p_cfg->ctsuchac1 & (~p_cfg->ctsuchtrc1)) << (CTSU_CORRCFC_SHIFT8)) |
         ((uint64_t) (p_cfg->ctsuchac2 & (~p_cfg->ctsuchtrc2)) << (CTSU_CORRCFC_SHIFT8 * 2)) |
         ((uint64_t) (p_cfg->ctsuchac3 & (~p_cfg->ctsuchtrc3)) << (CTSU_CORRCFC_SHIFT8 * 3)) |
         ((uint64_t) (p_cfg->ctsuchac4 & (~p_cfg->ctsuchtrc4)) << (CTSU_CORRCFC_SHIFT8 * 4)));

    /* Get RX bitmap at this correction. */
    new_bitmap = p_instance_ctrl->cfc_rx_bitmap & (~g_ctsu_corrcfc_info.stored_rx_bitmap);

    /* Get TS id and number of TS in this instance. */
    g_ctsu_corrcfc_info.num_ts = 0;
    for (ts_id = 0; ts_id < CTSU_CORRCFC_TS_MAX; ts_id++)
    {
        if (1 == ((new_bitmap >> ts_id) & 1))
        {
            g_ctsu_corrcfc_info.ts_table[index + g_ctsu_corrcfc_info.num_ts] = ts_id;
            g_ctsu_corrcfc_info.num_ts++;
        }
    }

    /* Add the bitmap of this instance to the entire CFC correction information. */
    g_ctsu_corrcfc_info.stored_rx_bitmap |= p_instance_ctrl->cfc_rx_bitmap;

    /* Write Channel setting */
    R_CTSU->CTSUCHAC0 = (uint8_t) (new_bitmap);
    R_CTSU->CTSUCHAC1 = (uint8_t) (new_bitmap >> (CTSU_CORRCFC_SHIFT8));
    R_CTSU->CTSUCHAC2 = (uint8_t) (new_bitmap >> (CTSU_CORRCFC_SHIFT8 * 2));
    R_CTSU->CTSUCHAC3 = (uint8_t) (new_bitmap >> (CTSU_CORRCFC_SHIFT8 * 3));
    R_CTSU->CTSUCHAC4 = (uint8_t) (new_bitmap >> (CTSU_CORRCFC_SHIFT8 * 4));

    /* Set register of CFC self mode */
    R_CTSU->CTSUCRA_b.MD0  = 1;
    R_CTSU->CTSUCRA_b.MD1  = 0;
    R_CTSU->CTSUCRA_b.MD2  = 1;
    R_CTSU->CTSUMCH_b.MCA0 = 1;
    R_CTSU->CTSUMCH_b.MCA1 = 0;
    R_CTSU->CTSUMCH_b.MCA2 = 0;
    R_CTSU->CTSUMCH_b.MCA3 = 0;

    /* Set time of measurement */
    g_ctsu_corrcfc_info.ctsuwr.ctsuso = (CTSU_SNUM_RECOMMEND << 10);

    /* Step1 : Measure the current input to the CFC-ICO by passing bias current. */
    /*         The theoretical value of the current is 6uA. */
    ctsu_corrcfc_measurement(p_instance_ctrl, &g_ctsu_corrcfc_info.base_value[index], 1);

    /* Step2 : Measure by inputting each constant current from internal DAC to CFC-ICO. */
    R_CTSU->CTSUCRB_b.SSCNT     = 0;
    R_CTSU->CTSUCRA_b.LOAD      = 1;
    R_CTSU->CTSUCALIB_b.CCOCLK  = 0;
    R_CTSU->CTSUCALIB_b.CFCMODE = 1;

    for (j = 0; j < CTSU_CORRCFC_POINT_NUM; j++)
    {
        R_CTSU->CTSUCRA_b.SDPSEL = 0;
        R_CTSU->CTSUSUCLK0       = (uint16_t) (((j + CTSU_CORRCFC_CENTER_POINT) * CTSU_CORRECTION_SUMULTI) - 1);
        R_CTSU->CTSUCRA_b.SDPSEL = 1;

        ctsu_corrcfc_measurement(p_instance_ctrl, &g_ctsu_corrcfc_info.dac_value[index][j], CTSU_CORRCFC_POINT_NUM);
    }

    /* Reset register */
    R_CTSU->CTSUCALIB_b.CFCMODE = 0;
    R_CTSU->CTSUCALIB_b.CCOCLK  = 1;

    /* Step3 : Calculate the error between step1 and step2. */
    for (i = index; i < (index + g_ctsu_corrcfc_info.num_ts); i++)
    {
        /* Linear interpolation calculation */
        base_value = g_ctsu_corrcfc_info.base_value[i];
        j          = 1;
        while (1)
        {
            if ((base_value < g_ctsu_corrcfc_info.dac_value[index][j]) || ((CTSU_CORRCFC_POINT_NUM - 1) == j))
            {
                y0 = (uint16_t) (CTSU_CORRECTION_STD_UNIT * (j + CTSU_CORRCFC_CENTER_POINT));
                x0 = g_ctsu_corrcfc_info.dac_value[index][j];
                x1 = g_ctsu_corrcfc_info.dac_value[index][j - 1];
                break;
            }

            j++;
        }

        base_conv_dac = (uint16_t) (y0 - ((CTSU_CORRECTION_STD_UNIT * (x0 - base_value)) / (x0 - x1)));

        /* Error rate calculation */
        g_ctsu_corrcfc_info.error_rate[i] =
            (uint16_t) (((CTSU_CORRECTION_STD_UNIT * 4) << CTSU_SHIFT_AMOUNT) / base_conv_dac);

        for (j = 0; j < CTSU_CORRCFC_POINT_NUM; j++)
        {
            g_ctsu_corrcfc_info.ref_value[i][j] =
                (uint16_t) ((CTSU_CORRECTION_STD_UNIT * (j + CTSU_CORRCFC_CENTER_POINT) *
                             g_ctsu_corrcfc_info.error_rate[i]) >> CTSU_SHIFT_AMOUNT);
        }
    }

    g_ctsu_corrcfc_info.index = (uint8_t) (index + g_ctsu_corrcfc_info.num_ts);

    g_ctsu_corrcfc_info.status = CTSU_CORRECTION_COMPLETE;
}

/***********************************************************************************************************************
 * ctsu_corrcfc_measurement
 ***********************************************************************************************************************/
void ctsu_corrcfc_measurement (ctsu_instance_ctrl_t * const p_instance_ctrl, uint16_t * data, uint8_t point_num)
{
    uint16_t i;
    uint8_t  cfc_id;
    uint32_t sum[CTSU_CFG_NUM_CFC];

    /* initialize sum array */
    for (cfc_id = 0; cfc_id < CTSU_CFG_NUM_CFC; cfc_id++)
    {
        sum[cfc_id] = 0;
    }

    for (i = 0; i < CTSU_CORRECTION_AVERAGE; i++)
    {
  #if (CTSU_CFG_DTC_SUPPORT_ENABLE == 1)
        ctsu_transfer_configure(p_instance_ctrl);
  #else
        FSP_PARAMETER_NOT_USED(p_instance_ctrl);
  #endif
        p_instance_ctrl->state = CTSU_STATE_SCANNING;
        R_CTSU->CTSUCR0       |= 0x01;
        while (p_instance_ctrl->state != CTSU_STATE_SCANNED)
        {
        }

        /* Get sum */
        for (cfc_id = 0; cfc_id < CTSU_CFG_NUM_CFC; cfc_id++)
        {
            sum[cfc_id] += g_ctsu_corrcfc_info.scanbuf[cfc_id];
        }
    }

    /* Average sum data */
    for (cfc_id = 0; cfc_id < g_ctsu_corrcfc_info.num_ts; cfc_id++)
    {
        *(data + (cfc_id * point_num)) = (uint16_t) (sum[cfc_id] / CTSU_CORRECTION_AVERAGE);
    }
}

 #endif
#endif

/*******************************************************************************************************************//**
 * @brief Diagnosis the CTSU peripheral.
 * Implements @ref ctsu_api_t::diagnosis.
 *
 *
 * Example:
 * @snippet r_ctsu_example.c R_CTSU_Diagnosis
 *
 * @retval FSP_SUCCESS                             CTSU successfully configured.
 * @retval FSP_ERR_ASSERTION                       Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN                        Module is not open.
 * @retval FSP_ERR_CTSU_NOT_GET_DATA               The previous data has not been retrieved by DataGet.
 * @retval FSP_ERR_CTSU_DIAG_LDO_OVER_VOLTAGE      Diagnosis of LDO over voltage failed.
 * @retval FSP_ERR_CTSU_DIAG_CCO_HIGH              Diagnosis of CCO into 19.2uA failed.
 * @retval FSP_ERR_CTSU_DIAG_CCO_LOW               Diagnosis of CCO into 2.4uA failed.
 * @retval FSP_ERR_CTSU_DIAG_SSCG                  Diagnosis of SSCG frequency failed.
 * @retval FSP_ERR_CTSU_DIAG_DAC                   Diagnosis of non-touch count value failed.
 * @retval FSP_ERR_CTSU_DIAG_OUTPUT_VOLTAGE        Diagnosis of LDO output voltage failed.
 * @retval FSP_ERR_CTSU_DIAG_OVER_VOLTAGE          Diagnosis of over voltage detection circuit failed.
 * @retval FSP_ERR_CTSU_DIAG_OVER_CURRENT          Diagnosis of over current detection circuit failed.
 * @retval FSP_ERR_CTSU_DIAG_LOAD_RESISTANCE       Diagnosis of LDO internal resistance value failed.
 * @retval FSP_ERR_CTSU_DIAG_CURRENT_SOURCE        Diagnosis of LDO internal resistance value failed.
 * @retval FSP_ERR_CTSU_DIAG_SENSCLK_GAIN          Diagnosis of SENSCLK frequency gain failed.
 * @retval FSP_ERR_CTSU_DIAG_SUCLK_GAIN            Diagnosis of SUCLK frequency gain failed.
 * @retval FSP_ERR_CTSU_DIAG_CLOCK_RECOVERY        Diagnosis of SUCLK clock recovery function failed.
 * @retval FSP_ERR_CTSU_DIAG_CFC_GAIN              Diagnosis of CFC oscillator gain failed.
 **********************************************************************************************************************/

fsp_err_t R_CTSU_Diagnosis (ctsu_ctrl_t * const p_ctrl)
{
#if (CTSU_CFG_DIAG_SUPPORT_ENABLE == 1)
    fsp_err_t diag_err;
#endif
    ctsu_instance_ctrl_t * p_instance_ctrl = (ctsu_instance_ctrl_t *) p_ctrl;

#if (CTSU_CFG_PARAM_CHECKING_ENABLE == 1)
    FSP_ASSERT(p_instance_ctrl);
    FSP_ERROR_RETURN(CTSU_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif
    FSP_ERROR_RETURN(CTSU_STATE_SCANNED != p_instance_ctrl->state, FSP_ERR_CTSU_NOT_GET_DATA);

#if (BSP_FEATURE_CTSU_VERSION == 1)
 #if (CTSU_CFG_DIAG_SUPPORT_ENABLE == 1)
    if (CTSU_DIAG_COMPLETE == g_ctsu_diag_info.state)
    {
        diag_err = ctsu_diag_ldo_over_voltage_result();
        if (FSP_SUCCESS != diag_err)
        {
            g_ctsu_diag_info.state = CTSU_DIAG_INIT;

            return FSP_ERR_CTSU_DIAG_LDO_OVER_VOLTAGE;
        }

        diag_err = ctsu_diag_oscillator_high_result();
        if (FSP_SUCCESS != diag_err)
        {
            g_ctsu_diag_info.state = CTSU_DIAG_INIT;

            return FSP_ERR_CTSU_DIAG_CCO_HIGH;
        }

        diag_err = ctsu_diag_oscillator_low_result();
        if (FSP_SUCCESS != diag_err)
        {
            g_ctsu_diag_info.state = CTSU_DIAG_INIT;

            return FSP_ERR_CTSU_DIAG_CCO_LOW;
        }

        diag_err = ctsu_diag_sscg_result();
        if (FSP_SUCCESS != diag_err)
        {
            g_ctsu_diag_info.state = CTSU_DIAG_INIT;

            return FSP_ERR_CTSU_DIAG_SSCG;
        }

        diag_err = ctsu_diag_dac_result();
        if (FSP_SUCCESS != diag_err)
        {
            g_ctsu_diag_info.state = CTSU_DIAG_INIT;

            return FSP_ERR_CTSU_DIAG_DAC;
        }

        g_ctsu_diag_info.state = CTSU_DIAG_INIT;
    }
 #endif
#endif

#if (BSP_FEATURE_CTSU_VERSION == 2)
 #if (CTSU_CFG_DIAG_SUPPORT_ENABLE == 1)
    if (CTSU_DIAG_COMPLETE == g_ctsu_diag_info.state)
    {
        ctsu_diag_regi_store2();

        g_ctsu_diag_info.state = CTSU_DIAG_OUTPUT_VOLTAGE;
        diag_err               = ctsu_diag_output_voltage_result();
        if (FSP_SUCCESS != diag_err)
        {
            ctsu_diag_regi_restore2();
            g_ctsu_diag_info.state = CTSU_DIAG_INIT;

            return FSP_ERR_CTSU_DIAG_OUTPUT_VOLTAGE;
        }

        g_ctsu_diag_info.state = CTSU_DIAG_OVER_VOLTAGE;
        diag_err               = ctsu_diag_over_voltage_result();
        if (FSP_SUCCESS != diag_err)
        {
            ctsu_diag_regi_restore2();
            g_ctsu_diag_info.state = CTSU_DIAG_INIT;

            return FSP_ERR_CTSU_DIAG_OVER_VOLTAGE;
        }

        g_ctsu_diag_info.state = CTSU_DIAG_OVER_CURRENT;
        diag_err               = ctsu_diag_over_current_result();
        if (FSP_SUCCESS != diag_err)
        {
            ctsu_diag_regi_restore2();
            g_ctsu_diag_info.state = CTSU_DIAG_INIT;

            return FSP_ERR_CTSU_DIAG_OVER_CURRENT;
        }

        g_ctsu_diag_info.state = CTSU_DIAG_LOAD_RESISTANCE;
        diag_err               = ctsu_diag_load_resistance_result();
        if (FSP_SUCCESS != diag_err)
        {
            ctsu_diag_regi_restore2();
            g_ctsu_diag_info.state = CTSU_DIAG_INIT;

            return FSP_ERR_CTSU_DIAG_LOAD_RESISTANCE;
        }

        g_ctsu_diag_info.state = CTSU_DIAG_CURRENT_SOURCE;
        diag_err               = ctsu_diag_current_source_result();
        if (FSP_SUCCESS != diag_err)
        {
            ctsu_diag_regi_restore2();
            g_ctsu_diag_info.state = CTSU_DIAG_INIT;

            return FSP_ERR_CTSU_DIAG_CURRENT_SOURCE;
        }

        g_ctsu_diag_info.state = CTSU_DIAG_SENSCLK;
        diag_err               = ctsu_diag_cco_gain_result();
        if (FSP_SUCCESS != diag_err)
        {
            ctsu_diag_regi_restore2();
            g_ctsu_diag_info.state = CTSU_DIAG_INIT;

            return FSP_ERR_CTSU_DIAG_SENSCLK_GAIN;
        }

        g_ctsu_diag_info.state = CTSU_DIAG_SUCLK;
        diag_err               = ctsu_diag_cco_gain_result();
        if (FSP_SUCCESS != diag_err)
        {
            ctsu_diag_regi_restore2();
            g_ctsu_diag_info.state = CTSU_DIAG_INIT;

            return FSP_ERR_CTSU_DIAG_SUCLK_GAIN;
        }

        g_ctsu_diag_info.state = CTSU_DIAG_CLOCK_RECOVERY;
        diag_err               = ctsu_diag_clock_recovery_result();
        if (FSP_SUCCESS != diag_err)
        {
            ctsu_diag_regi_restore2();
            g_ctsu_diag_info.state = CTSU_DIAG_INIT;

            return FSP_ERR_CTSU_DIAG_CLOCK_RECOVERY;
        }

  #if (CTSU_CFG_NUM_CFC != 0)
        g_ctsu_diag_info.state = CTSU_DIAG_CFC;
        diag_err               = ctsu_diag_cfc_gain_result();
        if (FSP_SUCCESS != diag_err)
        {
            ctsu_diag_regi_restore2();
            g_ctsu_diag_info.state = CTSU_DIAG_INIT;

            return FSP_ERR_CTSU_DIAG_CFC_GAIN;
        }
  #endif

        ctsu_diag_regi_restore2();
        g_ctsu_diag_info.state = CTSU_DIAG_INIT;
    }
 #endif
#endif

    /* if all checks passed to this point, return success */
    return FSP_SUCCESS;
}

#if (BSP_FEATURE_CTSU_VERSION == 1)
 #if (CTSU_CFG_DIAG_SUPPORT_ENABLE == 1)

/***********************************************************************************************************************
 * ctsu_diag_scan_start1
 ***********************************************************************************************************************/
static void ctsu_diag_scan_start1 (ctsu_instance_ctrl_t * const p_instance_ctrl)
{
    if (CTSU_DIAG_INIT == g_ctsu_diag_info.state)
    {
        g_ctsu_diag_info.state = CTSU_DIAG_OVER_VOLTAGE;
    }

    /* ctsu normal scan register save */
    g_ctsu_diag_reg.ctsucr0    = R_CTSU->CTSUCR0;
    g_ctsu_diag_reg.ctsucr1    = R_CTSU->CTSUCR1;
    g_ctsu_diag_reg.ctsusdprs  = R_CTSU->CTSUSDPRS;
    g_ctsu_diag_reg.ctsusst    = R_CTSU->CTSUSST;
    g_ctsu_diag_reg.ctsuchac0  = R_CTSU->CTSUCHAC[0];
    g_ctsu_diag_reg.ctsuchac1  = R_CTSU->CTSUCHAC[1];
    g_ctsu_diag_reg.ctsuchac2  = R_CTSU->CTSUCHAC[2];
    g_ctsu_diag_reg.ctsuchtrc0 = R_CTSU->CTSUCHTRC[0];
    g_ctsu_diag_reg.ctsuchtrc1 = R_CTSU->CTSUCHTRC[1];
    g_ctsu_diag_reg.ctsuchtrc2 = R_CTSU->CTSUCHTRC[2];
    g_ctsu_diag_reg.ctsudclkc  = R_CTSU->CTSUDCLKC;
    g_ctsu_diag_reg.ctsuerrs   = R_CTSU->CTSUERRS;

    /* scan register setting */
    if (CTSU_DIAG_OVER_VOLTAGE == g_ctsu_diag_info.state)
    {
        ctsu_diag_ldo_over_voltage_scan_start();
    }

    if (CTSU_DIAG_CCO_HIGH == g_ctsu_diag_info.state)
    {
        ctsu_diag_oscillator_high_scan_start();
    }

    if (CTSU_DIAG_CCO_LOW == g_ctsu_diag_info.state)
    {
        ctsu_diag_oscillator_low_scan_start();
    }

    if (CTSU_DIAG_SSCG == g_ctsu_diag_info.state)
    {
        ctsu_diag_sscg_scan_start();
    }

    if (CTSU_DIAG_DAC == g_ctsu_diag_info.state)
    {
        ctsu_diag_dac_scan_start(p_instance_ctrl);
    }
}

/***********************************************************************************************************************
 * ctsu_diag_data_get1
 ***********************************************************************************************************************/
static fsp_err_t ctsu_diag_data_get1 (void)
{
    fsp_err_t err;

    /* data get */
    if (CTSU_DIAG_OVER_VOLTAGE == g_ctsu_diag_info.state)
    {
        ctsu_diag_ldo_over_voltage_data_get();

        g_ctsu_diag_info.state = CTSU_DIAG_CCO_HIGH;
    }
    else if (CTSU_DIAG_CCO_HIGH == g_ctsu_diag_info.state)
    {
        ctsu_diag_oscillator_high_data_get();

        g_ctsu_diag_info.state = CTSU_DIAG_CCO_LOW;
    }
    else if (CTSU_DIAG_CCO_LOW == g_ctsu_diag_info.state)
    {
        ctsu_diag_oscillator_low_data_get();

        g_ctsu_diag_info.state = CTSU_DIAG_SSCG;
    }
    else if (CTSU_DIAG_SSCG == g_ctsu_diag_info.state)
    {
        ctsu_diag_sscg_data_get();

        g_ctsu_diag_info.state = CTSU_DIAG_DAC;
    }
    else if (CTSU_DIAG_DAC == g_ctsu_diag_info.state)
    {
        ctsu_diag_dac_data_get();
        if (CTSU_TUNING_INCOMPLETE == g_ctsu_diag_info.tuning)
        {
            g_ctsu_diag_info.state = CTSU_DIAG_DAC;
        }
        else
        {
            g_ctsu_diag_info.loop_count++;
            if (6 <= g_ctsu_diag_info.loop_count)
            {
                g_ctsu_diag_info.state      = CTSU_DIAG_COMPLETE;
                g_ctsu_diag_info.loop_count = 0;
            }
        }
    }
    else
    {
    }

    /* register restore */
    R_CTSU->CTSUCR0                = g_ctsu_diag_reg.ctsucr0;
    R_CTSU->CTSUCR1                = g_ctsu_diag_reg.ctsucr1;
    R_CTSU->CTSUSDPRS              = g_ctsu_diag_reg.ctsusdprs;
    R_CTSU->CTSUSST                = g_ctsu_diag_reg.ctsusst;
    R_CTSU->CTSUCHAC[0]            = g_ctsu_diag_reg.ctsuchac0;
    R_CTSU->CTSUCHAC[1]            = g_ctsu_diag_reg.ctsuchac1;
    R_CTSU->CTSUCHAC[2]            = g_ctsu_diag_reg.ctsuchac2;
    R_CTSU->CTSUCHTRC[0]           = g_ctsu_diag_reg.ctsuchtrc0;
    R_CTSU->CTSUCHTRC[1]           = g_ctsu_diag_reg.ctsuchtrc1;
    R_CTSU->CTSUCHTRC[2]           = g_ctsu_diag_reg.ctsuchtrc2;
    R_CTSU->CTSUDCLKC              = g_ctsu_diag_reg.ctsudclkc;
    R_CTSU->CTSUERRS_b.CTSUSPMD    = 0;
    R_CTSU->CTSUERRS_b.CTSUTSOD    = 0;
    R_CTSU->CTSUERRS_b.CTSUDRV     = 0;
    R_CTSU->CTSUERRS_b.CTSUTSOC    = 0;
    R_CTSU->CTSUERRS_b.CTSUCLKSEL1 = 0;

    if (CTSU_DIAG_COMPLETE == g_ctsu_diag_info.state)
    {
        err = FSP_SUCCESS;
    }
    else
    {
        err = FSP_ERR_CTSU_DIAG_NOT_YET;
    }

    return err;
}

static void ctsu_diag_ldo_over_voltage_scan_start (void)
{
    uint32_t pclkb_mhz;
    uint32_t ctsu_sdpa;

    /* Set power on */
    R_CTSU->CTSUCR1 = ((CTSU_CFG_LOW_VOLTAGE_MODE << 2) | (CTSU_CSW_ON << 1) | CTSU_PON_ON);

    /* Synchronous Noise Reduction Setting */
    R_CTSU->CTSUSDPRS = ((CTSU_SOFF_ON << 6) | (CTSU_PRMODE_62_PULSES << 4) | CTSU_PRRATIO_RECOMMEND);

    /* High Pass Noise Reduction- ALWAYS 0x30 as per HW Manual */
    R_CTSU->CTSUDCLKC = ((CTSU_SSCNT << 4) | CTSU_SSMOD);

    /* Sensor Stabilization- ALWAYS 0x10 as per HW Manual */
    R_CTSU->CTSUSST = (CTSU_SST_RECOMMEND);

    /* Since CLK is rewritten by correction, set here. */
    R_CTSU->CTSUCR1 |= (uint8_t) (CTSU_CFG_PCLK_DIVISION << 4);

    pclkb_mhz = R_FSP_SystemClockHzGet(FSP_PRIV_CLOCK_PCLKB) / CTSU_PCLKB_FREQ_MHZ;
    if (CTSU_PCLKB_FREQ_RANGE1 >= pclkb_mhz)
    {
        R_CTSU->CTSUCR1 |= (0 << 4);
        ctsu_sdpa        = pclkb_mhz - 1;
    }
    else if ((CTSU_PCLKB_FREQ_RANGE1 < pclkb_mhz) && (CTSU_PCLKB_FREQ_RANGE2 >= pclkb_mhz))
    {
        R_CTSU->CTSUCR1 |= (1 << 4);
        ctsu_sdpa        = (pclkb_mhz / 2) - 1;
    }
    else
    {
        R_CTSU->CTSUCR1 |= (2 << 4);
        ctsu_sdpa        = (pclkb_mhz / 4) - 1;
    }

    R_CTSU->CTSUCR1     |= (CTSU_MODE_SELF_MULTI_SCAN << 6);
    R_CTSU->CTSUCHAC[0]  = 0x01;
    R_CTSU->CTSUCHAC[1]  = 0x00;
    R_CTSU->CTSUCHAC[2]  = 0x00;
    R_CTSU->CTSUCHAC[3]  = 0x00;
    R_CTSU->CTSUCHAC[4]  = 0x00;
    R_CTSU->CTSUCHTRC[0] = 0x00;
    R_CTSU->CTSUCHTRC[1] = 0x00;
    R_CTSU->CTSUCHTRC[2] = 0x00;
    R_CTSU->CTSUCHTRC[3] = 0x00;
    R_CTSU->CTSUCHTRC[4] = 0x00;

    /* Correction measurement setting */
    R_CTSU->CTSUERRS_b.CTSUSPMD    = 0;
    R_CTSU->CTSUERRS_b.CTSUTSOD    = 0;
    R_CTSU->CTSUERRS_b.CTSUDRV     = 0;
    R_CTSU->CTSUERRS_b.CTSUCLKSEL1 = 0;
    R_CTSU->CTSUERRS_b.CTSUTSOC    = 1;
    g_ctsu_diag_info.icomp         = 0;

    g_ctsu_diag_info.ctsuwr.ctsussc = (CTSU_SSDIV_0500 << 8);
    g_ctsu_diag_info.ctsuwr.ctsuso0 = CTSU_DIAG_DAC_SO_MAX;
    g_ctsu_diag_info.ctsuwr.ctsuso1 = (uint16_t) ((CTSU_ICOG_66 << 13) | (ctsu_sdpa << 8) | CTSU_RICOA_RECOMMEND);
}

static void ctsu_diag_ldo_over_voltage_data_get (void)
{
    /* Nothing */
}

static fsp_err_t ctsu_diag_ldo_over_voltage_result (void)
{
    if (1 != g_ctsu_diag_info.icomp)
    {
        return FSP_ERR_CTSU_DIAG_LDO_OVER_VOLTAGE;
    }

    /* if all checks passed to this point, return success */
    return FSP_SUCCESS;
}

static void ctsu_diag_oscillator_high_scan_start (void)
{
    uint32_t ctsu_sdpa;
    uint32_t pclkb_mhz;

    /* Set power on */
    R_CTSU->CTSUCR1 = ((CTSU_CFG_LOW_VOLTAGE_MODE << 2) | (CTSU_CSW_ON << 1) | CTSU_PON_ON);

    /* Synchronous Noise Reduction Setting */
    R_CTSU->CTSUSDPRS = ((CTSU_SOFF_ON << 6) | (CTSU_PRMODE_62_PULSES << 4) | CTSU_PRRATIO_RECOMMEND);

    /* High Pass Noise Reduction- ALWAYS 0x30 as per HW Manual */
    R_CTSU->CTSUDCLKC = ((CTSU_SSCNT << 4) | CTSU_SSMOD);

    /* Sensor Stabilization- ALWAYS 0x10 as per HW Manual */
    R_CTSU->CTSUSST = (CTSU_SST_RECOMMEND);

    /* Since CLK is rewritten by correction, set here. */
    R_CTSU->CTSUCR1 |= (uint8_t) (CTSU_CFG_PCLK_DIVISION << 4);

    pclkb_mhz = R_FSP_SystemClockHzGet(FSP_PRIV_CLOCK_PCLKB) / CTSU_PCLKB_FREQ_MHZ;
    if (CTSU_PCLKB_FREQ_RANGE1 >= pclkb_mhz)
    {
        R_CTSU->CTSUCR1 |= (0 << 4);
        ctsu_sdpa        = pclkb_mhz - 1;
    }
    else if ((CTSU_PCLKB_FREQ_RANGE1 < pclkb_mhz) && (CTSU_PCLKB_FREQ_RANGE2 >= pclkb_mhz))
    {
        R_CTSU->CTSUCR1 |= (1 << 4);
        ctsu_sdpa        = (pclkb_mhz / 2) - 1;
    }
    else
    {
        R_CTSU->CTSUCR1 |= (2 << 4);
        ctsu_sdpa        = (pclkb_mhz / 4) - 1;
    }

    R_CTSU->CTSUCR1     |= (CTSU_MODE_SELF_MULTI_SCAN << 6);
    R_CTSU->CTSUCHAC[0]  = 0x01;
    R_CTSU->CTSUCHAC[1]  = 0x00;
    R_CTSU->CTSUCHAC[2]  = 0x00;
    R_CTSU->CTSUCHAC[3]  = 0x00;
    R_CTSU->CTSUCHAC[4]  = 0x00;
    R_CTSU->CTSUCHTRC[0] = 0x00;
    R_CTSU->CTSUCHTRC[1] = 0x00;
    R_CTSU->CTSUCHTRC[2] = 0x00;
    R_CTSU->CTSUCHTRC[3] = 0x00;
    R_CTSU->CTSUCHTRC[4] = 0x00;

    R_CTSU->CTSUSO0_b.CTSUSO = 0;

    g_ctsu_diag_info.ctsuwr.ctsussc = (CTSU_SSDIV_0500 << 8);
    g_ctsu_diag_info.ctsuwr.ctsuso0 = 0x0000;
    g_ctsu_diag_info.ctsuwr.ctsuso1 = (uint16_t) ((CTSU_ICOG_66 << 13) | (ctsu_sdpa << 8) | CTSU_RICOA_RECOMMEND);

    /* Correction measurement setting */
    R_CTSU->CTSUERRS_b.CTSUSPMD = 2;   // 0x82
    R_CTSU->CTSUERRS_b.CTSUTSOC = 1;
    R_BSP_SoftwareDelay(10, BSP_DELAY_UNITS_MILLISECONDS);
}

static void ctsu_diag_oscillator_high_data_get (void)
{
    g_ctsu_diag_info.cco_high = g_ctsu_diag_info.scanbuf.sen;
}

static fsp_err_t ctsu_diag_oscillator_high_result (void)
{
    if ((g_ctsu_diag_info.cco_high < CTSU_CFG_DIAG_CCO_HIGH_MAX) &&
        (g_ctsu_diag_info.cco_high > CTSU_CFG_DIAG_CCO_HIGH_MIN))
    {
    }
    else
    {
        return FSP_ERR_CTSU_DIAG_CCO_HIGH;
    }

    /* if all checks passed to this point, return success */
    return FSP_SUCCESS;
}

static void ctsu_diag_oscillator_low_scan_start (void)
{
    uint32_t ctsu_sdpa;
    uint32_t pclkb_mhz;

    /* Set power on */
    R_CTSU->CTSUCR1 = ((CTSU_CFG_LOW_VOLTAGE_MODE << 2) | (CTSU_CSW_ON << 1) | CTSU_PON_ON);

    /* Synchronous Noise Reduction Setting */
    R_CTSU->CTSUSDPRS = ((CTSU_SOFF_ON << 6) | (CTSU_PRMODE_62_PULSES << 4) | CTSU_PRRATIO_RECOMMEND);

    /* High Pass Noise Reduction- ALWAYS 0x30 as per HW Manual */
    R_CTSU->CTSUDCLKC = ((CTSU_SSCNT << 4) | CTSU_SSMOD);

    /* Sensor Stabilization- ALWAYS 0x10 as per HW Manual */
    R_CTSU->CTSUSST = (CTSU_SST_RECOMMEND);

    /* Since CLK is rewritten by correction, set here. */
    R_CTSU->CTSUCR1 |= (uint8_t) (CTSU_CFG_PCLK_DIVISION << 4);

    pclkb_mhz = R_FSP_SystemClockHzGet(FSP_PRIV_CLOCK_PCLKB) / CTSU_PCLKB_FREQ_MHZ;
    if (CTSU_PCLKB_FREQ_RANGE1 >= pclkb_mhz)
    {
        R_CTSU->CTSUCR1 |= (0 << 4);
        ctsu_sdpa        = pclkb_mhz - 1;
    }
    else if ((CTSU_PCLKB_FREQ_RANGE1 < pclkb_mhz) && (CTSU_PCLKB_FREQ_RANGE2 >= pclkb_mhz))
    {
        R_CTSU->CTSUCR1 |= (1 << 4);
        ctsu_sdpa        = (pclkb_mhz / 2) - 1;
    }
    else
    {
        R_CTSU->CTSUCR1 |= (2 << 4);
        ctsu_sdpa        = (pclkb_mhz / 4) - 1;
    }

    R_CTSU->CTSUCR1     |= (CTSU_MODE_SELF_MULTI_SCAN << 6);
    R_CTSU->CTSUCHAC[0]  = 0x01;
    R_CTSU->CTSUCHAC[1]  = 0x00;
    R_CTSU->CTSUCHAC[2]  = 0x00;
    R_CTSU->CTSUCHAC[3]  = 0x00;
    R_CTSU->CTSUCHAC[4]  = 0x00;
    R_CTSU->CTSUCHTRC[0] = 0x00;
    R_CTSU->CTSUCHTRC[1] = 0x00;
    R_CTSU->CTSUCHTRC[2] = 0x00;
    R_CTSU->CTSUCHTRC[3] = 0x00;
    R_CTSU->CTSUCHTRC[4] = 0x00;

    R_CTSU->CTSUSO0_b.CTSUSO = 0;

    g_ctsu_diag_info.ctsuwr.ctsussc = (CTSU_SSDIV_0500 << 8);
    g_ctsu_diag_info.ctsuwr.ctsuso0 = 0x0000;
    g_ctsu_diag_info.ctsuwr.ctsuso1 = (uint16_t) ((CTSU_ICOG_66 << 13) | (ctsu_sdpa << 8) | CTSU_RICOA_RECOMMEND);

    /* Correction measurement setting */
    R_CTSU->CTSUERRS_b.CTSUSPMD = 0;   // 0x80
    R_CTSU->CTSUERRS_b.CTSUTSOC = 1;
    R_BSP_SoftwareDelay(10, BSP_DELAY_UNITS_MILLISECONDS);
}

static void ctsu_diag_oscillator_low_data_get (void)
{
    g_ctsu_diag_info.cco_low = g_ctsu_diag_info.scanbuf.sen;
}

static fsp_err_t ctsu_diag_oscillator_low_result (void)
{
    if ((g_ctsu_diag_info.cco_low < CTSU_CFG_DIAG_CCO_LOW_MAX) &&
        (g_ctsu_diag_info.cco_low > CTSU_CFG_DIAG_CCO_LOW_MIN))
    {
    }
    else
    {
        return FSP_ERR_CTSU_DIAG_CCO_LOW;
    }

    /* if all checks passed to this point, return success */
    return FSP_SUCCESS;
}

static void ctsu_diag_sscg_scan_start (void)
{
    uint32_t ctsu_sdpa;
    uint32_t pclkb_mhz;

    /* Set power on */
    R_CTSU->CTSUCR1 = ((CTSU_CFG_LOW_VOLTAGE_MODE << 2) | (CTSU_CSW_ON << 1) | CTSU_PON_ON);

    /* Synchronous Noise Reduction Setting */
    R_CTSU->CTSUSDPRS = ((CTSU_SOFF_ON << 6) | (CTSU_PRMODE_62_PULSES << 4) | CTSU_PRRATIO_RECOMMEND);

    /* High Pass Noise Reduction- ALWAYS 0x30 as per HW Manual */
    R_CTSU->CTSUDCLKC = ((CTSU_SSCNT << 4) | CTSU_SSMOD);

    /* Sensor Stabilization- ALWAYS 0x10 as per HW Manual */
    R_CTSU->CTSUSST = (CTSU_SST_RECOMMEND);

    /* Since CLK is rewritten by correction, set here. */
    R_CTSU->CTSUCR1 |= (uint8_t) (CTSU_CFG_PCLK_DIVISION << 4);

    pclkb_mhz = R_FSP_SystemClockHzGet(FSP_PRIV_CLOCK_PCLKB) / CTSU_PCLKB_FREQ_MHZ;
    if (CTSU_PCLKB_FREQ_RANGE1 >= pclkb_mhz)
    {
        R_CTSU->CTSUCR1 |= (0 << 4);
        ctsu_sdpa        = pclkb_mhz - 1;
    }
    else if ((CTSU_PCLKB_FREQ_RANGE1 < pclkb_mhz) && (CTSU_PCLKB_FREQ_RANGE2 >= pclkb_mhz))
    {
        R_CTSU->CTSUCR1 |= (1 << 4);
        ctsu_sdpa        = (pclkb_mhz / 2) - 1;
    }
    else
    {
        R_CTSU->CTSUCR1 |= (2 << 4);
        ctsu_sdpa        = (pclkb_mhz / 4) - 1;
    }

    R_CTSU->CTSUCR1 |= (CTSU_MODE_SELF_MULTI_SCAN << 6);

    R_CTSU->CTSUCHAC[0]  = 0x01;
    R_CTSU->CTSUCHAC[1]  = 0x00;
    R_CTSU->CTSUCHAC[2]  = 0x00;
    R_CTSU->CTSUCHAC[3]  = 0x00;
    R_CTSU->CTSUCHAC[4]  = 0x00;
    R_CTSU->CTSUCHTRC[0] = 0x00;
    R_CTSU->CTSUCHTRC[1] = 0x00;
    R_CTSU->CTSUCHTRC[2] = 0x00;
    R_CTSU->CTSUCHTRC[3] = 0x00;
    R_CTSU->CTSUCHTRC[4] = 0x00;

    R_CTSU->CTSUSO0_b.CTSUSO = 0;

    g_ctsu_diag_info.ctsuwr.ctsussc = (CTSU_SSDIV_0500 << 8);
    g_ctsu_diag_info.ctsuwr.ctsuso0 = 0x0000;
    g_ctsu_diag_info.ctsuwr.ctsuso1 = (uint16_t) ((CTSU_ICOG_66 << 13) | (ctsu_sdpa << 8) | CTSU_RICOA_RECOMMEND);

    /* Correction measurement setting */
    R_CTSU->CTSUERRS_b.CTSUSPMD    = 0;
    R_CTSU->CTSUERRS_b.CTSUTSOD    = 0;
    R_CTSU->CTSUERRS_b.CTSUDRV     = 0;
    R_CTSU->CTSUERRS_b.CTSUTSOC    = 1;
    R_CTSU->CTSUERRS_b.CTSUCLKSEL1 = 1;
}

static void ctsu_diag_sscg_data_get (void)
{
    g_ctsu_diag_info.sscg = g_ctsu_diag_info.scanbuf.ref;
}

static fsp_err_t ctsu_diag_sscg_result (void)
{
    if ((g_ctsu_diag_info.sscg > CTSU_CFG_DIAG_SSCG_MAX) || (g_ctsu_diag_info.sscg < CTSU_CFG_DIAG_SSCG_MIN))
    {
        return FSP_ERR_CTSU_DIAG_SSCG;
    }

    /* if all checks passed to this point, return success */
    return FSP_SUCCESS;
}

static void ctsu_diag_dac_initial_tuning (void)
{
    int32_t  diff          = 0;
    uint32_t complete_flag = 0;
    uint16_t ctsuso;

    diff = g_ctsu_diag_info.correct_data - CTSU_DIAG_DAC_TARGET_VALUE;

    ctsuso = g_ctsu_diag_info.ctsuwr.ctsuso0 & CTSU_TUNING_MAX;
    if (0 < diff)
    {
        if (g_ctsu_diag_info.tuning_diff < 0)
        {
            if ((-diff) > g_ctsu_diag_info.tuning_diff)
            {
                ctsuso++;
            }

            complete_flag = 1;
        }
        else
        {
            if (CTSU_TUNING_MAX == ctsuso)
            {
                complete_flag = 1;
            }
            else
            {
                ctsuso++;
                g_ctsu_diag_info.tuning_diff = diff;
            }
        }
    }
    else if (0 == diff)
    {
        complete_flag = 1;
    }
    else
    {
        if (g_ctsu_diag_info.tuning_diff > 0)
        {
            if ((-diff) > g_ctsu_diag_info.tuning_diff)
            {
                ctsuso--;
            }

            complete_flag = 1;
        }
        else
        {
            complete_flag = 1;
        }
    }

    g_ctsu_diag_info.ctsuwr.ctsuso0 &= (uint16_t) (~CTSU_TUNING_MAX);
    g_ctsu_diag_info.ctsuwr.ctsuso0 |= ctsuso;

    if (CTSU_CFG_NUM_SUMULTI == complete_flag)
    {
        g_ctsu_diag_info.tuning_diff = 0;
        g_ctsu_diag_info.so0_4uc_val = ctsuso;
        g_ctsu_diag_info.dac_init    = 3;
        g_ctsu_diag_info.tuning      = CTSU_TUNING_COMPLETE;
        g_ctsu_diag_info.loop_count  = 0;
        g_ctsu_diag_info.dac_cnt[0]  = g_ctsu_diag_info.correct_data;
    }
}

static void ctsu_diag_dac_scan_start (ctsu_instance_ctrl_t * const p_instance_ctrl)
{
    uint8_t temp;

    /* Set power on */
    R_CTSU->CTSUCR1 = ((CTSU_CFG_LOW_VOLTAGE_MODE << 2) | (CTSU_CSW_ON << 1) | CTSU_PON_ON);

    /* Synchronous Noise Reduction Setting */
    R_CTSU->CTSUSDPRS = ((CTSU_SOFF_ON << 6) | (CTSU_PRMODE_62_PULSES << 4) | CTSU_PRRATIO_RECOMMEND);

    /* High Pass Noise Reduction- ALWAYS 0x30 as per HW Manual */
    R_CTSU->CTSUDCLKC = ((CTSU_SSCNT << 4) | CTSU_SSMOD);

    /* Sensor Stabilization- ALWAYS 0x10 as per HW Manual */
    R_CTSU->CTSUSST = (CTSU_SST_RECOMMEND);

    /* Since CLK is rewritten by correction, set here. */
    R_CTSU->CTSUCR1 |= (uint8_t) (CTSU_CFG_PCLK_DIVISION << 4);

    temp            = (uint8_t) (R_CTSU->CTSUCR1 & ~(CTSU_CR1_MODIFY_BIT));
    R_CTSU->CTSUCR1 = (uint8_t) (temp | (p_instance_ctrl->ctsucr1 & CTSU_CR1_MODIFY_BIT) | CTSU_DAC_TEST_ATUNE1); // MD1, MD0, ATUNE1=1
  #if BSP_FEATURE_CTSU_HAS_TXVSEL
    R_CTSU->CTSUCR0 =
        (uint8_t) ((R_CTSU->CTSUCR0 & ~(CTSU_TXVSEL)) | (p_instance_ctrl->p_ctsu_cfg->txvsel & CTSU_TXVSEL));
  #endif

    /* Write Channel setting */
  #if (CTSU_CFG_DIAG_DAC_TS >= 0) && (CTSU_CFG_DIAG_DAC_TS < 8)
    R_CTSU->CTSUCHAC[0] = 1 << CTSU_CFG_DIAG_DAC_TS;
  #else
    R_CTSU->CTSUCHAC[0] = 0;
  #endif
  #if (CTSU_CFG_DIAG_DAC_TS >= 8) && (CTSU_CFG_DIAG_DAC_TS < 16)
    R_CTSU->CTSUCHAC[1] = 1 << (CTSU_CFG_DIAG_DAC_TS - 8);
  #else
    R_CTSU->CTSUCHAC[1] = 0;
  #endif
  #if (CTSU_CFG_DIAG_DAC_TS >= 16) && (CTSU_CFG_DIAG_DAC_TS < 24)
    R_CTSU->CTSUCHAC[2] = 1 << (CTSU_CFG_DIAG_DAC_TS - 16);
  #else
    R_CTSU->CTSUCHAC[2] = 0;
  #endif
  #if (CTSU_CFG_DIAG_DAC_TS >= 24) && (CTSU_CFG_DIAG_DAC_TS < 32)
    R_CTSU->CTSUCHAC[3] = 1 << (CTSU_CFG_DIAG_DAC_TS - 24);
  #else
    R_CTSU->CTSUCHAC[3] = 0;
  #endif
    R_CTSU->CTSUCHAC[4]  = 0;
    R_CTSU->CTSUCHTRC[0] = 0;
    R_CTSU->CTSUCHTRC[1] = 0;
    R_CTSU->CTSUCHTRC[2] = 0;
    R_CTSU->CTSUCHTRC[3] = 0;
    R_CTSU->CTSUCHTRC[4] = 0;

    g_ctsu_diag_info.ctsuwr.ctsussc = (uint16_t) (CTSU_SSDIV_1330 << 8);
    g_ctsu_diag_info.ctsuwr.ctsuso1 = (uint16_t) ((CTSU_ICOG_RECOMMEND << 13) | (7 << 8) | CTSU_RICOA_RECOMMEND);

    if (g_ctsu_diag_info.dac_init > 2)
    {
        /* Apply DAC current */
        if (0 == g_ctsu_diag_info.loop_count)
        {
            g_ctsu_diag_info.ctsuwr.ctsuso0 = (uint16_t) ((3 << 10) | g_ctsu_diag_info.so0_4uc_val);
        }
        else if (1 == g_ctsu_diag_info.loop_count)
        {
            g_ctsu_diag_info.ctsuwr.ctsuso0 =
                (uint16_t) ((3 << 10) | (g_ctsu_diag_info.so0_4uc_val - CTSU_DIAG_DAC_1UC));
        }
        else if (2 == g_ctsu_diag_info.loop_count)
        {
            g_ctsu_diag_info.ctsuwr.ctsuso0 =
                (uint16_t) ((3 << 10) | (g_ctsu_diag_info.so0_4uc_val - CTSU_DIAG_DAC_2UC));
        }
        else if (3 == g_ctsu_diag_info.loop_count)
        {
            g_ctsu_diag_info.ctsuwr.ctsuso0 =
                (uint16_t) ((3 << 10) | (g_ctsu_diag_info.so0_4uc_val - CTSU_DIAG_DAC_4UC));
        }
        else if (4 == g_ctsu_diag_info.loop_count)
        {
            g_ctsu_diag_info.ctsuwr.ctsuso0 =
                (uint16_t) ((3 << 10) | (g_ctsu_diag_info.so0_4uc_val - CTSU_DIAG_DAC_8UC));
        }
        else if (5 == g_ctsu_diag_info.loop_count)
        {
            g_ctsu_diag_info.ctsuwr.ctsuso0 =
                (uint16_t) ((3 << 10) | (g_ctsu_diag_info.so0_4uc_val - CTSU_DIAG_DAC_16UC));
        }
        else
        {
        }
    }

    if (g_ctsu_diag_info.dac_init == 0)
    {
        g_ctsu_diag_info.dac_init       = 1;
        g_ctsu_diag_info.so0_4uc_val    = 0;
        g_ctsu_diag_info.tuning_diff    = 0;
        g_ctsu_diag_info.ctsuwr.ctsuso0 = (3 << 10) + CTSU_DIAG_DAC_START_VALUE;
    }
}

static void ctsu_diag_dac_data_get (void)
{
    ctsu_correction_calc_t calc;

    calc.snum = (g_ctsu_diag_info.ctsuwr.ctsuso0 >> 10) & CTSU_SNUM_MAX;

    if (CTSU_DIAG_DAC == g_ctsu_diag_info.state)
    {
        calc.snum = 3;
    }

    calc.sdpa = (g_ctsu_diag_info.ctsuwr.ctsuso1 >> 8) & CTSU_SDPA_MAX;

    /* Correction process */
    ctsu_correction_calc(&g_ctsu_diag_info.correct_data, g_ctsu_diag_info.scanbuf.sen, &calc);

    if (g_ctsu_diag_info.tuning == CTSU_TUNING_COMPLETE)
    {
        g_ctsu_diag_info.dac_cnt[g_ctsu_diag_info.loop_count] = g_ctsu_diag_info.correct_data;
    }
    else
    {
        ctsu_diag_dac_initial_tuning();
    }
}

static fsp_err_t ctsu_diag_dac_result (void)
{
    uint8_t k;
    if (g_ctsu_diag_info.tuning == CTSU_TUNING_COMPLETE)
    {
        for (k = 0; k < 6; k++)
        {
            if ((g_ctsu_diag_info.dac_cnt[k] > dac_oscil_table[k][0]) ||
                (g_ctsu_diag_info.dac_cnt[k] < dac_oscil_table[k][1]))
            {
                return FSP_ERR_CTSU_DIAG_DAC;
            }
        }
    }

    /* if all checks passed to this point, return success */
    return FSP_SUCCESS;
}

 #endif
#endif

#if (BSP_FEATURE_CTSU_VERSION == 2)
 #if (CTSU_CFG_DIAG_SUPPORT_ENABLE == 1)

/***********************************************************************************************************************
 * ctsu_diag_scan_start2
 ***********************************************************************************************************************/
static fsp_err_t ctsu_diag_scan_start2 (ctsu_instance_ctrl_t * const p_instance_ctrl)
{
    adc_instance_t const * p_adc = p_instance_ctrl->p_ctsu_cfg->p_adc_instance;
    fsp_err_t              err   = FSP_SUCCESS;

    /* initial state change*/
    if (CTSU_DIAG_INIT == g_ctsu_diag_info.state)
    {
        g_ctsu_diag_info.state = CTSU_DIAG_OUTPUT_VOLTAGE;
    }

    /* ctsu normal scan register save */
    ctsu_diag_regi_store2();

    /* scan register setting */
    if (CTSU_DIAG_OUTPUT_VOLTAGE == g_ctsu_diag_info.state)
    {
        err = ctsu_diag_output_voltage_scan_start(p_instance_ctrl);
        if (FSP_SUCCESS == err)
        {
            g_ctsu_diag_info.state = CTSU_DIAG_OVER_VOLTAGE;
        }
        else
        {
            if (FSP_ERR_ALREADY_OPEN != err)
            {
                p_adc->p_api->close(p_adc->p_ctrl);
            }

            err = FSP_SUCCESS;

            g_ctsu_diag_info.state   = CTSU_DIAG_OUTPUT_VOLTAGE;
            R_CTSU->CTSUCRA_b.ATUNE1 = 0;
            R_CTSU->CTSUCRA_b.ATUNE2 = 0;
            R_CTSU->CTSUCRA_b.LOAD   = 0;
            R_CTSU->CTSUMCH_b.MCA0   = 1;
            R_CTSU->CTSUMCH_b.MCA1   = 0;
            R_CTSU->CTSUMCH_b.MCA2   = 0;
            R_CTSU->CTSUMCH_b.MCA3   = 0;
            R_CTSU->CTSUCHACA        = g_ctsu_diag_info.chaca;
            R_CTSU->CTSUCHACB        = g_ctsu_diag_info.chacb;
            R_CTSU->CTSUCHTRC0       = 0;
            R_CTSU->CTSUCHTRC1       = 0;
            R_CTSU->CTSUCHTRC2       = 0;
            R_CTSU->CTSUCHTRC3       = 0;
            R_CTSU->CTSUCHTRC4       = 0;
        }
    }

    if (CTSU_DIAG_OVER_VOLTAGE == g_ctsu_diag_info.state)
    {
        ctsu_diag_over_voltage_scan_start();
        g_ctsu_diag_info.state = CTSU_DIAG_OVER_CURRENT;
    }

    if (CTSU_DIAG_OVER_CURRENT == g_ctsu_diag_info.state)
    {
        ctsu_diag_over_current_scan_start();
    }

    if (CTSU_DIAG_LOAD_RESISTANCE == g_ctsu_diag_info.state)
    {
        ctsu_diag_load_resistance_scan_start();
    }

    if (CTSU_DIAG_CURRENT_SOURCE == g_ctsu_diag_info.state)
    {
        ctsu_diag_current_source_scan_start();
    }

    if (CTSU_DIAG_SENSCLK == g_ctsu_diag_info.state)
    {
        ctsu_diag_cco_gain_scan_start();
    }

    if (CTSU_DIAG_SUCLK == g_ctsu_diag_info.state)
    {
        ctsu_diag_cco_gain_scan_start();
    }

    if (CTSU_DIAG_CLOCK_RECOVERY == g_ctsu_diag_info.state)
    {
        ctsu_diag_clock_recovery_scan_start();
    }

  #if (CTSU_CFG_NUM_CFC != 0)
    if (CTSU_DIAG_CFC == g_ctsu_diag_info.state)
    {
        ctsu_diag_cfc_gain_scan_start();
    }
  #endif

    return err;
}

/***********************************************************************************************************************
 * ctsu_diag_data_get2
 ***********************************************************************************************************************/
static fsp_err_t ctsu_diag_data_get2 (uint16_t * p_data)
{
    fsp_err_t err;

    if (CTSU_DIAG_LOAD_RESISTANCE == g_ctsu_diag_info.state)
    {
        ctsu_diag_load_resistance_data_get();
    }

    if (CTSU_DIAG_CURRENT_SOURCE == g_ctsu_diag_info.state)
    {
        ctsu_diag_current_source_data_get();
    }

    if (CTSU_DIAG_SENSCLK == g_ctsu_diag_info.state)
    {
        ctsu_diag_cco_gain_data_get();
    }

    if (CTSU_DIAG_SUCLK == g_ctsu_diag_info.state)
    {
        ctsu_diag_cco_gain_data_get();
    }

    if (CTSU_DIAG_CLOCK_RECOVERY == g_ctsu_diag_info.state)
    {
        ctsu_diag_clock_recovery_data_get();
    }

  #if (CTSU_CFG_NUM_CFC != 0)
    if (CTSU_DIAG_CFC == g_ctsu_diag_info.state)
    {
        ctsu_diag_cfc_gain_data_get();
    }
  #endif

    /* DIagnosis state transition */
    if (CTSU_DIAG_OVER_CURRENT == g_ctsu_diag_info.state)
    {
        g_ctsu_diag_info.loop_count = 0;
        g_ctsu_diag_info.state      = CTSU_DIAG_LOAD_RESISTANCE;
    }
    else if ((CTSU_DIAG_LOAD_RESISTANCE == g_ctsu_diag_info.state) && (CTSU_RANGE_NUM <= g_ctsu_diag_info.loop_count))
    {
        g_ctsu_diag_info.loop_count = 0;
        g_ctsu_diag_info.state      = CTSU_DIAG_CURRENT_SOURCE;
    }
    else if ((CTSU_DIAG_CURRENT_SOURCE == g_ctsu_diag_info.state) &&
             ((CTSU_DIAG_HIGH_CURRENT_SOURCE + CTSU_DIAG_LOW_CURRENT_SOURCE) <= g_ctsu_diag_info.loop_count))
    {
        g_ctsu_diag_info.loop_count = 0;
        g_ctsu_diag_info.state      = CTSU_DIAG_SENSCLK;
    }
    else if ((CTSU_DIAG_SENSCLK == g_ctsu_diag_info.state) &&
             (CTSU_CORRECTION_POINT_NUM <= g_ctsu_diag_info.loop_count))
    {
        g_ctsu_diag_info.loop_count = 0;
        g_ctsu_diag_info.state      = CTSU_DIAG_SUCLK;
    }
    else if ((CTSU_DIAG_SUCLK == g_ctsu_diag_info.state) && (CTSU_CORRECTION_POINT_NUM <= g_ctsu_diag_info.loop_count))
    {
        g_ctsu_diag_info.loop_count = 0;
        g_ctsu_diag_info.state      = CTSU_DIAG_CLOCK_RECOVERY;
    }
    else if (CTSU_DIAG_CLOCK_RECOVERY == g_ctsu_diag_info.state)
    {
  #if (CTSU_CFG_NUM_CFC != 0)
        g_ctsu_diag_info.state = CTSU_DIAG_CFC;
  #else
        g_ctsu_diag_info.state = CTSU_DIAG_COMPLETE;
  #endif
    }

  #if (CTSU_CFG_NUM_CFC != 0)
    else if ((CTSU_DIAG_CFC == g_ctsu_diag_info.state) && (CTSU_CORRCFC_POINT_NUM <= g_ctsu_diag_info.loop_count))
    {
        g_ctsu_diag_info.loop_count = 0;
        g_ctsu_diag_info.state      = CTSU_DIAG_COMPLETE;
    }
  #endif
    else
    {
    }

    if ((CTSU_DIAG_OUTPUT_VOLTAGE <= g_ctsu_diag_info.state) && (CTSU_DIAG_OVER_CURRENT >= g_ctsu_diag_info.state))
    {
        *p_data = g_ctsu_diag_info.output_voltage_cnt[0];
    }
    else
    {
        /* Indicates that ADC measurement was not performed. */
        *p_data = CTSU_COUNT_MAX;
    }

    /* register restore */
    ctsu_diag_regi_restore2();

    if (CTSU_DIAG_COMPLETE == g_ctsu_diag_info.state)
    {
        err = FSP_SUCCESS;
    }
    else if (CTSU_DIAG_OUTPUT_VOLTAGE == g_ctsu_diag_info.state)
    {
        err = FSP_ERR_ABORTED;
        g_ctsu_diag_info.state = CTSU_DIAG_INIT;
    }
    else
    {
        err = FSP_ERR_CTSU_DIAG_NOT_YET;
    }

    return err;
}

static void ctsu_diag_regi_store2 (void)
{
    g_ctsu_diag_reg.ctsucra    = R_CTSU->CTSUCRA;
    g_ctsu_diag_reg.ctsucrb    = R_CTSU->CTSUCRB;
    g_ctsu_diag_reg.ctsuchaca  = R_CTSU->CTSUCHACA;
    g_ctsu_diag_reg.ctsuchacb  = R_CTSU->CTSUCHACB;
    g_ctsu_diag_reg.ctsuchtrca = R_CTSU->CTSUCHTRCA;
    g_ctsu_diag_reg.ctsuchtrcb = R_CTSU->CTSUCHTRCB;
    g_ctsu_diag_reg.ctsumch    = R_CTSU->CTSUMCH;
    g_ctsu_diag_reg.ctsucalib  = R_CTSU->CTSUCALIB;
    g_ctsu_diag_reg.ctsusuclka = R_CTSU->CTSUSUCLKA;
    g_ctsu_diag_reg.ctsusuclkb = R_CTSU->CTSUSUCLKB;
}

static void ctsu_diag_regi_restore2 (void)
{
    /* register restore */
    R_CTSU->CTSUCRA    = g_ctsu_diag_reg.ctsucra;
    R_CTSU->CTSUCRB    = g_ctsu_diag_reg.ctsucrb;
    R_CTSU->CTSUCHACA  = g_ctsu_diag_reg.ctsuchaca;
    R_CTSU->CTSUCHACB  = g_ctsu_diag_reg.ctsuchacb;
    R_CTSU->CTSUCHTRCA = g_ctsu_diag_reg.ctsuchtrca;
    R_CTSU->CTSUCHTRCB = g_ctsu_diag_reg.ctsuchtrcb;
    R_CTSU->CTSUMCH    = g_ctsu_diag_reg.ctsumch;
    R_CTSU->CTSUCALIB  = g_ctsu_diag_reg.ctsucalib;
    R_CTSU->CTSUSUCLKA = g_ctsu_diag_reg.ctsusuclka;
    R_CTSU->CTSUSUCLKB = g_ctsu_diag_reg.ctsusuclkb;
}

static fsp_err_t ctsu_diag_output_voltage_scan_start (ctsu_instance_ctrl_t * const p_instance_ctrl)
{
    uint8_t                k;
    adc_status_t           status;
    adc_instance_t const * p_adc = p_instance_ctrl->p_ctsu_cfg->p_adc_instance;
    fsp_err_t              err;

    /* Initialize ADC for CTSU TSCAP */
    err = p_adc->p_api->open(p_adc->p_ctrl, p_adc->p_cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    err = p_adc->p_api->scanCfg(p_adc->p_ctrl, p_adc->p_channel_cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    R_ADC0->ADSSTRL = CTSU_DIAG_ADSSTRL;

    /* CTSU setting */
    R_CTSU->CTSUCRA_b.PUMPON = 1;
    R_CTSU->CTSUCRA_b.CSW    = 1;
    R_CTSU->CTSUCRA_b.PON    = 1;
    R_CTSU->CTSUCALIB        = 0;

    /* Self single scan mode */
    R_CTSU->CTSUCRA_b.MD0 = 0;
    R_CTSU->CTSUCRA_b.MD1 = 0;
    R_CTSU->CTSUCRA_b.MD2 = 0;
    R_CTSU->CTSUSO        = CTSU_DIAG_DAC_INIT_0;
    R_CTSU->CTSUSO        = CTSU_DIAG_DAC_INIT_1;
    R_CTSU->CTSUSO        = CTSU_DIAG_DAC_INIT_2;
    R_CTSU->CTSUSO        = CTSU_DIAG_DAC_INIT_3;

    /* LDO setting */
    R_CTSU->CTSUCALIB_b.DRV = 0;

    for (k = 0; k < 8; k++)
    {
        switch (k)
        {
            case 0:
            {
                /*select normal mode */
                R_CTSU->CTSUCRA_b.LOAD = 0;

                /* LDO Setting (20uA)*/
                R_CTSU->CTSUCRA_b.ATUNE1 = 0;
                R_CTSU->CTSUCRA_b.ATUNE2 = 1;
                break;
            }

            case 1:
            {
                /*select normal mode */
                R_CTSU->CTSUCRA_b.LOAD = 0;

                /* LDO Setting (40uA) */
                R_CTSU->CTSUCRA_b.ATUNE1 = 1;
                R_CTSU->CTSUCRA_b.ATUNE2 = 0;
                break;
            }

            case 2:
            {
                /*select normal mode */
                R_CTSU->CTSUCRA_b.LOAD = 0;

                /* LDO Setting (80uA) */
                R_CTSU->CTSUCRA_b.ATUNE1 = 0;
                R_CTSU->CTSUCRA_b.ATUNE2 = 0;
                break;
            }

            case 3:
            {
                /*select normal mode */
                R_CTSU->CTSUCRA_b.LOAD = 0;

                /* LDO Setting (160uA) */
                R_CTSU->CTSUCRA_b.ATUNE1 = 1;
                R_CTSU->CTSUCRA_b.ATUNE2 = 1;
                break;
            }

            case 4:
            {
                /*select normal mode */
                R_CTSU->CTSUCRA_b.LOAD = 1;
                R_CTSU->CTSUCRA_b.LOAD = 3;

                /* LDO Setting (20uA) */
                R_CTSU->CTSUCRA_b.ATUNE1 = 0;
                R_CTSU->CTSUCRA_b.ATUNE2 = 1;
                break;
            }

            case 5:
            {
                /* select Resistive load mode */
                R_CTSU->CTSUCRA_b.LOAD = 1;
                R_CTSU->CTSUCRA_b.LOAD = 3;

                /* LDO Setting (40uA) */
                R_CTSU->CTSUCRA_b.ATUNE1 = 1;
                R_CTSU->CTSUCRA_b.ATUNE2 = 0;
                break;
            }

            case 6:
            {
                /* select Resistive load mode */
                R_CTSU->CTSUCRA_b.LOAD = 1;
                R_CTSU->CTSUCRA_b.LOAD = 3;

                /* LDO Setting (80uA) */
                R_CTSU->CTSUCRA_b.ATUNE1 = 0;
                R_CTSU->CTSUCRA_b.ATUNE2 = 0;
                break;
            }

            case 7:
            {
                /* select Resistive load mode */
                R_CTSU->CTSUCRA_b.LOAD = 1;
                R_CTSU->CTSUCRA_b.LOAD = 3;

                /* LDO Setting (160uA) */
                R_CTSU->CTSUCRA_b.ATUNE1 = 1;
                R_CTSU->CTSUCRA_b.ATUNE2 = 1;
                break;
            }

            default:
            {
                break;
            }
        }

        R_CTSU->CTSUCALIB_b.DRV = 1;

        /* Measure TSCAP Voltage with ADC */
        err = p_adc->p_api->scanStart(p_adc->p_ctrl);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

        /* Wait for conversion to complete. */
        status.state = ADC_STATE_SCAN_IN_PROGRESS;
        while (ADC_STATE_SCAN_IN_PROGRESS == status.state)
        {
            err = p_adc->p_api->scanStatusGet(p_adc->p_ctrl, &status);
            FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
        }

        err = p_adc->p_api->read(p_adc->p_ctrl, ADC_CHANNEL_16, &g_ctsu_diag_info.output_voltage_cnt[k]);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }

    /* Close ADC for CTSU TSCAP */
    p_adc->p_api->close(p_adc->p_ctrl);

    return err;
}

static fsp_err_t ctsu_diag_output_voltage_result (void)
{
    uint8_t k;

    for (k = 0; k < 8; k++)
    {
        if ((g_ctsu_diag_info.output_voltage_cnt[k] <= CTSU_DIAG_TSCAP_RANGE_LOW) ||
            (g_ctsu_diag_info.output_voltage_cnt[k] >= CTSU_DIAG_TSCAP_RANGE_HIGH))
        {
            return FSP_ERR_CTSU_DIAG_OUTPUT_VOLTAGE;
        }
    }

    /* if all checks passed to this point, return success */
    return FSP_SUCCESS;
}

static void ctsu_diag_over_voltage_scan_start (void)
{
    g_ctsu_diag_info.icomp0_value = 1;

    R_CTSU->CTSUCRA_b.PUMPON  = 1;
    R_CTSU->CTSUCRA_b.CSW     = 1;
    R_CTSU->CTSUCRA_b.PON     = 1;
    R_CTSU->CTSUCALIB         = 0;
    R_CTSU->CTSUCALIB_b.DRV   = 1;
    R_CTSU->CTSUCALIB_b.DCOFF = 1;

    R_CTSU->CTSUCRA_b.LOAD   = 1;
    R_CTSU->CTSUCRA_b.ATUNE1 = 1;
    R_CTSU->CTSUCRA_b.ATUNE2 = 0;
    R_CTSU->CTSUCRA_b.LOAD   = 3;

    R_CTSU->CTSUSR_b.ICOMPRST = 1;
    R_CTSU->CTSUCALIB         = CTSU_DIAG_CURRENT_CLIB_REG;
    R_CTSU->CTSUSO            = 0;
    R_CTSU->CTSUSO            = 0;

    R_BSP_SoftwareDelay(1, BSP_DELAY_UNITS_MILLISECONDS);

    if (R_CTSU->CTSUSR_b.ICOMP0 != 0)
    {
        g_ctsu_diag_info.icomp0_value = 0;
    }

    R_CTSU->CTSUCRA_b.LOAD   = 1;
    R_CTSU->CTSUCRA_b.ATUNE1 = 1;
    R_CTSU->CTSUCRA_b.ATUNE2 = 1;
    R_CTSU->CTSUCRA_b.LOAD   = 3;

    R_CTSU->CTSUCALIB = CTSU_DIAG_CURRENT_CLIB_REG;

    R_CTSU->CTSUCRA_b.LOAD = 2;
    R_CTSU->CTSUSO         = CTSU_DIAG_DAC_DATA_MAX_2;
    R_CTSU->CTSUSO         = CTSU_DIAG_DAC_DATA_MAX_3;

    R_BSP_SoftwareDelay(1, BSP_DELAY_UNITS_MILLISECONDS);

    if (R_CTSU->CTSUSR_b.ICOMP0 != 1)
    {
        g_ctsu_diag_info.icomp0_value = 0;
    }

    R_CTSU->CTSUSR_b.ICOMPRST = 1;

    R_BSP_SoftwareDelay(1, BSP_DELAY_UNITS_MILLISECONDS);

    if (R_CTSU->CTSUSR_b.ICOMP0 != 1)
    {
        g_ctsu_diag_info.icomp0_value = 0;
    }

    /* 30kohm setting */
    R_CTSU->CTSUCRA_b.ATUNE1 = 1;
    R_CTSU->CTSUCRA_b.ATUNE2 = 0;
    R_CTSU->CTSUCRA_b.LOAD   = 1;
    R_CTSU->CTSUCALIB        = CTSU_DIAG_CURRENT_CLIB_REG;

    /* 0uA setting */
    R_CTSU->CTSUSO = 0x00000000;
    R_CTSU->CTSUSO = 0x00000000;

    R_BSP_SoftwareDelay(1, BSP_DELAY_UNITS_MILLISECONDS);

    if (R_CTSU->CTSUSR_b.ICOMP0 != 1)
    {
        g_ctsu_diag_info.icomp0_value = 0;
    }

    R_CTSU->CTSUSR_b.ICOMPRST = 1;

    R_BSP_SoftwareDelay(1, BSP_DELAY_UNITS_MILLISECONDS);

    if (R_CTSU->CTSUSR_b.ICOMP0 != 0)
    {
        g_ctsu_diag_info.icomp0_value = 0;
    }
}

static fsp_err_t ctsu_diag_over_voltage_result (void)
{
    if (0 == g_ctsu_diag_info.icomp0_value)
    {
        return FSP_ERR_CTSU_DIAG_OVER_VOLTAGE;
    }

    /* if all checks passed to this point, return success */
    return FSP_SUCCESS;
}

static void ctsu_diag_over_current_scan_start (void)
{
    R_CTSU->CTSUCALIB         = 0;
    R_CTSU->CTSUCALIB_b.DRV   = 0;
    R_CTSU->CTSUCALIB_b.DCOFF = 0;
    R_CTSU->CTSUCRA_b.ATUNE1  = 0;
    R_CTSU->CTSUCRA_b.ATUNE2  = 0;
    R_CTSU->CTSUCRA_b.LOAD    = 0;
    R_CTSU->CTSUSR_b.ICOMPRST = 1;

    R_CTSU->CTSUMCH_b.MCA0 = 1;
    R_CTSU->CTSUMCH_b.MCA1 = 0;
    R_CTSU->CTSUMCH_b.MCA2 = 0;
    R_CTSU->CTSUMCH_b.MCA3 = 0;

    R_CTSU->CTSUCRA_b.MD0 = 1;
    R_CTSU->CTSUCRA_b.MD1 = 0;
    R_CTSU->CTSUCRA_b.MD2 = 0;

    R_CTSU->CTSUCHACA  = g_ctsu_diag_info.chaca;
    R_CTSU->CTSUCHACB  = g_ctsu_diag_info.chacb;
    R_CTSU->CTSUCHTRC0 = 0;
    R_CTSU->CTSUCHTRC1 = 0;
    R_CTSU->CTSUCHTRC2 = 0;
    R_CTSU->CTSUCHTRC3 = 0;
    R_CTSU->CTSUCHTRC4 = 0;

    R_CTSU->CTSUCRA_b.CSW = 0;
    R_CTSU->CTSUCRA_b.PON = 0;

    /* TSCAP discharge process */
    g_ctsu_tscap_pin_cfg_data.pin_cfg =
        ((uint32_t) IOPORT_CFG_PORT_DIRECTION_OUTPUT | (uint32_t) IOPORT_CFG_PORT_OUTPUT_LOW);
    R_IOPORT_Open(&g_ctsu_tscap_ioport_ctrl, &g_ctsu_tscap_pin_cfg);
    R_BSP_SoftwareDelay(10, BSP_DELAY_UNITS_MICROSECONDS);
    g_ctsu_tscap_pin_cfg_data.pin_cfg =
        ((uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_CTSU);
    R_IOPORT_PinsCfg(&g_ctsu_tscap_ioport_ctrl, &g_ctsu_tscap_pin_cfg);
    R_IOPORT_Close(&g_ctsu_tscap_ioport_ctrl);

    R_CTSU->CTSUCRA_b.CSW = 1;
    R_CTSU->CTSUCRA_b.PON = 1;
}

static fsp_err_t ctsu_diag_over_current_result (void)
{
    if (g_ctsu_diag_info.icomp1_value == 0)
    {
        return FSP_ERR_CTSU_DIAG_OVER_CURRENT;
    }

    /* if all checks passed to this point, return success */
    return FSP_SUCCESS;
}

static void ctsu_diag_load_resistance_scan_start (void)
{
    /* CTSU setting */
    R_CTSU->CTSUCRA_b.PUMPON = 1;
    R_CTSU->CTSUCRA_b.CSW    = 1;
    R_CTSU->CTSUCRA_b.PON    = 1;

    R_CTSU->CTSUCRA_b.SDPSEL    = 1;
    R_CTSU->CTSUCRA_b.PCSEL     = 1;
    R_CTSU->CTSUSST             = CTSU_SST_RECOMMEND;
    R_CTSU->CTSUCALIB_b.CCOCLK  = 0;
    R_CTSU->CTSUCALIB_b.SUCLKEN = 0;

    R_CTSU->CTSUCRA_b.MD0  = 1;
    R_CTSU->CTSUCRA_b.MD1  = 0;
    R_CTSU->CTSUCRA_b.MD2  = 0;
    R_CTSU->CTSUMCH_b.MCA0 = 1;
    R_CTSU->CTSUMCH_b.MCA1 = 0;
    R_CTSU->CTSUMCH_b.MCA2 = 0;
    R_CTSU->CTSUMCH_b.MCA3 = 0;
    R_CTSU->CTSUCRA_b.LOAD = 1;

    /* Setting time of measurement */
    g_ctsu_diag_info.ctsuwr.ctsuso = (CTSU_SNUM_RECOMMEND << 10);

    R_CTSU->CTSUCHACA  = 1;
    R_CTSU->CTSUCHACB  = 0;
    R_CTSU->CTSUCHTRC0 = 0;
    R_CTSU->CTSUCHTRC1 = 0;
    R_CTSU->CTSUCHTRC2 = 0;
    R_CTSU->CTSUCHTRC3 = 0;
    R_CTSU->CTSUCHTRC4 = 0;

    R_CTSU->CTSUCALIB_b.TSOC = 1;

    switch (g_ctsu_diag_info.loop_count)
    {
        case 0:
        {
            R_CTSU->CTSUCRA_b.ATUNE1 = 1;
            R_CTSU->CTSUCRA_b.ATUNE2 = 1; // 7.5Kohm 160uA
            break;
        }

        case 1:
        {
            R_CTSU->CTSUCRA_b.ATUNE1 = 0;
            R_CTSU->CTSUCRA_b.ATUNE2 = 0; // 15Kohm 80uA
            break;
        }

        case 2:
        {
            R_CTSU->CTSUCRA_b.ATUNE1 = 1;
            R_CTSU->CTSUCRA_b.ATUNE2 = 0; // 30Kohm 40uA
            break;
        }

        case 3:
        {
            R_CTSU->CTSUCRA_b.ATUNE1 = 0;
            R_CTSU->CTSUCRA_b.ATUNE2 = 1; // 60Kohm 20uA
            break;
        }

        default:
        {
            break;
        }
    }

    R_CTSU->CTSUCRA_b.LOAD = 3;
}

static void ctsu_diag_load_resistance_data_get (void)
{
    g_ctsu_diag_info.load_resistance[g_ctsu_diag_info.loop_count] = (uint16_t) g_ctsu_diag_info.ctsuscnt[0];

    g_ctsu_diag_info.load_resistance[g_ctsu_diag_info.loop_count] =
        (uint16_t) ((((uint32_t) g_ctsu_diag_info.load_resistance[g_ctsu_diag_info.loop_count]) *
                     g_ctsu_diag_info.error_registance[3 - g_ctsu_diag_info.loop_count]) >> (CTSU_SHIFT_AMOUNT));

    ctsu_correction_calc_t calc;
    calc.snum  = CTSU_SNUM_RECOMMEND;
    calc.range = CTSU_RANGE_40UA;
    calc.md    = CTSU_MODE_DIAGNOSIS_SCAN;
    ctsu_correction_calc(&g_ctsu_diag_info.load_resistance[g_ctsu_diag_info.loop_count],
                         g_ctsu_diag_info.load_resistance[g_ctsu_diag_info.loop_count],
                         &calc);
    g_ctsu_diag_info.loop_count++;
}

static fsp_err_t ctsu_diag_load_resistance_result (void)
{
    uint8_t k;

    for (k = 0; k < 4; k++)
    {
        if ((g_ctsu_diag_info.load_resistance[k] > CTSU_CFG_DIAG_LOAD_REISTER_MIN) &&
            (g_ctsu_diag_info.load_resistance[k] < CTSU_CFG_DIAG_LOAD_REISTER_MAX))
        {
        }
        else
        {
            return FSP_ERR_CTSU_DIAG_LOAD_RESISTANCE;
        }
    }

    /* if all checks passed to this point, return success */
    return FSP_SUCCESS;
}

static void ctsu_diag_current_source_scan_start (void)
{
    /* CTSU setting */
    R_CTSU->CTSUCRA_b.PUMPON = 1;
    R_CTSU->CTSUCRA_b.CSW    = 1;
    R_CTSU->CTSUCRA_b.PON    = 1;

    R_CTSU->CTSUCRA_b.SDPSEL    = 1;
    R_CTSU->CTSUCRA_b.PCSEL     = 1;
    R_CTSU->CTSUSST             = CTSU_SST_RECOMMEND;
    R_CTSU->CTSUCALIB_b.CCOCLK  = 0;
    R_CTSU->CTSUCALIB_b.SUCLKEN = 0;

    R_CTSU->CTSUCRA_b.MD0  = 1;
    R_CTSU->CTSUCRA_b.MD1  = 0;
    R_CTSU->CTSUCRA_b.MD2  = 0;
    R_CTSU->CTSUMCH_b.MCA0 = 1;
    R_CTSU->CTSUMCH_b.MCA1 = 0;
    R_CTSU->CTSUMCH_b.MCA2 = 0;
    R_CTSU->CTSUMCH_b.MCA3 = 0;

    R_CTSU->CTSUCHACA  = 1;
    R_CTSU->CTSUCHACB  = 0;
    R_CTSU->CTSUCHTRC0 = 0;
    R_CTSU->CTSUCHTRC1 = 0;
    R_CTSU->CTSUCHTRC2 = 0;
    R_CTSU->CTSUCHTRC3 = 0;
    R_CTSU->CTSUCHTRC4 = 0;

    R_CTSU->CTSUSO = CTSU_DIAG_DAC_INIT_0;
    R_CTSU->CTSUSO = CTSU_DIAG_DAC_INIT_1;
    R_CTSU->CTSUSO = CTSU_DIAG_DAC_INIT_2;
    R_CTSU->CTSUSO = CTSU_DIAG_DAC_INIT_3;

    /* LDO Nch setting (40uAmode) */
    R_CTSU->CTSUCRA_b.LOAD   = 1;
    R_CTSU->CTSUCALIB_b.TSOC = 1;
    R_CTSU->CTSUCRA_b.ATUNE1 = 1;
    R_CTSU->CTSUCRA_b.ATUNE2 = 0;
    R_CTSU->CTSUCRA_b.LOAD   = 3;

    /* DAC initial setting */
    R_CTSU->CTSUCALIB_b.DACMSEL  = 1;
    R_CTSU->CTSUCALIB_b.DACCARRY = 1;

    R_CTSU->CTSUCRA_b.DCMODE = 0;
    R_CTSU->CTSUCRA_b.DCBACK = 0;

    if (15 >= g_ctsu_diag_info.loop_count)
    {
        /* Upper Current source setting (10uA) */
        R_CTSU->CTSUSO = CTSU_DIAG_DAC_INIT_0;
        R_CTSU->CTSUSO = CTSU_DIAG_DAC_INIT_1;

        switch (g_ctsu_diag_info.loop_count)
        {
            case 0:
            {
                R_CTSU->CTSUSO = CTSU_DIAG_DAC_INIT_2 + CTSU_DIAG_DAC_0BIT;
                R_CTSU->CTSUSO = CTSU_DIAG_DAC_INIT_3;

                /* Setting time of measurement */
                g_ctsu_diag_info.ctsuwr.ctsuso = (CTSU_SNUM_RECOMMEND << 10) | CTSU_DIAG_DAC_INIT_3;
                break;
            }

            case 1:
            {
                R_CTSU->CTSUSO                 = CTSU_DIAG_DAC_INIT_2 + CTSU_DIAG_DAC_1BIT;
                R_CTSU->CTSUSO                 = CTSU_DIAG_DAC_INIT_3;
                g_ctsu_diag_info.ctsuwr.ctsuso = (CTSU_SNUM_RECOMMEND << 10) | CTSU_DIAG_DAC_INIT_3;
                break;
            }

            case 2:
            {
                R_CTSU->CTSUSO                 = CTSU_DIAG_DAC_INIT_2 + CTSU_DIAG_DAC_2BIT;
                R_CTSU->CTSUSO                 = CTSU_DIAG_DAC_INIT_3;
                g_ctsu_diag_info.ctsuwr.ctsuso = (CTSU_SNUM_RECOMMEND << 10) | CTSU_DIAG_DAC_INIT_3;
                break;
            }

            case 3:
            {
                R_CTSU->CTSUSO                 = CTSU_DIAG_DAC_INIT_2 + CTSU_DIAG_DAC_3BIT;
                R_CTSU->CTSUSO                 = CTSU_DIAG_DAC_INIT_3;
                g_ctsu_diag_info.ctsuwr.ctsuso = (CTSU_SNUM_RECOMMEND << 10) | CTSU_DIAG_DAC_INIT_3;
                break;
            }

            case 4:
            {
                R_CTSU->CTSUSO                 = CTSU_DIAG_DAC_INIT_2 + CTSU_DIAG_DAC_4BIT;
                R_CTSU->CTSUSO                 = CTSU_DIAG_DAC_INIT_3;
                g_ctsu_diag_info.ctsuwr.ctsuso = (CTSU_SNUM_RECOMMEND << 10) | CTSU_DIAG_DAC_INIT_3;
                break;
            }

            case 5:
            {
                R_CTSU->CTSUSO                 = CTSU_DIAG_DAC_INIT_2 + CTSU_DIAG_DAC_5BIT;
                R_CTSU->CTSUSO                 = CTSU_DIAG_DAC_INIT_3;
                g_ctsu_diag_info.ctsuwr.ctsuso = (CTSU_SNUM_RECOMMEND << 10) | CTSU_DIAG_DAC_INIT_3;
                break;
            }

            case 6:
            {
                R_CTSU->CTSUSO                 = CTSU_DIAG_DAC_INIT_2 + CTSU_DIAG_DAC_6BIT;
                R_CTSU->CTSUSO                 = CTSU_DIAG_DAC_INIT_3;
                g_ctsu_diag_info.ctsuwr.ctsuso = (CTSU_SNUM_RECOMMEND << 10) | CTSU_DIAG_DAC_INIT_3;
                break;
            }

            case 7:
            {
                R_CTSU->CTSUSO                 = CTSU_DIAG_DAC_INIT_2 + CTSU_DIAG_DAC_7BIT;
                R_CTSU->CTSUSO                 = CTSU_DIAG_DAC_INIT_3;
                g_ctsu_diag_info.ctsuwr.ctsuso = (CTSU_SNUM_RECOMMEND << 10) | CTSU_DIAG_DAC_INIT_3;
                break;
            }

            case 8:
            {
                R_CTSU->CTSUSO                 = CTSU_DIAG_DAC_INIT_2;
                R_CTSU->CTSUSO                 = CTSU_DIAG_DAC_INIT_3 + CTSU_DIAG_DAC_0BIT;
                g_ctsu_diag_info.ctsuwr.ctsuso = (CTSU_SNUM_RECOMMEND << 10) |
                                                 (CTSU_DIAG_DAC_INIT_3 + CTSU_DIAG_DAC_0BIT);
                break;
            }

            case 9:
            {
                R_CTSU->CTSUSO                 = CTSU_DIAG_DAC_INIT_2;
                R_CTSU->CTSUSO                 = CTSU_DIAG_DAC_INIT_3 + CTSU_DIAG_DAC_1BIT;
                g_ctsu_diag_info.ctsuwr.ctsuso = (CTSU_SNUM_RECOMMEND << 10) |
                                                 (CTSU_DIAG_DAC_INIT_3 + CTSU_DIAG_DAC_1BIT);
                break;
            }

            case 10:
            {
                R_CTSU->CTSUSO                 = CTSU_DIAG_DAC_INIT_2;
                R_CTSU->CTSUSO                 = CTSU_DIAG_DAC_INIT_3 + CTSU_DIAG_DAC_2BIT;
                g_ctsu_diag_info.ctsuwr.ctsuso = (CTSU_SNUM_RECOMMEND << 10) |
                                                 (CTSU_DIAG_DAC_INIT_3 + CTSU_DIAG_DAC_2BIT);
                break;
            }

            case 11:
            {
                R_CTSU->CTSUSO                 = CTSU_DIAG_DAC_INIT_2;
                R_CTSU->CTSUSO                 = CTSU_DIAG_DAC_INIT_3 + CTSU_DIAG_DAC_3BIT;
                g_ctsu_diag_info.ctsuwr.ctsuso = (CTSU_SNUM_RECOMMEND << 10) |
                                                 (CTSU_DIAG_DAC_INIT_3 + CTSU_DIAG_DAC_3BIT);
                break;
            }

            case 12:
            {
                R_CTSU->CTSUSO                 = CTSU_DIAG_DAC_INIT_2;
                R_CTSU->CTSUSO                 = CTSU_DIAG_DAC_INIT_3 + CTSU_DIAG_DAC_4BIT;
                g_ctsu_diag_info.ctsuwr.ctsuso = (CTSU_SNUM_RECOMMEND << 10) |
                                                 (CTSU_DIAG_DAC_INIT_3 + CTSU_DIAG_DAC_4BIT);
                break;
            }

            case 13:
            {
                R_CTSU->CTSUSO                 = CTSU_DIAG_DAC_INIT_2;
                R_CTSU->CTSUSO                 = CTSU_DIAG_DAC_INIT_3 + CTSU_DIAG_DAC_5BIT;
                g_ctsu_diag_info.ctsuwr.ctsuso = (CTSU_SNUM_RECOMMEND << 10) |
                                                 (CTSU_DIAG_DAC_INIT_3 + CTSU_DIAG_DAC_5BIT);
                break;
            }

            case 14:
            {
                R_CTSU->CTSUSO                 = CTSU_DIAG_DAC_INIT_2;
                R_CTSU->CTSUSO                 = CTSU_DIAG_DAC_INIT_3 + CTSU_DIAG_DAC_6BIT;
                g_ctsu_diag_info.ctsuwr.ctsuso = (CTSU_SNUM_RECOMMEND << 10) |
                                                 (CTSU_DIAG_DAC_INIT_3 + CTSU_DIAG_DAC_6BIT);
                break;
            }

            case 15:
            {
                R_CTSU->CTSUSO                 = CTSU_DIAG_DAC_INIT_2;
                R_CTSU->CTSUSO                 = CTSU_DIAG_DAC_INIT_3 + CTSU_DIAG_DAC_7BIT;
                g_ctsu_diag_info.ctsuwr.ctsuso = (CTSU_SNUM_RECOMMEND << 10) |
                                                 (CTSU_DIAG_DAC_INIT_3 + CTSU_DIAG_DAC_7BIT);
                break;
            }
        }
    }

    if (16 <= g_ctsu_diag_info.loop_count)
    {
        /* Lower Current source setting (10uA) */
        switch (g_ctsu_diag_info.loop_count)
        {
            case 16:
            {
                R_CTSU->CTSUSO = CTSU_DIAG_DAC_DATA_MAX_0;
                R_CTSU->CTSUSO = CTSU_DIAG_DAC_INIT_1;
                break;
            }

            case 17:
            {
                R_CTSU->CTSUSO = CTSU_DIAG_DAC_DATA_MAX_0 - CTSU_DIAG_DAC_0BIT;
                R_CTSU->CTSUSO = CTSU_DIAG_DAC_INIT_1 + CTSU_DIAG_DAC_0BIT;
                break;
            }

            case 18:
            {
                R_CTSU->CTSUSO = CTSU_DIAG_DAC_DATA_MAX_0 - (CTSU_DIAG_DAC_0BIT + CTSU_DIAG_DAC_1BIT);
                R_CTSU->CTSUSO = CTSU_DIAG_DAC_INIT_1 + (CTSU_DIAG_DAC_0BIT + CTSU_DIAG_DAC_1BIT);
                break;
            }

            case 19:
            {
                R_CTSU->CTSUSO = CTSU_DIAG_DAC_DATA_MAX_0 - (CTSU_DIAG_DAC_1BIT + CTSU_DIAG_DAC_2BIT);
                R_CTSU->CTSUSO = CTSU_DIAG_DAC_INIT_1 + (CTSU_DIAG_DAC_0BIT + CTSU_DIAG_DAC_1BIT);
                break;
            }

            case 20:
            {
                R_CTSU->CTSUSO = CTSU_DIAG_DAC_DATA_MAX_0 - (CTSU_DIAG_DAC_2BIT + CTSU_DIAG_DAC_3BIT);
                R_CTSU->CTSUSO = CTSU_DIAG_DAC_INIT_1 + (CTSU_DIAG_DAC_0BIT + CTSU_DIAG_DAC_1BIT);
                break;
            }

            case 21:
            {
                R_CTSU->CTSUSO = CTSU_DIAG_DAC_DATA_MAX_0 - (CTSU_DIAG_DAC_3BIT + CTSU_DIAG_DAC_4BIT);
                R_CTSU->CTSUSO = CTSU_DIAG_DAC_INIT_1 + (CTSU_DIAG_DAC_0BIT + CTSU_DIAG_DAC_1BIT);
                break;
            }

            case 22:
            {
                R_CTSU->CTSUSO = CTSU_DIAG_DAC_DATA_MAX_0 - (CTSU_DIAG_DAC_4BIT + CTSU_DIAG_DAC_5BIT);
                R_CTSU->CTSUSO = CTSU_DIAG_DAC_INIT_1 + (CTSU_DIAG_DAC_0BIT + CTSU_DIAG_DAC_1BIT);
                break;
            }

            case 23:
            {
                R_CTSU->CTSUSO = CTSU_DIAG_DAC_DATA_MAX_0 - (CTSU_DIAG_DAC_5BIT + CTSU_DIAG_DAC_6BIT);
                R_CTSU->CTSUSO = CTSU_DIAG_DAC_INIT_1 + (CTSU_DIAG_DAC_0BIT + CTSU_DIAG_DAC_1BIT);
                break;
            }

            case 24:
            {
                R_CTSU->CTSUSO = CTSU_DIAG_DAC_DATA_MAX_0 - (CTSU_DIAG_DAC_6BIT + CTSU_DIAG_DAC_7BIT);
                R_CTSU->CTSUSO = CTSU_DIAG_DAC_INIT_1 + (CTSU_DIAG_DAC_0BIT + CTSU_DIAG_DAC_1BIT);
                break;
            }

            case 25:
            {
                R_CTSU->CTSUSO = CTSU_DIAG_DAC_DATA_MAX_0 - CTSU_DIAG_DAC_7BIT;
                R_CTSU->CTSUSO = CTSU_DIAG_DAC_INIT_1 + CTSU_DIAG_DAC_1BIT;
                break;
            }
        }

        R_CTSU->CTSUSO                 = CTSU_DIAG_DAC_INIT_2;
        R_CTSU->CTSUSO                 = CTSU_DIAG_DAC_INIT_3;
        g_ctsu_diag_info.ctsuwr.ctsuso = (CTSU_SNUM_RECOMMEND << 10) | CTSU_DIAG_DAC_INIT_3;
    }
}

static void ctsu_diag_current_source_data_get (void)
{
    g_ctsu_diag_info.current_source[g_ctsu_diag_info.loop_count] = (uint16_t) g_ctsu_diag_info.ctsuscnt[0];

    g_ctsu_diag_info.current_source[g_ctsu_diag_info.loop_count] =
        (uint16_t) ((((uint32_t) g_ctsu_diag_info.current_source[g_ctsu_diag_info.loop_count]) *
                     g_ctsu_diag_info.error_registance[2]) >> (CTSU_SHIFT_AMOUNT));

    ctsu_correction_calc_t calc;
    calc.snum  = CTSU_SNUM_RECOMMEND;
    calc.range = CTSU_RANGE_40UA;
    calc.md    = CTSU_MODE_DIAGNOSIS_SCAN;
    ctsu_correction_calc(&g_ctsu_diag_info.current_source[g_ctsu_diag_info.loop_count],
                         g_ctsu_diag_info.current_source[g_ctsu_diag_info.loop_count], &calc);
    g_ctsu_diag_info.loop_count++;
}

static fsp_err_t ctsu_diag_current_source_result (void)
{
    uint8_t  k;
    uint16_t current_source_diff;

    for (k = 0; k < (CTSU_DIAG_HIGH_CURRENT_SOURCE + CTSU_DIAG_LOW_CURRENT_SOURCE); k++)
    {
        current_source_diff = (uint16_t) (g_ctsu_diag_info.load_resistance[2] - g_ctsu_diag_info.current_source[k]);
        if ((current_source_diff < CTSU_CFG_DIAG_CURRENT_SOURCE_DIFF_MAX) &&
            (current_source_diff > CTSU_CFG_DIAG_CURRENT_SOURCE_DIFF_MIN))
        {
        }
        else
        {
            return FSP_ERR_CTSU_DIAG_CURRENT_SOURCE;
        }
    }

    /* if all checks passed to this point, return success */
    return FSP_SUCCESS;
}

static void ctsu_diag_cco_gain_scan_start (void)
{
    uint16_t read_reg;

    /* CTSU Setting */
    R_CTSU->CTSUCRA_b.MD0    = 0;
    R_CTSU->CTSUCRA_b.MD1    = 0;
    R_CTSU->CTSUCRA_b.MD2    = 0;
    R_CTSU->CTSUCRA_b.LOAD   = 1;
    R_CTSU->CTSUCRA_b.PON    = 1;
    R_CTSU->CTSUCRA_b.CSW    = 1;
    R_CTSU->CTSUCRA_b.PUMPON = 1;

    R_CTSU->CTSUMCH_b.MCA0 = 1;
    R_CTSU->CTSUMCH_b.MCA1 = 0;
    R_CTSU->CTSUMCH_b.MCA2 = 0;
    R_CTSU->CTSUMCH_b.MCA3 = 0;

    R_CTSU->CTSUCRB_b.SSMOD = 4;
    R_CTSU->CTSUCRB_b.SSCNT = 0;
    R_CTSU->CTSUCRB_b.SST   = CTSU_SST_RECOMMEND;

    R_CTSU->CTSUCRA_b.PCSEL  = 1;
    R_CTSU->CTSUCRA_b.SDPSEL = 1;

    R_CTSU->CTSUCALIB           = 0;
    R_CTSU->CTSUCALIB_b.SUCARRY = 0;

    if (CTSU_DIAG_SENSCLK == g_ctsu_diag_info.state)
    {
        R_CTSU->CTSUCALIB_b.CCOCALIB = 1;
    }

    if (CTSU_DIAG_SUCLK == g_ctsu_diag_info.state)
    {
        R_CTSU->CTSUCALIB_b.CCOCALIB = 0;
    }

    R_CTSU->CTSUCALIB_b.CCOCLK = 0;

    R_CTSU->CTSUCHACA  = 1;
    R_CTSU->CTSUCHACB  = 0;
    R_CTSU->CTSUCHTRC0 = 0;
    R_CTSU->CTSUCHTRC1 = 0;
    R_CTSU->CTSUCHTRC2 = 0;
    R_CTSU->CTSUCHTRC3 = 0;
    R_CTSU->CTSUCHTRC4 = 0;

    /* Setting time of measurement */
    g_ctsu_diag_info.ctsuwr.ctsuso = (CTSU_SNUM_RECOMMEND << 10);

    R_CTSU->CTSUMCH_b.MCH0 = 0;

    if (g_ctsu_diag_info.loop_count < 8)
    {
        read_reg = R_CTSU->CTSUSUCLK0;
        read_reg =
            (uint16_t) ((read_reg & CTSU_DIAG_SUCLK0_REG1) |
                        (0x1f + (g_ctsu_diag_info.loop_count * CTSU_DIAG_SUCLK0_REG2)));
        R_CTSU->CTSUSUCLK0 = read_reg;
    }
    else if ((8 <= g_ctsu_diag_info.loop_count) && (g_ctsu_diag_info.loop_count < 11))
    {
        read_reg = R_CTSU->CTSUSUCLK0;
        read_reg =
            (uint16_t) ((read_reg & CTSU_DIAG_SUCLK0_REG1) | (0x1f + (7 * CTSU_DIAG_SUCLK0_REG2)));
        R_CTSU->CTSUSUCLK0 = read_reg;

        if (8 == g_ctsu_diag_info.loop_count)
        {
            R_CTSU->CTSUCRB_b.SSCNT = 0;
        }
        else if (9 == g_ctsu_diag_info.loop_count)
        {
            R_CTSU->CTSUCRB_b.SSCNT = 1;
        }
        else if (10 == g_ctsu_diag_info.loop_count)
        {
            R_CTSU->CTSUCRB_b.SSCNT = 2;
        }
        else
        {
        }

        R_CTSU->CTSUCALIB_b.SUCARRY = 0;
        if (CTSU_DIAG_SENSCLK == g_ctsu_diag_info.state)
        {
            R_CTSU->CTSUCALIB_b.CCOCALIB = 1;
        }

        if (CTSU_DIAG_SUCLK == g_ctsu_diag_info.state)
        {
            R_CTSU->CTSUCALIB_b.CCOCALIB = 0;
        }

        R_CTSU->CTSUCALIB_b.CCOCLK = 0;
        R_CTSU->CTSUCRB_b.SSMOD    = 1;
        R_CTSU->CTSUCRB_b.SST      = CTSU_SST_RECOMMEND_CURRENT;
        if (8 == g_ctsu_diag_info.loop_count)
        {
            R_CTSU->CTSUCRB_b.SSCNT = 1;
        }
        else if (9 == g_ctsu_diag_info.loop_count)
        {
            R_CTSU->CTSUCRB_b.SSCNT = 2;
        }
        else if (10 == g_ctsu_diag_info.loop_count)
        {
            R_CTSU->CTSUCRB_b.SSCNT = 3;
        }
        else
        {
        }
    }
    else if (11 == g_ctsu_diag_info.loop_count)
    {
        read_reg = R_CTSU->CTSUSUCLK0;
        read_reg =
            (uint16_t) ((read_reg & CTSU_DIAG_SUCLK0_REG1) | (0x1f + (7 * CTSU_DIAG_SUCLK0_REG2)));
        R_CTSU->CTSUSUCLK0 = read_reg;

        R_CTSU->CTSUCRB_b.SSCNT     = 2;
        R_CTSU->CTSUCALIB_b.SUCARRY = 1;
        if (CTSU_DIAG_SENSCLK == g_ctsu_diag_info.state)
        {
            R_CTSU->CTSUCALIB_b.CCOCALIB = 1;
        }

        if (CTSU_DIAG_SUCLK == g_ctsu_diag_info.state)
        {
            R_CTSU->CTSUCALIB_b.CCOCALIB = 0;
        }

        R_CTSU->CTSUCALIB_b.CCOCLK = 0;
        R_CTSU->CTSUCRB_b.SSMOD    = 1;
        R_CTSU->CTSUCRB_b.SST      = CTSU_SST_RECOMMEND_CURRENT;
        R_CTSU->CTSUCRB_b.SSCNT    = 3;
    }
    else
    {
    }
}

static void ctsu_diag_cco_gain_data_get (void)
{
    if (CTSU_DIAG_SENSCLK == g_ctsu_diag_info.state)
    {
        g_ctsu_diag_info.sensclk_cnt[g_ctsu_diag_info.loop_count] = (uint16_t) g_ctsu_diag_info.ctsuscnt[0];
    }

    if (CTSU_DIAG_SUCLK == g_ctsu_diag_info.state)
    {
        g_ctsu_diag_info.suclk_cnt[g_ctsu_diag_info.loop_count] = (uint16_t) (g_ctsu_diag_info.ctsuscnt[0] >> 16);
    }

    g_ctsu_diag_info.loop_count++;
}

static fsp_err_t ctsu_diag_cco_gain_result (void)
{
    uint32_t          k;
    volatile uint16_t cco_gain_data;
    uint16_t          cco_gain_data_pre;
    uint16_t          cco_gain_diff;
    uint16_t          cco_gain_max;
    uint16_t          cco_gain_min;
    uint16_t          cco_gain_diff_max;
    uint16_t          cco_gain_diff_min;

    /* read counter data */
    for (k = 0; k < CTSU_CORRECTION_POINT_NUM; k++)
    {
        if (CTSU_DIAG_SENSCLK == g_ctsu_diag_info.state)
        {
            cco_gain_data = g_ctsu_diag_info.sensclk_cnt[k];
        }

        if (CTSU_DIAG_SUCLK == g_ctsu_diag_info.state)
        {
            cco_gain_data = g_ctsu_diag_info.suclk_cnt[k];
        }

        cco_gain_max = cco_gain_table[k][1];
        cco_gain_min = cco_gain_table[k][0];

        /* check measurement result */
        if ((cco_gain_data <= cco_gain_max) && (cco_gain_data >= cco_gain_min))
        {
        }
        else
        {
            if (CTSU_DIAG_SENSCLK == g_ctsu_diag_info.state)
            {
                return FSP_ERR_CTSU_DIAG_SENSCLK_GAIN;
            }

            if (CTSU_DIAG_SUCLK == g_ctsu_diag_info.state)
            {
                return FSP_ERR_CTSU_DIAG_SUCLK_GAIN;
            }
        }

        if (0 < k)
        {
            cco_gain_diff_max = cco_gain_diff_table[k - 1][1];
            cco_gain_diff_min = cco_gain_diff_table[k - 1][0];

            if (cco_gain_data > cco_gain_data_pre)
            {
                cco_gain_diff = (uint16_t) (cco_gain_data - cco_gain_data_pre);
            }
            else
            {
                cco_gain_diff = (uint16_t) (cco_gain_data_pre - cco_gain_data);
            }

            /* check measurement result */
            if ((cco_gain_diff > cco_gain_diff_max) || (cco_gain_diff < cco_gain_diff_min))
            {
                if (CTSU_DIAG_SENSCLK == g_ctsu_diag_info.state)
                {
                    return FSP_ERR_CTSU_DIAG_SENSCLK_GAIN;
                }

                if (CTSU_DIAG_SUCLK == g_ctsu_diag_info.state)
                {
                    return FSP_ERR_CTSU_DIAG_SUCLK_GAIN;
                }
            }
        }

        cco_gain_data_pre = cco_gain_data;
    }

    /* if all checks passed to this point, return success */
    return FSP_SUCCESS;
}

static void ctsu_diag_clock_recovery_scan_start (void)
{
    R_CTSU->CTSUCRA              = g_ctsu_diag_reg.ctsucra;
    R_CTSU->CTSUCRA_b.MD0        = 1;
    R_CTSU->CTSUCRA_b.MD1        = 0;
    R_CTSU->CTSUCRA_b.MD2        = 0;
    R_CTSU->CTSUMCH              = g_ctsu_diag_reg.ctsumch;
    R_CTSU->CTSUCRB              = g_ctsu_diag_reg.ctsucrb;
    R_CTSU->CTSUCRA_b.LOAD       = 1;
    R_CTSU->CTSUCRB_b.SSCNT      = 1;
    R_CTSU->CTSUCALIB_b.SUCARRY  = 0;
    R_CTSU->CTSUCALIB_b.CCOCALIB = 0;
    R_CTSU->CTSUCALIB_b.CCOCLK   = 1;
    R_CTSU->CTSUCALIB_b.TSOC     = 0;
    R_CTSU->CTSUCALIB_b.SUCLKEN  = 1;

    R_CTSU->CTSUCRA_b.SDPSEL = 0;
    R_CTSU->CTSUSUCLKA       = g_ctsu_diag_reg.ctsusuclka;
    R_CTSU->CTSUSUCLKB       = g_ctsu_diag_reg.ctsusuclkb;
    R_CTSU->CTSUCRA_b.SDPSEL = 1;

    R_CTSU->CTSUMCH_b.MCA0 = 1;
    R_CTSU->CTSUMCH_b.MCA1 = 1;
    R_CTSU->CTSUMCH_b.MCA2 = 1;
    R_CTSU->CTSUMCH_b.MCA3 = 0;

    R_CTSU->CTSUCHACA = g_ctsu_diag_info.chaca;
    R_CTSU->CTSUCHACB = g_ctsu_diag_info.chacb;

    R_CTSU->CTSUCHTRC0 = 0;
    R_CTSU->CTSUCHTRC1 = 0;
    R_CTSU->CTSUCHTRC2 = 0;
    R_CTSU->CTSUCHTRC3 = 0;
    R_CTSU->CTSUCHTRC4 = 0;

    /* Setting time of measurement */

    g_ctsu_diag_info.ctsuwr.ctsuso = (uint32_t) ((0xf << 24) | (CTSU_SNUM_RECOMMEND << 10));
}

static void ctsu_diag_clock_recovery_data_get (void)
{
    uint8_t i;
    for (i = 0; i < 3; i++)
    {
        g_ctsu_diag_info.suclk_count_clk_recv[i] = (uint16_t) (g_ctsu_diag_info.ctsuscnt[i] >> 16);
    }
}

static fsp_err_t ctsu_diag_clock_recovery_result (void)
{
    uint8_t         i;
    uint32_t        suclk[3];
    static uint32_t suclk_cnt[3];

    suclk[0] = (CTSU_DIAG_STCLK_FREQ * (CTSU_CFG_SUMULTI0 + 1));
    suclk[1] = (CTSU_DIAG_STCLK_FREQ * (CTSU_CFG_SUMULTI1 + 1));
    suclk[2] = (CTSU_DIAG_STCLK_FREQ * (CTSU_CFG_SUMULTI2 + 1));

    for (i = 0; i < 3; i++)
    {
        suclk_cnt[i % 3] = ((suclk[i % 3] * (CTSU_SNUM_RECOMMEND + 1)) / CTSU_DIAG_STCLK_FREQ) * 8 * 2;

        /* suclk check */
        if ((suclk_cnt[i % 3] + CTSU_CFG_DIAG_CLOCK_RECOV_RANGE) < g_ctsu_diag_info.suclk_count_clk_recv[i])
        {
            return FSP_ERR_CTSU_DIAG_CLOCK_RECOVERY;
        }

        if ((suclk_cnt[i % 3] - CTSU_CFG_DIAG_CLOCK_RECOV_RANGE) > g_ctsu_diag_info.suclk_count_clk_recv[i])
        {
            return FSP_ERR_CTSU_DIAG_CLOCK_RECOVERY;
        }
    }

    /* if all checks passed to this point, return success */
    return FSP_SUCCESS;
}

  #if (CTSU_CFG_NUM_CFC != 0)
static void ctsu_diag_cfc_gain_scan_start (void)
{
    /* CTSU Setting */
    R_CTSU->CTSUCRA_b.MD0    = 1;
    R_CTSU->CTSUCRA_b.MD1    = 0;
    R_CTSU->CTSUCRA_b.MD2    = 1;
    R_CTSU->CTSUMCH_b.MCA0   = 1;
    R_CTSU->CTSUMCH_b.MCA1   = 0;
    R_CTSU->CTSUMCH_b.MCA2   = 0;
    R_CTSU->CTSUMCH_b.MCA3   = 0;
    R_CTSU->CTSUCRA_b.LOAD   = 1;
    R_CTSU->CTSUCRA_b.CFCON  = 1;
    R_CTSU->CTSUCRA_b.PUMPON = 1;
    R_CTSU->CTSUCRA_b.TXVSEL = 1;

    R_CTSU->CTSUCRB_b.SSMOD = 0;
    R_CTSU->CTSUCRB_b.SSCNT = 0;
    R_CTSU->CTSUCRB_b.SST   = 0x1F;

    R_CTSU->CTSUCRA_b.PCSEL  = 1;
    R_CTSU->CTSUCRA_b.SDPSEL = 1;

    R_CTSU->CTSUCALIB            = 0;
    R_CTSU->CTSUCALIB_b.SUCARRY  = 0;
    R_CTSU->CTSUCALIB_b.CCOCALIB = 0;
    R_CTSU->CTSUCALIB_b.CCOCLK   = 0;
    R_CTSU->CTSUCALIB_b.CFCMODE  = 1;
    R_CTSU->CTSUCALIB_b.CFCRDMD  = 1;

    if (CTSU_DIAG_CHACA_TSMAX > g_ctsu_corrcfc_info.ts_table[0])
    {
        R_CTSU->CTSUCHACA = (uint32_t) (1 << g_ctsu_corrcfc_info.ts_table[0]);
        R_CTSU->CTSUCHACB = 0;
    }
    else
    {
        R_CTSU->CTSUCHACA = 0;
        R_CTSU->CTSUCHACB = (uint32_t) (1 << (g_ctsu_corrcfc_info.ts_table[0] - CTSU_DIAG_CHACA_TSMAX));
    }

    R_CTSU->CTSUCHTRC0 = 0;
    R_CTSU->CTSUCHTRC1 = 0;
    R_CTSU->CTSUCHTRC2 = 0;
    R_CTSU->CTSUCHTRC3 = 0;
    R_CTSU->CTSUCHTRC4 = 0;

    R_CTSU->CTSUMCH_b.MCH0 = 0;

    R_CTSU->CTSUCRA_b.SDPSEL = 0;
    R_CTSU->CTSUSUCLK0       =
        (uint16_t) (((g_ctsu_diag_info.loop_count + CTSU_CORRCFC_CENTER_POINT) * CTSU_CORRECTION_SUMULTI) - 1);
    R_CTSU->CTSUCRA_b.SDPSEL = 1;

    g_ctsu_diag_info.ctsuwr.ctsuso = (uint32_t) (CTSU_SNUM_RECOMMEND << 10);
}

static void ctsu_diag_cfc_gain_data_get (void)
{
    g_ctsu_diag_info.cfc_cnt[g_ctsu_diag_info.loop_count] = (uint16_t) g_ctsu_diag_info.ctsuscnt[0];

    g_ctsu_diag_info.loop_count++;
}

static fsp_err_t ctsu_diag_cfc_gain_result (void)
{
    uint8_t k;

    for (k = 0; k < (CTSU_CORRCFC_POINT_NUM - 1); k++)
    {
        if (g_ctsu_diag_info.cfc_cnt[k + 1] > g_ctsu_diag_info.cfc_cnt[k])
        {
            /* PASS */
        }
        else
        {

            /* FAIL */
            return FSP_ERR_CTSU_DIAG_CFC_GAIN;
        }
    }

    return FSP_SUCCESS;
}

  #endif
 #endif
#endif
