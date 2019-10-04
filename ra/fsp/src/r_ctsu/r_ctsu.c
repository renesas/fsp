/***********************************************************************************************************************
 * Copyright [2019] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software is supplied by Renesas Electronics America Inc. and may only be used with products of Renesas
 * Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.  This software is protected under
 * all applicable laws, including copyright laws. Renesas reserves the right to change or discontinue this software.
 * THE SOFTWARE IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND TO THE FULLEST
 * EXTENT PERMISSIBLE UNDER APPLICABLE LAW,DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY, INCLUDING
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE SOFTWARE.
 * TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE
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
#if (CTSU_CFG_DTC_SUPPORT_ENABLE == 1)
 #include "r_dtc.h"
#endif

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#ifndef CTSU_ERROR_RETURN
/*LDRA_INSPECTED 77 S This macro does not work when surrounded by parentheses. */
#define CTSU_ERROR_RETURN(a, err) FSP_ERROR_RETURN((a), (err))
#endif

/** "CTSU" in ASCII, used to determine if device is open. */
#define CTSU_OPEN               (0x43545355ULL)

/* Macro definitions for register setting */
#define CTSU_PON_OFF            (0)        // CTSU hardware macro power off
#define CTSU_PON_ON             (1)        // CTSU hardware macro power on
#define CTSU_CSW_OFF            (0)        // Capacitance switch turned off
#define CTSU_CSW_ON             (1)        // Capacitance switch turned on
#define CTSU_PRRATIO_RECOMMEND  (3)        // Recommended setting value
#define CTSU_PRMODE_62_PULSES   (2)        // 62 pulses (recommended setting value)
#define CTSU_SOFF_ON            (0)        // High-pass noise reduction function turned on
#define CTSU_SST_RECOMMEND      (0x10)     // The value of SST should be fixed to 00010000b
#define CTSU_SSMOD              (0)        // The value of SSMOD should be fixed to 00b
#define CTSU_SSCNT              (3)        // The value of SSCNT should be fixed to 11b
#define CTSU_RICOA_RECOMMEND    (0x0F)     // Recommended setting value
#define CTSU_ICOG_100           (0)        // ICOG = 100%
#define CTSU_ICOG_66            (1)        // ICOG = 66%
#define CTSU_ICOG_50            (2)        // ICOG = 50%
#define CTSU_ICOG_40            (3)        // ICOG = 40%
#if (BSP_CFG_MCU_PART_SERIES == 2) || (BSP_CFG_MCU_PART_SERIES == 4)
#define CTSU_ICOG_RECOMMEND     (CTSU_ICOG_66)        // Recommended setting value
#endif
#if (BSP_CFG_MCU_PART_SERIES == 6)
#define CTSU_ICOG_RECOMMEND     (CTSU_ICOG_100)       // Recommended setting value
#endif

#define CTSU_TXVSEL             (0x80)     // TXVSEL bit
#define CTSU_TXVSEL2            (0x40)     // TXVSEL2 bit
#define CTSU_SOVF               (0x20)     // Overflow bit
#define CTSU_ICOMP              (0xC0)     // ICOMP bit
#define CTSU_ICOMP0             (0x80)     // ICOMP0 bit
#define CTSU_ICOMP1             (0x40)     // ICOMP1 bit
#define CTSU_ICOMPRST           (0x20)     // ICOMPRST bit
#define CTSU_PUMPON             (0x20)     // PUMPON bit
#define CTSU_CR0_MODIFY_BIT     (0xC0)     // TXVSEL
#define CTSU_CR1_MODIFY_BIT     (0xFC)     // MD1, MD0, CLK, ATUNE1, ATUNE0
#define CTSU_CR2_MODIFY_BIT     (0x33)     // POSEL, ATUNE2, MD2
#define CTSU_MULTI_FREQ_NUM     (3)
#define CTSU_SUMULTI0           (0x0047)
#define CTSU_SUMULTI1           (0x0043)
#define CTSU_SUMULTI2           (0x003F)
#define CTSU_SUMULTI3           (0x003C)
#define CTSU_SUADJ_RECOMMEND    (0x0080)

/* Macro definitions for initial offset tuning */
#define CTSU_TUNING_MAX              (0x03FF)
#define CTSU_TUNING_MIN              (0x0000)
#define CTSU_TUNING_VALUE_SELF       (15360)
#define CTSU_TUNING_VALUE_MUTUAL     (10240)

/* Macro definitions for correction */
#if (BSP_CFG_MCU_PART_SERIES == 2) || (BSP_CFG_MCU_PART_SERIES == 4)
#define CTSU_CORRECTION_1ST_STD_VAL  (40960UL)      ///< ICOG = 66%
#define CTSU_CORRECTION_2ND_STD_VAL  (24824)        ///< ICOG = 40%, (x = 40960 * 40 / 66)
#define CTSU_WAFER_PARAMETER         (0.96523525)
#endif
#if (BSP_CFG_MCU_PART_SERIES == 6)
#define CTSU_WAFER_PARAMETER         (1)
#define CTSU_CORRECTION_1ST_STD_VAL  (27306UL)      ///< ICOG = 66%, (x = 40960 * 66 / 100)
#define CTSU_CORRECTION_2ND_STD_VAL  (16384)        ///< ICOG = 40%, (x = 40960 * 40 / 100)
#endif
#define CTSU_CORRECTION_AVERAGE      (32)
#define CTSU_DECIMAL_POINT_PRECISION (10000)
#define CTSU_COUNT_MAX               (0xFFFF)
#define CTSU_PCLKB_FREQ_MHZ          (1000000)
#define CTSU_PCLKB_FREQ_RANGE1       (32000000)
#define CTSU_PCLKB_FREQ_RANGE2       (64000000)
#define CTSU_WAIT_TIME               (500)
#define CTSU_REGISTER_CTSUERRS       (*(uint16_t *)0x4008101c)
#define CTSU_CTSUERRS_VALUE          (0x0082)

#define CTSU_CORRECTION_STD_VAL      (30720)
#define CTSU_CORRECTION_STD_UNIT     (3840/2)
#define CTSU_CORRECTION_POINT_NUM    (16)
#define CTSU_CORRECTION_OFFSET_UNIT  (0x80)
#define CTSU_CORRECTION_SUMULTI_OFFSET (0x40)
#define CTSU_CORRECTION_SUMULTI0     (0x0F)
#define CTSU_CORRECTION_SUMULTI1     (0x1F)
#define CTSU_CORRECTION_SUMULTI2     (0x2F)
#define CTSU_CORRECTION_SUMULTI3     (0x3F)

/***********************************************************************************************************************
* Typedef definitions
***********************************************************************************************************************/
typedef enum e_ctsu_correction
{
    CTSU_CORRECTION_INIT,
    CTSU_CORRECTION_RUN,
    CTSU_CORRECTION_COMPLETE,
    CTSU_CORRECTION_ERROR
} ctsu_correction_status_t;

typedef struct st_ctsu_correction_info
{
    ctsu_correction_status_t status;
    ctsu_ctsuwr_t            ctsuwr;                ///> CTSU measurement parameter
#if (BSP_FEATURE_CTSU_VERSION == 2)
    uint16_t                 index;
    uint16_t                 value[CTSU_CORRECTION_POINT_NUM];
    uint32_t                 coefficient[CTSU_CORRECTION_POINT_NUM];
#endif
#if (BSP_FEATURE_CTSU_VERSION == 1)
    volatile ctsu_self_buf_t scanbuf;
    uint16_t                 first_val;             ///> 1st correction value
    uint16_t                 second_val;            ///> 2nd correction value
    uint32_t                 first_coefficient;     ///> 1st correction coefficient
    uint32_t                 second_coefficient;    ///> 2nd correction coefficient
    uint32_t                 ctsu_clock;
#endif
#if (CTSU_CFG_DTC_SUPPORT_ENABLE == 1)
    transfer_instance_t const * p_transfer_tx; ///< DTC instance for transmit at CTSUWR.Set to NULL if unused.
    transfer_instance_t const * p_transfer_rx; ///< DTC instance for receive at CTSURD. Set to NULL if unused.
#endif
} ctsu_correction_info_t;

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
#if (CTSU_CFG_DTC_SUPPORT_ENABLE == 1)
static fsp_err_t ctsu_transfer_open(ctsu_instance_ctrl_t * const p_instance_ctrl);
static fsp_err_t ctsu_transfer_close(ctsu_instance_ctrl_t * const p_instance_ctrl);
static fsp_err_t ctsu_transfer_configure(ctsu_instance_ctrl_t * const p_instance_ctrl);
#endif
static void      ctsu_moving_average(ctsu_instance_ctrl_t * const p_instance_ctrl);
static void      ctsu_initial_offset_tuning(ctsu_instance_ctrl_t * const p_instance_ctrl);
static void      ctsu_correction_process(void);
static void      ctsu_correction_measurement(uint16_t *data);
static void      ctsu_correction_count(uint16_t *correction_data, uint16_t raw_data);
void             ctsu_write_isr(void);
void             ctsu_read_isr(void);
void             ctsu_end_isr(void);
static void      ctsu_correction_and_filter(ctsu_instance_ctrl_t * const p_instance_ctrl);
#if (BSP_FEATURE_CTSU_VERSION == 2)
static void      ctsu_correction_and_filter_sub(ctsu_instance_ctrl_t * const p_instance_ctrl, uint16_t *out, uint16_t *in, uint32_t offset_count);
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
static ctsu_correction_info_t  g_ctsu_correction_info;
static uint16_t         g_ctsu_element_index = 0;
static uint8_t          g_ctsu_tuning_complete[CTSU_NUM_ELEMENTS];
static int32_t          g_ctsu_tuning_diff[CTSU_NUM_ELEMENTS];
static ctsu_ctsuwr_t    g_ctsu_ctsuwr[CTSU_NUM_ELEMENTS];
#if (CTSU_CFG_NUM_SELF_ELEMENTS != 0)
static uint16_t         g_ctsu_self_element_index = 0;
#if (BSP_FEATURE_CTSU_VERSION == 1)
static ctsu_self_buf_t  g_ctsu_self_raw[CTSU_CFG_NUM_SELF_ELEMENTS];
#endif
#if (BSP_FEATURE_CTSU_VERSION == 2)
static ctsu_self_buf_t  g_ctsu_self_raw[CTSU_CFG_NUM_SELF_ELEMENTS * 3];
#endif
static uint16_t         g_ctsu_self_work[CTSU_CFG_NUM_SELF_ELEMENTS];
static uint16_t         g_ctsu_self_data[CTSU_CFG_NUM_SELF_ELEMENTS];
#endif
#if (CTSU_CFG_NUM_MUTUAL_ELEMENTS != 0)
static uint16_t             g_ctsu_mutual_element_index = 0;
#if (BSP_FEATURE_CTSU_VERSION == 1)
static ctsu_mutual_buf_t    g_ctsu_mutual_raw[CTSU_CFG_NUM_MUTUAL_ELEMENTS];
#endif
#if (BSP_FEATURE_CTSU_VERSION == 2)
static ctsu_mutual_buf_t    g_ctsu_mutual_raw[CTSU_CFG_NUM_MUTUAL_ELEMENTS * 6];
#endif
static uint16_t             g_ctsu_mutual_pri_work[CTSU_CFG_NUM_MUTUAL_ELEMENTS];
static uint16_t             g_ctsu_mutual_snd_work[CTSU_CFG_NUM_MUTUAL_ELEMENTS];
static uint16_t             g_ctsu_mutual_pri_data[CTSU_CFG_NUM_MUTUAL_ELEMENTS];
static uint16_t             g_ctsu_mutual_snd_data[CTSU_CFG_NUM_MUTUAL_ELEMENTS];
static uint16_t             g_ctsu_mutual_data[CTSU_CFG_NUM_MUTUAL_ELEMENTS];
#endif

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/
const ctsu_api_t g_ctsu_on_ctsu =
{
    .open       = R_CTSU_Open,
    .scanStart  = R_CTSU_ScanStart,
    .dataGet    = R_CTSU_DataGet,
    .close      = R_CTSU_Close,
    .versionGet = R_CTSU_VersionGet,
};

