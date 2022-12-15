/**************************************************************************/

/*                                                                        */
/*       Copyright (c) Microsoft Corporation. All rights reserved.        */
/*                                                                        */
/*       This software is licensed under the Microsoft Software License   */
/*       Terms for Microsoft Azure RTOS. Full text of the license can be  */
/*       found in the LICENSE file at https://aka.ms/AzureRTOS_EULA       */
/*       and in the root directory of this software.                      */
/*                                                                        */
/**************************************************************************/

/**************************************************************************/
/**************************************************************************/
/**                                                                       */
/** NetX Component                                                        */
/**                                                                       */
/** FSP WiFi driver                                                       */
/**                                                                       */
/**************************************************************************/
/**************************************************************************/

/* Indicate that driver source is being compiled.  */

#include "rm_netxduo_wifi.h"
#include "stdint.h"

/* Timeout err, this is an internal define from the Silex driver module */
#define RM_NETXDUO_WIFI_SILEX_ERR_TIMEOUT                        (-4)

#ifndef RM_NETXDUO_WIFI_IP_MTU
 #define RM_NETXDUO_WIFI_IP_MTU                                  1500
#endif                                 /* RM_NETXDUO_WIFI_IP_MTU */

#ifndef RM_NETXDUO_WIFI_DRIVER_THREAD_STACK_SIZE
 #define RM_NETXDUO_WIFI_DRIVER_THREAD_STACK_SIZE                1024
#endif                                 /* RM_NETXDUO_WIFI_DRIVER_THREAD_STACK_SIZE  */

/* Define the maximum sockets at the same time. This is limited by hardware TCP/IP on Silex WiFi driver.  */
#define RM_NETXDUO_WIFI_SOCKETS_MAXIMUM                          WIFI_ONCHIP_SILEX_CFG_NUM_CREATEABLE_SOCKETS

/* Define timeouts for TCP recv semaphores */
#ifndef RM_NETXDUO_WIFI_BYTE_START_SEMAPHORE_TIMEOUT_MS
 #define RM_NETXDUO_WIFI_BYTE_START_SEMAPHORE_TIMEOUT_MS         (50)
#endif
#ifndef RM_NETXDUO_WIFI_PACKET_COMPLETE_SEMAPHORE_TIMEOUT_MS
 #define RM_NETXDUO_WIFI_PACKET_COMPLETE_SEMAPHORE_TIMEOUT_MS    (100)
#endif
#define RM_NETXDUO_WIFI_MIN_TICKS                                (2)

/* Define the maximum wait timeout in ms for socket send. This is limited by hardware TCP/IP on Silex WiFi driver.  */
#define RM_NETXDUO_WIFI_SOCKET_SEND_TIMEOUT_MAXIMUM              (3000)
#define RM_NETXDUO_WIFI_SOCKET_UDP_SEND_TIMEOUT_MAXIMUM          (200)

#define RM_NETXDUO_WIFI_MAC_LENGTH                               (6)

#define TickType_t                                               unsigned long
#define MS_TO_TICKS(xTimeInMs)    ((TickType_t) (((TickType_t) (xTimeInMs) * (TickType_t) TX_TIMER_TICKS_PER_SECOND * \
                                                  1ULL) /                                                             \
                                                 (TickType_t) 1000ULL))

#define RM_NETXDUO_WIFI_TIME_TICKS_WAIT_DIV                      (1000)
#define RM_NETXDUO_WIFI_SOCKET_TYPE_TCP                          (0)
#define RM_NETXDUO_WIFI_SOCKET_TYPE_UDP                          (2)
#define RM_NETXDUO_WIFI_SOCKET_IPV4                              (4)

/* NetX Driver States */
#define NX_DRIVER_STATE_NOT_INITIALIZED                          1
#define NX_DRIVER_STATE_INITIALIZE_FAILED                        2
#define NX_DRIVER_STATE_INITIALIZED                              3
#define NX_DRIVER_STATE_LINK_ENABLED                             4
#define NX_DRIVER_ERROR                                          90

/* Driver Thread Events */
#define RM_NETXDUO_DRIVER_THREAD_EVENT_DEINITIALIZE              (0x1)

/* Define basic network driver information typedef.  */

typedef struct NX_DRIVER_INFORMATION_STRUCT
{
    /* NetX IP instance that this driver is attached to.  */
    NX_IP * nx_driver_information_ip_ptr;

    /* Driver's current states.  */
    ULONG nx_driver_information_states;

    /* Packet pool used for receiving packets. */
    NX_PACKET_POOL * nx_driver_information_packet_pool_ptr;

    /* Define the driver interface association.  */
    NX_INTERFACE * nx_driver_information_interface;
} NX_DRIVER_INFORMATION;

/* Define socket structure for hardware TCP/IP.  */

typedef struct NX_DRIVER_SOCKET_STRUCT
{
    VOID * socket_ptr;
    UINT   protocol;
    ULONG  local_ip;
    ULONG  remote_ip;
    USHORT local_port;
    USHORT remote_port;
    UINT   socket_id;
} NX_DRIVER_SOCKET;

static NX_DRIVER_INFORMATION nx_driver_information;
static NX_DRIVER_SOCKET      nx_driver_sockets[RM_NETXDUO_WIFI_SOCKETS_MAXIMUM];
static TX_THREAD             nx_driver_thread;
static UCHAR                 nx_driver_thread_stack[RM_NETXDUO_WIFI_DRIVER_THREAD_STACK_SIZE];
static TX_EVENT_FLAGS_GROUP  nx_driver_thread_events;

/* Define the routines for processing each driver entry request.  The contents of these routines will change with
 * each driver. However, the main driver entry function will not change, except for the entry function name.  */

static VOID _nx_driver_interface_attach(NX_IP_DRIVER * driver_req_ptr);
static VOID _nx_driver_initialize(NX_IP_DRIVER * driver_req_ptr);
static VOID _nx_driver_enable(NX_IP_DRIVER * driver_req_ptr);
static VOID _nx_driver_disable(NX_IP_DRIVER * driver_req_ptr);
static VOID _nx_driver_multicast_join(NX_IP_DRIVER * driver_req_ptr);
static VOID _nx_driver_multicast_leave(NX_IP_DRIVER * driver_req_ptr);
static VOID _nx_driver_get_status(NX_IP_DRIVER * driver_req_ptr);
static VOID _nx_driver_thread_entry(ULONG thread_input);
static UINT _nx_driver_tcpip_handler(struct NX_IP_STRUCT        * ip_ptr,
                                     struct NX_INTERFACE_STRUCT * interface_ptr,
                                     VOID                       * socket_ptr,
                                     UINT                         operation,
                                     NX_PACKET                  * packet_ptr,
                                     NXD_ADDRESS                * local_ip,
                                     NXD_ADDRESS                * remote_ip,
                                     UINT                         local_port,
                                     UINT                       * remote_port,
                                     UINT                         wait_option);

