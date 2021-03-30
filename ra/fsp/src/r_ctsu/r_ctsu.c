/***********************************************************************************************************************
 * Copyright [2020-2021] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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
#define CTSU_COUNT_MAX                       (0xFFFF)
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
#define CTSU_TUNING_OT_COUNT                 (25)

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
  #define CTSU_CORRECTION_1ST_STD_VAL        (40960UL)       // ICOG = 66%
  #define CTSU_CORRECTION_2ND_STD_VAL        (24824)         // ICOG = 40%, (x = 40960 * 40 / 66)
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
    int32_t  offset_error[CTSU_CFG_NUM_SUMULTI];
    bool     judge_disable;
} ctsu_correction_multi_t;

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

#endif
static void ctsu_initial_offset_tuning(ctsu_instance_ctrl_t * const p_instance_ctrl);
static void ctsu_moving_average(uint16_t * p_average, uint16_t new_data, uint16_t average_num);
void        ctsu_write_isr(void);
void        ctsu_read_isr(void);
void        ctsu_end_isr(void);
static void ctsu_correction_process(ctsu_instance_ctrl_t * const p_instance_ctrl);
static void ctsu_correction_measurement(ctsu_instance_ctrl_t * const p_instance_ctrl, uint16_t * data);
static void ctsu_correction_calc(uint16_t * correction_data, uint16_t raw_data, ctsu_correction_calc_t * p_calc);
static void ctsu_correction_exec(ctsu_instance_ctrl_t * const p_instance_ctrl);

#if (BSP_FEATURE_CTSU_VERSION == 2)
static void ctsu_correction_multi(ctsu_correction_multi_t * p_multi, uint16_t * p_pri, uint16_t * p_snd);

 #if (CTSU_CFG_TEMP_CORRECTION_SUPPORT == 1)
static void ctsu_correction_scan_start(void);
static void ctsu_correction_data_get(ctsu_instance_ctrl_t * const p_instance_ctrl, uint16_t * p_data);

  #if (CTSU_CFG_CALIB_RTRIM_SUPPORT == 1)
static void ctsu_correction_calib_rtrim(ctsu_instance_ctrl_t * const p_instance_ctrl, uint16_t * p_data);

  #endif
 #endif
 #if (CTSU_CFG_NUM_CFC != 0)
static void ctsu_corrcfc_process(ctsu_instance_ctrl_t * const p_instance_ctrl);
static void ctsu_corrcfc_measurement(ctsu_instance_ctrl_t * const p_instance_ctrl, uint16_t * data, uint8_t point_num);

 #endif
#endif

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/** Version data structure used by error logger macro. */
static const fsp_version_t g_ctsu_version =
{
    .api_version_minor  = CTSU_API_VERSION_MINOR,
    .api_version_major  = CTSU_API_VERSION_MAJOR,
    .code_version_major = CTSU_CODE_VERSION_MAJOR,
    .code_version_minor = CTSU_CODE_VERSION_MINOR
};
static uint16_t      g_ctsu_element_index = 0;
static uint8_t       g_ctsu_tuning_count[CTSU_CFG_NUM_SELF_ELEMENTS + CTSU_CFG_NUM_MUTUAL_ELEMENTS];
static int32_t       g_ctsu_tuning_diff[CTSU_CFG_NUM_SELF_ELEMENTS + CTSU_CFG_NUM_MUTUAL_ELEMENTS];
static ctsu_ctsuwr_t g_ctsu_ctsuwr[(CTSU_CFG_NUM_SELF_ELEMENTS + CTSU_CFG_NUM_MUTUAL_ELEMENTS) * CTSU_CFG_NUM_SUMULTI];
#if (CTSU_CFG_NUM_SELF_ELEMENTS != 0)
static uint16_t        g_ctsu_self_element_index = 0;
static ctsu_self_buf_t g_ctsu_self_raw[CTSU_CFG_NUM_SELF_ELEMENTS * CTSU_CFG_NUM_SUMULTI];
static uint16_t        g_ctsu_self_data[CTSU_CFG_NUM_SELF_ELEMENTS * CTSU_CFG_NUM_SUMULTI];
#endif
#if (CTSU_CFG_NUM_MUTUAL_ELEMENTS != 0)
static uint16_t          g_ctsu_mutual_element_index = 0;
static ctsu_mutual_buf_t g_ctsu_mutual_raw[CTSU_CFG_NUM_MUTUAL_ELEMENTS * CTSU_MUTUAL_BUF_SIZE];
static uint16_t          g_ctsu_mutual_pri_data[CTSU_CFG_NUM_MUTUAL_ELEMENTS * CTSU_CFG_NUM_SUMULTI];
static uint16_t          g_ctsu_mutual_snd_data[CTSU_CFG_NUM_MUTUAL_ELEMENTS * CTSU_CFG_NUM_SUMULTI];
#endif
static ctsu_correction_info_t g_ctsu_correction_info;
#if (BSP_FEATURE_CTSU_VERSION == 2)
 #if (CTSU_CFG_NUM_CFC != 0)
static ctsu_corrcfc_info_t g_ctsu_corrcfc_info;
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

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/
const ctsu_api_t g_ctsu_on_ctsu =
{
    .open        = R_CTSU_Open,
    .scanStart   = R_CTSU_ScanStart,
    .dataGet     = R_CTSU_DataGet,
    .close       = R_CTSU_Close,
    .callbackSet = R_CTSU_CallbackSet,
    .versionGet  = R_CTSU_VersionGet,
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
        p_instance_ctrl->p_self_data  = &g_ctsu_self_data[g_ctsu_self_element_index * CTSU_CFG_NUM_SUMULTI];
        p_instance_ctrl->num_elements = p_cfg->num_rx;
        g_ctsu_self_element_index     = (uint8_t) (g_ctsu_self_element_index + p_instance_ctrl->num_elements);
    }
