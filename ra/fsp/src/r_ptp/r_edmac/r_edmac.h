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

#include "bsp_api.h"

#ifndef R_EDMAC_H
 #define R_EDMAC_H

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/*********************************************************************************************************************
 * Macro definitions
 ********************************************************************************************************************/

/* EDMAC Channels available. */
 #define ETHERC_EDMAC_CHANNEL    (0U)
 #define PTPC_EDMAC_CHANNEL      (1U)

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/* EDMAC Descriptor Type. */
typedef enum
{
    EDMAC_DESC_RECEIVE,
    EDMAC_DESC_TRANSMIT
} edmac_desc_type_t;

/* Number of bytes to insert into a received Ethernet packet. */
typedef enum
{
    EDMAC_PADDING_DISABLE,
    EDMAC_PADDING_1BYTE,
    EDMAC_PADDING_2BYTE,
    EDMAC_PADDING_3BYTE,
} edmac_padding_t;

/* The status of a descriptor. */
typedef struct __PACKED
{
    union
    {
        uint32_t raw;

        struct
        {
            uint32_t        : 31U;
            uint32_t active : 1U;
        } raw_b;
    };
} edmac_desc_status_t;

/* Buffer descriptor. */
typedef struct
{
    volatile edmac_desc_status_t status; // The status of the descriptor.
    volatile uint16_t            size;   // The number of bytes received or the number of bytes to transmit.
    uint16_t  buffer_size;               // The total size of the buffer (Receive descriptor only).
    uint8_t * p_buffer;                  // Pointer to a buffer to transmit or receive.
    uint32_t  resv;
} edmac_desc_t;

typedef struct
{
    uint32_t status;                   // Current EDMAC status (EESR).
    void   * p_context;
} edmac_callback_args_t;

typedef struct
{
    uint32_t        channel;           // The channel of the EDMAC instance.
    edmac_padding_t padding;           // Number of bytes to insert into a received buffer.
    uint32_t        padding_offset;    // The offset into the received buffer to insert padding bytes.
    uint32_t        num_tx_desc;       // Number of descriptors in the transmit descriptor list.
    uint32_t        num_rx_desc;       // Number of descriptors in the receive descriptor list.
    edmac_desc_t  * p_tx_descriptors;  // Transmit descriptor list.
    edmac_desc_t  * p_rx_descriptors;  // Receive descriptor list.
    IRQn_Type       edmac_irq;         // IRQ number for the EDMAC instance.
    uint8_t         edmac_ipl;         // Interrupt priority for the EDMAC IRQ.

    /* Callback called when a buffer is transmitted or received, or if an error occurred during transmission. */
    void (* p_callback)(edmac_callback_args_t * p_args);

    void * p_context;
    void * p_extend;
} edmac_cfg_t;

typedef struct
{
    uint32_t              open;        // Mark if the instance has been opened.
    R_ETHERC_EDMAC_Type * p_reg;       // Pointer to the EDMAC registers for this instance.
    edmac_cfg_t const   * p_cfg;       // Pointer to the configuration structure.
} edmac_instance_ctrl_t;

typedef struct
{
    edmac_instance_ctrl_t * const p_ctrl;
    edmac_cfg_t const * const     p_cfg;
} edmac_instance_t;

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/
fsp_err_t R_EDMAC_Open(edmac_instance_ctrl_t * const p_ctrl, edmac_cfg_t const * const p_cfg);

fsp_err_t R_EDMAC_DescriptorUpdate(edmac_instance_ctrl_t * const p_ctrl,
                                   edmac_desc_type_t             type,
                                   uint32_t                      index,
                                   uint8_t * const               p_buffer,
                                   uint16_t                      length);

fsp_err_t R_EDMAC_DescriptorGet(edmac_instance_ctrl_t * const p_ctrl,
                                edmac_desc_type_t             type,
                                uint32_t                      index,
                                edmac_desc_t ** const         p_desc);

fsp_err_t R_EDMAC_Close(edmac_instance_ctrl_t * const p_ctrl);

void edmac_eint_isr(void);

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
