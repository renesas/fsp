/***********************************************************************************************************************
 * Copyright [2020-2022] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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
#include "rm_netxduo_ether.h"

#include "nx_arp.h"
#include "nx_rarp.h"

#include "r_ether.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* Disable support for RARP by default. */
#ifndef RM_NETXDUO_ETHER_RARP_SUPPORT
 #define RM_NETXDUO_ETHER_RARP_SUPPORT    (0U)
#endif

#define NX_ETHERNET_SIZE                  14

/* Ethernet Frame IDs. */
#define NX_ETHERNET_IP                    0x0800
#define NX_ETHERNET_ARP                   0x0806
#define NX_ETHERNET_RARP                  0x8035
#define NX_ETHERNET_IPV6                  0x86DD

#define NX_ETHERNET_MIN_TRANSMIT_SIZE     60U

#ifndef NX_ETHERNET_POLLING_INTERVAL
 #define NX_ETHERNET_POLLING_INTERVAL     (10U)
#endif

#ifndef NX_ETHERNET_POLLING_TIMEOUT
 #define NX_ETHERNET_POLLING_TIMEOUT      (100U)
#endif

/* Transmit Complete. */
#define ETHER_ISR_EE_TC_MASK              (1U << 21U)

/* Frame Receive. */
#define ETHER_ISR_EE_FR_MASK              (1U << 18U)

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

static void rm_netxduo_ether_cleanup(rm_netxduo_ether_instance_t * p_netxduo_ether_instance);
void        rm_netxduo_ether_receive_packet(rm_netxduo_ether_instance_t * p_netxduo_ether_instance);
void        rm_event_timer_callback(ULONG data);

/*******************************************************************************************************************//**
 * Ethernet driver for NetX Duo.
 **********************************************************************************************************************/