/* Define the prototypes for the hardware implementation of this driver. The contents of these routines are
 * driver-specific.  */

static UINT _nx_driver_hardware_initialize(NX_IP_DRIVER * driver_req_ptr);
static UINT _nx_driver_hardware_enable(NX_IP_DRIVER * driver_req_ptr);
static UINT _nx_driver_hardware_disable(NX_IP_DRIVER * driver_req_ptr);

/**************************************************************************/
/*                                                                        */
/*  FUNCTION                                               RELEASE        */
/*                                                                        */
/*    rm_netxduo_wifi                                      PORTABLE C     */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This is the entry point of the NetX Driver. This driver             */
/*    function is responsible for initializing the network controller,    */
/*    enabling or disabling the controller as need, preparing             */
/*    a packet for transmission, and getting status information.          */
/*                                                                        */
/*  INPUT                                                                 */
/*                                                                        */
/*    driver_req_ptr                        The driver request from the   */
/*                                            IP layer.                   */
/*                                                                        */
/*  OUTPUT                                                                */
/*                                                                        */
/*    None                                                                */
/*                                                                        */
/*  CALLS                                                                 */
/*                                                                        */
/*    _nx_driver_interface_attach           Process attach request        */
/*    _nx_driver_initialize                 Process initialize request    */
/*    _nx_driver_enable                     Process link enable request   */
/*    _nx_driver_disable                    Process link disable request  */
/*    _nx_driver_multicast_join             Process multicast join request*/
/*    _nx_driver_multicast_leave            Process multicast leave req   */
/*    _nx_driver_get_status                 Process get status request    */
/*                                                                        */
/*  CALLED BY                                                             */
/*                                                                        */
/*    IP layer                                                            */
/**************************************************************************/
VOID rm_netxduo_wifi (NX_IP_DRIVER * driver_req_ptr)
{
    /* Default to successful return.  */
    driver_req_ptr->nx_ip_driver_status = NX_SUCCESS;

    /* Process according to the driver request type in the IP control
     * block.  */
    switch (driver_req_ptr->nx_ip_driver_command)
    {
        case NX_LINK_INTERFACE_ATTACH:
        {
            /* Process link interface attach requests.  */
            _nx_driver_interface_attach(driver_req_ptr);
            break;
        }

        case NX_LINK_INITIALIZE:
        {
            /* Process link initialize requests.  */
            _nx_driver_initialize(driver_req_ptr);
            break;
        }

        case NX_LINK_UNINITIALIZE:
        {
            UINT thread_state = TX_READY;

            /* Send signal for driver thread to exit */
            tx_event_flags_set(&nx_driver_thread_events, RM_NETXDUO_DRIVER_THREAD_EVENT_DEINITIALIZE, TX_OR);

            /* Wait for driver thread to exit */
            while (TX_TERMINATED != thread_state)
            {
                tx_thread_info_get(&nx_driver_thread, NULL, &thread_state, NULL, NULL, NULL, NULL, NULL, NULL);
                tx_thread_sleep(1);
            }

            /* Delete thread */
            tx_thread_delete(&nx_driver_thread);

            tx_event_flags_delete(&nx_driver_thread_events);

            break;
        }

        case NX_LINK_ENABLE:
        {
            /* Process link enable requests.  */
            _nx_driver_enable(driver_req_ptr);
            break;
        }

        case NX_LINK_DISABLE:
        {
            /* Process link disable requests.  */
            _nx_driver_disable(driver_req_ptr);
            break;
        }

        case NX_LINK_ARP_SEND:
        case NX_LINK_ARP_RESPONSE_SEND:
        case NX_LINK_PACKET_BROADCAST:
        case NX_LINK_RARP_SEND:
        case NX_LINK_PACKET_SEND:
        {
            /* Not supported by hardware TCP/IP.  */
            driver_req_ptr->nx_ip_driver_status = NX_DRIVER_ERROR;
            nx_packet_transmit_release(driver_req_ptr->nx_ip_driver_packet);
            break;
        }

        case NX_LINK_MULTICAST_JOIN:
        {
            /* Process multicast join requests.  */
            _nx_driver_multicast_join(driver_req_ptr);
            break;
        }

        case NX_LINK_MULTICAST_LEAVE:
        {
            /* Process multicast leave requests.  */
            _nx_driver_multicast_leave(driver_req_ptr);
            break;
        }

        case NX_LINK_GET_STATUS:
        {
            /* Process get status requests.  */
            _nx_driver_get_status(driver_req_ptr);
            break;
        }

        case NX_LINK_DEFERRED_PROCESSING:
        {
            /* Process driver deferred requests.  */

            /* Process a device driver function on behalf of the IP thread. */

            break;
        }

        case NX_INTERFACE_CAPABILITY_GET:
        {
            /* Return the capability of the Ethernet controller.  */
            *(driver_req_ptr->nx_ip_driver_return_ptr) = NX_INTERFACE_CAPABILITY_TCPIP_OFFLOAD;

            /* Return the success status.  */
            driver_req_ptr->nx_ip_driver_status = NX_SUCCESS;
            break;
        }

        case NX_INTERFACE_CAPABILITY_SET:
        {
            /* Process set capability requests.  */
            /* Indicate the request was successful.   */
            driver_req_ptr->nx_ip_driver_status = NX_SUCCESS;
            break;
        }

        case NX_LINK_SET_PHYSICAL_ADDRESS:
        {
            driver_req_ptr->nx_ip_driver_status = NX_NOT_SUPPORTED;
            break;
        }

        default:

            /* Invalid driver request.  */

            /* Return the unhandled command status.  */
            driver_req_ptr->nx_ip_driver_status = NX_UNHANDLED_COMMAND;
    }
}

/**************************************************************************/
/*                                                                        */
/*  FUNCTION                                               RELEASE        */
/*                                                                        */
/*    _nx_driver_interface_attach                         PORTABLE C      */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function processing the interface attach request.              */
/*                                                                        */
/*  INPUT                                                                 */
/*                                                                        */
/*    driver_req_ptr                        Driver command from the IP    */
/*                                            thread                      */
/*                                                                        */
/*  OUTPUT                                                                */
/*                                                                        */
/*    None                                                                */
/*                                                                        */
/*  CALLS                                                                 */
/*                                                                        */
/*    None                                                                */
/*                                                                        */
/*  CALLED BY                                                             */
/*                                                                        */
/*    Driver entry function                                               */
/**************************************************************************/
static VOID _nx_driver_interface_attach (NX_IP_DRIVER * driver_req_ptr)
{
    driver_req_ptr->nx_ip_driver_interface->nx_interface_capability_flag = NX_INTERFACE_CAPABILITY_TCPIP_OFFLOAD;

    /* Return successful status.  */
    driver_req_ptr->nx_ip_driver_status = NX_SUCCESS;
}