/*******************************************************************************************************************//**
 * @addtogroup CTSU
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief Opens and configures the CTSU driver module. Implements ctsu_api_t::open.
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
fsp_err_t R_CTSU_Open(ctsu_ctrl_t * const p_ctrl, ctsu_cfg_t const * const p_cfg)
{
    ctsu_instance_ctrl_t * p_instance_ctrl = (ctsu_instance_ctrl_t *) p_ctrl;
    fsp_err_t    err = FSP_SUCCESS;
    uint8_t     element_id;
    const ctsu_element_cfg_t *element_cfgs;

#if (CTSU_CFG_PARAM_CHECKING_ENABLE == 1)
    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_cfg);
#endif
    CTSU_ERROR_RETURN(CTSU_OPEN != p_instance_ctrl->open, FSP_ERR_ALREADY_OPEN);
#if (CTSU_CFG_NUM_SELF_ELEMENTS != 0)
    if (CTSU_MODE_SELF_MULTI_SCAN == (CTSU_MODE_MUTUAL_FULL_SCAN & p_cfg->md))
    {
        CTSU_ERROR_RETURN(CTSU_CFG_NUM_SELF_ELEMENTS >=
                (uint8_t)(g_ctsu_self_element_index + p_cfg->num_rx), FSP_ERR_INVALID_ARGUMENT);
    }
#endif
#if (CTSU_CFG_NUM_MUTUAL_ELEMENTS != 0)
    if (CTSU_MODE_MUTUAL_FULL_SCAN == (CTSU_MODE_MUTUAL_FULL_SCAN & p_cfg->md))
    {
        CTSU_ERROR_RETURN(CTSU_CFG_NUM_MUTUAL_ELEMENTS >=
                (uint8_t)(g_ctsu_mutual_element_index + (p_cfg->num_rx * p_cfg->num_tx)), FSP_ERR_INVALID_ARGUMENT);

    }
#endif
    p_instance_ctrl->state = CTSU_STATE_INIT;

    p_instance_ctrl->p_ctsu_cfg = p_cfg;

    /* Initialize driver control structure */
#if (CTSU_CFG_NUM_SELF_ELEMENTS != 0)
    if (CTSU_MODE_SELF_MULTI_SCAN == (CTSU_MODE_MUTUAL_FULL_SCAN & p_cfg->md))
    {
        p_instance_ctrl->p_self_raw    = &g_ctsu_self_raw[g_ctsu_self_element_index];
        p_instance_ctrl->p_self_work   = &g_ctsu_self_work[g_ctsu_self_element_index];
        p_instance_ctrl->p_self_data   = &g_ctsu_self_data[g_ctsu_self_element_index];
        p_instance_ctrl->num_elements = p_cfg->num_rx;
        g_ctsu_self_element_index = (uint8_t)(g_ctsu_self_element_index + p_instance_ctrl->num_elements);
    }
#endif
#if (CTSU_CFG_NUM_MUTUAL_ELEMENTS != 0)
    if (CTSU_MODE_MUTUAL_FULL_SCAN == (CTSU_MODE_MUTUAL_FULL_SCAN & p_cfg->md))
    {
        p_instance_ctrl->p_mutual_raw   = &g_ctsu_mutual_raw[g_ctsu_mutual_element_index];
        p_instance_ctrl->p_mutual_pri_work = &g_ctsu_mutual_pri_work[g_ctsu_mutual_element_index];
        p_instance_ctrl->p_mutual_snd_work = &g_ctsu_mutual_snd_work[g_ctsu_mutual_element_index];
        p_instance_ctrl->p_mutual_pri_data = &g_ctsu_mutual_pri_data[g_ctsu_mutual_element_index];
        p_instance_ctrl->p_mutual_snd_data = &g_ctsu_mutual_snd_data[g_ctsu_mutual_element_index];
        p_instance_ctrl->p_mutual_data = &g_ctsu_mutual_data[g_ctsu_mutual_element_index];
        p_instance_ctrl->num_elements = (uint8_t)(p_cfg->num_rx * p_cfg->num_tx);
        g_ctsu_mutual_element_index = (uint8_t)(g_ctsu_mutual_element_index + p_instance_ctrl->num_elements);
    }
#endif
    p_instance_ctrl->p_tuning_complete = &g_ctsu_tuning_complete[g_ctsu_element_index];
    p_instance_ctrl->p_tuning_diff = &g_ctsu_tuning_diff[g_ctsu_element_index];
    p_instance_ctrl->p_ctsuwr = &g_ctsu_ctsuwr[g_ctsu_element_index];
    g_ctsu_element_index = (uint8_t)(g_ctsu_element_index + p_instance_ctrl->num_elements);

    /* Set Value */
    p_instance_ctrl->average = 0;
#if (BSP_FEATURE_CTSU_VERSION == 2)
    if (CTSU_MODE_MUTUAL_CFC_SCAN == p_cfg->md)
    {
        p_instance_ctrl->tuning = CTSU_TUNING_COMPLETE;
    }
    else if (CTSU_MODE_CURRENT_SCAN == p_cfg->md)
    {
        p_instance_ctrl->tuning = CTSU_TUNING_COMPLETE;
    }
    else
    {
#endif
        if (true == p_cfg->tunning_enable)
        {
            p_instance_ctrl->tuning = CTSU_TUNING_INCOMPLETE;
        }
        else
        {
            p_instance_ctrl->tuning = CTSU_TUNING_COMPLETE;
        }
#if (BSP_FEATURE_CTSU_VERSION == 2)
    }
#endif
    p_instance_ctrl->num_moving_average = p_cfg->num_moving_average;

#if (BSP_FEATURE_CTSU_VERSION == 1)
    p_instance_ctrl->ctsucr1 = (CTSU_CSW_ON << 1 | CTSU_PON_ON);
    p_instance_ctrl->ctsucr1 |= (uint8_t)(p_cfg->atune1 << 3);
#endif
#if (BSP_FEATURE_CTSU_VERSION == 2)
    p_instance_ctrl->ctsucr1 = (uint8_t)((p_cfg->atune12 & 0x01) << 3);
#endif
#if BSP_FEATURE_CGC_HAS_ATUNE0
    p_instance_ctrl->ctsucr1 |= (uint8_t)(p_cfg->atune0 << 2);
#endif
    p_instance_ctrl->ctsucr1 |= (uint8_t)(p_cfg->clk << 4);
    p_instance_ctrl->ctsucr1 |= (uint8_t)(p_cfg->md << 6);
#if (BSP_FEATURE_CTSU_VERSION == 2)
    p_instance_ctrl->ctsucr2 = (uint8_t)(p_cfg->atune12 & 0x02);
    p_instance_ctrl->ctsucr2 |= (uint8_t)((p_cfg->md & 0x02) >> 1);
    p_instance_ctrl->ctsucr2 |= (uint8_t)(p_cfg->posel << 4);
#endif
    for (element_id = 0; element_id < p_instance_ctrl->num_elements; element_id++)
    {
        p_instance_ctrl->p_tuning_complete[element_id] = 0;
        p_instance_ctrl->p_tuning_diff[element_id] = 0;
        element_cfgs = (p_cfg->p_elements + element_id);
#if (BSP_FEATURE_CTSU_VERSION == 2)
        if (CTSU_MODE_CURRENT_SCAN == p_cfg->md)
        {
            p_instance_ctrl->p_ctsuwr[element_id].ctsuso = (uint32_t)(element_cfgs->snum << 10);
        }
        else
        {
            p_instance_ctrl->p_ctsuwr[element_id].ctsuso = (uint32_t)((element_cfgs->sdpa << 24) | (element_cfgs->snum << 10) | element_cfgs->so);
        }
#endif
#if (BSP_FEATURE_CTSU_VERSION == 1)
        p_instance_ctrl->p_ctsuwr[element_id].ctsussc = (uint16_t)(element_cfgs->ssdiv << 8);
        p_instance_ctrl->p_ctsuwr[element_id].ctsuso0 = (uint16_t)((element_cfgs->snum << 10) | element_cfgs->so);
        p_instance_ctrl->p_ctsuwr[element_id].ctsuso1 = (uint16_t)((CTSU_ICOG_RECOMMEND << 13) | (element_cfgs->sdpa << 8) | CTSU_RICOA_RECOMMEND);
#endif
    }

    p_instance_ctrl->write_irq = p_cfg->write_irq;
    p_instance_ctrl->read_irq = p_cfg->read_irq;
    p_instance_ctrl->end_irq = p_cfg->end_irq;

    if (p_instance_ctrl->num_elements == g_ctsu_element_index)
    {
        /* Get CTSU out of stop state (supply power/clock) */
        R_BSP_MODULE_START(FSP_IP_CTSU, 0);

        /* Enable interrupts for CTSUWR, CTSURD, CTSUFN */
        R_BSP_IrqCfgEnable(p_cfg->write_irq, CTSU_CFG_INT_PRIORITY_LEVEL, p_instance_ctrl);
        R_BSP_IrqCfgEnable(p_cfg->read_irq, CTSU_CFG_INT_PRIORITY_LEVEL, p_instance_ctrl);
        R_BSP_IrqCfgEnable(p_cfg->end_irq, CTSU_CFG_INT_PRIORITY_LEVEL, p_instance_ctrl);

#if (CTSU_CFG_DTC_SUPPORT_ENABLE == 1)
        err = ctsu_transfer_open(p_instance_ctrl);
#endif
    }