void rm_netxduo_ether (NX_IP_DRIVER * driver_req_ptr, rm_netxduo_ether_instance_t * p_netxduo_ether_instance)
{
    ether_instance_t const * p_ether_instance = p_netxduo_ether_instance->p_cfg->p_ether_instance;
    NX_INTERFACE           * interface_ptr    = driver_req_ptr->nx_ip_driver_interface;

    p_netxduo_ether_instance->p_ctrl->p_interface = interface_ptr;

    p_netxduo_ether_instance->p_ctrl->p_ip = driver_req_ptr->nx_ip_driver_ptr;

    driver_req_ptr->nx_ip_driver_status = NX_SUCCESS;

    switch (driver_req_ptr->nx_ip_driver_command)
    {
        case NX_LINK_INITIALIZE:
        {
            /* The nx_interface_ip_mtu_size should be the MTU for the IP payload.
             * For regular Ethernet, the IP MTU is 1500. */
            nx_ip_interface_mtu_set(driver_req_ptr->nx_ip_driver_ptr,
                                    p_ether_instance->p_cfg->channel,
                                    p_netxduo_ether_instance->p_cfg->mtu);

            /* Set the physical address (MAC address) of this IP instance.  */
            uint8_t * p_mac_address = p_ether_instance->p_cfg->p_mac_address;
            nx_ip_interface_physical_address_set(driver_req_ptr->nx_ip_driver_ptr,
                                                 p_ether_instance->p_cfg->channel,
                                                 (ULONG) ((p_mac_address[0] << 8) | (p_mac_address[1] << 0)),
                                                 (ULONG) ((p_mac_address[2] << 24) | (p_mac_address[3] << 16) |
                                                          (p_mac_address[4] << 8) |
                                                          (p_mac_address[5] << 0)),
                                                 NX_FALSE);

            /* Indicate to the IP software that IP to physical mapping is required.  */
            nx_ip_interface_address_mapping_configure(driver_req_ptr->nx_ip_driver_ptr,
                                                      p_ether_instance->p_cfg->channel,
                                                      NX_TRUE);
            break;
        }

        case NX_LINK_ENABLE:
        {
            /* Initialize ether driver state. */
            p_netxduo_ether_instance->p_ctrl->tx_packet_index             = 0;
            p_netxduo_ether_instance->p_ctrl->tx_packet_transmitted_index = 0;
            p_netxduo_ether_instance->p_ctrl->rx_packet_index             = 0;

            /* Clear the multicast MAC address list. */
            memset(p_netxduo_ether_instance->p_ctrl->multicast_mac_addresses, 0,
                   sizeof(p_netxduo_ether_instance->p_ctrl->multicast_mac_addresses));

            for (int i = 0; i < p_ether_instance->p_cfg->num_tx_descriptors; i++)
            {
                p_netxduo_ether_instance->p_cfg->p_tx_packets[i] = NULL;
            }

            /* Set the return status to be invalid if the link is not enabled. */
            driver_req_ptr->nx_ip_driver_status = NX_NOT_ENABLED;
            p_netxduo_ether_instance->p_ctrl->p_interface->nx_interface_link_up = NX_FALSE;

            /* Create ether tx semaphore in order to synchronize ether task with transmit complete interrupts. */
            if (TX_SUCCESS !=
                tx_semaphore_create(&p_netxduo_ether_instance->p_ctrl->ether_tx_semaphore, "ether_tx_semaphore",
                                    p_ether_instance->p_cfg->num_tx_descriptors))
            {
                FSP_LOG_PRINT("Failed to create ether_tx_semaphore.");
            }
            /* Open the r_ether driver. */
            else if (FSP_SUCCESS != p_ether_instance->p_api->open(p_ether_instance->p_ctrl, p_ether_instance->p_cfg))
            {
                FSP_LOG_PRINT("Failed to open Ethernet driver.");
                tx_semaphore_delete(&p_netxduo_ether_instance->p_ctrl->ether_tx_semaphore);
            }
            /* Create a timer to poll for completion of auto negotiation. */
            else if (TX_SUCCESS !=
                     tx_timer_create(&p_netxduo_ether_instance->p_ctrl->event_timer, (CHAR *) "nx ether driver timer",
                                     rm_event_timer_callback, (ULONG) p_netxduo_ether_instance,
                                     NX_ETHERNET_POLLING_INTERVAL,
                                     NX_ETHERNET_POLLING_INTERVAL, TX_AUTO_ACTIVATE))
            {
                FSP_LOG_PRINT("Failed to create \"nx ether driver timer\".");
                tx_semaphore_delete(&p_netxduo_ether_instance->p_ctrl->ether_tx_semaphore);
                p_ether_instance->p_api->close(p_ether_instance->p_ctrl);
            }
            else
            {
                driver_req_ptr->nx_ip_driver_status = NX_SUCCESS;
            }

            break;
        }

        case NX_LINK_DISABLE:
        {
            /* Delete RTOS objects. */
            rm_netxduo_ether_cleanup(p_netxduo_ether_instance);

            break;
        }

        case NX_LINK_PACKET_SEND:
        case NX_LINK_PACKET_BROADCAST:
        case NX_LINK_ARP_SEND:
        case NX_LINK_ARP_RESPONSE_SEND:
        case NX_LINK_RARP_SEND:
        {
            if (NX_TRUE != interface_ptr->nx_interface_link_up)
            {
                /* THe link has not been established yet. */
                driver_req_ptr->nx_ip_driver_status = NX_INVALID_INTERFACE;

                FSP_LOG_PRINT("Cannot transmit Ethernet packets because the link is down.");

                /* Release the NetX packet because it cannot be sent. */
                if (NX_SUCCESS != nx_packet_transmit_release(driver_req_ptr->nx_ip_driver_packet))
                {
                    FSP_LOG_PRINT("Failed to release transmit packet.");
                }

                return;
            }

            NX_PACKET * packet_ptr = driver_req_ptr->nx_ip_driver_packet;

            /* Adjust prepend pointer to make room for Ethernet header. */
            UCHAR * p_packet_prepend = packet_ptr->nx_packet_prepend_ptr - NX_ETHERNET_SIZE;
            UINT    packet_length    = packet_ptr->nx_packet_length + NX_ETHERNET_SIZE;

            /* Setup the Ethernet frame pointer to build the Ethernet frame.  Backup another 2
             * bytes to get 32-bit word alignment.  */
            ULONG * ethernet_frame_ptr = (ULONG *) (p_packet_prepend - 2);

            /* Build the Ethernet frame.  */
            *ethernet_frame_ptr       = driver_req_ptr->nx_ip_driver_physical_address_msw;
            *(ethernet_frame_ptr + 1) = driver_req_ptr->nx_ip_driver_physical_address_lsw;
            *(ethernet_frame_ptr + 2) = (interface_ptr->nx_interface_physical_address_msw << 16) |
                                        (interface_ptr->nx_interface_physical_address_lsw >> 16);
            *(ethernet_frame_ptr + 3) = (interface_ptr->nx_interface_physical_address_lsw << 16);

            if (driver_req_ptr->nx_ip_driver_command == NX_LINK_ARP_SEND)
            {
                *(ethernet_frame_ptr + 3) |= NX_ETHERNET_ARP;
            }
            else if (driver_req_ptr->nx_ip_driver_command == NX_LINK_ARP_RESPONSE_SEND)
            {
                *(ethernet_frame_ptr + 3) |= NX_ETHERNET_ARP;
            }

#if RM_NETXDUO_ETHER_RARP_SUPPORT
            else if (driver_req_ptr->nx_ip_driver_command == NX_LINK_RARP_SEND)
            {
                *(ethernet_frame_ptr + 3) |= NX_ETHERNET_RARP;
            }
#endif
            else if (packet_ptr->nx_packet_ip_version == 4)
            {
                *(ethernet_frame_ptr + 3) |= NX_ETHERNET_IP;
            }
            else
            {
                *(ethernet_frame_ptr + 3) |= NX_ETHERNET_IPV6;
            }

            /* Endian swapping if NX_LITTLE_ENDIAN is defined.  */
            NX_CHANGE_ULONG_ENDIAN(*(ethernet_frame_ptr));
            NX_CHANGE_ULONG_ENDIAN(*(ethernet_frame_ptr + 1));
            NX_CHANGE_ULONG_ENDIAN(*(ethernet_frame_ptr + 2));
            NX_CHANGE_ULONG_ENDIAN(*(ethernet_frame_ptr + 3));

            /* Zero-pad if the packet is smaller than the minimum packet size. */
            if (packet_length < NX_ETHERNET_MIN_TRANSMIT_SIZE)
            {
                memset(p_packet_prepend + packet_length, 0, NX_ETHERNET_MIN_TRANSMIT_SIZE - packet_length);
                packet_length = NX_ETHERNET_MIN_TRANSMIT_SIZE;
            }

            if (TX_SUCCESS !=
                tx_semaphore_get(&p_netxduo_ether_instance->p_ctrl->ether_tx_semaphore, NX_IP_PERIODIC_RATE))
            {
                /* Set driver status to indicate that the packet was not transmitted. */
                driver_req_ptr->nx_ip_driver_status = NX_TX_QUEUE_DEPTH;

                FSP_LOG_PRINT("No space in the Ethernet transmit queue.");

                return;
            }

            /* Store the NetX Packet so that it can be released after transmission is completed. */
            UINT index = p_netxduo_ether_instance->p_ctrl->tx_packet_index;
            p_netxduo_ether_instance->p_cfg->p_tx_packets[index] = packet_ptr;

            /* Transmit the Ethernet packet. */
            fsp_err_t err = p_ether_instance->p_api->write(p_ether_instance->p_ctrl, p_packet_prepend, packet_length);

            if (FSP_SUCCESS != err)
            {
                /* Set driver status to indicate that the packet was not transmitted. */
                driver_req_ptr->nx_ip_driver_status = NX_TX_QUEUE_DEPTH;

                FSP_LOG_PRINT("Failed to transmit the Ethernet packet.");

                return;
            }

            /* Increment the index used to store the NetX packet. */
            p_netxduo_ether_instance->p_ctrl->tx_packet_index = (index + 1U) %
                                                                p_ether_instance->p_cfg->num_tx_descriptors;

            break;
        }

        case NX_LINK_MULTICAST_JOIN:
        {
            /* Store the multicast MAC address in list at the next available location. */
            uint32_t i;
            for (i = 0; i < NX_MAX_MULTICAST_GROUPS; i++)
            {
                if ((p_netxduo_ether_instance->p_ctrl->multicast_mac_addresses[i].mac_address_msw == 0U) &&
                    (p_netxduo_ether_instance->p_ctrl->multicast_mac_addresses[i].mac_address_lsw == 0U))
                {
                    p_netxduo_ether_instance->p_ctrl->multicast_mac_addresses[i].mac_address_msw =
                        driver_req_ptr->nx_ip_driver_physical_address_msw;
                    p_netxduo_ether_instance->p_ctrl->multicast_mac_addresses[i].mac_address_lsw =
                        driver_req_ptr->nx_ip_driver_physical_address_lsw;
                    break;
                }
            }

            if (NX_MAX_MULTICAST_GROUPS == i)
            {
                driver_req_ptr->nx_ip_driver_status = NX_NO_MORE_ENTRIES;
            }

            break;
        }

        case NX_LINK_MULTICAST_LEAVE:
        {
            /* Remove the multicast MAC address from the list. */
            uint32_t i;
            for (i = 0; i < NX_MAX_MULTICAST_GROUPS; i++)
            {
                if ((p_netxduo_ether_instance->p_ctrl->multicast_mac_addresses[i].mac_address_msw ==
                     driver_req_ptr->nx_ip_driver_physical_address_msw) &&
                    (p_netxduo_ether_instance->p_ctrl->multicast_mac_addresses[i].mac_address_lsw ==
                     driver_req_ptr->nx_ip_driver_physical_address_lsw))
                {
                    p_netxduo_ether_instance->p_ctrl->multicast_mac_addresses[i].mac_address_msw = 0U;
                    p_netxduo_ether_instance->p_ctrl->multicast_mac_addresses[i].mac_address_lsw = 0U;
                    break;
                }
            }

            if (NX_MAX_MULTICAST_GROUPS == i)
            {
                driver_req_ptr->nx_ip_driver_status = NX_ENTRY_NOT_FOUND;
            }

            break;
        }

        case NX_LINK_DEFERRED_PROCESSING:
        {
            /* linkProcess will call the Ethernet callback from the ip task when the link changes. */
            if (0U != ((ether_instance_ctrl_t *) p_ether_instance->p_ctrl)->open)
            {
                p_ether_instance->p_api->linkProcess(p_ether_instance->p_ctrl);
            }

            break;
        }

        case NX_LINK_GET_STATUS:
        {
            /* Return the link status in the supplied return pointer.  */
            *(driver_req_ptr->nx_ip_driver_return_ptr) =
                driver_req_ptr->nx_ip_driver_ptr->nx_ip_interface[p_ether_instance->p_cfg->channel].nx_interface_link_up;
            break;
        }

        case NX_LINK_SET_PHYSICAL_ADDRESS:
        {
            if (p_netxduo_ether_instance->p_ctrl->p_interface->nx_interface_link_up)
            {
                /* The MAC address cannot be changed while the link is up. */
                FSP_LOG_PRINT("Failed to update the MAC address because the link is up.");
                driver_req_ptr->nx_ip_driver_status = NX_NOT_SUPPORTED;
            }
            else
            {
                uint8_t * p_mac_address = p_ether_instance->p_cfg->p_mac_address;

                uint32_t physical_msw = driver_req_ptr->nx_ip_driver_physical_address_msw;
                uint32_t physical_lsw = driver_req_ptr->nx_ip_driver_physical_address_lsw;

                /* Update the MAC address in the r_ether configuration. */
                p_mac_address[0] = (uint8_t) (physical_msw >> 8U) & UINT8_MAX;
                p_mac_address[1] = (uint8_t) (physical_msw >> 0U) & UINT8_MAX;
                p_mac_address[2] = (uint8_t) (physical_lsw >> 24U) & UINT8_MAX;
                p_mac_address[3] = (uint8_t) (physical_lsw >> 16U) & UINT8_MAX;
                p_mac_address[4] = (uint8_t) (physical_lsw >> 8U) & UINT8_MAX;
                p_mac_address[5] = (uint8_t) (physical_lsw >> 0U) & UINT8_MAX;
            }

            break;
        }

        default:
        {
            break;
        }
    }
}

