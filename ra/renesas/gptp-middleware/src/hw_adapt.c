/***********************************************************************************************************************
 * Copyright [2023] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software and documentation are supplied by Renesas Electronics Corporation and/or its affiliates and may only
 * be used with products of Renesas Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.
 * Renesas products are sold pursuant to Renesas terms and conditions of sale.  Purchasers are solely responsible for
 * the selection and use of Renesas products and Renesas assumes no liability.  No license, express or implied, to any
 * intellectual property right is granted by Renesas.  This software is protected under all applicable laws, including
 * copyright laws. Renesas reserves the right to change or discontinue this software and/or this documentation.
 * THE SOFTWARE AND DOCUMENTATION IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND
 * TO THE FULLEST EXTENT PERMISSIBLE UNDER APPLICABLE LAW, DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY,
 * INCLUDING WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE
 * SOFTWARE OR DOCUMENTATION.  RENESAS SHALL HAVE NO LIABILITY ARISING OUT OF ANY SECURITY VULNERABILITY OR BREACH.
 * TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE OR
 * DOCUMENTATION (OR ANY PERSON OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER,
 * INCLUDING, WITHOUT LIMITATION, ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES; ANY
 * LOST PROFITS, OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF THE
 * POSSIBILITY OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS.
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * File Name    : hw_adapt.c
 * Version      : 0.01
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version  Description
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 *********************************************************************************************************************/
#include <stdlib.h>
#include <string.h>
#include "gptp_api.h"
#include "hw_adapt.h"
#include "sync_8021_as.h"
#include "utils.h"
#include "bmca.h"
#include "data_sets.h"
#include "delay_measurement.h"
#include "ptp_clock_timer.h"

// 2024.05.17 refs #5490
#include <stdio.h>


/**********************************************************************************************************************
 Macro definitions
 *********************************************************************************************************************/
#define UNDERFLOW_DETECTION ((uint32_t)999999999)
/* tx cotorl 1 */
#define ETHPORT_CTRLBIT_FORCE_FORWARD   (0x0001U) /* [0] */
#define ETHPORT_CTRLBIT_FILTERING       (0x0002U) /* [1] */
#define ETHPORT_CTRLBIT_PRIORITY        (0x0004U) /* [2] */
#define ETHPORT_CTRLBIT_TIMESTAMPING    (0x0008U) /* [3] */
#define ETHPORT_CTRLBIT_ONE_STEP        (0x0010U) /* [4] */
#define ETHPORT_CTRLBIT_OVERRIDE_QUEUE  (0x0200U) /* [9] */
#define ETHPORT_CTRL_QUEUE(num)         (((uint16_t)num<<10U) & 0x1C00U)    /* [12:10] */

/* tx cotorl 2 */
#define ETHPORT_CTRL_PORTMASK(port)     (((uint32_t)1U<<port) & 0x00000007U) /* [2:0] */
#define ETHPORT_CTRL_TIMESTAMP_ID(id)   (((uint32_t)id<<9U)  & 0x0000FE00U)  /* [15:9] */

#define ONE_SECOND                           ((uint32_t)1000000000)
#define ONE_SECOND_UINT64                    ((uint64_t)1000000000)
#define CLK_CLOCK_200MHZ                     (0x28000000)

#define GPTP_RATE_THREDHOLD                  (15000)
#define GPTP_TIME_VALUE_GET_PROCESSING_TIME  (645)
#define GPTP_MAXIMUM_ETHERNET_FRAME_SIZE     (1514)

#if (4 == ETHSW_CLOCK_PERIOD)
#define ETHSW_CLOCK_RATE_CORRECTION          (5)
#endif

extern st_master_selection_information_t   g_master_selection[NUMBER_OF_INSTANCES];
extern st_ptp_clock_timer_t g_ptp_clock_timer[NUMBER_OF_CLOCKS];
extern uint8_t                  link_state_check[NUMBER_OF_ETHERNET_PORTS];
extern uint8_t                  link_speed[NUMBER_OF_ETHERNET_PORTS];

/**********************************************************************************************************************
 Local Typedef definitions
 *********************************************************************************************************************/
/* Structure for the parameters of tx timstamp callback */
typedef struct st_event_data_txts
{
    uint8_t     msg_type;
    uint8_t     domain;
    uint16_t    seq_id;
    uint16_t    tx_tsp_id;
}st_event_data_txts_t;

/* Event data structure used during tx timestamp process */
typedef struct st_gptpnet_event_data_t
{

    uint8_t port_index;
    union
    {
        st_event_data_txts_t         txts;
    };
}st_gptpnet_event_data_t;

/* Structure of the ethernet port header with additional control information */
typedef struct st_ethernet_port_header_t
{
    uint8_t     dst_address[6];
    uint8_t     src_address[6];
    uint16_t    tag;
    uint16_t    control_1;
    uint32_t    control_2;
    uint16_t    type;
}__attribute__((packed)) st_ethernet_port_header_t;

/* Structure of a generell ethernet protocol data unit */
typedef struct st_ethernet_port_pdu_t
{
    st_ethernet_port_header_t   hdr;
    uint8_t                     payload[512];
}__attribute__((packed))st_ethernet_port_pdu_t;

/** gPTP Tx status */
typedef enum
{
    GPTP_TX_STATUE_IDLE    = 0,
    GPTP_TX_STATUE_WAIT_TS = 1,
    GPTP_TX_STATUE_END     = 2,
    GPTP_TX_STATUE_ERROR   = 3,
} gptp_tx_status_t;

