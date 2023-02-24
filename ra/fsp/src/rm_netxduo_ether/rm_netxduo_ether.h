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

#include "nx_api.h"
#include "r_ether_api.h"

#ifndef RM_NETXDUO_ETHER_H
 #define RM_NETXDUO_ETHER_H

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

typedef struct
{
    /* Pointer to the ip instance that the driver is attached to. */
    NX_IP * p_ip;

    /* Pointer to the interface structure associated with this driver. */
    NX_INTERFACE * p_interface;

    /* Semaphore used to synchronize the ip task with the transmit complete ISR. */
    TX_SEMAPHORE ether_tx_semaphore;

    /* Timer instance for polling the Ethernet link status. */
    TX_TIMER event_timer;

    /* Index to store the next transmit packet. */
    UINT tx_packet_index;

    /* Index of the next transmit packet to release. */
    UINT tx_packet_transmitted_index;

    /* Index into the receive descriptor list. */
    UINT rx_packet_index;

    /* Multicast MAC addresses to process during packet reception. */
    struct
    {
        uint32_t mac_address_msw;
        uint32_t mac_address_lsw;
    } multicast_mac_addresses[NX_MAX_MULTICAST_GROUPS];
} rm_netxduo_ether_ctrl_t;

typedef struct
{
    /** r_ether instance. */
    ether_instance_t const * p_ether_instance;

    /**
     * The maximum transfer unit for the interface.
     *
     * Note:
     *  - The Ethernet instance must have a buffer size larger than the MTU.
     *  - The Ethernet instance buffer size must be a multiple of 32.
     */
    UINT mtu;

    /* Used to keep track of the NetX packets that have been transmitted so that the driver can release them.
     * Note:
     * - Needs to be an array with size equal to the number of TX buffer descriptors defined in p_ether_instance.
     */
    NX_PACKET ** volatile p_tx_packets;

    /* Used to keep track of the NetX packets that have been written into the ether receive descriptor.
     * Note:
     * - Needs to be an array with size equal to the number of RX buffer descriptors defined in p_ether_instance.
     */
    NX_PACKET ** p_rx_packets;
} rm_netxduo_ether_cfg_t;

typedef struct
{
    rm_netxduo_ether_ctrl_t * p_ctrl;
    rm_netxduo_ether_cfg_t  * p_cfg;
} rm_netxduo_ether_instance_t;

void rm_netxduo_ether(NX_IP_DRIVER * driver_req_ptr, rm_netxduo_ether_instance_t * p_netxduo_ether_instance);
void rm_netxduo_ether_callback(ether_callback_args_t * p_args);

/** Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