/**************************************************************************/
/*                                                                        */
/*  FUNCTION                                               RELEASE        */
/*                                                                        */
/*    _nx_driver_initialize                               PORTABLE C      */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function processing the initialize request.  The processing    */
/*    in this function is generic. All ethernet controller logic is to    */
/*    be placed in _nx_driver_hardware_initialize.                        */
/*                                                                        */
/*  INPUT                                                                 */
/*                                                                        */
/*    driver_req_ptr                        Driver command from the IP    */
/*                                            thread                      */
/*                                                                        */
/*  OUTPUT                                                                */
/*                                                                        */
/*    None                                                                */
/*                                                                        */
/*  CALLS                                                                 */
/*                                                                        */
/*    _nx_driver_hardware_initialize        Process initialize request    */
/*                                                                        */
/*  CALLED BY                                                             */
/*                                                                        */
/*    Driver entry function                                               */
/*                                                                        */
/**************************************************************************/
static VOID _nx_driver_initialize (NX_IP_DRIVER * driver_req_ptr)
{
    NX_IP        * ip_ptr;
    NX_INTERFACE * interface_ptr;
    UINT           status;

    /* Setup the driver state to not initialized.  */
    nx_driver_information.nx_driver_information_states = NX_DRIVER_STATE_NOT_INITIALIZED;

    /* Setup the IP pointer from the driver request.  */
    ip_ptr = driver_req_ptr->nx_ip_driver_ptr;

    /* Setup interface pointer.  */
    interface_ptr = driver_req_ptr->nx_ip_driver_interface;

    /* Initialize the driver's information structure.  */

    /* Default IP pointer to NULL.  */
    nx_driver_information.nx_driver_information_ip_ptr = NX_NULL;

    /* Setup the default packet pool for the driver's received packets.  */
    nx_driver_information.nx_driver_information_packet_pool_ptr = ip_ptr->nx_ip_default_packet_pool;

    /* Call the hardware-specific ethernet controller initialization.  */
    status = _nx_driver_hardware_initialize(driver_req_ptr);

    /* Determine if the request was successful.  */
    if (status == NX_SUCCESS)
    {
        uint8_t mac[RM_NETXDUO_WIFI_MAC_LENGTH];

        /* Successful hardware initialization.  */

        /* Setup driver information to point to IP pointer.  */
        nx_driver_information.nx_driver_information_ip_ptr    = ip_ptr;
        nx_driver_information.nx_driver_information_interface = interface_ptr;

        /* Setup the link maximum transfer unit. */
        interface_ptr->nx_interface_ip_mtu_size = RM_NETXDUO_WIFI_IP_MTU;

        /* Setup the physical address of this IP instance.  */
        fsp_err_t err = rm_wifi_onchip_silex_mac_addr_get(mac);
        if (FSP_SUCCESS != err)
        {
            /* Initialization failed.  Indicate that the request failed.  */
            driver_req_ptr->nx_ip_driver_status = NX_DRIVER_ERROR;

            return;
        }

        interface_ptr->nx_interface_physical_address_msw = (ULONG) ((mac[0] << 8) | (mac[1] << 0));
        interface_ptr->nx_interface_physical_address_lsw = (ULONG) ((mac[2] << 24) | (mac[3] << 16) |
                                                                    (mac[4] << 8) |
                                                                    (mac[5] << 0));

        /* Indicate to the IP software that IP to physical mapping
         * is required.  */
        interface_ptr->nx_interface_address_mapping_needed = NX_FALSE;

        /* Move the driver's state to initialized.  */
        nx_driver_information.nx_driver_information_states = NX_DRIVER_STATE_INITIALIZED;

        /* Indicate successful initialize.  */
        driver_req_ptr->nx_ip_driver_status = NX_SUCCESS;
    }
    else
    {
        /* Initialization failed.  Indicate that the request failed.  */
        driver_req_ptr->nx_ip_driver_status = NX_DRIVER_ERROR;
    }
}

/**************************************************************************/
/*                                                                        */
/*  FUNCTION                                               RELEASE        */
/*                                                                        */
/*    _nx_driver_enable                                   PORTABLE C      */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function processing the initialize request. The processing     */
/*    in this function is generic. All ethernet controller logic is to    */
/*    be placed in _nx_driver_hardware_enable.                            */
/*                                                                        */
/*  INPUT                                                                 */
/*                                                                        */
/*    driver_req_ptr                        Driver command from the IP    */
/*                                            thread                      */
/*                                                                        */
/*  OUTPUT                                                                */
/*                                                                        */
/*    None                                                                */
/*                                                                        */
/*  CALLS                                                                 */
/*                                                                        */
/*    _nx_driver_hardware_enable            Process enable request        */
/*                                                                        */
/*  CALLED BY                                                             */
/*                                                                        */
/*    Driver entry function                                               */
/*                                                                        */
/**************************************************************************/
static VOID _nx_driver_enable (NX_IP_DRIVER * driver_req_ptr)
{
    UINT status;

    /* See if we can honor the NX_LINK_ENABLE request.  */
    if (nx_driver_information.nx_driver_information_states < NX_DRIVER_STATE_INITIALIZED)
    {
        /* Mark the request as not successful.  */
        driver_req_ptr->nx_ip_driver_status = NX_DRIVER_ERROR;

        return;
    }

    /* Check if it is enabled by someone already */
    if (nx_driver_information.nx_driver_information_states >= NX_DRIVER_STATE_LINK_ENABLED)
    {
        /* Yes, the request has already been made.  */
        driver_req_ptr->nx_ip_driver_status = NX_ALREADY_ENABLED;

        return;
    }

    /* Call hardware specific enable.  */
    status = _nx_driver_hardware_enable(driver_req_ptr);

    /* Was the hardware enable successful?  */
    if (status == NX_SUCCESS)
    {
        /* Update the driver state to link enabled.  */
        nx_driver_information.nx_driver_information_states = NX_DRIVER_STATE_LINK_ENABLED;

        /* Mark request as successful.  */
        driver_req_ptr->nx_ip_driver_status = NX_SUCCESS;

        /* Mark the IP interface as link up.  */
        driver_req_ptr->nx_ip_driver_interface->nx_interface_link_up = NX_TRUE;

        /* Set TCP/IP callback function.  */
        driver_req_ptr->nx_ip_driver_interface->nx_interface_tcpip_offload_handler = _nx_driver_tcpip_handler;
    }
    else
    {
        /* Enable failed.  Indicate that the request failed.  */
        driver_req_ptr->nx_ip_driver_status = NX_DRIVER_ERROR;
    }
}