typedef enum e_gptp_send_result
{
    GPTP_SEND_RESULT_SUCCESS                           = 0U,
    GPTP_SEND_RESULT_FAILURE                           = 1U,
    GPTP_SEND_RESULT_TRANSMIT_TIMESTAMP_GET_FAILURE    = 2U,
} gptp_send_result_t;

int gptp_clock_pulser( gptp_pulse_period_t period );
static void gptp_link_status(uint8_t port_num, ether_event_t link_status);
static void gptp_link_process_cb(ether_callback_args_t * p_args);
static void gptp_recv_func(uint8_t *recv_buff,
                           uint16_t recv_size,
                           uint16_t recv_port,
                           rmac_timestamp_t * p_timestamp);
static gptp_send_result_t gptp_write(uint8_t *p_send_buff,
                                     uint16_t frame_length,
                                     uint8_t port_number,
                                     rmac_timestamp_t * p_timestamp);

/**********************************************************************************************************************
 Exported global variables
 *********************************************************************************************************************/
extern st_domain_information_t  g_domains[NUMBER_OF_DOMAINS];

extern uint8_t link_state_check[NUMBER_OF_ETHERNET_PORTS];
extern uint8_t link_state_last[NUMBER_OF_ETHERNET_PORTS];
extern uint8_t g_sync_state[NUMBER_OF_INSTANCES];

/**********************************************************************************************************************
 Private (static) variables and functions
 *********************************************************************************************************************/
//static st_clock_identity_t  s_device_clock_identity                                 = {0};
static st_timestamp_t                   s_working_clock_tx_timestamp[NUMBER_OF_ETHERNET_PORTS]  = {0};
static st_timestamp_t                   s_master_tx_timestamp[NUMBER_OF_ETHERNET_PORTS]         = {0};
static int32_t                          s_new_timestamp[NUMBER_OF_ETHERNET_PORTS]               = {0};
static uint16_t                         s_tx_timestamp_id[NUMBER_OF_ETHERNET_PORTS]             = {0};
static ether_instance_t const * s_ether_instances[NUMBER_OF_ETHERNET_PORTS] = {0};
static gptp_instance_t const * s_gptp_instance = NULL;

uint8_t g_mac_address[6] = {0};

static void set_pps_signal (uint8_t timer, uint32_t seconds_to_set, uint32_t nanoseconds_to_set);
void adjust_offset(uint8_t clock_id, int64_t offset64);

/**********************************************************************************************************************
 * Function Name: initialize_ptp_hardware_functionality
 * Description  : initialize the ptp functions from the hardware
 * Arguments    : None
 * Return Value : None
 *********************************************************************************************************************/
void initialize_ptp_hardware_functionality(void)
{
    uint8_t                 clock_cnt               = 0;
    fsp_err_t               err;

    for (clock_cnt = 0; clock_cnt < NUMBER_OF_HW_CLOCKS; clock_cnt++)
    {
        /* R_ETHSW_TsActive */
        gptp_timer_cfg_t timer_cfg =
        {
         .clock_period = ETHSW_CLOCK_PERIOD,
        };

        err = s_gptp_instance->p_api->timerCfg(s_gptp_instance->p_ctrl, clock_cnt, &timer_cfg);
        if(FSP_SUCCESS == err)
        {
            err = s_gptp_instance->p_api->start(s_gptp_instance->p_ctrl, clock_cnt);
        }
        else
        {
            err = s_gptp_instance->p_api->stop(s_gptp_instance->p_ctrl, clock_cnt);
        }

    }

    gptp_clock_pulser( GPTP_OUTPUT_PULSE_PERIOD );

    return;
}
/**********************************************************************************************************************
 * End of function initialize_ptp_hardware_functionality
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: send_frame
 * Description  : send a ptp frame
 * Arguments    : port_number       - The number of the egress ethernet port
 *                frame_length      - The length of the egress ptp frame
 *                frame_buffer      - Pointer to the frame buffer of the egress ptp frame
 *                tx_timestamp      - Return parameter for the tx timestamp if a timestamp is generated
 *                master_timestamp  - True if the transmission time of the local clock is needed
 * Return Value : usr_err_t
 *********************************************************************************************************************/