#if (BSP_FEATURE_CTSU_VERSION == 1)
    /* Set power on */
    R_CTSU->CTSUCR1 = ((CTSU_CSW_ON << 1) | CTSU_PON_ON);
    /* Synchronous Noise Reduction Setting */
    R_CTSU->CTSUSDPRS = ((CTSU_SOFF_ON << 6) | (CTSU_PRMODE_62_PULSES << 4) | CTSU_PRRATIO_RECOMMEND);
    /* High Pass Noise Reduction- ALWAYS 0x30 as per HW Manual */
    R_CTSU->CTSUDCLKC = ((CTSU_SSCNT << 4) | CTSU_SSMOD);
    /* Sensor Stabilization- ALWAYS 0x10 as per HW Manual */
    R_CTSU->CTSUSST   = (CTSU_SST_RECOMMEND);

    if (CTSU_CORRECTION_INIT == g_ctsu_correction_info.status)
    {
        ctsu_correction_process();
    }
#endif
#if (BSP_FEATURE_CTSU_VERSION == 2)
    R_CTSU->CTSUCR0   = CTSU_PUMPON;

    if (CTSU_MODE_MUTUAL_CFC_SCAN == p_cfg->md)
    {
#if (CTSU_CFG_DTC_SUPPORT_ENABLE == 1)
        R_CTSU->CTSUCALIB_b.CFCRDMD = 0;
#else
        R_CTSU->CTSUCALIB_b.CFCRDMD = 1;
#endif
        R_CTSU->CTSUCRA_b.CFCON = 1;
    }
    else
    {
        /* Set power on */
        R_CTSU->CTSUCRA_b.CSW = CTSU_CSW_ON;
        R_CTSU->CTSUCRA_b.PON = CTSU_PON_ON;
    }

    uint32_t pckb_frequency = R_FSP_SystemClockHzGet(FSP_PRIV_CLOCK_PCLKB);

    if (CTSU_PCLKB_FREQ_RANGE1 >= pckb_frequency)
    {
        R_CTSU->CTSUCR1 |= (0 << 4);
        R_CTSU->CTSUCR3 = (uint8_t)((pckb_frequency / CTSU_PCLKB_FREQ_MHZ) - 1);
    }
    else if ((CTSU_PCLKB_FREQ_RANGE1 < pckb_frequency) && (CTSU_PCLKB_FREQ_RANGE2 >= pckb_frequency))
    {
        R_CTSU->CTSUCR1 |= (1 << 4);
        R_CTSU->CTSUCR3 = (uint8_t)((pckb_frequency / 2 / CTSU_PCLKB_FREQ_MHZ) - 1);
    }
    else
    {
        R_CTSU->CTSUCR1 |= (2 << 4);
        R_CTSU->CTSUCR3 = (uint8_t)((pckb_frequency / 4 / CTSU_PCLKB_FREQ_MHZ) - 1);
    }

    /* High resolution pulse mode  */
    R_CTSU->CTSUCRA_b.SDPSEL = 1;
    R_CTSU->CTSUCRA_b.LOAD = 1;
    R_CTSU->CTSUSST   = 0x18;

    if (CTSU_MODE_MUTUAL_CFC_SCAN == p_cfg->md)
    {
    }
    else if (CTSU_MODE_CURRENT_SCAN == p_cfg->md)
    {
    }
    else
    {
        if (CTSU_CORRECTION_INIT == g_ctsu_correction_info.status)
        {
            ctsu_correction_process();
        }
    }

    R_CTSU->CTSUCALIB_b.CCOCLK = 0x1;
    R_CTSU->CTSUCALIB_b.SUCLKEN = 0x1;

    R_CTSU->CTSUMCH_b.MCA0  = 1;
    R_CTSU->CTSUMCH_b.MCA1  = 1;
    R_CTSU->CTSUMCH_b.MCA2  = 1;
    R_CTSU->CTSUMCH_b.MCA3  = 0;
    R_CTSU->CTSUCRA_b.FCMODE = 0;
    R_CTSU->CTSUSUCLK0 = (uint16_t)(CTSU_SUMULTI0 << 8) | CTSU_SUADJ_RECOMMEND;
    R_CTSU->CTSUSUCLK1 = (uint16_t)(CTSU_SUMULTI1 << 8) | CTSU_SUADJ_RECOMMEND;
    R_CTSU->CTSUSUCLK2 = (uint16_t)(CTSU_SUMULTI2 << 8) | CTSU_SUADJ_RECOMMEND;
    R_CTSU->CTSUSUCLK3 = (uint16_t)(CTSU_SUMULTI3 << 8) | CTSU_SUADJ_RECOMMEND;
    R_CTSU->CTSUCRA_b.FCMODE = 1;
#endif

    p_instance_ctrl->rd_index = 0;
    p_instance_ctrl->wr_index = 0;
    p_instance_ctrl->p_callback = p_cfg->p_callback;
    p_instance_ctrl->state = CTSU_STATE_IDLE;

    /* Mark driver as open */
    p_instance_ctrl->open = CTSU_OPEN;

    return err;
}

/*******************************************************************************************************************//**
 * @brief This function should be called each time a periodic timer expires.
 * If initial offset tuning is enabled, The first several calls are used to tuning for the sensors.
 * Once that is complete, normal processing of the data from the last scan occurs.
 * If a different control block should be run on the next scan, that is set up as well, then the next scan is started.
 * Implements ctsu_api_t::scanStart.
 *
 * Example:
 * @snippet r_ctsu_example.c R_CTSU_ScanStart
 *
 * @retval FSP_SUCCESS              CTSU successfully configured.
 * @retval FSP_ERR_ASSERTION        Null pointer, or one or more configuration options is invalid.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 * @retval FSP_ERR_INVALID_STATE    Now Scanning or not get data.
 * @retval FSP_ERR_NOT_ENABLED      Other control block scan running.
 **********************************************************************************************************************/