/**************************************************************************/
/*                                                                        */
/*  FUNCTION                                               RELEASE        */
/*                                                                        */
/*    _nx_driver_disable                                  PORTABLE C      */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function processing the disable request. The processing        */
/*    in this function is generic. All ethernet controller logic is to    */
/*    be placed in _nx_driver_hardware_disable.                           */
/*                                                                        */
/*  INPUT                                                                 */
/*                                                                        */
/*    driver_req_ptr                        Driver command from the IP    */
/*                                            thread                      */
/*                                                                        */
/*  OUTPUT                                                                */
/*                                                                        */
/*    None                                                                */
/*                                                                        */
/*  CALLS                                                                 */
/*                                                                        */
/*    _nx_driver_hardware_disable           Process disable request       */
/*                                                                        */
/*  CALLED BY                                                             */
/*                                                                        */
/*    Driver entry function                                               */
/*                                                                        */
/**************************************************************************/
static VOID _nx_driver_disable (NX_IP_DRIVER * driver_req_ptr)
{
    UINT status;

    /* Check if the link is enabled.  */
    if (nx_driver_information.nx_driver_information_states != NX_DRIVER_STATE_LINK_ENABLED)
    {
        /* The link is not enabled, so just return an error.  */
        driver_req_ptr->nx_ip_driver_status = NX_DRIVER_ERROR;

        return;
    }

    /* Call hardware specific disable.  */
    status = _nx_driver_hardware_disable(driver_req_ptr);

    /* Was the hardware disable successful?  */
    if (status == NX_SUCCESS)
    {
        /* Mark the IP interface as link down.  */
        driver_req_ptr->nx_ip_driver_interface->nx_interface_link_up = NX_FALSE;

        /* Update the driver state back to initialized.  */
        nx_driver_information.nx_driver_information_states = NX_DRIVER_STATE_INITIALIZED;

        /* Mark request as successful.  */
        driver_req_ptr->nx_ip_driver_status = NX_SUCCESS;

        /* Clear the TCP/IP callback function.  */
        driver_req_ptr->nx_ip_driver_interface->nx_interface_tcpip_offload_handler = NX_NULL;
    }
    else
    {
        /* Disable failed, return an error.  */
        driver_req_ptr->nx_ip_driver_status = NX_DRIVER_ERROR;
    }
}

/**************************************************************************/
/*                                                                        */
/*  FUNCTION                                               RELEASE        */
/*                                                                        */
/*    _nx_driver_multicast_join                           PORTABLE C      */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function processing the multicast join request. The processing */
/*    in this function is generic. All ethernet controller multicast join */
/*    logic is to be placed in _nx_driver_hardware_multicast_join.        */
/*                                                                        */
/*  INPUT                                                                 */
/*                                                                        */
/*    driver_req_ptr                        Driver command from the IP    */
/*                                            thread                      */
/*                                                                        */
/*  OUTPUT                                                                */
/*                                                                        */
/*    None                                                                */
/*                                                                        */
/*  CALLS                                                                 */
/*                                                                        */
/*    None                                                                */
/*                                                                        */
/*  CALLED BY                                                             */
/*                                                                        */
/*    Driver entry function                                               */
/*                                                                        */
/**************************************************************************/
static VOID _nx_driver_multicast_join (NX_IP_DRIVER * driver_req_ptr)
{
    /* Not supported.  */
    driver_req_ptr->nx_ip_driver_status = NX_DRIVER_ERROR;
}

/**************************************************************************/
/*                                                                        */
/*  FUNCTION                                               RELEASE        */
/*                                                                        */
/*    _nx_driver_multicast_leave                          PORTABLE C      */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function processing the multicast leave request. The           */
/*    processing in this function is generic. All ethernet controller     */
/*    multicast leave logic is to be placed in                            */
/*    _nx_driver_hardware_multicast_leave.                                */
/*                                                                        */
/*  INPUT                                                                 */
/*                                                                        */
/*    driver_req_ptr                        Driver command from the IP    */
/*                                            thread                      */
/*                                                                        */
/*  OUTPUT                                                                */
/*                                                                        */
/*    None                                                                */
/*                                                                        */
/*  CALLS                                                                 */
/*                                                                        */
/*    None                                                                */
/*                                                                        */
/*  CALLED BY                                                             */
/*                                                                        */
/*    Driver entry function                                               */
/*                                                                        */
/**************************************************************************/
static VOID _nx_driver_multicast_leave (NX_IP_DRIVER * driver_req_ptr)
{
    /* Not supported.  */
    driver_req_ptr->nx_ip_driver_status = NX_DRIVER_ERROR;
}

/**************************************************************************/
/*                                                                        */
/*  FUNCTION                                               RELEASE        */
/*                                                                        */
/*    _nx_driver_get_status                               PORTABLE C      */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function processing the get status request. The processing     */
/*    in this function is generic. All ethernet controller get status     */
/*    logic is to be placed in _nx_driver_hardware_get_status.            */
/*                                                                        */
/*  INPUT                                                                 */
/*                                                                        */
/*    driver_req_ptr                        Driver command from the IP    */
/*                                            thread                      */
/*                                                                        */
/*  OUTPUT                                                                */
/*                                                                        */
/*    None                                                                */
/*                                                                        */
/*  CALLS                                                                 */
/*                                                                        */
/*    _nx_driver_hardware_get_status        Process get status request    */
/*                                                                        */
/*  CALLED BY                                                             */
/*                                                                        */
/*    Driver entry function                                               */
/*                                                                        */
/**************************************************************************/
static VOID _nx_driver_get_status (NX_IP_DRIVER * driver_req_ptr)
{
    *(driver_req_ptr->nx_ip_driver_return_ptr) = driver_req_ptr->nx_ip_driver_interface->nx_interface_link_up;
    driver_req_ptr->nx_ip_driver_status        = NX_SUCCESS;
}