void send_frame(uint16_t port_number, uint16_t frame_length, uint8_t *p_frame_buffer, st_timestamp_t * p_tx_timestamp,
                bool master_timestamp)
{
    static st_timestamp_t  s_transmit_timestamp;
    gptp_timer_value_t     current_time     = {0};
    gptp_timer_value_t     working_time     = {0};

    /*Cast to ensure correct behavoir when moving pointer in memory*/
    uint8_t         message_type        = (p_frame_buffer[MESSAGE_ID_OFFSET])&(MESSAGE_ID_MASK);

    uint32_t temp_nanoseconds   = 0;
    uint32_t egress_latency     = TX_PHY_DELAY;

    int32_t  capture_diff       = 0;
    rmac_timestamp_t trans_timestamp = {0};
    uint32_t result = GPTP_SEND_RESULT_FAILURE;

    memset(&s_transmit_timestamp, 0, sizeof(st_timestamp_t));
    s_new_timestamp[port_number] = GPTP_TX_STATUE_WAIT_TS;

    /*frame is an event frame and needs a timestamp*/
    if (((message_type == MESSAGE_ID_SYNC)||(message_type == MESSAGE_ID_PDELAY_REQUEST)||(message_type == MESSAGE_ID_PDELAY_RESPONSE)) && \
        (NULL != p_tx_timestamp))
    {
        result = gptp_write(p_frame_buffer, frame_length, (uint8_t)(port_number), &trans_timestamp);
    }
    else
    {
        result = gptp_write(p_frame_buffer, frame_length, (uint8_t)(port_number), NULL);
    }

    if(GPTP_SEND_RESULT_SUCCESS == result)
    {
        s_working_clock_tx_timestamp[port_number].seconds_msb = 0;
        s_working_clock_tx_timestamp[port_number].seconds_lsb = trans_timestamp.sec_lower;
        s_working_clock_tx_timestamp[port_number].nanoseconds = trans_timestamp.ns;
        s_new_timestamp[port_number] = GPTP_TX_STATUE_END;
    }
    else
    {
        s_new_timestamp[port_number] = GPTP_TX_STATUE_END;
        USR_LOG_ERROR("error 2\n");
        goto send_end;
    }

    if (((message_type == MESSAGE_ID_SYNC)||(message_type == MESSAGE_ID_PDELAY_REQUEST)||(message_type == MESSAGE_ID_PDELAY_RESPONSE)) && \
        (NULL != p_tx_timestamp))
    {
        if (GPTP_TX_STATUE_END == s_new_timestamp[port_number])
        {
            if (master_timestamp)
            {
                __disable_irq();
                s_gptp_instance->p_api->timerValueGet(s_gptp_instance->p_ctrl, LOCAL_CLOCK_TIMER, &current_time);
                s_gptp_instance->p_api->timerValueGet(s_gptp_instance->p_ctrl, SYNCRHONIZED_CLOCK_TIMER, &working_time);
                __enable_irq();

                // timestamp correction for second gptp driver function processing time
                if(GPTP_TIME_VALUE_GET_PROCESSING_TIME > s_working_clock_tx_timestamp[port_number].nanoseconds)
                {
                    s_working_clock_tx_timestamp[port_number].seconds_lsb = s_working_clock_tx_timestamp[port_number].seconds_lsb - 1;
                    s_working_clock_tx_timestamp[port_number].nanoseconds = s_working_clock_tx_timestamp[port_number].nanoseconds + ONE_SECOND;
                }
                s_working_clock_tx_timestamp[port_number].nanoseconds = s_working_clock_tx_timestamp[port_number].nanoseconds - \
                        GPTP_TIME_VALUE_GET_PROCESSING_TIME;

                if (current_time.time_nsec > s_working_clock_tx_timestamp[port_number].nanoseconds)
                {
                    capture_diff = current_time.time_nsec - s_working_clock_tx_timestamp[port_number].nanoseconds;
                }
                else
                {
                    capture_diff = (ONE_SECOND + current_time.time_nsec) - s_working_clock_tx_timestamp[port_number].\
                            nanoseconds;
                }

                s_master_tx_timestamp[port_number].seconds_msb = 0;

                if ((int32_t)working_time.time_nsec < (int32_t)capture_diff)
                {
                    s_master_tx_timestamp[port_number].seconds_lsb = working_time.time_sec_lower - 1;
                    s_master_tx_timestamp[port_number].nanoseconds = ONE_SECOND + \
                            working_time.time_nsec - (uint32_t)capture_diff;
                }
                else
                {
                    s_master_tx_timestamp[port_number].seconds_lsb = working_time.time_sec_lower;
                    s_master_tx_timestamp[port_number].nanoseconds = working_time.time_nsec - (uint32_t)capture_diff;
                }

                s_transmit_timestamp.seconds_msb = s_master_tx_timestamp[port_number].seconds_msb;
                s_transmit_timestamp.seconds_lsb = s_master_tx_timestamp[port_number].seconds_lsb;

                s_transmit_timestamp.nanoseconds = s_master_tx_timestamp[port_number].nanoseconds + egress_latency;

                if (ONE_SECOND <= s_transmit_timestamp.nanoseconds)
                {
                    temp_nanoseconds = s_transmit_timestamp.nanoseconds - ONE_SECOND;
                    s_transmit_timestamp.seconds_lsb = s_transmit_timestamp.seconds_lsb + 1;
                    s_transmit_timestamp.nanoseconds = temp_nanoseconds;
                }
            }
            else
            {
                if(message_type == MESSAGE_ID_SYNC)
                {
                    // timestamp correction for second gptp driver function processing time
                    if(GPTP_TIME_VALUE_GET_PROCESSING_TIME > s_working_clock_tx_timestamp[port_number].nanoseconds)
                    {
                        s_working_clock_tx_timestamp[port_number].seconds_lsb = s_working_clock_tx_timestamp[port_number].seconds_lsb - 1;
                        s_working_clock_tx_timestamp[port_number].nanoseconds = s_working_clock_tx_timestamp[port_number].nanoseconds + ONE_SECOND;
                    }
                    s_working_clock_tx_timestamp[port_number].nanoseconds = s_working_clock_tx_timestamp[port_number].nanoseconds - \
                            GPTP_TIME_VALUE_GET_PROCESSING_TIME;
                }

                s_transmit_timestamp.seconds_msb = s_working_clock_tx_timestamp[port_number].seconds_msb;
                s_transmit_timestamp.seconds_lsb = s_working_clock_tx_timestamp[port_number].seconds_lsb;
                s_transmit_timestamp.nanoseconds = s_working_clock_tx_timestamp[port_number].nanoseconds + \
                        egress_latency;

                if (ONE_SECOND <= s_transmit_timestamp.nanoseconds)
                {
                    temp_nanoseconds = s_transmit_timestamp.nanoseconds - ONE_SECOND;
                    s_transmit_timestamp.seconds_lsb = s_transmit_timestamp.seconds_lsb + 1;
                    s_transmit_timestamp.nanoseconds = temp_nanoseconds;
                }
            }
            memcpy(p_tx_timestamp,&s_transmit_timestamp,sizeof(st_timestamp_t));
        }
        else
        {
            static uint32_t s_tx_id_error;
            static uint32_t s_tx_time_out;

            if (GPTP_TX_STATUE_ERROR == s_new_timestamp[port_number])
            {
                s_tx_id_error++;
            }
            else
            {
                s_tx_time_out++;
            }
        }
        s_tx_timestamp_id[port_number] = (s_tx_timestamp_id[port_number] + 1) & 0x007f;
    }

    send_end:
        s_new_timestamp[port_number] = GPTP_TX_STATUE_IDLE;

    return;
}