#endif
#if (CTSU_CFG_NUM_MUTUAL_ELEMENTS != 0)
    if (CTSU_MODE_MUTUAL_FULL_SCAN == (CTSU_MODE_MUTUAL_FULL_SCAN & p_cfg->md))
    {
        p_instance_ctrl->p_mutual_raw      = &g_ctsu_mutual_raw[g_ctsu_mutual_element_index * CTSU_MUTUAL_BUF_SIZE];
        p_instance_ctrl->p_mutual_pri_data =
            &g_ctsu_mutual_pri_data[g_ctsu_mutual_element_index * CTSU_CFG_NUM_SUMULTI];
        p_instance_ctrl->p_mutual_snd_data =
            &g_ctsu_mutual_snd_data[g_ctsu_mutual_element_index * CTSU_CFG_NUM_SUMULTI];
        p_instance_ctrl->num_elements = (uint8_t) (p_cfg->num_rx * p_cfg->num_tx);
        g_ctsu_mutual_element_index   = (uint8_t) (g_ctsu_mutual_element_index + p_instance_ctrl->num_elements);
    }
#endif
    p_instance_ctrl->p_tuning_count = &g_ctsu_tuning_count[g_ctsu_element_index];
    p_instance_ctrl->p_tuning_diff  = &g_ctsu_tuning_diff[g_ctsu_element_index];
    p_instance_ctrl->p_ctsuwr       = &g_ctsu_ctsuwr[g_ctsu_element_index * CTSU_CFG_NUM_SUMULTI];
    g_ctsu_element_index            = (uint8_t) (g_ctsu_element_index + p_instance_ctrl->num_elements);

    /* Set Value */
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
        p_instance_ctrl->p_tuning_count[element_id] = 0;
        p_instance_ctrl->p_tuning_diff[element_id]  = 0;
        element_cfgs = (p_cfg->p_elements + element_id);
