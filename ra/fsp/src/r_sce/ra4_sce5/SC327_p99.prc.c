/***********************************************************************************************************************
 * Copyright [2020] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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

//////////////////////////////////////////////////////////////////////////
// <SC32#7 Secure Boot procedure>                                       //
// Procedure number: 99                                                 //
// File name       : SC327_p99.prc                                      //
// State Diagram   : main(FSM1)                                         //
// Start State     : main02                                             //
// End State       : main03                                             //
// Input Data      : void                                               //
// Output Data     : void                                               //
// Return value    : Pass, Resource_Conflict                            //
// ----------------------------------------------------------------------//
// total cycle     : polling + write access + read access               //
// polling         :  TBD                                               //
// polling access  :  TBD                                               //
// write access    :  TBD                                               //
// read  access    :  TBD                                               //
//////////////////////////////////////////////////////////////////////////

#include "SCE_ProcCommon.h"
#include "hw_sce_private.h"

/*******************************************************************************************************************//**
 * Secure Boot procedure
 * @retval FSP_SUCCESS          The operation completed successfully.
 **********************************************************************************************************************/
fsp_err_t HW_SCE_secureBoot (void) {
    return FSP_SUCCESS;
}