/**************************************************************************/
/*                                                                        */
/*  FUNCTION                                               RELEASE        */
/*                                                                        */
/*    _nx_driver_thread_entry                             PORTABLE C      */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function is the driver thread entry. In this thread, it        */
/*    performs checking for incoming TCP packets. On new packet,          */
/*    it will be passed to NetX.                                          */
/*                                                                        */
/*  INPUT                                                                 */
/*                                                                        */
/*    thread_input                          Thread input                  */
/*                                                                        */
/*  OUTPUT                                                                */
/*                                                                        */
/*    None                                                                */
/*                                                                        */
/*  CALLS                                                                 */
/*                                                                        */
/*    tx_mutex_get                          Obtain protection mutex       */
/*    tx_mutex_put                          Release protection mutex      */
/*    tx_thread_sleep                       Sleep driver thread           */
/*    nx_packet_allocate                    Allocate a packet for incoming*/
/*                                            TCP                         */
/*    _nx_tcp_socket_driver_packet_receive                                */
/*                                          Receive TCP packet            */
/*                                                                        */
/*  CALLED BY                                                             */
/*                                                                        */
/*    Driver entry function                                               */
/*                                                                        */
/**************************************************************************/
static VOID _nx_driver_thread_entry (ULONG thread_input)
{
    uint32_t    i;
    NX_PACKET * current_packet_ptr;
    NX_PACKET * next_packet_ptr;

    uint32_t         data_length;
    NX_IP          * ip_ptr        = nx_driver_information.nx_driver_information_ip_ptr;
    NX_INTERFACE   * interface_ptr = nx_driver_information.nx_driver_information_interface;
    NX_PACKET_POOL * pool_ptr      = nx_driver_information.nx_driver_information_packet_pool_ptr;

    NX_PARAMETER_NOT_USED(thread_input);

    /* Allocate 2 packets (one for the active transfer and one for the next) */
    nx_packet_allocate(pool_ptr, &current_packet_ptr, NX_TCP_PACKET, NX_WAIT_FOREVER);
    nx_packet_allocate(pool_ptr, &next_packet_ptr, NX_TCP_PACKET, NX_WAIT_FOREVER);

    /* Get available size of packet.  */
    data_length =
        ((uint32_t) current_packet_ptr->nx_packet_data_end - (uint32_t) current_packet_ptr->nx_packet_prepend_ptr);

    /* Set packet pointers and packet size */
    rm_wifi_onchip_silex_initialize_packet_buffers((uint8_t *) (current_packet_ptr->nx_packet_prepend_ptr),
                                                   (uint8_t *) (next_packet_ptr->nx_packet_prepend_ptr),
                                                   data_length);

    ULONG wait_ticks_byte_start      = MS_TO_TICKS(RM_NETXDUO_WIFI_BYTE_START_SEMAPHORE_TIMEOUT_MS);
    ULONG wait_ticks_packet_complete = MS_TO_TICKS(RM_NETXDUO_WIFI_PACKET_COMPLETE_SEMAPHORE_TIMEOUT_MS);

    /* Enforce 2 tick minimum wait for packets */
    if (wait_ticks_byte_start < RM_NETXDUO_WIFI_MIN_TICKS)
    {
        wait_ticks_byte_start = RM_NETXDUO_WIFI_MIN_TICKS;
    }

    if (wait_ticks_packet_complete < RM_NETXDUO_WIFI_MIN_TICKS)
    {
        wait_ticks_packet_complete = RM_NETXDUO_WIFI_MIN_TICKS;
    }

    for ( ; ; )
    {
        ULONG actual_events = 0;

        if (TX_SUCCESS ==
            tx_event_flags_get(&nx_driver_thread_events, RM_NETXDUO_DRIVER_THREAD_EVENT_DEINITIALIZE, TX_AND_CLEAR,
                               &actual_events, TX_NO_WAIT))
        {
            /* Check for driver close */
            if (actual_events & RM_NETXDUO_DRIVER_THREAD_EVENT_DEINITIALIZE)
            {
                /* Attempt to release packets */
                nx_packet_release(current_packet_ptr);
                nx_packet_release(next_packet_ptr);

                /* Terminate thread */
                tx_thread_terminate(&nx_driver_thread);
            }
        }

        /* Obtain the IP internal mutex before processing the IP event.  */
        tx_mutex_get(&(ip_ptr->nx_ip_protection), TX_WAIT_FOREVER);

        /* Find NetX socket that corresponds to currently active socket index */
        for (i = 0; i < RM_NETXDUO_WIFI_SOCKETS_MAXIMUM; i++)
        {
            if (rm_wifi_onchip_silex_get_current_socket_index() == nx_driver_sockets[i].socket_id)
            {
                break;
            }
        }

        uint32_t start_socket_index = i;
        do
        {
            if ((nx_driver_sockets[i].socket_ptr == NX_NULL) ||
                (nx_driver_sockets[i].remote_port == 0))
            {
                /* Skip sockets not used.  */
                i = (i + 1) % RM_NETXDUO_WIFI_SOCKETS_MAXIMUM;

                continue;
            }

            /* Tell driver to switch sockets */
            rm_wifi_onchip_silex_change_socket(nx_driver_sockets[i].socket_id);

            /* Wait on semaphore that notifies of a byte received for a socket */
            if (TX_SUCCESS == rm_wifi_onchip_silex_get_rx_start_semaphore(wait_ticks_byte_start))
            {
                /* We've started receiving data, loop to receive the remaining data on current socket.  */
                for ( ; ; )
                {
                    ULONG received_length = (ULONG) data_length;

                    NXD_ADDRESS local_ip;
                    NXD_ADDRESS remote_ip;
                    local_ip.nxd_ip_version     = NX_IP_VERSION_V4;
                    local_ip.nxd_ip_address.v4  = nx_driver_sockets[i].local_ip;
                    remote_ip.nxd_ip_version    = NX_IP_VERSION_V4;
                    remote_ip.nxd_ip_address.v4 = nx_driver_sockets[i].remote_ip;

                    /* Wait for semaphore that notifies of packet being filled */
                    if (TX_SUCCESS == rm_wifi_onchip_silex_get_rx_complete_semaphore(wait_ticks_packet_complete))
                    {
                        /* Packet has been filled */
                        /* Set packet length.  */
                        current_packet_ptr->nx_packet_length     = received_length;
                        current_packet_ptr->nx_packet_append_ptr = current_packet_ptr->nx_packet_prepend_ptr +
                                                                   received_length;
                        current_packet_ptr->nx_packet_ip_interface = interface_ptr;

                        /* Save off packet to send to NetX */
                        NX_PACKET * packet_to_send = current_packet_ptr;

                        /* Allocate a new packet */
                        current_packet_ptr = next_packet_ptr;
                        if (NX_SUCCESS != nx_packet_allocate(pool_ptr, &next_packet_ptr, NX_TCP_PACKET, NX_NO_WAIT))
                        {
                            if (nx_driver_sockets[i].protocol == NX_PROTOCOL_TCP)
                            {
                                _nx_tcp_socket_driver_packet_receive(nx_driver_sockets[i].socket_ptr, NX_NULL);
                            }
                            else
                            {
                                _nx_udp_socket_driver_packet_receive(nx_driver_sockets[i].socket_ptr,
                                                                     NX_NULL,
                                                                     &local_ip,
                                                                     &remote_ip,
                                                                     nx_driver_sockets[i].remote_port);
                            }
                        }

                        /* Set next packet pointer */
                        rm_wifi_onchip_silex_set_next_packet_buffer((uint8_t *) next_packet_ptr->nx_packet_prepend_ptr);

                        /* Pass packet to NetXDuo.  */
                        if (nx_driver_sockets[i].protocol == NX_PROTOCOL_TCP)
                        {
                            _nx_tcp_socket_driver_packet_receive(nx_driver_sockets[i].socket_ptr, packet_to_send);
                        }
                        else
                        {
                            _nx_udp_socket_driver_packet_receive(nx_driver_sockets[i].socket_ptr,
                                                                 packet_to_send,
                                                                 &local_ip,
                                                                 &remote_ip,
                                                                 nx_driver_sockets[i].remote_port);
                        }
                    }
                    else
                    {
                        /* Semaphore timed out, received less data than packet size */
                        FSP_CRITICAL_SECTION_DEFINE;
                        FSP_CRITICAL_SECTION_ENTER;

                        /* Get semaphore again in case operation completed between semaphore timeout and critical section entry */
                        UINT semaphore_err = rm_wifi_onchip_silex_get_rx_complete_semaphore(TX_NO_WAIT);

                        if (TX_NO_INSTANCE == semaphore_err)
                        {
                            /* No more data at the moment */
                            rm_wifi_onchip_silex_stop_tcp_recv((uint32_t *) &received_length);

                            /* Advance to next packet buffer inside the critical section in case we get more data before buffers can be switched */
                            rm_wifi_onchip_silex_move_to_next_packet_buffer();
                        }

                        FSP_CRITICAL_SECTION_EXIT;

                        /* Set packet length. */
                        current_packet_ptr->nx_packet_length     = received_length;
                        current_packet_ptr->nx_packet_append_ptr = current_packet_ptr->nx_packet_prepend_ptr +
                                                                   received_length;
                        current_packet_ptr->nx_packet_ip_interface = interface_ptr;

                        /* Save off packet to send to NetX */
                        NX_PACKET * packet_to_send = current_packet_ptr;

                        /* Allocate a new packet */
                        current_packet_ptr = next_packet_ptr;
                        if (NX_SUCCESS != nx_packet_allocate(pool_ptr, &next_packet_ptr, NX_TCP_PACKET, NX_NO_WAIT))
                        {
                            if (nx_driver_sockets[i].protocol == NX_PROTOCOL_TCP)
                            {
                                _nx_tcp_socket_driver_packet_receive(nx_driver_sockets[i].socket_ptr, NX_NULL);
                            }
                            else
                            {
                                _nx_udp_socket_driver_packet_receive(nx_driver_sockets[i].socket_ptr,
                                                                     NX_NULL,
                                                                     &local_ip,
                                                                     &remote_ip,
                                                                     nx_driver_sockets[i].remote_port);
                            }
                        }

                        /* Set next packet pointer */
                        rm_wifi_onchip_silex_set_next_packet_buffer((uint8_t *) next_packet_ptr->nx_packet_prepend_ptr);

                        /* Pass packet to NetXDuo.  */
                        if (nx_driver_sockets[i].protocol == NX_PROTOCOL_TCP)
                        {
                            _nx_tcp_socket_driver_packet_receive(nx_driver_sockets[i].socket_ptr, packet_to_send);
                        }
                        else
                        {
                            _nx_udp_socket_driver_packet_receive(nx_driver_sockets[i].socket_ptr,
                                                                 packet_to_send,
                                                                 &local_ip,
                                                                 &remote_ip,
                                                                 nx_driver_sockets[i].remote_port);
                        }

                        if (TX_NO_INSTANCE == semaphore_err)
                        {
                            break;
                        }
                    }
                }
            }

            i = (i + 1) % RM_NETXDUO_WIFI_SOCKETS_MAXIMUM;
        } while (i != start_socket_index);

        /* Release the IP internal mutex before processing the IP event.  */
        tx_mutex_put(&(ip_ptr->nx_ip_protection));

        /* Sleep at least one tick so that other threads can grab IP mutex */
        tx_thread_sleep(1);
    }
}