#if (BSP_FEATURE_CTSU_VERSION == 2)
        if (CTSU_MODE_CURRENT_SCAN == p_cfg->md)
        {
            /* Current scan does not run multiple frequency */
            p_instance_ctrl->p_ctsuwr[element_id].ctsuso =
                (uint32_t) ((element_cfgs->sdpa << 24) | (element_cfgs->snum << 10) | element_cfgs->so);
        }
        else
        {
            if (CTSU_MODE_MUTUAL_CFC_SCAN != p_cfg->md)
            {
                p_instance_ctrl->p_ctsuwr[element_id * CTSU_CFG_NUM_SUMULTI].ctsuso =
                    (uint32_t) ((element_cfgs->sdpa << 24) | (element_cfgs->snum << 10) | element_cfgs->so);
            }

 #if (CTSU_CFG_NUM_CFC != 0)
            else
            {
                /* CFC scan does not use CTSUSO */
                p_instance_ctrl->p_ctsuwr[element_id * CTSU_CFG_NUM_SUMULTI].ctsuso =
                    (uint32_t) ((element_cfgs->sdpa << 24) | (element_cfgs->snum << 10));
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

    p_instance_ctrl->p_correction_info = &g_ctsu_correction_info;
    p_instance_ctrl->rd_index          = 0;
    p_instance_ctrl->wr_index          = 0;
    p_instance_ctrl->state             = CTSU_STATE_IDLE;

    p_instance_ctrl->p_callback        = p_cfg->p_callback;
    p_instance_ctrl->p_context         = p_cfg->p_context;
    p_instance_ctrl->p_callback_memory = NULL;

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
    if (CTSU_CAP_SOFTWARE == p_instance_ctrl->p_ctsu_cfg->cap)
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

    if (CTSU_CAP_SOFTWARE == p_instance_ctrl->p_ctsu_cfg->cap)
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
    if (CTSU_MODE_CORRECTION_SCAN != p_instance_ctrl->p_ctsu_cfg->md)
    {
        txvsel =
            (uint8_t) ((p_instance_ctrl->p_ctsu_cfg->txvsel2 << 6) | (p_instance_ctrl->p_ctsu_cfg->txvsel << 7));
        temp            = (uint8_t) (R_CTSU->CTSUCR0 & ~(CTSU_CR0_MODIFY_BIT));
        R_CTSU->CTSUCR0 = (uint8_t) (temp | (txvsel & CTSU_CR0_MODIFY_BIT));                   // TXVSEL
        temp            = (uint8_t) (R_CTSU->CTSUCR1 & ~(CTSU_CR1_MODIFY_BIT));
        R_CTSU->CTSUCR1 = (uint8_t) (temp | (p_instance_ctrl->ctsucr1 & CTSU_CR1_MODIFY_BIT)); // MD1, MD0, ATUNE1
        temp            = (uint8_t) (R_CTSU->CTSUCR2 & ~(CTSU_CR2_MODIFY_BIT));
        R_CTSU->CTSUCR2 = (uint8_t) (temp | (p_instance_ctrl->ctsucr2 & CTSU_CR2_MODIFY_BIT)); // POSEL, ATUNE2, MD2
        if (CTSU_MODE_CURRENT_SCAN == p_instance_ctrl->p_ctsu_cfg->md)
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
        R_CTSU->CTSUCHAC0  = p_instance_ctrl->p_ctsu_cfg->ctsuchac0;
        R_CTSU->CTSUCHAC1  = p_instance_ctrl->p_ctsu_cfg->ctsuchac1;
        R_CTSU->CTSUCHAC2  = p_instance_ctrl->p_ctsu_cfg->ctsuchac2;
        R_CTSU->CTSUCHAC3  = p_instance_ctrl->p_ctsu_cfg->ctsuchac3;
        R_CTSU->CTSUCHAC4  = p_instance_ctrl->p_ctsu_cfg->ctsuchac4;
        R_CTSU->CTSUCHTRC0 = p_instance_ctrl->p_ctsu_cfg->ctsuchtrc0;
        R_CTSU->CTSUCHTRC1 = p_instance_ctrl->p_ctsu_cfg->ctsuchtrc1;
        R_CTSU->CTSUCHTRC2 = p_instance_ctrl->p_ctsu_cfg->ctsuchtrc2;
        R_CTSU->CTSUCHTRC3 = p_instance_ctrl->p_ctsu_cfg->ctsuchtrc3;
        R_CTSU->CTSUCHTRC4 = p_instance_ctrl->p_ctsu_cfg->ctsuchtrc4;
    }

 #if (CTSU_CFG_TEMP_CORRECTION_SUPPORT == 1)
    else
    {
        R_CTSU->CTSUSST = CTSU_SST_RECOMMEND;
        ctsu_correction_scan_start();
    }
 #endif
#endif
#if (BSP_FEATURE_CTSU_VERSION == 1)
    temp            = (uint8_t) (R_CTSU->CTSUCR1 & ~(CTSU_CR1_MODIFY_BIT));
    R_CTSU->CTSUCR1 = (uint8_t) (temp | (p_instance_ctrl->ctsucr1 & CTSU_CR1_MODIFY_BIT)); // MD1, MD0, ATUNE1

 #if BSP_FEATURE_CTSU_HAS_TXVSEL
    R_CTSU->CTSUCR0 =
        (uint8_t) ((R_CTSU->CTSUCR0 & ~(CTSU_TXVSEL)) | (p_instance_ctrl->p_ctsu_cfg->txvsel & CTSU_TXVSEL));
 #endif

    /* Write Channel setting */
    R_CTSU->CTSUCHAC[0] = p_instance_ctrl->p_ctsu_cfg->ctsuchac0;
    R_CTSU->CTSUCHAC[1] = p_instance_ctrl->p_ctsu_cfg->ctsuchac1;
 #if (BSP_FEATURE_CTSU_CTSUCHAC_REGISTER_COUNT >= 3)
    R_CTSU->CTSUCHAC[2] = p_instance_ctrl->p_ctsu_cfg->ctsuchac2;
 #endif
 #if (BSP_FEATURE_CTSU_CTSUCHAC_REGISTER_COUNT >= 4)
    R_CTSU->CTSUCHAC[3] = p_instance_ctrl->p_ctsu_cfg->ctsuchac3;
 #endif
 #if (BSP_FEATURE_CTSU_CTSUCHAC_REGISTER_COUNT >= 5)
    R_CTSU->CTSUCHAC[4] = p_instance_ctrl->p_ctsu_cfg->ctsuchac4;
 #endif

 #if (CTSU_CFG_NUM_MUTUAL_ELEMENTS != 0)
    R_CTSU->CTSUCHTRC[0] = p_instance_ctrl->p_ctsu_cfg->ctsuchtrc0;
    R_CTSU->CTSUCHTRC[1] = p_instance_ctrl->p_ctsu_cfg->ctsuchtrc1;
  #if (BSP_FEATURE_CTSU_CTSUCHTRC_REGISTER_COUNT >= 3)
    R_CTSU->CTSUCHTRC[2] = p_instance_ctrl->p_ctsu_cfg->ctsuchtrc2;
  #endif
  #if (BSP_FEATURE_CTSU_CTSUCHTRC_REGISTER_COUNT >= 4)
    R_CTSU->CTSUCHTRC[3] = p_instance_ctrl->p_ctsu_cfg->ctsuchtrc3;
  #endif
  #if (BSP_FEATURE_CTSU_CTSUCHTRC_REGISTER_COUNT >= 5)
    R_CTSU->CTSUCHTRC[4] = p_instance_ctrl->p_ctsu_cfg->ctsuchtrc4;
  #endif
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
    if (CTSU_MODE_CORRECTION_SCAN == p_instance_ctrl->p_ctsu_cfg->md)
    {
        ctsu_correction_data_get(p_instance_ctrl, p_data);
        p_instance_ctrl->state = CTSU_STATE_IDLE;

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
            if ((CTSU_MODE_SELF_MULTI_SCAN == p_instance_ctrl->p_ctsu_cfg->md) ||
                (CTSU_MODE_MUTUAL_FULL_SCAN == p_instance_ctrl->p_ctsu_cfg->md))
            {
                ctsu_initial_offset_tuning(p_instance_ctrl);
            }
        }

        p_instance_ctrl->state = CTSU_STATE_IDLE;
    }

    FSP_ERROR_RETURN(0 < p_instance_ctrl->average, FSP_ERR_CTSU_INCOMPLETE_TUNING);

#if (CTSU_CFG_NUM_SELF_ELEMENTS != 0)
    if (CTSU_MODE_SELF_MULTI_SCAN == (CTSU_MODE_MUTUAL_FULL_SCAN & p_instance_ctrl->p_ctsu_cfg->md))
    {
        if (true == p_instance_ctrl->p_ctsu_cfg->judge_multifreq_disable)
        {
            for (element_id = 0; element_id < (p_instance_ctrl->num_elements * CTSU_CFG_NUM_SUMULTI); element_id++)
            {
                *p_data = *(p_instance_ctrl->p_self_data + element_id);
                p_data++;
            }
        }
        else
        {
            for (element_id = 0; element_id < p_instance_ctrl->num_elements; element_id++)
            {
                *p_data = *(p_instance_ctrl->p_self_data + (element_id * CTSU_CFG_NUM_SUMULTI));
                p_data++;
            }
        }
    }
#endif
#if (CTSU_CFG_NUM_MUTUAL_ELEMENTS != 0)
    if (CTSU_MODE_MUTUAL_FULL_SCAN == (CTSU_MODE_MUTUAL_FULL_SCAN & p_instance_ctrl->p_ctsu_cfg->md))
    {
        if (true == p_instance_ctrl->p_ctsu_cfg->judge_multifreq_disable)
        {
            for (element_id = 0; element_id < (p_instance_ctrl->num_elements * CTSU_CFG_NUM_SUMULTI); element_id++)
            {
                *p_data = *(p_instance_ctrl->p_mutual_pri_data + element_id);
                p_data++;
                *p_data = *(p_instance_ctrl->p_mutual_snd_data + element_id);
                p_data++;
            }
        }
        else
        {
            for (element_id = 0; element_id < p_instance_ctrl->num_elements; element_id++)
            {
                *p_data = *(p_instance_ctrl->p_mutual_pri_data + (element_id * CTSU_CFG_NUM_SUMULTI));
                p_data++;
                *p_data = *(p_instance_ctrl->p_mutual_snd_data + (element_id * CTSU_CFG_NUM_SUMULTI));
                p_data++;
            }
        }
    }
#endif

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
    if (CTSU_MODE_SELF_MULTI_SCAN == (CTSU_MODE_MUTUAL_FULL_SCAN & p_instance_ctrl->p_ctsu_cfg->md))
    {
        g_ctsu_self_element_index = (uint8_t) (g_ctsu_self_element_index - p_instance_ctrl->num_elements);
    }
#endif
#if (CTSU_CFG_NUM_MUTUAL_ELEMENTS != 0)
    if (CTSU_MODE_MUTUAL_FULL_SCAN == (CTSU_MODE_MUTUAL_FULL_SCAN & p_instance_ctrl->p_ctsu_cfg->md))
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

/***********************************************************************************************************************
 * DEPRECATED Return CTSU HAL driver version. Implements @ref ctsu_api_t::versionGet.
 *
 * @retval FSP_SUCCESS             Version information successfully read.
 * @retval FSP_ERR_ASSERTION       Null pointer passed as a parameter
 **********************************************************************************************************************/
fsp_err_t R_CTSU_VersionGet (fsp_version_t * const p_version)
{
#if CTSU_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_version);
#endif

    p_version->version_id = g_ctsu_version.version_id;

    return FSP_SUCCESS;
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

    p_info->chain_mode    = TRANSFER_CHAIN_MODE_DISABLED;
    p_info->src_addr_mode = TRANSFER_ADDR_MODE_INCREMENTED;
    p_info->irq           = TRANSFER_IRQ_END;
 #if (BSP_FEATURE_CTSU_VERSION == 2)
    p_info->dest_addr_mode = TRANSFER_ADDR_MODE_FIXED;
    p_info->size           = TRANSFER_SIZE_4_BYTE;
    p_info->p_dest         = (void *) &R_CTSU->CTSUSO;
    p_info->mode           = TRANSFER_MODE_BLOCK;
    p_info->repeat_area    = TRANSFER_REPEAT_AREA_DESTINATION;
    p_info->length         = 1;
 #endif
 #if (BSP_FEATURE_CTSU_VERSION == 1)
    p_info->dest_addr_mode = TRANSFER_ADDR_MODE_INCREMENTED;
    p_info->size           = TRANSFER_SIZE_2_BYTE;
    p_info->p_dest         = (void *) &R_CTSU->CTSUSSC;
    p_info->mode           = TRANSFER_MODE_BLOCK;
    p_info->repeat_area    = TRANSFER_REPEAT_AREA_DESTINATION;
    p_info->length         = 3;
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

    p_info->chain_mode     = TRANSFER_CHAIN_MODE_DISABLED;
    p_info->dest_addr_mode = TRANSFER_ADDR_MODE_INCREMENTED;
    p_info->irq            = TRANSFER_IRQ_END;
 #if (BSP_FEATURE_CTSU_VERSION == 2)
    p_info->src_addr_mode = TRANSFER_ADDR_MODE_FIXED;
    p_info->size          = TRANSFER_SIZE_2_BYTE;
    p_info->p_dest        = p_instance_ctrl->p_mutual_raw;
    p_info->mode          = TRANSFER_MODE_BLOCK;
    p_info->repeat_area   = TRANSFER_REPEAT_AREA_SOURCE;
    p_info->length        = 1;
 #endif
 #if (BSP_FEATURE_CTSU_VERSION == 1)
    p_info->src_addr_mode = TRANSFER_ADDR_MODE_INCREMENTED;
    p_info->size          = TRANSFER_SIZE_2_BYTE;
    p_info->mode          = TRANSFER_MODE_BLOCK;
    p_info->repeat_area   = TRANSFER_REPEAT_AREA_SOURCE;
    p_info->length        = 2;
 #endif
    p_info->p_src  = (void *) &R_CTSU->CTSUSC;
    p_info->p_dest = p_instance_ctrl->p_self_raw;
 #if (CTSU_CFG_NUM_MUTUAL_ELEMENTS != 0)
    if (CTSU_MODE_MUTUAL_FULL_SCAN == (CTSU_MODE_MUTUAL_FULL_SCAN & p_instance_ctrl->p_ctsu_cfg->md))
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
    else
    {
        if (CTSU_MODE_CURRENT_SCAN == p_instance_ctrl->p_ctsu_cfg->md)
        {
            p_info->num_blocks = p_instance_ctrl->num_elements;
        }
        else
        {
            p_info->num_blocks = (uint16_t) (p_instance_ctrl->num_elements * CTSU_CFG_NUM_SUMULTI);
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
    else
    {
        p_info->num_blocks = p_instance_ctrl->num_elements;
        p_info->p_src      = p_instance_ctrl->p_ctsuwr;
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
        p_info->num_blocks = 1;
        p_info->p_dest     = (void *) &g_ctsu_correction_info.scanbuf;
        p_info->p_src      = (void *) &R_CTSU->CTSUSC;
    }

  #if (CTSU_CFG_NUM_CFC != 0)
    else if (CTSU_CORRECTION_RUN == g_ctsu_corrcfc_info.status)
    {
        p_info->length     = g_ctsu_corrcfc_info.num_ts;
        p_info->num_blocks = 1;
        p_info->p_dest     = (void *) g_ctsu_corrcfc_info.scanbuf;
        p_info->p_src      = (void *) &R_CTSU->CTSUCFCCNT;
    }
  #endif
    else
    {
        if (CTSU_MODE_CURRENT_SCAN == p_instance_ctrl->p_ctsu_cfg->md)
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
        if (CTSU_MODE_MUTUAL_FULL_SCAN == (CTSU_MODE_MUTUAL_FULL_SCAN & p_instance_ctrl->p_ctsu_cfg->md))
        {
            p_info->p_dest     = p_instance_ctrl->p_mutual_raw;
            p_info->num_blocks = (uint16_t) (p_info->num_blocks * 2); ///< Primary and Secondary
        }

   #if (CTSU_CFG_NUM_CFC != 0)
        if (CTSU_MODE_MUTUAL_CFC_SCAN == p_instance_ctrl->p_ctsu_cfg->md)
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
    else
    {
        p_info->num_blocks = p_instance_ctrl->num_elements;
        p_info->p_dest     = p_instance_ctrl->p_self_raw;
  #if (CTSU_CFG_NUM_MUTUAL_ELEMENTS != 0)
        if (CTSU_MODE_MUTUAL_FULL_SCAN == (CTSU_MODE_MUTUAL_FULL_SCAN & p_instance_ctrl->p_ctsu_cfg->md))
        {
            p_info->p_dest     = p_instance_ctrl->p_mutual_raw;
            p_info->num_blocks = (uint16_t) (p_info->num_blocks * 2); ///< Primary and Secondary
        }
  #endif
    }
 #endif
    err = p_transfer->p_api->reconfigure(p_transfer->p_ctrl, p_info);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

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
#if (BSP_FEATURE_CTSU_VERSION == 1)
    uint16_t ctsuso;
#endif
#if (BSP_FEATURE_CTSU_VERSION == 2)
    uint16_t i;
    uint16_t element_top;
    uint16_t corr_data[CTSU_CFG_NUM_SUMULTI];
    uint16_t target_val;
    int32_t  ctsuso;
    uint32_t snum;

    if (CTSU_MODE_SELF_MULTI_SCAN == p_instance_ctrl->p_ctsu_cfg->md)
    {
        target_val = (CTSU_TUNING_VALUE_SELF / 2);
    }
    else
    {
        target_val = (CTSU_TUNING_VALUE_MUTUAL / 2);
    }
#endif

    /* element_id through each element for control block */
    for (element_id = 0; element_id < p_instance_ctrl->num_elements; element_id++)
    {
        if (CTSU_TUNING_OT_COUNT != *(p_instance_ctrl->p_tuning_count + element_id))
        {
#if (BSP_FEATURE_CTSU_VERSION == 1)
 #if (CTSU_CFG_NUM_SELF_ELEMENTS != 0)
            if (CTSU_MODE_SELF_MULTI_SCAN == p_instance_ctrl->p_ctsu_cfg->md)
            {
                diff = *(p_instance_ctrl->p_self_data + element_id) - CTSU_TUNING_VALUE_SELF;
            }
 #endif
 #if (CTSU_CFG_NUM_MUTUAL_ELEMENTS != 0)
            if (CTSU_MODE_MUTUAL_FULL_SCAN == p_instance_ctrl->p_ctsu_cfg->md)
            {
                diff = *(p_instance_ctrl->p_mutual_pri_data + element_id) - CTSU_TUNING_VALUE_MUTUAL;
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
                if (CTSU_MODE_SELF_MULTI_SCAN == p_instance_ctrl->p_ctsu_cfg->md)
                {
                    corr_data[i] = p_instance_ctrl->p_self_data[element_top + i];
                }
                else
                {
                    corr_data[i] = p_instance_ctrl->p_mutual_pri_data[(element_top + i)];
                }

                snum = (p_instance_ctrl->p_ctsuwr[(element_id * CTSU_CFG_NUM_SUMULTI)].ctsuso >> 10) &
                       CTSU_SNUM_MAX;
                corr_data[i] = (uint16_t) (((uint32_t) corr_data[i] * (CTSU_SNUM_RECOMMEND + 1)) / (snum + 1));

                /* Calculate CTSUSO equivalent difference between current value and target value */
                diff = (int32_t) ((int32_t) corr_data[i] - (int32_t) target_val) /
                       (CTSU_CORRECTION_OFFSET_UNIT >> p_instance_ctrl->range);

                ctsuso  = (int32_t) (p_instance_ctrl->p_ctsuwr[element_top + i].ctsuso & CTSU_TUNING_MAX);
                ctsuso += diff;

                /* If the CTSUSO exceeds the minimum value or the maximum value, tuning complete */
                if (ctsuso < 0)
                {
                    ctsuso = 0;
                    complete_flag++;
                }
                else if (ctsuso > CTSU_TUNING_MAX)
                {
                    ctsuso = CTSU_TUNING_MAX;
                    complete_flag++;
                }
                else
                {
                    /* If the difference is large, tuning value may not be able to match, so create the next opportunity */
                    if (0 == diff)
                    {
                        complete_flag++;
                    }
                    else
                    {
                        (*(p_instance_ctrl->p_tuning_count + element_id))++;
                    }
                }

                /* Set the result of the calculated CTSUSO */
                p_instance_ctrl->p_ctsuwr[element_top + i].ctsuso &= (uint32_t) (~CTSU_TUNING_MAX);
                p_instance_ctrl->p_ctsuwr[element_top + i].ctsuso |= (uint32_t) ctsuso;
            }
#endif
        }
        else
        {
            complete_flag = CTSU_CFG_NUM_SUMULTI;
        }

        if (CTSU_CFG_NUM_SUMULTI == complete_flag)
        {
            complete_flag = 0;
            num_complete++;
            *(p_instance_ctrl->p_tuning_count + element_id) = CTSU_TUNING_OT_COUNT;
        }
    }

    if (num_complete == p_instance_ctrl->num_elements)
    {
        p_instance_ctrl->tuning = CTSU_TUNING_COMPLETE;
    }
}

/***********************************************************************************************************************
 * ctsu_moving_average
 ***********************************************************************************************************************/
void ctsu_moving_average (uint16_t * p_average, uint16_t new_data, uint16_t average_num)
{
    uint32_t work;

    work       = (uint32_t) ((uint32_t) *p_average * (uint32_t) (average_num - 1)); /* Average * (num - 1) */
    work      += new_data;                                                          /* Add Now data        */
    *p_average = (uint16_t) (work / average_num);                                   /* Average calculation */
}

/***********************************************************************************************************************
 * CTSUWR interrupt handler. This service routine sets the tuning for the next element to be scanned by hardware.
 ***********************************************************************************************************************/
void ctsu_write_isr (void)
{
#if (CTSU_CFG_DTC_SUPPORT_ENABLE == 1)

    /** Clear the BSP IRQ Flag     */
    R_BSP_IrqStatusClear(R_FSP_CurrentIrqGet());
#else
    IRQn_Type              irq             = R_FSP_CurrentIrqGet();
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
}

/***********************************************************************************************************************
 * CTSURD interrupt handler. This service routine reads the sensor count and reference counter for
 * the current element and places the value in the scan data buffer. Note that the reference counter
 * does not work properly but is saved anyway for backward compatibility and potential future use.
 * Additionally, the SC register cannot be read again until RC is read.
 ***********************************************************************************************************************/
void ctsu_read_isr (void)
{
#if (CTSU_CFG_DTC_SUPPORT_ENABLE == 1)

    /** Clear the BSP IRQ Flag     */
    R_BSP_IrqStatusClear(R_FSP_CurrentIrqGet());
#else
    IRQn_Type              irq             = R_FSP_CurrentIrqGet();
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
    else
    {
  #if (CTSU_CFG_NUM_SELF_ELEMENTS != 0)
        if (CTSU_MODE_SELF_MULTI_SCAN == p_instance_ctrl->p_ctsu_cfg->md)
        {
            (p_instance_ctrl->p_self_raw + p_instance_ctrl->rd_index)->sen = R_CTSU->CTSUSC;
            (p_instance_ctrl->p_self_raw + p_instance_ctrl->rd_index)->ref = R_CTSU->CTSURC;
            p_instance_ctrl->rd_index++;
        }
  #endif
  #if (CTSU_CFG_NUM_MUTUAL_ELEMENTS != 0)
        if (CTSU_MODE_MUTUAL_FULL_SCAN == p_instance_ctrl->p_ctsu_cfg->md)
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
    else
    {
  #if (CTSU_CFG_NUM_SELF_ELEMENTS != 0)
        if (CTSU_MODE_SELF_MULTI_SCAN == (CTSU_MODE_MUTUAL_FULL_SCAN & p_instance_ctrl->p_ctsu_cfg->md))
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
        if (CTSU_MODE_MUTUAL_FULL_SCAN == p_instance_ctrl->p_ctsu_cfg->md)
        {
            p_instance_ctrl->p_mutual_raw[p_instance_ctrl->rd_index] = R_CTSU->CTSUSC;
            p_instance_ctrl->rd_index++;
        }

   #if (CTSU_CFG_NUM_CFC != 0)
        if (CTSU_MODE_MUTUAL_CFC_SCAN == p_instance_ctrl->p_ctsu_cfg->md)
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
#endif
}

/***********************************************************************************************************************
 * CTSUFN interrupt handler. This service routine occurs when all elements have been scanned (finished).
 * The user's callback function is called if available.
 ***********************************************************************************************************************/
void ctsu_end_isr (void)
{
    IRQn_Type              irq             = R_FSP_CurrentIrqGet();
    ctsu_instance_ctrl_t * p_instance_ctrl = (ctsu_instance_ctrl_t *) R_FSP_IsrContextGet(irq);
    ctsu_callback_args_t   args;

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

    /** Clear the BSP IRQ Flag     */
    R_BSP_IrqStatusClear(R_FSP_CurrentIrqGet());

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
        if (CTSU_MODE_CORRECTION_SCAN == p_instance_ctrl->p_ctsu_cfg->md)
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

    p_instance_ctrl->state = CTSU_STATE_SCANNED;
    p_args->p_context      = p_instance_ctrl->p_context;

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
        R_CTSU->CTSUCR0 |= 0x01;
        while (0x01 & R_CTSU->CTSUCR0)
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
void ctsu_correction_data_get (ctsu_instance_ctrl_t * const p_instance_ctrl, uint16_t * p_data)
{
    uint32_t i;
    uint32_t j;
    uint16_t base_value;
    uint16_t base_conv_dac;
    int32_t  x0;
    int32_t  x1;
    int32_t  y0;

    if (g_ctsu_correction_info.scan_index < CTSU_CORRECTION_POINT_NUM)
    {
        ctsu_moving_average(&g_ctsu_correction_info.dac_value[g_ctsu_correction_info.scan_index],
                            *p_instance_ctrl->p_self_raw,
                            4);
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
            ctsu_moving_average(&g_ctsu_correction_info.ex_base_value, *p_instance_ctrl->p_self_raw, 4);
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
        ctsu_correction_calib_rtrim(p_instance_ctrl, p_data);
  #endif
    }
    else
    {
        /* Indicates that ADC measurement was not performed. */
        *p_data = CTSU_COUNT_MAX;
    }
}

  #if (CTSU_CFG_CALIB_RTRIM_SUPPORT == 1)

/***********************************************************************************************************************
 * ctsu_correction_calib_rtrim
 ***********************************************************************************************************************/
void ctsu_correction_calib_rtrim (ctsu_instance_ctrl_t * const p_instance_ctrl, uint16_t * p_data)
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

    /* Initialize ADC for CTSU TSCAP */
    p_adc->p_api->open(p_adc->p_ctrl, p_adc->p_cfg);
    p_adc->p_api->scanCfg(p_adc->p_ctrl, p_adc->p_channel_cfg);
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
            p_adc->p_api->scanStart(p_adc->p_ctrl);

            /* Wait for conversion to complete. */
            status.state = ADC_STATE_SCAN_IN_PROGRESS;
            while (ADC_STATE_SCAN_IN_PROGRESS == status.state)
            {
                p_adc->p_api->scanStatusGet(p_adc->p_ctrl, &status);
            }

            p_adc->p_api->read(p_adc->p_ctrl, ADC_CHANNEL_16, &adctdr_result);
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
    int32_t  y0 = 0;
    int32_t  y1 = 0;
    int32_t  x0 = 0;
    int32_t  x1 = 0;
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

        answer = (uint32_t) (y0 - (((y0 - y1) * (x0 - cmp_data)) / (x0 - x1)));

        if (CTSU_SNUM_RECOMMEND != p_calc->snum)
        {
            answer = (uint32_t) ((answer * (uint32_t) (p_calc->snum + 1)) / (CTSU_SNUM_RECOMMEND + 1));
        }
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
    uint16_t * p_self_data;
    uint16_t   average_self;
 #endif
 #if (CTSU_CFG_NUM_MUTUAL_ELEMENTS != 0)
    uint16_t * p_pri_data;
    uint16_t * p_snd_data;
    uint16_t   average_pri;
    uint16_t   average_snd;
 #endif

    for (element_id = 0; element_id < p_instance_ctrl->num_elements; element_id++)
    {
        calc.snum = (p_instance_ctrl->p_ctsuwr[element_id].ctsuso0 >> 10) & CTSU_SNUM_MAX;
        calc.sdpa = (p_instance_ctrl->p_ctsuwr[element_id].ctsuso1 >> 8) & CTSU_SDPA_MAX;
 #if (CTSU_CFG_NUM_SELF_ELEMENTS != 0)
        if (CTSU_MODE_SELF_MULTI_SCAN == p_instance_ctrl->p_ctsu_cfg->md)
        {
            p_self_data  = (p_instance_ctrl->p_self_data + element_id);
            average_self = *p_self_data;
            ctsu_correction_calc(p_self_data, (p_instance_ctrl->p_self_raw + element_id)->sen, &calc);
            if (1 < p_instance_ctrl->average)
            {
                ctsu_moving_average(&average_self, *p_self_data, p_instance_ctrl->average);
                *p_self_data = average_self;
            }
        }
 #endif
 #if (CTSU_CFG_NUM_MUTUAL_ELEMENTS != 0)
        p_pri_data = (p_instance_ctrl->p_mutual_pri_data + element_id);
        p_snd_data = (p_instance_ctrl->p_mutual_snd_data + element_id);
        if (CTSU_MODE_MUTUAL_FULL_SCAN == p_instance_ctrl->p_ctsu_cfg->md)
        {
            average_pri = *p_pri_data;
            average_snd = *p_snd_data;
            ctsu_correction_calc(p_pri_data, (p_instance_ctrl->p_mutual_raw + element_id)->pri_sen, &calc);
            ctsu_correction_calc(p_snd_data, (p_instance_ctrl->p_mutual_raw + element_id)->snd_sen, &calc);
            if (1 < p_instance_ctrl->average)
            {
                ctsu_moving_average(&average_pri, *p_pri_data, p_instance_ctrl->average);
                ctsu_moving_average(&average_snd, *p_snd_data, p_instance_ctrl->average);
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
    ctsu_correction_multi_t multi;
 #if (CTSU_CFG_NUM_SELF_ELEMENTS != 0)
    uint16_t * p_self_data;
    uint16_t   average_self[CTSU_CFG_NUM_SUMULTI];
 #endif
 #if (CTSU_CFG_NUM_MUTUAL_ELEMENTS != 0)
    uint16_t * p_pri_data;
    uint16_t * p_snd_data;
    uint16_t   average_pri[CTSU_CFG_NUM_SUMULTI];
    uint16_t   average_snd[CTSU_CFG_NUM_SUMULTI];

  #if (CTSU_CFG_NUM_CFC != 0)
    uint8_t  ts_id;
    uint8_t  table_id;
    uint8_t  cfc_ts_table[CTSU_CFG_NUM_CFC];
    uint16_t offset = 0;
    uint16_t cfc_id = 0;
    uint16_t num_rx = 0;

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
    calc.range          = p_instance_ctrl->range;
    calc.md             = p_instance_ctrl->p_ctsu_cfg->md;
    multi.judge_disable = p_instance_ctrl->p_ctsu_cfg->judge_multifreq_disable;

    for (element_id = 0; element_id < p_instance_ctrl->num_elements; element_id++)
    {
        calc.snum = (p_instance_ctrl->p_ctsuwr[(element_id * CTSU_CFG_NUM_SUMULTI)].ctsuso >> 10) & CTSU_SNUM_MAX;
        for (i = 0; i < CTSU_CFG_NUM_SUMULTI; i++)
        {
            ctsuso =
                (p_instance_ctrl->p_ctsuwr[(element_id * CTSU_CFG_NUM_SUMULTI) + i].ctsuso & CTSU_TUNING_MAX);
            multi.offset[i] = (ctsuso * (uint32_t) (CTSU_CORRECTION_OFFSET_UNIT >> calc.range));
        }

        if (CTSU_MODE_SELF_MULTI_SCAN == p_instance_ctrl->p_ctsu_cfg->md)
        {
 #if (CTSU_CFG_NUM_SELF_ELEMENTS != 0)
            for (i = 0; i < CTSU_CFG_NUM_SUMULTI; i++)
            {
                ctsu_correction_calc(&multi.pri[i],
                                     p_instance_ctrl->p_self_raw[(element_id * CTSU_CFG_NUM_SUMULTI) + i],
                                     &calc);
                multi.snd[i] = 0;
            }

            p_self_data = (p_instance_ctrl->p_self_data + (element_id * CTSU_CFG_NUM_SUMULTI));

            if (0 == p_instance_ctrl->average)
            {
                /* Store corrected data in p_pri_data[i] for initial offset tuning */
                for (i = 0; i < CTSU_CFG_NUM_SUMULTI; i++)
                {
                    p_self_data[i] = multi.pri[i];
                }
            }
            else
            {
                /* Store last moving averaged data */
                for (i = 0; i < CTSU_CFG_NUM_SUMULTI; i++)
                {
                    average_self[i] = p_self_data[i];
                }

                /* Matching values */
                ctsu_correction_multi(&multi, p_self_data, NULL);

                /* Update moving averaged data */
                for (i = 0; i < CTSU_CFG_NUM_SUMULTI; i++)
                {
                    ctsu_moving_average(&average_self[i], p_self_data[i], p_instance_ctrl->average);
                    p_self_data[i] = average_self[i];
                }
            }
        }
        else if (CTSU_MODE_CURRENT_SCAN == p_instance_ctrl->p_ctsu_cfg->md)
        {
            p_self_data = (p_instance_ctrl->p_self_data + (element_id * CTSU_CFG_NUM_SUMULTI));

            /* Store last moving averaged data */
            average_self[0] = p_self_data[0];

            /* Correction */
            ctsu_correction_calc(p_self_data, p_instance_ctrl->p_self_raw[element_id], &calc);

            /* Update moving averaged data */
            if (1 < p_instance_ctrl->average)
            {
                ctsu_moving_average(&average_self[0], p_self_data[0], p_instance_ctrl->average);
                p_self_data[0] = average_self[0];
            }
 #endif
        }
        else if (CTSU_MODE_MUTUAL_FULL_SCAN == p_instance_ctrl->p_ctsu_cfg->md)
        {
 #if (CTSU_CFG_NUM_MUTUAL_ELEMENTS != 0)
            for (i = 0; i < CTSU_CFG_NUM_SUMULTI; i++)
            {
                ctsu_correction_calc(&multi.pri[i],
                                     p_instance_ctrl->p_mutual_raw[(element_id * CTSU_MUTUAL_BUF_SIZE) + (i * 2)],
                                     &calc);
                ctsu_correction_calc(&multi.snd[i],
                                     p_instance_ctrl->p_mutual_raw[(element_id * CTSU_MUTUAL_BUF_SIZE) + (i * 2) + 1],
                                     &calc);
            }

            p_pri_data = (p_instance_ctrl->p_mutual_pri_data + (element_id * CTSU_CFG_NUM_SUMULTI));
            p_snd_data = (p_instance_ctrl->p_mutual_snd_data + (element_id * CTSU_CFG_NUM_SUMULTI));

            if (0 == p_instance_ctrl->average)
            {
                /* Store corrected data in p_pri_data[i] for initial offset tuning */
                for (i = 0; i < CTSU_CFG_NUM_SUMULTI; i++)
                {
                    p_pri_data[i] = multi.pri[i];
                }
            }
            else
            {
                /* Store last moving averaged data */
                for (i = 0; i < CTSU_CFG_NUM_SUMULTI; i++)
                {
                    average_pri[i] = p_pri_data[i];
                    average_snd[i] = p_snd_data[i];
                }

                /* Matching values */
                ctsu_correction_multi(&multi, p_pri_data, p_snd_data);

                /* Update moving averaged data */
                for (i = 0; i < CTSU_CFG_NUM_SUMULTI; i++)
                {
                    ctsu_moving_average(&average_pri[i], p_pri_data[i], p_instance_ctrl->average);
                    p_pri_data[i] = average_pri[i];
                    ctsu_moving_average(&average_snd[i], p_snd_data[i], p_instance_ctrl->average);
                    p_snd_data[i] = average_snd[i];
                }
            }
 #endif
        }
        else if (CTSU_MODE_MUTUAL_CFC_SCAN == p_instance_ctrl->p_ctsu_cfg->md)
        {
 #if (CTSU_CFG_NUM_MUTUAL_ELEMENTS != 0)
  #if (CTSU_CFG_NUM_CFC != 0)
            if (CTSU_MODE_MUTUAL_CFC_SCAN == p_instance_ctrl->p_ctsu_cfg->md)
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
                ctsu_correction_calc(&multi.pri[i],
                                     p_instance_ctrl->p_mutual_raw[offset + cfc_id + (num_rx * i * 2)],
                                     &calc);
                ctsu_correction_calc(&multi.snd[i],
                                     p_instance_ctrl->p_mutual_raw[offset + cfc_id + (num_rx * i * 2) + num_rx],
                                     &calc);
            }

            p_pri_data = (p_instance_ctrl->p_mutual_pri_data + (element_id * CTSU_CFG_NUM_SUMULTI));
            p_snd_data = (p_instance_ctrl->p_mutual_snd_data + (element_id * CTSU_CFG_NUM_SUMULTI));

            if (0 == p_instance_ctrl->average)
            {
                /* Store corrected data in p_pri_data[i] for initial offset tuning */
                for (i = 0; i < CTSU_CFG_NUM_SUMULTI; i++)
                {
                    p_pri_data[i] = multi.pri[i];
                }
            }
            else
            {
                /* Store last moving averaged data */
                for (i = 0; i < CTSU_CFG_NUM_SUMULTI; i++)
                {
                    average_pri[i] = p_pri_data[i];
                    average_snd[i] = p_snd_data[i];
                }

                /* Matching values */
                ctsu_correction_multi(&multi, p_pri_data, p_snd_data);

                /* Update moving averaged data */
                for (i = 0; i < CTSU_CFG_NUM_SUMULTI; i++)
                {
                    ctsu_moving_average(&average_pri[i], p_pri_data[i], p_instance_ctrl->average);
                    p_pri_data[i] = average_pri[i];
                    ctsu_moving_average(&average_snd[i], p_snd_data[i], p_instance_ctrl->average);
                    p_snd_data[i] = average_snd[i];
                }
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
void ctsu_correction_multi (ctsu_correction_multi_t * p_multi, uint16_t * p_pri, uint16_t * p_snd)
{
    uint32_t i;
    int32_t  pri_calc[CTSU_CFG_NUM_SUMULTI];
    int32_t  snd_calc[CTSU_CFG_NUM_SUMULTI];
    int32_t  sumulti[CTSU_CFG_NUM_SUMULTI];
    int32_t  pri_total;
    int32_t  snd_total;
    int32_t  add_pri;
    int32_t  add_snd;
 #if CTSU_CFG_NUM_SUMULTI >= 3
    int32_t diff[CTSU_CFG_NUM_SUMULTI];
 #endif

    sumulti[0] = CTSU_CFG_SUMULTI0 + 1;
 #if CTSU_CFG_NUM_SUMULTI >= 2
    sumulti[1] = CTSU_CFG_SUMULTI1 + 1;
 #endif
 #if CTSU_CFG_NUM_SUMULTI >= 3
    sumulti[2] = CTSU_CFG_SUMULTI2 + 1;
 #endif

    pri_calc[0] = p_multi->pri[0];
    for (i = 1; i < CTSU_CFG_NUM_SUMULTI; i++)
    {
        pri_total   = (int32_t) (p_multi->pri[i] + p_multi->offset[i]);
        pri_calc[i] = (int32_t) (((pri_total * sumulti[0]) / sumulti[i]) - (int32_t) p_multi->offset[0]);
    }

    if (NULL == p_snd)
    {
        for (i = 0; i < CTSU_CFG_NUM_SUMULTI; i++)
        {
            snd_calc[i] = 0;
        }
    }
    else
    {
        snd_calc[0] = p_multi->snd[0];
        for (i = 1; i < CTSU_CFG_NUM_SUMULTI; i++)
        {
            snd_total   = (int32_t) (p_multi->snd[i] + p_multi->offset[i]);
            snd_calc[i] = (int32_t) (((snd_total * sumulti[0]) / sumulti[i]) - (int32_t) p_multi->offset[0]);
        }
    }

    if (true == p_multi->judge_disable)
    {
        for (i = 0; i < CTSU_CFG_NUM_SUMULTI; i++)
        {
            p_pri[i] = (uint16_t) pri_calc[i];
            if (NULL != p_snd)
            {
                p_snd[i] = (uint16_t) snd_calc[i];
            }
        }
    }
    else
    {
 #if CTSU_CFG_NUM_SUMULTI == 1
        add_pri = pri_calc[0];
        add_snd = snd_calc[0];
 #endif
 #if CTSU_CFG_NUM_SUMULTI == 2
        add_pri = pri_calc[0] + pri_calc[1];
        add_snd = snd_calc[0] + snd_calc[1];
 #endif
 #if CTSU_CFG_NUM_SUMULTI >= 3
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
        }
        else
        {
            if (diff[1] < diff[2])
            {
                add_pri = pri_calc[0] + pri_calc[2];
                add_snd = snd_calc[0] + snd_calc[2];
            }
            else
            {
                add_pri = pri_calc[1] + pri_calc[2];
                add_snd = snd_calc[1] + snd_calc[2];
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
        R_CTSU->CTSUCR0 |= 0x01;
        while (0x01 & R_CTSU->CTSUCR0)
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