fsp_err_t R_CTSU_ScanStart(ctsu_ctrl_t * const p_ctrl)
{
    fsp_err_t    err = FSP_SUCCESS;
    ctsu_instance_ctrl_t * p_instance_ctrl = (ctsu_instance_ctrl_t *) p_ctrl;
#if (BSP_FEATURE_CTSU_VERSION == 2)
    uint8_t temp;
    uint8_t txvsel;
#endif

#if (CTSU_CFG_PARAM_CHECKING_ENABLE == 1)
    FSP_ASSERT(p_instance_ctrl);
    CTSU_ERROR_RETURN(CTSU_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif
    CTSU_ERROR_RETURN(CTSU_STATE_IDLE == p_instance_ctrl->state, FSP_ERR_INVALID_STATE);
    CTSU_ERROR_RETURN(0x01 != (R_CTSU->CTSUCR0 & 0x01), FSP_ERR_NOT_ENABLED);

    R_FSP_IsrContextSet(p_instance_ctrl->write_irq, p_instance_ctrl);
    R_FSP_IsrContextSet(p_instance_ctrl->read_irq, p_instance_ctrl);
    R_FSP_IsrContextSet(p_instance_ctrl->end_irq, p_instance_ctrl);

#if (CTSU_CFG_DTC_SUPPORT_ENABLE == 1)
    err = ctsu_transfer_configure(p_instance_ctrl);
    CTSU_ERROR_RETURN(FSP_SUCCESS == err, err);
#endif

    if (CTSU_CAP_EXTERNAL == p_instance_ctrl->p_ctsu_cfg->cap)
    {
        R_CTSU->CTSUCR0 |= 0x06;       // specify external trigger usage
        R_CTSU->CTSUCR0 &= (uint8_t)~0x01;      // To write CTSUCR1
    }
    /* Write CTSU Control Register 1 and save mode */
#if (BSP_FEATURE_CTSU_VERSION == 2)
    txvsel = (uint8_t)((p_instance_ctrl->p_ctsu_cfg->txvsel2 << 6) | (p_instance_ctrl->p_ctsu_cfg->txvsel << 7));
    temp = (uint8_t)(R_CTSU->CTSUCR0 & ~(CTSU_CR0_MODIFY_BIT));
    R_CTSU->CTSUCR0 = (uint8_t)(temp | (txvsel & CTSU_CR0_MODIFY_BIT)); // TXVSEL
    temp = (uint8_t)(R_CTSU->CTSUCR1 & ~(CTSU_CR1_MODIFY_BIT));
    R_CTSU->CTSUCR1 = (uint8_t)(temp | (p_instance_ctrl->ctsucr1 & CTSU_CR1_MODIFY_BIT));   // MD1, MD0, CLK, ATUNE1, ATUNE0
    temp = (uint8_t)(R_CTSU->CTSUCR2 & ~(CTSU_CR2_MODIFY_BIT));
    R_CTSU->CTSUCR2 = (uint8_t)(temp | (p_instance_ctrl->ctsucr2 & CTSU_CR2_MODIFY_BIT));   // POSEL, ATUNE2, MD2
    if (CTSU_MODE_CURRENT_SCAN == p_instance_ctrl->p_ctsu_cfg->md)
    {
        R_CTSU->CTSUCRA_b.DCMODE = 1;
        R_CTSU->CTSUMCH_b.MCA0  = 1;
        R_CTSU->CTSUMCH_b.MCA1  = 0;
        R_CTSU->CTSUMCH_b.MCA2  = 0;
        R_CTSU->CTSUMCH_b.MCA3  = 0;
    }
    else
    {
        R_CTSU->CTSUCRA_b.DCMODE = 0;
        R_CTSU->CTSUMCH_b.MCA0  = 1;
        R_CTSU->CTSUMCH_b.MCA1  = 1;
        R_CTSU->CTSUMCH_b.MCA2  = 1;
        R_CTSU->CTSUMCH_b.MCA3  = 0;
    }

    /* Write Channel setting */
    R_CTSU->CTSUCHAC0 = p_instance_ctrl->p_ctsu_cfg->ctsuchac0;
    R_CTSU->CTSUCHAC1 = p_instance_ctrl->p_ctsu_cfg->ctsuchac1;
    R_CTSU->CTSUCHAC2 = p_instance_ctrl->p_ctsu_cfg->ctsuchac2;
    R_CTSU->CTSUCHAC3 = p_instance_ctrl->p_ctsu_cfg->ctsuchac3;
    R_CTSU->CTSUCHAC4 = p_instance_ctrl->p_ctsu_cfg->ctsuchac4;
    R_CTSU->CTSUCHTRC0 = p_instance_ctrl->p_ctsu_cfg->ctsuchtrc0;
    R_CTSU->CTSUCHTRC1 = p_instance_ctrl->p_ctsu_cfg->ctsuchtrc1;
    R_CTSU->CTSUCHTRC2 = p_instance_ctrl->p_ctsu_cfg->ctsuchtrc2;
    R_CTSU->CTSUCHTRC3 = p_instance_ctrl->p_ctsu_cfg->ctsuchtrc3;
    R_CTSU->CTSUCHTRC4 = p_instance_ctrl->p_ctsu_cfg->ctsuchtrc4;
#endif
#if (BSP_FEATURE_CTSU_VERSION == 1)
    R_CTSU->CTSUCR1 = p_instance_ctrl->ctsucr1;
#if BSP_FEATURE_CTSU_HAS_TXVSEL
    R_CTSU->CTSUCR0 = (uint8_t)((R_CTSU->CTSUCR0 & ~(CTSU_TXVSEL)) | (p_instance_ctrl->p_ctsu_cfg->txvsel & CTSU_TXVSEL));
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

    /* Initialize CTSU hardware control block */
    R_CTSU->CTSUCR0 |= 0x10;
    /* CTSU scan start */
    R_CTSU->CTSUCR0 |= 0x01;   ///< CTSU_STRT

    p_instance_ctrl->state = CTSU_STATE_SCANNING;

    return err;
}

/*******************************************************************************************************************//**
 * @brief This function gets the sensor values as scanned by the CTSU. Implements ctsu_api_t::dataGet.
 *
 * Example:
 * @snippet r_ctsu_example.c R_CTSU_DataGet
 *
 * @retval FSP_SUCCESS              CTSU successfully configured.
 * @retval FSP_ERR_ASSERTION        Null pointer, or one or more configuration options is invalid.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 * @retval FSP_ERR_INVALID_STATE    Other scan running.
 * @retval FSP_ERR_NOT_ENABLED      Incomplete initial offset tuning.
 **********************************************************************************************************************/
fsp_err_t R_CTSU_DataGet(ctsu_ctrl_t * const p_ctrl, uint16_t *p_data)
{
    ctsu_instance_ctrl_t * p_instance_ctrl = (ctsu_instance_ctrl_t *) p_ctrl;
    uint8_t element_id;

#if (CTSU_CFG_PARAM_CHECKING_ENABLE == 1)
    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_data);
    CTSU_ERROR_RETURN(CTSU_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif
    CTSU_ERROR_RETURN(CTSU_STATE_SCANNED == p_instance_ctrl->state, FSP_ERR_INVALID_STATE);

#if (BSP_FEATURE_CTSU_VERSION == 2)
    if (CTSU_MODE_CURRENT_SCAN == p_instance_ctrl->p_ctsu_cfg->md)
    {
        for (element_id = 0; element_id < p_instance_ctrl->num_elements; element_id++)
        {
            *(p_instance_ctrl->p_self_work + element_id) = *(p_instance_ctrl->p_self_raw + element_id);
        }
    }
#endif

    ctsu_correction_and_filter(p_instance_ctrl);

    if (CTSU_TUNING_COMPLETE == p_instance_ctrl->tuning)
    {
        /* Make Touch count value */
        ctsu_moving_average(p_instance_ctrl);
    }
    else
    {
        ctsu_initial_offset_tuning(p_instance_ctrl);
        /* Check for all elements completed. */
        for (element_id = 0; element_id < p_instance_ctrl->num_elements; element_id++)
        {
            if (0 == *(p_instance_ctrl->p_tuning_complete + element_id))
            {
                break;
            }
        }
        if (element_id == p_instance_ctrl->num_elements)
        {
            p_instance_ctrl->tuning = CTSU_TUNING_COMPLETE;
        }
    }

    p_instance_ctrl->state = CTSU_STATE_IDLE;

    CTSU_ERROR_RETURN(0 < p_instance_ctrl->average, FSP_ERR_NOT_ENABLED);

#if (CTSU_CFG_NUM_SELF_ELEMENTS != 0)
    if (CTSU_MODE_SELF_MULTI_SCAN == (CTSU_MODE_MUTUAL_FULL_SCAN & p_instance_ctrl->p_ctsu_cfg->md))
    {
        for (element_id = 0; element_id < p_instance_ctrl->num_elements; element_id++)
        {
            *p_data = *(p_instance_ctrl->p_self_data + element_id);
            p_data++;
        }
    }
#endif
#if (CTSU_CFG_NUM_MUTUAL_ELEMENTS != 0)
    if (CTSU_MODE_MUTUAL_FULL_SCAN == (CTSU_MODE_MUTUAL_FULL_SCAN & p_instance_ctrl->p_ctsu_cfg->md))
    {
        for (element_id = 0; element_id < p_instance_ctrl->num_elements; element_id++)
        {
            *p_data = *(p_instance_ctrl->p_mutual_pri_data + element_id);
            p_data++;
            *p_data = *(p_instance_ctrl->p_mutual_snd_data + element_id);
            p_data++;
        }
    }
#endif

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Disables specified CTSU control block. Implements transfer_api_t::close.
 *
 * @retval FSP_SUCCESS              CTSU successfully configured.
 * @retval FSP_ERR_ASSERTION        Null pointer, or one or more configuration options is invalid.
 * @retval FSP_ERR_NOT_OPEN         Module is not open.
 **********************************************************************************************************************/
fsp_err_t R_CTSU_Close(ctsu_ctrl_t * const p_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;
    ctsu_instance_ctrl_t * p_instance_ctrl = (ctsu_instance_ctrl_t *) p_ctrl;

    FSP_ASSERT(p_instance_ctrl);
    CTSU_ERROR_RETURN(CTSU_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);

    g_ctsu_element_index = (uint8_t)(g_ctsu_element_index - p_instance_ctrl->num_elements);
#if (CTSU_CFG_NUM_SELF_ELEMENTS != 0)
    if (CTSU_MODE_SELF_MULTI_SCAN == p_instance_ctrl->p_ctsu_cfg->md)
    {
        g_ctsu_self_element_index = (uint8_t)(g_ctsu_self_element_index - p_instance_ctrl->num_elements);
    }
#endif
#if (CTSU_CFG_NUM_MUTUAL_ELEMENTS != 0)
    if (CTSU_MODE_MUTUAL_FULL_SCAN == (CTSU_MODE_MUTUAL_FULL_SCAN & p_instance_ctrl->p_ctsu_cfg->md))
    {
        g_ctsu_mutual_element_index = (uint8_t)(g_ctsu_mutual_element_index - p_instance_ctrl->num_elements);
    }
#endif
    if (0 == g_ctsu_element_index)
    {
#if (CTSU_CFG_DTC_SUPPORT_ENABLE == 1)
        err = ctsu_transfer_close(p_instance_ctrl);
#endif
    }

    p_instance_ctrl->state = CTSU_STATE_INIT;
    p_instance_ctrl->open = false;

    return err;
}

/*******************************************************************************************************************//**
 * @brief Return CTSU HAL driver version. Implements ctsu_api_t::versionGet.
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
fsp_err_t ctsu_transfer_open(ctsu_instance_ctrl_t * const p_instance_ctrl)
{
    fsp_err_t err;
    transfer_instance_t const * p_transfer;
    transfer_info_t * p_info;
    transfer_cfg_t          cfg;
    dtc_extended_cfg_t * p_dtc_extended_configuration;

    p_transfer = p_instance_ctrl->p_ctsu_cfg->p_transfer_tx;
    p_info = p_transfer->p_cfg->p_info;
    cfg = *(p_transfer->p_cfg);
    p_dtc_extended_configuration = (dtc_extended_cfg_t *) (cfg.p_extend);

    p_info->chain_mode     = TRANSFER_CHAIN_MODE_DISABLED;
    p_info->src_addr_mode  = TRANSFER_ADDR_MODE_INCREMENTED;
    p_info->irq            = TRANSFER_IRQ_END;
#if (BSP_FEATURE_CTSU_VERSION == 2)
    p_info->dest_addr_mode = TRANSFER_ADDR_MODE_FIXED;
    p_info->size           = TRANSFER_SIZE_4_BYTE;
    p_info->p_dest         = (void *) &R_CTSU->CTSUSO;
    p_info->mode           = TRANSFER_MODE_REPEAT;
    p_info->repeat_area    = TRANSFER_REPEAT_AREA_SOURCE;
    p_info->length         = p_instance_ctrl->num_elements;
#endif
#if (BSP_FEATURE_CTSU_VERSION == 1)
    p_info->dest_addr_mode = TRANSFER_ADDR_MODE_INCREMENTED;
    p_info->size           = TRANSFER_SIZE_2_BYTE;
    p_info->p_dest         = (void *) &R_CTSU->CTSUSSC;
    p_info->mode           = TRANSFER_MODE_BLOCK;
    p_info->repeat_area    = TRANSFER_REPEAT_AREA_DESTINATION;
    p_info->length         = 3;
#endif
    p_info->p_src          = p_instance_ctrl->p_ctsuwr;
    p_dtc_extended_configuration->activation_source = p_instance_ctrl->p_ctsu_cfg->write_irq;

    err = p_transfer->p_api->open(p_transfer->p_ctrl, &cfg);
    CTSU_ERROR_RETURN(FSP_SUCCESS == err, err);
    err = p_transfer->p_api->enable(p_transfer->p_ctrl);
    CTSU_ERROR_RETURN(FSP_SUCCESS == err, err);

    g_ctsu_correction_info.p_transfer_tx = p_transfer;

    p_transfer = p_instance_ctrl->p_ctsu_cfg->p_transfer_rx;
    p_info = p_transfer->p_cfg->p_info;
    cfg = *(p_transfer->p_cfg);
    p_dtc_extended_configuration = (dtc_extended_cfg_t *) (cfg.p_extend);

    p_info->chain_mode     = TRANSFER_CHAIN_MODE_DISABLED;
    p_info->dest_addr_mode = TRANSFER_ADDR_MODE_INCREMENTED;
    p_info->irq            = TRANSFER_IRQ_END;
#if (BSP_FEATURE_CTSU_VERSION == 2)
    p_info->src_addr_mode  = TRANSFER_ADDR_MODE_FIXED;
    p_info->size           = TRANSFER_SIZE_2_BYTE;
    p_info->p_dest = p_instance_ctrl->p_mutual_raw;
    p_info->mode           = TRANSFER_MODE_REPEAT;
    p_info->repeat_area    = TRANSFER_REPEAT_AREA_DESTINATION;
    p_info->length         = (uint16_t)(p_instance_ctrl->num_elements * 3);
#endif
#if (BSP_FEATURE_CTSU_VERSION == 1)
    p_info->src_addr_mode  = TRANSFER_ADDR_MODE_INCREMENTED;
    p_info->size           = TRANSFER_SIZE_2_BYTE;
    p_info->mode           = TRANSFER_MODE_BLOCK;
    p_info->repeat_area    = TRANSFER_REPEAT_AREA_SOURCE;
    p_info->length         = 2;
#endif
    p_info->p_src          = (void *) &R_CTSU->CTSUSC;
    p_info->p_dest         = p_instance_ctrl->p_self_raw;
#if (CTSU_CFG_NUM_MUTUAL_ELEMENTS != 0)
    if (CTSU_MODE_MUTUAL_FULL_SCAN == (CTSU_MODE_MUTUAL_FULL_SCAN & p_instance_ctrl->p_ctsu_cfg->md))
    {
        p_info->p_dest = p_instance_ctrl->p_mutual_raw;
    }
#endif
    p_dtc_extended_configuration->activation_source = p_instance_ctrl->p_ctsu_cfg->read_irq;

    err = p_transfer->p_api->open(p_transfer->p_ctrl, &cfg);
    CTSU_ERROR_RETURN(FSP_SUCCESS == err, err);
    err = p_transfer->p_api->enable(p_transfer->p_ctrl);
    CTSU_ERROR_RETURN(FSP_SUCCESS == err, err);

    g_ctsu_correction_info.p_transfer_rx = p_transfer;

    return FSP_SUCCESS;
}

/***********************************************************************************************************************
* ctsu_transfer_close
***********************************************************************************************************************/
fsp_err_t ctsu_transfer_close(ctsu_instance_ctrl_t * const p_instance_ctrl)
{
    fsp_err_t err;
    transfer_instance_t const * p_transfer;

    p_transfer = p_instance_ctrl->p_ctsu_cfg->p_transfer_tx;
    err = p_transfer->p_api->close(p_transfer->p_ctrl);
    CTSU_ERROR_RETURN(FSP_SUCCESS == err, err);

    p_transfer = p_instance_ctrl->p_ctsu_cfg->p_transfer_rx;
    err = p_transfer->p_api->close(p_transfer->p_ctrl);
    CTSU_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/***********************************************************************************************************************
* ctsu_transfer_configure
***********************************************************************************************************************/
fsp_err_t ctsu_transfer_configure(ctsu_instance_ctrl_t * const p_instance_ctrl)
{
    fsp_err_t err;
    transfer_instance_t const * p_transfer;
    transfer_info_t * p_info;

    p_transfer = p_instance_ctrl->p_ctsu_cfg->p_transfer_tx;
    p_info = p_transfer->p_cfg->p_info;

#if (BSP_FEATURE_CTSU_VERSION == 2)
    p_info->length         = p_instance_ctrl->num_elements;
    p_info->p_src          = p_instance_ctrl->p_ctsuwr;
#endif
#if (BSP_FEATURE_CTSU_VERSION == 1)
    p_info->num_blocks     = p_instance_ctrl->num_elements;
    p_info->length         = 3;
    p_info->p_src          = p_instance_ctrl->p_ctsuwr;
#endif
    err = p_transfer->p_api->reconfigure(p_transfer->p_ctrl, p_info);
    CTSU_ERROR_RETURN(FSP_SUCCESS == err, err);

    p_transfer = p_instance_ctrl->p_ctsu_cfg->p_transfer_rx;
    p_info = p_transfer->p_cfg->p_info;

#if (BSP_FEATURE_CTSU_VERSION == 2)
    p_info->length         = (uint16_t)(p_instance_ctrl->num_elements * 3);
    p_info->p_dest         = p_instance_ctrl->p_self_raw;
    p_info->p_src          = (void *) &R_CTSU->CTSUSC;
#if (CTSU_CFG_NUM_MUTUAL_ELEMENTS != 0)
    if (CTSU_MODE_MUTUAL_FULL_SCAN == (CTSU_MODE_MUTUAL_FULL_SCAN & p_instance_ctrl->p_ctsu_cfg->md))
    {
        p_info->p_dest = p_instance_ctrl->p_mutual_raw;
        p_info->length = (uint16_t)(p_info->length * 2);  ///< Primary and Secondary
    }
    if (CTSU_MODE_MUTUAL_CFC_SCAN == p_instance_ctrl->p_ctsu_cfg->md)
    {
        p_info->p_src  = (void *) &R_CTSU->CTSUCFCCNT;
    }
#endif
#endif
#if (BSP_FEATURE_CTSU_VERSION == 1)
    p_info->num_blocks     = p_instance_ctrl->num_elements;
    p_info->length         = 2;
    p_info->p_dest         = p_instance_ctrl->p_self_raw;
#if (CTSU_CFG_NUM_MUTUAL_ELEMENTS != 0)
    if (CTSU_MODE_MUTUAL_FULL_SCAN == (CTSU_MODE_MUTUAL_FULL_SCAN & p_instance_ctrl->p_ctsu_cfg->md))
    {
        p_info->p_dest = p_instance_ctrl->p_mutual_raw;
        p_info->num_blocks = (uint16_t)(p_info->num_blocks * 2);  ///< Primary and Secondary
    }
#endif
#endif
    err = p_transfer->p_api->reconfigure(p_transfer->p_ctrl, p_info);
    CTSU_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}
#endif

/***********************************************************************************************************************
* ctsu_initial_offset_tuning
***********************************************************************************************************************/
void ctsu_initial_offset_tuning(ctsu_instance_ctrl_t * const p_instance_ctrl)
{
    uint8_t  element_id;
    uint16_t ctsuso;
    int32_t  diff = 0;

    /* element_id through each element for control block */
    for (element_id = 0; element_id < p_instance_ctrl->num_elements; element_id++)
    {
        if (0 == *(p_instance_ctrl->p_tuning_complete + element_id))
        {
#if (CTSU_CFG_NUM_SELF_ELEMENTS != 0)
            if (CTSU_MODE_SELF_MULTI_SCAN == p_instance_ctrl->p_ctsu_cfg->md)
            {
                diff = *(p_instance_ctrl->p_self_work + element_id) - CTSU_TUNING_VALUE_SELF;
            }
#endif
#if (CTSU_CFG_NUM_MUTUAL_ELEMENTS != 0)
            if (CTSU_MODE_MUTUAL_FULL_SCAN == p_instance_ctrl->p_ctsu_cfg->md)
            {
                diff = *(p_instance_ctrl->p_mutual_pri_work + element_id) - CTSU_TUNING_VALUE_MUTUAL;
            }
#endif
#if (BSP_FEATURE_CTSU_VERSION == 2)
            ctsuso = (uint16_t)(p_instance_ctrl->p_ctsuwr[element_id].ctsuso & CTSU_TUNING_MAX);
#endif
#if (BSP_FEATURE_CTSU_VERSION == 1)
            ctsuso = (p_instance_ctrl->p_ctsuwr[element_id].ctsuso0 & CTSU_TUNING_MAX);
#endif

            if (0 < diff)
            {
                if (*(p_instance_ctrl->p_tuning_diff + element_id) < 0)
                {
                    if ((-diff) > *(p_instance_ctrl->p_tuning_diff + element_id) )
                    {
                        ctsuso++;   ///< Decrease count
                    }
                    *(p_instance_ctrl->p_tuning_complete + element_id) = 1;
                }
                else
                {
                    if (CTSU_TUNING_MAX == ctsuso)  /* CTSUSO limit check    */
                    {
                        *(p_instance_ctrl->p_tuning_complete + element_id) = 1;
                        break;
                    }
                    ctsuso++;   ///< Decrease count
                    (*(p_instance_ctrl->p_tuning_diff + element_id)) = diff;    ///< Plus
                }
            }
            else if (0 == diff)
            {
                *(p_instance_ctrl->p_tuning_complete + element_id) = 1;
            }
            else
            {
                if (*(p_instance_ctrl->p_tuning_diff + element_id) > 0)
                {
                    if ((-diff) > *(p_instance_ctrl->p_tuning_diff + element_id) )
                    {
                        ctsuso--;   ///< Increase count
                    }
                    *(p_instance_ctrl->p_tuning_complete + element_id) = 1;
                }
                else
                {
                    if (CTSU_TUNING_MIN == ctsuso)  /* CTSUSO limit check    */
                    {
                        *(p_instance_ctrl->p_tuning_complete + element_id) = 1;
                        break;
                    }
                    ctsuso--;   ///< Increase count
                    (*(p_instance_ctrl->p_tuning_diff + element_id)) = diff;    ///< Minus
                }
            }
#if (BSP_FEATURE_CTSU_VERSION == 2)
            p_instance_ctrl->p_ctsuwr[element_id].ctsuso &= (uint32_t)(~CTSU_TUNING_MAX);
            p_instance_ctrl->p_ctsuwr[element_id].ctsuso |= ctsuso;
#endif
#if (BSP_FEATURE_CTSU_VERSION == 1)
            p_instance_ctrl->p_ctsuwr[element_id].ctsuso0 &= (uint16_t)(~CTSU_TUNING_MAX);
            p_instance_ctrl->p_ctsuwr[element_id].ctsuso0 |= ctsuso;
#endif
        }
    }
}

/***********************************************************************************************************************
* ctsu_moving_average
***********************************************************************************************************************/
void ctsu_moving_average(ctsu_instance_ctrl_t * const p_instance_ctrl)
{
    uint8_t     element_id;
    uint32_t    work;
    uint16_t    *p_average_data;
#if (CTSU_CFG_NUM_MUTUAL_ELEMENTS != 0)
    uint16_t    *p_average_data2;
#endif

    if (p_instance_ctrl->average < p_instance_ctrl->num_moving_average)
    {
        (p_instance_ctrl->average)++;
    }

    for (element_id = 0; element_id < p_instance_ctrl->num_elements; element_id++)
    {
#if (CTSU_CFG_NUM_SELF_ELEMENTS != 0)
        if (CTSU_MODE_SELF_MULTI_SCAN == (CTSU_MODE_MUTUAL_FULL_SCAN & p_instance_ctrl->p_ctsu_cfg->md))
        {
            p_average_data = p_instance_ctrl->p_self_data + element_id;
            if (1 == p_instance_ctrl->average)
            {
                *p_average_data = *(p_instance_ctrl->p_self_work + element_id);
            }
            else
            {
                work = (uint32_t)(*p_average_data * ((p_instance_ctrl->average) - 1)); /* Average * (ADDTIME-1)  */
                work += *(p_instance_ctrl->p_self_work + element_id);                  /* Add Now data           */
                *p_average_data = (uint16_t)(work / p_instance_ctrl->average);
            }
        }
#endif
#if (CTSU_CFG_NUM_MUTUAL_ELEMENTS != 0)
        if (CTSU_MODE_MUTUAL_FULL_SCAN == (CTSU_MODE_MUTUAL_FULL_SCAN & p_instance_ctrl->p_ctsu_cfg->md))
        {
            /* Primary */
            p_average_data = p_instance_ctrl->p_mutual_pri_data + element_id;
            if (1 == p_instance_ctrl->average)
            {
                *p_average_data = *(p_instance_ctrl->p_mutual_pri_work + element_id);
            }
            else
            {
                work = (uint32_t)(*p_average_data * ((p_instance_ctrl->average) - 1)); /* Average * (ADDTIME-1)  */
                work += *(p_instance_ctrl->p_mutual_pri_work + element_id);            /* Add Now data           */
                *p_average_data = (uint16_t)(work / p_instance_ctrl->average);
            }
            /* Secondary */
            p_average_data2 = p_instance_ctrl->p_mutual_snd_data + element_id;
            if (1 == p_instance_ctrl->average)
            {
                *p_average_data2 = *(p_instance_ctrl->p_mutual_snd_work + element_id);;
            }
            else
            {
                work = (uint32_t)(*p_average_data2 * ((p_instance_ctrl->average) - 1)); /* Average * (ADDTIME-1)  */
                work += *(p_instance_ctrl->p_mutual_snd_work + element_id);             /* Add Now data           */
                *p_average_data2 = (uint16_t)(work / p_instance_ctrl->average);
            }

            if (*p_average_data2 > *p_average_data)
            {
                *(p_instance_ctrl->p_mutual_data + element_id) = (uint16_t)(*p_average_data2 - *p_average_data);
            }
            else
            {
                *(p_instance_ctrl->p_mutual_data + element_id) = 0;
            }
        }
#endif
    }
}

/***********************************************************************************************************************
* CTSUWR interrupt handler. This service routine sets the tuning for the next element to be scanned by hardware.
***********************************************************************************************************************/
void ctsu_write_isr(void)
{
#if (CTSU_CFG_DTC_SUPPORT_ENABLE == 1)
    /** Clear the BSP IRQ Flag     */
    R_BSP_IrqStatusClear(R_FSP_CurrentIrqGet());
#else
    IRQn_Type             irq    = R_FSP_CurrentIrqGet();
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
    else
    {
#if (BSP_FEATURE_CTSU_VERSION == 2)
        R_CTSU->CTSUSO = p_instance_ctrl->p_ctsuwr[p_instance_ctrl->wr_index / 3].ctsuso;
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
void ctsu_read_isr(void)
{
#if (CTSU_CFG_DTC_SUPPORT_ENABLE == 1)
    /** Clear the BSP IRQ Flag     */
    R_BSP_IrqStatusClear(R_FSP_CurrentIrqGet());
#else
    IRQn_Type             irq    = R_FSP_CurrentIrqGet();
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
        if (CTSU_MODE_MUTUAL_FULL_SCAN == (CTSU_MODE_MUTUAL_FULL_SCAN & p_instance_ctrl->p_ctsu_cfg->md))
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
    if (CTSU_CORRECTION_RUN == g_ctsu_correction_info.status)
    {
        g_ctsu_correction_info.value[g_ctsu_correction_info.index] = R_CTSU->CTSUSC;
        g_ctsu_correction_info.index++;
        if (0 == (g_ctsu_correction_info.index % 4))
        {
            g_ctsu_correction_info.index = (uint8_t)(g_ctsu_correction_info.index - 4);
        }
    }
    else
    {
#if (CTSU_CFG_NUM_SELF_ELEMENTS != 0)
        if (CTSU_MODE_SELF_MULTI_SCAN == p_instance_ctrl->p_ctsu_cfg->md || (CTSU_MODE_CURRENT_SCAN == p_instance_ctrl->p_ctsu_cfg->md))
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
        if (CTSU_MODE_MUTUAL_CFC_SCAN == p_instance_ctrl->p_ctsu_cfg->md)
        {
            uint16_t i;
            for (i = 0; i < p_instance_ctrl->p_ctsu_cfg->num_rx; i++)
            {
                p_instance_ctrl->p_mutual_raw[p_instance_ctrl->rd_index] = R_CTSU->CTSUCFCCNT_b.CFCCNT;
                p_instance_ctrl->rd_index++;
            }
        }
#endif
    }
#endif
#endif
}

/***********************************************************************************************************************
* CTSUFN interrupt handler. This service routine occurs when all elements have been scanned (finished).
* The user's callback function is called if available.
***********************************************************************************************************************/
void ctsu_end_isr(void)
{
    IRQn_Type             irq    = R_FSP_CurrentIrqGet();
    ctsu_instance_ctrl_t * p_instance_ctrl = (ctsu_instance_ctrl_t *) R_FSP_IsrContextGet(irq);
    ctsu_callback_args_t   args;

    /** Clear the BSP IRQ Flag     */
    R_BSP_IrqStatusClear(R_FSP_CurrentIrqGet());

    args.event = CTSU_EVENT_SCAN_COMPLETE;
    /* if callback present, check for error and do callback */
    if (p_instance_ctrl->p_callback != NULL)
    {
        if (R_CTSU->CTSUST & CTSU_SOVF) ///< SENSOVF
        {
            args.event |= CTSU_EVENT_OVERFLOW;
            R_CTSU->CTSUST &= (uint8_t)(~CTSU_SOVF);
        }
#if (BSP_FEATURE_CTSU_VERSION == 2)
        if (R_CTSU->CTSUSR0 & CTSU_ICOMP)   ///< ICOMP1, ICOMP0
        {
            if (R_CTSU->CTSUSR0 & CTSU_ICOMP0)
            {
                args.event |= CTSU_EVENT_ICOMP;
            }
            if (R_CTSU->CTSUSR0 & CTSU_ICOMP1)
            {
                args.event |= CTSU_EVENT_ICOMP1;
            }
            R_CTSU->CTSUSR0 |= CTSU_ICOMPRST;   ///< ICOMPRST
        }
#endif
#if (BSP_FEATURE_CTSU_VERSION == 1)
        if (R_CTSU->CTSUERRS_b.CTSUICOMP == 1)
        {
            R_CTSU->CTSUCR1 &= (uint8_t)(~0x01);
            __NOP();
            __NOP();
            R_CTSU->CTSUCR1 |= 0x01;
            args.event = CTSU_EVENT_ICOMP;
        }
#endif
        if (CTSU_STATE_SCANNING == p_instance_ctrl->state)
        {
            p_instance_ctrl->state = CTSU_STATE_SCANNED;
            p_instance_ctrl->p_callback(&args);
        }
    }

    /* reset indexes */
    p_instance_ctrl->wr_index = 0;
    p_instance_ctrl->rd_index = 0;
}

/***********************************************************************************************************************
* ctsu_correction_process
***********************************************************************************************************************/
void ctsu_correction_process(void)
{
#if (BSP_FEATURE_CTSU_VERSION == 2)
    uint8_t i;

    g_ctsu_correction_info.status = CTSU_CORRECTION_RUN;
    g_ctsu_correction_info.ctsuwr.ctsuso = (0x0F << 10);
    R_CTSU->CTSUCRA_b.MD0 = 1;
    R_CTSU->CTSUCHAC0 = 1;
    R_CTSU->CTSUCALIB_b.CCOCLK = 0x0;
    R_CTSU->CTSUCALIB_b.CCOCALIB = 1;
    R_CTSU->CTSUCALIB_b.TSOC = 1;
    R_CTSU->CTSUMCH_b.MCA0  = 1;
    R_CTSU->CTSUMCH_b.MCA1  = 1;
    R_CTSU->CTSUMCH_b.MCA2  = 1;
    R_CTSU->CTSUMCH_b.MCA3  = 1;

    for (i = 0; i < 4; i++)
    {
        R_CTSU->CTSUCRA_b.FCMODE = 0;
        R_CTSU->CTSUSUCLK0 = (uint16_t)((i * CTSU_CORRECTION_SUMULTI_OFFSET) + CTSU_CORRECTION_SUMULTI0);
        R_CTSU->CTSUSUCLK1 = (uint16_t)((i * CTSU_CORRECTION_SUMULTI_OFFSET) + CTSU_CORRECTION_SUMULTI1);
        R_CTSU->CTSUSUCLK2 = (uint16_t)((i * CTSU_CORRECTION_SUMULTI_OFFSET) + CTSU_CORRECTION_SUMULTI2);
        R_CTSU->CTSUSUCLK3 = (uint16_t)((i * CTSU_CORRECTION_SUMULTI_OFFSET) + CTSU_CORRECTION_SUMULTI3);
        R_CTSU->CTSUCRA_b.FCMODE = 1;
        g_ctsu_correction_info.index = (uint8_t)(i * 4);
        ctsu_correction_measurement(&g_ctsu_correction_info.value[g_ctsu_correction_info.index]);
    }

    R_CTSU->CTSUCALIB_b.CCOCALIB = 0;
    R_CTSU->CTSUCALIB_b.TSOC = 0;

    for (i = 0; i < CTSU_CORRECTION_POINT_NUM; i++)
    {
        if (0 == g_ctsu_correction_info.value[i])
        {
            g_ctsu_correction_info.status = CTSU_CORRECTION_ERROR;
            break;
        }
        g_ctsu_correction_info.coefficient[i] =
        (uint32_t)((CTSU_CORRECTION_STD_UNIT * (i + 1) * CTSU_DECIMAL_POINT_PRECISION) / g_ctsu_correction_info.value[i]);
    }

    g_ctsu_correction_info.status = CTSU_CORRECTION_COMPLETE;
#endif
#if (BSP_FEATURE_CTSU_VERSION == 1)
    uint16_t second_std_val;
    uint16_t ctsu_sdpa;
    uint32_t pckb_frequency = R_FSP_SystemClockHzGet(FSP_PRIV_CLOCK_PCLKB);

#if BSP_FEATURE_CTSU_HAS_TRMR
    uint8_t ctsutrimr_def;
#endif

    g_ctsu_correction_info.status = CTSU_CORRECTION_RUN;

    if (CTSU_PCLKB_FREQ_RANGE1 >= pckb_frequency)
    {
        R_CTSU->CTSUCR1 |= (0 << 4);
        g_ctsu_correction_info.ctsu_clock = pckb_frequency;
    }
    else if ((CTSU_PCLKB_FREQ_RANGE1 < pckb_frequency) && (CTSU_PCLKB_FREQ_RANGE2 >= pckb_frequency))
    {
        R_CTSU->CTSUCR1 |= (1 << 4);
        g_ctsu_correction_info.ctsu_clock = pckb_frequency / 2;
    }
    else
    {
        R_CTSU->CTSUCR1 |= (2 << 4);
        g_ctsu_correction_info.ctsu_clock = pckb_frequency / 4;
    }

    R_CTSU->CTSUCR1 |= (CTSU_MODE_SELF_MULTI_SCAN << 6);
    R_CTSU->CTSUCHAC[0] = 0x01;

    /* Initialize CTSU hardware control block */
    R_CTSU->CTSUCR0 |= 0x10;

    g_ctsu_correction_info.ctsuwr.ctsussc = (CTSU_SSDIV_0500 << 8);
    g_ctsu_correction_info.ctsuwr.ctsuso0 = 0x0000;
    /* Get SDPA value */
    ctsu_sdpa = (uint16_t)((g_ctsu_correction_info.ctsu_clock / CTSU_PCLKB_FREQ_MHZ) - 1);
    g_ctsu_correction_info.ctsuwr.ctsuso1 = (uint16_t)((CTSU_ICOG_66 << 13) | (ctsu_sdpa << 8) | CTSU_RICOA_RECOMMEND);

    /* Correction measurement setting */
    CTSU_REGISTER_CTSUERRS |= (uint16_t)CTSU_CTSUERRS_VALUE;
    R_BSP_SoftwareDelay(CTSU_WAIT_TIME, BSP_DELAY_UNITS_MICROSECONDS);

    /* First value measurement */
    ctsu_correction_measurement(&g_ctsu_correction_info.first_val);

    /* Second standard value create */
#if BSP_FEATURE_CTSU_HAS_TRMR
    uint32_t work;

    /*                       ctsutrimr_def + 273            ((ctsutrimr_def + 273) * 2560 * 128)      */
    /*    second_std_val  =  ------------------- * 40960 =  ------------------------------------ + 64 */
    /*                               528                                   33 * 128                   */

    work = (ctsutrimr_def + 273) * 9930 + 64;
    second_std_val = (uint16_t)(work >> 7);
    /* Current trimming value storage */
    ctsutrimr_def    = CTSU.CTSUTRMR;
    /* 0xFF set in the current trimming register */
    CTSU.CTSUTRMR = 0xFF;
#else
    second_std_val = (uint16_t)(CTSU_CORRECTION_2ND_STD_VAL * CTSU_WAFER_PARAMETER);
    g_ctsu_correction_info.ctsuwr.ctsuso1 |= (uint16_t)(CTSU_ICOG_40 << 13); /* ICO gain  66% -> 40% */
#endif

    /* Second value measurement */
    ctsu_correction_measurement(&g_ctsu_correction_info.second_val);
#if BSP_FEATURE_CTSU_HAS_TRMR
    /* Return the current trimming register to the initial value */
    CTSU.CTSUTRMR = ctsutrimr_def;
#endif

    /* Normal measurement setting */
    CTSU_REGISTER_CTSUERRS = (uint16_t)0x0000;
    R_BSP_SoftwareDelay(CTSU_WAIT_TIME, BSP_DELAY_UNITS_MICROSECONDS);

    if ((0 != g_ctsu_correction_info.first_val) && (0 != g_ctsu_correction_info.second_val))
    {
        if (g_ctsu_correction_info.second_val < g_ctsu_correction_info.first_val)
        {
            /* 1st coefficient create */
            g_ctsu_correction_info.first_coefficient = ((CTSU_CORRECTION_1ST_STD_VAL * CTSU_DECIMAL_POINT_PRECISION)
                    + (g_ctsu_correction_info.first_val / 2) ) / g_ctsu_correction_info.first_val;

            /* 2nd coefficient create */
            g_ctsu_correction_info.second_coefficient = (((uint32_t)second_std_val * CTSU_DECIMAL_POINT_PRECISION)
                    + (g_ctsu_correction_info.second_val / 2)) / g_ctsu_correction_info.second_val;

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
void ctsu_correction_measurement(uint16_t *data)
{
    uint8_t     i;
#if (BSP_FEATURE_CTSU_VERSION == 1)
    uint32_t    sum = 0;
#endif
#if (BSP_FEATURE_CTSU_VERSION == 2)
    uint32_t    sum[4] = {0, 0, 0, 0};
#endif

#if (CTSU_CFG_DTC_SUPPORT_ENABLE == 1)
    transfer_instance_t const * p_transfer_tx = g_ctsu_correction_info.p_transfer_tx;
    transfer_instance_t const * p_transfer_rx = g_ctsu_correction_info.p_transfer_rx;
    transfer_info_t * p_info_tx = p_transfer_tx->p_cfg->p_info;
    transfer_info_t * p_info_rx = p_transfer_rx->p_cfg->p_info;
    void const * temp_src = p_info_tx->p_src;
    void * temp_dest = p_info_rx->p_dest;
#endif
    for (i = 0; i < CTSU_CORRECTION_AVERAGE; i++)
    {
#if (CTSU_CFG_DTC_SUPPORT_ENABLE == 1)
#if (BSP_FEATURE_CTSU_VERSION == 2)
        p_info_tx->length         = 1;
        p_info_rx->length         = 4;
        p_info_rx->p_dest = (void *)data;
#endif
#if (BSP_FEATURE_CTSU_VERSION == 1)
        p_info_tx->length         = 3;
        p_info_rx->length         = 2;
        p_info_tx->num_blocks     = 1;
        p_info_rx->num_blocks     = 1;
        p_info_rx->p_dest = (void *)&g_ctsu_correction_info.scanbuf;
#endif
        p_info_tx->p_src  = (void *)&(g_ctsu_correction_info.ctsuwr);
        p_transfer_tx->p_api->reconfigure(p_transfer_tx->p_ctrl, p_info_tx);
        p_transfer_rx->p_api->reconfigure(p_transfer_rx->p_ctrl, p_info_rx);
#endif
        R_CTSU->CTSUCR0 |= 0x01;
        while (0x01 & R_CTSU->CTSUCR0)
        {
        }
#if (BSP_FEATURE_CTSU_VERSION == 2)
        sum[0] += *data;
        sum[1] += *(data + 1);
        sum[2] += *(data + 2);
        sum[3] += *(data + 3);
#endif
#if (BSP_FEATURE_CTSU_VERSION == 1)
        sum += g_ctsu_correction_info.scanbuf.sen;
#endif
    }

#if (CTSU_CFG_DTC_SUPPORT_ENABLE == 1)
    p_info_tx->p_src  = temp_src;
    p_info_rx->p_dest = temp_dest;
#endif
#if (BSP_FEATURE_CTSU_VERSION == 2)
    *data       = (uint16_t)(sum[0] / CTSU_CORRECTION_AVERAGE);
    *(data + 1) = (uint16_t)(sum[1] / CTSU_CORRECTION_AVERAGE);
    *(data + 2) = (uint16_t)(sum[2] / CTSU_CORRECTION_AVERAGE);
    *(data + 3) = (uint16_t)(sum[3] / CTSU_CORRECTION_AVERAGE);
#endif
#if (BSP_FEATURE_CTSU_VERSION == 1)
    *data = (uint16_t)(sum / CTSU_CORRECTION_AVERAGE);
#endif
}

/***********************************************************************************************************************
* ctsu_correction_count
***********************************************************************************************************************/
void ctsu_correction_count(uint16_t *correction_data, uint16_t raw_data)
{
    uint32_t    answer;
    uint32_t    coefficient;
#if (BSP_FEATURE_CTSU_VERSION == 1)
    uint16_t diff_val;
    int32_t  diff_coefficient;
    int32_t  mul_diffcoff_diff1valsval;
    uint32_t mul_coff1val_diffcorr;
#endif
#if (BSP_FEATURE_CTSU_VERSION == 2)
    uint32_t    y0 = 0;
    uint32_t    y1 = 0;
    uint32_t    x0 = 0;
    uint32_t    x1 = 0;
    uint8_t     i;
#endif

    if (CTSU_CORRECTION_COMPLETE == g_ctsu_correction_info.status)
    {
#if (BSP_FEATURE_CTSU_VERSION == 1)
        /*               g_mul_coff1val_diffcorr - g_diff_cofficient * (g_ctsu_correction_info.first_val - raw_data) */
        /*  cofficient = ------------------------------------------------------------------------------------------  */
        /*                                      g_diff_correct_val                                                   */
        /*                                                                                                           */

        diff_val = (uint16_t)(g_ctsu_correction_info.first_val - g_ctsu_correction_info.second_val);

        /* Get multiplication of g_ctsu_correction_info.first_coefficient and difference of Correction value */
        mul_coff1val_diffcorr = g_ctsu_correction_info.first_coefficient * diff_val;

        /* Get difference of Correction coefficient */
        diff_coefficient = (int32_t)(g_ctsu_correction_info.second_coefficient - g_ctsu_correction_info.first_coefficient);

        /* Get multiplication of  g_diff_cofficient  and (g_ctsu_correction_info.first_val - raw_data_coff) */
        mul_diffcoff_diff1valsval = diff_coefficient * (g_ctsu_correction_info.first_val - raw_data);

        /* Get correction coefficient of scan data */
        coefficient = (uint32_t)(((int32_t)mul_coff1val_diffcorr - mul_diffcoff_diff1valsval) / diff_val);
#endif
#if (BSP_FEATURE_CTSU_VERSION == 2)
        /* y = y0 + (y1 - y0) * (x - x0) / (x1 - x0);    [y=coeff,x=val] */
        if (raw_data <= g_ctsu_correction_info.value[0])
        {
            coefficient = g_ctsu_correction_info.coefficient[0];
        }
        else if (raw_data >= g_ctsu_correction_info.value[15])
        {
            coefficient = g_ctsu_correction_info.coefficient[15];
        }
        else
        {
            for (i = 1; i < 16; i++)
            {
                if (raw_data < g_ctsu_correction_info.value[i])
                {
                    y0 = g_ctsu_correction_info.coefficient[i];
                    y1 = g_ctsu_correction_info.coefficient[i - 1];
                    x0 = g_ctsu_correction_info.value[i];
                    x1 = g_ctsu_correction_info.value[i - 1];
                    break;
                }
            }

            if (y1 > y0)
            {
                coefficient = y0 + ((y1 - y0) * (x0 - raw_data) / (x0 - x1));
            }
            else
            {
                coefficient = y0 - ((y0 - y1) * (x0 - raw_data) / (x0 - x1));
            }
        }
#endif
        /* Get output count data */
        answer = (raw_data * coefficient) / CTSU_DECIMAL_POINT_PRECISION;

        /* Value Overflow Check */
        if (CTSU_COUNT_MAX < answer)
        {
            *correction_data = CTSU_COUNT_MAX;
        }
        else
        {
            *correction_data = (uint16_t)answer;
        }
    }
    else
    {
        *correction_data = raw_data;
    }
}

void ctsu_correction_and_filter(ctsu_instance_ctrl_t * const p_instance_ctrl)
{
    uint16_t element_id;

#if (BSP_FEATURE_CTSU_VERSION == 1)
    for (element_id = 0; element_id < p_instance_ctrl->num_elements; element_id++)
    {
#if (CTSU_CFG_NUM_SELF_ELEMENTS != 0)
        if (CTSU_MODE_SELF_MULTI_SCAN == p_instance_ctrl->p_ctsu_cfg->md)
        {
            ctsu_correction_count((p_instance_ctrl->p_self_work + element_id), (p_instance_ctrl->p_self_raw + element_id)->sen);
        }
#endif
#if (CTSU_CFG_NUM_MUTUAL_ELEMENTS != 0)
        if (CTSU_MODE_MUTUAL_FULL_SCAN == p_instance_ctrl->p_ctsu_cfg->md)
        {
            ctsu_correction_count((p_instance_ctrl->p_mutual_pri_work + element_id), (p_instance_ctrl->p_mutual_raw + element_id)->pri_sen);
            ctsu_correction_count((p_instance_ctrl->p_mutual_snd_work + element_id), (p_instance_ctrl->p_mutual_raw + element_id)->snd_sen);
        }
#endif
    }
#endif
#if (BSP_FEATURE_CTSU_VERSION == 2)
    uint32_t offset_count;
    uint16_t offset_unit;
    uint8_t  atune;
    uint32_t ctsuso;
    uint16_t raw[3] = {0, 0, 0};
#if (CTSU_CFG_NUM_MUTUAL_ELEMENTS != 0)
    uint16_t offset = 0;
    uint16_t cfc_id = 0;
#endif

    for (element_id = 0; element_id < p_instance_ctrl->num_elements; element_id++)
    {
        ctsuso = (uint16_t)(p_instance_ctrl->p_ctsuwr[element_id].ctsuso & CTSU_TUNING_MAX);
        /* 0 : 80uA, 1 : 40uA, 2 : 20uA, 3 : 160uA */
        atune = (uint8_t)((p_instance_ctrl->ctsucr2 & 0x02) | ((p_instance_ctrl->ctsucr1 & 0x08) >> 3));
        if (0 == atune)
        {
            offset_unit = CTSU_CORRECTION_OFFSET_UNIT;
        }
        else if (1 == atune)
        {
            offset_unit = CTSU_CORRECTION_OFFSET_UNIT * 2;
        }
        else if (2 == atune)
        {
            offset_unit = CTSU_CORRECTION_OFFSET_UNIT * 4;
        }
        else
        {
            offset_unit = CTSU_CORRECTION_OFFSET_UNIT / 2;
        }
        offset_count = ((ctsuso * CTSU_CORRECTION_STD_VAL) / offset_unit);

#if (CTSU_CFG_NUM_SELF_ELEMENTS != 0)
        if (CTSU_MODE_SELF_MULTI_SCAN == p_instance_ctrl->p_ctsu_cfg->md)
        {
            raw[0] = p_instance_ctrl->p_self_raw[(element_id * 3)];
            raw[1] = p_instance_ctrl->p_self_raw[(element_id * 3) + 1];
            raw[2] = p_instance_ctrl->p_self_raw[(element_id * 3) + 2];
            ctsu_correction_and_filter_sub(p_instance_ctrl, (p_instance_ctrl->p_self_work + element_id), raw, offset_count);
        }
#endif
#if (CTSU_CFG_NUM_MUTUAL_ELEMENTS != 0)
        if (CTSU_MODE_MUTUAL_FULL_SCAN == p_instance_ctrl->p_ctsu_cfg->md)
        {
            raw[0] = p_instance_ctrl->p_mutual_raw[(element_id * 6)];
            raw[1] = p_instance_ctrl->p_mutual_raw[(element_id * 6)+ 2];
            raw[2] = p_instance_ctrl->p_mutual_raw[(element_id * 6)+ 4];
            ctsu_correction_and_filter_sub(p_instance_ctrl, (p_instance_ctrl->p_mutual_pri_work + element_id), raw, offset_count);

            raw[0] = p_instance_ctrl->p_mutual_raw[(element_id * 6) + 1];
            raw[1] = p_instance_ctrl->p_mutual_raw[(element_id * 6) + 3];
            raw[2] = p_instance_ctrl->p_mutual_raw[(element_id * 6) + 5];
            ctsu_correction_and_filter_sub(p_instance_ctrl, (p_instance_ctrl->p_mutual_snd_work + element_id), raw, offset_count);
        }

        if (CTSU_MODE_MUTUAL_CFC_SCAN == p_instance_ctrl->p_ctsu_cfg->md)
        {
            cfc_id = (uint16_t)(element_id % p_instance_ctrl->p_ctsu_cfg->num_tx);
            if (0 == cfc_id)
            {
                if (0 == element_id)
                {
                    offset = 0;
                }
                else
                {
                    offset = (uint16_t)(offset + (p_instance_ctrl->p_ctsu_cfg->num_rx * 6));
                }
            }
            raw[0] = p_instance_ctrl->p_mutual_raw[offset + cfc_id];
            raw[1] = p_instance_ctrl->p_mutual_raw[offset + cfc_id + (p_instance_ctrl->p_ctsu_cfg->num_rx * 2)];
            raw[2] = p_instance_ctrl->p_mutual_raw[offset + cfc_id + (p_instance_ctrl->p_ctsu_cfg->num_rx * 4)];
            ctsu_correction_and_filter_sub(p_instance_ctrl, (p_instance_ctrl->p_mutual_pri_work + element_id), raw, offset_count);

            raw[0] = p_instance_ctrl->p_mutual_raw[offset + cfc_id +  p_instance_ctrl->p_ctsu_cfg->num_rx];
            raw[1] = p_instance_ctrl->p_mutual_raw[offset + cfc_id + (p_instance_ctrl->p_ctsu_cfg->num_rx * 3)];
            raw[2] = p_instance_ctrl->p_mutual_raw[offset + cfc_id + (p_instance_ctrl->p_ctsu_cfg->num_rx * 5)];
            ctsu_correction_and_filter_sub(p_instance_ctrl, (p_instance_ctrl->p_mutual_snd_work + element_id), raw, offset_count);
        }
#endif
    }
#endif
}

#if (BSP_FEATURE_CTSU_VERSION == 2)
void ctsu_correction_and_filter_sub(ctsu_instance_ctrl_t * const p_instance_ctrl,
        uint16_t *out, uint16_t *in, uint32_t offset_count)
{
    int32_t  diff_01;
    int32_t  diff_02;
    uint16_t work[3];
    uint32_t add_work;

    if (CTSU_MODE_MUTUAL_CFC_SCAN == p_instance_ctrl->p_ctsu_cfg->md)
    {
        work[0] = in[0];
        work[1] = in[1];
        work[2] = in[2];
    }
    else
    {
        ctsu_correction_count(&work[0], in[0]);
        ctsu_correction_count(&work[1], in[1]);
        ctsu_correction_count(&work[2], in[2]);
    }

    work[1] = (uint16_t)((((work[1] + offset_count) * (CTSU_SUMULTI0 + 1)) / (CTSU_SUMULTI1 + 1)) - offset_count);
    work[2] = (uint16_t)((((work[2] + offset_count) * (CTSU_SUMULTI0 + 1)) / (CTSU_SUMULTI2 + 1)) - offset_count);

    diff_01 = work[0] - work[1];
    diff_02 = work[0] - work[2];

    if (diff_01 < 0)
    {
        diff_01 = -diff_01;
    }
    if (diff_02 < 0)
    {
        diff_02 = -diff_02;
    }

    /* freq1 far from freq0 and freq2, or freq2 far from freq0 and freq1 */
    if ((diff_01 < p_instance_ctrl->p_ctsu_cfg->threshold_3freq) || (diff_02 < p_instance_ctrl->p_ctsu_cfg->threshold_3freq))
    {
        if (diff_01 < diff_02)
        {
            add_work = (uint32_t)(work[0] + work[1]);
        }
        else
        {
            add_work = (uint32_t)(work[0] + work[2]);
        }
    }
    else
    {
        /* It is likely that the one far from freq0 is normal */
        add_work = (uint32_t)(work[1] + work[2]);
    }

    if (CTSU_COUNT_MAX < add_work)
    {
        *out = CTSU_COUNT_MAX;
    }
    else
    {
        *out = (uint16_t)add_work;
    }
}
#endif