/**************************************************************************/
/*                                                                        */
/*  FUNCTION                                               RELEASE        */
/*                                                                        */
/*    _nx_driver_tcpip_handler                            PORTABLE C      */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function processing the TCP/IP request.                        */
/*                                                                        */
/*  INPUT                                                                 */
/*                                                                        */
/*    ip_ptr                                Pointer to IP                 */
/*    interface_ptr                         Pointer to interface          */
/*    socket_ptr                            Pointer to TCP socket         */
/*    operation                             Operation of TCP/IP request   */
/*    packet_ptr                            Pointer to packet             */
/*    local_ip                              Pointer to local IP address   */
/*    remote_ip                             Pointer to remote IP address  */
/*    local_port                            Local socket port             */
/*    remote_port                           Remote socket port            */
/*    wait_option                           Wait option in ticks          */
/*                                                                        */
/*  OUTPUT                                                                */
/*                                                                        */
/*    None                                                                */
/*                                                                        */
/*  CALLS                                                                 */
/*                                                                        */
/*    nx_packet_transmit_release            Release transmittion packet   */
/*                                                                        */
/*  CALLED BY                                                             */
/*                                                                        */
/*    Driver entry function                                               */
/*                                                                        */
/**************************************************************************/
static UINT _nx_driver_tcpip_handler (struct NX_IP_STRUCT        * ip_ptr,
                                      struct NX_INTERFACE_STRUCT * interface_ptr,
                                      VOID                       * socket_ptr,
                                      UINT                         operation,
                                      NX_PACKET                  * packet_ptr,
                                      NXD_ADDRESS                * local_ip,
                                      NXD_ADDRESS                * remote_ip,
                                      UINT                         local_port,
                                      UINT                       * remote_port,
                                      UINT                         wait_option)
{
    FSP_PARAMETER_NOT_USED(ip_ptr);
    FSP_PARAMETER_NOT_USED(interface_ptr);
    FSP_PARAMETER_NOT_USED(local_ip);

    UINT status = NX_NOT_SUCCESSFUL;

    NX_PACKET * current_packet;
    int32_t     packet_size;

    int32_t sent_size = 0;
    UINT    i         = 0;

    if ((operation == NX_TCPIP_OFFLOAD_TCP_CLIENT_SOCKET_CONNECT) || (operation == NX_TCPIP_OFFLOAD_UDP_SOCKET_BIND))
    {
        /* Find a socket that is not used.  */
        while (i < RM_NETXDUO_WIFI_SOCKETS_MAXIMUM)
        {
            if (nx_driver_sockets[i].socket_ptr == NX_NULL)
            {
                /* Find an empty entry.  */
                nx_driver_sockets[i].socket_ptr = socket_ptr;
                break;
            }

            i++;
        }

        if (i == RM_NETXDUO_WIFI_SOCKETS_MAXIMUM)
        {

            /* No more entries.  */
            return NX_NO_MORE_ENTRIES;
        }
    }

    switch (operation)
    {
        case NX_TCPIP_OFFLOAD_TCP_CLIENT_SOCKET_CONNECT:
        {
            /* Store the index of driver socket.  */
            ((NX_TCP_SOCKET *) socket_ptr)->nx_tcp_socket_tcpip_offload_context = (VOID *) i;

            if (rm_wifi_onchip_silex_socket_create(i, RM_NETXDUO_WIFI_SOCKET_TYPE_TCP, RM_NETXDUO_WIFI_SOCKET_IPV4))
            {
                return NX_NOT_SUCCESSFUL;
            }

            /* Set the socket id.  */
            nx_driver_sockets[i].socket_id = i;

            if (rm_wifi_onchip_silex_tcp_connect(nx_driver_sockets[i].socket_id, remote_ip->nxd_ip_address.v4,
                                                 *remote_port))
            {
                return NX_NOT_SUCCESSFUL;
            }

            /* Store address and port.  */
            nx_driver_sockets[i].remote_ip   = remote_ip->nxd_ip_address.v4;
            nx_driver_sockets[i].local_port  = (uint16_t) local_port;
            nx_driver_sockets[i].remote_port = (uint16_t) *remote_port;
            nx_driver_sockets[i].protocol    = NX_PROTOCOL_TCP;

            status = NX_SUCCESS;

            break;
        }

        case NX_TCPIP_OFFLOAD_TCP_SOCKET_DISCONNECT:
        {
            /* Disconnect socket */
            i = (UINT) (((NX_TCP_SOCKET *) socket_ptr)->nx_tcp_socket_tcpip_offload_context);
            if (nx_driver_sockets[i].remote_port)
            {
                status = rm_wifi_onchip_silex_socket_disconnect(nx_driver_sockets[i].socket_id);
            }

            /* Reset socket to free this entry.  */
            nx_driver_sockets[i].socket_ptr  = NX_NULL;
            nx_driver_sockets[i].remote_port = 0;
            break;
        }

        case NX_TCPIP_OFFLOAD_UDP_SOCKET_UNBIND:
        {
            /* Disconnect socket */
            i = (UINT) (((NX_UDP_SOCKET *) socket_ptr)->nx_udp_socket_tcpip_offload_context);
            if (nx_driver_sockets[i].remote_port)
            {
                status = rm_wifi_onchip_silex_socket_disconnect(nx_driver_sockets[i].socket_id);
            }

            /* Reset socket to free this entry.  */
            nx_driver_sockets[i].socket_ptr  = NX_NULL;
            nx_driver_sockets[i].remote_port = 0;
            break;
        }

        case NX_TCPIP_OFFLOAD_UDP_SOCKET_BIND:
        {
            /* Store the index of driver socket.  */
            ((NX_UDP_SOCKET *) socket_ptr)->nx_udp_socket_tcpip_offload_context = (VOID *) i;

            /* Create UDP socket */
            if (rm_wifi_onchip_silex_socket_create(i, RM_NETXDUO_WIFI_SOCKET_TYPE_UDP, RM_NETXDUO_WIFI_SOCKET_IPV4)) // Create a UDP socket
            {
                return NX_NOT_SUCCESSFUL;
            }

            /* Set the socket id.  */
            nx_driver_sockets[i].socket_id = i;

            status = NX_SUCCESS;

            break;
        }

        case NX_TCPIP_OFFLOAD_UDP_SOCKET_SEND:
        {
            i = (UINT) (((NX_UDP_SOCKET *) socket_ptr)->nx_udp_socket_tcpip_offload_context);

            /* Initialize the current packet to the input packet pointer.  */
            current_packet = packet_ptr;

            /* Setup UDP connection with server if not already done*/
            if (nx_driver_sockets[i].remote_port == 0)
            {
                /* Setup UDP client to remote ip and port */
                if (rm_wifi_onchip_silex_udp_connect(nx_driver_sockets[i].socket_id, remote_ip->nxd_ip_address.v4,
                                                     *remote_port, 0)) // Connect UDP port client
                {
                    return NX_NOT_SUCCESSFUL;
                }

                /* Store address and port.  */
                nx_driver_sockets[i].remote_ip   = remote_ip->nxd_ip_address.v4;
                nx_driver_sockets[i].local_port  = (uint16_t) local_port;
                nx_driver_sockets[i].remote_port = (uint16_t) *remote_port;
                nx_driver_sockets[i].protocol    = NX_PROTOCOL_UDP;
            }

            /* Loop to send the packet.  */
            while (current_packet)
            {
                sent_size = rm_wifi_onchip_silex_send(nx_driver_sockets[i].socket_id,
                                                      (const uint8_t *) current_packet->nx_packet_prepend_ptr,
                                                      (uint32_t) current_packet->nx_packet_length,
                                                      RM_NETXDUO_WIFI_SOCKET_UDP_SEND_TIMEOUT_MAXIMUM);

                /* Check status.  */
                if (sent_size != (int32_t) current_packet->nx_packet_length)
                {
                    return NX_NOT_SUCCESSFUL;
                }

#ifndef NX_DISABLE_PACKET_CHAIN

                /* We have crossed the packet boundary.  Move to the next packet structure.  */
                current_packet = current_packet->nx_packet_next;
#else

                /* End of the loop.  */
                current_packet = NX_NULL;
#endif                                 /* NX_DISABLE_PACKET_CHAIN */
            }

            /* Release the packet.  */
            nx_packet_transmit_release(packet_ptr);

            status = NX_SUCCESS;

            break;
        }

        case NX_TCPIP_OFFLOAD_TCP_SOCKET_SEND:
        {
            i = (UINT) (((NX_TCP_SOCKET *) socket_ptr)->nx_tcp_socket_tcpip_offload_context);

            /* Initialize the current packet to the input packet pointer.  */
            current_packet = packet_ptr;

            /* Convert wait option from ticks to ms.  */
            if (wait_option >
                ((RM_NETXDUO_WIFI_SOCKET_SEND_TIMEOUT_MAXIMUM / RM_NETXDUO_WIFI_TIME_TICKS_WAIT_DIV) *
                 NX_IP_PERIODIC_RATE))
            {
                wait_option = RM_NETXDUO_WIFI_SOCKET_SEND_TIMEOUT_MAXIMUM;
            }
            else
            {
                wait_option = (wait_option / NX_IP_PERIODIC_RATE) * RM_NETXDUO_WIFI_TIME_TICKS_WAIT_DIV;
            }

            /* Loop to send the packet.  */
            while (current_packet)
            {
                /* Calculate current packet size. */
                packet_size = (int32_t) current_packet->nx_packet_append_ptr -
                              (int32_t) current_packet->nx_packet_prepend_ptr;

                sent_size = rm_wifi_onchip_silex_send(nx_driver_sockets[i].socket_id,
                                                      (const uint8_t *) current_packet->nx_packet_prepend_ptr,
                                                      (uint32_t) packet_size,
                                                      wait_option);

                /* Check status.  */
                if (sent_size != packet_size)
                {
                    return NX_NOT_SUCCESSFUL;
                }

#ifndef NX_DISABLE_PACKET_CHAIN

                /* We have crossed the packet boundary.  Move to the next packet structure.  */
                current_packet = current_packet->nx_packet_next;
#else

                /* End of the loop.  */
                current_packet = NX_NULL;
#endif                                 /* NX_DISABLE_PACKET_CHAIN */
            }

            /* Release the packet.  */
            nx_packet_transmit_release(packet_ptr);

            status = NX_SUCCESS;

            break;
        }

        default:
        {
            break;
        }
    }

    return status;
}