/*******************************************************************************************************************//**
 * Delete all unused rtos objects.
 **********************************************************************************************************************/
static void rm_netxduo_ether_cleanup (rm_netxduo_ether_instance_t * p_netxduo_ether_instance)
{
    /* Set interface link status to down. */
    p_netxduo_ether_instance->p_ctrl->p_interface->nx_interface_link_up = NX_FALSE;

    ether_instance_t const * p_ether_instance = p_netxduo_ether_instance->p_cfg->p_ether_instance;

    CHAR         * semaphore_name;
    ULONG          semaphore_current_value;
    TX_THREAD    * semaphore_first_suspended;
    ULONG          semaphore_suspended_count;
    TX_SEMAPHORE * semaphore_next_semaphore;
    uint32_t       timeout_count = NX_ETHERNET_POLLING_TIMEOUT;

    /* Wait for all transmit packets to be sent before closing the Ethernet driver.
     * If the ETHERC peripheral is reset while packets are being transmitted, then
     * invalid data may be observed on the TXD lines.
     *
     * See section 31.2.1 "EDMAC Mode Register (EDMR)" in the RA6M3 manual R01UH0886EJ0110.
     */
    while (1)
    {
        _txe_semaphore_info_get(&p_netxduo_ether_instance->p_ctrl->ether_tx_semaphore,
                                &semaphore_name,
                                &semaphore_current_value,
                                &semaphore_first_suspended,
                                &semaphore_suspended_count,
                                &semaphore_next_semaphore);

        if ((semaphore_current_value < p_ether_instance->p_cfg->num_tx_descriptors) && --timeout_count)
        {
            tx_thread_sleep(NX_ETHERNET_POLLING_INTERVAL);
        }
        else
        {
            break;
        }
    }

    if (0 == timeout_count)
    {
        FSP_LOG_PRINT("Failed to transmit remaining packets.");
    }

    /* Close the ether driver. */
    p_ether_instance->p_api->close(p_ether_instance->p_ctrl);

    /* Reset the tx packet index. */
    p_netxduo_ether_instance->p_ctrl->tx_packet_index             = 0;
    p_netxduo_ether_instance->p_ctrl->tx_packet_transmitted_index = 0;

    /* Delete RTOS Objects. */
    tx_semaphore_delete(&p_netxduo_ether_instance->p_ctrl->ether_tx_semaphore);
    tx_timer_deactivate(&p_netxduo_ether_instance->p_ctrl->event_timer);
    tx_timer_delete(&p_netxduo_ether_instance->p_ctrl->event_timer);

    /* Release all transmit packets. */
    for (uint32_t i = 0; i < p_ether_instance->p_cfg->num_tx_descriptors; i++)
    {
        if (NULL != p_netxduo_ether_instance->p_cfg->p_tx_packets[i])
        {
            nx_packet_release(p_netxduo_ether_instance->p_cfg->p_tx_packets[i]);
            p_netxduo_ether_instance->p_cfg->p_tx_packets[i] = NULL;
        }
    }

    /* Release all receive packets. */
    for (uint32_t i = 0; i < p_ether_instance->p_cfg->num_rx_descriptors; i++)
    {
        nx_packet_release(p_netxduo_ether_instance->p_cfg->p_rx_packets[i]);
    }
}