/**********************************************************************************************************************
 * End of function send_frame
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: set_clock_value
 * Description  : Set the clock to an new time value
 * Arguments    : clock_id      - The clock id of the clock that should be set
 *                time_to_set   - The time that should be set
 * Return Value : None
 *********************************************************************************************************************/
void set_clock_value(uint8_t clock_id, st_timestamp_t * p_time_to_set)
{
    gptp_timer_value_t       current_time   = {0};

    s_gptp_instance->p_api->timerValueGet(s_gptp_instance->p_ctrl, clock_id, &current_time);

    uint64_t timestamp_master = (uint64_t) p_time_to_set->seconds_lsb  * ONE_SECOND_UINT64 + \
            (uint64_t)p_time_to_set->nanoseconds;
    uint64_t timestamp_slave  = (uint64_t) current_time.time_sec_lower * ONE_SECOND_UINT64 + \
            (uint64_t)current_time.time_nsec;
    int64_t offset = (int64_t)(timestamp_master - timestamp_slave);

    s_gptp_instance->p_api->timerOffsetSet(s_gptp_instance->p_ctrl, clock_id, offset);

    gptp_clock_pulser(GPTP_OUTPUT_PULSE_PERIOD);
    return;
}
/**********************************************************************************************************************
 * End of function set_clock_value
 *********************************************************************************************************************/

void set_and_adjust(uint8_t clock_id, int64_t offset_from_master)
{
    if ((offset_from_master < GPTP_RATE_THREDHOLD) && (offset_from_master > -GPTP_RATE_THREDHOLD))
    {
        adjust_clock(clock_id, offset_from_master);

    }
    else
    {
        s_gptp_instance->p_api->timerOffsetSet(s_gptp_instance->p_ctrl, clock_id, offset_from_master);

/* If ETHSW Freq is 250MHz, cannot to sync only offsetSet,  */
#if (4 == ETHSW_CLOCK_PERIOD)
        adjust_clock(clock_id, (offset_from_master * (int64_t)ETHSW_CLOCK_RATE_CORRECTION));
#endif
    }
    return;
}

/**********************************************************************************************************************
 * Function Name: get_clock_value
 * Description  : Get the current time value in a timestamp format
 * Arguments    : clock_id              - The clock id of the clock that should be read
 *                current_clock_Value   - The current clock value
 * Return Value : None
 *********************************************************************************************************************/
void get_clock_value(uint8_t clock_id, st_timestamp_t * p_current_clock_value)
{
    gptp_timer_value_t get_time = {0};

    s_gptp_instance->p_api->timerValueGet(s_gptp_instance->p_ctrl, clock_id, &get_time);

    p_current_clock_value->seconds_msb = 0;
    p_current_clock_value->seconds_lsb = get_time.time_sec_lower;
    p_current_clock_value->nanoseconds = get_time.time_nsec;

    return;
}
/**********************************************************************************************************************
 * End of function get_clock_value
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: get_clock_value_all
 * Description  : Get the current time value in a timestamp format
 * Arguments    : p_current_clock_value1   - Current clock value of timer 0
 *                p_current_clock_value2   - Current clock value of timer 1
 * Return Value : None
 *********************************************************************************************************************/
void get_clock_value_all(st_timestamp_t * p_current_clock_value1, st_timestamp_t * p_current_clock_value2)
{
    gptp_timer_value_t get_time1 = {0};
    gptp_timer_value_t get_time2 = {0};

    __disable_irq();
    s_gptp_instance->p_api->timerValueGet(s_gptp_instance->p_ctrl, LOCAL_CLOCK_TIMER, &get_time1);
    s_gptp_instance->p_api->timerValueGet(s_gptp_instance->p_ctrl, SYNCRHONIZED_CLOCK_TIMER, &get_time2);
    __enable_irq();

    p_current_clock_value1->seconds_msb = 0;
    p_current_clock_value1->seconds_lsb = get_time1.time_sec_lower;
    p_current_clock_value1->nanoseconds = get_time1.time_nsec;

    p_current_clock_value2->seconds_msb = 0;
    p_current_clock_value2->seconds_lsb = get_time2.time_sec_lower;
    p_current_clock_value2->nanoseconds = get_time2.time_nsec;

    return;
}
/**********************************************************************************************************************
 * End of function get_clock_value_all
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: adjust_clock
 * Description  : Adjust the clock
 * Arguments    : clock_id  - The clock id of the clock which should be adjusted
 *                offset    - The offset that should be adjusted
 * Return Value : None
 *********************************************************************************************************************/
