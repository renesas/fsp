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
#include "r_cgc.h"
#include "r_cgc_cfg.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

#if BSP_TZ_NONSECURE_BUILD
 #if defined(BSP_CFG_CLOCKS_SECURE) && BSP_CFG_CLOCKS_SECURE
  #error "The CGC registers are only accessible in the TrustZone Secure Project."
 #endif
#endif

/* "CGC" in ASCII, used to determine if the module is open. */
#define CGC_OPEN                                 (0x00434743U)

#define CGC_PRV_SUBCLOCK_LOCO_HZ                 (32768U)

#define CGC_PRV_OSTDCR_OSC_STOP_ENABLE           (0x81U)

#if 3U == BSP_FEATURE_CGC_PLLCCR_TYPE

/* PLLMULNF in PLLCCR is 2 bits wide. */
 #define CGC_PRV_PLLCCR_PLLMULNF_MASK            (0x3U)

/* PLLMULNF in PLLCCR starts at bit 6. */
 #define CGC_PRV_PLLCCR_PLLMULNF_BIT             (6U)

/* PLLMUL in PLLCCR is 8 bits wide. */
 #define CGC_PRV_PLLCCR_PLLMUL_MASK              (0xFFU)
#elif 4U == BSP_FEATURE_CGC_PLLCCR_TYPE

/* PLLMUL in PLLCCR is 8 bits wide. */
 #define CGC_PRV_PLLCCR_PLLMUL_MASK              (0xFFU)
#else

/* PLLMUL in PLLCCR is 6 bits wide. */
 #define CGC_PRV_PLLCCR_PLLMUL_MASK              (0x3FU)
#endif

/* PLLMUL in PLLCCR starts at bit 8. */
#define CGC_PRV_PLLCCR_PLLMUL_BIT                (8U)

/* PLSRCSEL in PLLCCR starts at bit 4. */
#define CGC_PRV_PLLCCR_PLSRCSEL_BIT              (4U)

/* PLSET in PLLCCR starts at bit 6. */
#define CGC_PRV_PLLCCR_PLSET_BIT                 (6U)

/* PLLMUL in PLLCCR2 is 5 bits wide. */
#define CGC_PRV_PLLCCR2_PLLMUL_MASK              (0x1FU)

/* PLODIV in PLLCCR2 starts at bit 6. */
#define CGC_PRV_PLLCCR2_PLODIV_BIT               (6U)

/* CKODIV in CKOCR starts at bit 4. */
#define CGC_PRV_CKOCR_CKODIV_BIT                 (4)

/* PLODIVx in PLLCCR2 are 4 bits wide. */
#define CGC_PRV_PLLCCR2_PLODIVX_MASK             (0xFU)

/* PLODIVP in PLLCCR2 starts at bit 0. */
#define CGC_PRV_PLLCCR2_PLODIVP_BIT              (0U)

/* PLODIVP in PLLCCR2 starts at bit 4. */
#define CGC_PRV_PLLCCR2_PLODIVQ_BIT              (4U)

/* PLODIVP in PLLCCR2 starts at bit 8. */
#define CGC_PRV_PLLCCR2_PLODIVR_BIT              (8U)

#if 4U == BSP_FEATURE_CGC_PLLCCR_TYPE

/* Bit-mask of values that must be 1 for PLLCCR type 4. */
 #define CGC_PRV_PLLCCR_RESET_VALUE              (0x04U)
#endif

#if BSP_PRV_PLL_SUPPORTED
 #if BSP_PRV_PLL2_SUPPORTED
  #define CGC_PRV_NUM_CLOCKS                     ((uint8_t) CGC_CLOCK_PLL2 + 1U)
 #else
  #define CGC_PRV_NUM_CLOCKS                     ((uint8_t) CGC_CLOCK_PLL + 1U)
 #endif
#else
 #define CGC_PRV_NUM_CLOCKS                      ((uint8_t) CGC_CLOCK_SUBCLOCK + 1U)
#endif

/* Mask used to isolate dividers for ICLK and FCLK. */
#define CGC_PRV_SCKDIVCR_ICLK_FCLK_MASK          (0x77000000U)

#define CGC_PRV_HOCOCR                           ((uint8_t *) &R_SYSTEM->HOCOCR)
#define CGC_PRV_MOCOCR                           ((uint8_t *) &R_SYSTEM->MOCOCR)
#define CGC_PRV_LOCOCR                           ((uint8_t *) &R_SYSTEM->LOCOCR)
#define CGC_PRV_MOSCCR                           ((uint8_t *) &R_SYSTEM->MOSCCR)
#define CGC_PRV_SOSCCR                           ((uint8_t *) &R_SYSTEM->SOSCCR)
#define CGC_PRV_PLLCR                            ((uint8_t *) &R_SYSTEM->PLLCR)
#define CGC_PRV_PLL2CR                           ((uint8_t *) &R_SYSTEM->PLL2CR)

/* The closest supported power mode to use when exiting low speed or low voltage mode. */
#if BSP_FEATURE_CGC_MIDDLE_SPEED_MAX_FREQ_HZ > 0U
 #define CGC_PRV_EXIT_LOW_SPEED_MODE             (BSP_PRV_OPERATING_MODE_MIDDLE_SPEED)
#else
 #define CGC_PRV_EXIT_LOW_SPEED_MODE             (BSP_PRV_OPERATING_MODE_HIGH_SPEED)
#endif

#if BSP_FEATURE_CGC_LOW_VOLTAGE_MAX_FREQ_HZ > 0U
 #define CGC_PRV_USE_LOW_VOLTAGE_MODE            (CGC_CFG_USE_LOW_VOLTAGE_MODE)
#else
 #define CGC_PRV_USE_LOW_VOLTAGE_MODE            (0)
#endif

/* Specifications for PLL on MCUs with PLLCCR. */
#if 3U == BSP_FEATURE_CGC_PLLCCR_TYPE
 #define CGC_PRV_PLLCCR_PLL_MIN_HZ               (40000000U)
#elif 4U == BSP_FEATURE_CGC_PLLCCR_TYPE
 #define CGC_PRV_PLLCCR_PLL_MIN_HZ               (11000000U)
#else
 #define CGC_PRV_PLLCCR_PLL_MIN_HZ               (120000000U)
#endif

/* Specifications for PLL on MCUs with PLLCCR2. */
#define CGC_PRV_PLLCCR2_PLL_MIN_HZ               (24000000U)
#define CGC_PRV_PLLCCR2_PLL_MULTIPLIED_MAX_HZ    (128000000U)
#define CGC_PRV_PLLCCR2_PLL_SRC_MIN_HZ           (4000000U)
#define CGC_PRV_PLLCCR2_PLL_SRC_MAX_HZ           (12500000U)

/* Scaling factor for calculating the multiplier for PLLCCR type 3. */
#define CGC_PRV_PLL_MUL_FACTOR                   (6U)

/* Scaling factor for PLLMUL values; using scaling of 6. */
#define CGC_PRV_PLL_MUL_COEFF                    (6U)
#define CGC_PRV_PLL_MUL_NF_COEFF                 (2U)

/* Mask of the uppermost bit of all dividers in SCKDIVCR that are valid when oscillation stop detection is enabled. */
#define CGC_PRV_SCKDIVCR_UPPER_BIT               (BSP_PRV_SCKDIVCR_MASK & 0x44444444U)

/* Offset factor to convert PLL MUL values to register values. */
#define CGC_PRV_PLLCCR_TYPE4_PLLMUL_OFFSET       (574U)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/* Private enumeration used to tell if a clock is running or not. */
typedef enum e_cgc_prv_clock_state
{
    CGC_PRV_CLOCK_STATE_STOPPED = 0,
    CGC_PRV_CLOCK_STATE_RUNNING = 1,
} cgc_prv_clock_state_t;

/* Private enumeration used to specify whether changing just LPM operating modes or both LPM operating modes and CGC. */
typedef enum e_cgc_prv_change
{
    CGC_PRV_CHANGE_LPM     = 0,
    CGC_PRV_CHANGE_LPM_CGC = 1,
} cgc_prv_change_t;

/* Private enumeration for PLL output selection. */
typedef enum e_cgc_prv_pllout
{
    CGC_PRV_PLLOUT_P = 0,              ///< Primary clock output for single output PLLs or P clock output for multi-output PLL.
    CGC_PRV_PLLOUT_Q = 1,              ///< Q clock output for multi-output PLL.
    CGC_PRV_PLLOUT_R = 2,              ///< R clock output for multi-output PLL.
} cgc_prv_pllout_t;

#if defined(__ARMCC_VERSION) || defined(__ICCARM__)
typedef void (BSP_CMSE_NONSECURE_CALL * cgc_prv_ns_callback)(cgc_callback_args_t * p_args);
#elif defined(__GNUC__)
typedef BSP_CMSE_NONSECURE_CALL void (*volatile cgc_prv_ns_callback)(cgc_callback_args_t * p_args);
#endif

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
static bool                  r_cgc_low_speed_or_voltage_mode_possible(uint32_t sckdivcr, uint8_t ostdcr);
static fsp_err_t             r_cgc_clock_check(cgc_clock_t const clock_source);
static bool                  r_cgc_stabilization_check(cgc_clock_t clock, cgc_prv_clock_state_t status);
static void                  r_cgc_nmi_internal_callback(bsp_grp_irq_t irq);
static void                  r_cgc_clock_change(cgc_clock_t clock, cgc_clock_change_t state);
static cgc_prv_clock_state_t r_cgc_clock_run_state_get(cgc_clock_t clock);
static void                  r_cgc_post_change(cgc_prv_change_t change);
static void                  r_cgc_pre_change(cgc_prv_change_t change);

#if !BSP_CFG_USE_LOW_VOLTAGE_MODE

 #if BSP_FEATURE_CGC_HAS_SOPCCR
static bool r_cgc_subosc_mode_possible(uint32_t sckdivcr);

 #endif

static void r_cgc_operating_mode_reduce(uint32_t sckdivcr);

#endif

#if CGC_CFG_PARAM_CHECKING_ENABLE
static fsp_err_t r_cgc_common_parameter_checking(cgc_instance_ctrl_t * p_instance_ctrl);
static fsp_err_t r_cgc_check_config_dividers(cgc_divider_cfg_t const * const p_divider_cfg);

 #if BSP_PRV_PLL_SUPPORTED
static fsp_err_t r_cgc_pll_parameter_check(cgc_pll_cfg_t const * const p_pll_cfg, bool verify_source_stable);

 #endif
#endif

#if BSP_PRV_PLL_SUPPORTED || BSP_PRV_PLL2_SUPPORTED
static uint32_t r_cgc_pllccr_calculate(cgc_pll_cfg_t const * const p_pll_cfg);

 #if BSP_PRV_PLL_SUPPORTED

static inline cgc_clock_t r_cgc_pll_clocksource_get(void);

 #endif

 #if BSP_PRV_PLL2_SUPPORTED && CGC_CFG_PARAM_CHECKING_ENABLE

static inline cgc_clock_t r_cgc_pll2_clocksource_get(void);

 #endif

static fsp_err_t r_cgc_pll_hz_calculate(cgc_pll_cfg_t const * const p_pll_cfg,
                                        cgc_prv_pllout_t            pll_out,
                                        uint32_t * const            p_pll_hz);
static void      r_cgc_pll_cfg(uint32_t pll_hz, uint32_t pllccr);
static fsp_err_t r_cgc_pllccr_pll_hz_calculate(cgc_pll_cfg_t const * const p_pll_cfg,
                                               cgc_clock_t                 pll,
                                               cgc_prv_pllout_t            pll_out,
                                               uint32_t * const            p_pll_hz,
                                               uint32_t * const            p_pllccr);

#endif

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/** Global pointer to control structure for use by the NMI callback.  */
static cgc_instance_ctrl_t * gp_cgc_ctrl = NULL;

/* This array stores the address of the register containing the stop bit for each clock. All of these registers are
 * 8-bit registers and only bit 0 is valid.  All other bits are read as 0 and should be written to 0.  Bit 0 of each
 * of these registers indicates that the corresponding clock is stopped when set, or that the corresponding clock
 * is operating when cleared. */
static uint8_t volatile * const gp_cgc_clock_stp_registers[CGC_PRV_NUM_CLOCKS] =
{
    [CGC_CLOCK_HOCO]     = CGC_PRV_HOCOCR,
    [CGC_CLOCK_MOCO]     = CGC_PRV_MOCOCR,
    [CGC_CLOCK_LOCO]     = CGC_PRV_LOCOCR,
    [CGC_CLOCK_MAIN_OSC] = CGC_PRV_MOSCCR,
    [CGC_CLOCK_SUBCLOCK] = CGC_PRV_SOSCCR,
#if BSP_PRV_PLL_SUPPORTED
    [CGC_CLOCK_PLL] = CGC_PRV_PLLCR,
#endif
#if BSP_PRV_PLL2_SUPPORTED
    [CGC_CLOCK_PLL2] = CGC_PRV_PLL2CR,
#endif
};