/****** DRIVER SPECIFIC ****** Start of part/vendor specific internal driver functions.  */

/**************************************************************************/
/*                                                                        */
/*  FUNCTION                                               RELEASE        */
/*                                                                        */
/*    _nx_driver_hardware_initialize                      PORTABLE C      */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function processes hardware-specific initialization.           */
/*                                                                        */
/*  INPUT                                                                 */
/*                                                                        */
/*    driver_req_ptr                        Driver request pointer        */
/*                                                                        */
/*  OUTPUT                                                                */
/*                                                                        */
/*    status                                [NX_SUCCESS|NX_DRIVER_ERROR]  */
/*                                                                        */
/*  CALLS                                                                 */
/*                                                                        */
/*    tx_thread_info_get                    Get thread information        */
/*    tx_thread_create                      Create driver thread          */
/*                                                                        */
/*  CALLED BY                                                             */
/*                                                                        */
/*    _nx_driver_initialize                 Driver initialize processing  */
/*                                                                        */
/**************************************************************************/
static UINT _nx_driver_hardware_initialize (NX_IP_DRIVER * driver_req_ptr)
{
    FSP_PARAMETER_NOT_USED(driver_req_ptr);

    UINT status;
    UINT priority = 0;

    status = tx_event_flags_create(&nx_driver_thread_events, "nx_driver_thread_events");

    if (TX_SUCCESS == status)
    {
        /* Get priority of IP thread.  */
        tx_thread_info_get(tx_thread_identify(),
                           NX_NULL,
                           NX_NULL,
                           NX_NULL,
                           &priority,
                           NX_NULL,
                           NX_NULL,
                           NX_NULL,
                           NX_NULL);

        /* Create the driver thread.  */
        /* The priority of network thread is lower than IP thread.  */
        status = tx_thread_create(&nx_driver_thread,
                                  "Driver Thread",
                                  _nx_driver_thread_entry,
                                  0,
                                  nx_driver_thread_stack,
                                  RM_NETXDUO_WIFI_DRIVER_THREAD_STACK_SIZE,
                                  priority + 1,
                                  priority + 1,
                                  TX_NO_TIME_SLICE,
                                  TX_DONT_START);
    }

    /* Return success!  */
    return status;
}

