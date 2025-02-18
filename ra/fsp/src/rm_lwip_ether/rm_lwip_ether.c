/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 ***********************************************************************************************************************/
#include "rm_lwip_ether.h"

#include "netif/etharp.h"
#include "lwip/sys.h"
#include "lwip/timeouts.h"
#include "lwip/priv/memp_priv.h"

/***********************************************************************************************************************
 * Macro definitions
 ***********************************************************************************************************************/
#define LWIP_ETHER_MINIMUM_FRAME_SIZE    (60U) /* Minimum number of transmitted data */

/***********************************************************************************************************************
 * Typedef definitions
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global variables (to be accessed by other files)
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global function
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables and functions
 ***********************************************************************************************************************/

/* Static functions */
static err_t rm_lwip_ether_output(struct netif * p_netif, struct pbuf * p_pbuf);
static void  rm_lwip_ether_buffer_init(rm_lwip_ether_instance_t * p_lwip_instance);
static void  rm_lwip_ether_check_link_status(void * p_lwip_instance);
static void  rm_lwip_ether_free(struct pbuf * p_pbuf);
static void  rm_lwip_ether_input(rm_lwip_ether_instance_t * p_lwip_instance);
static void  rm_lwip_ether_remove(struct netif * p_netif);

#if !NO_SYS
static void rm_lwip_ether_input_thread(void * arg);

#endif

/*******************************************************************************************************************//**
 * @addtogroup RM_LWIP_ETHER
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/********************************************************************************************************************//**
 * Initialize ethernet hardware and lwIP network interface.
 * This function is passed to netif_add()
 ***********************************************************************************************************************/
err_t rm_lwip_ether_init (struct netif * p_netif)
{
    fsp_err_t fsp_err;
    err_t     lwip_err;

    rm_lwip_ether_instance_t * p_lwip_instance;
    ether_instance_t         * p_ether_instance;

    FSP_ERROR_RETURN(NULL != p_netif, ERR_IF);
    FSP_ERROR_RETURN(NULL != p_netif->state, ERR_IF);
    FSP_ERROR_RETURN(NULL != ((rm_lwip_ether_instance_t *) (p_netif->state))->p_cfg->p_ether_instance, ERR_IF);

    p_lwip_instance  = (rm_lwip_ether_instance_t *) (p_netif->state);
    p_ether_instance = p_lwip_instance->p_cfg->p_ether_instance;

    /* Set netif to lwIP port instance */
    p_lwip_instance->p_ctrl->p_netif = p_netif;

    /* Set flags indicating the capability of the interface. */
    p_netif->flags = p_lwip_instance->p_cfg->flags;

    /* Set maximum transfer unit. */
    p_netif->mtu = p_lwip_instance->p_cfg->mtu;

    /* Set MAC hardware address */
    memcpy(&p_netif->hwaddr[0], &p_ether_instance->p_cfg->p_mac_address[0], sizeof(p_netif->hwaddr));

    /* Set hardware address length of Ethernet. */
    p_netif->hwaddr_len = ETH_HWADDR_LEN;

    /* Set output function that support ARP. */
    p_netif->output = etharp_output;

    /* Set function to send a Ethernet frame */
    p_netif->linkoutput = rm_lwip_ether_output;

    /* Set interface name as channel number. e.g. "c1" */
    p_netif->name[0] = 'c';
    p_netif->name[1] = (char) (p_ether_instance->p_cfg->channel + '0');

    /* Set end process */
    netif_set_remove_callback(p_netif, rm_lwip_ether_remove);

    /* Initialize Ethernet module */
    fsp_err = p_ether_instance->p_api->open(p_ether_instance->p_ctrl, p_ether_instance->p_cfg);

    if (FSP_SUCCESS == fsp_err)
    {
        lwip_err = ERR_OK;

        /* Check link status periodically.*/
        rm_lwip_ether_check_link_status(p_lwip_instance);

#if !NO_SYS
        if (0 == p_lwip_instance->p_ctrl->input_thread_exist)
        {
/* GCC compilier occur aggregate-return warning on FreeRTOS port. */
 #if defined(__GNUC__)
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Waggregate-return"
 #endif

            /* Start input thread. */
            sys_thread_new("lwip_ether_input_thread",
                           rm_lwip_ether_input_thread,
                           p_lwip_instance,
                           p_lwip_instance->p_cfg->input_thread_stacksize,
                           p_lwip_instance->p_cfg->input_thread_priority);
 #if defined(__GNUC__)
  #pragma GCC diagnostic pop
 #endif

            p_lwip_instance->p_ctrl->input_thread_exist = true;
        }
#endif
    }
    else
    {
        lwip_err = ERR_IF;
    }

    return lwip_err;
}