/* How long of a software delay is required after starting each clock before activating it as the system clock. */
static const uint8_t g_cgc_software_wait_us[CGC_PRV_NUM_CLOCKS] =
{
    [CGC_CLOCK_HOCO]     = 0U,         // HOCO has a stabilization wait flag
    [CGC_CLOCK_MOCO]     = BSP_FEATURE_CGC_MOCO_STABILIZATION_MAX_US,
    [CGC_CLOCK_LOCO]     = BSP_FEATURE_CGC_LOCO_STABILIZATION_MAX_US,
    [CGC_CLOCK_MAIN_OSC] = 0U,         // Main oscillator has a stabilization wait flag
    [CGC_CLOCK_SUBCLOCK] = 0U,         // Subclock is assumed to be stable
#if BSP_PRV_PLL_SUPPORTED
    [CGC_CLOCK_PLL] = 0U,              // PLL has a stabilization wait flag
#endif
#if BSP_PRV_PLL2_SUPPORTED
    [CGC_CLOCK_PLL2] = 0U,             // PLL2 has a stabilization wait flag
#endif
};

/***********************************************************************************************************************
 * Global Variables
 **********************************************************************************************************************/

const cgc_api_t g_cgc_on_cgc =
{
    .open                 = R_CGC_Open,
    .clocksCfg            = R_CGC_ClocksCfg,
    .clockStart           = R_CGC_ClockStart,
    .clockStop            = R_CGC_ClockStop,
    .clockCheck           = R_CGC_ClockCheck,
    .systemClockSet       = R_CGC_SystemClockSet,
    .systemClockGet       = R_CGC_SystemClockGet,
    .oscStopDetectEnable  = R_CGC_OscStopDetectEnable,
    .oscStopDetectDisable = R_CGC_OscStopDetectDisable,
    .oscStopStatusClear   = R_CGC_OscStopStatusClear,
    .callbackSet          = R_CGC_CallbackSet,
    .close                = R_CGC_Close,
};

/*******************************************************************************************************************//**
 * @addtogroup CGC
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Initialize the CGC API.  Implements @ref cgc_api_t::open.
 *
 * Example:
 * @snippet r_cgc_example.c R_CGC_Open
 *
 * @retval FSP_SUCCESS              CGC successfully initialized.
 * @retval FSP_ERR_ASSERTION        Invalid input argument.
 * @retval FSP_ERR_ALREADY_OPEN     Module is already open.
 **********************************************************************************************************************/