/*******************************************************************************************************************//**
 * Process all Ethernet packets that have been received.
 **********************************************************************************************************************/
void rm_netxduo_ether_receive_packet (rm_netxduo_ether_instance_t * p_netxduo_ether_instance)
{
    NX_PACKET             ** p_nx_buffers     = p_netxduo_ether_instance->p_cfg->p_rx_packets;
    ether_instance_t const * p_ether_instance = p_netxduo_ether_instance->p_cfg->p_ether_instance;
    uint8_t                * p_mac_address    = p_ether_instance->p_cfg->p_mac_address;
    ULONG mac_msw = (ULONG) ((p_mac_address[0] << 8) | (p_mac_address[1] << 0));
    ULONG mac_lsw =
        (ULONG) ((p_mac_address[2] << 24) | (p_mac_address[3] << 16) | (p_mac_address[4] << 8) |
                 (p_mac_address[5] << 0));
    fsp_err_t   err;
    NX_PACKET * p_nx_packet = NULL;
    do
    {
        /* Get a pointer to the packet received. */
        uint8_t * p_buffer_out;
        uint32_t  length;
        err = p_ether_instance->p_api->read(p_ether_instance->p_ctrl, &p_buffer_out, &length);
        if (FSP_SUCCESS != err)
        {
            break;
        }

        /* Allocate NetX packet to copy data into. */
        if (NX_SUCCESS !=
            nx_packet_allocate(p_netxduo_ether_instance->p_ctrl->p_ip->nx_ip_default_packet_pool, &p_nx_packet,
                               NX_RECEIVE_PACKET, NX_NO_WAIT))
        {
            /* If a NetX packet could not be allocated, then the received packet must be dropped in order to receive the next packet. */
            FSP_LOG_PRINT("Failed to allocate NetX Packet.");

            /* Update the buffer pointer in the buffer descriptor. */
            if (FSP_SUCCESS != p_ether_instance->p_api->rxBufferUpdate(p_ether_instance->p_ctrl, p_buffer_out))
            {
                FSP_LOG_PRINT("Failed to update buffer in r_ether driver.");
            }
        }
        else
        {
            /*
             * Make sure that the buffer is 32 byte aligned (See section 31.3.1.2 "Receive descriptor" in the RA6M3 User Manual R01UH0886EJ0100)
             */
            p_nx_packet->nx_packet_prepend_ptr =
                (UCHAR *) (((uint32_t) p_nx_packet->nx_packet_prepend_ptr + 31U) & ~(31U));

            /* Update the buffer pointer in the buffer descriptor. */
            if (FSP_SUCCESS !=
                p_ether_instance->p_api->rxBufferUpdate(p_ether_instance->p_ctrl, p_nx_packet->nx_packet_prepend_ptr))
            {
                FSP_LOG_PRINT("Failed to update buffer in r_ether driver.");
                break;
            }

            /* Get the index of the NetX packet that was received. */
            uint32_t index = p_netxduo_ether_instance->p_ctrl->rx_packet_index;

            /*
             * If invalid Ethernet frames were received or if the driver previously failed to allocate a NetX packet, the index will need to be
             * incremented in order to get the NetX packet associated with the current buffer that has been received.
             */
            for (uint32_t i = 0;
                 p_nx_buffers[index]->nx_packet_prepend_ptr != p_buffer_out &&
                 i < p_ether_instance->p_cfg->num_rx_descriptors;
                 i++)
            {
                index = (index + 1) % p_ether_instance->p_cfg->num_rx_descriptors; // NOLINT(clang-analyzer-core.DivideZero)
                FSP_LOG_PRINT("Skipping to the next NetX packet.");
            }

            /* Save the expected index of the next NetX packet index. */
            p_netxduo_ether_instance->p_ctrl->rx_packet_index = (index + 1) % // NOLINT(clang-analyzer-core.DivideZero)
                                                                p_ether_instance->p_cfg->num_rx_descriptors;

            /* Verify that the NetX packet was found. */
            if (p_nx_buffers[index]->nx_packet_prepend_ptr != p_buffer_out)
            {
                FSP_LOG_PRINT("Could not find the NetX packet associated with the received buffer.");
            }
            else
            {
                /* Pick up the destination MAC address from the packet.  */
                ULONG destination_address_msw = (ULONG) *(p_nx_buffers[index]->nx_packet_prepend_ptr);
                destination_address_msw = (destination_address_msw << 8) |
                                          (ULONG) *(p_nx_buffers[index]->nx_packet_prepend_ptr + 1);
                ULONG destination_address_lsw = (ULONG) *(p_nx_buffers[index]->nx_packet_prepend_ptr + 2);
                destination_address_lsw = (destination_address_lsw << 8) |
                                          (ULONG) *(p_nx_buffers[index]->nx_packet_prepend_ptr + 3);
                destination_address_lsw = (destination_address_lsw << 8) |
                                          (ULONG) *(p_nx_buffers[index]->nx_packet_prepend_ptr + 4);
                destination_address_lsw = (destination_address_lsw << 8) |
                                          (ULONG) *(p_nx_buffers[index]->nx_packet_prepend_ptr + 5);

                bool multicast_group = false;

                /* Check if the packet is an IPv4 Multicast packet. */
                if ((destination_address_msw == 0x00000100U) && ((destination_address_lsw >> 24U) == 0x5EU)) // NOLINT(readability-magic-numbers)
                {
                    /* Check if the IP instance is a member of the group. */
                    for (uint32_t i = 0; i < NX_MAX_MULTICAST_GROUPS; i++)
                    {
                        /* IPv4 multicast MAC addreses always begin with 0x0100 so only destination_address_lsw needs to be checked. */
                        if (destination_address_lsw ==
                            p_netxduo_ether_instance->p_ctrl->multicast_mac_addresses[i].mac_address_lsw)
                        {
                            multicast_group = true;
                            break;
                        }
                    }
                }

                /* Only process packets that are meant for this mac address (dest=Broadcast/mac_address). */
                if (((destination_address_msw == ((ULONG) 0x0000FFFF)) &&  // NOLINT(readability-magic-numbers)
                     (destination_address_lsw == ((ULONG) 0xFFFFFFFF))) || // NOLINT(readability-magic-numbers)
                    ((destination_address_msw == mac_msw) &&               // NOLINT(readability-magic-numbers)
                     (destination_address_lsw == mac_lsw)) ||              // NOLINT(readability-magic-numbers)
                    (destination_address_msw == ((ULONG) 0x00003333)) ||   // NOLINT(readability-magic-numbers)
                    ((destination_address_msw == 0) && (destination_address_lsw == 0)) ||
                    multicast_group)
                {
                    /* Get the Ethernet packet id. */
                    UINT packet_type = (((UINT) (*(p_nx_buffers[index]->nx_packet_prepend_ptr + 12))) << 8) |
                                       ((UINT) (*(p_nx_buffers[index]->nx_packet_prepend_ptr + 13)));

                    if ((packet_type == NX_ETHERNET_IP) ||
#ifndef NX_DISABLE_IPV6
                        (packet_type == NX_ETHERNET_IPV6) ||
#endif
                        (packet_type == NX_ETHERNET_ARP)
#if RM_NETXDUO_ETHER_RARP_SUPPORT
                        || (packet_type == NX_ETHERNET_RARP)
#endif
                        )
                    {
                        /* Update length. */
                        p_nx_buffers[index]->nx_packet_length = length;

                        /* Move the append ptr to the new end of data. */
                        p_nx_buffers[index]->nx_packet_append_ptr = p_nx_buffers[index]->nx_packet_prepend_ptr +
                                                                    p_nx_buffers[index]->nx_packet_length;

                        /* Remove the Ethernet packet header. */
                        uint32_t padding = p_ether_instance->p_cfg->padding;
                        p_nx_buffers[index]->nx_packet_prepend_ptr += (NX_ETHERNET_SIZE + padding);
                        p_nx_buffers[index]->nx_packet_length      -= (NX_ETHERNET_SIZE + padding);

                        switch (packet_type)
                        {
                            case NX_ETHERNET_IP:
#ifndef NX_DISABLE_IPV6
                            case NX_ETHERNET_IPV6:
#endif
                                {
                                    /* Process the IP packet. */
                                    _nx_ip_packet_deferred_receive(p_netxduo_ether_instance->p_ctrl->p_ip,
                                                                   p_nx_buffers[index]);
                                    break;
                                }

                            case NX_ETHERNET_ARP:
                            {
                                /* Process the ARP packet. */
                                _nx_arp_packet_deferred_receive(p_netxduo_ether_instance->p_ctrl->p_ip,
                                                                p_nx_buffers[index]);
                                break;
                            }

#if RM_NETXDUO_ETHER_RARP_SUPPORT
                            case NX_ETHERNET_RARP:
                            {
                                /* Process the RARP packet. */
                                _nx_rarp_packet_deferred_receive(p_netxduo_ether_instance->p_ctrl->p_ip,
                                                                 p_nx_buffers[index]);
                                break;
                            }
#endif

                            default:
                            {
                                break;
                            }
                        }
                    }
                    else
                    {
                        if (NX_SUCCESS != nx_packet_release(p_nx_buffers[index]))
                        {
                            FSP_LOG_PRINT("Failed to release NetX Packet.");
                        }
                    }
                }
                else
                {
                    if (NX_SUCCESS != nx_packet_release(p_nx_buffers[index]))
                    {
                        FSP_LOG_PRINT("Failed to release NetX Packet.");
                    }
                }
            }

            /* Store pointer to the newly allocated NetX Packet at the index where it was written into the r_ether buffer descriptor. */
            p_nx_buffers[index] = p_nx_packet;
        }
    } while (FSP_SUCCESS == err);
}