/********************************************************************************************************************//**
 * Callback of Ethernet interrupt subroutine.
 * This function is set to ethernet driver callback by configurator.
 ***********************************************************************************************************************/
void rm_lwip_ether_callback (ether_callback_args_t * p_args)
{
    rm_lwip_ether_instance_t * p_lwip_instance = (rm_lwip_ether_instance_t *) p_args->p_context;
    struct netif             * p_netif         = p_lwip_instance->p_ctrl->p_netif;

    switch (p_args->event)
    {
        /* When a frame is received. This includes the case when the receive buffer is full. */
        case ETHER_EVENT_RX_COMPLETE:
        case ETHER_EVENT_RX_MESSAGE_LOST:
        {
#if !NO_SYS

            /* Send a message to input thread. */
            sys_mbox_trypost_fromisr(p_lwip_instance->p_ctrl->p_read_complete_mbox,
                                     &p_lwip_instance->p_ctrl->read_complete_message);
#else

            /* Notify packet to lwIP. */
            rm_lwip_ether_input(p_lwip_instance);
#endif
            break;
        }

        case ETHER_EVENT_LINK_ON:
        {
            netif_set_link_up(p_netif);

            /* Initialize RX buffers. It is necessary that buffers are initialized in linkup callback. */
            rm_lwip_ether_buffer_init(p_lwip_instance);
            break;
        }

        case ETHER_EVENT_LINK_OFF:
        {
            netif_set_link_down(p_netif);
            break;
        }

        default:
        {
            break;
        }
    }
}

/** @} (end addtogroup GPT) */

/*******************************************************************************************************************//**
 * Private Functions
 **********************************************************************************************************************/

/**
 * Send frame of pbuf.
 */
static err_t rm_lwip_ether_output (struct netif * p_netif, struct pbuf * p_pbuf)
{
    fsp_err_t          fsp_err;
    ether_instance_t * p_ether_instance = ((rm_lwip_ether_instance_t *) p_netif->state)->p_cfg->p_ether_instance;
    err_t              lwip_err         = ERR_OK;
    struct pbuf      * temp             = p_pbuf;

    while (NULL != temp)
    {
        /* Sending frame buffer for the frame shorter than 60bytes. */
        uint8_t minimum_frame[LWIP_ETHER_MINIMUM_FRAME_SIZE] = {0};

        if (temp->len < LWIP_ETHER_MINIMUM_FRAME_SIZE)
        {
            /* Add padding when shorter than 60bytes. */
            memcpy(minimum_frame, (char *) temp->payload, temp->len);
            fsp_err =
                p_ether_instance->p_api->write(p_ether_instance->p_ctrl, minimum_frame, LWIP_ETHER_MINIMUM_FRAME_SIZE);
        }
        else
        {
            fsp_err = p_ether_instance->p_api->write(p_ether_instance->p_ctrl, temp->payload, temp->len);
        }

        /* If the write operation fails, the remaining pbufs are not output .*/
        if (fsp_err != FSP_SUCCESS)
        {
            lwip_err = ERR_IF;
            break;
        }

        temp = temp->next;
    }

    return lwip_err;
}

/**
 * Receive frame and notify it to lwIP.
 */