fsp_err_t R_CGC_Open (cgc_ctrl_t * const p_ctrl, cgc_cfg_t const * const p_cfg)
{
    cgc_instance_ctrl_t * p_instance_ctrl = (cgc_instance_ctrl_t *) p_ctrl;

#if CGC_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_cfg);
    FSP_ERROR_RETURN(CGC_OPEN != p_instance_ctrl->open, FSP_ERR_ALREADY_OPEN);
#endif

    /* Store the control structure in a private global variable so the oscillation stop detection function can be
     * called from the NMI callback. */
    gp_cgc_ctrl                        = p_instance_ctrl;
    p_instance_ctrl->p_callback        = p_cfg->p_callback;
    p_instance_ctrl->p_context         = p_cfg->p_context;
    p_instance_ctrl->p_callback_memory = NULL;

    /* Mark the module as open so other APIs can be used. */
    p_instance_ctrl->open = CGC_OPEN;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Reconfigures all main system clocks.  This API can be used for any of the following purposes:
 *   - start or stop clocks
 *   - change the system clock source
 *   - configure the PLL/PLL2 multiplication and division ratios when starting the PLL
 *   - change the system dividers
 *
 * If the requested system clock source has a stabilization flag, this function blocks waiting for the stabilization
 * flag of the requested system clock source to be set.  If the requested system clock source was just started and it
 * has no stabilization flag, this function blocks for the stabilization time required by the requested system clock
 * source according to the Electrical Characteristics section of the hardware manual.  If the requested system clock
 * source has no stabilization flag and it is already running, it is assumed to be stable and this function will not
 * block.  If the requested system clock is the subclock, the subclock must be stable prior to calling this function.
 *
 * The internal dividers (cgc_clocks_cfg_t::divider_cfg) are subject to constraints described in footnotes of the
 * hardware manual table detailing specifications for the clock generation circuit for the internal clocks for the MCU.
 * For example:
 *   - RA6M3: see footnotes of Table 9.2 "Specifications of the clock generation circuit for the internal clocks" in
 *     the RA6M3 manual R01UH0886EJ0100
 *   - RA2A1: see footnotes of Table 9.2 "Clock generation circuit specifications for the internal clocks" in the RA2A1
 *     manual R01UH0888EJ0100
 *
 * Do not attempt to stop the requested clock source or the source of a PLL if the PLL will be running after this
 * operation completes.
 *
 * Implements @ref cgc_api_t::clocksCfg.
 *
 * Example:
 * @snippet r_cgc_example.c R_CGC_ClocksCfg
 *
 * @retval FSP_SUCCESS                  Clock configuration applied successfully.
 * @retval FSP_ERR_ASSERTION            Invalid input argument.
 * @retval FSP_ERR_NOT_OPEN             Module is not open.
 * @retval FSP_ERR_IN_USE               Attempt to stop the current system clock or the PLL source clock.
 * @retval FSP_ERR_CLOCK_ACTIVE         PLL configuration cannot be changed while PLL is running.
 * @retval FSP_ERR_OSC_STOP_DET_ENABLED PLL multiplier must be less than 20 if oscillation stop detect is enabled and
 *                                      the input frequency is less than 12.5 MHz.
 * @retval FSP_ERR_NOT_STABILIZED       PLL clock source is not stable.
 * @retval FSP_ERR_PLL_SRC_INACTIVE     PLL clock source is not running.
 * @retval FSP_ERR_INVALID_STATE        The subclock must be running before activating HOCO with FLL.
 **********************************************************************************************************************/
fsp_err_t R_CGC_ClocksCfg (cgc_ctrl_t * const p_ctrl, cgc_clocks_cfg_t const * const p_clock_cfg)
{
    cgc_instance_ctrl_t * p_instance_ctrl = (cgc_instance_ctrl_t *) p_ctrl;

    fsp_err_t err = FSP_SUCCESS;
    FSP_PARAMETER_NOT_USED(err);       // unused in some build configurations
#if CGC_CFG_PARAM_CHECKING_ENABLE
    err = r_cgc_common_parameter_checking(p_instance_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    FSP_ASSERT(NULL != p_clock_cfg);

 #if 0 == BSP_FEATURE_CGC_EXECUTE_FROM_LOCO
    FSP_ASSERT(CGC_CLOCK_LOCO != p_clock_cfg->system_clock);
 #endif

    /* Check dividers. */
    err = r_cgc_check_config_dividers(&p_clock_cfg->divider_cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#else
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
#endif

    cgc_clock_t requested_system_clock = p_clock_cfg->system_clock;
    cgc_clock_t current_system_clock   = (cgc_clock_t) R_SYSTEM->SCKSCR;

    cgc_clock_change_t options[CGC_PRV_NUM_CLOCKS];
    options[CGC_CLOCK_HOCO]     = p_clock_cfg->hoco_state;
    options[CGC_CLOCK_LOCO]     = p_clock_cfg->loco_state;
    options[CGC_CLOCK_MOCO]     = p_clock_cfg->moco_state;
    options[CGC_CLOCK_MAIN_OSC] = p_clock_cfg->mainosc_state;
    options[CGC_CLOCK_SUBCLOCK] = CGC_CLOCK_CHANGE_NONE;
#if CGC_CFG_PARAM_CHECKING_ENABLE
 #if BSP_CFG_USE_LOW_VOLTAGE_MODE

    /* HOCO must be running in low voltage mode. */
    FSP_ASSERT(CGC_CLOCK_CHANGE_STOP != p_clock_cfg->hoco_state);
 #endif
 #if BSP_PRV_HOCO_USE_FLL

    /* Determine if HOCO will be started. */
  #if BSP_PRV_PLL2_SUPPORTED
    uint8_t start_hoco = (CGC_CLOCK_CHANGE_START == p_clock_cfg->hoco_state) ||
                         ((CGC_CLOCK_CHANGE_START == p_clock_cfg->pll_state) &&
                          (CGC_CLOCK_HOCO == p_clock_cfg->pll_cfg.source_clock)) ||
                         ((CGC_CLOCK_CHANGE_START == p_clock_cfg->pll2_state) &&
                          (CGC_CLOCK_HOCO == p_clock_cfg->pll2_cfg.source_clock));
  #else
    uint8_t start_hoco = (CGC_CLOCK_CHANGE_START == p_clock_cfg->hoco_state) ||
                         ((CGC_CLOCK_CHANGE_START == p_clock_cfg->pll_state) &&
                          (CGC_CLOCK_HOCO == p_clock_cfg->pll_cfg.source_clock));
  #endif

    /* Subclock must be running to use FLL. */
    FSP_ERROR_RETURN(!(start_hoco && R_SYSTEM->SOSCCR), FSP_ERR_INVALID_STATE);
 #endif
#endif
#if BSP_PRV_PLL_SUPPORTED
    options[CGC_CLOCK_PLL] = p_clock_cfg->pll_state;

    /* The PLL source variable is used to prevent stopping the PLL source if the PLL is the current system clock until
     * after the system clock is changed.  Set PLL source to subclock if PLL source is not used since the subclock
     * cannot be changed in this function. */
    cgc_clock_t current_pll_source = CGC_CLOCK_SUBCLOCK;
    bool        pll_active         = r_cgc_clock_run_state_get(CGC_CLOCK_PLL);
    if (pll_active)
    {
        current_pll_source = r_cgc_pll_clocksource_get();
    }

    uint32_t pll_hz = 0U;
    uint32_t pllccr = 0U;
    if (CGC_CLOCK_CHANGE_START == p_clock_cfg->pll_state)
    {
 #if 3U == BSP_FEATURE_CGC_PLLCCR_TYPE
        err = r_cgc_pllccr_pll_hz_calculate(&p_clock_cfg->pll_cfg, CGC_CLOCK_PLL, CGC_PRV_PLLOUT_P, &pll_hz, &pllccr);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

        err = r_cgc_pllccr_pll_hz_calculate(&p_clock_cfg->pll_cfg, CGC_CLOCK_PLL, CGC_PRV_PLLOUT_Q, &pll_hz, &pllccr);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

        err = r_cgc_pllccr_pll_hz_calculate(&p_clock_cfg->pll_cfg, CGC_CLOCK_PLL, CGC_PRV_PLLOUT_R, &pll_hz, &pllccr);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
 #else
        err = r_cgc_pllccr_pll_hz_calculate(&p_clock_cfg->pll_cfg, CGC_CLOCK_PLL, CGC_PRV_PLLOUT_P, &pll_hz, &pllccr);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
 #endif
    }

 #if CGC_CFG_PARAM_CHECKING_ENABLE

    /* Check the PLL parameters if starting the PLL. */
    if (CGC_CLOCK_CHANGE_START == p_clock_cfg->pll_state)
    {
        err =
            r_cgc_pll_parameter_check(&p_clock_cfg->pll_cfg,
                                      (CGC_CLOCK_CHANGE_START != options[p_clock_cfg->pll_cfg.source_clock]));
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }
 #endif
#endif

#if BSP_PRV_PLL2_SUPPORTED
    options[CGC_CLOCK_PLL2] = p_clock_cfg->pll2_state;

    uint32_t pll2_hz = 0U;
    uint32_t pll2ccr = 0U;
    if (CGC_CLOCK_CHANGE_START == p_clock_cfg->pll2_state)
    {
 #if 3U == BSP_FEATURE_CGC_PLLCCR_TYPE
        err =
            r_cgc_pllccr_pll_hz_calculate(&p_clock_cfg->pll2_cfg, CGC_CLOCK_PLL2, CGC_PRV_PLLOUT_P, &pll2_hz, &pll2ccr);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

        err =
            r_cgc_pllccr_pll_hz_calculate(&p_clock_cfg->pll2_cfg, CGC_CLOCK_PLL2, CGC_PRV_PLLOUT_Q, &pll2_hz, &pll2ccr);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

        err =
            r_cgc_pllccr_pll_hz_calculate(&p_clock_cfg->pll2_cfg, CGC_CLOCK_PLL2, CGC_PRV_PLLOUT_R, &pll2_hz, &pll2ccr);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
 #else
        err =
            r_cgc_pllccr_pll_hz_calculate(&p_clock_cfg->pll2_cfg, CGC_CLOCK_PLL2, CGC_PRV_PLLOUT_P, &pll2_hz, &pll2ccr);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
 #endif
    }

 #if CGC_CFG_PARAM_CHECKING_ENABLE

    /* Check the PLL2 parameters if starting PLL2. */
    if (CGC_CLOCK_CHANGE_START == p_clock_cfg->pll2_state)
    {
        err =
            r_cgc_pll_parameter_check(&p_clock_cfg->pll2_cfg,
                                      (CGC_CLOCK_CHANGE_START != options[p_clock_cfg->pll2_cfg.source_clock]));
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }
 #endif
#endif

#if CGC_CFG_PARAM_CHECKING_ENABLE

    /* Do not attempt to stop the new system clock. */
    FSP_ERROR_RETURN(CGC_CLOCK_CHANGE_STOP != options[p_clock_cfg->system_clock], FSP_ERR_IN_USE);
 #if BSP_PRV_PLL_SUPPORTED

    /* Do not attempt to stop the source of the PLL if the PLL will be running after this operation completes. */
    if (CGC_CLOCK_CHANGE_STOP != options[CGC_CLOCK_PLL])
    {
        if ((CGC_CLOCK_CHANGE_START == options[CGC_CLOCK_PLL]) || pll_active)
        {
            FSP_ERROR_RETURN(CGC_CLOCK_CHANGE_STOP != options[p_clock_cfg->pll_cfg.source_clock], FSP_ERR_IN_USE);
        }
    }
 #endif
 #if BSP_PRV_PLL2_SUPPORTED

    /* Do not attempt to stop the source of PLL2 if PLL2 will be running after this operation completes. */
    if (CGC_CLOCK_CHANGE_STOP != options[CGC_CLOCK_PLL2])
    {
        if ((CGC_CLOCK_CHANGE_START == options[CGC_CLOCK_PLL2]) || r_cgc_clock_run_state_get(CGC_CLOCK_PLL2))
        {
            FSP_ERROR_RETURN(CGC_CLOCK_CHANGE_STOP != options[p_clock_cfg->pll2_cfg.source_clock], FSP_ERR_IN_USE);
        }
    }
 #endif
#endif

    /* Prerequisite to starting clocks or changing the system clock. */
    r_cgc_pre_change(CGC_PRV_CHANGE_LPM_CGC);

#if BSP_PRV_HOCO_USE_FLL
    if (CGC_CLOCK_CHANGE_START == p_clock_cfg->hoco_state)
    {
        /* If FLL is to be used set FLLCR1 before starting HOCO. */
        R_SYSTEM->FLLCR1 = 1U;
    }
#endif

#if BSP_PRV_PLL_SUPPORTED
    if (CGC_CLOCK_CHANGE_START == p_clock_cfg->pll_state)
    {
        /* Configure PLL and store PLL frequency in BSP. */
        r_cgc_pll_cfg(pll_hz, pllccr);

 #if 3U == BSP_FEATURE_CGC_PLLCCR_TYPE

        /* Configure the output clock dividers. */
        uint32_t outdiv =
            (((p_clock_cfg->pll_cfg.out_div_p - 1U) & CGC_PRV_PLLCCR2_PLODIVX_MASK) << CGC_PRV_PLLCCR2_PLODIVP_BIT) |
            (((p_clock_cfg->pll_cfg.out_div_q - 1U) & CGC_PRV_PLLCCR2_PLODIVX_MASK) << CGC_PRV_PLLCCR2_PLODIVQ_BIT) |
            (((p_clock_cfg->pll_cfg.out_div_r - 1U) & CGC_PRV_PLLCCR2_PLODIVX_MASK) << CGC_PRV_PLLCCR2_PLODIVR_BIT);
        R_SYSTEM->PLLCCR2 = (uint16_t) outdiv;
 #endif

        if (CGC_CLOCK_CHANGE_START == options[p_clock_cfg->pll_cfg.source_clock])
        {
            /* Need to start PLL source clock and let it stabilize before starting PLL. */
            r_cgc_clock_change(p_clock_cfg->pll_cfg.source_clock, CGC_CLOCK_CHANGE_START);

 #if BSP_PRV_HOCO_USE_FLL
            if (CGC_CLOCK_HOCO == p_clock_cfg->pll_cfg.source_clock)
            {
                /* If FLL is enabled and HOCO is turned on an additional stabilization wait is required before
                 * checking the flag and starting the PLL. */
                R_BSP_SoftwareDelay(BSP_PRV_FLL_STABILIZATION_TIME_US, BSP_DELAY_UNITS_MICROSECONDS);
            }
 #endif

            FSP_HARDWARE_REGISTER_WAIT(r_cgc_clock_check(p_clock_cfg->pll_cfg.source_clock), FSP_SUCCESS);
        }
    }
#endif
#if BSP_PRV_PLL2_SUPPORTED
    if (CGC_CLOCK_CHANGE_START == p_clock_cfg->pll2_state)
    {
        /* Configure PLL2 and store frequency in BSP. */
        R_SYSTEM->PLL2CCR = (uint16_t) pll2ccr;

 #if 3U == BSP_FEATURE_CGC_PLLCCR_TYPE

        /* Configure the output clock dividers. */
        uint32_t outdiv =
            (((p_clock_cfg->pll2_cfg.out_div_p - 1) & CGC_PRV_PLLCCR2_PLODIVX_MASK) << CGC_PRV_PLLCCR2_PLODIVP_BIT) |
            (((p_clock_cfg->pll2_cfg.out_div_q - 1) & CGC_PRV_PLLCCR2_PLODIVX_MASK) << CGC_PRV_PLLCCR2_PLODIVQ_BIT) |
            (((p_clock_cfg->pll2_cfg.out_div_r - 1) & CGC_PRV_PLLCCR2_PLODIVX_MASK) << CGC_PRV_PLLCCR2_PLODIVR_BIT);
        R_SYSTEM->PLL2CCR2 = (uint16_t) outdiv;
 #endif

        if (CGC_CLOCK_CHANGE_START == options[p_clock_cfg->pll_cfg.source_clock])
        {
            /* Need to start PLL source clock and let it stabilize before starting PLL. */
            r_cgc_clock_change(p_clock_cfg->pll2_cfg.source_clock, CGC_CLOCK_CHANGE_START);

 #if BSP_PRV_HOCO_USE_FLL
            if (CGC_CLOCK_HOCO == p_clock_cfg->pll2_cfg.source_clock)
            {
                /* If FLL is enabled and HOCO is turned on an additional stabilization wait is required before
                 * checking the flag and starting PLL2. */
                R_BSP_SoftwareDelay(BSP_PRV_FLL_STABILIZATION_TIME_US, BSP_DELAY_UNITS_MICROSECONDS);
            }
 #endif

            FSP_HARDWARE_REGISTER_WAIT(r_cgc_clock_check(p_clock_cfg->pll2_cfg.source_clock), FSP_SUCCESS);
        }
    }
#endif

    /* Start or stop clocks based on the input configuration. Start with PLL clock, so it can be stopped before trying
     * to stop the PLL source clock. */
    for (int32_t i = (CGC_PRV_NUM_CLOCKS - 1); i >= 0; i--)
    {
        cgc_clock_change_t clock_state     = options[i];
        cgc_clock_t        clock_to_change = (cgc_clock_t) i;
        if (CGC_CLOCK_CHANGE_STOP == clock_state)
        {
            /* Current system clock and current PLL source will be stopped after changing the system clock. */
            if ((current_system_clock != clock_to_change)
#if BSP_PRV_PLL_SUPPORTED
                && (current_pll_source != clock_to_change)
#endif
                )
            {
                r_cgc_clock_change(clock_to_change, CGC_CLOCK_CHANGE_STOP);
            }
        }

        if (CGC_CLOCK_CHANGE_START == clock_state)
        {
            r_cgc_clock_change(clock_to_change, CGC_CLOCK_CHANGE_START);
        }
    }

#if BSP_PRV_HOCO_USE_FLL
    if (CGC_CLOCK_CHANGE_STOP == p_clock_cfg->hoco_state)
    {
        /* If HOCO is disabled then disable FLL as well. */
        R_SYSTEM->FLLCR1 = 0U;
    }
#endif

    /* Verify the requested clock is stable if it has a stabilization flag. */
    FSP_HARDWARE_REGISTER_WAIT(r_cgc_clock_check(requested_system_clock), FSP_SUCCESS);

    /* If the requested clock is not the subclock and it was just started and it has no stabilization flag, wait
     * for the required stabilization time in software. */
    if (g_cgc_software_wait_us[requested_system_clock] > 0U)
    {
        if (options[requested_system_clock] == CGC_CLOCK_CHANGE_START)
        {
            R_BSP_SoftwareDelay(g_cgc_software_wait_us[requested_system_clock], BSP_DELAY_UNITS_MICROSECONDS);
        }
    }

    /* Set which clock to use for system clock and dividers for all system clocks. */
    cgc_divider_cfg_t clock_cfg;
    clock_cfg.sckdivcr_w = p_clock_cfg->divider_cfg.sckdivcr_w;
#if BSP_FEATURE_CGC_HAS_CPUCLK
    clock_cfg.sckdivcr2 = p_clock_cfg->divider_cfg.sckdivcr2;
#else
    clock_cfg.sckdivcr2 = 0;
#endif
#if BSP_FEATURE_CGC_SCKDIVCR_BCLK_MATCHES_PCLKB

    /* Some MCUs require the bits normally used for BCLK to be set the same as PCLKB. */
    clock_cfg.sckdivcr_b.bclk_div = clock_cfg.sckdivcr_b.pclkb_div;
#endif
    bsp_prv_clock_set(requested_system_clock, clock_cfg.sckdivcr_w, clock_cfg.sckdivcr2);

    /* If the system clock has changed, stop previous system clock if requested. */
    if (requested_system_clock != current_system_clock)
    {
        if (CGC_CLOCK_CHANGE_STOP == options[current_system_clock])
        {
            r_cgc_clock_change(current_system_clock, CGC_CLOCK_CHANGE_STOP);

#if BSP_PRV_PLL_SUPPORTED

            /* This could stop the PLL source a second time, but it is more efficient than storing a variable to
             * remember if it needs to be stopped. */
            if (CGC_CLOCK_CHANGE_STOP == options[current_pll_source])
            {
                r_cgc_clock_change(current_pll_source, CGC_CLOCK_CHANGE_STOP);
            }
#endif
        }
    }

    /* Reduce the operating speed mode to the optimal setting for these clock configurations and restore the cache to
     * its previous state. */
    r_cgc_post_change(CGC_PRV_CHANGE_LPM_CGC);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Start the specified clock if it is not currently active. The PLL configuration cannot be changed while the PLL
 * is running. Implements @ref cgc_api_t::clockStart.
 *
 * The PLL source clock must be operating and stable prior to starting the PLL.
 *
 * Example:
 * @snippet r_cgc_example.c R_CGC_ClockStart
 *
 * @retval FSP_SUCCESS                  Clock initialized successfully.
 * @retval FSP_ERR_ASSERTION            Invalid input argument.
 * @retval FSP_ERR_NOT_OPEN             Module is not open.
 * @retval FSP_ERR_NOT_STABILIZED       The clock source is not stabilized after being turned off or PLL clock source
 *                                      is not stable.
 * @retval FSP_ERR_PLL_SRC_INACTIVE     PLL clock source is not running.
 * @retval FSP_ERR_CLOCK_ACTIVE         PLL configuration cannot be changed while PLL is running.
 * @retval FSP_ERR_OSC_STOP_DET_ENABLED PLL multiplier must be less than 20 if oscillation stop detect is enabled and
 *                                      the input frequency is less than 12.5 MHz.
 * @retval FSP_ERR_INVALID_STATE        The subclock must be running before activating HOCO with FLL.
 **********************************************************************************************************************/
fsp_err_t R_CGC_ClockStart (cgc_ctrl_t * const p_ctrl, cgc_clock_t clock_source, cgc_pll_cfg_t const * const p_pll_cfg)
{
    cgc_instance_ctrl_t * p_instance_ctrl = (cgc_instance_ctrl_t *) p_ctrl;

    fsp_err_t err = FSP_SUCCESS;
    FSP_PARAMETER_NOT_USED(err);       // unused in some build configurations
#if !BSP_PRV_PLL_SUPPORTED && !BSP_PRV_PLL2_SUPPORTED
    FSP_PARAMETER_NOT_USED(p_pll_cfg);
#endif
#if CGC_CFG_PARAM_CHECKING_ENABLE
    err = r_cgc_common_parameter_checking(p_instance_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

 #if !BSP_PRV_PLL_SUPPORTED
    FSP_ASSERT(CGC_CLOCK_PLL != clock_source);
 #endif
 #if !BSP_PRV_PLL2_SUPPORTED
    FSP_ASSERT(CGC_CLOCK_PLL2 != clock_source);
 #endif
 #if BSP_PRV_PLL_SUPPORTED
    if ((CGC_CLOCK_PLL == clock_source)
  #if BSP_PRV_PLL2_SUPPORTED
        || (CGC_CLOCK_PLL2 == clock_source)
  #endif
        )
    {
        /* p_pll_cfg is required to start PLL. */
        FSP_ASSERT(NULL != p_pll_cfg);

        err = r_cgc_pll_parameter_check(p_pll_cfg, true);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }
 #endif
 #if BSP_PRV_HOCO_USE_FLL
    FSP_ERROR_RETURN(!((CGC_CLOCK_HOCO == clock_source) && R_SYSTEM->SOSCCR), FSP_ERR_INVALID_STATE);
 #endif
#else
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
#endif

#if BSP_PRV_PLL_SUPPORTED
    uint32_t pll_hz;
    uint32_t pllccr;
    if ((CGC_CLOCK_PLL == clock_source)
 #if BSP_PRV_PLL2_SUPPORTED
        || (CGC_CLOCK_PLL2 == clock_source)
 #endif
        )
    {
 #if 3U == BSP_FEATURE_CGC_PLLCCR_TYPE
        err = r_cgc_pllccr_pll_hz_calculate(p_pll_cfg, clock_source, CGC_PRV_PLLOUT_P, &pll_hz, &pllccr);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

        err = r_cgc_pllccr_pll_hz_calculate(p_pll_cfg, clock_source, CGC_PRV_PLLOUT_Q, &pll_hz, &pllccr);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

        err = r_cgc_pllccr_pll_hz_calculate(p_pll_cfg, clock_source, CGC_PRV_PLLOUT_R, &pll_hz, &pllccr);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
 #else
        err = r_cgc_pllccr_pll_hz_calculate(p_pll_cfg, clock_source, CGC_PRV_PLLOUT_P, &pll_hz, &pllccr);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
 #endif
    }

    /* Make sure the oscillator is stable. */
    FSP_ERROR_RETURN(r_cgc_stabilization_check(clock_source, r_cgc_clock_run_state_get(clock_source)),
                     FSP_ERR_NOT_STABILIZED);
#endif

    /* Prerequisite to starting clocks or changing the system clock. */
    r_cgc_pre_change(CGC_PRV_CHANGE_LPM_CGC);

#if BSP_PRV_PLL_SUPPORTED
    if (CGC_CLOCK_PLL == clock_source)
    {
        r_cgc_pll_cfg(pll_hz, pllccr);
    }

 #if BSP_PRV_PLL2_SUPPORTED
    else if (CGC_CLOCK_PLL2 == clock_source)
    {
        R_SYSTEM->PLL2CCR = (uint16_t) pllccr;
    }
    else
    {
        /* Do nothing. */
    }
 #endif
#endif

#if BSP_PRV_HOCO_USE_FLL
    if (CGC_CLOCK_HOCO == clock_source)
    {
        /* If FLL is to be used set FLLCR1 before starting HOCO. */
        R_SYSTEM->FLLCR1 = 1U;
    }
#endif

    /* Start the clock. */
    r_cgc_clock_change(clock_source, CGC_CLOCK_CHANGE_START);

    /* Reduce the operating speed mode to the optimal setting for these clock configurations and restore the cache to
     * it's previous state. */
    r_cgc_post_change(CGC_PRV_CHANGE_LPM_CGC);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Stop the specified clock if it is active.  Implements @ref cgc_api_t::clockStop.
 *
 * Do not attempt to stop the current system clock source.  Do not attempt to stop the source clock of a PLL if the
 * PLL is running.
 *
 * @retval FSP_SUCCESS                      Clock stopped successfully.
 * @retval FSP_ERR_ASSERTION                Invalid input argument.
 * @retval FSP_ERR_NOT_OPEN                 Module is not open.
 * @retval FSP_ERR_IN_USE                   Attempt to stop the current system clock or the PLL source clock.
 * @retval FSP_ERR_OSC_STOP_DET_ENABLED     Attempt to stop MOCO when Oscillation stop is enabled.
 * @retval FSP_ERR_NOT_STABILIZED           Clock not stabilized after starting.
 **********************************************************************************************************************/
fsp_err_t R_CGC_ClockStop (cgc_ctrl_t * const p_ctrl, cgc_clock_t clock_source)
{
    cgc_instance_ctrl_t * p_instance_ctrl = (cgc_instance_ctrl_t *) p_ctrl;

#if CGC_CFG_PARAM_CHECKING_ENABLE

    /* Verify p_instance_ctrl is not NULL and the module is open. */
    fsp_err_t err = r_cgc_common_parameter_checking(p_instance_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

 #if BSP_CFG_USE_LOW_VOLTAGE_MODE

    /* HOCO must be running in low voltage mode. */
    FSP_ASSERT(CGC_CLOCK_HOCO != clock_source);
 #endif

    /* If clock source is the current system clock, return error */
    cgc_clock_t current_clock = (cgc_clock_t) R_SYSTEM->SCKSCR;
    FSP_ERROR_RETURN(clock_source != current_clock, FSP_ERR_IN_USE);

 #if BSP_PRV_PLL_SUPPORTED

    /* If PLL is operating, the PLL clock source cannot be stopped. */
    FSP_ERROR_RETURN(!((r_cgc_clock_run_state_get(CGC_CLOCK_PLL) && (r_cgc_pll_clocksource_get() == clock_source)))
  #if BSP_PRV_PLL2_SUPPORTED
                     && !((r_cgc_clock_run_state_get(CGC_CLOCK_PLL2) && (r_cgc_pll2_clocksource_get() == clock_source)))
  #endif
                     ,
                     FSP_ERR_IN_USE);
 #endif

    /* MOCO cannot be stopped if oscillation stop detection is enabled. */
    FSP_ERROR_RETURN(!((clock_source == CGC_CLOCK_MOCO) && (R_SYSTEM->OSTDCR_b.OSTDE == 1U)),
                     FSP_ERR_OSC_STOP_DET_ENABLED);

    /* Make sure the oscillator is stable. */
    FSP_ERROR_RETURN(r_cgc_stabilization_check(clock_source, r_cgc_clock_run_state_get(clock_source)),
                     FSP_ERR_NOT_STABILIZED);
#else
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
#endif

    /* Stop the clock. */
    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_CGC);
    r_cgc_clock_change(clock_source, CGC_CLOCK_CHANGE_STOP);

#if BSP_PRV_HOCO_USE_FLL

    /* FLL must be disabled after stopping HOCO. */
    if (CGC_CLOCK_HOCO == clock_source)
    {
        R_SYSTEM->FLLCR1 = 0U;
    }
#endif

    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_CGC);

#if !BSP_CFG_USE_LOW_VOLTAGE_MODE

    /* Reduce the operating speed mode if possible based on the new clock configuration. */
    r_cgc_pre_change(CGC_PRV_CHANGE_LPM);
    r_cgc_operating_mode_reduce(R_SYSTEM->SCKDIVCR);
    r_cgc_post_change(CGC_PRV_CHANGE_LPM);
#endif

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Set the specified clock as the system clock and configure the internal dividers for ICLK, PCLKA, PCLKB, PCLKC,
 * PCLKD, BCLK, and FCLK.  Implements @ref cgc_api_t::systemClockSet.
 *
 * The requested clock source must be running and stable prior to calling this function.  The internal dividers are
 * subject to constraints described in the hardware manual table "Specifications of the Clock Generation Circuit for
 * the internal clocks".
 *
 * The internal dividers (p_divider_cfg) are subject to constraints described in footnotes of the hardware manual table
 * detailing specifications for the clock generation circuit for the internal clocks for the MCU.
 * For example:
 *   - RA6M3: see footnotes of Table 9.2 "Specifications of the clock generation circuit for the internal clocks" in
 *     the RA6M3 manual R01UH0886EJ0100
 *   - RA2A1: see footnotes of Table 9.2 "Clock generation circuit specifications for the internal clocks" in the RA2A1
 *     manual R01UH0888EJ0100
 *
 * This function also updates the RAM and ROM wait states, the operating power control mode, and the SystemCoreClock
 * CMSIS global variable.
 *
 * Example:
 * @snippet r_cgc_example.c R_CGC_SystemClockSet
 *
 * @retval FSP_SUCCESS                  Operation performed successfully.
 * @retval FSP_ERR_ASSERTION            Invalid input argument.
 * @retval FSP_ERR_NOT_OPEN             Module is not open.
 * @retval FSP_ERR_CLOCK_INACTIVE       The specified clock source is inactive.
 * @retval FSP_ERR_NOT_STABILIZED       The clock source has not stabilized
 **********************************************************************************************************************/
fsp_err_t R_CGC_SystemClockSet (cgc_ctrl_t * const              p_ctrl,
                                cgc_clock_t                     clock_source,
                                cgc_divider_cfg_t const * const p_divider_cfg)
{
    cgc_instance_ctrl_t * p_instance_ctrl = (cgc_instance_ctrl_t *) p_ctrl;

#if CGC_CFG_PARAM_CHECKING_ENABLE

    /* Verify p_instance_ctrl is not NULL and the module is open. */
    fsp_err_t err = r_cgc_common_parameter_checking(p_instance_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    FSP_ASSERT(NULL != p_divider_cfg);

 #if 0 == BSP_FEATURE_CGC_EXECUTE_FROM_LOCO
    FSP_ASSERT(CGC_CLOCK_LOCO != clock_source);
 #endif

    /* Check divider constraints. */
    err = r_cgc_check_config_dividers(p_divider_cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Confirm the requested clock is stable. */
    err = r_cgc_clock_check(clock_source);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#else
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
#endif

    /* Prerequisite to starting clocks or changing the system clock. */
    r_cgc_pre_change(CGC_PRV_CHANGE_LPM_CGC);

    cgc_divider_cfg_t clock_cfg;
    clock_cfg.sckdivcr_w = p_divider_cfg->sckdivcr_w;
#if BSP_FEATURE_CGC_HAS_CPUCLK
    clock_cfg.sckdivcr2 = p_divider_cfg->sckdivcr2;
#else
    clock_cfg.sckdivcr2 = 0;
#endif

#if BSP_FEATURE_CGC_SCKDIVCR_BCLK_MATCHES_PCLKB

    /* Some MCUs require the bits normally used for BCLK to be set the same as PCLKB. */
    clock_cfg.sckdivcr_b.bclk_div = clock_cfg.sckdivcr_b.pclkb_div;
#endif

    bsp_prv_clock_set(clock_source, clock_cfg.sckdivcr_w, clock_cfg.sckdivcr2);

    /* Apply the optimal operating power mode and restore the cache to it's previous state. */
    r_cgc_post_change(CGC_PRV_CHANGE_LPM_CGC);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Return the current system clock source and configuration.  Implements @ref cgc_api_t::systemClockGet.
 *
 * @retval FSP_SUCCESS                 Parameters returned successfully.
 * @retval FSP_ERR_ASSERTION           Invalid input argument.
 * @retval FSP_ERR_NOT_OPEN            Module is not open.
 **********************************************************************************************************************/
fsp_err_t R_CGC_SystemClockGet (cgc_ctrl_t * const        p_ctrl,
                                cgc_clock_t * const       p_clock_source,
                                cgc_divider_cfg_t * const p_divider_cfg)
{
    cgc_instance_ctrl_t * p_instance_ctrl = (cgc_instance_ctrl_t *) p_ctrl;

#if CGC_CFG_PARAM_CHECKING_ENABLE

    /* Verify p_instance_ctrl is not NULL and the module is open. */
    fsp_err_t err = r_cgc_common_parameter_checking(p_instance_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#else
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
#endif

    /* Get the system clock source */
    if (NULL != p_clock_source)
    {
        *p_clock_source = (cgc_clock_t) R_SYSTEM->SCKSCR;
    }

    /* Get current dividers. */
    if (NULL != p_divider_cfg)
    {
        p_divider_cfg->sckdivcr_w = R_SYSTEM->SCKDIVCR;

#if BSP_FEATURE_CGC_HAS_CPUCLK
        p_divider_cfg->sckdivcr2 = R_SYSTEM->SCKDIVCR2;
#endif
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Check the specified clock for stability.  Implements @ref cgc_api_t::clockCheck.
 *
 * @retval FSP_SUCCESS                 Clock is running and stable.
 * @retval FSP_ERR_ASSERTION           Invalid input argument.
 * @retval FSP_ERR_NOT_OPEN            Module is not open.
 * @retval FSP_ERR_NOT_STABILIZED      Clock not stabilized.
 * @retval FSP_ERR_CLOCK_INACTIVE      Clock not turned on.
 **********************************************************************************************************************/
fsp_err_t R_CGC_ClockCheck (cgc_ctrl_t * const p_ctrl, cgc_clock_t clock_source)
{
    cgc_instance_ctrl_t * p_instance_ctrl = (cgc_instance_ctrl_t *) p_ctrl;
    fsp_err_t             err;

#if CGC_CFG_PARAM_CHECKING_ENABLE

    /* Verify p_instance_ctrl is not NULL and the module is open. */
    err = r_cgc_common_parameter_checking(p_instance_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#else
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
#endif

    /* Ensure the clock is running and stable. */
    err = r_cgc_clock_check(clock_source);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Enable the oscillation stop detection for the main clock.  Implements @ref cgc_api_t::oscStopDetectEnable.
 *
 * The MCU will automatically switch the system clock to MOCO when a stop is detected if Main Clock is
 * the system clock. If the system clock is the PLL, then the clock source will not be changed and the
 * PLL free running frequency will be the system clock frequency.
 *
 * Example:
 * @snippet r_cgc_example.c R_CGC_OscStopDetectEnable
 *
 * @retval FSP_SUCCESS                 Operation performed successfully.
 * @retval FSP_ERR_ASSERTION           Invalid input argument.
 * @retval FSP_ERR_NOT_OPEN            Module is not open.
 * @retval FSP_ERR_LOW_VOLTAGE_MODE    Settings not allowed in low voltage mode.
 **********************************************************************************************************************/
fsp_err_t R_CGC_OscStopDetectEnable (cgc_ctrl_t * const p_ctrl)
{
    cgc_instance_ctrl_t * p_instance_ctrl = (cgc_instance_ctrl_t *) p_ctrl;

#if CGC_CFG_PARAM_CHECKING_ENABLE

    /* Verify p_instance_ctrl is not NULL and the module is open. */
    fsp_err_t err = r_cgc_common_parameter_checking(p_instance_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

 #if defined(BSP_TZ_NONSECURE_BUILD) && BSP_TZ_NONSECURE_BUILD

    /* The NMI must be configured to TrustZone Non-secure in order to be used in a Non-secure project. */
    FSP_ASSERT(0U != (SCB->AIRCR & SCB_AIRCR_BFHFNMINS_Msk));
 #elif defined(BSP_TZ_SECURE_BUILD) && BSP_TZ_SECURE_BUILD

    /* The NMI must be configured to TrustZone Secure in order to be used in a Secure project. */
    FSP_ASSERT(0U == (SCB->AIRCR & SCB_AIRCR_BFHFNMINS_Msk));
 #endif
#else
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
#endif

    /* Low speed and low voltage mode have divider restrictions when using oscillation stop detection. */
#if BSP_CFG_USE_LOW_VOLTAGE_MODE
    FSP_ERROR_RETURN(r_cgc_low_speed_or_voltage_mode_possible(R_SYSTEM->SCKDIVCR, CGC_PRV_OSTDCR_OSC_STOP_ENABLE),
                     FSP_ERR_LOW_VOLTAGE_MODE);
#else

    /* When low voltage mode is not used, switch to the next available power mode if currently in low speed mode and
     * this mode is not supported when oscillation stop is enabled to ensure the operating power control mode remains
     * in spec. */
    uint32_t operating_mode = R_SYSTEM->OPCCR_b.OPCM;
    uint32_t sckdivcr       = R_SYSTEM->SCKDIVCR;
    if (operating_mode == BSP_PRV_OPERATING_MODE_LOW_SPEED)
    {
        if (!(r_cgc_low_speed_or_voltage_mode_possible(sckdivcr, CGC_PRV_OSTDCR_OSC_STOP_ENABLE)))
        {
            r_cgc_pre_change(CGC_PRV_CHANGE_LPM);
            bsp_prv_operating_mode_set(CGC_PRV_EXIT_LOW_SPEED_MODE);
            r_cgc_post_change(CGC_PRV_CHANGE_LPM);
        }
    }
#endif

    /* Add callback function to BSP */
    (void) R_BSP_GroupIrqWrite(BSP_GRP_IRQ_OSC_STOP_DETECT, r_cgc_nmi_internal_callback);

    /* Enable the oscillation stop NMI.  */

    /* Set OSTEN bit to enable NMI on oscillation stop detection. NMIER bits cannot be cleared after reset, so no need
     * to read-modify-write. */
    R_ICU->NMIER = R_ICU_NMIER_OSTEN_Msk;

    /* Enable oscillation stop detection */
    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_CGC);
    R_SYSTEM->OSTDCR = CGC_PRV_OSTDCR_OSC_STOP_ENABLE;
    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_CGC);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Disable the oscillation stop detection for the main clock.  Implements @ref cgc_api_t::oscStopDetectDisable.
 *
 * Example:
 * @snippet r_cgc_example.c R_CGC_OscStopDetectDisable
 *
 * @retval FSP_SUCCESS                 Operation performed successfully.
 * @retval FSP_ERR_ASSERTION           Invalid input argument.
 * @retval FSP_ERR_NOT_OPEN            Module is not open.
 * @retval FSP_ERR_OSC_STOP_DETECTED   The Oscillation stop detect status flag is set. Under this condition it is not
 *                                     possible to disable the Oscillation stop detection function.
 **********************************************************************************************************************/
fsp_err_t R_CGC_OscStopDetectDisable (cgc_ctrl_t * const p_ctrl)
{
    cgc_instance_ctrl_t * p_instance_ctrl = (cgc_instance_ctrl_t *) p_ctrl;

#if CGC_CFG_PARAM_CHECKING_ENABLE

    /* Verify p_instance_ctrl is not NULL and the module is open. */
    fsp_err_t err = r_cgc_common_parameter_checking(p_instance_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* If the oscillation stop flag is set, oscillation stop cannot be disabled. */
    FSP_ERROR_RETURN((R_SYSTEM->OSTDSR != 1U), FSP_ERR_OSC_STOP_DETECTED);
#else
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
#endif

    /* Disable oscillation stop detection. */
    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_CGC);
    R_SYSTEM->OSTDCR = 0U;             // disable osc stop detection
    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_CGC);

#if !BSP_CFG_USE_LOW_VOLTAGE_MODE

    /* Attempt to reduce the operating power control mode. */
    r_cgc_pre_change(CGC_PRV_CHANGE_LPM);
    r_cgc_operating_mode_reduce(R_SYSTEM->SCKDIVCR);
    r_cgc_post_change(CGC_PRV_CHANGE_LPM);
#endif

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Clear the Oscillation Stop Detection Status register.  This register is not cleared automatically if the stopped
 * clock is restarted.  Implements @ref cgc_api_t::oscStopStatusClear.
 *
 * After clearing the status, oscillation stop detection is no longer enabled.
 *
 * This register cannot be cleared while the main oscillator is the system clock or the PLL source clock.
 *
 * Example:
 * @snippet r_cgc_example.c R_CGC_OscStopStatusClear
 *
 * @retval FSP_SUCCESS                      Operation performed successfully.
 * @retval FSP_ERR_ASSERTION                Invalid input argument.
 * @retval FSP_ERR_NOT_OPEN                 Module is not open.
 * @retval FSP_ERR_CLOCK_INACTIVE           Main oscillator must be running to clear the oscillation stop detection
 *                                          flag.
 * @retval FSP_ERR_OSC_STOP_CLOCK_ACTIVE    The Oscillation Detect Status flag cannot be cleared if the
 *                                          Main Osc or PLL is set as the system clock. Change the
 *                                          system clock before attempting to clear this bit.
 * @retval FSP_ERR_INVALID_HW_CONDITION     Oscillation stop status was not cleared.  Check preconditions and try again.
 **********************************************************************************************************************/
fsp_err_t R_CGC_OscStopStatusClear (cgc_ctrl_t * const p_ctrl)
{
    cgc_instance_ctrl_t * p_instance_ctrl = (cgc_instance_ctrl_t *) p_ctrl;

#if CGC_CFG_PARAM_CHECKING_ENABLE

    /* Verify p_instance_ctrl is not NULL and the module is open. */
    fsp_err_t err = r_cgc_common_parameter_checking(p_instance_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#else
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
#endif

    if (R_SYSTEM->OSTDSR == 1U)
    {
#if CGC_CFG_PARAM_CHECKING_ENABLE

        /* Verify the main oscillator is running. */
        FSP_ERROR_RETURN(CGC_PRV_CLOCK_STATE_RUNNING == r_cgc_clock_run_state_get(CGC_CLOCK_MAIN_OSC),
                         FSP_ERR_CLOCK_INACTIVE);

        /* Get the system clock source */
        cgc_clock_t current_clock = (cgc_clock_t) R_SYSTEM->SCKSCR;

 #if BSP_PRV_PLL_SUPPORTED
  #if 1U == BSP_FEATURE_CGC_PLLCCR_TYPE || 3U == BSP_FEATURE_CGC_PLLCCR_TYPE

        /* Oscillation stop status cannot be cleared if PLL is the current source clock and main oscillator is the
         * source of the PLL. */
        FSP_ERROR_RETURN(!((CGC_CLOCK_PLL == current_clock) && (0U == R_SYSTEM->PLLCCR_b.PLSRCSEL)),
                         FSP_ERR_OSC_STOP_CLOCK_ACTIVE);
  #else

        /* Oscillation stop status cannot be cleared if PLL is the current source clock. */
        FSP_ERROR_RETURN(!(CGC_CLOCK_PLL == current_clock), FSP_ERR_OSC_STOP_CLOCK_ACTIVE);
  #endif
 #endif

        /* Oscillation stop status cannot be cleared if the main oscillator is the current source clock. */
        FSP_ERROR_RETURN(!(CGC_CLOCK_MAIN_OSC == current_clock), FSP_ERR_OSC_STOP_CLOCK_ACTIVE);
#endif

        /* Clear the oscillation stop status flag. */
        R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_CGC);
        R_SYSTEM->OSTDCR = 0U;
        R_SYSTEM->OSTDSR = 0U;
        R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_CGC);

        /* At least 3 ICLK cycles of wait time are required between writing 0 to OSTDF and reading it as 0 (see section
         * 8.2.13 "Oscillation Stop Detection Status Register (OSTDSR)" of the RA6M3 manual. The call to enable register
         * protection for CGC registers above takes more than 3 ICLK cycles. */

        /* Verify the flag was cleared (see Figure 9.12 "Flow of recovery on detection of oscillator stop" of the RA6M3
         * manual R01UH0886EJ0100). If not, return an error. */
        FSP_ERROR_RETURN(0U == R_SYSTEM->OSTDSR, FSP_ERR_INVALID_HW_CONDITION);
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Updates the user callback and has option of providing memory for callback structure.
 * Implements cgc_api_t::callbackSet
 *
 * @retval  FSP_SUCCESS                  Callback updated successfully.
 * @retval  FSP_ERR_ASSERTION            A required pointer is NULL.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened.
 * @retval  FSP_ERR_NO_CALLBACK_MEMORY   p_callback is non-secure and p_callback_memory is either secure or NULL.
 **********************************************************************************************************************/
fsp_err_t R_CGC_CallbackSet (cgc_ctrl_t * const          p_api_ctrl,
                             void (                    * p_callback)(cgc_callback_args_t *),
                             void const * const          p_context,
                             cgc_callback_args_t * const p_callback_memory)
{
    cgc_instance_ctrl_t * p_ctrl = (cgc_instance_ctrl_t *) p_api_ctrl;

#if BSP_TZ_SECURE_BUILD
    bool callback_is_secure =
        (NULL == cmse_check_address_range((void *) p_callback, sizeof(void *), CMSE_AU_NONSECURE));
#endif

#if CGC_CFG_PARAM_CHECKING_ENABLE

    /* Verify p_ctrl is not NULL and the module is open. */
    fsp_err_t err = r_cgc_common_parameter_checking(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Verify that the callback is not NULL. */
    FSP_ASSERT(NULL != p_callback);

 #if BSP_TZ_SECURE_BUILD

    /* In secure projects, p_callback_memory must be provided in non-secure space if p_callback is non-secure */
    cgc_callback_args_t * const p_callback_memory_checked = cmse_check_pointed_object(p_callback_memory,
                                                                                      CMSE_AU_NONSECURE);
    FSP_ERROR_RETURN(callback_is_secure || (NULL != p_callback_memory_checked), FSP_ERR_NO_CALLBACK_MEMORY);
 #endif
#endif

#if BSP_TZ_SECURE_BUILD
    p_ctrl->p_callback = callback_is_secure ? p_callback :
                         (void (*)(cgc_callback_args_t *))cmse_nsfptr_create(p_callback);
#else
    p_ctrl->p_callback = p_callback;
#endif
    p_ctrl->p_context         = p_context;
    p_ctrl->p_callback_memory = p_callback_memory;

    return FSP_SUCCESS;
}

/******************************************************************************************************************//**
 * Closes the CGC module.  Implements @ref cgc_api_t::close.
 *
 * @retval FSP_SUCCESS                 The module is successfully closed.
 * @retval FSP_ERR_ASSERTION           Invalid input argument.
 * @retval FSP_ERR_NOT_OPEN            Module is not open.
 **********************************************************************************************************************/
fsp_err_t R_CGC_Close (cgc_ctrl_t * const p_ctrl)
{
    cgc_instance_ctrl_t * p_instance_ctrl = (cgc_instance_ctrl_t *) p_ctrl;

#if CGC_CFG_PARAM_CHECKING_ENABLE

    /* Verify p_instance_ctrl is not NULL and the module is open. */
    fsp_err_t err = r_cgc_common_parameter_checking(p_instance_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#endif

    p_instance_ctrl->open = 0U;

    /* All done, return success. */
    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup CGC)
 **********************************************************************************************************************/

#if CGC_CFG_PARAM_CHECKING_ENABLE

/*******************************************************************************************************************//**
 * Verifies the control structure is not NULL and the module is open. This reduces code size when the error logger is
 * used.
 *
 * @param[in]  p_instance_ctrl          Pointer to instance control structure.
 *
 * @retval FSP_SUCCESS                  No error detected.
 * @retval FSP_ERR_ASSERTION            Invalid input argument.
 * @retval FSP_ERR_NOT_OPEN             Module is not open.
 **********************************************************************************************************************/
static fsp_err_t r_cgc_common_parameter_checking (cgc_instance_ctrl_t * p_instance_ctrl)
{
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(CGC_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);

    return FSP_SUCCESS;
}

#endif

/*******************************************************************************************************************//**
 * Sets operating mode to high speed mode, unlocks CGC and LPM protection registers, disables the flash cache, and
 * returns the previous state of the flash cache.  Must be paired with r_cgc_post_change().
 *
 * @param[in]  change                  Whether or not to enter high speed mode and unprotect CGC registers.
 *
 * @return Cache state to restore
 **********************************************************************************************************************/
static void r_cgc_pre_change (cgc_prv_change_t change)
{
#if !BSP_CFG_USE_LOW_VOLTAGE_MODE
 #if BSP_FEATURE_BSP_FLASH_CACHE_DISABLE_OPM

    /* Disable flash cache. */
    R_BSP_FlashCacheDisable();
 #endif

    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_OM_LPC_BATT);
#endif
    if (CGC_PRV_CHANGE_LPM_CGC == change)
    {
#if !BSP_CFG_USE_LOW_VOLTAGE_MODE

        /* Switch to high-speed to prevent any issues with the subsequent system clock change. */
        bsp_prv_operating_mode_set(BSP_PRV_OPERATING_MODE_HIGH_SPEED);
#endif
        R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_CGC);
    }
}

/*******************************************************************************************************************//**
 * Reduces operating speed mode to the optimal value based on current configurations, locks CGC and LPM protection
 * registers, and restores the cache state.  Must be paired with r_cgc_pre_change().
 *
 * @param[in]  change                  Whether or not to protect CGC registers.
 **********************************************************************************************************************/
static void r_cgc_post_change (cgc_prv_change_t change)
{
    /* Set the operating speed mode based on the new system clock source */
    if (CGC_PRV_CHANGE_LPM_CGC == change)
    {
        R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_CGC);
#if !BSP_CFG_USE_LOW_VOLTAGE_MODE
        r_cgc_operating_mode_reduce(R_SYSTEM->SCKDIVCR);
#endif
    }

#if !BSP_CFG_USE_LOW_VOLTAGE_MODE
    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_OM_LPC_BATT);
 #if BSP_FEATURE_BSP_FLASH_CACHE_DISABLE_OPM && BSP_FEATURE_BSP_FLASH_CACHE
    R_BSP_FlashCacheEnable();
 #endif
#endif
}

#if !BSP_CFG_USE_LOW_VOLTAGE_MODE && BSP_FEATURE_CGC_HAS_SOPCCR

/*******************************************************************************************************************//**
 * Verifies if Subosc speed mode is possible
 *
 * @param[in] sckdivcr                 Requested SCKDIVCR register setting
 *
 * @return  true if subosc speed mode is can be used based on current clock configurations
 **********************************************************************************************************************/
static bool r_cgc_subosc_mode_possible (uint32_t sckdivcr)
{
    /* Subosc speed mode is only supported on the LOCO or the subclock. */
    if (CGC_PRV_SUBCLOCK_LOCO_HZ != SystemCoreClock)
    {
        return false;
    }

    /* If the stop bit is cleared for HOCO, MOCO, MOSC, or PLL, subosc speed mode is not possible. All of these clocks
     * must be stopped to enter subosc speed mode. */
    if ((((!R_SYSTEM->HOCOCR) || (!R_SYSTEM->MOCOCR)) || (!R_SYSTEM->MOSCCR))
 #if BSP_PRV_PLL_SUPPORTED
        || (!R_SYSTEM->PLLCR)
 #endif
 #if BSP_PRV_PLL2_SUPPORTED
        || (!R_SYSTEM->PLL2CR)
 #endif
        )
    {
        return false;
    }

    /* If the ICLK or FCLK divider is not 1, sub-oscillator mode is not possible. */
    if (0U != (sckdivcr & CGC_PRV_SCKDIVCR_ICLK_FCLK_MASK))
    {
        return false;
    }

    return true;
}

#endif

/*******************************************************************************************************************//**
 * Verifies divisor, oscillation stop, and PLL settings to determine if low-speed or low-voltage mode is possible.
 * Maximum frequency must be verified outside this function. Checks if low voltage mode is possible if
 * BSP_CFG_USE_LOW_VOLTAGE_MODE is set, otherwise checks if low speed mode is possible.
 *
 * @param[in] sckdivcr                 Requested SCKDIVCR register setting
 * @param[in] ostdcr                   Requested OSTDCR register setting
 *
 * @return  true if the requested mode can be used based on the specified clock configurations
 **********************************************************************************************************************/
static bool r_cgc_low_speed_or_voltage_mode_possible (uint32_t sckdivcr, uint8_t ostdcr)
{
#if BSP_CFG_USE_LOW_VOLTAGE_MODE

    /* HOCO must be operating in low voltage mode. */
    if (0U != R_SYSTEM->HOCOCR)
    {
        return false;
    }
#endif

    /* When oscillation stop detection is enabled, clock division of 1, 2, 4, or 8 is prohibited for all clocks in
     * low speed mode. The remaining dividers (16, 32, and 64) all have the upper bit of the bitfield set. */
    if (0U != ostdcr)
    {
        uint32_t test = sckdivcr;
#if BSP_CFG_USE_LOW_VOLTAGE_MODE

        /* When oscillation stop detection is enabled, clock division of 1 or 2 is prohibited for all clocks in
         * low voltage mode. The remaining dividers (4, 8, 16, 32, and 64) all have either bit 2 or bit 1 of
         * the bitfield set. */
        test = sckdivcr | (sckdivcr << 1);
#endif
        if ((CGC_PRV_SCKDIVCR_UPPER_BIT & test) != CGC_PRV_SCKDIVCR_UPPER_BIT)
        {
            return false;
        }
    }

#if BSP_PRV_PLL_SUPPORTED

    /* Low speed mode is only possible if the PLL is stopped. */
    return (bool) R_SYSTEM->PLLCR
 #if BSP_PRV_PLL2_SUPPORTED
           || R_SYSTEM->PLL2CR
 #endif
    ;
#else                                  /* BSP_PRV_PLL_SUPPORTED */
    return true;
#endif
}

#if !BSP_CFG_USE_LOW_VOLTAGE_MODE

/*******************************************************************************************************************//**
 * Sets the optimum operating speed mode based on the current system clock.
 *
 * @param[in] sckdivcr                 Requested SCKDIVCR register setting
 **********************************************************************************************************************/
static void r_cgc_operating_mode_reduce (uint32_t sckdivcr)
{
    uint8_t ostdcr = R_SYSTEM->OSTDCR;

 #if BSP_FEATURE_CGC_HAS_SOPCCR

    /* Switch to subosc-speed mode if possible. */
    if (r_cgc_subosc_mode_possible(sckdivcr))
    {
        /* Switch to sub oscillator mode */
        bsp_prv_operating_mode_set(BSP_PRV_OPERATING_MODE_SUBOSC_SPEED);
    }
    else
 #endif

    /* Switch to low-speed mode if possible. */
    if (r_cgc_low_speed_or_voltage_mode_possible(sckdivcr, ostdcr) &&
        (SystemCoreClock <= BSP_FEATURE_CGC_LOW_SPEED_MAX_FREQ_HZ))
    {
        /* Switch to low speed mode */
        bsp_prv_operating_mode_set(BSP_PRV_OPERATING_MODE_LOW_SPEED);
    }

 #if BSP_FEATURE_CGC_MIDDLE_SPEED_MAX_FREQ_HZ > 0U

    /* Switch to middle-speed mode if the ICLK frequency supports it. */
    else if (SystemCoreClock <= BSP_FEATURE_CGC_MIDDLE_SPEED_MAX_FREQ_HZ)
    {
        bsp_prv_operating_mode_set(BSP_PRV_OPERATING_MODE_MIDDLE_SPEED);
    }
 #endif
    else
    {
        /* Do nothing, remain in high speed mode. */
    }
}

#endif

/*******************************************************************************************************************//**
 * Check if the specified clock is running and stable
 *
 * @param[in]   clock_source           Clock to be verified
 *
 * @retval FSP_SUCCESS                 Clock is running and stable.
 * @retval FSP_ERR_NOT_STABILIZED      Clock not stabilized.
 * @retval FSP_ERR_CLOCK_INACTIVE      Clock not turned on.
 **********************************************************************************************************************/
static fsp_err_t r_cgc_clock_check (cgc_clock_t const clock_source)
{
    cgc_prv_clock_state_t running = r_cgc_clock_run_state_get(clock_source);

    /* Ensure the clock is stable if the clock has a stabilization flag. */
    FSP_ERROR_RETURN(r_cgc_stabilization_check(clock_source, running), FSP_ERR_NOT_STABILIZED);

    /* Ensure the clock is running. */
    FSP_ERROR_RETURN(running, FSP_ERR_CLOCK_INACTIVE);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * This function returns the run state of the selected clock
 *
 * @param[in]  clock   Clock to check
 *
 * @return  1 if running, 0 if stopped
 **********************************************************************************************************************/
static cgc_prv_clock_state_t r_cgc_clock_run_state_get (cgc_clock_t clock)
{

    /* Get clock run state. */
    return (cgc_prv_clock_state_t) !(*gp_cgc_clock_stp_registers[clock]);
}

/*******************************************************************************************************************//**
 * This function checks the selected clock for stability.
 *
 * @param[in]  clock   Clock to check
 * @param[in]  status  Current state of the clock
 *
 * @return true if stable or the clock has no stability flag, false if not stable
 **********************************************************************************************************************/
static bool r_cgc_stabilization_check (cgc_clock_t clock, cgc_prv_clock_state_t status)
{
    /* MOCO, LOCO, and subclock have no stabilization flags, so return true if the clock is any of these. */
    uint32_t bitmask_moco_loco_subclock =
        ((1U << CGC_CLOCK_MOCO) | (1U << CGC_CLOCK_LOCO) | (1U << CGC_CLOCK_SUBCLOCK));
    if (bitmask_moco_loco_subclock & (1U << clock))
    {
        return true;
    }

    /*  Check for stability of selected clock. */
    uint32_t oscsf     = R_SYSTEM->OSCSF;
    uint32_t oscsf_bit = (oscsf >> clock) & 1U;

    return oscsf_bit == (uint32_t) status;
}

/*******************************************************************************************************************//**
 * This function starts or stops the selected clock.  Do not call this subroutine with CGC_CLOCK_CHANGE_NONE.
 *
 * @param[in]  clock   Clock to start or stop
 * @param[in]  state   1 to stop clock, 0 to start clock
 **********************************************************************************************************************/
static void r_cgc_clock_change (cgc_clock_t clock, cgc_clock_change_t state)
{
    *gp_cgc_clock_stp_registers[clock] = (uint8_t) state;

    /* Wait setting to be reflected in hardware registers. */
    FSP_HARDWARE_REGISTER_WAIT(*gp_cgc_clock_stp_registers[clock], state);

#if BSP_FEATURE_BSP_HAS_SYRACCR
    if (CGC_CLOCK_LOCO == clock)
    {
        /* MREF_INTERNAL_003 */
        FSP_HARDWARE_REGISTER_WAIT(R_SYSTEM->SYRACCR, 0);
    }
#endif
}

#if CGC_CFG_PARAM_CHECKING_ENABLE

/*******************************************************************************************************************//**
 * Check divider values against hardware manual constraints.
 *
 * @param[in]   p_divider_cfg            Pointer to clock divider configuration
 *
 * @retval      FSP_SUCCESS              Dividers satisfy hardware manual constraints.
 * @retval      FSP_ERR_ASSERTION        One or more divider values do not satisfy constraints specified in the
 *                                       hardware manual.
 **********************************************************************************************************************/
static fsp_err_t r_cgc_check_config_dividers (cgc_divider_cfg_t const * const p_divider_cfg)
{
    FSP_PARAMETER_NOT_USED(p_divider_cfg); // unused if FSP_ASSERT is compiled out
 #if BSP_FEATURE_CGC_HAS_PCLKA

    /* Check dividers against hardware constraints (see footnotes of Table 9.2 "Specifications of the clock generation
     * circuit for the internal clocks" in the RA6M3 manual R01UH0886EJ0100). */

    /* ICLK frequency must be >= PCLKA, so ICLK divider must be <= PCLKA. */
    FSP_ASSERT(p_divider_cfg->sckdivcr_b.iclk_div <= p_divider_cfg->sckdivcr_b.pclka_div);

    /* PCLKA frequency must be >= PCLKB, so PCLKA divider must be <= PCLKB. */
    FSP_ASSERT(p_divider_cfg->sckdivcr_b.pclka_div <= p_divider_cfg->sckdivcr_b.pclkb_div);

    /* PCLKD frequency must be >= PCLKA, so PCLKD divider must be <= PCLKA. */
    FSP_ASSERT(p_divider_cfg->sckdivcr_b.pclkd_div <= p_divider_cfg->sckdivcr_b.pclka_div);
 #elif BSP_FEATURE_CGC_HAS_PCLKB

    /* Check dividers against hardware constraints (see footnotes of Table 9.2 "Clock generation circuit specifications
     * for the internal clocks" in the RA2A1 manual R01UH0888EJ0100). */

    /* ICLK frequency must be >= PCLKB, so ICLK divider must be <= PCLKB. */
    FSP_ASSERT(p_divider_cfg->sckdivcr_b.iclk_div <= p_divider_cfg->sckdivcr_b.pclkb_div);

    /* PCLKD frequency must be >= PCLKB, so PCLKD divider must be <= PCLKB. */
    FSP_ASSERT(p_divider_cfg->sckdivcr_b.pclkd_div <= p_divider_cfg->sckdivcr_b.pclkb_div);
 #endif

 #if BSP_FEATURE_CGC_HAS_FCLK

    /* ICLK frequency must be >= FCLK, so ICLK divider must be <= FCLK. */
    FSP_ASSERT(p_divider_cfg->sckdivcr_b.iclk_div <= p_divider_cfg->sckdivcr_b.fclk_div);
 #endif

 #if BSP_FEATURE_CGC_HAS_BCLK

    /* ICLK frequency must be >= BCLK, so ICLK divider must be <= BCLK. */
    FSP_ASSERT(p_divider_cfg->sckdivcr_b.iclk_div <= p_divider_cfg->sckdivcr_b.bclk_div);
 #endif

 #if BSP_FEATURE_CGC_HAS_CPUCLK

    /* CPUCLK divider must be less than or equal to ICLK divider. */
    FSP_ASSERT(p_divider_cfg->sckdivcr2_b.cpuclk_div <= p_divider_cfg->sckdivcr_b.iclk_div);
 #endif

    return FSP_SUCCESS;
}

#endif

#if CGC_CFG_PARAM_CHECKING_ENABLE
 #if BSP_PRV_PLL_SUPPORTED

/*******************************************************************************************************************//**
 * Check PLL configuration against hardware manual constraints. Also verify the PLL source clock is running and stable
 * if requested.
 *
 * @param[in]   p_pll_cfg              Pointer to PLL configuration
 * @param[in]   verify_source_stable   Whether or not to verify the source clock is running and stable
 *
 * @retval FSP_SUCCESS                   PLL configuration satisfies hardware manual constraints.
 * @retval FSP_ERR_ASSERTION             One or more divider PLL configurations do not satisfy constraints specified
 *                                       in the hardware manual.
 * @retval FSP_ERR_OSC_STOP_DET_ENABLED  PLL multiplier must be less than 20 if oscillation stop detect is enabled and
 *                                       the input frequency is less than 12.5 MHz.
 * @retval FSP_ERR_PLL_SRC_INACTIVE      PLL clock source is not running.
 * @retval FSP_ERR_NOT_STABILIZED        PLL clock source is not stable.
 **********************************************************************************************************************/
static fsp_err_t r_cgc_pll_parameter_check (cgc_pll_cfg_t const * const p_pll_cfg, bool verify_source_stable)
{
  #if 1U == BSP_FEATURE_CGC_PLLCCR_TYPE

    /* Ensure PLL configuration is supported on this MCU (see Section 9.2.4 "PLL Clock Control Register (PLLCCR)" in the
     * RA6M3 manual R01UH0886EJ0100). */

    /* PLLCCR clock source can only be main oscillator or HOCO. */
    FSP_ASSERT((CGC_CLOCK_MAIN_OSC == p_pll_cfg->source_clock) || (CGC_CLOCK_HOCO == p_pll_cfg->source_clock));

    /* Divider of 4 is not supported for PLLCCR. */
    FSP_ASSERT(CGC_PLL_DIV_4 != p_pll_cfg->divider);

    /* PLLCCR multiplier must be between 10 and 30. */
    FSP_ASSERT(p_pll_cfg->multiplier >= CGC_PLL_MUL_10_0);
    FSP_ASSERT(p_pll_cfg->multiplier <= CGC_PLL_MUL_30_0);

   #if BSP_CFG_XTAL_HZ < 12000000

    /* PLLMUL must be 20 or less if oscillation stop detect is enabled and the input frequency is less than 12 MHz. HOCO
     * cannot run at less than 16 MHz, so this only applies for the main oscillator. */
    if (R_SYSTEM->OSTDCR_b.OSTDE == 1U)
    {
        if (CGC_CLOCK_MAIN_OSC == p_pll_cfg->source_clock)
        {
            FSP_ERROR_RETURN(p_pll_cfg->multiplier <= CGC_PLL_MUL_20_0, FSP_ERR_OSC_STOP_DET_ENABLED);
        }
    }
   #endif
  #elif 3U == BSP_FEATURE_CGC_PLLCCR_TYPE

    /* Ensure PLL configuration is supported on this MCU (MREF_INTERNAL_004). */

    /* PLLCCR clock source can only be main oscillator or HOCO. */
    FSP_ASSERT((CGC_CLOCK_MAIN_OSC == p_pll_cfg->source_clock) || (CGC_CLOCK_HOCO == p_pll_cfg->source_clock));

    /* Divider of 4 is not supported for PLLCCR. */
    FSP_ASSERT(CGC_PLL_DIV_4 != p_pll_cfg->divider);

    /* PLLCCR multiplier must be between 26.00 and 180.50.
     * 180.50 is larger than 180.66 in the integer representation of the enum. */
    FSP_ASSERT(p_pll_cfg->multiplier >= CGC_PLL_MUL_26_0);
    FSP_ASSERT(p_pll_cfg->multiplier <= CGC_PLL_MUL_180_5);
  #elif 4U == BSP_FEATURE_CGC_PLLCCR_TYPE

    /* Ensure PLL configuration is supported on this MCU (MREF_INTERNAL_006). */

    /* PLLCCR clock source can only be the subclock. */
    FSP_ASSERT(CGC_CLOCK_SUBCLOCK == p_pll_cfg->source_clock);

    /* Divider of 2 is the only supported value for PLLCCR. */
    FSP_ASSERT(CGC_PLL_DIV_2 == p_pll_cfg->divider);

    /* PLLCCR multiplier must be between 732 and 781. */
    FSP_ASSERT(p_pll_cfg->multiplier >= CGC_PLL_MUL_732_0);
    FSP_ASSERT(p_pll_cfg->multiplier <= CGC_PLL_MUL_781_0);
  #else

    /* Ensure PLL configuration is supported on this MCU (see Section 8.2.3 "PLL Clock Control Register 2 (PLLCCR2)" in
     * the RA4M1 manual R01UH0887EJ0100). */

    /* PLLCCR2 clock source can only be main oscillator. */
    FSP_ASSERT(CGC_CLOCK_MAIN_OSC == p_pll_cfg->source_clock);

    /* Only dividers of 2 and 4 supported for PLLCCR2. */
    FSP_ASSERT((CGC_PLL_DIV_2 == p_pll_cfg->divider) || (CGC_PLL_DIV_4 == p_pll_cfg->divider));

    /* Only integer multipliers are supported for PLLCCR2. Integer multipliers have the lowest bit set in the enum
     * value. */
    FSP_ASSERT(1U == (p_pll_cfg->multiplier & 1U));
  #endif

    if (verify_source_stable)
    {
        /* If the PLL source clock isn't running, the PLL cannot be started. */
        FSP_ERROR_RETURN(CGC_PRV_CLOCK_STATE_RUNNING == r_cgc_clock_run_state_get(p_pll_cfg->source_clock),
                         FSP_ERR_PLL_SRC_INACTIVE);

        /* Make sure the PLL source is stable before starting the PLL. */
        FSP_ERROR_RETURN((r_cgc_stabilization_check(p_pll_cfg->source_clock, CGC_PRV_CLOCK_STATE_RUNNING)),
                         FSP_ERR_NOT_STABILIZED);
    }

    return FSP_SUCCESS;
}

 #endif
#endif

#if BSP_PRV_PLL_SUPPORTED

/*******************************************************************************************************************//**
 * Calculates the new PLL frequency.
 *
 * @param[in]  p_pll_cfg               PLL configuration
 * @param[in]  pll_out                 PLL output clock
 * @param[out] p_pll_hz                Pointer to store PLL frequency in Hz
 *
 * @retval FSP_SUCCESS                 Requested PLL configuration meets hardware manual requirements.
 * @retval FSP_ERR_ASSERTION           Requested PLL configuration violates hardware manual constraints.
 **********************************************************************************************************************/
static fsp_err_t r_cgc_pll_hz_calculate (cgc_pll_cfg_t const * const p_pll_cfg,
                                         cgc_prv_pllout_t            pll_out,
                                         uint32_t * const            p_pll_hz)
{
    /* Calculate the PLL frequency and set PLLCCR. The PLL frequency is required to update SystemCoreClock after
     * switching to PLL. */
    uint32_t pll_src_freq_hz = BSP_CFG_XTAL_HZ;
 #if 1U == BSP_FEATURE_CGC_PLLCCR_TYPE
    FSP_PARAMETER_NOT_USED(pll_out);

    if (CGC_CLOCK_HOCO == p_pll_cfg->source_clock)
    {
        pll_src_freq_hz = BSP_HOCO_HZ;
    }

    /* The nominal values of the PLL multiplier are equal to (the PLLMUL bitfield + 1) / 2.
     * The highest value for PLLMUL + 1 is 60, and the maximum PLL source clock is 24 MHz.
     * 60 * 24000000 = 1440000000 = 0x55D4A800, which does not overflow 32-bits.
     */
    uint32_t clock_freq_multiplied = (pll_src_freq_hz * (p_pll_cfg->multiplier + 1U)) >> 1;
    uint32_t divider               = p_pll_cfg->divider + 1U;

    uint32_t pll_hz = clock_freq_multiplied / divider;

  #if CGC_CFG_PARAM_CHECKING_ENABLE

    /* The PLL output frequency must be between 120 MHz and 240 MHz on most MCUs (see Table 9.1 "Specifications of the
     * clock generation circuit for the clock sources" in the RA6M3 manual R01UH0886EJ0100). */
    FSP_ASSERT(pll_hz >= CGC_PRV_PLLCCR_PLL_MIN_HZ);
    FSP_ASSERT(pll_hz <= BSP_FEATURE_CGC_PLLCCR_MAX_HZ);
  #endif
 #elif 3U == BSP_FEATURE_CGC_PLLCCR_TYPE
    if (CGC_CLOCK_HOCO == p_pll_cfg->source_clock)
    {
        pll_src_freq_hz = BSP_HOCO_HZ;
    }

    /* The multiplier can have a fractional component of either 1/3, 2/3, or 1/2. All of
     * these fractions have a common multiple of 6, so scale the multiplier by that value. */
    uint32_t multiplier = ((p_pll_cfg->multiplier >> BSP_PRV_CLOCKS_PLL_MUL_INT_SHIFT) + 1) * CGC_PRV_PLL_MUL_COEFF;
    uint8_t  fractional = (uint8_t) (p_pll_cfg->multiplier & BSP_PRV_CLOCKS_PLL_MUL_FRAC_MASK);

    /* Convert the MULNF value to use a common multiple of 6. */
    if (fractional < 3U)
    {
        /* Values for 1/3 and 2/3 are 1 and 2 respectivly therefore it only needs a coefficient of 2 applied. */
        fractional *= CGC_PRV_PLL_MUL_NF_COEFF;
    }
    else
    {
        /* Do nothing: the value of 1/2 is 3 so it will work without a coeficient being applied (3/6 = 1/2). */
    }

    /* Add the fractional value into the scaled integer multiplier. */
    multiplier += fractional;

    /* The highest value for PLLMUL + 1 is 180, the highest fraction for PLLMULNF is 0.66, and the maximum PLL source
     * clock is 48 MHz. The VCO frequency can be calculated to be more than 32-bits.
     */
    uint64_t clock_freq_multiplied = ((uint64_t) pll_src_freq_hz * (uint64_t) multiplier) / CGC_PRV_PLL_MUL_FACTOR;
    uint32_t divider               = p_pll_cfg->divider + 1U;

    uint64_t vco_hz = clock_freq_multiplied / divider;

  #if CGC_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(vco_hz <= BSP_FEATURE_CGC_PLLCCR_VCO_MAX_HZ);
  #endif

    uint32_t pll_hz = 0;
    if (CGC_PRV_PLLOUT_P == pll_out)
    {
        pll_hz = (uint32_t) (vco_hz / p_pll_cfg->out_div_p);
    }
    else if (CGC_PRV_PLLOUT_Q == pll_out)
    {
        pll_hz = (uint32_t) (vco_hz / p_pll_cfg->out_div_q);
    }
    else if (CGC_PRV_PLLOUT_R == pll_out)
    {
        pll_hz = (uint32_t) (vco_hz / p_pll_cfg->out_div_r);
    }
    else
    {
        /* Do nothing */
    }

  #if CGC_CFG_PARAM_CHECKING_ENABLE

    /* The PLL output frequency must be between 40 MHz and 480 MHz for this PLL type. */
    FSP_ASSERT(pll_hz >= CGC_PRV_PLLCCR_PLL_MIN_HZ);
    FSP_ASSERT(pll_hz <= BSP_FEATURE_CGC_PLLCCR_MAX_HZ);
  #endif
 #elif 4U == BSP_FEATURE_CGC_PLLCCR_TYPE

    /* Normal P,Q,R outputs are not supported. */
    FSP_PARAMETER_NOT_USED(pll_out);

    /* PLLCCR type 4 only supports the subclock as a source. */
    pll_src_freq_hz = BSP_SUB_CLOCK_HZ;

    uint32_t multiplier            = (p_pll_cfg->multiplier + BSP_PRV_CLOCKS_PLL_MUL_INT_OFFSET);
    uint32_t clock_freq_multiplied = pll_src_freq_hz * multiplier;

    uint32_t pll_hz = clock_freq_multiplied >> 1; // Always div-by-2 for this PLLCCR type.
 #else                                            // 2U == BSP_FEATURE_CGC_PLLCCR_TYPE
    FSP_PARAMETER_NOT_USED(pll_out);

    uint32_t multiplier            = (p_pll_cfg->multiplier + 1U) >> 1;
    uint32_t clock_freq_multiplied = pll_src_freq_hz * multiplier;
    uint32_t divider_shift         = p_pll_cfg->divider;
    if (CGC_PLL_DIV_4 == p_pll_cfg->divider)
    {
        divider_shift = 2;
    }

    uint32_t pll_hz = clock_freq_multiplied >> divider_shift;

  #if CGC_CFG_PARAM_CHECKING_ENABLE

    /* The following restrictions apply to the PLL on this MCU (see Table 8.1 "Clock generation circuit specifications
     * for the clock sources" in the RA4M1 manual R01UH0887EJ0100):
     *   - The PLL input frequency must be between 4 MHz and 12.5 MHz.
     *   - The maximum frequency after multiplication is 128 MHz.
     *   - The minimum frequency is 24 MHz.
     */
    FSP_ASSERT(
        (pll_src_freq_hz <= CGC_PRV_PLLCCR2_PLL_SRC_MAX_HZ) && (pll_src_freq_hz >= CGC_PRV_PLLCCR2_PLL_SRC_MIN_HZ));
    FSP_ASSERT(clock_freq_multiplied <= CGC_PRV_PLLCCR2_PLL_MULTIPLIED_MAX_HZ);
    FSP_ASSERT(pll_hz >= CGC_PRV_PLLCCR2_PLL_MIN_HZ);
  #endif
 #endif

    /* Store the calculated frequency in the provided pointer if there are no violations. */
    *p_pll_hz = pll_hz;

    return FSP_SUCCESS;
}

#endif

#if BSP_PRV_PLL_SUPPORTED

/*******************************************************************************************************************//**
 * Calculate PLL registers for PLL clock start
 *
 * @param[in]   p_pll_cfg               Pointer to clock system configuration
 *
 * @return PLLCCR register value
 **********************************************************************************************************************/
static uint32_t r_cgc_pllccr_calculate (cgc_pll_cfg_t const * const p_pll_cfg)
{
    /* Set the PLL control register. */
 #if 1U == BSP_FEATURE_CGC_PLLCCR_TYPE
    uint16_t plsrcsel = 0U;
    if (CGC_CLOCK_HOCO == p_pll_cfg->source_clock)
    {
        plsrcsel = 1U;
    }

    uint16_t pllmul         = (uint16_t) p_pll_cfg->multiplier;
    uint16_t plidiv         = (uint16_t) p_pll_cfg->divider;
    uint32_t register_value = ((((pllmul & CGC_PRV_PLLCCR_PLLMUL_MASK) << CGC_PRV_PLLCCR_PLLMUL_BIT) |
                                (uint32_t) (plsrcsel << CGC_PRV_PLLCCR_PLSRCSEL_BIT)) | plidiv);

    return register_value;
 #elif 3U == BSP_FEATURE_CGC_PLLCCR_TYPE
    uint16_t plsrcsel = 0U;
    if (CGC_CLOCK_HOCO == p_pll_cfg->source_clock)
    {
        plsrcsel = 1U;
    }

    uint16_t pllmul         = (uint16_t) (p_pll_cfg->multiplier >> BSP_PRV_CLOCKS_PLL_MUL_INT_SHIFT);
    uint16_t pllmulnf       = (uint16_t) (p_pll_cfg->multiplier & BSP_PRV_CLOCKS_PLL_MUL_FRAC_MASK);
    uint16_t plidiv         = (uint16_t) p_pll_cfg->divider;
    uint32_t register_value = ((((pllmul & CGC_PRV_PLLCCR_PLLMUL_MASK) << CGC_PRV_PLLCCR_PLLMUL_BIT) |
                                ((pllmulnf & CGC_PRV_PLLCCR_PLLMULNF_MASK) << CGC_PRV_PLLCCR_PLLMULNF_BIT) |
                                (uint32_t) (plsrcsel << CGC_PRV_PLLCCR_PLSRCSEL_BIT)) | plidiv);

    return register_value;
 #elif 4U == BSP_FEATURE_CGC_PLLCCR_TYPE
    uint8_t pllmul = (uint8_t) ((p_pll_cfg->multiplier >> 1) - CGC_PRV_PLLCCR_TYPE4_PLLMUL_OFFSET);

    uint32_t register_value = ((pllmul & CGC_PRV_PLLCCR_PLLMUL_MASK) << CGC_PRV_PLLCCR_PLLMUL_BIT);

    return register_value;
 #else                                 // 2U == BSP_FEATURE_CGC_PLLCCR_TYPE
    uint8_t pllmul = (uint8_t) p_pll_cfg->multiplier >> 1;
    uint8_t plodiv = (uint8_t) p_pll_cfg->divider;
    if (CGC_PLL_DIV_4 == p_pll_cfg->divider)
    {
        plodiv = 2U;
    }

    uint32_t register_value =
        ((pllmul & CGC_PRV_PLLCCR2_PLLMUL_MASK) | (uint32_t) (plodiv << CGC_PRV_PLLCCR2_PLODIV_BIT));

    return register_value;
 #endif
}

#endif

#if BSP_PRV_PLL_SUPPORTED

/*******************************************************************************************************************//**
 * This function returns the PLL clock source.
 *
 * @return PLL clock source
 **********************************************************************************************************************/
static inline cgc_clock_t r_cgc_pll_clocksource_get (void)
{
    /*  PLL source selection only available on PLLCCR */
    cgc_clock_t pll_src = CGC_CLOCK_MAIN_OSC;
 #if 1U == BSP_FEATURE_CGC_PLLCCR_TYPE || 3U == BSP_FEATURE_CGC_PLLCCR_TYPE

    /* Get the PLL clock source */
    if (R_SYSTEM->PLLCCR_b.PLSRCSEL == 1U)
    {
        pll_src = CGC_CLOCK_HOCO;
    }

 #elif 4U == BSP_FEATURE_CGC_PLLCCR_TYPE
    pll_src = CGC_CLOCK_SUBCLOCK;
 #endif

    return pll_src;
}

#endif

#if BSP_PRV_PLL2_SUPPORTED && CGC_CFG_PARAM_CHECKING_ENABLE

/*******************************************************************************************************************//**
 * This function returns the PLL2 clock source.
 *
 * @return PLL2 clock source
 **********************************************************************************************************************/
static inline cgc_clock_t r_cgc_pll2_clocksource_get (void)
{
    return R_SYSTEM->PLL2CCR_b.PL2SRCSEL == 1U ? CGC_CLOCK_HOCO : CGC_CLOCK_MAIN_OSC;
}

#endif

#if BSP_PRV_PLL_SUPPORTED

/*******************************************************************************************************************//**
 * Calculate requested PLL frequency and PLLCCR value.
 *
 * @param[in]   p_pll_cfg               Pointer to clock system configuration.
 * @param[in]   pll                     PLL to be configured (if PLL2 is supported).
 * @param[in]   pll_out                 PLL output clock selection (P, Q, or R).
 * @param[out]  p_pll_hz                Pointer to store calculated PLL output frequency.
 * @param[out]  p_pllccr                Pointer to store calculated PLLCCR value.
 *
 * @retval FSP_SUCCESS                  No errors detected in PLL configuration.
 * @retval FSP_ERR_ASSERTION            Invalid input argument.
 * @retval FSP_ERR_CLOCK_ACTIVE         PLL configuration cannot be changed while PLL is running.
 **********************************************************************************************************************/
static fsp_err_t r_cgc_pllccr_pll_hz_calculate (cgc_pll_cfg_t const * const p_pll_cfg,
                                                cgc_clock_t                 pll,
                                                cgc_prv_pllout_t            pll_out,
                                                uint32_t * const            p_pll_hz,
                                                uint32_t * const            p_pllccr)
{
 #if !BSP_PRV_PLL2_SUPPORTED
    FSP_PARAMETER_NOT_USED(pll);
 #endif

    /* Calculate the PLLCCR register. */
    uint32_t pllccr = r_cgc_pllccr_calculate(p_pll_cfg);

 #if 1U == BSP_FEATURE_CGC_PLLCCR_TYPE || 3U == BSP_FEATURE_CGC_PLLCCR_TYPE || 4U == BSP_FEATURE_CGC_PLLCCR_TYPE
    volatile uint16_t * p_pllccr_reg;
 #else
    volatile uint8_t * p_pllccr_reg;
 #endif

 #if BSP_PRV_PLL2_SUPPORTED
    if (CGC_CLOCK_PLL == pll)
 #endif
    {
 #if 1U == BSP_FEATURE_CGC_PLLCCR_TYPE || 3U == BSP_FEATURE_CGC_PLLCCR_TYPE || 4U == BSP_FEATURE_CGC_PLLCCR_TYPE
        p_pllccr_reg = &(R_SYSTEM->PLLCCR);
 #else
        p_pllccr_reg = &(R_SYSTEM->PLLCCR2);
 #endif
    }

 #if BSP_PRV_PLL2_SUPPORTED
    else
    {
        p_pllccr_reg = &(R_SYSTEM->PLL2CCR);
    }
 #endif

    /* PLLCCR cannot be changed while PLL is running. Verify requested PLLCCR value is unchanged or the PLL is
     * currently stopped. */
    FSP_ERROR_RETURN((*p_pllccr_reg == pllccr) || (CGC_PRV_CLOCK_STATE_STOPPED == r_cgc_clock_run_state_get(pll)),
                     FSP_ERR_CLOCK_ACTIVE);

    /* Calculate the new PLL frequency. Parameter checking is performed during this calculation if parameter
     * checking is enabled, but the calculation is required even if parameter checking is not enabled. */
    fsp_err_t err = r_cgc_pll_hz_calculate(p_pll_cfg, pll_out, p_pll_hz);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    *p_pllccr = pllccr;

    return FSP_SUCCESS;
}

#endif

#if BSP_PRV_PLL_SUPPORTED

/*******************************************************************************************************************//**
 * Set PLLCCR and store PLL frequency in the BSP.
 *
 * @param[in]  pll_hz                   Previously calculated PLL frequency
 * @param[in]  pllccr                   Previously calculated PLLCCR value
 **********************************************************************************************************************/
static void r_cgc_pll_cfg (uint32_t pll_hz, uint32_t pllccr)
{
 #if 1U == BSP_FEATURE_CGC_PLLCCR_TYPE || 3U == BSP_FEATURE_CGC_PLLCCR_TYPE
    R_SYSTEM->PLLCCR = (uint16_t) pllccr;
 #elif 4U == BSP_FEATURE_CGC_PLLCCR_TYPE
    R_SYSTEM->PLLCCR = (uint16_t) pllccr | CGC_PRV_PLLCCR_RESET_VALUE;
 #else                                 // 2U == BSP_FEATURE_CGC_PLLCCR_TYPE
    R_SYSTEM->PLLCCR2 = (uint8_t) pllccr;
 #endif

    /* Update the PLL frequency in the BSP. */
    bsp_prv_prepare_pll(pll_hz);

 #if BSP_FEATURE_CGC_PLLCCR_WAIT_US > 0

    /* This loop is provided to ensure at least 1 us passes between setting PLLMUL and clearing PLLSTP on some
     * MCUs (see PLLSTP notes in Section 8.2.4 "PLL Control Register (PLLCR)" of the RA4M1 manual R01UH0887EJ0100).
     * Five loops are needed here to ensure the most efficient path takes at least 1 us from the setting of
     * PLLMUL to the clearing of PLLSTP. HOCO is the fastest clock we can be using here since PLL cannot be running
     * while setting PLLCCR. */
    bsp_prv_software_delay_loop(BSP_DELAY_LOOPS_CALCULATE(BSP_PRV_MAX_HOCO_CYCLES_PER_US));
 #endif
}

#endif

/*******************************************************************************************************************//**
 * Internal NMI ISR callback which calls the user provided callback passing the context provided by the user.
 *
 * @param[in]    irq        IRQ which has triggered the NMI interrupt.
 **********************************************************************************************************************/
static void r_cgc_nmi_internal_callback (bsp_grp_irq_t irq)
{
    FSP_PARAMETER_NOT_USED(irq);

    /* Call user registered callback */
    if (NULL != gp_cgc_ctrl)
    {
        if (NULL != gp_cgc_ctrl->p_callback)
        {
            cgc_callback_args_t args;

            cgc_callback_args_t * p_args = gp_cgc_ctrl->p_callback_memory;
            if (NULL == p_args)
            {
                p_args = &args;
            }
            else
            {
                args = *p_args;
            }

            p_args->event     = CGC_EVENT_OSC_STOP_DETECT;
            p_args->p_context = gp_cgc_ctrl->p_context;

#if BSP_TZ_SECURE_BUILD

            /* p_callback can point to a secure function or a non-secure function. */
            if (!cmse_is_nsfptr(gp_cgc_ctrl->p_callback))
            {
                /* If p_callback is secure, then the project does not need to change security state. */
                gp_cgc_ctrl->p_callback(&args);
            }
            else
            {
                /* If p_callback is Non-secure, then the project must change to Non-secure state in order to call the callback. */
                cgc_prv_ns_callback p_callback = (cgc_prv_ns_callback) (gp_cgc_ctrl->p_callback);
                p_callback(p_args);
            }

#else

            /* If the project is not Trustzone Secure, then it will never need to change security state in order to call the callback. */
            gp_cgc_ctrl->p_callback(&args);
#endif

            if (NULL != gp_cgc_ctrl->p_callback_memory)
            {
                /* Restore callback memory in case this is a nested interrupt. */
                *gp_cgc_ctrl->p_callback_memory = args;
            }
        }
    }
}