/**************************************************************************/
/*                                                                        */
/*  FUNCTION                                               RELEASE        */
/*                                                                        */
/*    _nx_driver_hardware_enable                          PORTABLE C      */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function processes hardware-specific link enable requests.     */
/*                                                                        */
/*  INPUT                                                                 */
/*                                                                        */
/*    driver_req_ptr                        Driver request pointer        */
/*                                                                        */
/*  OUTPUT                                                                */
/*                                                                        */
/*    status                                [NX_SUCCESS|NX_DRIVER_ERROR]  */
/*                                                                        */
/*  CALLS                                                                 */
/*                                                                        */
/*    tx_thread_reset                       Reset driver thread           */
/*    tx_thread_resume                      Resume driver thread          */
/*                                                                        */
/*  CALLED BY                                                             */
/*                                                                        */
/*    _nx_driver_enable                     Driver link enable processing */
/*                                                                        */
/**************************************************************************/
static UINT _nx_driver_hardware_enable (NX_IP_DRIVER * driver_req_ptr)
{
    FSP_PARAMETER_NOT_USED(driver_req_ptr);

    tx_thread_reset(&nx_driver_thread);
    tx_thread_resume(&nx_driver_thread);

    /* Return success!  */
    return NX_SUCCESS;
}

/**************************************************************************/
/*                                                                        */
/*  FUNCTION                                               RELEASE        */
/*                                                                        */
/*    _nx_driver_hardware_disable                         PORTABLE C      */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function processes hardware-specific link disable requests.    */
/*                                                                        */
/*  INPUT                                                                 */
/*                                                                        */
/*    driver_req_ptr                        Driver request pointer        */
/*                                                                        */
/*  OUTPUT                                                                */
/*                                                                        */
/*    status                                [NX_SUCCESS|NX_DRIVER_ERROR]  */
/*                                                                        */
/*  CALLS                                                                 */
/*                                                                        */
/*    tx_thread_suspend                     Suspend driver thread         */
/*    tx_thread_terminate                   Terminate driver thread       */
/*                                                                        */
/*  CALLED BY                                                             */
/*                                                                        */
/*    _nx_driver_disable                    Driver link disable processing*/
/*                                                                        */
/**************************************************************************/
static UINT _nx_driver_hardware_disable (NX_IP_DRIVER * driver_req_ptr)
{
    FSP_PARAMETER_NOT_USED(driver_req_ptr);

    UINT i;

    /* Reset all sockets.  */
    for (i = 0; i < RM_NETXDUO_WIFI_SOCKETS_MAXIMUM; i++)
    {
        if (nx_driver_sockets[i].socket_ptr)
        {
            rm_wifi_onchip_silex_socket_disconnect(nx_driver_sockets[i].socket_id);
            nx_driver_sockets[i].socket_ptr = NX_NULL;
        }
    }

    tx_thread_suspend(&nx_driver_thread);
    tx_thread_terminate(&nx_driver_thread);

    /* Return success!  */
    return NX_SUCCESS;
}

/****** DRIVER SPECIFIC ****** Start of part/vendor specific internal driver functions.  */