void adjust_clock(uint8_t clock_id, int64_t offset)
{
    static uint32_t rate_value = CLK_CLOCK_200MHZ;
    static int64_t offset_old = 0;

    float offset_rate  = 0.0;

    if(abs((int32_t)offset_old) < abs((int32_t)offset))
    {
        if(0 < offset)
        {
            offset_rate = ((float)(offset) / (float)CLOCK_FREQ);
            rate_value  += (uint32_t)(offset_rate * (2 << 26));
        }
        else if(0 > offset)
        {
            offset_rate = ((float)(offset * (int64_t)-1 ) / (float)CLOCK_FREQ);
            rate_value  -= (uint32_t)(offset_rate * (2 << 26));
        }
        else
        {
            // rate value is not changed
        }

        s_gptp_instance->p_api->timerRateSet(s_gptp_instance->p_ctrl, clock_id, rate_value);
    }
    offset_old = offset;
    return;
}
/**********************************************************************************************************************
 * End of function adjust_clock
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: generate_clock_identity
 * Description  : Generate the clock identity for the ptp instance on the device
 * Arguments    : None
 * Return Value : None
 *********************************************************************************************************************/
/*void generate_clock_identity(void)
{
    gptp_info.clock_identity.element[0] = gptp_info.mac_address[0];
    gptp_info.clock_identity.element[1] = gptp_info.mac_address[1];
    gptp_info.clock_identity.element[2] = gptp_info.mac_address[2];
    gptp_info.clock_identity.element[3] = 0xff;
    gptp_info.clock_identity.element[4] = 0xfe;
    gptp_info.clock_identity.element[5] = gptp_info.mac_address[3];
    gptp_info.clock_identity.element[6] = gptp_info.mac_address[4];
    gptp_info.clock_identity.element[7] = gptp_info.mac_address[5];
    return;
}*/
/**********************************************************************************************************************
 * End of function generate_clock_identity
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: get_src_mac_address
 * Description  : Get the source mac address of a port
 * Arguments    : None
 * Return Value : port_src_mac_addr - Pointer to the associated source mac address
 *********************************************************************************************************************/
uint8_t * get_src_mac_address(void)
{
    return g_mac_address;
}

static void set_pps_signal(uint8_t timer, uint32_t seconds_to_set, uint32_t nanoseconds_to_set)
{
    gptp_pulse_generator_t pps =  {0};
    gptp_pulsed_output_cfg_t pps_cfgs[BSP_FEATURE_ESWM_GPTP_PULSE_GENERATOR_NUM] = {0};

    for (uint8_t i = 0; i < BSP_FEATURE_ESWM_GPTP_PULSE_GENERATOR_NUM; i++)
    {
        pps_cfgs[i].pulse_num        = timer;
        pps_cfgs[i].start_sec_lower  = seconds_to_set + 1;
        pps_cfgs[i].start_sec_upper  = 0;
        pps_cfgs[i].start_ns         = nanoseconds_to_set+1;
        pps_cfgs[i].period_sec_lower = 1;
        pps_cfgs[i].period_sec_upper = 0;
        pps_cfgs[i].period_ns        = 0;
        pps_cfgs[i].wide             = 62500;
        pps.p_pulsed_output_cfg_list[i] = &pps_cfgs[i];
      }

    R_GPTP_PulseGeneratorSet(s_gptp_instance->p_ctrl, timer, &pps);

    return;
}

// 2024.05.17 refs #5490 <start>
/*
 *
 */
int gptp_clock_pulser( gptp_pulse_period_t period )
{
    fsp_err_t                   ercd;
    gptp_timer_value_t          ts = {0};
    gptp_pulse_generator_t      pulse = {0};
    gptp_pulsed_output_cfg_t    pulse_cfgs[BSP_FEATURE_ESWM_GPTP_PULSE_GENERATOR_NUM] = {0};
    uint32_t    time_num = SYNCRHONIZED_CLOCK_TIMER;

    ercd = s_gptp_instance->p_api->timerValueGet(s_gptp_instance->p_ctrl, (uint8_t) time_num, &ts);

    if ( FSP_SUCCESS != ercd )
    {
        USR_DEBUG_PRINT( "%s:failed to tsGet. ercd =[%d]\n",
                         __func__,
                         ercd );
        goto gptp_clock_pulser_end;
    }

    for (uint8_t i = 0; i < BSP_FEATURE_ESWM_GPTP_PULSE_GENERATOR_NUM; i++)
    {
        pulse_cfgs[i].pulse_num        = 0;
        pulse_cfgs[i].start_sec_lower  = ts.time_sec_lower + 2;
        pulse_cfgs[i].start_sec_upper  = ts.time_sec_upper;
        pulse_cfgs[i].start_ns         = 0;
        pulse.p_pulsed_output_cfg_list[i] = &pulse_cfgs[i];
    }

    switch ( period )
    {
        case GPTP_PULSE_PERIOD_SEC:
            for (uint8_t i = 0; i < BSP_FEATURE_ESWM_GPTP_PULSE_GENERATOR_NUM; i++)
            {
                pulse_cfgs[i].wide             = 62500;       // wide: 62500 * 8 = 500,000ns = 500us
                pulse_cfgs[i].period_sec_lower = 1;           // period: 1s
                pulse_cfgs[i].period_sec_upper = 0;           // period: 1s
                pulse_cfgs[i].period_ns        = 0;
                pulse.p_pulsed_output_cfg_list[i] = &pulse_cfgs[i];
            }
            break;
        case GPTP_PULSE_PERIOD_MSEC:
            for (uint8_t i = 0; i < BSP_FEATURE_ESWM_GPTP_PULSE_GENERATOR_NUM; i++)
            {
                pulse_cfgs[i].wide             = 62500;       // wide: 625 * 8 = 5,000ns = 5us
                pulse_cfgs[i].period_sec_lower = 0;           // period: 1ms
                pulse_cfgs[i].period_sec_upper = 0;           // period: 1ms
                pulse_cfgs[i].period_ns        = 1000*1000;
                pulse.p_pulsed_output_cfg_list[i] = &pulse_cfgs[i];
            }
            break;
        default:
            goto gptp_clock_pulser_end;
    }

    ercd = R_GPTP_PulseGeneratorSet (s_gptp_instance->p_ctrl, (uint8_t)time_num, &pulse);

    if ( FSP_SUCCESS != ercd )
    {
        USR_DEBUG_PRINT( "%s:failed to pulseGeneratorSet. ercd =[%d]\n",
                         __func__,
                         ercd );
        goto gptp_clock_pulser_end;
    }

gptp_clock_pulser_end:

    return 0;
}