static void rm_lwip_ether_input (rm_lwip_ether_instance_t * p_lwip_instance)
{
    struct pbuf       * p_pbuf;
    rm_lwip_rx_pbuf_t * p_custom_pbuf      = NULL;
    uint32_t            read_buffer_length = 0;
    void              * p_rx_buffer        = NULL;

    /* When p_netif is NULL, this driver is uninitialized or terminated. */
    FSP_ERROR_RETURN(NULL != p_lwip_instance->p_ctrl->p_netif, );

    ether_instance_t * p_ether_instance = p_lwip_instance->p_cfg->p_ether_instance;
    fsp_err_t          err              = FSP_SUCCESS;

    /* Read all RX descriptors that received a frame. */
    do
    {
        /* Allocate a custom pbuf. */
        p_custom_pbuf = (rm_lwip_rx_pbuf_t *) memp_malloc_pool(p_lwip_instance->p_cfg->p_rx_pbuf_mempool);
        if (NULL == p_custom_pbuf)
        {
            break;
        }

        /* Allocate a buffer that store received frame. */
        p_rx_buffer = memp_malloc_pool(p_lwip_instance->p_cfg->p_rx_buffers_mempool);
        if (NULL == p_rx_buffer)
        {
            memp_free_pool(p_custom_pbuf->p_lwip_instance->p_cfg->p_rx_pbuf_mempool, p_custom_pbuf);
            break;
        }

        /* Set custom pbuf members. */
        p_custom_pbuf->p_lwip_instance           = p_lwip_instance;
        p_custom_pbuf->pbuf.custom_free_function = rm_lwip_ether_free;
        p_pbuf = pbuf_alloced_custom(PBUF_RAW,
                                     0,
                                     PBUF_REF,
                                     &p_custom_pbuf->pbuf,
                                     NULL,
                                     (uint16_t) p_ether_instance->p_cfg->ether_buffer_size);

        if (ETHER_ZEROCOPY_ENABLE == p_ether_instance->p_cfg->zerocopy)
        {
            err = p_ether_instance->p_api->read(p_ether_instance->p_ctrl, &p_pbuf->payload, &read_buffer_length);
            if (FSP_SUCCESS == err)
            {
                /* Update the buffer of Ethernet descriptor to new one. */
                p_ether_instance->p_api->rxBufferUpdate(p_ether_instance->p_ctrl, p_rx_buffer);
            }
            else if (FSP_ERR_ETHER_ERROR_NO_DATA != err)
            {
                /* Release new buffer. */
                memp_free_pool(p_custom_pbuf->p_lwip_instance->p_cfg->p_rx_buffers_mempool, p_rx_buffer);

                /* Release current buffer that set to the descriptor. */
                p_ether_instance->p_api->bufferRelease(p_ether_instance->p_ctrl);
            }
            else
            {
                /* Release new buffer. */
                memp_free_pool(p_custom_pbuf->p_lwip_instance->p_cfg->p_rx_buffers_mempool, p_rx_buffer);
            }
        }
        else                           /* ETHER_ZEROCOPY_ENABLE == p_ether_instance->p_cfg->zerocopy */
        {
            /* Read data. */
            err = p_ether_instance->p_api->read(p_ether_instance->p_ctrl, p_rx_buffer, &read_buffer_length);

            /* Copy data to pbuf. */
            p_pbuf->payload = p_rx_buffer;
        }

        /* Store the buffer address. It need to release the buffer. */
        p_custom_pbuf->p_buffer = p_pbuf->payload;

        if (FSP_SUCCESS == err)
        {
            /* Set packet length */
            p_pbuf->len     = (uint16_t) read_buffer_length;
            p_pbuf->tot_len = (uint16_t) read_buffer_length;

            /* Notify packet */
            if (p_lwip_instance->p_ctrl->p_netif->input(p_pbuf, p_lwip_instance->p_ctrl->p_netif) != ERR_OK)
            {
                pbuf_free(p_pbuf);
            }
        }
        else
        {
            /* When the receive error is happened, release the buffer. */
            pbuf_free(p_pbuf);
        }

        /* Continue until all received buffers are read. */
    } while (FSP_ERR_ETHER_ERROR_NO_DATA != err);
}