/*******************************************************************************************************************//**
 * Timer callback for notifying the driver to poll the Ethernet link status.
 **********************************************************************************************************************/
void rm_event_timer_callback (ULONG data)
{
    rm_netxduo_ether_instance_t * p_netxduo_ether_instance = (rm_netxduo_ether_instance_t *) data;

    /* Call NetX to register a deferred event.  */
    _nx_ip_driver_deferred_processing(p_netxduo_ether_instance->p_ctrl->p_ip);
}

/*******************************************************************************************************************//**
 * Callback from r_ether ISR.
 *
 * Notifies ether_thread when a packet is received using a semaphore.
 * Processes Link Up and Link Down events.
 **********************************************************************************************************************/
void rm_netxduo_ether_callback (ether_callback_args_t * p_args)
{
    /* Get the ether interface from a global pointer because r_ether does not set p_contect in p_args. */
    rm_netxduo_ether_instance_t * p_netxduo_ether_instance = (rm_netxduo_ether_instance_t *) p_args->p_context;
    ether_instance_t const      * p_ether_instance         = p_netxduo_ether_instance->p_cfg->p_ether_instance;

    /* Either the callback was called from an ISR or it was called from the linkProcess. */
    switch (p_args->event)
    {
        case ETHER_EVENT_INTERRUPT:
        {
            /* Packet Transmitted. */
            uint32_t tx_packet_transmitted_index = p_netxduo_ether_instance->p_ctrl->tx_packet_transmitted_index;
            if ((ETHER_ISR_EE_TC_MASK == (p_args->status_eesr & ETHER_ISR_EE_TC_MASK)) &&
                (NULL != p_netxduo_ether_instance->p_cfg->p_tx_packets[tx_packet_transmitted_index]))
            {
                uint8_t * p_buffer_current = NULL;
                uint8_t * p_buffer_last    = NULL;

                /* Get the pointer to the last buffer that was transmitted. */
                if (FSP_SUCCESS != p_ether_instance->p_api->txStatusGet(p_ether_instance->p_ctrl, &p_buffer_last))
                {
                    FSP_LOG_PRINT("Failed to get the last buffer transmitted.");
                }

                do
                {
                    /* Get the pointer to the next NX_PACKET to release. */
                    NX_PACKET * p_nx_packet_current =
                        p_netxduo_ether_instance->p_cfg->p_tx_packets[tx_packet_transmitted_index];

                    if (NULL != p_nx_packet_current)
                    {
                        /* Calculate the pointer to the start of the Ethernet packet that was transmitted. */
                        p_buffer_current = p_nx_packet_current->nx_packet_prepend_ptr - NX_ETHERNET_SIZE;

                        /* Release the NX_PACKET. */
                        if (TX_SUCCESS != nx_packet_transmit_release(p_nx_packet_current))
                        {
                            FSP_LOG_PRINT("Failed to release NetX transmit Packet.");
                        }

                        /* Remove the NX_PACKET from the transmit queue. */
                        p_netxduo_ether_instance->p_cfg->p_tx_packets[tx_packet_transmitted_index] = NULL;

                        /* Synchronize the IP task with the transmit complete ISR. */
                        if (TX_SUCCESS !=
                            tx_semaphore_ceiling_put(&p_netxduo_ether_instance->p_ctrl->ether_tx_semaphore,
                                                     p_ether_instance->p_cfg->num_tx_descriptors))
                        {
                            FSP_LOG_PRINT("Failed to increment tx semaphore.");
                        }
                    }
                    else
                    {
                        FSP_LOG_PRINT("Failed to get the last NX_PACKET transmitted.");
                    }

                    /* Calculate the index of the next NX_PACKET. */
                    tx_packet_transmitted_index = tx_packet_transmitted_index + 1;
                    if (tx_packet_transmitted_index == p_ether_instance->p_cfg->num_tx_descriptors)
                    {
                        tx_packet_transmitted_index = 0;
                    }
                } while (p_buffer_current != p_buffer_last);

                p_netxduo_ether_instance->p_ctrl->tx_packet_transmitted_index = tx_packet_transmitted_index;
            }

            /* Packet received. */
            if (ETHER_ISR_EE_FR_MASK == (p_args->status_eesr & ETHER_ISR_EE_FR_MASK))
            {
                rm_netxduo_ether_receive_packet(p_netxduo_ether_instance);
            }

            break;
        }

        case ETHER_EVENT_LINK_ON:
        {
            /* Disable Ethernet IRQs so that the receive buffer descriptor can be initialized without being interrupted. */
            R_BSP_IrqDisable(p_ether_instance->p_cfg->irq);

            /* Allocate NetX Packets required for receiving data. */
            NX_PACKET ** p_rx_buffers = p_netxduo_ether_instance->p_cfg->p_rx_packets;
            for (uint32_t i = 0; i < p_ether_instance->p_cfg->num_rx_descriptors; i++)
            {
                if (NX_SUCCESS !=
                    nx_packet_allocate(p_netxduo_ether_instance->p_ctrl->p_ip->nx_ip_default_packet_pool,
                                       &p_rx_buffers[i], NX_RECEIVE_PACKET, TX_NO_WAIT))
                {
                    FSP_LOG_PRINT("Failed to allocate NetX Packet.");
                }

                /*
                 * Make sure that the buffer is 32 byte aligned (See section 31.3.1.2 "Receive descriptor" in the RA6M3 User Manual R01UH0886EJ0100)
                 */
                p_rx_buffers[i]->nx_packet_prepend_ptr =
                    (UCHAR *) (((uint32_t) p_rx_buffers[i]->nx_packet_prepend_ptr + 31U) & ~(31U));

                /* Update the buffer pointer in the buffer descriptor. */
                if (FSP_SUCCESS !=
                    p_ether_instance->p_api->rxBufferUpdate(p_ether_instance->p_ctrl,
                                                            p_rx_buffers[i]->nx_packet_prepend_ptr))
                {
                    FSP_LOG_PRINT("Failed to update buffer in r_ether driver.");
                }
            }

            R_BSP_IrqEnable(p_ether_instance->p_cfg->irq);

            /* Notify NetX that the link is up. */
            p_netxduo_ether_instance->p_ctrl->p_interface->nx_interface_link_up = NX_TRUE;
            _nx_ip_driver_link_status_event(p_netxduo_ether_instance->p_ctrl->p_ip, p_args->channel);
            break;
        }

        case ETHER_EVENT_LINK_OFF:
        {
            /*
             * When the link is re-established, the Ethernet driver will reset all of the buffer descriptors.
             * Release NetX Packets (New packets will be allocated when the link is up).
             */
            p_netxduo_ether_instance->p_ctrl->tx_packet_index             = 0;
            p_netxduo_ether_instance->p_ctrl->tx_packet_transmitted_index = 0;
            NX_PACKET ** p_tx_buffers = p_netxduo_ether_instance->p_cfg->p_tx_packets;
            for (uint32_t i = 0; i < p_ether_instance->p_cfg->num_tx_descriptors; i++)
            {
                if (NULL != p_tx_buffers[i])
                {
                    if (NX_SUCCESS != nx_packet_release(p_tx_buffers[i]))
                    {
                        FSP_LOG_PRINT("Failed to release NetX Packet.");
                    }

                    if (NX_SUCCESS !=
                        tx_semaphore_ceiling_put(&p_netxduo_ether_instance->p_ctrl->ether_tx_semaphore,
                                                 p_ether_instance->p_cfg->num_tx_descriptors))
                    {
                        FSP_LOG_PRINT("Failed to increment tx semaphore.");
                    }

                    p_tx_buffers[i] = NULL;
                }
            }

            p_netxduo_ether_instance->p_ctrl->rx_packet_index = 0;
            NX_PACKET ** p_rx_buffers = p_netxduo_ether_instance->p_cfg->p_rx_packets;
            for (uint32_t i = 0; i < p_ether_instance->p_cfg->num_rx_descriptors; i++)
            {
                if (NX_SUCCESS != nx_packet_release(p_rx_buffers[i]))
                {
                    FSP_LOG_PRINT("Failed to release NetX Packet.");
                }
            }

            /* Notify NetX that the link is down. */
            p_netxduo_ether_instance->p_ctrl->p_interface->nx_interface_link_up = NX_FALSE;
            _nx_ip_driver_link_status_event(p_netxduo_ether_instance->p_ctrl->p_ip, p_args->channel);
            break;
        }

        default:
        {
            break;
        }
    }
}