void gptp_link_status(uint8_t port_num, ether_event_t link_status)
{
    if(NUMBER_OF_ETHERNET_PORTS < port_num)
    {
        return;
    }

    if((ETHER_EVENT_LINK_OFF != link_status) && (ETHER_EVENT_LINK_ON != link_status))
    {
        return;
    }

    uint8_t instance_cnt = 0;
    bool external_port_configuration_enabled = false;
    link_state_check[port_num] = link_status;

    if (link_status != link_state_last[port_num])
    {
        if (LINK_DOWN == link_status)
        {
            USR_LOG_INFO("Link down on Port %d", port_num + 1);
            for (instance_cnt = 0; instance_cnt < NUMBER_OF_INSTANCES; instance_cnt++)
            {
                if (INSTANCE_ACTIVE == is_instance_active(instance_cnt))
                {
                    //USR_LOG_INFO("Port_Number %u", port_num);
                    delete_gptp_capable_rx_timeout_timer(instance_cnt, port_num);
                    stop_gptp_capable_tx_timer(instance_cnt,port_num);
                    stop_pdelay_req_tx_timer(port_num);
                    g_domains[instance_cnt].per_port[port_num].as_capable = NOT_AS_CAPABLE;
                    g_domains[instance_cnt].per_port[port_num].global_port_parameters->as_capable_across_domains = NOT_AS_CAPABLE_ACROSS_DOMAINS;
                    g_domains[instance_cnt].per_port[port_num].global_port_parameters->mean_link_delay = 0;
                    g_domains[instance_cnt].per_port[port_num].global_port_parameters->neighbor_rate_ratio = 0;
                    if (SYNC_MASTER == g_sync_state[instance_cnt])
                    {
                        stop_tx_sync_timer(instance_cnt, port_num);
                        stop_tx_announce_timer(instance_cnt, port_num);
                    }
                    read_external_port_configuration_enabled(instance_cnt, &external_port_configuration_enabled);
                    if(false == external_port_configuration_enabled)
                    {
                        if (g_domains[instance_cnt].selected_state[port_num] == slave_port)
                        {
                            delete_sync_timeout_timer(instance_cnt);
                            stop_announce_rx_timeout_timer(instance_cnt,port_num);
                        }
                        g_master_selection[instance_cnt].port_specific[port_num].info_is = disabled;
                        g_master_selection[instance_cnt].selected[port_num] = false;
                        g_master_selection[instance_cnt].reselect[port_num] = true;
                        port_state_selection(instance_cnt);


                    }
                    //??
                    // if(i==get_slave_port(instance_cnt)){
                    //     reset_sync_role(instance_cnt);
                    // }
                    //??
                    stop_announce_rx_timeout_timer(instance_cnt, port_num);
                }
            }
        }
        else if (LINK_DOWN != link_status)
        {
            USR_LOG_INFO("Link up on Port %d", port_num + 1);

            for (instance_cnt = 0; instance_cnt < NUMBER_OF_INSTANCES; instance_cnt++)
            {
                if (INSTANCE_ACTIVE == is_instance_active(instance_cnt))
                {
                    //USR_LOG_INFO("Instance %i active", instance_cnt);
                    start_gptp_capable_tx_timer(instance_cnt,port_num);
                    start_pdelay_req_tx_timer(port_num);
                }
            }
        }
        else
        {
            ;
        }
    }
    link_state_last[port_num] = link_status;

    for (instance_cnt = 0; instance_cnt < NUMBER_OF_INSTANCES; instance_cnt++)
    {
        if (INSTANCE_ACTIVE == is_instance_active(instance_cnt))
        {
            read_external_port_configuration_enabled(instance_cnt, &external_port_configuration_enabled);
            if ((!port_as_capable(instance_cnt)) && (SYNC_MASTER == g_sync_state[instance_cnt]) && \
                (false == external_port_configuration_enabled))
            {
                g_sync_state[instance_cnt] = SYNC_INIT;
                g_ptp_clock_timer[instance_cnt].in_operation = false;
                map_instance_to_hardware_clock_timer();
            }
        }

    }
}

