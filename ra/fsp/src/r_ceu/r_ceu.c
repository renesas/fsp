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

/***************************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 ***************************************************************************************************************************/
#include "r_ceu.h"
#include "r_ceu_cfg.h"

/***************************************************************************************************************************
 * Macro definitions
 ***************************************************************************************************************************/
#define CEU_OPEN    (0x52434555)       // RCEU in hex

/***************************************************************************************************************************
 * Typedef definitions
 ***************************************************************************************************************************/

#if defined(__ARMCC_VERSION) || defined(__ICCARM__)
typedef void (BSP_CMSE_NONSECURE_CALL * ceu_prv_ns_callback)(capture_callback_args_t * p_args);
#elif defined(__GNUC__)
typedef BSP_CMSE_NONSECURE_CALL void (*volatile ceu_prv_ns_callback)(capture_callback_args_t * p_args);
#endif

/***************************************************************************************************************************
 * Imported global variables and functions (from other files)
 ***************************************************************************************************************************/

/***************************************************************************************************************************
 * Exported global variables and functions (to be accessed by other files)
 ***************************************************************************************************************************/

/* CEU API  */
const capture_api_t g_ceu_on_capture =
{
    .open         = R_CEU_Open,
    .close        = R_CEU_Close,
    .captureStart = R_CEU_CaptureStart,
    .callbackSet  = R_CEU_CallbackSet,
    .statusGet    = R_CEU_StatusGet
};

void ceu_isr(void);

/***************************************************************************************************************************
 * Private global variables and functions
 ***************************************************************************************************************************/
static void ceu_call_callback(ceu_instance_ctrl_t * p_instance_ctrl, capture_callback_args_t * p_args);

static void ceu_disable_interrupts(ceu_instance_ctrl_t * p_instance_ctrl);
static void ceu_enable_interrupts(ceu_instance_ctrl_t * p_instance_ctrl);

/***********************************************************************************************************************//**
 * @addtogroup CEU
 * @{
 ***************************************************************************************************************************/

/***************************************************************************************************************************
 * Functions
 ***************************************************************************************************************************/

/***********************************************************************************************************************//**
 * CEU module initialization.
 *
 * Implements @ref capture_api_t::open
 *
 * The function provides initial configuration for the CEU module. Further initialization may be performed in
 * @ref capture_api_t::captureStart. This function should be called once prior to calling any other CEU API functions. After
 * the CEU is opened the Open function should not be called again without first calling the Close function.
 *
 * Example:
 * @snippet r_ceu_example.c R_CEU_Open
 *
 * @retval FSP_SUCCESS              Initialization was successful.
 * @retval FSP_ERR_ASSERTION        One or more parameters is NULL.
 * @retval FSP_ERR_ALREADY_OPEN     Module is already open.
 **************************************************************************************************************************/