/**
 * Free buffer for RX.
 */
static void rm_lwip_ether_free (struct pbuf * p_pbuf)
{
    rm_lwip_rx_pbuf_t * p_custom_pbuf = (rm_lwip_rx_pbuf_t *) p_pbuf;

    /* Release RX buffer and custom pbuf. */
    if (NULL != p_custom_pbuf->p_buffer)
    {
        memp_free_pool(p_custom_pbuf->p_lwip_instance->p_cfg->p_rx_buffers_mempool, p_custom_pbuf->p_buffer);
    }

    memp_free_pool(p_custom_pbuf->p_lwip_instance->p_cfg->p_rx_pbuf_mempool, p_custom_pbuf);
}

/**
 * Terminating network driver.
 */
static void rm_lwip_ether_remove (struct netif * p_netif)
{
    rm_lwip_ether_instance_t * p_lwip_instance  = (rm_lwip_ether_instance_t *) p_netif->state;
    ether_instance_t         * p_ether_instance = p_lwip_instance->p_cfg->p_ether_instance;

    /* Remove lwip timer for link check. */
    sys_untimeout(rm_lwip_ether_check_link_status, p_lwip_instance);

    /* Remove the pointer to netif. */
    p_lwip_instance->p_ctrl->p_netif = NULL;

    /* Close Ethernet driver. */
    p_ether_instance->p_api->close(p_ether_instance->p_ctrl);
}

/**
 * Checking link status periodically.
 */
static void rm_lwip_ether_check_link_status (void * p_lwip_instance)
{
    ether_instance_t * p_ether_instance = ((rm_lwip_ether_instance_t *) p_lwip_instance)->p_cfg->p_ether_instance;

    /* Check link status. If link status change detected, change the lwIP status in link callback. */
    p_ether_instance->p_api->linkProcess(p_ether_instance->p_ctrl);
    sys_timeout(((rm_lwip_ether_instance_t *) p_lwip_instance)->p_cfg->link_check_interval,
                rm_lwip_ether_check_link_status,
                p_lwip_instance);
}

/**
 * Initialize RX buffers.
 */
static void rm_lwip_ether_buffer_init (rm_lwip_ether_instance_t * p_lwip_instance)
{
    ether_instance_t * p_ether_instance = p_lwip_instance->p_cfg->p_ether_instance;
    void             * p_rx_buffer;

    memp_init_pool(p_lwip_instance->p_cfg->p_rx_pbuf_mempool);
    memp_init_pool(p_lwip_instance->p_cfg->p_rx_buffers_mempool);

    if (ETHER_ZEROCOPY_ENABLE == p_ether_instance->p_cfg->zerocopy)
    {
        /* If zerocopy mode, set RX buffers to Ethernet descriptors. */
        for (int i = 0; i < p_ether_instance->p_cfg->num_rx_descriptors; i++)
        {
            p_rx_buffer = memp_malloc_pool(p_lwip_instance->p_cfg->p_rx_buffers_mempool);
            p_ether_instance->p_api->rxBufferUpdate(p_ether_instance->p_ctrl, p_rx_buffer);
        }
    }
}

/**
 * Thread for receiving process.
 */
#if !NO_SYS
static void rm_lwip_ether_input_thread (void * arg)
{
    rm_lwip_ether_instance_t * p_lwip_instance = (rm_lwip_ether_instance_t *) arg;
    uint32_t                 * p_read_complete_flag;

    /* Create new mbox for checking read complete. */
    p_lwip_instance->p_ctrl->p_read_complete_mbox = (sys_mbox_t *) mem_malloc(sizeof(sys_mbox_t));
    sys_mbox_new(p_lwip_instance->p_ctrl->p_read_complete_mbox, 1);

    while (true)
    {
        sys_mbox_fetch(p_lwip_instance->p_ctrl->p_read_complete_mbox, (void **) &p_read_complete_flag);
        rm_lwip_ether_input(p_lwip_instance);
    }
}

#endif