void gptp_recv_func(uint8_t *recv_buff,
                    uint16_t recv_size,
                    uint16_t recv_port,
                    rmac_timestamp_t * p_timestamp)
{
    static st_timestamp_t   s_receive_timestamp = {0};
    static st_timestamp_t   s_working_time      = {0};
    gptp_timer_value_t      current_time        = {0};
    gptp_timer_value_t      working_time        = {0};

    static uint8_t          s_rx_frame[512]     = {0};
    uint16_t                cnt                 = 0;
    int32_t                 capture_diff        = 0;
    uint8_t                 ptp_message_id      = 0;
    uint32_t ingress_latency                    = RX_PHY_DELAY;

    ptp_message_id = (recv_buff[RX_FRAME_MESSAGE_ID_OFFSET])&MESSAGE_ID_MASK;

    st_timestamp_t recv_timestamp = {0};
    recv_timestamp.seconds_lsb = p_timestamp->sec_lower;
    recv_timestamp.nanoseconds = p_timestamp->ns;

    memset(&s_rx_frame, 0, 512);
    memset(&s_receive_timestamp, 0, sizeof(st_timestamp_t));

    /*extract and correct rx timestamp*/
    if ((ptp_message_id == MESSAGE_ID_SYNC)||(ptp_message_id == MESSAGE_ID_PDELAY_REQUEST)||(ptp_message_id == MESSAGE_ID_PDELAY_RESPONSE))
    {
        if (ptp_message_id == MESSAGE_ID_SYNC) // if the frame contains a sync message
        {
            __disable_irq();
            s_gptp_instance->p_api->timerValueGet(s_gptp_instance->p_ctrl, LOCAL_CLOCK_TIMER, &current_time);
            s_gptp_instance->p_api->timerValueGet(s_gptp_instance->p_ctrl, SYNCRHONIZED_CLOCK_TIMER, &working_time);
            __enable_irq();

            s_receive_timestamp.seconds_msb = 0;
            s_receive_timestamp.seconds_lsb = recv_timestamp.seconds_lsb;
            s_receive_timestamp.nanoseconds = recv_timestamp.nanoseconds;

            // timestamp correction for second gptp driver function processing time
            if(GPTP_TIME_VALUE_GET_PROCESSING_TIME > s_receive_timestamp.nanoseconds)
            {
                s_receive_timestamp.seconds_lsb = s_receive_timestamp.seconds_lsb - 1;
                s_receive_timestamp.nanoseconds = s_receive_timestamp.nanoseconds + ONE_SECOND;
            }

            s_receive_timestamp.nanoseconds = s_receive_timestamp.nanoseconds - \
                    GPTP_TIME_VALUE_GET_PROCESSING_TIME;

            // calculate reception delay
            if (s_receive_timestamp.nanoseconds < ingress_latency)
            {
                s_receive_timestamp.seconds_lsb = s_receive_timestamp.seconds_lsb - 1;
                s_receive_timestamp.nanoseconds = s_receive_timestamp.nanoseconds + ONE_SECOND;
            }

            s_receive_timestamp.nanoseconds = s_receive_timestamp.nanoseconds - ingress_latency;

            if(current_time.time_nsec > s_receive_timestamp.nanoseconds)
            {
                capture_diff = (int32_t)current_time.time_nsec - (int32_t)s_receive_timestamp.nanoseconds;
            }
            else
            {
                capture_diff = (int32_t)current_time.time_nsec - (int32_t)s_receive_timestamp.nanoseconds + \
                        (int32_t)ONE_SECOND;
            }

            s_working_time.seconds_msb = 0;
            if (0 > ((int32_t)working_time.time_nsec - (int32_t)capture_diff))
            {
                s_working_time.seconds_lsb = working_time.time_sec_lower - 1;
                s_working_time.nanoseconds = ONE_SECOND + working_time.time_nsec - (uint32_t)capture_diff;
            }
            else
            {
                s_working_time.seconds_lsb = working_time.time_sec_lower;
                s_working_time.nanoseconds = working_time.time_nsec - (uint32_t)capture_diff;
            }
        }
        else
        {
            s_receive_timestamp.seconds_msb = 0;
            s_receive_timestamp.seconds_lsb = recv_timestamp.seconds_lsb;
            s_receive_timestamp.nanoseconds = recv_timestamp.nanoseconds;

            // calculate reception delay
            if (s_receive_timestamp.nanoseconds < ingress_latency)
            {
                s_receive_timestamp.seconds_lsb = s_receive_timestamp.seconds_lsb - 1;
                s_receive_timestamp.nanoseconds = s_receive_timestamp.nanoseconds + ONE_SECOND;
            }

            s_receive_timestamp.nanoseconds = s_receive_timestamp.nanoseconds - ingress_latency;
        }
    }
    for (cnt = 0; cnt < recv_size; cnt++)
    {
        s_rx_frame[cnt] = recv_buff[cnt];
    }

    /*Cast from uint8 to uint8_t* */
    receive_8021_as_frame(recv_port, (uint8_t *)s_rx_frame, &s_working_time, &s_receive_timestamp);
}

