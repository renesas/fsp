/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/**********************************************************************************************************************
 * File Name    : r_vdev_fsbl_option.h
 * Version      : 1.0
 * Description  : .
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 *********************************************************************************************************************/
#include "common.h"

/**********************************************************************************************************************
 Macro definitions
 *********************************************************************************************************************/
#ifndef SRC_VDEV_R_VDEV_FSBL_OPTION_H_
#define SRC_VDEV_R_VDEV_FSBL_OPTION_H_

#define VFSBL_u32FSBLCTRL0                  (*(( volatile u32 *)( CM_u32BASE_FSBLOPTION + (u32)(0x00000080))))
#define VFSBL_u32FSBLCTRL0_FSBLCLK_MASK     ( (u32)0x00000E00 )
#define VFSBL_u32FSBLCTRL0_FSBLCLK_BIT_NUM  ( (u32)3 )

#define VFSBL_u32FSBLCTRL1                  (*(( volatile u32 *)( CM_u32BASE_FSBLOPTION + (u32)(0x00000084))))
#define VFSBL_u32FSBLCTRL1_FSBLEXMD_MASK    ( (u32)0x00000003 )
#define VFSBL_u32FSBLCTRL1_FSBLEXMD_00      ( (u32)0x00000000 )
#define VFSBL_u32FSBLCTRL1_FSBLEXMD_01      ( (u32)0x00000001 )
#define VFSBL_u32FSBLCTRL1_FSBLEXMD_10      ( (u32)0x00000002 )
#define VFSBL_u32FSBLCTRL1_FSBLEXMD_11      ( (u32)0x00000003 )

#define VFSBL_u32FSBLCTRL2                  (*(( volatile u32 *)( CM_u32BASE_FSBLOPTION + (u32)(0x00000088))))
#define VFSBL_u32FSBLCTRL2_PORTPN_MASK      ( (u32)0x0000000F )
#define VFSBL_u32FSBLCTRL2_PORTGN_MASK      ( (u32)0x000001F0 )
#define VFSBL_u32FSBLCTRL2_PORTGN_SHIFT     ( (u32)4 )

#define VFSBL_u32SACC0                      (*(( volatile u32 *)( CM_u32BASE_FSBLOPTION + (u32)(0x0000008C))))

#define VFSBL_u32SACC1                      (*(( volatile u32 *)( CM_u32BASE_FSBLOPTION + (u32)(0x00000090))))

#define VFSBL_u32SAMR                       (*(( volatile u32 *)( CM_u32BASE_FSBLOPTION + (u32)(0x00000094))))

#define VFSBL_OEMROOTPKHASH_ADDR            ( CM_u32BASE_FSBLOPTION + (u32)(0x00000360))

#define VFSBL_FCNTDATAR0                    (*(( volatile u32 *)( CM_u32BASE_FSBLOPTION + (u32)(0x00000878))))
#define VFSBL_FCNTDATAR1                    (*(( volatile u32 *)( CM_u32BASE_FSBLOPTION + (u32)(0x0000087C))))

/**********************************************************************************************************************
 Global Typedef definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 External global variables
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Exported global functions
 *********************************************************************************************************************/

#endif /* SRC_VDEV_R_VDEV_FSBL_OPTION_H_ */
