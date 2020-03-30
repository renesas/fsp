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

/*******************************************************************************************************************//**
 * @ingroup SCE
 * @addtogroup SCE_PROC
 * @{
 ***********************************************************************************************************************/

#ifndef HW_SCE_PRIVATE_H
#define HW_SCE_PRIVATE_H

/**********************************************************************************************************************
 * Includes
 ***********************************************************************************************************************/
#include "bsp_api.h"
#include "hw_sce_common.h"

/**********************************************************************************************************************
 * Macro definitions
 ***********************************************************************************************************************/
#define R_SCE_S_HEAP_SIZE    256
#define R_SCE_S_RAM_SIZE     80

/**********************************************************************************************************************
 * Typedef definitions
 ***********************************************************************************************************************/

typedef enum e_crypto_word_endian
{
    CRYPTO_WORD_ENDIAN_BIG    = 0,
    CRYPTO_WORD_ENDIAN_LITTLE = 1
} crypto_word_endian_t;

/**********************************************************************************************************************
 * Function Prototypes
 ***********************************************************************************************************************/

/**********************************************************************************************************************
 * Includes
 ***********************************************************************************************************************/

extern uint32_t S_RAM[R_SCE_S_RAM_SIZE];
extern uint32_t S_HEAP[R_SCE_S_HEAP_SIZE];

extern void HW_SCE_SoftReset(void);

extern fsp_err_t HW_SCE_Initialization1(void);

extern fsp_err_t HW_SCE_Initialization2(void);

void      HW_SCE_Initialization1_Subproc1(void);
void      HW_SCE_Initialization2_Subproc2(void);
void      SC32_Subprc03(void);
void      SC32_Subprc04(void);
void      SC32_Subprc05(void);
fsp_err_t HW_SCE_secureBoot(void);

void                 HW_SCE_EndianSetBig(void);
void                 HW_SCE_EndianSetLittle(void);
crypto_word_endian_t HW_SCE_EndianFlagGet(void);

#endif                                 /* HW_SCE_PRIVATE_H */

/*******************************************************************************************************************//**
 * @} (end addtogroup SCE_PROC)
 ***********************************************************************************************************************/