fsp_err_t gptp_initialize (gptp_eswm_instance_ctrl_t * const p_ctrl)
{
	fsp_err_t err = FSP_SUCCESS;
    rmac_extended_cfg_t * p_ether_extend;
    layer3_switch_extended_cfg_t * p_switch_extend;

    for (uint8_t i = 0; i < NUMBER_OF_ETHERNET_PORTS; i++)
{
        if (NULL != p_ctrl->p_cfg->p_ether_instances[i])
    {
            s_ether_instances[i] = p_ctrl->p_cfg->p_ether_instances[i];
            err = s_ether_instances[i]->p_api->callbackSet(s_ether_instances[i]->p_ctrl, gptp_link_process_cb, NULL, NULL);

            /* Get the gptp instance. */
            p_ether_extend = (rmac_extended_cfg_t *)p_ctrl->p_cfg->p_ether_instances[i]->p_cfg->p_extend;
            p_switch_extend = (layer3_switch_extended_cfg_t *)p_ether_extend->p_ether_switch->p_cfg->p_extend;
                if (NULL != p_switch_extend->p_gptp_instance)
            {
                s_gptp_instance = p_switch_extend->p_gptp_instance;
            }

        }
    }

    memcpy(&g_mac_address[0], p_ctrl->p_mac_address, 6);

    initialize8021AS();

    return err;
}

void gptp_link_process_cb(ether_callback_args_t * p_args)
{
    gptp_link_status((uint8_t)p_args->channel, p_args->event);
    return;
}

fsp_err_t gptp_link_process(void)
{
	fsp_err_t err = FSP_SUCCESS;
    for(uint8_t rmac_cnt = 0; rmac_cnt < NUMBER_OF_ETHERNET_PORTS; rmac_cnt++)
    {
       if(NULL == s_ether_instances[rmac_cnt])
       {
           continue;
       }

       err = s_ether_instances[rmac_cnt]->p_api->linkProcess(s_ether_instances[rmac_cnt]->p_ctrl);
    }
    return err;
}

void gptp_read(void)
{
    rmac_timestamp_t timestamp = {0};

    uint8_t  recv_buffer[GPTP_MAXIMUM_ETHERNET_FRAME_SIZE] = {0};
    uint8_t* p_recv_buff_address = NULL;
    uint32_t recv_length = 0;

    for(uint8_t rmac_cnt = 0; rmac_cnt < NUMBER_OF_ETHERNET_PORTS; rmac_cnt++)
    {
       if(NULL == s_ether_instances[rmac_cnt])
       {
           continue;
       }

       fsp_err_t err = FSP_SUCCESS;

       ether_zerocopy_t zero_copy_mode = s_ether_instances[rmac_cnt]->p_cfg->zerocopy;

       while(FSP_SUCCESS == err)
       {
           R_RMAC_GetRxTimestamp(s_ether_instances[rmac_cnt]->p_ctrl, &timestamp);
           if(ETHER_ZEROCOPY_ENABLE == zero_copy_mode)
           {
               err = s_ether_instances[rmac_cnt]->p_api->read(s_ether_instances[rmac_cnt]->p_ctrl, (void *)&p_recv_buff_address, &recv_length);
           }
           else
           {
               err = s_ether_instances[rmac_cnt]->p_api->read(s_ether_instances[rmac_cnt]->p_ctrl, (void *) recv_buffer, &recv_length);
               p_recv_buff_address = recv_buffer;
           }

           if(FSP_SUCCESS == err)
           {
               gptp_recv_func(p_recv_buff_address, (uint16_t)recv_length, s_ether_instances[rmac_cnt]->p_cfg->channel, &timestamp);
           }

           if(ETHER_ZEROCOPY_ENABLE == zero_copy_mode)
           {
               err = s_ether_instances[rmac_cnt]->p_api->bufferRelease(s_ether_instances[rmac_cnt]->p_ctrl);
           }
       }
    }

    return;
}

gptp_send_result_t gptp_write(uint8_t *p_send_buff, uint16_t frame_length, uint8_t port_number, rmac_timestamp_t * p_timestamp)
{
    // invalid argument
    if(port_number >= NUMBER_OF_ETHERNET_PORTS)
    {
        return GPTP_SEND_RESULT_FAILURE;
    }

    // RMAC is not open
    if(NULL == s_ether_instances[port_number])
    {
        return GPTP_SEND_RESULT_FAILURE;
    }

    if(NULL != p_timestamp)
    {
        rmac_write_cfg_t write_cfg = {.tx_timestamp_enable = 1,};
        R_RMAC_SetWriteConfig(s_ether_instances[port_number]->p_ctrl, &write_cfg);
    }

    fsp_err_t err = s_ether_instances[port_number]->p_api->write(s_ether_instances[port_number]->p_ctrl, p_send_buff, frame_length);
    if(FSP_SUCCESS == err)
    {
        if(NULL != p_timestamp)
        {
            R_RMAC_GetTxTimestamp(s_ether_instances[port_number]->p_ctrl, p_timestamp);
        }
        return GPTP_SEND_RESULT_SUCCESS;
    }
    else if(FSP_ERR_NOT_FOUND == err)
    {
        return GPTP_SEND_RESULT_TRANSMIT_TIMESTAMP_GET_FAILURE;
    }
    return GPTP_SEND_RESULT_FAILURE;
}

void gptp_send(void)
{
    message_generation(NULL);
}

void get_link_state (uint16_t port_number, uint8_t * state)
{
    rmac_instance_ctrl_t * p_rmac_instance_ctrl;
    for (uint8_t rmac_cnt = 0; rmac_cnt < NUMBER_OF_ETHERNET_PORTS; rmac_cnt++)
    {
        if (NULL == s_ether_instances[rmac_cnt])
        {
            continue;
        }

        s_ether_instances[rmac_cnt]->p_api->linkProcess(s_ether_instances[rmac_cnt]->p_ctrl);
        if (rmac_cnt == port_number)
        {
            *state = ((rmac_instance_ctrl_t *)(s_ether_instances[rmac_cnt]->p_ctrl))->link_establish_status;
        }
    }
}
