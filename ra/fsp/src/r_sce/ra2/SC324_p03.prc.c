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

/////////////////////////////////////////////////////////////////////////
// <SC32#4 128bit Random Number Generation>                            //
// Procedure number: 03                                                //
// File name      : SC324_p03.prc                                      //
// State Diagram  : main(FSM1)                                         //
// Start State    : main03                                             //
// End State      : main03                                             //
// Input Data     : void                                               //
// Output Data    : OutData_Text[4]                                    //
// Return Value   : Pass or Resource_Conflict                          //
// ---------------------------------------------------------------------//
// total cycle    : polling + write access + read access               //
// polling        :     cycle                                          //
// polling access :     cycle                                          //
// write access   :     times                                          //
// read  access   :     times                                          //
/////////////////////////////////////////////////////////////////////////

#include "SC324_private.h"
#include "bsp_api.h"
#include "hw_sce_trng_private.h"

/*******************************************************************************************************************//**
 * 128bit Random Number Generation
 * @param      OutData_Text    The out data text
 * @retval FSP_SUCCESS      The operation completed successfully.
 **********************************************************************************************************************/
fsp_err_t HW_SCE_RNG_Read (uint32_t * OutData_Text) {
    uint8_t * ptmp = (uint8_t *) OutData_Text;
    uint32_t  k;

    for (k = 0; k < 4; k++)            // read 4 words of random data similar (to make this API consistent with S7 and S3 implementation)
    {
        /* Set core_en bit and rng_start bit */
        SCE1_TRNG->TRNGSCR0.core_en   = 1;
        SCE1_TRNG->TRNGSCR0.rng_start = 1;

        /* Wait for RDRDY bit to be set */
        while (0 == SCE1_TRNG->TRNGSCR0.rdrdy)
        {
        }

        /* Read generated random data */
        *ptmp++ = SCE1_TRNG->REG_00H;
        *ptmp++ = SCE1_TRNG->REG_00H;
        *ptmp++ = SCE1_TRNG->REG_00H;
        *ptmp++ = SCE1_TRNG->REG_00H;
    }

    return FSP_SUCCESS;
}