fsp_err_t R_CEU_Open (capture_ctrl_t * const p_ctrl, capture_cfg_t const * const p_cfg)
{
    ceu_instance_ctrl_t * p_instance_ctrl = (ceu_instance_ctrl_t *) p_ctrl;

#if CEU_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_cfg);
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(0 <= ((ceu_extended_cfg_t *) p_cfg->p_extend)->ceu_irq);
    FSP_ERROR_RETURN(CEU_OPEN != p_instance_ctrl->open, FSP_ERR_ALREADY_OPEN);
#endif

    /* Local variables */
    p_instance_ctrl->p_cfg = p_cfg;
    ceu_extended_cfg_t * p_extend = (ceu_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;

    bool     bus_width_8_bit = (CEU_DATA_BUS_SIZE_8_BIT == p_extend->data_bus_width);
    uint32_t bytes_per_cycle = p_extend->data_bus_width + 1;
    uint32_t bytes_per_line  = p_cfg->x_capture_pixels * p_cfg->bytes_per_pixel;
    uint32_t cycles_per_byte = (bus_width_8_bit ? 2 : 1);
    uint32_t cycles_per_line = bytes_per_line / bytes_per_cycle;
    uint32_t lines_per_image = p_cfg->y_capture_pixels;
    uint32_t hfclp           = cycles_per_line / cycles_per_byte; // Div by 2 for CEU_DATA_BUS_SIZE_8_BIT
    uint32_t vfclp           = lines_per_image;

    /* Initialize control structure data */
    p_instance_ctrl->p_callback = p_cfg->p_callback;

    if (CEU_CAPTURE_FORMAT_DATA_ENABLE == p_extend->capture_format)
    {
        p_instance_ctrl->image_area_size = p_extend->image_area_size;
    }
    else
    {
        p_instance_ctrl->image_area_size = cycles_per_line * bytes_per_line;
    }

    /* Start the peripheral */
    R_BSP_MODULE_START(FSP_IP_CEU, 0U);

    /* Wait for module reset, if in progress
     * Refer to figure 53.6 "Timing of software reset and restart of capturing" in the RA8M1 manual R01UH0994EJ0100. */
    FSP_HARDWARE_REGISTER_WAIT(R_CEU->CSTSR_b.CPTON, 0);
    FSP_HARDWARE_REGISTER_WAIT(R_CEU->CAPSR_b.CPKIL, 0);

    /* capture control register (CAPCR)
     * [Note] Continuous capture operations are possible only in image capture mode. */
    R_CEU->CAPCR = ((uint32_t) (p_extend->burst_mode << R_CEU_CAPCR_MTCM_Pos) & R_CEU_CAPCR_MTCM_Msk);         // Unit for transferring data to bus bridge module;

    /* Capture Interface Control Register (CAMCR) */
    R_CEU->CAMCR = ((uint32_t) (p_extend->hsync_polarity << R_CEU_CAMCR_HDPOL_Pos) & R_CEU_CAMCR_HDPOL_Msk) |  // Polarity for detection of the horizontal sync signal input
                   ((uint32_t) (p_extend->vsync_polarity << R_CEU_CAMCR_VDPOL_Pos) & R_CEU_CAMCR_VDPOL_Msk) |  // Polarity for detection of the vertical sync signal input
                   ((uint32_t) (p_extend->capture_format << R_CEU_CAMCR_JPG_Pos) & R_CEU_CAMCR_JPG_Msk) |      // Fetched data type
                   ((uint32_t) (p_extend->data_bus_width << R_CEU_CAMCR_DTIF_Pos) & R_CEU_CAMCR_DTIF_Msk) |    // Digital image input pins from which data is to be captured
                   ((uint32_t) (p_extend->edge_info.dsel << R_CEU_CAMCR_DSEL_Pos) & R_CEU_CAMCR_DSEL_Msk) |    // Edge for fetching external image data (D7 to D0)
                   ((uint32_t) (p_extend->edge_info.hdsel << R_CEU_CAMCR_HDSEL_Pos) & R_CEU_CAMCR_HDSEL_Msk) | // Edge for capturing external horizontal sync signal (HD)
                   ((uint32_t) (p_extend->edge_info.vdsel << R_CEU_CAMCR_VDSEL_Pos) & R_CEU_CAMCR_VDSEL_Msk);  // Edge for capturing external vertical sync signal (VD)

    /* Capture Interface Cycle Register (CMCYR) - Used to detect illegal VD and illegal HD
     * [Note] Should be 0 (disabled) for Data Enable Fetch mode. */
    R_CEU->CMCYR = (((uint32_t) p_cfg->x_capture_pixels << R_CEU_CMCYR_HCYL_Pos) & R_CEU_CMCYR_HCYL_Msk) |
                   (((uint32_t) p_cfg->y_capture_pixels << R_CEU_CMCYR_VCYL_Pos) & R_CEU_CMCYR_VCYL_Msk);

    /* Capture Interface Offset Register (CAMOR)
     * [Note] Should be 0 for Data Enable Fetch mode. */
    uint32_t x_cycle_start = (uint32_t) p_cfg->x_capture_start_pixel * cycles_per_byte;
    R_CEU->CAMOR = ((x_cycle_start << R_CEU_CAMOR_HOFST_Pos) & R_CEU_CAMOR_HOFST_Msk) |                          // capture start location from a horizontal sync signal (1-cycle units)
                   (((uint32_t) p_cfg->y_capture_start_pixel << R_CEU_CAMOR_VOFST_Pos) & R_CEU_CAMOR_VOFST_Msk); // capture start location from a vertical sync signal (1-HD units)

    /* Capture Interface Width Register (CAPWR)
     * [Note] This register is used during Data synchronous fetch mode. */
    R_CEU->CAPWR = ((cycles_per_line << R_CEU_CAPWR_HWDTH_Pos) & R_CEU_CAPWR_HWDTH_Msk) |                        // Number of HD cycles to be captured, starting from CAMOR.HOFST
                   ((lines_per_image << R_CEU_CAPWR_VWDTH_Pos) & R_CEU_CAPWR_VWDTH_Msk);                         // Number of VD cycles (HD count) to be captured from CAMOR.VOFST

    /* Firewall Operation Control Register (CFWCR)
     * Disable firewall in this call to open. If applicable, it will be re-enabled in the call to captureStart() */
    R_CEU->CFWCR = 0;

    /* Capture Filter Size Clip Register (CFSZR)
     * [Note] Set HFCLP to CAPWR.HWDTH/2 in 8-bit interface mode */
    R_CEU->CFSZR = ((vfclp << R_CEU_CFSZR_VFCLP_Pos) & R_CEU_CFSZR_VFCLP_Msk) | // Vertical clipping value of the filter output size (4-pixel units)
                   ((hfclp << R_CEU_CFSZR_HFCLP_Pos) & R_CEU_CFSZR_HFCLP_Msk);  // Horizontal clipping value of the filter output size (4-pixel units)

    /* Capture Destination Width Register (CDWDR)
     * [Note] Set CHDW to CAPWR.HWDTH * 2 for 16-bit interface mode */
    R_CEU->CDWDR = bytes_per_line;                                              // Horizontal image size in the memory where image is to be stored (4-byte units)

    /* Capture Low-Pass Filter Control Register (CLFCR)  */
    R_CEU->CLFCR = 0U;

    /* Capture Data Output Control Register (CDOCR) */
    R_CEU->CDOCR =
        (((uint32_t) p_extend->byte_swapping.swap_8bit_units << R_CEU_CDOCR_COBS_Pos) & R_CEU_CDOCR_COBS_Msk) |  // Swapping 8-bit units for data output from the CEU
        (((uint32_t) p_extend->byte_swapping.swap_16bit_units << R_CEU_CDOCR_COWS_Pos) & R_CEU_CDOCR_COWS_Msk) | // Swapping 16-bit units for data output from the CEU
        (((uint32_t) p_extend->byte_swapping.swap_32bit_units << R_CEU_CDOCR_COLS_Pos) & R_CEU_CDOCR_COLS_Msk) | // Swapping 32-bit units for data output from the CEU
        (((uint32_t) 1U << R_CEU_CDOCR_CDS_Pos) & R_CEU_CDOCR_CDS_Msk);                                          // Image format for data captured in the YCbCr 422 format (Must be set for Data Fetch capture modes)

    /* Clear any previous buffer address */
    p_instance_ctrl->p_buffer = 0U;

    /* Mark driver as open
     * [Note] Open driver prior to enabling interrupts to fascilitate any required callback processing */
    p_instance_ctrl->open = CEU_OPEN;

    ceu_enable_interrupts(p_instance_ctrl);

    return FSP_SUCCESS;
}                                      /* End of function R_CEU_Open() */

/***********************************************************************************************************************//**
 * Stops and closes the transfer interface.
 *
 * Implements @ref capture_api_t::close
 *
 * Stops any active captures, clears internal driver state-data, disables interrupts, and powers off the CEU peripheral.
 *
 * Example:
 * @snippet r_ceu_example.c R_CEU_Close
 *
 * @retval FSP_SUCCESS              Initialization was successful.
 * @retval FSP_ERR_ASSERTION        One or more parameters is NULL.
 * @retval FSP_ERR_NOT_OPEN         Open has not been successfully called.
 **************************************************************************************************************************/
fsp_err_t R_CEU_Close (capture_ctrl_t * const p_ctrl)
{
    ceu_instance_ctrl_t * p_instance_ctrl = (ceu_instance_ctrl_t *) p_ctrl;

#if CEU_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(CEU_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    ceu_disable_interrupts(p_instance_ctrl);

    R_CEU->CAPSR = R_CEU_CAPSR_CPKIL_Msk; // Setting the CPKIL starts

    /* Mark driver as closed
     * [Note] Set interface as closed after disabling interrupts to fascilitate any API calls in the application callback  */
    p_instance_ctrl->open = 0U;

    R_BSP_MODULE_STOP(FSP_IP_CEU, 0U);

    return FSP_SUCCESS;
}

/***********************************************************************************************************************//**
 * Starts a capture.
 *
 * Implements @ref capture_api_t::captureStart.
 *
 * Sets up the interface to transfer data from the CEU into the specifiec buffer. Configures the CEU settings as previously
 * set by the @ref capture_api_t::open API. When a capture is complete the callback registered during @ref capture_api_t::open API
 * call or by @ref capture_api_t::callbackSet API will be called.
 *
 * Example:
 * @snippet r_ceu_example.c R_CEU_CaptureStart
 *
 * @retval FSP_SUCCESS              Initialization was successful.
 * @retval FSP_ERR_ASSERTION        One or more parameters is NULL.
 * @retval FSP_ERR_NOT_OPEN         Open has not been successfully called.
 * @retval FSP_ERR_INVALID_ADDRESS  Invalid buffer address alignment.
 * @retval FSP_ERR_IN_USE           CEU is already in use.
 * @retval FSP_ERR_NOT_INITIALIZED  Callback function has not been set
 **************************************************************************************************************************/
fsp_err_t R_CEU_CaptureStart (capture_ctrl_t * const p_ctrl, uint8_t * const p_buffer)
{
    ceu_instance_ctrl_t * p_instance_ctrl = (ceu_instance_ctrl_t *) p_ctrl;

#if CEU_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT((NULL != p_buffer));                                               // buffer must not be NULL
    FSP_ERROR_RETURN(0 == ((uint32_t) p_buffer & 0x07), FSP_ERR_INVALID_ADDRESS); // Buffer must be 8 byte aligned
    FSP_ERROR_RETURN(CEU_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(NULL != p_instance_ctrl->p_callback, FSP_ERR_NOT_INITIALIZED);
#endif

    /* Return error if peripheral is in use
     * Refer to figure 53.6 "Timing of software reset and restart of capturing" in the RA8M1 manual R01UH0994EJ0100. */
    FSP_ERROR_RETURN(R_CEU->CSTSR_b.CPTON == 0x0, FSP_ERR_IN_USE);
    FSP_ERROR_RETURN(R_CEU->CAPSR_b.CPKIL == 0x0, FSP_ERR_IN_USE);

    ceu_extended_cfg_t * p_extend = (ceu_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;

    p_instance_ctrl->p_buffer = p_buffer;
    if ((CEU_CAPTURE_FORMAT_DATA_ENABLE == p_extend->capture_format))
    {
        /* Firewall Operation Control Register (CFWCR)
         * [Note] Set CFWCR to zero in Image Capture or Data Synchronous Fetch modes
         * P [Note] Firewall address is upper 27-bits of memory address. Lowest 5 bits assumed to be be 0x1F. */
        uint32_t firewall_address = (uint32_t) p_buffer + p_instance_ctrl->image_area_size - 1;
        R_CEU->CFWCR = R_CEU_CFWCR_FWE_Msk | (firewall_address & R_CEU_CFWCR_FWV_Msk);
    }

    R_CEU->CDAYR = (uint32_t) p_instance_ctrl->p_buffer; // Set start address of memory area for write

    /* Clear pending flags before starting capture */
    R_CEU->CETCR = 0;

    /* Start Capturing (at next V-Sync) */
    R_CEU->CAPSR = R_CEU_CAPSR_CE_Msk;

    return FSP_SUCCESS;
}                                      /* End of function R_CEU_SetMemoryAddress() */

/***********************************************************************************************************************//**
 * Updates the user callback and has option of providing memory for callback structure.
 *
 * Implements @ref capture_api_t::callbackSet.
 *
 * @retval FSP_SUCCESS                  Initialization was successful.
 * @retval FSP_ERR_ASSERTION            One or more parameters is NULL.
 * @retval FSP_ERR_NOT_OPEN             Open has not been successfully called.
 * @retval FSP_ERR_NO_CALLBACK_MEMORY   p_callback is non-secure and p_callback_memory is either secure or NULL.
 **************************************************************************************************************************/
fsp_err_t R_CEU_CallbackSet (capture_ctrl_t * const          p_ctrl,
                             void (                        * p_callback)(capture_callback_args_t *),
                             void const * const              p_context,
                             capture_callback_args_t * const p_callback_memory)
{
    ceu_instance_ctrl_t * p_instance_ctrl = (ceu_instance_ctrl_t *) p_ctrl;

#if (CEU_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl);
    FSP_ERROR_RETURN(CEU_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ASSERT(p_callback);
#endif
    (void) p_instance_ctrl;

    /* Store callback and context */

#if BSP_TZ_SECURE_BUILD

    /* Get security state of p_callback */
    bool callback_is_secure =
        (NULL == cmse_check_address_range((void *) p_callback, sizeof(void *), CMSE_AU_NONSECURE));

 #if CEU_CFG_PARAM_CHECKING_ENABLE

    /* In secure projects, p_callback_memory must be provided in non-secure space if p_callback is non-secure */
    capture_callback_args_t * const p_callback_memory_checked = cmse_check_pointed_object(p_callback_memory,
                                                                                          CMSE_AU_NONSECURE);
    FSP_ERROR_RETURN(callback_is_secure || (NULL != p_callback_memory_checked), FSP_ERR_NO_CALLBACK_MEMORY);
 #endif

    p_instance_ctrl->p_callback = callback_is_secure ? p_callback :
                                  (void (*)(capture_callback_args_t *))cmse_nsfptr_create(p_callback);
#else
    p_instance_ctrl->p_callback = p_callback;
#endif

    p_instance_ctrl->p_context         = p_context;
    p_instance_ctrl->p_callback_memory = p_callback_memory;

    return FSP_SUCCESS;
}                                      /* End of function R_CEU_CallbackSet() */

/***********************************************************************************************************************//**
 * Provides the ceu operating status.
 *
 * Implements @ref capture_api_t::statusGet.
 *
 * @retval FSP_SUCCESS                  Initialization was successful.
 * @retval FSP_ERR_ASSERTION            One or more parameters is NULL.
 * @retval FSP_ERR_NOT_OPEN             Open has not been successfully called.
 **************************************************************************************************************************/
fsp_err_t R_CEU_StatusGet (capture_ctrl_t * const p_ctrl, capture_status_t * p_status)
{
    ceu_instance_ctrl_t * p_instance_ctrl = (ceu_instance_ctrl_t *) p_ctrl;

#if (CEU_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_status);
    FSP_ERROR_RETURN(CEU_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
#endif

    if (R_CEU->CAPSR_b.CPKIL)
    {
        p_status->state = CAPTURE_STATE_BUSY;
    }
    else
    {
        p_status->state = (capture_state_t) (R_CEU->CSTSR_b.CPTON || R_CEU->CAPSR_b.CE);
    }

    p_status->p_buffer  = (uint32_t *) p_instance_ctrl->p_buffer;
    p_status->data_size = R_CEU->CDSSR;

    return FSP_SUCCESS;
}                                      /* End of function R_CEU_StatusGet() */

/*******************************************************************************************************************//**
 * @} (end addtogroup CEU)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Disable all ceu interrupts
 **********************************************************************************************************************/
static void ceu_disable_interrupts (ceu_instance_ctrl_t * p_instance_ctrl)
{
    R_CEU->CEIER = 0U;                 /* Disable all */

    ceu_extended_cfg_t * p_extend = (ceu_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;

    R_BSP_IrqDisable(p_extend->ceu_irq);
    R_FSP_IsrContextSet(p_extend->ceu_irq, NULL);
}

/***********************************************************************************************************************
 * Enable ceu interrupts
 **********************************************************************************************************************/
static void ceu_enable_interrupts (ceu_instance_ctrl_t * p_instance_ctrl)
{
    ceu_extended_cfg_t * p_extend = (ceu_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;
    p_instance_ctrl->interrupts_enabled = p_extend->interrupts_enabled;

    R_BSP_IrqCfgEnable(p_extend->ceu_irq, p_extend->ceu_ipl, p_instance_ctrl);

    /* Capture Event Flag CLear Register (CETCR) */
    R_CEU->CETCR = 0U;                                  /* clear all   */
    R_CEU->CEIER = p_instance_ctrl->interrupts_enabled; /* Set enabled interrupts */
}

/***********************************************************************************************************************
 * Common ISR callback wrapper. Manages callback argument memory and security context.
 **********************************************************************************************************************/
static void ceu_call_callback (ceu_instance_ctrl_t * p_instance_ctrl, capture_callback_args_t * p_args)
{
    capture_callback_args_t args;

    /* Store callback arguments in memory provided by user if available.  This allows callback arguments to be
     * stored in non-secure memory so they can be accessed by a non-secure callback function. */
    capture_callback_args_t * p_args_memory = p_instance_ctrl->p_callback_memory;
    if (NULL == p_args_memory)
    {
        /* Use provided args struct on stack */
        p_args_memory = p_args;
    }
    else
    {
        /* Save current arguments on the stack in case this is a nested interrupt. */
        args = *p_args_memory;

        /* Copy the stacked args to callback memory */
        *p_args_memory = *p_args;
    }

#if BSP_TZ_SECURE_BUILD

    /* p_callback can point to a secure function or a non-secure function. */
    if (!cmse_is_nsfptr(p_instance_ctrl->p_callback))
    {
        /* If p_callback is secure, then the project does not need to change security state. */
        p_instance_ctrl->p_callback(p_args_memory);
    }
    else
    {
        /* If p_callback is Non-secure, then the project must change to Non-secure state in order to call the callback. */
        ceu_prv_ns_callback p_callback = (ceu_prv_ns_callback) (p_instance_ctrl->p_callback);
        p_callback(p_args_memory);
    }

#else

    /* If the project is not Trustzone Secure, then it will never need to change security state in order to call the callback. */
    p_instance_ctrl->p_callback(p_args_memory);
#endif

    if (NULL != p_instance_ctrl->p_callback_memory)
    {
        /* Restore callback memory in case this is a nested interrupt. */
        *p_instance_ctrl->p_callback_memory = args;
    }
}

/***********************************************************************************************************************
 * interrupt service routine
 **********************************************************************************************************************/
extern void ceu_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    ceu_event_t events = (ceu_event_t) R_CEU->CETCR;
    R_CEU->CETCR = ~events;
    IRQn_Type irq = R_FSP_CurrentIrqGet();
    R_BSP_IrqStatusClear(irq);

    ceu_instance_ctrl_t * p_instance_ctrl = (ceu_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    if (NULL != p_instance_ctrl->p_callback)
    {
        capture_callback_args_t args;
        args.event     = (capture_event_t) (events & p_instance_ctrl->interrupts_enabled);
        args.p_buffer  = p_instance_ctrl->p_buffer;
        args.p_context = p_instance_ctrl->p_context;
        ceu_call_callback(p_instance_ctrl, &args);
    }

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}
